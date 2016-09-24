#include "util.h"
#include "KeyDef.h"

uint8_t tmp;

void main() {
	portInit();
	serialInit();
	
	while (1) {
		tmp = (char)scanKey();
		if (tmp != 0xFF) {
			send(tmp);
			tmp = 0xFF;
			delay(10);
		}
	}
}