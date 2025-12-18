import os
import sys
from pathlib import Path

# Add parent directory to path for imports when run as a script
if __name__ == "__main__":
    sys.path.insert(0, str(Path(__file__).parent.parent))
from Util import file_generation

SOURCE_ROOT = Path(__file__).parent.parent.parent / 'Engine' / 'Source' / 'Minty'

RESULT_ERROR = 0
RESULT_IGNORE = 1
RESULT_PASS = 2
RESULT_SUCCESS = 3

AUTO_GENERATED_NOTICE = "// THIS FILE IS AUTO-GENERATED. DO NOT MODIFY."
IGNORED_DIRECTORIES = {"Library", "Generated"}
IGNORED_FILENAME_START = "_"

def generate_combined_header(directory_path):
    """
    Scans a directory for .h files and creates a combined header file
    that includes all of them.
    
    Args:
        directory_path: Path to the directory to scan
        
    Returns:
        True if successful, False otherwise
    """
    # Convert to Path object
    dir_path = Path(directory_path)
    
    # Verify the directory exists
    if not dir_path.exists():
        print(f"Error: Directory '{directory_path}' does not exist.")
        return RESULT_ERROR
    
    if not dir_path.is_dir():
        print(f"Error: '{directory_path}' is not a directory.")
        return RESULT_ERROR
    
    # Get directory name
    dir_name = dir_path.name

    # Skip ignored directories
    if dir_name in IGNORED_DIRECTORIES:
        return RESULT_IGNORE
    if dir_name.startswith(IGNORED_FILENAME_START):
        return RESULT_IGNORE
    
    # Find all .h files in the directory (non-recursive)
    h_files = sorted([f for f in dir_path.iterdir() if f.is_file() and f.suffix == '.h'])
    
    if not h_files:
        return RESULT_IGNORE  # No .h files to process, but not an error
    
    # Create output filename
    output_filename = f"_{dir_name}.h"
    output_path = dir_path / output_filename
    
    # Generate the combined header content
    lines = []
    lines.append(AUTO_GENERATED_NOTICE)
    lines.append("")
    
    # Add includes for each .h file
    for h_file in h_files:
        # Skip the output file itself if it already exists
        if h_file.name == output_filename:
            continue
        lines.append(f'#include "{h_file.name}"')
    lines.append("")
    
    # Write to file
    if file_generation.update_generated_file(output_path, '\n'.join(lines)):
        return RESULT_SUCCESS
    return RESULT_PASS


def generate_main_header(source_path, subdirs_with_headers):
    """
    Generates the main Minty.h header that includes all subdirectory combined headers.
    
    Args:
        source_path: Path to the source directory
        subdirs_with_headers: List of subdirectory names that have combined headers
        
    Returns:
        True if successful, False otherwise
    """
    src_path = Path(source_path)
    src_name = src_path.name
    output_path = src_path.parent / f"{src_name}.h"
    
    lines = []
    lines.append(AUTO_GENERATED_NOTICE)
    lines.append("")
    lines.append(f"#ifndef {src_name.upper()}_H")
    lines.append(f"#define {src_name.upper()}_H")
    lines.append("")
    
    # Add includes for each subdirectory's combined header
    for subdir_name in sorted(subdirs_with_headers):
        subdir_path = src_path / subdir_name / f"_{subdir_name}.h"
        if os.path.exists(subdir_path):
            subdir_header = f"{src_name}/{subdir_name}/_{subdir_name}.h"
            lines.append(f'#include "{subdir_header}"')
    
    lines.append("")
    lines.append(f"#endif // {src_name.upper()}_H")
    lines.append("")
    
    return file_generation.update_generated_file(output_path, '\n'.join(lines))


def process_source_directory():
    """
    Processes a source directory by generating combined headers for each subdirectory.
    
    Args:
        source_path: Path to the source directory containing subdirectories
        
    Returns:
        Number of successfully generated headers
    """
    src_path = Path(SOURCE_ROOT)
    
    if not src_path.exists():
        print(f"Error: Source directory '{src_path}' does not exist.")
        return 0
    
    if not src_path.is_dir():
        print(f"Error: '{src_path}' is not a directory.")
        return 0
    
    # Find all subdirectories
    subdirs = sorted([d for d in src_path.iterdir() if d.is_dir()])
    
    if not subdirs:
        print(f"No subdirectories found in '{src_path}'.")
        return 0
    
    successful_subdirs = []
    for subdir in subdirs:
        result = generate_combined_header(subdir)
        if result == RESULT_SUCCESS:
            print(f'Updated {subdir.name}.')
            successful_subdirs.append(subdir.name)
        elif result == RESULT_PASS:
            successful_subdirs.append(subdir.name)
        elif result == RESULT_ERROR:
            print(f'Error processing {subdir.name}.')
    
    # Generate the main header file
    if generate_main_header(src_path, successful_subdirs):
        print(f'Updated {src_path.name}.h.')


def main():
    process_source_directory()

if __name__ == "__main__":
    main()
