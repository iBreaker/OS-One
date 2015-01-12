##############################
#	2014年12月25日21:00:09
#	V1.0 	By Breaker
#
#	文件名：Makefile
#	项目的 Makefile
#
##############################
#	2015年01月05日11:58:29    
#	V2.0 	By Breaker 
#	增加include文件夹和source 等文件夹，libcsud.a
#	整理项目结构

#默认参数
DIR_SRC ?= ./source
DIR_INC ?= ./include
DIR_OBJ ?= ./object
DIR_LIB ?= ./lib

TARGET ?= kernel
#
#（1）Makefile中的 符号 $@, $^, $< 的意思：
#　　$@  表示目标文件
#　　$^  表示所有的依赖文件
#　　$<  表示第一个依赖文件
#　　$?  表示比目标还要新的依赖文件列表
#
#（2）wildcard、notdir、patsubst的意思：
#
#　　wildcard : 扩展通配符
#　　notdir ： 去除路径
#　　patsubst ：替换通配符

GNU = arm-none-eabi-
CFLAGS +=  -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s \
			-nostartfiles -fshort-wchar  -g -Wl,--verbose -c -I ${DIR_INC} 
LFLAGS +=   -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s \
			-nostartfiles  -fshort-wchar  -g -Wl,-T,${DIR_SRC}/pi.x 
objects = startup.o main.o gpio.o time.o GPU.o GPUS.o Graphic.o Global.o GlobalS.o debug.o  keyboardS.o 

SRC = $(wildcard  ${DIR_SRC}/*.c)
ASB = $(wildcard  ${DIR_SRC}/*.s)
OBJ = $(patsubst  %.c,${DIR_OBJ}/%.o,$(notdir ${SRC}))
LIB = $(notdir $(wildcard ${DIR_LIB}/*.a))
INC = $(wildcard ${DIR_INC}/*.h)

default:
	clear
	make kernel.img
	make clean
	
${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	${GNU}gcc ${CFLAGS} -c $< -o $@
	
${TARGET}.img: ${TARGET}.elf
	${GNU}objcopy  ${TARGET}.elf -O binary $@

${TARGET}.elf:${OBJ}  ${DIR_LIB}/${LIB} ${ASB} ${DIR_SRC}/pi.x  
	@echo ${OBJ}   ${LIB} ${ASB}  ${SRC} ${GNU}
	${GNU}gcc ${LFLAGS} ${OBJ} ${ASB} -L ${DIR_LIB}  -l csud -o ${TARGET}.elf
	
disasm:${TARGET}.elf
	${GNU}objdump -S  $< > ${TARGET}.disasm
clean:
	rm -rf  ./object/*.o
	rm -rf *.img *.elf *.disasm

install:
	make kernel.img
	sudo mount /dev/sde1  /media/breaker/boot/
	rm -f  /media/breaker/boot/kernel.img
	cp kernel.img /media/breaker/boot/kernel.img
	umount /dev/sde1
	make clean
	

