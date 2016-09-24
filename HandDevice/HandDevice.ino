#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include "Color.h"
Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCRIPT_MAX_LENGTH 128
#define TYPE_CONSOLE 0
#define TYPE_EXPLAIN 1

#define CLS_SCREEN "clear"
#define THIS_VERSION "ver0.05 (Embedded Repo)"

double numBuf;
char* strBuf;
char* codeBuf;
char* scpBuf;
char* scpHead;
char* scpBody;
char* strPtr;
int lines = 1;
int jmpFlag = 0;


void readln(char* str) {
    uint8_t i = 0;
    while (true) {
        if (Serial.available() > 0) {
            if (Serial.peek() == '\n') break;
            str[i] = Serial.read();
            tft.print(str[i]);
            i += 1;
        }
    }
    str[i] = '\0';
    Serial.read();
    tft.println();
}

void clear() {
    tft.setCursor(0, 0);
    tft.fillScreen(0x0000);
}

void encode(char* source, char* code) {
    int i = 0, j = 0, flag = 1;
    while (1) {
        strBuf[i] = source[i] + code[j];
        if (source[i + 1] == '\0') break;
        i += 1;
        if (code[j + 1] == '\0') flag = -flag;
        else if (j < 0) flag = -flag;
        j += flag;
    }
    strBuf[i + 1] = '\0';
}

void decode(char* source, char* code) {
    int i = 0, j = 0, flag = 1;
    while (1) {
        strBuf[i] = source[i] - code[j];
        if (source[i + 1] == '\0') break;
        i += 1;
        if (code[j + 1] == '\0') flag = -flag;
        else if (j < 0) flag = -flag;
        j += flag;  
    }
    strBuf[i + 1] = '\0';
}

int execute(char* script, int type) {
    sscanf(script, "%s %[^\n]", scpHead, scpBody);
    if (strcmp(scpHead, "print") == 0) {
        if (strcmp(scpBody, "_ver_") == 0) {
            tft.print(THIS_VERSION);
        } else if (strcmp(scpBody, "_mem_") == 0) {
            tft.print(numBuf);
        } else if (strcmp(scpBody, "_smem_") == 0) {
            tft.print(strBuf);
        } else if (strcmp(scpBody, "_code_") == 0) {
            tft.print(codeBuf);
        } else {
            tft.print(scpBody);
        }
        if (type == TYPE_CONSOLE) tft.print("\n");
    } else if (strcmp(scpHead, "println") == 0) {
        if (strcmp(scpBody, "_ver_") == 0) {
            tft.println(THIS_VERSION);
        } else if (strcmp(scpBody, "_mem_") == 0) {
            tft.println(numBuf);
        } else if (strcmp(scpBody, "_smem_") == 0) {
            tft.println(strBuf);
        } else if (strcmp(scpBody, "_code_") == 0) {
            tft.println(codeBuf);
        } else {
            tft.println(scpBody);
        }
    } else if (strcmp(scpHead, "version") == 0 || strcmp(scpHead, "ver") == 0) {
        tft.print("Scripter version: ");
        tft.println(THIS_VERSION);
    } else if (strcmp(scpHead, CLS_SCREEN) == 0) {
        clear();
    } 
    
    else if (strcmp(scpHead, "encode") == 0) {
        if (strcmp(scpBody, "_smem_") == 0) {
            encode(strBuf, codeBuf);
        } else {
            encode(scpBody, codeBuf);
        }
    } else if (strcmp(scpHead, "decode") == 0) {
        if (strcmp(scpBody, "_smem_") == 0) {
            decode(strBuf, codeBuf);
        } else {
            decode(scpBody, codeBuf);
        }
    } else if (strcmp(scpHead, "puts") == 0) {
        strcpy(strBuf, scpBody);
    } else if (strcmp(scpHead, "putc") == 0) {
        strcpy(codeBuf, scpBody);
    }
    
    else if (strcmp(scpHead, "put") == 0) {
        numBuf = atof(scpBody);
    } else if (strcmp(scpHead, "op+") == 0) {
        numBuf = numBuf + atof(scpBody);
    } else if (strcmp(scpHead, "op-") == 0) {
        numBuf = numBuf - atof(scpBody);
    } else if (strcmp(scpHead, "op*") == 0) {
        numBuf = numBuf * atof(scpBody);
    } else if (strcmp(scpHead, "op/") == 0) {
        numBuf = numBuf / atof(scpBody);
    }

    else if (strcmp(scpHead, "when") == 0) {
        if (strcmp(scpBody, "_mem_") == 0) {
            if (numBuf <= 0) jmpFlag = 1;
        } else {
            if (atof(scpBody) <= 0) jmpFlag = 1;
        }
    }

    else if (strcmp(scpHead, "run") == 0) {
        tft.println("Under construction...");
    }
    
    else if (strcmp(scpHead, "exit") == 0) {
        if (strcmp(scpBody, "this") == 0) {
            return 0;
        } else {
            return 1;
        }
    }

    else if (strcmp(scpHead, "reset") == 0) {
        if (strcmp(scpBody, "2") == 0) {
            tft.setTextSize(2);
        } else if (strcmp(scpBody, "3") == 0) {
            tft.setTextSize(3);
        } else {
            tft.setTextSize(1);
        }
        return 0;
    }
    
    else {
        tft.print("Syntax error, in line ");
        tft.print(lines);
        tft.print(" ");
        tft.print(scpHead);
        tft.print(" ");
        tft.println(scpBody);
        tft.println("Script aborted.");
        return type == TYPE_CONSOLE ? 1 : (type == TYPE_EXPLAIN ? 0 : 1);
    }
    return 1;
}

void cliBuild() {
    tft.println("================================");
    tft.print("Scripter ");
    tft.println(THIS_VERSION);
    tft.println("================================");
    tft.println("Usage: Serial Port 0\n\n");
    while (1) {
        tft.print(lines);
        tft.print(" >>> ");
        readln(scpBuf);
        if (jmpFlag) {
            jmpFlag = 0;
            lines++;
            continue;
        }
        if (!execute(scpBuf, TYPE_CONSOLE))
            break;
        lines++;
    }
}

int scripter() {
    scpBuf = (char* )malloc(sizeof(char) * SCRIPT_MAX_LENGTH);
    strcpy(scpBuf, "_null_");
    scpHead = (char* )malloc(sizeof(char) * SCRIPT_MAX_LENGTH);
    strcpy(scpHead, "_null_");
    scpBody = (char* )malloc(sizeof(char) * SCRIPT_MAX_LENGTH);
    strcpy(scpBody, "_null_");
    
    strBuf = (char* )malloc(sizeof(char) * SCRIPT_MAX_LENGTH);
    strcpy(strBuf, "_null_");
    codeBuf = (char* )malloc(sizeof(char) * SCRIPT_MAX_LENGTH);
    strcpy(codeBuf, "_null_");

    lines = 1;
    jmpFlag = 0;

    clear();
    cliBuild();

    free(strBuf);
    free(codeBuf);
    free(scpBuf);
    free(scpHead);
    free(scpBody);

    return 0;
}

void setup() {
    tft.reset();
    delay(10);
    tft.begin(tft.readID());
    tft.setRotation(3);
    tft.setCursor(0, 0);
    tft.setTextColor(0xFFFF);
    tft.setTextSize(1);
    tft.fillScreen(0x0000);

    Serial.begin(9600);
}

void loop() {
    scripter();
}
