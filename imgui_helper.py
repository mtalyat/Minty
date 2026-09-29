import re
import chivel as cv

# Enum creator
IMGUI_FILE_PATH = 'Engine/Source/Library/ImGui/Source/imgui.h'

def print_list(lst):
    for item in lst:
        print(item)

# Get name of the types
minty_name = input('Enter the name of the Minty type: ')
imgui_name = input('Enter the name of the ImGui type: ')

# Fix up names
if not imgui_name.startswith('ImGui'):
    imgui_name = 'ImGui' + imgui_name
if not imgui_name.endswith('_'):
    imgui_name += '_'
if imgui_name.endswith('Flags_') and not minty_name.endswith('FlagsEnum'):
    minty_name += 'FlagsEnum'
elif not minty_name.endswith('Enum'):
    minty_name += 'Enum'

print(f'Minty type: {minty_name}')
print(f'ImGui type: {imgui_name}')
print()

# Read the ImGui header file
with open(IMGUI_FILE_PATH, 'r') as f:
    imgui_content = f.read()

# Find the enum definition in the ImGui header file
enum_pattern = re.compile(r'enum\s+' + re.escape(imgui_name) + r'\s*{([^}]*)}', re.MULTILINE)
match = enum_pattern.search(imgui_content)
enum_body = ''
if match:
    enum_body = match.group(1)
    # print(f'Found enum {imgui_name} with body:\n{enum_body}')

    # Split into individual enum members
    enum_members = [m.strip() for m in enum_body.split('\n') if m.strip()]

    # If contains "[Internal]", remove those members
    enum_members = [m for m in enum_members if '[Internal]' not in m]

    # Remove comments and whitespace from each member
    enum_members = [re.sub(r'\s+', '', re.sub(r'//.*', '', re.sub(r'/\*.*?\*/', '', m))) for m in enum_members]

    # Remove any empty members
    enum_members = [m for m in enum_members if m]

    # Remove ImGui enum name from each member
    enum_members = [re.sub(re.escape(imgui_name), '', m) for m in enum_members]

    # Change '=' to ' = ' and '<<' to ' << ' for readability
    enum_members = [re.sub(r'=', ' = ', m) for m in enum_members]
    enum_members = [re.sub(r'<<', ' << ', m) for m in enum_members]

    # Create a readable string format for each member
    enum_members_text = '\n'.join(f'        {m}' for m in enum_members)

    # Get count of members (not including "None")
    enum_count = len([m for m in enum_members if not m.startswith('None')])

    # Create file text
    file_text = f'''#pragma once

namespace Minty
{{
    enum class {minty_name}
    {{
{enum_members_text}

        Count = {enum_count},
        Default = {enum_members[0][:enum_members[0].index('=')] if enum_members else 'None'}
    }};
}}'''
    print(file_text)
    cv.set_clipboard(file_text)
else:
    print(f'Enum {imgui_name} not found in {IMGUI_FILE_PATH}')