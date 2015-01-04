
/* keyboard.s */
unsigned int KeyboardAddress;
unsigned short* KeyboardOldDown;
char* KeysNoShift;
char* KeysShift;

void KeyboardUpdate();
char KeyWasDown(unsigned short  scanCode);
char KeyboardGetChar();

/* libcsud.a */
/** 
	\brief The current state of keyboard modifier keys.

	Encapsulates the current state of the keyboard modifier keys. Strucutre 
	mimics the most common keyboard ordering.
*/
struct KeyboardModifiers {
	char LeftControl : 1; // @0
	char LeftShift : 1; // @1
	char LeftAlt : 1; // @2
	char LeftGui : 1; // the 'windows' key @3
	char RightControl : 1;  // @4
	char RightShift : 1; // @5
	char RightAlt : 1; // 'alt gr' @6
	char RightGui : 1; // @7
} __attribute__ ((__packed__));

unsigned int  UsbInitialise(void);
void UsbCheckForChange();
unsigned int KeyboardCount();
unsigned int KeyboardGetAddress(unsigned int   index);
unsigned int KeyboardPoll(unsigned int   keyboardAddress);
struct KeyboardModifiers KeyboardGetModifiers(unsigned int keyboardAddress);
unsigned int KeyboardGetKeyDownCount(unsigned int keyboardAddress);


