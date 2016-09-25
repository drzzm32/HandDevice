#include "util.h"
#include "KeyDef.h"

uint8_t key, prev, i;
bit brust = 0;

void main() {
	portInit();
	serialInit();
	
	write("NSDN-Keypad v1.0\n");
	
	while (1) {
		key = (char)scanKey();
		if (key == KeyCL) {
			while (key == KeyCL)
				key = (char)scanKey();
			CapsLock = ~CapsLock;
			CLPOS = CapsLock;
		} else if (key == KeyCt) {
		
		} else if (key == KeyAl) {
		
		} else if (key == KeyEsc) {
		
		} else if (key != 0xFF) {
			if (key == prev && !brust) {
				for (i = 0; i < 10; i++) {
					delay(2);
					key = (char)scanKey();
					if (key != prev) goto END;
				}
				brust = 1;
				END:
				_nop_();
			}
			prev = key;
			if (key >= 'A' && key <= 'Z' && !CapsLock) key += 32;
			if (key != 0xFF) send(key);
			key = 0xFF;
			delay(2);
		} else {
			brust = 0;
			prev = 0;
		}
	}
}