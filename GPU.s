/******************************************************************************
*	frameBuffer.s
*	 by Alex Chadwick
*
*	A sample assembly code implementation of the screen01 operating system.
*	See main.s for details.
*
*	frameBuffer.s contains code that creates and manipulates the frame buffer.
******************************************************************************/

/* NEW
* When communicating with the graphics card about frame buffers, a message 
* consists of a pointer to the structure below. The comments explain what each
* member of the structure is.
* The .align 12 is necessary to ensure correct communication with the GPU, 
* which expects page alignment.
* C++ Signature: 
* struct FrameBuferDescription {
*  u32 width; u32 height; u32 vWidth; u32 vHeight; u32 pitch; u32 bitDepth;
*  u32 x; u32 y; void* pointer; u32 size;
* };
* FrameBuferDescription FrameBufferInfo =
*		{ 1024, 768, 1024, 768, 0, 16, 0, 0, 0, 0 };
*/
.section .data
.align 12
.globl FrameBufferInfo 
FrameBufferInfo:
	.int 1024	/* #0 Width */
	.int 768	/* #4 Height */
	.int 1024	/* #8 vWidth */
	.int 768	/* #12 vHeight */
	.int 0		/* #16 GPU - Pitch */
	.int 16		/* #20 Bit Dpeth */
	.int 0		/* #24 X */
	.int 0		/* #28 Y */
	.int 0		/* #32 GPU - Pointer */
	.int 0		/* #36 GPU - Size */


