#!/usr/bin/env python3
import cv2
import sys
import os
from datetime import datetime

DEBUG = False
DEBUG = True
TARGET_WIDTH = 128
TARGET_HEIGHT = 64
PIXEL_PER_BYTE = 8
WIDTH_BYTES = int(TARGET_WIDTH/PIXEL_PER_BYTE)
PIXEL_THRESHOLD = 128.0

# 将多个灰度像素打包到一个整数中
def pack_pixels(pixels, threshold):
    value = 0
    for gray in pixels:
        bit = 1 if gray >= threshold else 0 # 二值化
        value = (value << 1) + bit # 多个二值化像素值拼接为一个字节值
    return value

frameCount = 0
def resize_and_binarize_image(frame, width, height, threshold):
    data = []
    # count = 0 # for debug
    start = datetime.now()
    frame = cv2.resize(frame, (width, height)) # 缩放
    frame = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY) # 转为灰度图
    _, binary = cv2.threshold(frame, threshold, 255, cv2.THRESH_BINARY) # 二值化

    for r in range(height):
        for b in range(int(width / PIXEL_PER_BYTE)):
            colStart = b * PIXEL_PER_BYTE
            pixels = frame[r, colStart: colStart + PIXEL_PER_BYTE]
            byte = pack_pixels(pixels, threshold)
            data.append(byte)
    if DEBUG:
        global frameCount
        cv2.imwrite(os.path.join('debug', str(frameCount) + '.png'), frame)
        cv2.imwrite(os.path.join('debug', str(frameCount) + '-bin.png'), binary)
        frameCount += 1
        end = datetime.now()
        print('time cost:', end - start)
    return bytes(data)

def convert_frame_to_bytes(frame):
    return resize_and_binarize_image(frame, TARGET_WIDTH, TARGET_HEIGHT, PIXEL_THRESHOLD)

def main():
    if len(sys.argv) < 3:
        print("Usage: {} input outdir [width] [height] [threshold]".format(sys.argv[0]))
        exit(-1)

    imgPath = sys.argv[1]
    outdir = sys.argv[2]
    width = len(sys.argv) > 3 and int(sys.argv[3]) or TARGET_WIDTH
    height = len(sys.argv) > 4 and int(sys.argv[4]) or TARGET_HEIGHT
    threshold = len(sys.argv) > 5 and int(sys.argv[5]) or PIXEL_THRESHOLD
    imgFile = os.path.split(imgPath)[-1]
    imgBase = imgFile.split('.')[-2]
    codeFile = os.path.join(outdir, imgBase + '.c')
    if not os.path.exists(outdir):
        os.mkdir(outdir)

    frame = cv2.imread(imgPath) # 加载图片
    bitmap = resize_and_binarize_image(frame, width, height, threshold) # 转为目标格式的数组

    with open(codeFile, 'w+') as f: # 输出到.c文件
        f.write('const unsigned char {}Size[] = {{ {}, {} }};\n'.format(imgBase, width, height))
        f.write('const unsigned char {}Data[] = {{\n'.format(imgBase))
        for i in range(len(bitmap)):
            v = bitmap[i]
            sep = '\n' if (i+1) % (TARGET_WIDTH/PIXEL_PER_BYTE) == 0 else ' '
            f.write('0x%02X,%s' % (v, sep))
        f.write('};\n')
    print(imgFile, '=>', codeFile, 'done!')

if __name__ == "__main__":
    main()
