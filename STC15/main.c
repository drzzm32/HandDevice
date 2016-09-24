#include "util.h"
#include "KeyDef.h"

uint8_t tmp;

void main() {
	portInit();
	serialInit();
	
	while (1) {
		tmp = (char)scanKey();
		if (tmp == KeyCL) {
			while (tmp == KeyCL)
				tmp = (char)scanKey();
			CapsLock = ~CapsLock;
			CLPOS = CapsLock;
		} else if (tmp == KeyCt) {
		
		} else if (tmp == KeyAl) {
		
		} else if (tmp == KeyEsc) {
		
		} else if (tmp != 0xFF) {
			if (tmp >= 'A' && tmp <= 'Z' && !CapsLock) tmp += 32;
			send(tmp);
			tmp = 0xFF;
			delay(10);
		}
	}
}