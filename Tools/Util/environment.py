import os

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
            import winreg
            with winreg.OpenKey(winreg.HKEY_CURRENT_USER, 'Environment', 0, winreg.KEY_SET_VALUE) as env_key:
                winreg.SetValueEx(env_key, key, 0, winreg.REG_SZ, value)
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
            import winreg
            try:
                with winreg.OpenKey(winreg.HKEY_CURRENT_USER, 'Environment', 0, winreg.KEY_READ) as env_key:
                    value, _ = winreg.QueryValueEx(env_key, key)
                    return value
            except FileNotFoundError:
                return None
    return os.environ.get(key)