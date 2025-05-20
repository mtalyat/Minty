import os
import re

DIRECTORY = os.path.dirname(os.path.abspath(__file__))
FILE_INPUT = os.path.join(DIRECTORY, 'input.txt')
FILE_OUTPUT = os.path.join(DIRECTORY, 'output.txt')

PATTERN_EMPTY = re.compile(r'^\s*($|//)')
PATTERN_ENUM_NAME = re.compile(r'^\s*enum (class )?([a-zA-Z]\w*)\s*{?\s*$')
PATTERN_VALUE_NAME = re.compile(r'^\s*(\w+)\s*(=\s*[\dbBxX]+\s*)?,?\s*$')
PATTERN_PASCAL_TO_SNAKE = re.compile(r'(?<!^)(?=[A-Z])')

def generate(lines):
    # parse out name
    nameText = lines[0]
    nameMatch = re.search(PATTERN_ENUM_NAME, nameText)
    if nameMatch is None: 
        print(f'Name not found in line "{nameText}".')
        return
    name = nameMatch.group(2)
    name2 = re.sub(PATTERN_PASCAL_TO_SNAKE, '_', name).lower()

    # parse out the values
    values = []
    for line in lines[1:]:
        valueMatch = re.search(PATTERN_VALUE_NAME, line)
        if valueMatch:
            values.append(valueMatch.group(1))

    # if the first value is "Undefined", ignore it (default case)
    if values[0] == "Undefined":
        values = values[1:]

    # create output
    output = ''

    # helpers
    def loop_with_values(formattedString):
        result = ''
        for value in values:
            result += formattedString.format(value)
        return result
    
    def header(name):
        return f'====================\n\t{name}\n====================\n\n'
    
    #   ToString
    output += header('Header:')
    output += f'''#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

    String to_string({name} const obj);
    {name} parse_to_{name2}(String const& string);
    Bool parse_try_{name2}(String const& string, {name}& value);
    template<>
    inline {name} parse_to<{name}>(String const& string) {{ return parse_to_{name2}(string); }}
    template<>
    inline Bool parse_try<{name}>(String const& string, {name}& value) {{ return parse_try_{name2}(string, value); }}

'''
    
    output += header('Source:')
    temp = loop_with_values(f'\t\tcase {name}::{{0}}: return "{{0}}";\n')
    output += f'''using namespace Minty;

String Minty::to_string({name} const obj)
{{
    switch (obj)
	{{
{temp}
		default: return "";
	}}
}}

'''
    temp = loop_with_values(f'\tif (string == "{{0}}") return {name}::{{0}};\n')
    output += f'''{name} Minty::parse_to_{name2}(String const& string)
{{
{temp}
	return {name}();
}}

Bool Minty::parse_try_{name2}(String const& string, {name}& value)
{{
	value = parse_to_{name2}(string);
'''
    if values[0] == "Undefined":
        output += f'\treturn value != {name}();\n'
    else:
        output += f'\treturn true;\n'
    output += f'''}}

'''
    
    output += header('Test Header:')
    output += f'''#pragma once

#include "Test.h"

void test_{name}(Test& _test);

'''
    
    output += header('Test Source:')
    temp = loop_with_values(f'\t\t\t{{{{{name}::{{0}}, "{{0}}"}}}},\n')
    output += f'''#include "Test_{name}.h"
#include "Minty.h"

void test_{name}(Test& _test)
{{
	CATEGORY({name})
	{{
        std::vector<std::pair<{name}, String>> VALUES = {{
{temp}        }};
    
        TEST("To String")
        {{
            for (auto const& [value, name] : VALUES)
            {{
                EXPECT_EQUAL(to_string(value), name);
            }}
        }}

        TEST("Parse To")
        {{
            for (auto const& [value, name] : VALUES)
            {{
                EXPECT_EQUAL(parse_to_{name2}(name), value);
            }}

            EXPECT_EQUAL(parse_to_{name2}(""), {name}());
        }}

        TEST("Parse Try")
        {{
            {name} result;
            for (auto const& [value, name] : VALUES)
            {{
                EXPECT_TRUE(parse_try_{name2}(name, result));
                EXPECT_EQUAL(result, value);
            }}

            EXPECT_FALSE(parse_try_{name2}("", result));
            EXPECT_EQUAL(result, {name}());
        }}
	}}
}}
'''
    
    # output
    with open(FILE_OUTPUT, 'w') as file:
        file.write(output)

def main():
    # load text
    with open(FILE_INPUT, 'r') as file:
        lines = file.readlines()

    # remove empty lines
    lines = [line for line in lines if not re.match(PATTERN_EMPTY, line)]

    # do the work
    generate(lines)

    # notify
    print('Done.')


if __name__ == '__main__':
    main()