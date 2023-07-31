# -*- coding: utf-8 -*-

'''
* File name: MainWindow.py
* Author: Healer(Yu Hu)
* Author's blog: https://github.com/nudtyuyu
* Date: Aug 18th, 2022
* Description：This document realizes the user's Home interface, including the construction of the interface framework, the placement and property setting of each control, and the function of each button link
'''


from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import *
from PyQt5.QtWidgets import QWidget

import threading
import time
import inspect
import ctypes
import os
import subprocess
import sip

cmd_template = './run %d'

Empty = False
mutex = threading.BoundedSemaphore(1)
Way = -1
PID = 0
outmsg = ""
outerr = ""
CMD = False
BOOST=False
STYLE=True
FILENAME = True
EDIT = False
FINDEDIT=False
SECRET=False




######停止线程########
def _async_raise(tid, exctype):
    """raises the exception, performs cleanup if needed"""
    tid = ctypes.c_long(tid)
    if not inspect.isclass(exctype):
        exctype = type(exctype)
    res = ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, ctypes.py_object(exctype))
    if res == 0:
        raise ValueError("invalid thread id")
    elif res != 1:
        # """if it returns a number greater than one, you're in trouble,
        # and you should call it again with exc=NULL to revert the effect"""
        ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, None)
        raise SystemError("PyThreadState_SetAsyncExc failed")
def stop_thread(thread):
    _async_raise(thread.ident, SystemExit)




class Job(threading.Thread):
  '''自定义线程，可支持线程暂停开始'''

  def __init__(self, *args, **kwargs):
    super(Job, self).__init__(*args, **kwargs)
    # 用于暂停线程的标识
    self.__flag = threading.Event()   
    self.__flag.set()    # 设置为True
    # 用于停止线程的标识
    self.__running = threading.Event()   
    self.__running.set()   # 将running设置为True

  def run(self):
    while self.__running.isSet():
      self.__flag.wait()   # 为True时立即返回, 为False时阻塞直到内部的标识位为True后返回
      ##print(time.time())
      ##time.sleep(1)

  def pause(self):
    self.__flag.clear()   # 设置为False, 让线程阻塞

  def resume(self):
    self.__flag.set()  # 设置为True, 让线程停止阻塞

  def stop(self):
    self.__flag.set()    # 将线程从暂停状态恢复, 如果已经暂停的话
    self.__running.clear()    # 设置为False  


class SwitchButton(QWidget):
    """自定义Switch按钮"""

    def __init__(self, parent=None):
        super(SwitchButton, self).__init__(parent)

        # 设置无边框和背景透明
        self.setWindowFlags(self.windowFlags() | QtCore.Qt.FramelessWindowHint)
        self.setAttribute(QtCore.Qt.WA_TranslucentBackground)

        self.resize(160, 60)
        self.state = False  # 按钮状态：True表示开，False表示关

    def mousePressEvent(self, event):
        """鼠标点击事件：用于切换按钮状态"""
        super(SwitchButton, self).mousePressEvent(event)

        self.state = False if self.state else True
        self.update()

    def paintEvent(self, event):
        """绘制按钮"""
        super(SwitchButton, self).paintEvent(event)

        # 创建绘制器并设置抗锯齿和图片流畅转换
        painter = QPainter(self)
        painter.setRenderHints(QPainter.Antialiasing | QPainter.SmoothPixmapTransform)

        # 定义字体样式
        font = QtGui.QFont('Microsoft YaHei')
        font.setPixelSize(18)
        painter.setFont(font)
        font.setBold(True)
        font.setWeight(75)

        # 开关为开的状态
        if self.state:
            # 绘制背景
            painter.setPen(QtCore.Qt.NoPen)
            brush = QtGui.QBrush(QColor(133,208,225))
            painter.setBrush(brush)
            painter.drawRoundedRect(0, 0, self.width(), self.height(), self.height() // 2, self.height() // 2)

            # 绘制圆圈
            painter.setPen(QtCore.Qt.NoPen)
            brush.setColor(QtGui.QColor('#ffffff'))
            painter.setBrush(brush)
            painter.drawRoundedRect(100,3,56,56,28,28)

            # 绘制文本
            painter.setPen(QPen(QColor('#ffffff')))
            painter.setBrush(QtCore.Qt.NoBrush)
            painter.drawText(QtCore.QRect(15,15,85,50), QtCore.Qt.AlignLeft, '加密存储')
        # 开关为关的状态
        else:
            # 绘制背景
            painter.setPen(QtCore.Qt.NoPen)
            brush = QtGui.QBrush(QtGui.QColor(185,206,241,100))
            painter.setBrush(brush)
            painter.drawRoundedRect(0, 0, self.width(), self.height(), self.height()//2, self.height()//2)

            # 绘制圆圈
            pen = QtGui.QPen(QtGui.QColor('#999999'))
            pen.setWidth(1)
            painter.setPen(pen)
            painter.drawRoundedRect(3, 3, 56,56,28,28)

            # 绘制文本
            painter.setBrush(QtCore.Qt.NoBrush)
            painter.drawText(QtCore.QRect(70, 15, 85, 50), QtCore.Qt.AlignLeft, '普通存储')



class Ui_MyApp(object):
    """主界面设计，代码较长，可ctrl+F查找至'所有功能实现'部分查看后续代码"""
    def setupUi(self, MyApp):
        MyApp.setObjectName("MyApp")
        MyApp.resize(1200, 874)
        font = QtGui.QFont()
        font.setPointSize(11)
        font.setBold(True)
        font.setWeight(75)
        MyApp.setFont(font)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/icons/LOGO.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        MyApp.setWindowIcon(icon)
        self.centralwidget = QtWidgets.QWidget(MyApp)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.frame = QtWidgets.QFrame(self.centralwidget)
        self.frame.setStyleSheet("#frame{\n"
"    \n"
"    \n"
"    background-color: rgb(0, 25, 69);\n"
"    border-radius:30px;\n"
"}")
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.frame)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.frame_2 = QtWidgets.QFrame(self.frame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(1)
        sizePolicy.setHeightForWidth(self.frame_2.sizePolicy().hasHeightForWidth())
        self.frame_2.setSizePolicy(sizePolicy)
        self.frame_2.setStyleSheet("#frame_2{\n"
"    \n"
"    background-color: rgb(35, 83, 157);\n"
"    border-top-left-radius:30px;\n"
"    border-top-right-radius:30px;\n"
"}")
        self.frame_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_2.setObjectName("frame_2")
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout(self.frame_2)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.frame_4 = QtWidgets.QFrame(self.frame_2)
        self.frame_4.setMinimumSize(QtCore.QSize(200, 0))
        self.frame_4.setStyleSheet("QFrame{\n"
"    border:none\n"
"}\n"
"QPushButton{\n"
"    border:none;\n"
"}\n"
"QPushButton:hover{\n"
"    padding-bottom:5px;\n"
"}")
        self.frame_4.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_4.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_4.setObjectName("frame_4")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.frame_4)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.pushButton_max = QtWidgets.QPushButton(self.frame_4)
        self.pushButton_max.setStyleSheet("")
        self.pushButton_max.setText("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/icons/max.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_max.setIcon(icon1)
        self.pushButton_max.setObjectName("pushButton_max")
        self.horizontalLayout_2.addWidget(self.pushButton_max)
        self.pushButton_min = QtWidgets.QPushButton(self.frame_4)
        self.pushButton_min.setText("")
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/images/min.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_min.setIcon(icon2)
        self.pushButton_min.setObjectName("pushButton_min")
        self.horizontalLayout_2.addWidget(self.pushButton_min)
        self.pushButton_close = QtWidgets.QPushButton(self.frame_4)
        self.pushButton_close.setText("")
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(":/icons/close.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_close.setIcon(icon3)
        self.pushButton_close.setObjectName("pushButton_close")
        self.horizontalLayout_2.addWidget(self.pushButton_close)
        self.horizontalLayout_3.addWidget(self.frame_4, 0, QtCore.Qt.AlignRight)
        self.verticalLayout.addWidget(self.frame_2)
        self.frame_3 = QtWidgets.QFrame(self.frame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(10)
        sizePolicy.setHeightForWidth(self.frame_3.sizePolicy().hasHeightForWidth())
        self.frame_3.setSizePolicy(sizePolicy)
        self.frame_3.setStyleSheet("QFrame{\n"
"    border:none;\n"
"}")
        self.frame_3.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_3.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_3.setObjectName("frame_3")
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout(self.frame_3)
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_4.setSpacing(0)
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.frame_5 = QtWidgets.QFrame(self.frame_3)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_5.sizePolicy().hasHeightForWidth())
        self.frame_5.setSizePolicy(sizePolicy)
        self.frame_5.setStyleSheet("QPushButton{\n"
"    \n"
"    \n"
"    \n"
"    \n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(191, 230, 252, 255), stop:1 rgba(255, 255, 255, 255));\n"
"    border:none;\n"
"    border-radius:7px;\n"
"    \n"
"    color: rgb(50, 91, 168);\n"
"}\n"
"QPushButton:hover{\n"
"    \n"
"    background-color: rgba(99, 124, 174,80);\n"
"}\n"
"QPushButton:pressed{\n"
"    padding-left:5px;\n"
"    padding-top:5px;\n"
"    \n"
"}\n"
"\n"
"#frame_5{\n"
"    \n"
"    \n"
"    background-color: rgb(102, 120, 145);\n"
"}")
        self.frame_5.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_5.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_5.setObjectName("frame_5")
        self.horizontalLayout_5 = QtWidgets.QHBoxLayout(self.frame_5)
        self.horizontalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_5.setSpacing(0)
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        self.frame_7 = QtWidgets.QFrame(self.frame_5)
        self.frame_7.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_7.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_7.setObjectName("frame_7")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.frame_7)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.pushButton_about = QtWidgets.QPushButton(self.frame_7)
        self.pushButton_about.setMinimumSize(QtCore.QSize(120, 50))
        self.pushButton_about.setMaximumSize(QtCore.QSize(120, 50))
        font = QtGui.QFont()
        font.setFamily("Ubuntu")
        font.setPointSize(11)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_about.setFont(font)
        icon4 = QtGui.QIcon()
        icon4.addPixmap(QtGui.QPixmap(":/icons/aboutus.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_about.setIcon(icon4)
        self.pushButton_about.setIconSize(QtCore.QSize(26, 26))
        self.pushButton_about.setObjectName("pushButton_about")
        self.verticalLayout_2.addWidget(self.pushButton_about)
        self.pushButton_grap = QtWidgets.QPushButton(self.frame_7)
        self.pushButton_grap.setMinimumSize(QtCore.QSize(120, 50))
        self.pushButton_grap.setMaximumSize(QtCore.QSize(120, 50))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_grap.setFont(font)
        icon5 = QtGui.QIcon()
        icon5.addPixmap(QtGui.QPixmap(":/icons/video.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_grap.setIcon(icon5)
        self.pushButton_grap.setIconSize(QtCore.QSize(32, 32))
        self.pushButton_grap.setObjectName("pushButton_grap")
        self.verticalLayout_2.addWidget(self.pushButton_grap)
        self.pushButton_boost = QtWidgets.QPushButton(self.frame_7)
        self.pushButton_boost.setMinimumSize(QtCore.QSize(120, 50))
        self.pushButton_boost.setMaximumSize(QtCore.QSize(120, 50))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_boost.setFont(font)
        icon6 = QtGui.QIcon()
        icon6.addPixmap(QtGui.QPixmap(":/icons/boost.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_boost.setIcon(icon6)
        self.pushButton_boost.setIconSize(QtCore.QSize(30, 30))
        self.pushButton_boost.setObjectName("pushButton_boost")
        self.verticalLayout_2.addWidget(self.pushButton_boost)
        self.pushButton_jpeg = QtWidgets.QPushButton(self.frame_7)
        self.pushButton_jpeg.setMinimumSize(QtCore.QSize(120, 50))
        self.pushButton_jpeg.setMaximumSize(QtCore.QSize(120, 50))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_jpeg.setFont(font)
        icon7 = QtGui.QIcon()
        icon7.addPixmap(QtGui.QPixmap(":/icons/Jpeg.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_jpeg.setIcon(icon7)
        self.pushButton_jpeg.setIconSize(QtCore.QSize(30, 30))
        self.pushButton_jpeg.setObjectName("pushButton_jpeg")
        self.verticalLayout_2.addWidget(self.pushButton_jpeg)
        self.pushButton_cmp = QtWidgets.QPushButton(self.frame_7)
        self.pushButton_cmp.setMinimumSize(QtCore.QSize(120, 50))
        self.pushButton_cmp.setMaximumSize(QtCore.QSize(120, 50))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_cmp.setFont(font)
        icon8 = QtGui.QIcon()
        icon8.addPixmap(QtGui.QPixmap(":/icons/neon.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_cmp.setIcon(icon8)
        self.pushButton_cmp.setIconSize(QtCore.QSize(30, 30))
        self.pushButton_cmp.setObjectName("pushButton_cmp")
        self.verticalLayout_2.addWidget(self.pushButton_cmp)
        self.pushButton_anti = QtWidgets.QPushButton(self.frame_7)
        self.pushButton_anti.setMinimumSize(QtCore.QSize(120, 50))
        self.pushButton_anti.setMaximumSize(QtCore.QSize(120, 50))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_anti.setFont(font)
        icon9 = QtGui.QIcon()
        icon9.addPixmap(QtGui.QPixmap(":/icons/anti.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_anti.setIcon(icon9)
        self.pushButton_anti.setIconSize(QtCore.QSize(30, 30))
        self.pushButton_anti.setObjectName("pushButton_anti")
        self.verticalLayout_2.addWidget(self.pushButton_anti)
        self.horizontalLayout_5.addWidget(self.frame_7, 0, QtCore.Qt.AlignTop)
        self.horizontalLayout_4.addWidget(self.frame_5)
        self.frame_6 = QtWidgets.QFrame(self.frame_3)
        
        
        
        self.pushButton_jpeg.clicked.connect(self.clear)
        self.pushButton_jpeg.clicked.connect(self.reset)
        
        
        
        
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(6)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_6.sizePolicy().hasHeightForWidth())
        self.frame_6.setSizePolicy(sizePolicy)
        self.frame_6.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_6.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_6.setObjectName("frame_6")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.frame_6)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.stackedWidget = QtWidgets.QStackedWidget(self.frame_6)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.stackedWidget.sizePolicy().hasHeightForWidth())
        self.stackedWidget.setSizePolicy(sizePolicy)
        self.stackedWidget.setStyleSheet("background-color: rgba(27, 54, 40,0);\n"
"QHBoxLayout{\n"
"    border:none;\n"
"}")
        self.stackedWidget.setObjectName("stackedWidget")
        self.page_about = QtWidgets.QWidget()
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.page_about.sizePolicy().hasHeightForWidth())
        self.page_about.setSizePolicy(sizePolicy)
        self.page_about.setStyleSheet("")
        self.page_about.setObjectName("page_about")
        self.label = QtWidgets.QLabel(self.page_about)
        self.label.setGeometry(QtCore.QRect(130, 620, 921, 131))
        font = QtGui.QFont()
        font.setFamily("Ani")
        font.setPointSize(44)
        self.label.setFont(font)
        self.label.setStyleSheet("color: rgb(255, 255, 255);")
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(self.page_about)
        self.label_2.setGeometry(QtCore.QRect(0, 240, 251, 101))
        font = QtGui.QFont()
        font.setPointSize(24)
        font.setBold(True)
        font.setWeight(75)
        self.label_2.setFont(font)
        self.label_2.setStyleSheet("color: rgb(255, 255, 255);")
        self.label_2.setObjectName("label_2")
        self.plainTextEdit_2 = QtWidgets.QPlainTextEdit(self.page_about)
        self.plainTextEdit_2.setGeometry(QtCore.QRect(10, 10, 951, 241))
        font = QtGui.QFont()
        font.setPointSize(22)
        font.setBold(True)
        font.setWeight(75)
        self.plainTextEdit_2.setFont(font)
        self.plainTextEdit_2.setStyleSheet("color: rgb(255, 255, 255);")
        self.plainTextEdit_2.setObjectName("plainTextEdit_2")
        self.frame_26 = QtWidgets.QFrame(self.page_about)
        self.frame_26.setGeometry(QtCore.QRect(170, 310, 701, 321))
        self.frame_26.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_26.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_26.setObjectName("frame_26")
        self.feng = QtWidgets.QPushButton(self.frame_26)
        self.feng.setGeometry(QtCore.QRect(260, 20, 151, 261))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.feng.sizePolicy().hasHeightForWidth())
        self.feng.setSizePolicy(sizePolicy)
        self.feng.setMinimumSize(QtCore.QSize(0, 0))
        self.feng.setMaximumSize(QtCore.QSize(806, 1081))
        font = QtGui.QFont()
        font.setPointSize(28)
        self.feng.setFont(font)
        self.feng.setStyleSheet("QPushButton{\n"
"border-radius:5px;\n"
"    color: rgb(255, 255, 255);\n"
"    \n"
"    background-color: rgba(20, 78, 205,100);\n"
"}\n"
"QPushButton:pressed{\n"
"    padding-left:5px;\n"
"    padding-top:5px;\n"
"    \n"
"}\n"
"QPushButton:hover{\n"
"    border-image: url(:/images/fengfeng.jpg);\n"
"}")
        self.feng.setObjectName("feng")
        self.lzt = QtWidgets.QPushButton(self.frame_26)
        self.lzt.setGeometry(QtCore.QRect(470, 20, 151, 261))
        self.lzt.setMaximumSize(QtCore.QSize(1354, 1432))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.lzt.setFont(font)
        self.lzt.setStyleSheet("QPushButton{\n"
"border-radius:5px;\n"
"    color: rgb(255, 255, 255);\n"
"    \n"
"    background-color: rgba(20, 78, 205,100);\n"
"}\n"
"QPushButton:pressed{\n"
"    padding-left:5px;\n"
"    padding-top:5px;\n"
"    \n"
"}\n"
"QPushButton:hover{\n"
"    border-image: url(:/images/lzt.jpg);\n"
"}")
        self.lzt.setObjectName("lzt")
        self.healer = QtWidgets.QPushButton(self.frame_26)
        self.healer.setGeometry(QtCore.QRect(50, 20, 151, 261))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.healer.sizePolicy().hasHeightForWidth())
        self.healer.setSizePolicy(sizePolicy)
        self.healer.setMinimumSize(QtCore.QSize(0, 0))
        self.healer.setMaximumSize(QtCore.QSize(806, 1081))
        font = QtGui.QFont()
        font.setPointSize(30)
        self.healer.setFont(font)
        self.healer.setStyleSheet("QPushButton{\n"
"border-radius:5px;\n"
"    color: rgb(255, 255, 255);\n"
"    \n"
"    background-color: rgba(20, 78, 205,100);\n"
"}\n"
"QPushButton:pressed{\n"
"    padding-left:5px;\n"
"    padding-top:5px;\n"
"    \n"
"}\n"
"QPushButton:hover{\n"
"    border-image: url(:/images/healer.jpg);\n"
"}")
        self.healer.setObjectName("healer")
        
        self.healer.clicked.connect(self.about_healer)
        self.feng.clicked.connect(self.about_feng)
        self.lzt.clicked.connect(self.about_lzt)
        
        
        self.stackedWidget.addWidget(self.page_about)
        self.page_grap = QtWidgets.QWidget()
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.page_grap.sizePolicy().hasHeightForWidth())
        self.page_grap.setSizePolicy(sizePolicy)
        self.page_grap.setObjectName("page_grap")
        self.horizontalLayout_6 = QtWidgets.QHBoxLayout(self.page_grap)
        self.horizontalLayout_6.setObjectName("horizontalLayout_6")
        self.frame_8 = QtWidgets.QFrame(self.page_grap)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_8.sizePolicy().hasHeightForWidth())
        self.frame_8.setSizePolicy(sizePolicy)
        self.frame_8.setMinimumSize(QtCore.QSize(0, 0))
        self.frame_8.setStyleSheet("QHBoxLayout{\n"
"    border:none;\n"
"}")
        self.frame_8.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_8.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_8.setObjectName("frame_8")
        self.label_3 = QtWidgets.QLabel(self.frame_8)
        self.label_3.setGeometry(QtCore.QRect(0, -10, 361, 71))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_3.sizePolicy().hasHeightForWidth())
        self.label_3.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(24)
        font.setBold(True)
        font.setWeight(75)
        self.label_3.setFont(font)
        self.label_3.setStyleSheet("color: rgb(255, 255, 255);")
        self.label_3.setObjectName("label_3")
        self.progressBar = QtWidgets.QProgressBar(self.frame_8)
        self.progressBar.setGeometry(QtCore.QRect(50, 540, 921, 61))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.progressBar.sizePolicy().hasHeightForWidth())
        self.progressBar.setSizePolicy(sizePolicy)
        self.progressBar.setStyleSheet("#progressBar{\n"
"    \n"
"    background-color: rgba(79, 93, 81,75);\n"
"    \n"
"    color: white;\n"
"    border-radius:10px;\n"
"}\n"
"#progressBar:chunk{\n"
"    \n"
"    background-color: rgb(95, 178, 222);\n"
"    border-radius:10px;\n"
"}")
        self.progressBar.setProperty("value", 0)
        self.progressBar.setProperty("maximum",7000)
        self.progressBar.setAlignment(QtCore.Qt.AlignCenter)
        self.progressBar.setObjectName("progressBar")
        self.frame_9 = QtWidgets.QFrame(self.frame_8)
        self.frame_9.setGeometry(QtCore.QRect(210, 600, 751, 131))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_9.sizePolicy().hasHeightForWidth())
        self.frame_9.setSizePolicy(sizePolicy)
        self.frame_9.setStyleSheet("QPushButton:pressed{\n"
"    padding-left:5px;\n"
"    padding-top:5px;\n"
"    \n"
"}")
        self.frame_9.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_9.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_9.setObjectName("frame_9")
        self.pushButton_start = QtWidgets.QPushButton(self.frame_9)
        self.pushButton_start.setGeometry(QtCore.QRect(230, 40, 141, 71))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.pushButton_start.sizePolicy().hasHeightForWidth())
        self.pushButton_start.setSizePolicy(sizePolicy)
        self.pushButton_start.setMinimumSize(QtCore.QSize(0, 20))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_start.setFont(font)
        self.pushButton_start.setStyleSheet("QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(191, 230, 252, 255), stop:1 rgba(255, 255, 255, 255));\n"
"    border:none;\n"
"    \n"
"    \n"
"    color: rgb(50, 91, 168);\n"
"border-radius:10px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    padding-left:5px;\n"
"    padding-top:5px;\n"
"    \n"
"}\n"
"QPushButton:hover{\n"
"    \n"
"    background-color: rgba(255,255,255,240);\n"
"}")
        self.pushButton_start.setObjectName("pushButton_start")
        self.pushButton_stop = QtWidgets.QPushButton(self.frame_9)
        self.pushButton_stop.setGeometry(QtCore.QRect(440, 40, 131, 71))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.pushButton_stop.sizePolicy().hasHeightForWidth())
        self.pushButton_stop.setSizePolicy(sizePolicy)
        self.pushButton_stop.setMinimumSize(QtCore.QSize(0, 20))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_stop.setFont(font)
        self.pushButton_stop.setStyleSheet("QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(191, 230, 252, 255), stop:1 rgba(255, 255, 255, 255));\n"
"    border:none;\n"
"    \n"
"    color: rgb(50, 91, 168);\n"
"border-radius:10px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    padding-left:5px;\n"
"    padding-top:5px;\n"
"    \n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    \n"
"    background-color: rgba(255,255,255,240);\n"
"}")
        self.pushButton_stop.setObjectName("pushButton_stop")
        self.switch_secret  = SwitchButton(self.frame_9)
        self.switch_secret.setObjectName("switch_secret")
        self.switch_secret.setGeometry(QtCore.QRect(0, 45, 160, 60))
        
        self.pushButton_start.clicked.connect(self.button_camera)
        self.pushButton_stop.clicked.connect(self.stop_camera)
        
            
        
        
        
        
        
        
        
        
        
        
        
        self.frame_25 = QtWidgets.QFrame(self.frame_8)
        self.frame_25.setGeometry(QtCore.QRect(20, 60, 971, 451))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_25.sizePolicy().hasHeightForWidth())
        self.frame_25.setSizePolicy(sizePolicy)
        self.frame_25.setStyleSheet("background-color: rgba(211, 215, 207,80);\n"
"border:none;")
        self.frame_25.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_25.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_25.setObjectName("frame_25")
        self.horizontalLayout_6.addWidget(self.frame_8)
        self.stackedWidget.addWidget(self.page_grap)
        self.page_boost = QtWidgets.QWidget()
        self.page_boost.setObjectName("page_boost")
        self.frame_10 = QtWidgets.QFrame(self.page_boost)
        self.frame_10.setGeometry(QtCore.QRect(10, 60, 1011, 481))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_10.sizePolicy().hasHeightForWidth())
        self.frame_10.setSizePolicy(sizePolicy)
        self.frame_10.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_10.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_10.setObjectName("frame_10")
        self.horizontalLayout_7 = QtWidgets.QHBoxLayout(self.frame_10)
        self.horizontalLayout_7.setObjectName("horizontalLayout_7")
        self.frame_11 = QtWidgets.QFrame(self.frame_10)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_11.sizePolicy().hasHeightForWidth())
        self.frame_11.setSizePolicy(sizePolicy)
        self.frame_11.setStyleSheet("background-color: rgba(211, 215, 207,80);\n"
"border:none;")
        self.frame_11.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_11.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_11.setObjectName("frame_11")
        self.horizontalLayout_7.addWidget(self.frame_11)
        self.frame_12 = QtWidgets.QFrame(self.frame_10)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_12.sizePolicy().hasHeightForWidth())
        self.frame_12.setSizePolicy(sizePolicy)
        self.frame_12.setStyleSheet("background-color: rgba(211, 215, 207,80);\n"
"border:none;")
        self.frame_12.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_12.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_12.setObjectName("frame_12")
        self.horizontalLayout_7.addWidget(self.frame_12)
        self.label_4 = QtWidgets.QLabel(self.page_boost)
        self.label_4.setGeometry(QtCore.QRect(10, 10, 231, 41))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_4.sizePolicy().hasHeightForWidth())
        self.label_4.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setFamily("Ubuntu")
        font.setPointSize(24)
        font.setBold(True)
        font.setWeight(75)
        self.label_4.setFont(font)
        self.label_4.setStyleSheet("color: rgb(255, 255, 255);")
        self.label_4.setObjectName("label_4")
        self.frame_13 = QtWidgets.QFrame(self.page_boost)
        self.frame_13.setGeometry(QtCore.QRect(20, 390, 581, 61))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_13.sizePolicy().hasHeightForWidth())
        self.frame_13.setSizePolicy(sizePolicy)
        self.frame_13.setStyleSheet("")
        self.frame_13.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_13.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_13.setObjectName("frame_13")
        self.frame_14 = QtWidgets.QFrame(self.page_boost)
        self.frame_14.setGeometry(QtCore.QRect(80, 630, 881, 111))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_14.sizePolicy().hasHeightForWidth())
        self.frame_14.setSizePolicy(sizePolicy)
        self.frame_14.setStyleSheet("QPushButton{\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(191, 230, 252, 255), stop:1 rgba(255, 255, 255, 255));\n"
"    border:none;\n"
"    \n"
"    color: rgb(50, 91, 168);\n"
"    border-radius:10px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    padding-left:5px;\n"
"    padding-top:5px;\n"
"    \n"
"}\n"
"QPushButton:hover{\n"
"    \n"
"    background-color: rgba(255,255,255,240);\n"
"}")
        self.frame_14.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_14.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_14.setObjectName("frame_14")
        self.pushButton_way1 = QtWidgets.QPushButton(self.frame_14)
        self.pushButton_way1.setGeometry(QtCore.QRect(40, 20, 161, 71))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_way1.setFont(font)
        self.pushButton_way1.setObjectName("pushButton_way1")
        self.pushButton_way2 = QtWidgets.QPushButton(self.frame_14)
        self.pushButton_way2.setGeometry(QtCore.QRect(250, 20, 161, 71))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_way2.setFont(font)
        self.pushButton_way2.setObjectName("pushButton_way2")
        self.pushButton_neonway = QtWidgets.QPushButton(self.frame_14)
        self.pushButton_neonway.setGeometry(QtCore.QRect(460, 20, 171, 71))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_neonway.setFont(font)
        self.pushButton_neonway.setObjectName("pushButton_neonway")
        self.pushButton_stopboost = QtWidgets.QPushButton(self.frame_14)
        self.pushButton_stopboost.setGeometry(QtCore.QRect(680, 20, 171, 71))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_stopboost.setFont(font)
        self.pushButton_stopboost.setObjectName("pushButton_stopboost")
        self.progressBar_2 = QtWidgets.QProgressBar(self.page_boost)
        self.progressBar_2.setGeometry(QtCore.QRect(80, 560, 891, 61))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.progressBar_2.sizePolicy().hasHeightForWidth())
        self.progressBar_2.setSizePolicy(sizePolicy)
        self.progressBar_2.setStyleSheet("#progressBar_2{\n"
"    \n"
"    background-color: rgba(79, 93, 81,75);\n"
"    \n"
"    color: white;\n"
"    border-radius:10px;\n"
"}\n"
"#progressBar_2:chunk{\n"
"    \n"
"    background-color: rgb(95, 178, 222);\n"
"    border-radius:10px;\n"
"}")
        self.progressBar_2.setProperty("value", 0)
        self.progressBar_2.setProperty("maximum",7000)
        self.progressBar_2.setAlignment(QtCore.Qt.AlignCenter)
        self.progressBar_2.setObjectName("progressBar_2")
        
        self.pushButton_way1.clicked.connect(self.button_boost1)
        self.pushButton_way2.clicked.connect(self.button_boost2)
        self.pushButton_neonway.clicked.connect(self.button_boost3)
        self.pushButton_stopboost.clicked.connect(self.stop_boost)
        
        
        
        
        
        
        
        
        
        self.stackedWidget.addWidget(self.page_boost)
        self.page_jpeg = QtWidgets.QWidget()
        self.page_jpeg.setObjectName("page_jpeg")
        self.frame_15 = QtWidgets.QFrame(self.page_jpeg)
        self.frame_15.setGeometry(QtCore.QRect(20, 50, 1001, 501))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_15.sizePolicy().hasHeightForWidth())
        self.frame_15.setSizePolicy(sizePolicy)
        self.frame_15.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_15.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_15.setObjectName("frame_15")
        self.frame_16 = QtWidgets.QFrame(self.frame_15)
        self.frame_16.setGeometry(QtCore.QRect(20, 10, 501, 471))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_16.sizePolicy().hasHeightForWidth())
        self.frame_16.setSizePolicy(sizePolicy)
        self.frame_16.setStyleSheet("background-color: rgba(211, 215, 207,80);\n"
"border:none;")
        self.frame_16.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_16.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_16.setObjectName("frame_16")
        self.scrollArea = QtWidgets.QScrollArea(self.frame_15)
        self.scrollArea.setGeometry(QtCore.QRect(530, 10, 461, 471))
        self.scrollArea.setMinimumSize(QtCore.QSize(0, 0))
        self.scrollArea.setStyleSheet("background-color: rgba(99, 124, 174,80);")
        self.scrollArea.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOn)
        self.scrollArea.setWidgetResizable(False)
        self.scrollArea.setObjectName("scrollArea")
        self.scrollAreaWidgetContents = QtWidgets.QWidget()
        self.scrollAreaWidgetContents.setGeometry(QtCore.QRect(0, 0, 461, 3000))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.scrollAreaWidgetContents.sizePolicy().hasHeightForWidth())
        self.scrollAreaWidgetContents.setSizePolicy(sizePolicy)
        self.scrollAreaWidgetContents.setObjectName("scrollAreaWidgetContents")
        self.plainTextEdit = QtWidgets.QPlainTextEdit(self.scrollAreaWidgetContents)
        self.plainTextEdit.setGeometry(QtCore.QRect(0, 0, 461, 3000))
        self.plainTextEdit.setObjectName("plainTextEdit")
        self.plainTextEdit.setStyleSheet("color:white;")
        font = QtGui.QFont()
        font.setPointSize(18)
        font.setBold(True)
        font.setWeight(75)
        self.plainTextEdit.setFont(font)
        self.scrollArea.setWidget(self.scrollAreaWidgetContents)
        self.label_5 = QtWidgets.QLabel(self.page_jpeg)
        self.label_5.setGeometry(QtCore.QRect(30, 0, 211, 41))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_5.sizePolicy().hasHeightForWidth())
        self.label_5.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(24)
        font.setBold(True)
        font.setWeight(75)
        self.label_5.setFont(font)
        self.label_5.setStyleSheet("color: rgb(255, 255, 255);")
        self.label_5.setObjectName("label_5")
        self.progressBar_3 = QtWidgets.QProgressBar(self.page_jpeg)
        self.progressBar_3.setGeometry(QtCore.QRect(50, 560, 881, 61))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.progressBar_3.sizePolicy().hasHeightForWidth())
        self.progressBar_3.setSizePolicy(sizePolicy)
        self.progressBar_3.setStyleSheet("#progressBar_3{\n"
"    \n"
"    background-color: rgba(79, 93, 81,75);\n"
"    \n"
"    color: white;\n"
"    border-radius:10px;\n"
"}\n"
"#progressBar_3:chunk{\n"
"    \n"
"    \n"
"    background-color: rgb(95, 178, 222);\n"
"    border-radius:10px;\n"
"}")
        self.progressBar_3.setProperty("value", 0)
        self.progressBar_3.setProperty("maximum", 7000)
        self.progressBar_3.setAlignment(QtCore.Qt.AlignCenter)
        self.progressBar_3.setObjectName("progressBar_3")
        self.frame_17 = QtWidgets.QFrame(self.page_jpeg)
        self.frame_17.setGeometry(QtCore.QRect(40, 620, 791, 141))
        self.frame_17.setStyleSheet("QPushButton{\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(191, 230, 252, 255), stop:1 rgba(255, 255, 255, 255));\n"
"    border:none;\n"
"    \n"
"    color: rgb(50, 91, 168);\n"
"    border-radius:10px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    padding-left:5px;\n"
"    padding-top:5px;\n"
"    \n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    \n"
"    background-color: rgba(255,255,255,240);\n"
"}")
        self.frame_17.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_17.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_17.setObjectName("frame_17")
        self.pushButton_normal = QtWidgets.QPushButton(self.frame_17)
        self.pushButton_normal.setGeometry(QtCore.QRect(20, 60, 121, 61))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_normal.setFont(font)
        self.pushButton_normal.setObjectName("pushButton_normal")
        self.pushButton_fast = QtWidgets.QPushButton(self.frame_17)
        self.pushButton_fast.setGeometry(QtCore.QRect(320, 60, 151, 61))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_fast.setFont(font)
        self.pushButton_fast.setObjectName("pushButton_fast")
        self.pushButton_pthread = QtWidgets.QPushButton(self.frame_17)
        self.pushButton_pthread.setGeometry(QtCore.QRect(160, 60, 141, 61))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_pthread.setFont(font)
        self.pushButton_pthread.setObjectName("pushButton_pthread")
        self.pushButton_stopjpeg = QtWidgets.QPushButton(self.frame_17)
        self.pushButton_stopjpeg.setGeometry(QtCore.QRect(660, 60, 121, 61))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_stopjpeg.setFont(font)
        self.pushButton_stopjpeg.setObjectName("pushButton_stopjpeg")
        self.pushButton_fast_2 = QtWidgets.QPushButton(self.frame_17)
        self.pushButton_fast_2.setGeometry(QtCore.QRect(490, 60, 151, 61))
        font = QtGui.QFont()
        font.setPointSize(18)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_fast_2.setFont(font)
        self.pushButton_fast_2.setObjectName("pushButton_fast_2")
        self.spinBox = QtWidgets.QSpinBox(self.page_jpeg)
        self.spinBox.setGeometry(QtCore.QRect(840, 670, 161, 71))
        font = QtGui.QFont()
        font.setPointSize(26)
        font.setBold(True)
        font.setWeight(75)
        self.spinBox.setFont(font)
        self.spinBox.setStyleSheet("color: rgb(255, 255, 255);\n"
"background-color: rgba(35, 83, 157,80);")
        self.spinBox.setObjectName("spinBox")
        self.spinBox.setProperty("maximum","99999")
        self.stackedWidget.addWidget(self.page_jpeg)
        
        
        self.pushButton_normal.clicked.connect(self.button_jpegnormal)
        self.pushButton_stopjpeg.clicked.connect(self.stop_jpeg)
        self.pushButton_pthread.clicked.connect(self.button_jpegpthread)
        self.pushButton_fast.clicked.connect(self.button_jpegneon)
        self.pushButton_fast_2.clicked.connect(self.button_jpegneon_pthread)
        
        
        
        
        
        
        self.page_cmp = QtWidgets.QWidget()
        self.page_cmp.setObjectName("page_cmp")
        self.frame_18 = QtWidgets.QFrame(self.page_cmp)
        self.frame_18.setGeometry(QtCore.QRect(10, 60, 1011, 501))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_18.sizePolicy().hasHeightForWidth())
        self.frame_18.setSizePolicy(sizePolicy)
        self.frame_18.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_18.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_18.setObjectName("frame_18")
        self.horizontalLayout_11 = QtWidgets.QHBoxLayout(self.frame_18)
        self.horizontalLayout_11.setObjectName("horizontalLayout_11")
        self.frame_19 = QtWidgets.QFrame(self.frame_18)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_19.sizePolicy().hasHeightForWidth())
        self.frame_19.setSizePolicy(sizePolicy)
        self.frame_19.setStyleSheet("background-color: rgba(211, 215, 207,80);\n"
"border:none;")
        self.frame_19.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_19.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_19.setObjectName("frame_19")
        self.horizontalLayout_11.addWidget(self.frame_19)
        self.frame_20 = QtWidgets.QFrame(self.frame_18)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_20.sizePolicy().hasHeightForWidth())
        self.frame_20.setSizePolicy(sizePolicy)
        self.frame_20.setStyleSheet("background-color: rgba(211, 215, 207,80);\n"
"border:none;")
        self.frame_20.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_20.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_20.setObjectName("frame_20")
        self.horizontalLayout_11.addWidget(self.frame_20)
        self.label_6 = QtWidgets.QLabel(self.page_cmp)
        self.label_6.setGeometry(QtCore.QRect(20, 20, 281, 41))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_6.sizePolicy().hasHeightForWidth())
        self.label_6.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(24)
        font.setBold(True)
        font.setWeight(75)
        self.label_6.setFont(font)
        self.label_6.setStyleSheet("color: rgb(255, 255, 255);")
        self.label_6.setObjectName("label_6")
        self.progressBar_4 = QtWidgets.QProgressBar(self.page_cmp)
        self.progressBar_4.setGeometry(QtCore.QRect(60, 570, 911, 61))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.progressBar_4.sizePolicy().hasHeightForWidth())
        self.progressBar_4.setSizePolicy(sizePolicy)
        self.progressBar_4.setStyleSheet("#progressBar_4{\n"
"    \n"
"    background-color: rgba(79, 93, 81,75);\n"
"    \n"
"    color: white;\n"
"    border-radius:10px;\n"
"}\n"
"#progressBar_4:chunk{\n"
"    \n"
"    \n"
"    background-color: rgb(95, 178, 222);\n"
"    border-radius:10px;\n"
"}")
        self.progressBar_4.setProperty("value", 0)
        self.progressBar_4.setProperty("maximum", 7000)
        self.progressBar_4.setAlignment(QtCore.Qt.AlignCenter)
        self.progressBar_4.setObjectName("progressBar_4")
        self.pushButton_cmp_start = QtWidgets.QPushButton(self.page_cmp)
        self.pushButton_cmp_start.setGeometry(QtCore.QRect(430, 660, 161, 61))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_cmp_start.setFont(font)
        self.pushButton_cmp_start.setStyleSheet("QPushButton{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(191, 230, 252, 255), stop:1 rgba(255, 255, 255, 255));\n"
"    border:none;\n"
"    \n"
"    \n"
"    color: rgb(50, 91, 168);\n"
"    border:none;\n"
"    border-radius:10px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    padding-left:5px;\n"
"    padding-top:5px;\n"
"    \n"
"}\n"
"QPushButton:hover{\n"
"    \n"
"    background-color: rgba(255,255,255,240);\n"
"}")
        self.pushButton_cmp_start.setObjectName("pushButton_cmp_start")
        self.stackedWidget.addWidget(self.page_cmp)
        
        
        self.pushButton_cmp_start.clicked.connect(self.button_cmp)
        
        
        
        
        self.page_anti = QtWidgets.QWidget()
        self.page_anti.setObjectName("page_anti")
        self.frame_21 = QtWidgets.QFrame(self.page_anti)
        self.frame_21.setGeometry(QtCore.QRect(20, 50, 981, 501))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_21.sizePolicy().hasHeightForWidth())
        self.frame_21.setSizePolicy(sizePolicy)
        self.frame_21.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_21.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_21.setObjectName("frame_21")
        self.horizontalLayout_12 = QtWidgets.QHBoxLayout(self.frame_21)
        self.horizontalLayout_12.setObjectName("horizontalLayout_12")
        self.frame_22 = QtWidgets.QFrame(self.frame_21)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_22.sizePolicy().hasHeightForWidth())
        self.frame_22.setSizePolicy(sizePolicy)
        self.frame_22.setStyleSheet("background-color: rgba(211, 215, 207,80);\n"
"border:none;")
        self.frame_22.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_22.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_22.setObjectName("frame_22")
        self.horizontalLayout_12.addWidget(self.frame_22)
        self.frame_23 = QtWidgets.QFrame(self.frame_21)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_23.sizePolicy().hasHeightForWidth())
        self.frame_23.setSizePolicy(sizePolicy)
        self.frame_23.setStyleSheet("background-color: rgba(211, 215, 207,80);\n"
"border:none;")
        self.frame_23.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_23.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_23.setObjectName("frame_23")
        self.horizontalLayout_12.addWidget(self.frame_23)
        self.progressBar_5 = QtWidgets.QProgressBar(self.page_anti)
        self.progressBar_5.setGeometry(QtCore.QRect(70, 560, 911, 61))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.progressBar_5.sizePolicy().hasHeightForWidth())
        self.progressBar_5.setSizePolicy(sizePolicy)
        self.progressBar_5.setStyleSheet("#progressBar_5{\n"
"    \n"
"    background-color: rgba(79, 93, 81,75);\n"
"    \n"
"    color: white;\n"
"    border-radius:10px;\n"
"}\n"
"#progressBar_5:chunk{\n"
"    \n"
"    \n"
"    background-color: rgb(95, 178, 222);\n"
"    border-radius:10px;\n"
"}")
        self.progressBar_5.setProperty("value", 0)
        self.progressBar_5.setProperty("maximum", 7000)
        self.progressBar_5.setAlignment(QtCore.Qt.AlignCenter)
        self.progressBar_5.setObjectName("progressBar_5")
        self.label_7 = QtWidgets.QLabel(self.page_anti)
        self.label_7.setGeometry(QtCore.QRect(30, 10, 411, 41))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_7.sizePolicy().hasHeightForWidth())
        self.label_7.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(24)
        font.setBold(True)
        font.setWeight(75)
        self.label_7.setFont(font)
        self.label_7.setStyleSheet("color: rgb(255, 255, 255);")
        self.label_7.setObjectName("label_7")
        self.frame_24 = QtWidgets.QFrame(self.page_anti)
        self.frame_24.setGeometry(QtCore.QRect(120, 620, 821, 151))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_24.sizePolicy().hasHeightForWidth())
        self.frame_24.setSizePolicy(sizePolicy)
        self.frame_24.setStyleSheet("QPushButton{\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(191, 230, 252, 255), stop:1 rgba(255, 255, 255, 255));\n"
"    border:none;\n"
"    \n"
"    color: rgb(50, 91, 168);\n"
"    border-radius:10px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    padding-left:5px;\n"
"    padding-top:5px;\n"
"    \n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    \n"
"    background-color: rgba(255,255,255,240);\n"
"}")
        self.frame_24.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_24.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_24.setObjectName("frame_24")
        self.pushButton_edit = QtWidgets.QPushButton(self.frame_24)
        self.pushButton_edit.setGeometry(QtCore.QRect(70, 40, 141, 71))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_edit.setFont(font)
        self.pushButton_edit.setObjectName("pushButton_edit")
        self.pushButton_antiedit = QtWidgets.QPushButton(self.frame_24)
        self.pushButton_antiedit.setGeometry(QtCore.QRect(260, 40, 141, 71))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_antiedit.setFont(font)
        self.pushButton_antiedit.setObjectName("pushButton_antiedit")
        self.filename = QtWidgets.QLineEdit(self.frame_24)
        self.filename.setGeometry(QtCore.QRect(460, 50, 291, 51))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.filename.setFont(font)
        self.filename.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.filename.setText("")
        self.filename.setObjectName("filename")
        self.comboBox = QtWidgets.QComboBox(self.page_anti)
        self.comboBox.setGeometry(QtCore.QRect(40, 670, 131, 51))
        font = QtGui.QFont()
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.comboBox.setFont(font)
        self.comboBox.setStyleSheet("background-color: rgb(191, 230, 252);")
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.stackedWidget.addWidget(self.page_anti)
        self.verticalLayout_3.addWidget(self.stackedWidget)
        self.horizontalLayout_4.addWidget(self.frame_6)
        self.verticalLayout.addWidget(self.frame_3)
        self.horizontalLayout.addWidget(self.frame)
        MyApp.setCentralWidget(self.centralwidget)
        
        
        self.pushButton_edit.clicked.connect(self.button_edit)
        self.pushButton_antiedit.clicked.connect(self.button_anti)
        self.pushButton_anti.clicked.connect(self.reset) 
        
        
        
        
        
        
        
        
        
        
        

        self.retranslateUi(MyApp)
        self.stackedWidget.setCurrentIndex(0)
        self.pushButton_min.clicked.connect(MyApp.showMinimized)
        self.pushButton_close.clicked.connect(MyApp.close)
        QtCore.QMetaObject.connectSlotsByName(MyApp)

    def retranslateUi(self, MyApp):
        _translate = QtCore.QCoreApplication.translate
        MyApp.setWindowTitle(_translate("MyApp", "MainWindow"))
        self.pushButton_about.setText(_translate("MyApp", "关于我们"))
        self.pushButton_grap.setText(_translate("MyApp", "摄像头"))
        self.pushButton_boost.setText(_translate("MyApp", "图像增强"))
        self.pushButton_jpeg.setText(_translate("MyApp", "图像压缩"))
        self.pushButton_cmp.setText(_translate("MyApp", "性能对比"))
        self.pushButton_anti.setText(_translate("MyApp", "篡改检测"))
        self.label.setText(_translate("MyApp", "JPEG-NEON-SECURITY"))
        self.label_2.setText(_translate("MyApp", "我们的团队："))
        self.plainTextEdit_2.setPlainText(_translate("MyApp", "这是一个具有图像捕获，压缩，自动篡改，篡改检测功能的系统\n"
"我们给该系统取名为JPEG-NEON-SECURITY\n"
"“我们是飞腾对对队，是三个小侦探”\n"
"“眼见不一定为真，有图不一定有真相”\n"
"“因为真相只有一个，JPEG-NEON-SECURITY系统将给你答案”"))
        self.feng.setText(_translate("MyApp", "Banish"))
        self.lzt.setText(_translate("MyApp", "SnoopyBug"))
        self.healer.setText(_translate("MyApp", "Healer"))
        self.label_3.setText(_translate("MyApp", "摄像头实时捕获图像压缩"))
        self.pushButton_start.setText(_translate("MyApp", "开始"))
        self.pushButton_stop.setText(_translate("MyApp", "停止"))
        ##self.switch_secret.setText(_translate("MyApp",""))
        self.label_4.setText(_translate("MyApp", "低照度图像增强"))
        self.pushButton_way1.setText(_translate("MyApp", "邻域信息法"))
        self.pushButton_way2.setText(_translate("MyApp", "反色法"))
        self.pushButton_neonway.setText(_translate("MyApp", "NEON加速"))
        self.pushButton_stopboost.setText(_translate("MyApp", "停止"))
        self.label_5.setText(_translate("MyApp", "JPEG图像处理"))
        self.pushButton_normal.setText(_translate("MyApp", "普通版本"))
        self.pushButton_fast.setText(_translate("MyApp", "NEON加速"))
        self.pushButton_pthread.setText(_translate("MyApp", "多线程加速"))
        self.pushButton_stopjpeg.setText(_translate("MyApp", "停止"))
        self.pushButton_fast_2.setText(_translate("MyApp", "NEON多线程"))
        self.label_6.setText(_translate("MyApp", "加速前后性能对比"))
        self.pushButton_cmp_start.setText(_translate("MyApp", "开始"))
        self.label_7.setText(_translate("MyApp", "图像篡改&篡改检测和定位"))
        self.pushButton_edit.setText(_translate("MyApp", "图像篡改"))
        self.pushButton_antiedit.setText(_translate("MyApp", "篡改检测"))
        self.filename.setPlaceholderText(_translate("MyApp", "请输入文件名"))
        self.comboBox.setItemText(0, _translate("MyApp", "请选择"))
        self.comboBox.setItemText(1, _translate("MyApp", "旋转"))
        self.comboBox.setItemText(2, _translate("MyApp", "亮度"))
        self.comboBox.setItemText(3, _translate("MyApp", "翻转"))
        
        
        
        
        
    ################################################       所有功能实现        #############################################################        
    def about_healer(self):
        msg = QtWidgets.QMessageBox.about(None,"关于","healer")
    def about_feng(self):
        msg = QtWidgets.QMessageBox.about(None,"关于","Banish，别称普信鸡，当代文明小助手，当代睡眠小助手，爱好广泛，会的不多，理想远大，实力没有，主要负责本项目中的jpeg压缩原理和neon加速部分，技术交流：Imthere2002")
    def about_lzt(self):
        msg = QtWidgets.QMessageBox.about(None,"关于","SnoopyBug，当代作风小助手，毛发旺盛，热爱并精通水上运动（尤其划水摸鱼）。负责图像防篡改检测的网络搭建与调试，牵头表情包制作工作。")
    ######Camera Start#######
    def button_camera(self):
        '''点击摄像头开始按钮'''
        self.pic = QtWidgets.QLabel(self.frame_25)
        self.pic.resize(self.frame_25.width(),self.frame_25.height())
        self.pic.setScaledContents(True)
        self.pic.show()
        self.thread_camera = threading.Thread(target = self.camera)
        self.thread_camera.start()
        self.loader = QtCore.QTimer()
        self.loader.timeout.connect(lambda:  self.processbar_run(bar=self.progressBar))
        self.loader.start(30)
        self.checker = QtCore.QTimer()
        try:
            self.checker.timeout.connect(lambda:self.check_processbar(bar=self.progressBar,process=self.thread_camera))
            self.checker.start(100)
        except AttributeError:
            self.checker.stop()
            self.loader.stop()
            sip.delete(self.checker)
            sip.delete(self.loader)
            self.progressBar.setValue(self.progressBar.maximum())
            msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
            msg.exec_()
            self.progressBar.setValue(0)
    def stop_camera(self):
        '''停止摄像头捕获'''
        global PID
        if(self.switch_secret.state):
            if(PID==0):
                return
            kill = "kill -9 "+str(PID)
            popen=subprocess.Popen(kill,shell=True)
            while(1):
                if(subprocess.Popen.poll(popen)!=None):
                    break
        flag = True
        try:
            self.thread_camera
        except AttributeError:
            flag = False
        ##print(flag)
        if(flag):
            stop_thread(self.thread_camera)
        else:
            return
        try:
            self.checker.stop()
            self.loader.stop()
            sip.delete(self.checker)
            sip.delete(self.loader)
        except AttributeError:
            pass

        self.progressBar.setValue(self.progressBar.maximum())
        msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","停止！")
        msg.exec_()
        sip.delete(self.pic)
        self.progressBar.setValue(0)
        
            
    def camera(self):
            '''摄像头捕获图片存储'''
            global PID,SECRET
            opt = 2
            n=1
            cmd=cmd_template % (opt)#生成转换命令
            popen=subprocess.Popen(cmd,shell=True)
            while(1):
                if(subprocess.Popen.poll(popen)!=None):
                    break

            path =os.getcwd()+'/camera/b/'
            num = sum([os.path.isfile(path+listx)for listx in os.listdir(path)])
            image_file = './camera/b/%d.jpg'%(n)
            self.showcamera=QPixmap(image_file)
            ##msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","捕获图像压缩完成！下面开始展示!")
            ##msg.exec_()
            while(1):
                time.sleep(0.1)
                n+=1
            ###print("yesyesyse")
                if(n>num):
                    break
                image_file = './camera/b/%d.jpg'%(n)
                self.showcamera=QPixmap(image_file)
                self.pic.setPixmap(self.showcamera)
            if(self.switch_secret.state):
                SECRET=True
                p = subprocess.Popen("./control_toolkit/encrypt.bat",shell=True)
                PID=p.pid
                while(1):
                    if(subprocess.Popen.poll(p)!=None):
                        break
            
        ######pic boost######
    def button_boost1(self):
            '''低照度图像增强，邻域信息法'''
            global Way
            Way = 0
            self.pic = QtWidgets.QLabel(self.frame_11)
            self.pic.resize(self.frame_11.width(),self.frame_11.height())
            self.pic.setScaledContents(True)
            self.pic.show()
            self.pic2 = QtWidgets.QLabel(self.frame_12)
            self.pic2.resize(self.frame_12.width(),self.frame_12.height())
            self.pic2.setScaledContents(True)
            self.pic2.show()
            self.thread_boost1 = threading.Thread(args=[1,],target = self.boost1)
            self.thread_boost1.start()
            self.loader = QtCore.QTimer()
            self.loader.timeout.connect(lambda:  self.processbar_run(bar=self.progressBar_2))
            self.loader.start(20)
            self.checker = QtCore.QTimer()
            try:
                self.checker.timeout.connect(lambda:self.check_processbar(bar=self.progressBar_2,process=self.thread_boost1))
                self.checker.start(100)
            except AttributeError:
                self.checker.stop()
                self.loader.stop()
                sip.delete(self.checker)
                sip.delete(self.loader)
                self.progressBar_2.setValue(self.progressBar_2.maximum())
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
                msg.exec_()
                self.progressBar_2.setValue(0)
    def button_boost2(self):
            '''低照度图像增强，滤色混合法'''
            global Way
            Way = 1
            self.pic = QtWidgets.QLabel(self.frame_11)
            self.pic.resize(self.frame_11.width(),self.frame_11.height())
            self.pic.setScaledContents(True)
            self.pic.show()
            self.pic2 = QtWidgets.QLabel(self.frame_12)
            self.pic2.resize(self.frame_12.width(),self.frame_12.height())
            self.pic2.setScaledContents(True)
            self.pic2.show()
            self.thread_boost2 = threading.Thread(args=[2,],target = self.boost1)
            self.thread_boost2.start()
            self.loader = QtCore.QTimer()
            self.loader.timeout.connect(lambda:  self.processbar_run(bar=self.progressBar_2))
            self.loader.start(20)
            self.checker = QtCore.QTimer()
            try:
                self.checker.timeout.connect(lambda:self.check_processbar(bar=self.progressBar_2,process=self.thread_boost2))
                self.checker.start(10)
            except AttributeError:
                self.checker.stop()
                self.loader.stop()
                sip.delete(self.checker)
                sip.delete(self.loader)
                self.progressBar_2.setValue(self.progressBar_2.maximum())
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
                msg.exec_()
                self.progressBar_2.setValue(0)
                Way =-1
    def button_boost3(self):
        '''低照度图像增强，NEON加速版本'''
        global Way
        Way = 2
        self.pic = QtWidgets.QLabel(self.frame_11)
        self.pic.resize(self.frame_11.width(),self.frame_11.height())
        self.pic.setScaledContents(True)
        self.pic.show()
        self.pic2 = QtWidgets.QLabel(self.frame_12)
        self.pic2.resize(self.frame_12.width(),self.frame_12.height())
        self.pic2.setScaledContents(True)
        self.pic2.show()
        self.thread_boost3 = threading.Thread(args=[2,],target = self.boost1)
        self.thread_boost3.start()
        self.loader = QtCore.QTimer()
        self.loader.timeout.connect(lambda:  self.processbar_run(bar=self.progressBar_2))
        self.loader.start(20)
        self.checker = QtCore.QTimer()
        try:
            self.checker.timeout.connect(lambda:self.check_processbar(bar=self.progressBar_2,process=self.thread_boost3))
            self.checker.start(10)
        except AttributeError:
            self.checker.stop()
            self.loader.stop()
            sip.delete(self.checker)
            sip.delete(self.loader)
            self.progressBar_2.setValue(self.progressBar_2.maximum())
            msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
            msg.exec_()
            self.progressBar_2.setValue(0)
            Way =-1
    def boost1(self,id):
            '''执行图像增强'''
            global Way,PID,outmsg,BOOST
            BOOST=True
            opt = 5
            n=1
            ##print(id)
            if(id==1):
                way = "--neighbour"
            elif(id==2):
                way = "--inverse"
            elif(id==3):
                way = "--neon"
            cmd=cmd_template % (opt)#生成转换命令
            cmd =cmd+ " "+way
            cmd2 = "./control_toolkit/dark"+str(id-1)
            time_begin=time.perf_counter()
            p=subprocess.Popen(cmd,shell=True)
            while(1):
                if(subprocess.Popen.poll(p)!=None):
                    break
            popen = subprocess.Popen(cmd2,shell=True)
            PID = popen.pid
            ##print(PID)
            while(1):
                if(subprocess.Popen.poll(popen)!=None):
                    break
            time_end=time.perf_counter()
            outmsg = "核心代码执行时间\n%.4f s"%(time_end-time_begin)
            path =os.getcwd()+'/bmp2jpeg/pic/'
            num = sum([os.path.isfile(path+listx)for listx in os.listdir(path)])
            path2 =os.getcwd()+'/bmp2jpeg/frames/'
            image_file = './bmp2jpeg/pic/%d.bmp'%(n)
            image_file2 = './bmp2jpeg/frames-boost/%d.bmp'%(n)
            self.showcamera=QPixmap(image_file)
            self.showcamera2=QPixmap(image_file2)
            while(1):
                time.sleep(0.01)
                n+=1
            ###print("yesyesyse")
                if(n>num):
                    break
                image_file = './bmp2jpeg/pic/%d.bmp'%(n)
                image_file2 = './bmp2jpeg/frames-boost/%d.bmp'%(n)
                self.showcamera=QPixmap(image_file)
                self.showcamera2=QPixmap(image_file2)
                self.pic.setPixmap(self.showcamera)
                self.pic2.setPixmap(self.showcamera2)
    def stop_boost(self):
        n=1

        global Way,PID,outmsg
        if(PID==0):
            return
        kill = "kill -9 "+str(PID)
        popen=subprocess.Popen(kill,shell=True)
        while(1):
            if(subprocess.Popen.poll(popen)!=None):
                break
        time.sleep(1)
        print(outmsg)
        if(Way==0 and self.thread_boost1.is_alive()):
            stop_thread(self.thread_boost1)
        elif(Way==1 and self.thread_boost2.is_alive()):
            stop_thread(self.thread_boost2)
        elif(Way==2 and self.thread_boost3.is_alive()):
            stop_thread(self.thread_boost3)
        path =os.getcwd()+'/bmp2jpeg/pic/'

        path2 =os.getcwd()+'/bmp2jpeg/frames-boost/'
        ##num = sum([os.path.isfile(path2+listx)for listx in os.listdir(path2)])
        image_file = './bmp2jpeg/pic/%d.bmp'%(n)
        image_file2 = './bmp2jpeg/frames-boost/%d.bmp'%(n)
        self.showcamera=QPixmap(image_file)
        self.showcamera2=QPixmap(image_file2)
        for filename in os.listdir(path2):
            ##print("yesyes")
            time.sleep(0.1)
            ###print("yesyesyse")
            image_file = path+filename
            image_file2 = path2+filename
            self.showcamera=QPixmap(image_file)
            self.showcamera2=QPixmap(image_file2)
            self.pic.setPixmap(self.showcamera)
            self.pic2.setPixmap(self.showcamera2)
            self.pic.repaint()
            self.pic2.repaint()
        try:
            self.checker.stop()
            self.loader.stop()
            sip.delete(self.checker)
            sip.delete(self.loader)
        except AttributeError:
            pass
        PID = 0
        Way=-1    
        self.progressBar_2.setValue(self.progressBar_2.maximum())
        msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","停止！\n"+outmsg)
        msg.exec_()
        sip.delete(self.pic)
        sip.delete(self.pic2)
        outmsg=""
        self.progressBar_2.setValue(0)

        
        ######JPEG#######
    def button_jpegnormal(self):
            '''JPEG图像处理，普通版'''
            global Way
            Way = 0
            self.pic = QtWidgets.QLabel(self.frame_16)
            self.pic.resize(self.frame_16.width(),self.frame_16.height())
            self.pic.setScaledContents(True)
            self.pic.show()

            self.thread_jpeg1 = threading.Thread(args=[1,],target = self.jpeg)
            self.thread_jpeg1.start()
            self.loader = QtCore.QTimer()
            self.loader.timeout.connect(lambda:  self.processbar_run(bar=self.progressBar_3))
            self.loader.start(10)
            self.checker = QtCore.QTimer()
            try:
                self.checker.timeout.connect(lambda:self.check_processbar(bar=self.progressBar_3,process=self.thread_jpeg1))
                self.checker.start(100)
            except AttributeError:
                self.checker.stop()
                self.loader.stop()
                sip.delete(self.checker)
                sip.delete(self.loader)
                self.progressBar_3.setValue(self.progressBar_3.maximum())
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
                msg.exec_()
                self.progressBar_3.setValue(0)
    def button_jpegpthread(self):
            '''JPGE图像处理，多线程版'''
            global Way
            Way = 1
            self.pic = QtWidgets.QLabel(self.frame_16)
            self.pic.resize(self.frame_16.width(),self.frame_16.height())
            self.pic.setScaledContents(True)
            self.pic.show()

            self.thread_jpeg2 = threading.Thread(args=[2,],target = self.jpeg)
            self.thread_jpeg2.start()
            self.loader = QtCore.QTimer()
            self.loader.timeout.connect(lambda:  self.processbar_run(bar=self.progressBar_3))
            self.loader.start(10)
            self.checker = QtCore.QTimer()
            try:
                self.checker.timeout.connect(lambda:self.check_processbar(bar=self.progressBar_3,process=self.thread_jpeg2))
                self.checker.start(100)
            except AttributeError:
                self.checker.stop()
                self.loader.stop()
                sip.delete(self.checker)
                sip.delete(self.loader)
                self.progressBar_3.setValue(self.progressBar_3.maximum())
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
                msg.exec_()
                self.progressBar_3.setValue(0)
    def button_jpegneon(self):
            '''JPEG图像处理，NEON加速版'''
            global Way
            Way = 2
            self.pic = QtWidgets.QLabel(self.frame_16)
            self.pic.resize(self.frame_16.width(),self.frame_16.height())
            self.pic.setScaledContents(True)
            self.pic.show()

            self.thread_jpeg3 = threading.Thread(args=[3,],target = self.jpeg)
            self.thread_jpeg3.start()
            self.loader = QtCore.QTimer()
            self.loader.timeout.connect(lambda:  self.processbar_run(bar=self.progressBar_3))
            self.loader.start(10)
            self.checker = QtCore.QTimer()
            try:
                self.checker.timeout.connect(lambda:self.check_processbar(bar=self.progressBar_3,process=self.thread_jpeg3))
                self.checker.start(100)
            except AttributeError:
                self.checker.stop()
                self.loader.stop()
                sip.delete(self.checker)
                sip.delete(self.loader)
                self.progressBar_3.setValue(self.progressBar_3.maximum())
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
                msg.exec_()
                self.progressBar_3.setValue(0)
    def button_jpegneon_pthread(self):
            '''JPEG图像处理，NEON+多线程版'''
            global Way
            Way = 3
            self.pic = QtWidgets.QLabel(self.frame_16)
            self.pic.resize(self.frame_16.width(),self.frame_16.height())
            self.pic.setScaledContents(True)
            self.pic.show()

            self.thread_jpeg4 = threading.Thread(args=[4,],target = self.jpeg)
            self.thread_jpeg4.start()
            self.loader = QtCore.QTimer()
            self.loader.timeout.connect(lambda:  self.processbar_run(bar=self.progressBar_3))
            self.loader.start(10)
            self.checker = QtCore.QTimer()
            try:
                self.checker.timeout.connect(lambda:self.check_processbar(bar=self.progressBar_3,process=self.thread_jpeg4))
                self.checker.start(100)
            except AttributeError:
                self.checker.stop()
                self.loader.stop()
                sip.delete(self.checker)
                sip.delete(self.loader)
                self.progressBar_3.setValue(self.progressBar_3.maximum())
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
                msg.exec_()
                self.progressBar_3.setValue(0)

    def jpeg(self,id):
            '''执行JPEG图像处理'''
            global Way,PID,Empty,outerr,outmsg,CMD
            CMD = True
            opt = 1
            n=1

            value = str(self.spinBox.value())+'\n'
            if (self.spinBox.value()==0):
                Empty = True
                return -1
            ##print(value)
            ##print(id)
            if(id==1):
                way = " --normal"
            elif(id==2):
                way = " --pthread"
            elif(id==3):
                way=""
                opt=3
            elif(id==4):
                way = " --neon_pthread"
                opt = 3
            cmd=cmd_template % (opt)#生成转换命令
            cmd =cmd+way
            cmd2 = "./control_toolkit/command"+str(id)+".bat"
            print(cmd)
            print(value)
            time_begin = time.perf_counter()
            p=subprocess.Popen(cmd,shell=True,stdin=subprocess.PIPE)
            p.stdin.write(value.encode())
            p.stdin.flush()
            p.stdin.close()
            while(1):
            ##print(subprocess.Popen.poll(popen));
                if(p.poll()!=None):
                ##print("ready")
                    break
            time.sleep(0.1)
            popen = subprocess.Popen(cmd2,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
            PID = popen.pid
            for error in iter(popen.stderr.readline,b''):
                if(error==''):
                    break
                else:
                    outerr+=error.decode()
            for line in iter(popen.stdout.readline,b''):
                if(line==''):
                    break
                else:
                    outmsg+=line.decode()
            popen.stdout.close()
            popen.stderr.close()
            while(1):
            ##print(subprocess.Popen.poll(popen));
                if(popen.poll()!=None):
                    break
            time_end=time.perf_counter()
            outmsg+="图像压缩,解压缩核心代码执行时间%.6f s\n"%(time_end-time_begin)
            ##print(outmsg)
            if(id==1):
                path =os.getcwd()+'/bmp2jpeg/frames-jpeg/'
            elif(id==2):
                path =os.getcwd()+'/bmp2jpeg/frames/'
            elif(id==3):
                path =os.getcwd()+'/bmp2jpeg-optimized/frames/'
            elif(id==4):
                path = os.getcwd()+"/bmp2jpeg-optimized/frames-jpeg/"
            else:
                print("error!!")
                exit(0)
            num = sum([os.path.isfile(path+listx)for listx in os.listdir(path)])
            image_file = path+'%d.bmp'%(n)
            self.showcamera=QPixmap(image_file)
            while(1):
                time.sleep(0.1)
                n+=1
                if(n>num):
                    break
                image_file = path+'%d.bmp'%(n)
                self.showcamera=QPixmap(image_file)
                self.pic.setPixmap(self.showcamera)
    def stop_jpeg(self):
        '''停止JPEG图像处理'''
        n=1
        global Way,PID,outerr,outmsg,CMD
        if(PID==0):
            return
        kill = "kill -9 "+str(PID)
        try:
            subprocess.Popen(kill,shell=True)
        except:
            pass
        if(Way==0 and self.thread_jpeg1.is_alive()):
            stop_thread(self.thread_jpeg1)
        elif(Way==1 and self.thread_jpeg2.is_alive()):
            stop_thread(self.thread_jpeg2)
        elif(Way==2 and self.thread_jpeg3.is_alive()):
            stop_thread(self.thread_jpeg3)
        elif(Way==3 and self.thread_jpeg3.is_alive()):
            stop_thread(self.thread_jpeg3)
        self.printcmd()
        path =os.getcwd()+'/bmp2jpeg/frames-jpeg/'
        if(Way==2 or Way==3):
            path =os.getcwd()+'/bmp2jpeg-optimized/frames/'
        num = sum([os.path.isfile(path+listx)for listx in os.listdir(path)])
        image_file = path+'%d.bmp'%(n)
        self.showcamera=QPixmap(image_file)
        try:
            self.checker.stop()
            self.loader.stop()
            sip.delete(self.checker)
            sip.delete(self.loader)
        except AttributeError:
            pass
        for filename in os.listdir(path):
            ##print("yesyes")
            time.sleep(0.1)
            n+=1
            ###print("yesyesyse")
            image_file = path+filename
            self.showcamera=QPixmap(image_file)
            self.pic.setPixmap(self.showcamera)
            ##self.pic.repaint()
            self.progressBar_3.setValue(self.progressBar_3.value()+5)


        PID = 0
        Way = -1    
        CMD=False
        self.progressBar_3.setValue(self.progressBar_3.maximum())
        msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","停止！")
        msg.exec_()
        sip.delete(self.pic)
        self.progressBar_3.setValue(0)
        outerr=''
        outmsg=''
        
        
        
        
        ####Compare####
    def button_cmp(self):
            '''性能对比按钮'''
            self.pic = QtWidgets.QLabel(self.frame_19)
            self.pic.resize(self.frame_19.width(),self.frame_19.height())
            self.pic.setScaledContents(True)
            self.pic.show()
            self.pic2 = QtWidgets.QLabel(self.frame_20)
            self.pic2.resize(self.frame_20.width(),self.frame_20.height())
            self.pic2.setScaledContents(True)
            self.pic2.show()
            self.thread_cmp = threading.Thread(target = self.cmp)
            self.thread_cmp.start()
            self.loader = QtCore.QTimer()
            self.loader.timeout.connect(lambda:  self.processbar_run(bar=self.progressBar_4))
            self.loader.start(10)
            self.checker = QtCore.QTimer()
            try:
                self.checker.timeout.connect(lambda:self.check_processbar(bar=self.progressBar_4,process=self.thread_cmp))
                self.checker.start(100)
            except AttributeError:
                self.checker.stop()
                self.loader.stop()
                sip.delete(self.checker)
                sip.delete(self.loader)
                self.progressBar_4.setValue(self.progressBar_4.maximum())
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
                msg.exec_()
                self.progressBar_4.setValue(0)
    def cmp(self):
                image_file = './bmp2jpeg-optimized/img/graph_0.png'
                image_file2 = './bmp2jpeg/img/graph_0.png'
                self.showcamera=QPixmap(image_file)
                self.showcamera2=QPixmap(image_file2)
                self.pic.setPixmap(self.showcamera)
                self.pic2.setPixmap(self.showcamera2)
            
    #######  Edit/AntiEdit #######
    def button_edit(self):
            '''图像自动篡改'''
            try:
                sip.delete(self.pic)
                sip.delete(self.pic2)
            except:
                pass
            self.pic = QtWidgets.QLabel(self.frame_22)
            self.pic.resize(self.frame_22.width(),self.frame_22.height())
            self.pic.setScaledContents(True)
            self.pic.show()
            self.pic2 = QtWidgets.QLabel(self.frame_23)
            self.pic2.resize(self.frame_23.width(),self.frame_23.height())
            self.pic2.setScaledContents(True)
            self.pic2.show()
            self.thread_edit = threading.Thread(target = self.edit)
            self.thread_edit.start()
            self.loader = QtCore.QTimer()
            self.loader.timeout.connect(lambda:  self.processbar_run(bar=self.progressBar_5))
            self.loader.start(10)
            self.checker = QtCore.QTimer()
            try:
                self.checker.timeout.connect(lambda:self.check_processbar(bar=self.progressBar_5,process=self.thread_edit))
                self.checker.start(100)
            except AttributeError:
                self.checker.stop()
                self.loader.stop()
                sip.delete(self.checker)
                sip.delete(self.loader)
                self.progressBar_5.setValue(self.progressBar_5.maximum())
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
                msg.exec_()
                self.progressBar_5.setValue(0)
    def edit(self):
        '''图像篡改执行'''
        global STYLE,FILENAME,EDIT

        EDIT=True
        filename = self.filename.text()
        if filename=="":
            FILENAME = False
            return 
        if(self.comboBox.currentIndex()==1):
            way = " rotate "
            cmd = "python3 ./control_toolkit/edit.py --style"+way+"--filename "+filename
        elif(self.comboBox.currentIndex()==2):
            way = " light "
            cmd = "python3 ./control_toolkit/edit.py --style"+way+"--filename "+filename
        elif(self.comboBox.currentIndex()==3):
            way=" flip "
            cmd = "python3 ./control_toolkit/edit.py --style"+way+"--filename "+filename
        elif(self.comboBox.currentIndex()==0):
            STYLE=False
            return
        ##print(cmd)
        p=subprocess.Popen(cmd,shell=True)
        while(1):
            ##print(subprocess.Popen.poll(popen));
            if(p.poll()!=None):
                ##print("ready")
                break
        path = "./antiedit/origin/"
        path2 = "./antiedit/from/"
        image_file = path+filename+".bmp"
        image_file2 = path2+filename+".jpg"
        self.showcamera=QPixmap(image_file)
        self.showcamera2=QPixmap(image_file2)
        self.pic.setPixmap(self.showcamera)
        self.pic2.setPixmap(self.showcamera2)
        
    def button_anti(self):
            '''图像篡改检测按钮'''
            try:
                sip.delete(self.pic)
                sip.delete(self.pic2)
            except:
                pass
            self.pic = QtWidgets.QLabel(self.frame_22)
            self.pic.resize(self.frame_22.width(),self.frame_22.height())
            self.pic.setScaledContents(True)
            self.pic.show()
            self.pic2 = QtWidgets.QLabel(self.frame_23)
            self.pic2.resize(self.frame_23.width(),self.frame_23.height())
            self.pic2.setScaledContents(True)
            self.pic2.show()
            self.thread_anti = threading.Thread(target = self.anti)
            self.thread_anti.start()
            self.loader = QtCore.QTimer()
            self.loader.timeout.connect(lambda:  self.processbar_run(bar=self.progressBar_5))
            self.loader.start(10)
            self.checker = QtCore.QTimer()
            try:
                self.checker.timeout.connect(lambda:self.check_processbar(bar=self.progressBar_5,process=self.thread_anti))
                self.checker.start(100)
            except AttributeError:
                self.checker.stop()
                self.loader.stop()
                sip.delete(self.checker)
                sip.delete(self.loader)
                self.progressBar_5.setValue(self.progressBar_5.maximum())
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
                msg.exec_()
                self.progressBar_5.setValue(0)
    def anti(self):
        '''图像篡改检测，执行代码'''
        global FILENAME,FINDEDIT
        filename = self.filename.text()
        if filename=="":
            FILENAME = False
            return 
        cmd = "./control_toolkit/antijpeg/control.bat"
        ##print(cmd)
        p=subprocess.Popen(cmd,shell=True,stdin=subprocess.PIPE,stdout=subprocess.PIPE)
        p.stdin.write((filename+"\n").encode())
        p.stdin.flush()
        p.stdin.close()
        for line in iter(p.stdout.readline,b''):
            if(line==''):
                break
            if(line.decode()=='1\n'):
                FINDEDIT=True
        p.stdout.close()
        while(1):
            ##print(subprocess.Popen.poll(popen));
            if(p.poll()!=None):
                ##print("ready")
                break
                
        path = "./antiedit/origin/"
        path2 = "./antiedit/result/"
        image_file = path+filename+".bmp"
        ##print(image_file)
        image_file2 = path2+"result"+".bmp"
        self.showcamera=QPixmap(image_file)
        self.showcamera2=QPixmap(image_file2)
        self.pic.setPixmap(self.showcamera)
        self.pic2.setPixmap(self.showcamera2)
        
        
        
        
            
            
            
        
        
        
        

        
        
        
        
        
        
    ########Processbar#######
    def processbar_run(self,bar):
        '''进度条运行'''
        mutex.acquire()
        if(bar.value()==bar.maximum()):
            bar.setValue(bar.maximum())
        if(bar.maximum()*0.9<=bar.value()<bar.maximum()):
            bar.setValue(bar.value())
            self.loader.stop()
        else:
            bar.setValue(bar.value()+2)
        mutex.release()
    def check_processbar(self,bar,process):
        '''检查进程是否结束，进度条是否结束'''
        global Empty,Way,PID,outerr,outmsg,CMD,BOOST,STYLE,FILENAME,EDIT,FINDEDIT,SECRET
        ##print("check")
        if not process.is_alive():
            if(SECRET):
                SECRET=False
                PID=0
                mutex.acquire()
                bar.setValue(bar.maximum())
                mutex.release()
                self.checker.stop()
                self.loader.stop()
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","加密存储完成！\n密文路径：./camera/encrypt\n明文路径：./camera/decrypt")
                msg.exec_()
                try:
                    sip.delete(self.pic)
                except:
                    pass
                bar.setValue(0)
                return 0
            if(FINDEDIT):
                FINDEDIT=False
                mutex.acquire()
                bar.setValue(bar.maximum())
                mutex.release()
                self.checker.stop()
                self.loader.stop()
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Critical,"Error","发现篡改！")
                msg.exec_()
                bar.setValue(0)
                return 0
                
            if(not FILENAME):
                FILENAME=True
                mutex.acquire()
                bar.setValue(bar.maximum())
                mutex.release()
                self.checker.stop()
                self.loader.stop()
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Critical,"Error","没有输入图片文件名！")
                msg.exec_()
                bar.setValue(0)
                return 0
            if(not STYLE):
                STYLE=True
                mutex.acquire()
                bar.setValue(bar.maximum())
                mutex.release()
                self.checker.stop()
                self.loader.stop()
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Critical,"Error","没有选择篡改方式！")
                msg.exec_()
                bar.setValue(0)
                return 0
            if(Empty):
                Empty = False
                mutex.acquire()
                bar.setValue(bar.maximum())
                mutex.release()
                self.checker.stop()
                self.loader.stop()
                msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Critical,"Error","输入图片数量为0！")
                msg.exec_()
                bar.setValue(0)
                return 0
            else:
                    mutex.acquire()
                    bar.setValue(bar.maximum())
                    mutex.release() 
                    self.checker.stop()
                    self.loader.stop()
                    Way = -1
                    PID = 0
                    
                    
                    if(CMD==True):
                        self.printcmd()
                    if(BOOST==True):
                        msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！\n"+outmsg)
                        msg.exec_()
                    else:
                        msg = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Information,"Information","完成！")
                        msg.exec_()
                    if(EDIT==True):
                        outerr = ''
                        outmsg = ''
                        bar.setValue(0)
                        CMD = False
                        BOOST = False
                        EDIT=False
                        return 0
                    try:
                        sip.delete(self.pic)
                        sip.delete(self.pic2)
                    except:
                        pass
                    outerr = ''
                    outmsg = ''
                    bar.setValue(0)
                    CMD = False
                    BOOST = False
    def printcmd(self):
        global outerr,outmsg
        self.plainTextEdit.appendPlainText(outerr)
        self.plainTextEdit.appendPlainText(outmsg)
        ##self.plainTextEdit.appendPlainText('\n')
    def clear(self):
        self.plainTextEdit.setPlainText("")
    def reset(self):
        try:
            sip.delete(self.pic)
            sip.delete(self.pic2)
        except:
            pass
import log_in_rc



