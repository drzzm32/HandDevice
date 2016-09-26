#include "STC15.h"
#include <intrins.h>

#ifndef __UTIL_H_
#define __UTIL_H_

#define uint8_t unsigned char
	
#define CLPOS P25
#define CLNEG P26
static bit CapsLock = 0;
static bit Ctrl = 0;
static bit Alt = 0;
static bit Caps = 0;

static bit BUSY = 0;
static uint8_t DATA;

void portInit() {
	P1M0 = 0;		P1M1 = 0;
	P2M0 = 0x20;	P2M1 = 0;
	P3M0 = 0;		P3M1 = 0;
	
	CLNEG = 0;		CLPOS = 0;
}

void serialInit() {
	/*24MHz@9600bps*/
	SCON = 0x50;
	T2L = 0x8F;
	T2H = 0xFD;
	AUXR = 0x14;
    AUXR |= 0x01;
    ES = 1;      
    EA = 1;
}

void serialInterrupt() interrupt 4 using 1 {
	if (RI) {
        RI = 0;
        DATA = SBUF;
    }
	if (TI) {
        TI = 0;
        BUSY = 0;
    }
}

void send(uint8_t value) {
	while (BUSY);
	BUSY = 1;
	SBUF = value;
}

void write(char* str) {
	while (*str) send(*str++);
}

void delay(unsigned short time)
{
	unsigned char i, j;
	unsigned short t;
	i = 24;
	j = 85;
	t = time;
	do {
		do {
			while (--j) _nop_();
		} while (--i);
	} while (--t);
}

#endif