/*摄像头捕获图片并存储*/
/**************************************************
* File name: control_camera/gcommand.cpp
* Author: Healer(胡玉)
* Author's blog: https://github.com/nudtyuyu
* Date: Aug 18th, 2022
* 
* 描述：摄像头捕获图片并存储
**************************************************/


#include <iostream>

#include <string>

#include <opencv2/imgcodecs.hpp>

#include <opencv2/videoio/videoio.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

using namespace cv;

Mat frame;

int process(VideoCapture& capture) {

 string str;
 
  string suffix = ".bmp";
  string path ="./camera/frames/";  
   unsigned int i = 1;
    namedWindow("Video", WINDOW_NORMAL | WINDOW_FREERATIO);//打开摄像头捕获画面实时窗口

    resizeWindow("Video", 1280, 720);

   
    while(1) {
	if(i==51)
		break;
    
     capture >> frame;
     
      if (frame.empty())
      
       break;
       
       str = path + to_string(i) + suffix;
       i++;
           imshow("Video",frame);
           imwrite(str, frame);
           
            waitKey(5);
            
             }
             
              return 0;
              
              }
              
              int main()
              
              {
              
               VideoCapture capture(0);
               
                if(!capture.isOpened()) {
                
                 cerr << "open error \n" << endl;
                 
                  return 1;
                  
                   }
                   process(capture);
		   capture.release();
                    return 0;
                    
                    }
                    
                    
