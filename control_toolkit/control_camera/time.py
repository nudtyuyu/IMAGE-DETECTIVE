'''
* File name: control_camera/time.py
* Author: Healer(胡玉)
* Author's blog: https://github.com/nudtyuyu
* Date: Aug 18th, 2022
* 描述：本文件实现了摄像头捕获图片的JPEG压缩解压缩时间统计
'''






import matplotlib.pyplot as plt
from PIL import Image
import os
import numpy as np


Compress_rate=[]
USER_TIME=[]
SYS_TIME=[]
REAL_TIME=[]
time_folder = "./camera/time"
timelist = os.listdir(time_folder)
timelist.sort()
num=0;




 

for times in timelist:
	timeurl = os.path.join(time_folder,times)
	fp = open(timeurl,'rb')
	fp.readline()
	rel_time=fp.readline().split()
	usr_time=fp.readline().split()
	sys_time=fp.readline().split()
	USER_TIME.append(float(usr_time[1][2:7]))
	##print(times,float(usr_time[1][2:7]))
	##SYS_TIME.append(float(sys_time[1][2:7]))
	##REAL_TIME.append(float(rel_time[1][2:7]))
print("------------------------------------------")
print("---------Compression Time-------")
print("Average Time:        ",sum(USER_TIME)/len(USER_TIME))
print("MAX Time:            ",max(USER_TIME))
print("MIN Time:            ",min(USER_TIME))	
print("The Variance of Time:",np.var(USER_TIME))

    
    
    


