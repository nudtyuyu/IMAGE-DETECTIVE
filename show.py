'''
* File name: show.py
* Author: Healer(Yu Hu)
* Author's blog: https://github.com/nudtyuyu
* Date: Aug 18th, 2022
* Description：This document realizes the login of the user interface and the jump between the Home screen, as well as the basic functions of the user interface such as dragging the window with the mouse
'''





from Login2 import *
from MainWindow import *
from PyQt5.QtWidgets import QApplication,QMainWindow,QMessageBox
import sys

class LoginWindow(QMainWindow):
	def __init__(self):
		super().__init__()
		self.ui = Ui_MainWindow()
		self.ui.setupUi(self)
		self.setWindowFlag(QtCore.Qt.FramelessWindowHint)
		self.setAttribute(QtCore.Qt.WA_TranslucentBackground)
		self.ui.pushButton.clicked.connect(self.go_to_MyApp)
		self.show()
		
	##go_to_myapp
	def go_to_MyApp(self):
		account = self.ui.username.text()
		password = self.ui.pwd.text()
		msg = QMessageBox(QMessageBox.Critical,"错误","用户名或密码错误!")
		msg_succ = QMessageBox(QMessageBox.Information,"消息","登录成功!")
		if account =="root" and password =="123456":
			msg_succ.exec_()
			MyApp()
			self.close()
		else:
			msg.exec_()
	
	##drag
	def mousePressEvent(self,event):
		if event.button() == QtCore.Qt.LeftButton and self.isMaximized()==False:
			self.m_flag = True
			self.m_Position = event.globalPos()-self.pos()
			event.accept()
			self.setCursor(QtGui.QCursor(QtCore.Qt.OpenHandCursor))
	def mouseMoveEvent(self,mouse_event):
		if QtCore.Qt.LeftButton and self.m_flag:
			self.move(mouse_event.globalPos()-self.m_Position)
			mouse_event.accept()
	def mouseReleaseEvent(self,mouse_event):
		self.m_flag = False
		self.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))

class MyApp(QMainWindow):
	def __init__(self):
		super().__init__()
		self.ui = Ui_MyApp()
		self.ui.setupUi(self)
		self.setWindowFlag(QtCore.Qt.FramelessWindowHint)
		self.setAttribute(QtCore.Qt.WA_TranslucentBackground)
		self.ui.pushButton_about.clicked.connect(lambda:self.ui.stackedWidget.setCurrentIndex(0))
		self.ui.pushButton_grap.clicked.connect(lambda:self.ui.stackedWidget.setCurrentIndex(1))
		self.ui.pushButton_boost.clicked.connect(lambda:self.ui.stackedWidget.setCurrentIndex(2))
		self.ui.pushButton_jpeg.clicked.connect(lambda:self.ui.stackedWidget.setCurrentIndex(3))
		self.ui.pushButton_cmp.clicked.connect(lambda:self.ui.stackedWidget.setCurrentIndex(4))
		self.ui.pushButton_anti.clicked.connect(lambda:self.ui.stackedWidget.setCurrentIndex(5))
		self.ui.pushButton_max.clicked.connect(self.resize_win)
		
		self.show()
	##resize
	def resize_win(self):
		if self.isMaximized():
			self.showNormal()
			self.ui.pushButton_max.setIcon(QtGui.QIcon(u":/icons/max.png"))
		else:
			self.showMaximized()
			self.ui.pushButton_max.setIcon(QtGui.QIcon(u":/icons/mini.png"))
	##drag
	def mousePressEvent(self,event):
		if event.button() == QtCore.Qt.LeftButton and self.isMaximized()==False:
			self.m_flag = True
			self.m_Position = event.globalPos()-self.pos()
			event.accept()
			self.setCursor(QtGui.QCursor(QtCore.Qt.OpenHandCursor))
	def mouseMoveEvent(self,mouse_event):
		if QtCore.Qt.LeftButton and self.m_flag:
			self.move(mouse_event.globalPos()-self.m_Position)
			mouse_event.accept()
	def mouseReleaseEvent(self,mouse_event):
		self.m_flag = False
		self.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))


if __name__ =="__main__":
	QtCore.QCoreApplication.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)
	app = QApplication(sys.argv)
	##win = LoginWindow()
	win = MyApp()
	sys.exit(app.exec_())
	
