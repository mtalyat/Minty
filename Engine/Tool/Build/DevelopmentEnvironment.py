from __future__ import annotations

import sys
import os
import re
import argparse
import time
import shutil
from pathlib import Path
if __name__ == "__main__":
    sys.path.insert(0, str(Path(__file__).parent.parent))
from Build.HeaderGeneration import generate_directory_header
from Util import Environment
from Util import Command

LINE_SIZE = 40
LINE_CHAR_SMALL = '-'
LINE_CHAR_MED = '='
LINE_CHAR_LARGE = '#'

def create_line(text: str = '', char: str = LINE_CHAR_SMALL, width: int = LINE_SIZE) -> str:
    return f"{char * ((width - len(text)) // 2)}{text}{char * ((width - len(text)) // 2 + (width - len(text)) % 2)}"

def print_line(text: str = '', char: str = LINE_CHAR_SMALL, width: int = LINE_SIZE) -> None:
    if len(text) == 0:
        print(char * width)
    else:
        print(create_line(f' {text} ', char, width))

ACTION_CLEAN = 0x1
ACTION_BUILD = 0x2
ACTION_RUN = 0x4

ACTIONS = {
    'clean': ACTION_CLEAN,
    'build': ACTION_BUILD,
    'run': ACTION_RUN,
    'rebuild': ACTION_CLEAN | ACTION_BUILD,
    'rerun': ACTION_BUILD | ACTION_RUN,
    'all': ACTION_CLEAN | ACTION_BUILD | ACTION_RUN,
}

CONFIG_DEBUG = 0x1
CONFIG_RELEASE = 0x2
CONFIGS = {
    'debug': CONFIG_DEBUG,
    'release': CONFIG_RELEASE
}

ARCHITECTURE_32 = 0x1
ARCHITECTURE_64 = 0x2
ARCHITECTURE_ARM64 = 0x4
ARCHITECTURES = {
    'x64': ARCHITECTURE_64,
    'x86': ARCHITECTURE_32,
    'arm64': ARCHITECTURE_ARM64
}

RENDER_VULKAN = 0x1
RENDERS = {
    'vulkan': RENDER_VULKAN,
}

AUDIO_SOLOUD = 0x1
AUDIOS = {
    'soloud': AUDIO_SOLOUD,
}

MINTY_PATH_ENV = 'MINTY_PATH'
MINTY_PATH = Environment.get_environment_variable(MINTY_PATH_ENV, permanent=True)

ROOT = Path(__file__).resolve().parents[2]
SOURCE_ROOT = ROOT / "Source"
OUTPUT_DIR = ROOT / "Output"
ARTIFACTS_DIR = OUTPUT_DIR / "Artifacts"
BUILD_ROOT = OUTPUT_DIR / "Build"


def _discover_layers() -> list[str]:
    if not SOURCE_ROOT.exists():
        return []

    return sorted(
        [
            path.name
            for path in SOURCE_ROOT.iterdir()
            if path.is_dir() and (path / 'CMakeLists.txt').exists()
        ],
        key=str.lower,
    )


def _artifact_directory(config_name: str) -> Path:
    return ARTIFACTS_DIR / config_name


def _artifact_lib_names_for_layer(layer: str) -> list[str]:
    layer_lower = layer.lower()

    # Most layers output Minty<Layer>.lib.
    default_name = f'Minty{layer}.lib'

    special_names = {
        'library': ['MintyLibrary.lib', 'stb.lib', 'zlib.lib'],
        'libraries': ['MintyLibrary.lib', 'stb.lib', 'zlib.lib'],
    }

    return special_names.get(layer_lower, [default_name])


def _artifact_stems_for_layer(layer: str) -> set[str]:
    return {Path(name).stem for name in _artifact_lib_names_for_layer(layer)}


def _find_library_tool() -> tuple[str | None, bool]:
    lib_tool = shutil.which('lib.exe') or shutil.which('lib')
    if lib_tool:
        return lib_tool, False

    link_tool = shutil.which('link.exe') or shutil.which('link')
    if link_tool:
        return link_tool, True

    program_files_x86 = os.environ.get('ProgramFiles(x86)')
    if program_files_x86:
        vswhere_path = Path(program_files_x86) / 'Microsoft Visual Studio' / 'Installer' / 'vswhere.exe'
        if vswhere_path.exists():
            query_command = [
                str(vswhere_path),
                '-latest',
                '-requires',
                'Microsoft.VisualStudio.Component.VC.Tools.x86.x64',
                '-find',
                r'VC\Tools\MSVC\**\bin\Hostx64\x64\lib.exe',
            ]
            return_code, output = Command.run_command(query_command, ROOT)
            if return_code == 0 and output:
                tool_path = output.splitlines()[0].strip()
                if tool_path:
                    return tool_path, False

    return None, False

def _create_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description='Build and run the development environment.')
    parser.add_argument('action', choices=ACTIONS.keys(), help='Action to perform')
    parser.add_argument('project', nargs='?', default=None, help='Project/layer to build/run (omit for aggregate output library)')
    parser.add_argument('--config', choices=CONFIGS.keys(), default=list(CONFIGS.keys())[0], help='Build configuration')
    parser.add_argument('--arch', choices=ARCHITECTURES.keys(), default=list(ARCHITECTURES.keys())[0], help='Target architecture')
    parser.add_argument('--render', choices=RENDERS.keys(), default=list(RENDERS.keys())[0], help='Rendering backend')
    parser.add_argument('--audio', choices=AUDIOS.keys(), default=list(AUDIOS.keys())[0], help='Audio backend')
    parser.add_argument('--verbose', action='store_true', help='Print full configure/build command output')
    return parser


def _normalize_layer(project: str) -> str:
    project_fixed = re.sub(r'[.\\/]', '', project.lower())
    if project_fixed == 'all':
        return 'All'

    discovered_layers = _discover_layers()

    for layer in discovered_layers:
        if layer.lower() == project_fixed:
            return layer

    if project_fixed == 'libraries':
        for layer in discovered_layers:
            if layer.lower() == 'library':
                return layer

    raise ValueError(f'Unknown project/layer: {project}. Make sure the layer exists and has a CMakeLists.txt file. Discovered layers: {", ".join(sorted(discovered_layers))}')


def _load_layer_list_file(file_path: Path) -> list[str]:
    lines = file_path.read_text(encoding='utf-8').splitlines()
    layers: list[str] = []

    for index, raw_line in enumerate(lines, start=1):
        line = raw_line.strip()
        if not line or line.startswith('#'):
            continue

        try:
            layers.append(_normalize_layer(line))
        except ValueError as error:
            raise ValueError(f"{file_path}:{index}: {error}") from error

    if not layers:
        raise ValueError(f'Layer list file is empty: {file_path}')

    return layers


def _build_directory(layer: str, config: str) -> Path:
    return BUILD_ROOT / layer / config.capitalize()


def _ensure_build_dir_source(build_dir: Path, expected_source_dir: Path) -> None:
    cache_file = build_dir / 'CMakeCache.txt'
    if not cache_file.exists():
        return

    expected = str(expected_source_dir.resolve()).replace('\\', '/').lower()

    try:
        for line in cache_file.read_text(encoding='utf-8', errors='ignore').splitlines():
            if line.startswith('CMAKE_HOME_DIRECTORY:INTERNAL='):
                configured = line.split('=', 1)[1].strip().replace('\\', '/').lower()
                if configured != expected:
                    shutil.rmtree(build_dir)
                    print(f'Removed stale build directory with mismatched source: {build_dir}')
                break
    except OSError:
        pass


def _is_header_file(path: Path) -> bool:
    return path.suffix.lower() in {'.h', '.hpp', '.hh', '.hxx'}


def _has_direct_layer_headers(directory: Path) -> bool:
    return any(
        path.is_file()
        and _is_header_file(path)
        and path.name.lower() != 'pch.h'
        and not path.stem.startswith('__')
        for path in directory.iterdir()
    )


def _has_child_aggregate_headers(directory: Path) -> bool:
    return any(
        child.is_dir() and (child / f'__{child.name}.h').exists()
        for child in directory.iterdir()
    )


def _generate_layer_headers(layer: str) -> list[Path]:
    # Library intentionally opts out of generated aggregate headers.
    if layer.lower() == 'library':
        return []

    layer_root = SOURCE_ROOT / layer
    if not layer_root.is_dir():
        raise ValueError(f'Layer directory does not exist: {layer_root}')

    directories = [path for path in layer_root.rglob('*') if path.is_dir()]
    directories.sort(key=lambda path: len(path.relative_to(layer_root).parts), reverse=True)
    directories.append(layer_root)

    generated_headers: list[Path] = []
    for directory in directories:
        if not (_has_direct_layer_headers(directory) or _has_child_aggregate_headers(directory)):
            continue

        generated_headers.append(generate_directory_header(directory))

    return generated_headers


def _create_final_library(config_name: str, verbose: bool = False) -> int:
    artifact_dir = _artifact_directory(config_name)
    final_library = artifact_dir / f'{ROOT.name}.lib'
    final_library_name = final_library.name.lower()

    print_line(os.path.splitext(final_library_name)[0].title(), char=LINE_CHAR_LARGE)

    if not artifact_dir.exists():
        print(f'Error: artifact directory does not exist: {artifact_dir}')
        print_line(char=LINE_CHAR_LARGE)
        return 1

    input_libraries = sorted(
        path
        for path in artifact_dir.glob('*.lib')
        if path.resolve() != final_library.resolve() and path.name.lower() != final_library_name
    )

    if not input_libraries:
        print(f'Error: no libraries found in {artifact_dir} to merge into {final_library.name}.')
        print_line(char=LINE_CHAR_LARGE)
        return 1

    # Merge vendor libraries into Engine.lib so downstream projects only link Engine.lib.
    source_root = ROOT / 'Source'
    vendor_libs = [
        source_root / 'Library/Vulkan/Binary/vulkan-1.lib',
        source_root / 'Library/GLFW/Binary/glfw3.lib',
    ]

    if config_name.lower() == 'debug':
        vendor_libs.extend([
            source_root / 'Library/Bullet/Binary/Debug/BulletCollision.lib',
            source_root / 'Library/Bullet/Binary/Debug/BulletDynamics.lib',
            source_root / 'Library/Bullet/Binary/Debug/LinearMath.lib',
        ])
    else:
        vendor_libs.extend([
            source_root / 'Library/Bullet/Binary/Release/BulletCollision.lib',
            source_root / 'Library/Bullet/Binary/Release/BulletDynamics.lib',
            source_root / 'Library/Bullet/Binary/Release/LinearMath.lib',
        ])

    soloud_path = source_root / 'Library/SoLoud/Binary/soloud.lib'
    if not soloud_path.exists():
        soloud_path = source_root / 'Library/SoLoud/Binary/SoLoud.lib'
    if soloud_path.exists():
        vendor_libs.append(soloud_path)

    vendor_libs = [Path(lib) for lib in vendor_libs if Path(lib).exists()]

    if final_library.exists():
        newest_input = 0.0
        for input_library in [*input_libraries, *vendor_libs]:
            try:
                newest_input = max(newest_input, input_library.stat().st_mtime)
            except OSError:
                newest_input = 0.0
                break

        try:
            final_mtime = final_library.stat().st_mtime
        except OSError:
            final_mtime = -1.0

        if newest_input and final_mtime >= newest_input:
            print(f'{final_library.name} is up to date; skipping merge.')
            print_line(char=LINE_CHAR_LARGE)
            return 0

    library_tool, use_link_lib_mode = _find_library_tool()
    if not library_tool:
        print('Error: unable to find MSVC library tool. Expected lib.exe (or link.exe) in PATH or discoverable through vswhere.')
        print_line(char=LINE_CHAR_LARGE)
        return 1

    print(f'Creating {final_library.name}...')
    create_library_command = [library_tool]
    if use_link_lib_mode:
        create_library_command.append('/LIB')
    create_library_command.extend([
        '/nologo',
        f'/OUT:{str(final_library)}',
        *[str(path) for path in input_libraries],
        *[str(path) for path in vendor_libs],
    ])

    if verbose:
        return_code = Command.print_command(create_library_command, ROOT)
    else:
        return_code, output = Command.run_command(create_library_command, ROOT)
        if return_code != 0:
            print(output)

    if return_code != 0:
        print(f'Error: failed to create {final_library}')
        print_line(char=LINE_CHAR_LARGE)
        return return_code

    print(f'Created {final_library}')
    print_line(char=LINE_CHAR_LARGE)
    return 0

def main() -> int:
    if not MINTY_PATH:
        print(f'Error: {MINTY_PATH_ENV} environment variable is not set.')
        return 1
    
    # Parse command-line arguments
    parser = _create_parser()
    args = parser.parse_args()

    action = ACTIONS[args.action]
    project = None
    projects: list[str] = []
    if args.project:
        project_path = Path(args.project)
        if project_path.is_file():
            if action != ACTION_BUILD:
                print('Error: project list files are only supported for the "build" action.')
                return 1

            try:
                projects = _load_layer_list_file(project_path)
            except (OSError, ValueError) as error:
                print(f'Error: {error}')
                return 1
        else:
            try:
                project = _normalize_layer(args.project)
            except ValueError as error:
                print(f'Error: {error}')
                return 1

            projects = [project]

    config = CONFIGS[args.config]
    arch = ARCHITECTURES[args.arch]
    render = RENDERS[args.render]
    audio = AUDIOS[args.audio]

    config_name = 'Debug' if config == CONFIG_DEBUG else 'Release'
    _ = arch  # Reserved for future architecture-specific generator args.
    verbose = args.verbose

    if not args.project:
        if action == ACTION_BUILD:
            return _create_final_library(config_name, verbose)
        print('Error: project/layer is required unless action is "build" for aggregate output library creation.')
        return 1
    
    # Print configuration summary
    print_line(char=LINE_CHAR_LARGE)
    print_line('Configuration Summary', char=LINE_CHAR_MED)
    print(f'Project(s): {", ".join(projects)}')
    print(f'Action: {args.action}')
    print(f'Configuration: {args.config}')
    print(f'Architecture: {args.arch}')
    print(f'Render: {args.render}')
    print(f'Audio: {args.audio}')
    print_line(char=LINE_CHAR_MED)

    # Start timer
    start_time = time.time()

    build_dirs = {project_name: _build_directory(project_name, config_name) for project_name in projects}
    configure_commands: dict[str, list[str]] = {}
    build_commands: dict[str, list[str]] = {}

    for project_name in projects:
        build_dir = build_dirs[project_name]

        configure_command = [
            'cmake',
            '-S', str(ROOT / 'Build'),
            '-B', str(build_dir),
            f'-DMINTY_BUILD_LAYER={project_name}',
            f'-DCMAKE_BUILD_TYPE={config_name}',
            f'-DMINTY_ARTIFACTS_DIR={str(ARTIFACTS_DIR)}',
        ]
        if render == RENDER_VULKAN:
            configure_command.append('-DMINTY_ENABLE_VULKAN=ON')
        if audio == AUDIO_SOLOUD:
            configure_command.append('-DMINTY_ENABLE_SOLOUD=ON')

        build_command = [
            'cmake',
            '--build', str(build_dir),
            '--config', config_name,
            '--parallel',
        ]
        if project_name != 'All':
            build_command.extend(['--target', f'minty_{project_name.lower()}'])

        configure_commands[project_name] = configure_command
        build_commands[project_name] = build_command

    if action & ACTION_CLEAN:
        print_line('Step 1/1: Cleaning', char=LINE_CHAR_LARGE)
        for project_name in projects:
            print_line(f'Project: {project_name}', char=LINE_CHAR_MED)

            build_dir = build_dirs[project_name]
            if build_dir.exists():
                shutil.rmtree(build_dir)
                print(f'Removed {build_dir}')

            artifact_dir = _artifact_directory(config_name)
            if artifact_dir.exists():
                if project_name == 'All':
                    shutil.rmtree(artifact_dir)
                    print(f'Removed {artifact_dir}')
                else:
                    removed_artifacts: list[Path] = []
                    artifact_stems = _artifact_stems_for_layer(project_name)
                    for artifact_path in artifact_dir.glob('*'):
                        if not artifact_path.is_file():
                            continue

                        if artifact_path.stem in artifact_stems:
                            artifact_path.unlink()
                            removed_artifacts.append(artifact_path)

                    if removed_artifacts:
                        print('Removed layer artifacts:')
                        for path in removed_artifacts:
                            print(f'  {path}')
            print_line()
        print_line(char=LINE_CHAR_MED)

    if action & ACTION_BUILD:
        print_line('Step 1/3: Generating', char=LINE_CHAR_LARGE)
        discovered_layers = _discover_layers()
        for project_name in projects:
            print_line(f'Project: {project_name}', char=LINE_CHAR_MED)

            build_dir = build_dirs[project_name]
            _ensure_build_dir_source(build_dir, ROOT / 'Build')
            build_dir.mkdir(parents=True, exist_ok=True)

            header_layers = discovered_layers if project_name == 'All' else [project_name]
            for layer_name in header_layers:
                _generate_layer_headers(layer_name)
                # generated_headers = _generate_layer_headers(layer_name)
                # print(f'Ensured {len(generated_headers)} aggregate headers for {layer_name}.')
            print_line()
        print_line(char=LINE_CHAR_MED)

        print_line('Step 2/3: Configuring', char=LINE_CHAR_LARGE)
        for project_name in projects:
            print_line(f'Project: {project_name}', char=LINE_CHAR_MED)

            configure_return_code = 0
            configure_command = configure_commands[project_name]
            if verbose:
                configure_return_code = Command.print_command(configure_command, ROOT)
            else:
                configure_return_code, configure_text = Command.run_command(configure_command, ROOT)
                if configure_return_code != 0:
                    print(configure_text)
            if configure_return_code != 0:
                return configure_return_code
            print_line()
        print_line(char=LINE_CHAR_MED)

        print_line('Step 3/3: Building', char=LINE_CHAR_LARGE)
        for project_name in projects:
            print_line(f'Project: {project_name}', char=LINE_CHAR_MED)

            build_return_code = 0
            build_command = build_commands[project_name]
            if verbose:
                build_return_code = Command.print_command(build_command, ROOT)
            else:
                build_return_code, build_text = Command.run_command(build_command, ROOT)
                if build_text and build_return_code != 0:
                    print(build_text)
            if build_return_code != 0:
                return build_return_code
            print_line()
        print_line(char=LINE_CHAR_MED)

    if action & ACTION_RUN:
        print_line('Step 1/1: Running', char=LINE_CHAR_LARGE)
        for project_name in projects:
            print_line(f'Project: {project_name}', char=LINE_CHAR_MED)
            print('Run action is not implemented yet.')
            print_line()
        print_line(char=LINE_CHAR_MED)

    # End timer and print duration
    end_time = time.time()
    duration = end_time - start_time
    print(f'Completed in {duration:.2f} seconds.')
    print_line(char=LINE_CHAR_LARGE)
    return 0

if __name__ == '__main__':
    sys.exit(main())