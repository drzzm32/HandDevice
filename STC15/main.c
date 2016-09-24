#include "util.h"
#include "KeyDef.h"

uint8_t key, prev;
bit brust = 0;

void main() {
	portInit();
	serialInit();
	
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
		
		} else if (0) {
			if (key == prev && !brust) {
				delay(20);
				brust = 1;
				key = (char)scanKey();
			} else if (key != prev) {
				brust = 0;
			}
			if (key >= 'A' && key <= 'Z' && !CapsLock) key += 32;
			send(key);
			prev = key;
			key = 0xFF;
			delay(2);
		} else if (key != 0xFF) {
			if (key >= 'A' && key <= 'Z' && !CapsLock) key += 32;
			send(key);
			key = 0xFF;
			delay(10);
		} else {
			brust = 0;
		}
	}
}