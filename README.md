# OS One

一个自制的树莓派操作系统，OS One 这个名字来自于电影 《Her》。

## 特性

1. 提供 GPIO 处理函数；
2. GUI 界面，有窗体 demo， 窗体可对鼠标操作做出相应；
3. 默认分辨率 1440×900；
4. 可显示 bmp 24 位色（true color）图片；
5. 支持鼠标键盘输入设备；
6. 多任务，默认最多 16 个任务；
7. 时间片轮转调度；
8. 任务间通信；
9. 任务阻塞，挂起；
10. 支持动态申请内存；
11. 系统最多支持 255 个 timer 定时器；
12. 支持 UART 通信。

## 编译

**硬件**：Raspberry Pi B+ （其他版本树莓派没有测试）  
**Host**：Linux version 3.13.0-44-generic (buildd@lamiak) #73-Ubuntu SMP Tue Dec 16 00:22:43 UTC 2014  
**工具链**：`arm-none-eabi-` V4.8.2

### kernel.img

`make` = `make kernel.img` -编译最终产生的 kernel.img  
`make clean`               -清理项目     
`make install`             -将 kernel.img 复制到 SD 卡，复制之前确认请修改 Makefile 里的设备名称和路径  

### minocom for OS One

树莓派输入设备（鼠标键盘）用串口通信，所以必须运行串口程序。   
先 `make`，然后 `make install` <千万不要`./configure` !!!>。
 
## 使用

1. 接上树莓派串口线，两个 LED 灯分别连接到 GPIO16 和 GPIO19。这两个等会显示内核状态信息（不接这两个 LED 不影响系统运行）；
2. 编译运行 minocom for OS One；
3. 编译 kernel.img 并复制到 SD 卡，覆盖原来的 kernel.img (原来的 kernel.img 要备份)；
4. 加电运行；
5. 可以试着移动鼠标，拖动窗口；
6. 屏幕左上角显示 Task1 和 Task2 的通信状态；
7. 屏幕右上角显示四个 Timer 的状态；
8. 窗口显示 kernel status。分别有任务栈适用情况，鼠标键盘状态，空闲堆内存大小；
9. 可以试着按键，窗口上 input status 中的 key 会显示按键的 ASCII 码；
10. 移动鼠标，单机右击窗口都有显示。

## 已知漏洞

暂无。

## 参考资料

1. 《操作系统设计 Xinu 方法》
2. 《30 天自制操作系统》
3. 《嵌入式实时操作系统 uc/os III》
4. 《linux 内核设计的艺术》
5. 《Linux 0.01 内核分析与操作系统设计》  

**项目主页**：[OS One 主页](http://os.0x7c00.cn)  
**GitHub（国外）**：[https://github.com/iBreaker/OS-ONE.git](https://github.com/iBreaker/OS-ONE.git)  
**Coding（国内）**：[https://coding.net/breaker/OS-ONE.git](https://coding.net/breaker/OS-ONE.git)   

Breaker   
791628659@qq.com  
2015-03-12 15:05:14


## 效果预览

* 下面的是树莓派，没有写好显示驱动的时候就用那个灯调试。因为树莓派的输出只有这个灯，通过这个灯的亮灭来判断要被调试的某个值的大小。树莓派通过 HDMI 线和显示器连接。开发环境 backtrack5：

![https://pic.0x7c00.cn/OS-One/1.jpg](https://pic.0x7c00.cn/OS-One/1.jpg)

* 实现简单的 UI 库后，做出的一个 360 风格的窗口：

![https://pic.0x7c00.cn/OS-One/1.jpg](https://pic.0x7c00.cn/OS-One/2.jpg)

* 简单的进程管理器，显示当前多进程的信息，以及内存和鼠标键盘的状态：

![https://pic.0x7c00.cn/OS-One/1.jpg](https://pic.0x7c00.cn/OS-One/3.jpg)

* 同上：
![https://pic.0x7c00.cn/OS-One/1.jpg](https://pic.0x7c00.cn/OS-One/4.jpg)

* 同上，秀一秀鼠标箭头：

![https://pic.0x7c00.cn/OS-One/1.jpg](https://pic.0x7c00.cn/OS-One/5.jpg)

