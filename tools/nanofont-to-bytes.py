import imageio.v3 as iio
import numpy as np

if __name__ == "__main__":
    im = iio.imread("assets/nanofont3x4.bmp")
    # source data is 8 chars height, 16 chars wide,
    # each 4x4 pixels
    # iterate across each char from the top left,
    # skipping the first two rows which are blank
    # so 6 rows * 16 cols * 2 bytes per char (4x4 pixels)
    print("const uint8_t nanofont_bits[192] PROGMEM = {")
    for row in range(2, 8):
        for col in range(16):

            char = im[
                (row * 4): (row * 4) + 4,
                (col * 4): (col * 4) + 4,
            ]
            char_str = ", ".join(f"0x{byte:02x}" for byte in np.packbits(char)) + ", "
            print(char_str)
    print("};")
