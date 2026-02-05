import shutil

def get_terminal_width() -> int:
    """Get the width of the terminal."""
    return shutil.get_terminal_size((80, 20)).columns

def print_centered(text: str, fill_char: str = ' ', width: int = None) -> None:
    """Print text centered in the terminal."""
    if width is None:
        width = get_terminal_width()
    text_length = len(text)
    if text_length >= width:
        print(text)
        return
    total_padding = width - text_length
    left_padding = total_padding // 2
    right_padding = total_padding - left_padding
    print(f'{fill_char * left_padding}{text}{fill_char * right_padding}')

def print_line(fill_char: str = '-', width: int = None) -> None:
    """Print a line across the terminal."""
    if width is None:
        width = get_terminal_width()
    print(fill_char * width)