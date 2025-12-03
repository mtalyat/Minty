import os
import sys
from pathlib import Path

AUTO_GENERATED_NOTICE = "// THIS FILE IS AUTO-GENERATED. DO NOT MODIFY."

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
        return False
    
    if not dir_path.is_dir():
        print(f"Error: '{directory_path}' is not a directory.")
        return False
    
    # Get directory name
    dir_name = dir_path.name
    
    # Find all .h files in the directory (non-recursive)
    h_files = sorted([f for f in dir_path.iterdir() if f.is_file() and f.suffix == '.h'])
    
    if not h_files:
        return True  # No .h files to process, but not an error
    
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
    try:
        with open(output_path, 'w') as f:
            f.write('\n'.join(lines))
        return True
    except Exception as e:
        print(f"  Error writing file: {e}")
        return False


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
    
    try:
        with open(output_path, 'w') as f:
            f.write('\n'.join(lines))
        return True
    except Exception as e:
        print(f"\nError writing main header: {e}")
        return False


def process_source_directory(source_path):
    """
    Processes a source directory by generating combined headers for each subdirectory.
    
    Args:
        source_path: Path to the source directory containing subdirectories
        
    Returns:
        Number of successfully generated headers
    """
    src_path = Path(source_path)
    
    if not src_path.exists():
        print(f"Error: Source directory '{source_path}' does not exist.")
        return 0
    
    if not src_path.is_dir():
        print(f"Error: '{source_path}' is not a directory.")
        return 0
    
    # Find all subdirectories
    subdirs = sorted([d for d in src_path.iterdir() if d.is_dir()])
    
    if not subdirs:
        print(f"No subdirectories found in '{source_path}'.")
        return 0
    
    success_count = 0
    successful_subdirs = []
    for subdir in subdirs:
        if generate_combined_header(subdir):
            success_count += 1
            successful_subdirs.append(subdir.name)
    
    # Generate the main header file
    if successful_subdirs:
        generate_main_header(source_path, successful_subdirs)
    
    return success_count


def main():
    if len(sys.argv) != 2:
        print("Usage: python generate_directory_header.py <source_directory_path>")
        print("Example: python generate_directory_header.py C:\\path\\to\\Engine\\Source\\Minty")
        print("\nThis will process each subdirectory and generate combined headers.")
        sys.exit(1)
    
    source_path = sys.argv[1]
    success_count = process_source_directory(source_path)
    sys.exit(0 if success_count > 0 else 1)


if __name__ == "__main__":
    main()
