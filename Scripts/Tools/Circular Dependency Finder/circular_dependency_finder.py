import os
import re
from collections import deque

MINTY_SOURCE_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..', 'Minty', 'Source'))

def main():
    path = input("Enter the path to the directory to check for circular dependencies, or ENTER to check the Minty Source directory: ")    

    if not path:
        path = MINTY_SOURCE_PATH
    
    if not os.path.exists(path):
        print(f"Path does not exist: {path}")
        return
    
    if not os.path.isdir(path):
        print(f"Path is not a directory: {path}")
        return
    
    print(f"Checking for circular dependencies in: {path}")

    # collect all files and which files each of them include
    fileData = dict()
    for root, _, files in os.walk(path):
        for file in files:
            if not file.endswith('.h') or file.startswith('_'):
                continue
            fileIncludes = list()
            with open(os.path.join(root, file), 'r') as f:
                lines = f.readlines()
            for line in lines:
                match = re.search(r'#include\s+"(.+)"', line)
                if not match:
                    continue
                includeFile = match.group(1)
                includeFileName = os.path.basename(includeFile)
                fileIncludes.append(includeFileName)
            fileData[file] = fileIncludes

    # check for circular dependencies
    def search(file, visited, path):
        if file in visited:
            print(f"Circular dependency found: {' -> '.join(path + [file])}")
            return True
        visited.add(file)
        path.append(file)
        for include in fileData.get(file, []):
            if search(include, visited, path):
                return True
        visited.remove(file)
        path.pop()
        return False
    
    foundCount = 0
    for file, _ in fileData.items():
        visited = set()
        path = list()
        if search(file, visited, path):
            foundCount += 1
    print(f"Found {foundCount} circular dependencies.")

if __name__ == "__main__":
    main()