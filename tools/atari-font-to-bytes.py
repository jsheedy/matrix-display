# from https://atariage.com/forums/topic/267380-atari-font-as-assembly-source-file/

def read_glyph(f):
    header = f.readline()
    assert header.startswith(';')
    # print(header)
    for i in range(8):
        l = f.readline().strip()
        bits = l[-8:]
        b = int(bits, 2)
        # yield(f'0x{0:02x}')
        yield(f'0x{b:02x}')
    assert f.readline().strip() == ''

def get_bytes():
    with open('assets/atari-font.s') as f:
        for i in range(344):
            f.readline()

        # we're at 'A"
        for i in range(26):
            for b in read_glyph(f):
                yield b

        # skip 5 to heart
        for i in range(5 * 10):
            f.readline()

        for b in read_glyph(f):
            yield b
        print('')
print("const uint8_t atari[208] PROGMEM = {")
for i, b in enumerate(get_bytes()):
    print(b, end=', ')
print("};")
