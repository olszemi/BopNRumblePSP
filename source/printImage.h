#ifndef PRINTIMAGE_H
#define PRINTIMAGE_H

#include "graphics.h"

extern void Print_Number(int PN_number, int PN_posx, int PN_posy, int PN_SL);
extern void Print_Number_Init(void);
extern void Print_Number_End(void);
extern Image* Print_Text_To_Image(char* PT_text, int PT_posx, int PT_posy, int PT_width, int PT_height);
void Print_Large_Number_Draw(int PLND_number, int* PLND_posx, int* PLND_posy);
void Print_Number_Draw(int PND_number, int* PND_posx, int* PND_posy);

#endif
