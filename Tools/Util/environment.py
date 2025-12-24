import os
import sys
from pathlib import Path
if __name__ == "__main__":
    sys.path.insert(0, str(Path(__file__).parent.parent))
from Util import command

def set_environment_variable(key: str, value: str, permanent: bool) -> None:
    """
    Sets an environment variable for the current process.

    Args:
        key: The name of the environment variable
        value: The value to set
    """
    if permanent:
        if os.name == 'nt':
            # Windows
            command.run_command(f'setx {key} "{value}"') # /m for system-wide
        else:
            print("Permanent environment variable setting is not implemented for this OS.")
    os.environ[key] = value

def get_environment_variable(key: str, permanent: bool) -> str | None:
    """
    Retrieves the value of an environment variable.

    Args:
        key: The name of the environment variable

    Returns:
        The value of the environment variable, or None if it does not exist
    """
    if permanent:
        if os.name == 'nt':
            # Windows
            _, value = command.run_command(f'reg query "HKCU\\Environment" /v {key}')
            if value:
                return value.split()[-1]
        else:
            print("Permanent environment variable setting is not implemented for this OS.")
    return os.environ.get(key)