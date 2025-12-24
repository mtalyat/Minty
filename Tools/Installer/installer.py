import sys
import argparse
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent.parent))
from Util import environment

def main() -> int:
    parser = argparse.ArgumentParser(description="Install or uninstall Minty.")
    parser.add_argument('action', choices=['install', 'uninstall'], help='Action to perform.')
    args = parser.parse_args()

    if args.action == 'install':
        minty_path = str(Path(__file__).parent.parent.resolve())
        environment.set_environment_variable('MINTY_PATH', minty_path, permanent=True)
        print("Minty installed successfully.")
    elif args.action == 'uninstall':
        environment.set_environment_variable('MINTY_PATH', '', permanent=True)
        print("Minty uninstalled successfully.")

if __name__ == '__main__':
    sys.exit(main())