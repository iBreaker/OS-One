#
#	2014年12月25日21:00:09
#	V1.0 	By Breaker
#
#	文件名：Makefile
#	项目的 Makefile
#	
#

kernel.img:kernel.elf Makefile
	arm-none-eabi-objcopy kernel.elf -O binary kernel.img

kernel.elf:main.o gpio.o startup.o startup.s time.o pi.x Makefile
	arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g -Wl,-T,pi.x startup.s startup.o main.o gpio.o time.o -o kernel.elf

main.o:main.c Makefile
#2014年12月25日09:29:18
#这里之前是8个空格而不是Tab，导致编译出x64的程序，不能正常连接
	arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g -Wl,--verbose -c main.c -o main.o
	
gpio.o:gpio.c gpio.h Makefile
	arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g -Wl,--verbose -c gpio.c -o gpio.o
	
startup.o:startup.c Makefile
	arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g -Wl,--verbose -c startup.c -o startup.o

time.o:time.c time.h Makefile
	arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g -Wl,--verbose -c time.c -o time.o
	
clean:
	rm -f *.o  *.elf  *.img  *~

	

