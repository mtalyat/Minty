import os
import sys
from pathlib import Path

# Add parent directory to path for imports when run as a script
if __name__ == "__main__":
    sys.path.insert(0, str(Path(__file__).parent.parent))
from Util import file_generation

# Get the path to the source root (two levels up from this script)
SOURCE_ROOT = Path(__file__).parent.parent.parent / 'Engine' / 'Source' / 'Minty'
GENERATED_PATH = SOURCE_ROOT / 'Generated'

AUTO_GENERATED_NOTICE = "// THIS FILE IS AUTO-GENERATED. DO NOT MODIFY."
IGNORED_FILENAME_START = "_"

SYSTEM_PRIORITIES = {
    "Render": 10000,
    "Physics": 10000,
    "Audio": 10000,
    "Animation": 9999
}
SYSTEM_DEFAULT_PRIORITY = 0

def generate_component_registration(directory_path, output_path):
    """
    Scans a directory for component header files and creates a C++ source file
    that registers all components with the EntityManager.
    
    Args:
        directory_path: Path to the directory containing component headers
        output_path: Path where the generated registration file will be created
        
    Returns:
        True if file was updated, False otherwise
    """
    # Convert to Path object
    dir_path = Path(directory_path)
    out_path = Path(output_path)
    
    # Verify the directory exists
    if not dir_path.exists():
        print(f"Error: Directory '{directory_path}' does not exist.")
        return False
    
    if not dir_path.is_dir():
        print(f"Error: '{directory_path}' is not a directory.")
        return False
    
    # Get directory name for the include path
    dir_name = dir_path.name
    
    # Find all component header files (non-recursive)
    # Look for files ending with "Component.h" but not starting with "_"
    component_files = sorted([
        f for f in dir_path.iterdir()
        if f.is_file() 
        and f.suffix == '.h' 
        and f.stem.endswith('Component')
        and not f.name.startswith(IGNORED_FILENAME_START)
    ])
    
    if not component_files:
        print(f"No component files found in '{directory_path}'")
        return False
    
    # Extract component class names and registration names
    components = []
    for comp_file in component_files:
        class_name = comp_file.stem  # e.g., "TransformComponent"

        # Remove "Component" suffix for registration name
        reg_name = class_name.replace('Component', '')

        # If the reg_name is empty (e.g., class name was just "Component"), skip it
        if not reg_name:
            continue

        components.append((class_name, reg_name))
    
    # Generate the registration file content
    lines = []
    lines.append(AUTO_GENERATED_NOTICE)
    lines.append("")
    lines.append('#include "Minty/Application/Application.h"')
    lines.append('#include "Minty/Entity/EntityManager.h"')
    lines.append(f'#include "Minty/{dir_name}/_{dir_name}.h"')
    lines.append("")
    lines.append("using namespace Minty;")
    lines.append("")
    lines.append("void Minty::Application::register_components()")
    lines.append("{")
    
    for class_name, reg_name in components:
        lines.append(f'    EntityManager::register_component<{class_name}>("{reg_name}");')
    
    lines.append("}")
    lines.append("")
    
    # Write to file
    content = '\n'.join(lines)
    return file_generation.update_generated_file(out_path, content)


def generate_system_registration(directory_path, output_path):
    """
    Scans a directory for system header files and creates a C++ source file
    that registers all systems with the SystemManager.
    
    Args:
        directory_path: Path to the directory containing system headers
        output_path: Path where the generated registration file will be created
        
    Returns:
        True if file was updated, False otherwise
    """
    # Convert to Path object
    dir_path = Path(directory_path)
    out_path = Path(output_path)
    
    # Verify the directory exists
    if not dir_path.exists():
        print(f"Error: Directory '{directory_path}' does not exist.")
        return False
    
    if not dir_path.is_dir():
        print(f"Error: '{directory_path}' is not a directory.")
        return False
    
    # Get directory name for the include path
    dir_name = dir_path.name
    
    # Find all system header files (non-recursive)
    # Look for files ending with "System.h" but not starting with "_" and not "System.h" itself
    system_files = sorted([
        f for f in dir_path.iterdir()
        if f.is_file() 
        and f.suffix == '.h' 
        and f.stem.endswith('System')
        and f.stem != 'System'  # Exclude the base System.h
        and not f.name.startswith(IGNORED_FILENAME_START)
    ])
    
    if not system_files:
        print(f"No system files found in '{directory_path}'")
        return False
    
    # Extract system class names and registration names
    # For systems, we may want to preserve priority ordering
    systems = []
    for sys_file in system_files:
        class_name = sys_file.stem  # e.g., "RenderSystem"
        
        # Remove "System" suffix for registration name
        reg_name = class_name.replace('System', '')

        # If the reg_name is empty (e.g., class name was just "System"), skip it
        if not reg_name:
            continue
        
        # Determine priority
        priority = SYSTEM_PRIORITIES.get(reg_name, SYSTEM_DEFAULT_PRIORITY)
            
        systems.append((class_name, reg_name, priority))
    
    # Sort systems by priority (descending) for clarity in the file
    systems.sort(key=lambda x: -x[2])
    
    # Generate the registration file content
    lines = []
    lines.append(AUTO_GENERATED_NOTICE)
    lines.append("")
    lines.append('#include "Minty/Application/Application.h"')
    lines.append(f'#include "Minty/{dir_name}/_{dir_name}.h"')
    lines.append("")
    lines.append("using namespace Minty;")
    lines.append("")
    lines.append("void Minty::Application::register_systems()")
    lines.append("{")
    
    for class_name, reg_name, priority in systems:
        lines.append(f'    SystemManager::register_system<{class_name}>("{reg_name}", {priority});')
    
    lines.append("}")
    lines.append("")
    
    # Write to file
    content = '\n'.join(lines)
    return file_generation.update_generated_file(out_path, content)

def generate_registration(func, directory, output_dir, output_name):
    """
    Helper function to generate registration files.
    
    Args:
        func: The generation function to use (component or system)
        directory: The source directory to scan
        output_file: The output file path for the generated source
        
    Returns:
        True if file was updated, False otherwise
    """
    output_file = output_dir / output_name
    if func(directory, output_file):
        print(f'Updated {output_file}.')
        return True
    return False

def main():
    generate_registration(generate_component_registration, SOURCE_ROOT / 'Component', GENERATED_PATH, '_register_components.cpp')
    generate_registration(generate_system_registration, SOURCE_ROOT / 'System', GENERATED_PATH, '_register_systems.cpp')

if __name__ == "__main__":
    main()
