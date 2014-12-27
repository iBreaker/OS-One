.section .data
.align 4
.globl FrameBufferInfo		/*2014年12月27日21:01:11 这里复制的时候有一个不可见字符，导致链接的时候找不到FrameBufferInfo标号。找了两个小时*/
FrameBufferInfo:
.int 1024 	/* #0 Physical Width */
.int 768 	/* #4 Physical Height */
.int 1024 	/* #8 Virtual Width */
.int 768 	/* #12 Virtual Height */
.int 0 		/* #16 GPU - Pitch */
.int 16 	/* #20 Bit Depth */
.int 0 		/* #24 X */
.int 0 		/* #28 Y */
.int 0 		/* #32 GPU - Pointer */
.int 0 		/* #36 GPU - Size */


