import cv2
import numpy as np
import argparse
NUM = 1  ## 图片数量
ratio = 35 ##压缩质量系数


def imgBrightness(img1, c, b): 
    rows, cols, channels = img1.shape
    blank = np.zeros([rows, cols, channels], img1.dtype)
    rst = cv2.addWeighted(img1, c, blank, 1-c, b)
    return rst

def edit(style,filename,degree=90,lightness=1.5,direc="up-side-down"):
        for i in range(1,NUM+1,1):
                path1 = r"./antiedit/origin/" +filename+".bmp"
                path2 = r"./antiedit/mask/" + filename +".bmp"
                img1 = cv2.imread(path1)
                img2 = cv2.imread(path2)
                size1=img1.shape
                size2=img2.shape
                h1=size1[0]
                h2=size2[0]
                w1=size1[1]
                w2=size2[1]
                ##print(h1,h2,w1,w2)
                img2_part = img2[h2//3:h2*2//3,h1//4:h1//2]
                if(style=="rotate"):
                        if(degree==90):
                                dst = cv2.rotate(img2_part, cv2.ROTATE_90_CLOCKWISE)
                        elif(degree ==180):
                                dst = cv2.rotate(img2_part, cv2.ROTATE_180)
                        elif(degree ==270):
                                dst = cv2.rotate(img2_part, cv2.ROTATE_90_COUNTERCLOCKWISE)
                elif(style=="light"):
                        dst=imgBrightness(img2_part,lightness,3)
                elif(style=="flip"):
                        if(direc=="up-side-down"):
                                dst = cv2.flip(img2_part, 0)
                        elif(direc=="left-right"):
                                dst = cv2.flip(img2_part,1)
                        elif(direc=="dialog"):
                                dst = cv2.flip(img2_part,-1)
                        else:
                                dst = cv2.flip(img2_part, 0)
                        ###dst = np.vstack((img2_part, res))
                        
                else:
                        dst = img2_part
                img1[h2//3:h2*2//3,h1//4:h1//2] = dst
                path3 = r"./antiedit/from/" + filename +".jpg"
                params =[cv2.IMWRITE_JPEG_QUALITY,ratio]
                msg = cv2.imencode(".jpeg",img1,params)[1]
                msg = (np.array(msg)).tobytes()
                ##print("msg:",len(msg))
                cv2.imwrite(path3,img1,[cv2.IMWRITE_JPEG_QUALITY,50])


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='para transfer')
    parser.add_argument('--style', type=str,default="nothing", help='style -> transfer way.')
    parser.add_argument('--degree', type=int, default=180, help='degree -> rotation 90,180,270.')
    parser.add_argument('--lightness', type=float, default=2.0, help='lightness -> (0,3)')
    parser.add_argument('--direc', type=str, default="up-side-down", help='direc -> flip direction')
    parser.add_argument('--filename', type=str, default="1", help='filename -> pic to edit')
    args = parser.parse_args()
    ##print(args)
    edit(args.style,lightness=args.lightness,degree=args.degree,direc=args.direc,filename=args.filename)
                
