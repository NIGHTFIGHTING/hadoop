#!/usr/bin/python
# -*- coding: UTF-8 -*-
# 文件名：client.py
 
import socket               # 导入 socket 模块
import os
 
def get_pid(job_info):
    s = socket.socket()         # 创建 socket 对象
    host = socket.gethostname() # 获取本地主机名
    port = 12345                # 设置端口号
     
    s.connect(("127.0.0.1", 8888))
    #print s.recv(1024)
    s.send(str(os.getpid()) + " " + job_info +  str("\n"))
    s.close()
