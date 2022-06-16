import sys

import imageio
import numpy as np
from PIL import Image


WIDTH = 24
HEIGHT = 24

def synthetic_grid():
    return ', '.join([i % 2 == 0 and '0xff00ff' or '0x00ffff' for i in range(WIDTH * HEIGHT)])


def print_arr(arr, resize=(24, 24)):

    if resize:
        arr = np.array(Image.fromarray(arr).resize(resize, Image.NEAREST))

    height, width, channels = arr.shape

    if channels == 4:
        arr[:, :] = arr
        alpha = arr[:, :, 3]
        mask = alpha == 0
        arr[mask] = 0

    arr = np.rot90(arr)
    arr = arr[: , ::-1, :]
    arr = (arr / 8).astype(np.uint16)

    for y in range(height):
        for x in range(width):
            p = arr[y, x]
            bitpacked = (p[0] << 11) + (p[1] << 5) + p[2]
            s = f'0x{bitpacked:02x},'
            print(s, end=' ')


def print_progmem(prefix, im):
    l = len(im)
    # if l > 100:
    #     skip = 18
    # else:
    #     skip = 1
    # skip_im = im[::skip]
    # l = len(skip_im)

    m = 24 * 24
    lm = l*m

    print(f"const uint8_t {prefix}_length = {l};")
    print(f"const uint16_t {prefix}[{lm}] " + "PROGMEM = {", end='')

    for arr in im:
        print_arr(arr)
    print("};")


if __name__ == '__main__':
    fname = sys.argv[1]
    arr_name = sys.argv[2]

    im = [frame for frame in imageio.read(fname)]

    print_progmem(arr_name, im)