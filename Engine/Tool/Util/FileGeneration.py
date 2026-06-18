import os

def update_generated_file(file_path, content) -> bool:
    """
    Writes the given content to a file at the specified path, as long as the file has changed.
    
    Args:
        file_path: Path to the output file
        content: Content to write to the file
        
    Returns:
        True if successful, False otherwise
    """
    if os.path.exists(file_path):
        try:
            with open(file_path, 'r') as f:
                existing_content = f.read()
                if existing_content == content:
                    return False  # No changes needed, stop here
        except Exception as e:
            print(f"  Error reading file: {e}")
            return False
    
    try:
        with open(file_path, 'w') as f:
            f.write(content)
        return True
    except Exception as e:
        print(f"  Error writing file: {e}")
        return False