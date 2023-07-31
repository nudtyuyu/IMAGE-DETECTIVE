'''
* File name: 3/view.py
* Author: Healer(胡玉)
* Author's blog: https://github.com/nudtyuyu
* Date: Aug 18th, 2022
* 描述：本文件实现了NEON加速版图片的JPEG压缩解压缩时间统计和统计图绘制
'''






import matplotlib.pyplot as plt
from PIL import Image
import os
import numpy as np

img_folder ="./bmp2jpeg-optimized/frames"  #需要识别图片的文件夹
imlist = os.listdir(img_folder)
imlist.sort()
img_compress_folder ="./bmp2jpeg-optimized/b"  #需要识别图片的文件夹
imlist_compress = os.listdir(img_compress_folder)
imlist_compress.sort()

Compress_rate=[]
USER_TIME=[]
SYS_TIME=[]
REAL_TIME=[]
time_folder = "./bmp2jpeg-optimized/time"
timelist = os.listdir(time_folder)
timelist.sort()
num=0;


for image,image_compress in zip(imlist,imlist_compress):
	imurl = os.path.join(img_folder,image)
	imurl_compress = os.path.join(img_compress_folder,image_compress)
	##print(imurl)
	fp = open(imurl,'rb')
	fp_compress = open(imurl_compress,'rb')
	size = len(fp.read())
	size_compress = len(fp_compress.read())
	fp.close()
	fp_compress.close()
	Compress_rate.append(size/size_compress)

 

for times in timelist:
	timeurl = os.path.join(time_folder,times)
	fp = open(timeurl,'rb')
	fp.readline()
	rel_time=fp.readline().split()
	usr_time=fp.readline().split()
	sys_time=fp.readline().split()
	USER_TIME.append(float(usr_time[1][2:7]))
	##print(times,float(usr_time[1][2:7]))
	SYS_TIME.append(float(sys_time[1][2:7]))
	REAL_TIME.append(float(rel_time[1][2:7]))
print("++++++NEON加速+++++++")
print("压缩",len(USER_TIME),"张图片用时: %.6f s"%(sum(USER_TIME)))
print("单张平均用时: %.6f s"%(sum(USER_TIME)/len(USER_TIME)))
'''print("Average Time:        ",sum(USER_TIME)/len(USER_TIME))
print("MAX Time:            ",max(USER_TIME))
print("MIN Time:            ",min(USER_TIME))	
print("The Variance of Time:",np.var(USER_TIME))
'''
plt.plot(USER_TIME,Compress_rate,'g.')
plt.xlabel("Time For JPEG Compression: second")
plt.ylabel("Compression Rate: original_size/output_size")
path = "./bmp2jpeg-optimized/img/graph_"+ str(num)+".png"
plt.savefig(path)
    


