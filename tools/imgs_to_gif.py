import os
import sys

import imageio


if __name__ == '__main__':
    png_dir = sys.argv[1]
    gif_name = sys.argv[2]

    images = []
    for file_name in sorted(os.listdir(png_dir)):
        if file_name.endswith('.png'):
            file_path = os.path.join(png_dir, file_name)
            images.append(imageio.imread(file_path))
    imageio.mimsave(gif_name, images, fps=10)