
kernel.img:kernel.elf
	arm-none-eabi-objcopy kernel.elf -O binary kernel.img

kernel.elf:main.o gpio.o Makefile
	arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles main.o gpio.o -o kernel.elf

main.o:main.c Makefile
#2014年12月25日09:29:18
#这里之前是8个空格而不是Tab，导致编译出x64的程序，不能正常连接
	arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -c main.c -o main.o
	
gpio.o:gpio.c gpio.h Makefile
	arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -c gpio.c -o gpio.o
	

	
clean:
	rm -f *.o  *.elf  *.img  *~

	

