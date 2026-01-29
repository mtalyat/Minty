import sys
import re
from pathlib import Path
import shutil

RE_ERROR = r'\S.*?error(?::| [a-zA-Z]+\d+:)'
RE_WARNING = r'\S.*?warning(?::| [a-zA-Z]+\d+:)'
RE_FILE_PATH = r'^([a-zA-Z]:)?(\\|/)?([\w\-. ]+(\\|/))*[\w\-. ]+\.\w+'

LINE_TYPE_ERROR = 0
LINE_TYPE_WARNING = 1
LINE_TYPE_NORMAL = 2

class FilterObject:
    """Class to filter build log lines."""
    name: str
    pattern: re.Pattern
    line_type: int
    color: str

    def __init__(self, name: str, pattern: str, line_type: int, color: str):
        self.name = name
        self.pattern = re.compile(pattern, re.IGNORECASE)
        self.line_type = line_type
        self.color = color

ERROR_COLOR = '\033[30;101m'  # Black, Red
WARNING_COLOR = '\033[30;103m'  # Black, Yellow
NORMAL_COLOR = '\033[30;47m'  # Black, White
PATH_COLOR = '\033[90m'  # Dark Gray, ??

FAIL_COLOR = '\033[97;41m'  # Bright White, Red Background
SUCCESS_COLOR = '\033[97;42m'  # Bright White, Green Background

ERROR_OBJECT = FilterObject(' ERR ', RE_ERROR, LINE_TYPE_ERROR, ERROR_COLOR)    # Black, Red
WARNING_OBJECT = FilterObject(' WRN ', RE_WARNING, LINE_TYPE_WARNING, WARNING_COLOR)  # Black, Yellow

FILTER_OBJECTS = [
    ERROR_OBJECT,
    WARNING_OBJECT,
]
COLOR_RESET = '\033[0m'

def get_line_type(line: str) -> int:
    """Determine the type of a log line."""
    for filter_obj in FILTER_OBJECTS:
        if filter_obj.pattern.search(line):
            return filter_obj.line_type
    return LINE_TYPE_NORMAL

def get_terminal_width() -> int:
    """Get the width of the terminal."""
    return shutil.get_terminal_size((80, 20)).columns

class FilterLogger:
    """Class to handle logging of filtered lines."""
    log_path: Path
    current_path = ''
    current_line_numbers = ''
    counts: dict[int, int] = dict()

    def __init__(self, log_path: Path):
        self.log_path = log_path

        # Initialize the log file
        with open(self.log_path, 'w', encoding='utf-8', errors='replace') as log:
            log.write('')  # Clear the log file

    def log_line(self, line: str):
        """Log a single line."""
        # Write all content to the log file
        with open(self.log_path, 'a', encoding='utf-8', errors='replace') as log:
            log.write(f'{line}\n')
            log.flush()

        # Determine line type
        line_type = LINE_TYPE_NORMAL
        for filter_obj in FILTER_OBJECTS:
            text_match = filter_obj.pattern.search(line)
            if text_match:
                line_type = filter_obj.line_type
                break
        self.counts[line_type] = self.counts.get(line_type, 0) + 1

        # Get the file path, if any
        file_match = re.search(RE_FILE_PATH, line)
        if file_match:
            line_path = file_match.group(0).strip()

            if line_path.endswith('.cpp') or line_path.endswith('.h'):
                # Get the line numbers if present
                line_numbers_match = re.search(r'^\((\d+)(,\s*\d+)?\)', line[file_match.end():])
                if line_numbers_match:
                    self.current_line_numbers = line_numbers_match.group(0)

                # Print the file name if it has changed
                if self.current_path != line_path:
                    # Print the new file name
                    terminal_width = get_terminal_width()
                    line_name = str(Path(line_path).name)
                    spacing = '    '
                    sys.stdout.write(f'\r{spacing}{line_name}{" " * (terminal_width - len(line_name) - len(spacing))}')
                    self.current_path = line_path
                    # If not a normal line, add a newline after the file name
                    if line_type != LINE_TYPE_NORMAL:
                        sys.stdout.write('\n')

        # If it's a normal line, skip further processing
        if line_type == LINE_TYPE_NORMAL:
            return
        
        # Get the information from the error, warning, etc. to print
        info_text = line[text_match.end():].strip() if text_match else line.strip()
        info_text = re.sub(fr'\[.*?\]', '', info_text).strip()  # Remove anything in brackets
        if self.current_path:
            info_text += f' {PATH_COLOR}[{self.current_path}{self.current_line_numbers}]{COLOR_RESET}' # Append file path with line numbers

        # Print to stdout with color coding
        sys.stdout.write(f'{filter_obj.color}{filter_obj.name}{COLOR_RESET} {info_text}\n')
        sys.stdout.flush()

    def done(self):
        """Print the summary of logged lines and return the error count."""
        code = 0
        if len(self.counts) > 0 and (len(self.counts) != 1 or (LINE_TYPE_NORMAL not in self.counts)):
            sys.stdout.write(f'\n\n\t{NORMAL_COLOR}Build Summary:{COLOR_RESET}\n')
            for filter_obj in sorted(FILTER_OBJECTS, key=lambda fo: fo.line_type):
                count = self.counts.get(filter_obj.line_type, 0)
                if count > 0:
                    sys.stdout.write(f'{filter_obj.color}{filter_obj.name}{COLOR_RESET}: {count}\n')
            sys.stdout.write('\n')
            sys.stdout.flush()
            code = self.counts.get(LINE_TYPE_ERROR, 0)
        
        width = get_terminal_width()
        text = ' SUCCESS ' if code == 0 else ' FAIL '
        color = SUCCESS_COLOR if code == 0 else FAIL_COLOR
        sys.stdout.write(f'\r{color}{text}{COLOR_RESET}{" " * (width - len(text))}\n')
        sys.stdout.flush()

        return code
