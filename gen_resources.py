import sys
import os
import re

resources_file = sys.argv[1]
resources = sys.argv[2:]

with open(resources_file, 'w') as gen_result:
    for resource_file in resources:
        file_ext = os.path.splitext(resource_file)[-1]
        filename = re.findall(r'([^/]+)$', resource_file)[0]
        filename = re.sub(r'\.| |-', '_', filename)

        if file_ext in [".vert", ".frag", ".obj"]:
            with open(resource_file, 'r') as file:
                data = file.read()
            data = data.replace("\n", "\\n")
            gen_result.write(f"const char {filename}[] = \"{data}\";\n")
        else:
            with open(resource_file, 'rb') as file:
                data = file.read()
            data = ','.join(f'0x{b:02x}' for b in data)
            gen_result.write(f"const unsigned char {filename}[] = {{{data}}};\n")
