import sys
import os
import shutil
import re
import uuid
from pathlib import Path
import subprocess

TEMPLATE_PATTERN = re.compile(r'<<<(.*?)>>>')
def generate_uuid() -> str:
    """Generate a random UUID string."""
    return str(uuid.uuid4()).upper().replace('-', '')

def create_project(name, path):
    """Create a new project by copying the Template directory."""
    uuids: dict[int, str] = dict()
    def get_template(template_text: str) -> str:
        nonlocal name, uuids
        if(template_text.startswith("UUID")) and len(template_text) >= 7 and template_text[4] == '(' and template_text[-1] == ')':
            # If an index was provided, use or create a UUID for that index
            index = int(template_text[5:-1])
            if index in uuids:
                return uuids[index]
            else:
                new_uuid = generate_uuid()
                uuids[index] = new_uuid
                return new_uuid
        elif(template_text.startswith('NAME')):
            return name

        return template_text

    # Get the directory where this script is located
    script_dir = Path(__file__).parent
    template_dir = script_dir / "Template"
    
    # Verify template directory exists
    if not template_dir.exists():
        print(f"Error: Template directory not found at {template_dir}")
        return False
    
    # Create the target path
    target_path = Path(path)
    project_dir = target_path / name
    
    # Check if project already exists
    if project_dir.exists():
        print(f"Error: Project directory already exists at {project_dir}")
        return False
    
    # Create parent directories if they don't exist
    try:
        target_path.mkdir(parents=True, exist_ok=True)
    except Exception as e:
        print(f"Error: Could not create target path {target_path}: {e}")
        return False
    
    # Copy the template directory
    try:
        shutil.copytree(template_dir, project_dir)
        
        # Find and rename all .template files
        for template_file in project_dir.rglob("*.template"):
            # Remove the .template extension
            new_name = template_file.with_suffix('')
            template_file.rename(new_name)
            path = new_name.relative_to(project_dir)

            # Open the file and replace anything within <<< and >>> with the project name
            with open(new_name, 'r', encoding='utf-8') as file:
                content = file.read()
                matches = re.findall(TEMPLATE_PATTERN, content)
                for match in matches:
                    replacement = get_template(match)
                    content = content.replace(f'<<<{match}>>>', replacement)
            
            with open(new_name, 'w', encoding='utf-8') as file:
                file.write(content)
        
        print(f"Successfully created project '{name}' at {project_dir}")
        success = True
    except Exception as e:
        print(f"Error: Could not copy template to {project_dir}: {e}")
        success = False

    return success

def main():
    if len(sys.argv) < 3:
        print("Usage: python project_manager.py create <name> <path>")
        print("  create - Create a new project from the Template directory")
        print("  <name> - Name of the project")
        print("  <path> - Path where the project will be created")
        sys.exit(1)
    
    command = sys.argv[1]
    
    if command == "create":
        name = sys.argv[2]
        path = sys.argv[3] if len(sys.argv) >= 4 else "."
        success = create_project(name, path)
        sys.exit(0 if success else 1)
    else:
        print(f"Error: Unknown command '{command}'")
        print("Available commands: create")
        sys.exit(1)


if __name__ == "__main__":
    main()
