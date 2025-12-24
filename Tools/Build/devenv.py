import sys
import os
import argparse
import shutil
import time
import filter
from pathlib import Path
if __name__ == "__main__":
    sys.path.insert(0, str(Path(__file__).parent.parent))
from Util import command
from Util import environment
from Util import terminal

ACTION_CLEAN = 0x1
ACTION_BUILD = 0x2
ACTION_REBUILD = 0x3
ACTION_RUN = 0x4
ACTION_RERUN = 0x6
ACTION_ALL = 0x7
ACTIONS = {
    'clean': ACTION_CLEAN,
    'build': ACTION_BUILD,
    'rebuild': ACTION_REBUILD,
    'run': ACTION_RUN,
    'rerun': ACTION_RERUN,
    'all': ACTION_ALL
}

CONFIG_DEBUG = 1
CONFIG_TRACE = 2
CONFIG_RELEASE = 3
CONFIGS = {
    'debug': CONFIG_DEBUG,
    'debug-trace': CONFIG_TRACE,
    'release': CONFIG_RELEASE
}

ARCH_64 = 1
ARCH_ARM64 = 2
ARCH_86 = 3
ARCHITECTURES = {
    'x64': ARCH_64,
    'arm64': ARCH_ARM64,
    'x86': ARCH_86
}

WIDTH = 30

def main() -> int:
    minty_path = environment.get_environment_variable('MINTY_PATH', True)
    if not minty_path:
        print("Error: MINTY_PATH environment variable is not set. Run installer.bat to install Minty.")
        return 1

    # Set up parser
    parser = argparse.ArgumentParser(description="Manage a development environment.")
    parser.add_argument('action', choices=ACTIONS.keys(), help='Action to perform.')
    parser.add_argument('projects', nargs='+', help='Path to the project directory.')
    parser.add_argument('--config', '-c', choices=CONFIGS.keys(), default='debug', help='Build configuration (default: debug).')
    parser.add_argument('--arch', '-a', choices=ARCHITECTURES.keys(), default='x64', help='Target architecture (default: x64).')
    args = parser.parse_args()

    # Get the provided arguments
    action_name = args.action
    action = ACTIONS[action_name]
    projects = args.projects
    config_name = args.config
    config = CONFIGS[config_name]
    config_name = config_name.title()
    architecture_name = args.arch
    architecture = ARCHITECTURES[architecture_name]

    # Save the original working directory
    original_cwd = os.getcwd()

    # For each project, perform the specified action
    for project in projects:
        project_name = Path(project).name
        terminal.print_centered(f' {project_name} ', '=', width = WIDTH)

        # Start timer
        start_time = time.time()

        # Verify project path exists
        project_path = Path(project).resolve()
        if not project_path.exists() or not project_path.is_dir():
            print(f'  Error: Project path {project_path} does not exist or is not a directory.')
            continue

        # Move into the project directory
        os.chdir(project_path)

        # Define paths and filenames
        project_build_path = project_path / 'Build'
        project_cmake_path = project_build_path / 'CMakeLists.txt'
        project_build_bin_path = project_build_path / 'Bin'
        project_build_bin_config_path = project_build_bin_path / config_name
        project_build_output_path = project_build_path / 'Output'
        config_log_path = project_build_output_path / f'config_{project_name}.log'
        build_log_path = project_build_output_path / f'build_{project_name}.log'

        # Clean
        if action & ACTION_CLEAN:
            print(f'Cleaning...')

            # Remove Bin directory if it exists
            if os.path.exists(project_build_bin_path):
                shutil.rmtree(project_build_bin_path)

        # Build
        if action & ACTION_BUILD:
            if not os.path.exists(project_build_path):
                print(f'Error: Build path {project_build_path} does not exist. Cannot build project.')
                continue
            if not os.path.exists(project_cmake_path):
                print(f'Error: CMakeLists.txt not found in {project_build_path}. Cannot build project.')
                continue

            print(f'Building...')

            # Create Bin and Output directories if they don't exist
            os.makedirs(project_build_bin_path, exist_ok=True)
            os.makedirs(project_build_bin_config_path, exist_ok=True)
            os.makedirs(project_build_output_path, exist_ok=True)

            # Move to Build Output directory
            os.chdir(project_build_output_path)

            # Run the CMake config
            code, message = command.run_command(f'cmake .. -A {architecture_name}', cwd=project_build_output_path)

            if code != 0:
                print(f'Error: CMake configuration failed for project {project}. See {config_log_path} for details.')
                print(f'Code: {code}, Message: {message}')
                continue

            # Run the build
            filter_logger = filter.FilterLogger(build_log_path)
            for line in command.stream_command(fr'cmake --build . --config {config_name}', cwd=project_build_output_path):
                if line is None:
                    print('line is None')
                    continue
                filter_logger.log_line(line)
            code = filter_logger.done()
            
            if code != 0:
                print(f'Error: Build failed for project {project}. See {build_log_path} for details.')
                print(f'Code: {code}')
                continue

            # Copy built files to Bin directory
            build_output_config_path = project_build_output_path / config_name
            if os.path.exists(build_output_config_path):
                for item in os.listdir(build_output_config_path):
                    s = os.path.join(build_output_config_path, item)
                    d = os.path.join(project_build_bin_config_path, item)
                    if os.path.isdir(s):
                        shutil.copytree(s, d, dirs_exist_ok=True)
                    else:
                        shutil.copy2(s, d)
            else:
                print(f'Warning: Build output path {build_output_config_path} does not exist. No files copied to Bin directory.')

            # Move back to project directory
            os.chdir(project_path)
            
        # Run
        if action & ACTION_RUN:
            executable_found = False
            if os.path.exists(project_build_bin_config_path):
                for item in os.listdir(project_build_bin_config_path):
                    item_path = project_build_bin_config_path / item
                    if item_path.is_file() and os.access(item_path, os.X_OK):
                        print(f'Running...')
                        os.chdir(project_build_bin_config_path)
                        run_code, _ = command.run_command(f'"{item_path}"')
                        executable_found = True
                        if run_code != 0:
                            print(f'Error: Executable {item_path} exited with code {run_code}.')
                        break
            if not executable_found:
                print(f'Error: No executable found in {project_build_bin_config_path} to run.')
        
        # Print elapsed time
        elapsed_time = time.time() - start_time
        hours = int(elapsed_time // 3600)
        minutes = int((elapsed_time % 3600) // 60)
        seconds = int(elapsed_time % 60)
        milliseconds = int((elapsed_time % 1) * 1000)
        print(f'Elapsed time: {hours:02d}:{minutes:02d}:{seconds:02d}.{milliseconds:03d}')

        terminal.print_line('=', width = WIDTH)
    
    # Return to original directory
    os.chdir(original_cwd)

    return 0

if __name__ == '__main__':
    sys.exit(main())