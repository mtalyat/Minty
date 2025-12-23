import sys
import re
from pathlib import Path
import shutil

RE_ERROR = r'error(?::| [a-zA-Z]\d+:)'
RE_WARNING = r'warning(?::| [a-zA-Z]\d+:)'
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
INVERTED_COLOR = '\033[37;40m'  # White, Black
PATH_COLOR = '\033[90;40m'  # Dark Gray, Black

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

def main() -> int:
    """Main function to filter build logs."""
    # Get log file path from command line, default to 'build.log'
    log_file = sys.argv[1] if len(sys.argv) > 1 else 'build.log'
    
    # Ensure we're writing to an absolute path
    log_path = Path(log_file).absolute()

    current_path = ''
    current_line_numbers = ''
    counts: dict[int, int] = dict()
    
    try:
        # Open log file in write mode (overwrite existing)
        with open(log_path, 'w', encoding='utf-8', errors='replace') as log:
            # Read from stdin line by line
            for line in sys.stdin:
                # Write all content to log file
                log.write(line)
                log.flush()  # Ensure immediate write

                line_type = LINE_TYPE_NORMAL
                for filter_obj in FILTER_OBJECTS:
                    text_match = filter_obj.pattern.search(line)
                    if text_match:
                        line_type = filter_obj.line_type
                        break
                counts[line_type] = counts.get(line_type, 0) + 1

                # Get the file path, if any
                file_match = re.search(RE_FILE_PATH, line)
                if file_match:
                    line_path = file_match.group(0).strip()

                    if line_path.endswith('.cpp') or line_path.endswith('.h'):
                        # Get the line numbers if present
                        line_numbers_match = re.search(r'^\((\d+)(,\s*\d+)?\)', line[file_match.end():])
                        if line_numbers_match:
                            current_line_numbers = line_numbers_match.group(0)

                        # Print the file name if it has changed
                        if current_path != line_path:
                            # Print the new file name
                            terminal_width = get_terminal_width()
                            line_name = str(Path(line_path).name)
                            sys.stdout.write(f'\r    {line_name}{" " * (terminal_width - len(line_name) - 5)}')
                            current_path = line_path
                            # If not a normal line, add a newline after the file name
                            if line_type != LINE_TYPE_NORMAL:
                                sys.stdout.write('\n')

                # If it's a normal line, skip further processing
                if line_type == LINE_TYPE_NORMAL:
                    continue
                
                # Get the information from the error, warning, etc. to print
                info_text = line[text_match.end():].strip() if text_match else line.strip()
                info_text = re.sub(fr'[\[\(\<].*?[\]\)\>]', '', info_text).strip()  # Remove anything in brackets
                info_text += f' {PATH_COLOR}[{current_path}{current_line_numbers}]{COLOR_RESET}' # Append file path with line numbers

                # Print to stdout with color coding
                sys.stdout.write(f'{filter_obj.color}{filter_obj.name}{COLOR_RESET} {info_text}\n')
                sys.stdout.flush()

        # Print summary to stdout
        
        code = 0
        if len(counts) > 0 and (len(counts) != 1 or (LINE_TYPE_NORMAL not in counts)):
            sys.stdout.write(f'\n\n\t{INVERTED_COLOR}Build Summary:{COLOR_RESET}\n')
            for filter_obj in sorted(FILTER_OBJECTS, key=lambda fo: fo.line_type):
                count = counts.get(filter_obj.line_type, 0)
                if count > 0:
                    sys.stdout.write(f'{filter_obj.color}{filter_obj.name}{COLOR_RESET}: {count}\n')
            sys.stdout.write('\n')
            sys.stdout.flush()
            code = counts.get(LINE_TYPE_ERROR, 0)
        
        if code == 0:
            sys.stdout.write(f'{SUCCESS_COLOR} SUCCESS {COLOR_RESET}\n')
        else:
            sys.stdout.write(f'{FAIL_COLOR} FAIL {COLOR_RESET}\n')
        
        sys.stdout.flush()

        return code
                
    except KeyboardInterrupt:
        # Handle Ctrl+C gracefully
        return 130
    except Exception as e:
        print(f"Error in build_filter: {e}", file=sys.stderr)
        return -1

if __name__ == '__main__':
    sys.exit(main())
