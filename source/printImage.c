#include <png.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <time.h>
#include <stdio.h>

#include "printImage.h"
#include "graphics.h"

Image* P_numbers;

void Print_Number(int PN_number, int PN_posx, int PN_posy, int PN_SL)
{
     if(PN_number<10)
     {
           if(PN_SL == 's' || PN_SL == 'S') Print_Number_Draw(PN_number, &PN_posx, &PN_posy);
           else if(PN_SL == 'l' || PN_SL == 'L') Print_Large_Number_Draw(PN_number, &PN_posx, &PN_posy);
     }
     else if(PN_number<100)
     {
           if(PN_SL == 's' || PN_SL == 'S') Print_Number_Draw(PN_number/10, &PN_posx, &PN_posy);
           else if(PN_SL == 'l' || PN_SL == 'L') Print_Large_Number_Draw(PN_number/10, &PN_posx, &PN_posy);
           if(PN_SL == 's' || PN_SL == 'S') Print_Number_Draw(PN_number%10, &PN_posx, &PN_posy);
           else if(PN_SL == 'l' || PN_SL == 'L') Print_Large_Number_Draw(PN_number%10, &PN_posx, &PN_posy);
     }
     else if(PN_number<1000)
     {
           if(PN_SL == 's' || PN_SL == 'S') Print_Number_Draw(PN_number/100, &PN_posx, &PN_posy);
           else if(PN_SL == 'l' || PN_SL == 'L') Print_Large_Number_Draw(PN_number/100, &PN_posx, &PN_posy);
           
           if(PN_SL == 's' || PN_SL == 'S') Print_Number_Draw(((PN_number-((PN_number/100)*100))/10), &PN_posx, &PN_posy);
           else if(PN_SL == 'l' || PN_SL == 'L') Print_Large_Number_Draw(((PN_number-((PN_number/100)*100))/10), &PN_posx, &PN_posy);
           
           if(PN_SL == 's' || PN_SL == 'S') Print_Number_Draw(PN_number%10, &PN_posx, &PN_posy);
           else if(PN_SL == 'l' || PN_SL == 'L') Print_Large_Number_Draw(PN_number%10, &PN_posx, &PN_posy);
     }
}
void Print_Number_Draw(int PND_number, int* PND_posx, int* PND_posy)
{
     switch(PND_number)
     {
           case 1:
                blitAlphaImageToScreen(0, 0, 3, 7, P_numbers, *PND_posx, *PND_posy);
                *PND_posx+=4;
                break;
           case 2:
                blitAlphaImageToScreen(3, 0, 7, 7, P_numbers, *PND_posx, *PND_posy);
                *PND_posx+=8;
                break;
           case 3:
                blitAlphaImageToScreen(10, 0, 7, 7, P_numbers, *PND_posx, *PND_posy);
                *PND_posx+=8;
                break;
           case 4:
                blitAlphaImageToScreen(17, 0, 8, 7, P_numbers, *PND_posx, *PND_posy);
                *PND_posx+=9;
                break;
           case 5:
                blitAlphaImageToScreen(25, 0, 7, 7, P_numbers, *PND_posx, *PND_posy);
                *PND_posx+=8;
                break;
           case 6:
                blitAlphaImageToScreen(32, 0, 7, 7, P_numbers, *PND_posx, *PND_posy);
                *PND_posx+=8;
                break;
           case 7:
                blitAlphaImageToScreen(39, 0, 8, 7, P_numbers, *PND_posx, *PND_posy);
                *PND_posx+=9;
                break;
           case 8:
                blitAlphaImageToScreen(47, 0, 7, 7, P_numbers, *PND_posx, *PND_posy);
                *PND_posx+=8;
                break;
           case 9:
                blitAlphaImageToScreen(54, 0, 7, 7, P_numbers, *PND_posx, *PND_posy);
                *PND_posx+=8;
                break;
           case 0:
                blitAlphaImageToScreen(61, 0, 7, 7, P_numbers, *PND_posx, *PND_posy);
                *PND_posx+=8;
                break;
           default:
                *PND_posx+=4;
                break;
     }
}
void Print_Large_Number_Draw(int PLND_number, int* PLND_posx, int* PLND_posy)
{
     switch(PLND_number)
     {
           case 1:
                blitAlphaImageToScreen(0, 7, 6, 14, P_numbers, *PLND_posx, *PLND_posy);
                *PLND_posx+=8;
                break;
           case 2:
                blitAlphaImageToScreen(6, 7, 14, 14, P_numbers, *PLND_posx, *PLND_posy);
                *PLND_posx+=16;
                break;
           case 3:
                blitAlphaImageToScreen(20, 7, 14, 14, P_numbers, *PLND_posx, *PLND_posy);
                *PLND_posx+=16;
                break;
           case 4:
                blitAlphaImageToScreen(34, 7, 16, 14, P_numbers, *PLND_posx, *PLND_posy);
                *PLND_posx+=18;
                break;
           case 5:
                blitAlphaImageToScreen(50, 7, 14, 14, P_numbers, *PLND_posx, *PLND_posy);
                *PLND_posx+=16;
                break;
           case 6:
                blitAlphaImageToScreen(64, 7, 14, 14, P_numbers, *PLND_posx, *PLND_posy);
                *PLND_posx+=16;
                break;
           case 7:
                blitAlphaImageToScreen(78, 7, 16, 14, P_numbers, *PLND_posx, *PLND_posy);
                *PLND_posx+=18;
                break;
           case 8:
                blitAlphaImageToScreen(94, 7, 14, 14, P_numbers, *PLND_posx, *PLND_posy);
                *PLND_posx+=16;
                break;
           case 9:
                blitAlphaImageToScreen(108, 7, 14, 14, P_numbers, *PLND_posx, *PLND_posy);
                *PLND_posx+=16;
                break;
           case 0:
                blitAlphaImageToScreen(122, 7, 14, 14, P_numbers, *PLND_posx, *PLND_posy);
                *PLND_posx+=16;
                break;
           default:
                *PLND_posx+=8;
                break;
     }
}
void Print_Number_Init()
{
     P_numbers = loadImage("numbers.png");
}
void Print_Number_End()
{
     freeImage(P_numbers);
}
Image* Print_Text_To_Image(char* PT_text, int PT_posx, int PT_posy, int PT_width, int PT_height)
{
     
     Image* P_text;
     Image* P_return_text;
     int PT_n=PT_posx+1;
     int PT_letter_width[2][38]={{7,7,7,7,7,7,7,7,5,7,7,7,7,7,7,7,7,7,7,7,7,6,8,7,7,7,7,3,7,7,8,7,7,8,7,7,2,2},
                              {0,7,14,21,28,35,42,49,56,61,68,75,82,89,96,103,110,117,124,131,138,145,151,159,166,173,180,187,190,197,204,212,219,226,234,241,248,250}};
     
     P_text = loadImage("letters.png");                         
     P_return_text = createImage(PT_width, PT_height);
     
     while(PT_n)
     {
           sceDisplayWaitVblankStart();
           if(*PT_text>96 && *PT_text<123)
           {
                 if((PT_posx+PT_letter_width[0][*PT_text-97])>PT_width)
                 {
                       PT_posy+=11;
                       PT_posx=PT_n-1;
                       if(PT_posy+7>PT_height)
                       {
                             PT_n=0;
                       }
                       else
                       {
                             blitAlphaImageToImage(PT_letter_width[1][*PT_text-97], 0, PT_letter_width[0][*PT_text-97], 7, P_text, PT_posx, PT_posy, P_return_text);
                             PT_posx = PT_posx+PT_letter_width[0][*PT_text-97]+1;
                       }
                 }
                 else 
                 {
                       blitAlphaImageToImage(PT_letter_width[1][*PT_text-97], 0, PT_letter_width[0][*PT_text-97], 7, P_text, PT_posx, PT_posy, P_return_text);
                       PT_posx = PT_posx+PT_letter_width[0][*PT_text-97]+1;
                 }
           }
           if(*PT_text>47 && *PT_text<58)
           {
                 if((PT_posx+PT_letter_width[0][*PT_text-22])>PT_width)
                 {
                       PT_posy+=11;
                       PT_posx=PT_n-1;
                       if(PT_posy+7>PT_height)
                       {
                             PT_n=0;
                       }
                       else
                       {
                             blitAlphaImageToImage(PT_letter_width[1][*PT_text-22], 0, PT_letter_width[0][*PT_text-22], 7, P_text, PT_posx, PT_posy, P_return_text);
                             PT_posx = PT_posx+PT_letter_width[0][*PT_text-22]+1;
                       }
                 }
                 else 
                 {
                       blitAlphaImageToImage(PT_letter_width[1][*PT_text-22], 0, PT_letter_width[0][*PT_text-22], 7, P_text, PT_posx, PT_posy, P_return_text);
                       PT_posx = PT_posx+PT_letter_width[0][*PT_text-22]+1;
                 }
           }
           else if(*PT_text==44)
           {
                if(PT_posx+PT_letter_width[0][36]>PT_width)
                 {
                       PT_posy+=11;
                       PT_posx=PT_n-1;
                       if(PT_posy+7>PT_height)
                       {
                             PT_n=0;
                       }
                       else
                       {
                             blitAlphaImageToImage(PT_letter_width[1][36], 0, PT_letter_width[0][36], 7, P_text, PT_posx, PT_posy+2, P_return_text);
                             PT_posx = PT_posx+PT_letter_width[0][36]+1;
                       }
                 }
                 else 
                 {
                       blitAlphaImageToImage(PT_letter_width[1][36], 0, PT_letter_width[0][36], 7, P_text, PT_posx, PT_posy+2, P_return_text);
                       PT_posx = PT_posx+PT_letter_width[0][36]+1;
                 }
           }
           else if(*PT_text==46)
           {
                if(PT_posx+PT_letter_width[0][37]>PT_width)
                 {
                       PT_posy+=11;
                       PT_posx=PT_n-1;
                       if(PT_posy+7>PT_height)
                       {
                             PT_n=0;
                       }
                       else
                       {
                             blitAlphaImageToImage(PT_letter_width[1][37], 0, PT_letter_width[0][37], 7, P_text, PT_posx, PT_posy+2, P_return_text);
                             PT_posx = PT_posx+PT_letter_width[0][37]+1;
                       }
                 }
                 else 
                 {
                       blitAlphaImageToImage(PT_letter_width[1][37], 0, PT_letter_width[0][37], 7, P_text, PT_posx, PT_posy+2, P_return_text);
                       PT_posx = PT_posx+PT_letter_width[0][37]+1;
                 }
           }
           else if(*PT_text==' ')
           {
                if(PT_posx+4<PT_width)
                {
                      PT_posx+=4;
                }
                else if(PT_posx>PT_n-1)
                {
                      PT_posy+=11;
                      PT_posx=PT_n-1;
                      if(PT_posy+7>PT_height)
                      {
                            PT_n=0;
                      }
                }
           }
           else if(*PT_text=='\n')
           {
                PT_posy+=11;
                PT_posx=PT_n-1;
                if(PT_posy+7>PT_height)
                       {
                             PT_n=0;
                       }
           }
           PT_text++;
           if(*PT_text=='\0')PT_n=0;
     }
     
     freeImage(P_text);
     return P_return_text;
}
