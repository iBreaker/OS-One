OS One
========

一个自制的树莓派操作系统, OS one 这个名字来自于电影 《Her》

## 特性: 
1. 提供GPIO处理函数.
2. GUI界面，有窗体demo， 窗体可对鼠标操作做出相应.
3. 默认分辨率 1440 × 900 .
4. 可显示bmp 24位色（true color）图片.
5. 支持鼠标键盘输入设备.
6. 多任务，默认最多16个任务.
7. 时间片轮转调度.
8.  任务间通信
9.  任务阻塞， 挂起
10. 支持动态申请内存.
11. 系统最多支持255个timer定时器
12. 支持UART通信

## 编译:

**硬件**： Raspberry Pi B+ （其他版本树莓派没有测试）  
**Host** :   Linux version 3.13.0-44-generic (buildd@lamiak) #73-Ubuntu SMP Tue Dec 16 00:22:43 UTC 2014  
**工具链**：`arm-none-eabi-`         V4.8.2

###kernel.img   
`make` = `make kernel.img`        -编译最终产生的 kernel.img  
`make clean`                               -清理项目     
`make install`    -将kernel.img 复制到sd卡， 复制之前确认请修改Makefile里的设备名称和路径  

###minocom for OS One
树莓派输入设备（鼠标键盘）用串口通信，所以必须运行串口程序   
先`make`，然后`make install`  <千万不要`./configure` !!!>
 
## 使用:
1. 接上树莓派串口线， 两个LED灯分别连接到GPIO16和GPIO19。这两个等会显示内核状态信息（不接这两个LED不影响系统运行）  
2.  编译运行 minocom for OS One ，
3.  编译kernel.img 并复制到sd卡，覆盖原来的kernel.img (原来的kernel.img 要备份)
4.  加电运行
5.  可以试着移动鼠标，拖动窗口
6.  屏幕左上角显示Task1 和 Task2 的通信状态
7.  屏幕右上角显示四个Timer的状态
8.  窗口显示kernel status 。 分别有任务栈适用情况，鼠标键盘状态，空闲堆内存大小
9.  可以试着按键， 窗口上input status 中的key 会显示按键的ASCII码
10.  移动鼠标, 单机右击窗口都有显示

## 已知漏洞: 


##参考资料
1.  《操作系统设计 Xinu方法》
2.  《30天自制操作系统》
3.  《嵌入式实时操作系统uc/os III》
4.  《linux内核设计的艺术》
5.  《Linux 0.01内和分析与操作系统设计》  

**项目主页**：[OS One主页](http://os.0x7c00.cn)  
**github地址** :  
**coding地址**：  

Breaker   
791628659@qq.com  
2015-03-12 15:05:14
