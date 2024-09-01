#!/usr/bin/env python

message = """
WISDOM

COUR-
AGE

JUST
-ICE

TEMPE-
RANCE
""".strip()

if __name__ == "__main__":

    lines = message.split("\n")
    print(f"uint8_t line[{len(lines)}][6] = {{")
    for line in lines:
        encoded_line = ','.join([str(ord(c) - 32) for c in line])
        print(f"{{ {encoded_line} }},")
    print("};")
