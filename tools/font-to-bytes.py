# MASSIVE WIP to decode arbitrary fonts, far from working

from fontTools import ttLib
from ttfquery import describe
from ttfquery import glyphquery
import ttfquery.glyph as glyph
from skimage.draw import line
import numpy as np
from PIL import Image

import imageio.v3 as iio


fname = 'assets/PressStart2P-Regular.ttf'
# tt = ttLib.TTFont(fname)
# print([n.string.decode('utf-8') for n in tt['name'].names])
# ??

# print(tt.getGlyphNames())

# A_glyph_id = tt.getGlyphID('A')

# gset = tt.getGlyphSet()
# gset.keys()

# a_glyph = gset.get('B')

font = describe.openFont(fname)

for c in map(chr, range(65, 65+26)):
    g = glyph.Glyph(glyphquery.glyphName(font, c))
    size = 256
    img = np.zeros(shape=(size, size), dtype=np.uint8)

    contours = g.calculateContours(font)
    last_x = last_y = None
    first_x = first_y = None
    for contour in contours:
        for point, flag in contour:
            print(point, flag)
            x, y = map(lambda x: int(x / 1025 * size), point)
            print(x,y)
            if last_x and last_y:
                rr, cc = line(last_y, last_x, y, x)
                img[rr, cc] = 255
            else:
                first_x = x
                first_y = y

            last_x = x
            last_y = y

    line(y, x, first_y, first_x)
    Image.fromarray(img[::-1, ...]).save(f'/tmp/png/{c}.png')