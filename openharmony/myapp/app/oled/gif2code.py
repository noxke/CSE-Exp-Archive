#!/usr/bin/env python3
import os
import sys
import cv2
import numpy as np
from datetime import datetime
from PIL import Image

TARGET_WIDTH = 128
TARGET_HEIGHT = 64
PIXEL_PER_BYTE = 8
THRESHOLD = 32

def pack_pixels(pixels, threshold=THRESHOLD):
    value = 0
    for gray in pixels:
        bit = 1 if gray >= threshold else 0 # 二值化
        value = (value << 1) + bit # 多个二值化像素值拼接为一个字节值
    return value

def floyd_steinberg_dithering(gray_image, threshold=THRESHOLD):
    height, width = gray_image.shape
    dithered_image = np.copy(gray_image).astype(np.float32)
    
    for y in range(height):
        for x in range(width):
            old_pixel = dithered_image[y, x]
            new_pixel = 255 if old_pixel > threshold else 0
            dithered_image[y, x] = new_pixel
            error = old_pixel - new_pixel

            if x + 1 < width:
                dithered_image[y, x + 1] += error * 7 / 16
            if y + 1 < height:
                if x - 1 >= 0:
                    dithered_image[y + 1, x - 1] += error * 3 / 16
                dithered_image[y + 1, x] += error * 5 / 16
                if x + 1 < width:
                    dithered_image[y + 1, x + 1] += error * 1 / 16

    dithered_image = np.clip(dithered_image, 0, 255).astype(np.uint8)
    return dithered_image



if len(sys.argv) < 2:
	print('Usage: {} gif outfile'.format(sys.argv[0]))
	exit(-1)

gifimg = sys.argv[1]
outfile = sys.argv[2]
if os.path.exists(outfile):
	os.remove(outfile)

gif = Image.open(gifimg)
frame_count = gif.n_frames

# 遍历每一帧
for frame in range(frame_count):
    # 设置当前帧
    gif.seek(frame)
    
    # 将PIL图像转换为NumPy数组
    frame_image = np.array(gif.convert('RGB'))
    
    # 将NumPy数组转换为OpenCV图像
    cv_image = cv2.cvtColor(frame_image, cv2.COLOR_RGB2BGR)

    # 缩放
    cv_image = cv2.resize(cv_image, (TARGET_WIDTH, TARGET_HEIGHT))
    
    # 转换为灰度图像
    gray_image = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)

    # 抖动处理
    dithered_image = floyd_steinberg_dithering(gray_image)

    cv2.imwrite(f'debug/gray_{frame}_.png', gray_image)
    cv2.imwrite(f'debug/dithered_{frame}.png', dithered_image)


    with open(outfile, 'a+') as f: # 输出到.c文件
        f.write('const unsigned char frame{}Data[] = {{\n'.format(frame))
        for i in range(TARGET_HEIGHT):
            for j in range(0, TARGET_WIDTH, PIXEL_PER_BYTE):
                v = pack_pixels(dithered_image[i][j:j+PIXEL_PER_BYTE])
                sep = '\n' if (j + PIXEL_PER_BYTE >= TARGET_WIDTH) else ' '
                f.write('0x%02X,%s' % (v, sep))
        f.write('};\n')
