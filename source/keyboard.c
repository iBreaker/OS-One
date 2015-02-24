// void KeyboardUpdate();

#include "keyboard.h"
#include "Graphic.h"

void LogPrint(const char* message, u32 messageLength)
{
	char * MSG = (char * ) message;
	os_printf(MSG);
	os_printf("%n");
}
 
