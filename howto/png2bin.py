# -*- coding: utf-8 -*-
from PIL import Image
import os,cv2,sys

def checkfile(filename):
    val = os.path.exists(sfile)
    print('File exist or not:', val)
    return val

def output(sfile, dfile):
    img = cv2.imread(sfile,cv2.IMREAD_UNCHANGED)
    writer = open(dfile,"wb")
    writer.write(img)
    writer.close()
    print(dfile,"saved")

if __name__ == "__main__":
    sfile = sys.argv[1]
    sdir = os.path.dirname(sfile)
    if not checkfile(sfile):
        exit(0)
    else:
        dfile = sdir + '\\' + os.path.basename(sfile).split('.')[0] + '.bin'
        output(sfile, dfile)