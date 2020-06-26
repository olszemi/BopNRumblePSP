#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <png.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <time.h>
#include <stdio.h>

#include "keys.h"
#include "enum.h"

SceCtrlData pad; 
short start=0, select=0, left=0, up=0, right=0, down=0, square=0, triangle=0, circle=0, cross=0, ltrigger=0, rtrigger=0, note=0, screen=0, voldown=0, volup=0;
int keys[12] = {0,2,3,0,0,0,0,0,0,0,0,0};

void keys_Default(void)
{
       keys[0] = 0;
       keys[1] = 2;
       keys[2] = 3;
       keys[3] = 0;
       keys[4] = 0;
       keys[5] = 0;
       keys[6] = 0;
       keys[7] = 0;
       keys[8] = 0;
       keys[9] = 0;
       keys[10] = 0;
       keys[11] = 0;
}
void K_set_keys(int tab[12])
{
       keys[0]=tab[0];
       keys[1]=tab[1];
       keys[2]=tab[2];
       keys[3]=tab[3];
       keys[4]=tab[4];
       keys[5]=tab[5];
       keys[6]=tab[6];
       keys[7]=tab[7];
       keys[8]=tab[8];
       keys[9]=tab[9];
       keys[10]=tab[10];
       keys[11]=tab[11];
}
int* K_get_keys(void)
{
       return keys;
}
int key(void)
{   
    //////////////Naciœniêcie przycisku//////////////
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_SELECT)
                         return SELECT;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_START)
                         return START;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_LEFT)
                         return LEFT;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_UP)
                         return UP;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_RIGHT)
                         return RIGHT;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_DOWN)
                         return DOWN;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_SQUARE)
                         return SQUARE;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_TRIANGLE)
                         return TRIANGLE;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_CIRCLE)
                         return CIRCLE;
          sceCtrlPeekBufferPositive(&pad, 1);
           if(pad.Buttons & PSP_CTRL_CROSS)
                          return CROSS;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_LTRIGGER)
                         return LTRIGGER;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_RTRIGGER)
                         return RTRIGGER;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_NOTE)
                         return NOTE;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_SCREEN)
                         return SCREEN;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_VOLUP)
                         return VOLUP;
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_VOLDOWN)
                         return VOLDOWN;
          return 0;
}
int keyDown(void)
{ 
    keyUp();
    //////////////Naciœniêcie przycisku//////////////
          if(select==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_SELECT)
          {
                  select=1;
                  return SELECT;
          }
          }
          if(start==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_START)
          {
                         start=1;
                         return START;
          }
          }
          if(left==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_LEFT)
          {
                         left=1;
                         return LEFT;
          }
          }
          if(up==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_UP)
          {
                         up=1;
                         return UP;
          }
          }
          if(right==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_RIGHT)
          {
                         right=1;
                         return RIGHT;
          }
          }
          if(down==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_DOWN)
          {
                         down=1;
                         return DOWN;
          }
          }
          if(square==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_SQUARE)
          {
                         square=1;
                         return SQUARE;
          }
          }
          if(triangle==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_TRIANGLE)
          {
                         triangle=1;
                         return TRIANGLE;
          }
          }
          if(circle==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_CIRCLE)
          { 
                         circle=1;
                         return CIRCLE;
          }
          }
          if(cross==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
           if(pad.Buttons & PSP_CTRL_CROSS)
          { 
                          cross=1;
                          return CROSS;
          }
          }
          if(ltrigger==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_LTRIGGER)
          {
                         ltrigger=1;
                         return LTRIGGER;
          }
          }
          if(rtrigger==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_RTRIGGER)
          {
                         rtrigger=1;
                         return RTRIGGER;
          }
          }
          if(note==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_NOTE)
          {
                         note=1;
                         return NOTE;
          }
          }
          if(screen==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_SCREEN)
          {
                         screen=1;
                         return SCREEN;
          }
          }
          if(volup==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_VOLUP)
          {
                         volup=1;
                         return VOLUP;
          }
          }
          if(voldown==0)
          {
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_VOLDOWN)
          {
                         voldown=1;
                         return VOLDOWN;
          }
          }
          return 0;
}
int keyUp(void)
{
    //////////////Zwolnienie przycisku//////////////
          if(select==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_SELECT)
          {
                         select=0;
                         return SELECT;
          }
          }
          if(start==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_START)
          {
                         start=0;
                         return START;
          }
          }
          if(left==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_LEFT)
          {
                         left=0;
                         return LEFT;
          }
          }
          if(up==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_UP)
          {
                         up=0;
                         return UP;
          }
          }
          if(right==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_RIGHT)
          {
                         right=0;
                         return RIGHT;
          }
          }
          if(down==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_DOWN)
          {
                         down=0;
                         return DOWN;
          }
          }
          if(square==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_SQUARE)
          {
                         square=0;
                         return SQUARE;
          }
          }
          if(triangle==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_TRIANGLE)
          {
                         triangle=0;
                         return TRIANGLE;
          }
          }
          if(circle==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_CIRCLE)
          { 
                         circle=0;
                         return CIRCLE;
          }
          }
          if(cross==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
           if(pad.Buttons & PSP_CTRL_CROSS)
          { 
                          cross=0;
                          return CROSS;
          }
          }
          if(ltrigger==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_LTRIGGER)
          {
                         ltrigger=0;
                         return LTRIGGER;
          }
          }
          if(rtrigger==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_RTRIGGER)
          {
                         rtrigger=0;
                         return RTRIGGER;
          }
          }
          if(note==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_NOTE)
          {
                         note=0;
                         return NOTE;
          }
          }
          if(screen==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_SCREEN)
          {
                         screen=0;
                         return SCREEN;
          }
          }
          if(volup==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_VOLUP)
          {
                         volup=0;
                         return VOLUP;
          }
          }
          if(voldown==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_VOLDOWN)
          {
                         voldown=0;
                         return VOLDOWN;
          }
          }
          return 0;
}
int keyTab(int KT_lastKey)
    {
          keyTabUp();
          KT_lastKey = 0;
          //////////////Naciœniêcie przycisku//////////////
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_SQUARE)
          {
                         square=1;
                          KT_lastKey = SQUARE;
          }
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_TRIANGLE)
          {
                         triangle=1;
                          KT_lastKey = TRIANGLE;
          }
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_CIRCLE)
          { 
                         circle=1;
                          KT_lastKey = CIRCLE;
          }
          sceCtrlPeekBufferPositive(&pad, 1);
           if(pad.Buttons & PSP_CTRL_CROSS)
          { 
                          cross=1;
                          KT_lastKey = CROSS;
          }
          
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_UP)
          {
                         up=1;
                         if(square)KT_lastKey = UP_SQUARE;
                         else if(triangle)KT_lastKey = UP_TRIANGLE;
                         else if(circle)KT_lastKey = UP_CIRCLE;
                         else if(cross)KT_lastKey = UP_CROSS;
                         else KT_lastKey = UP;
          }
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_DOWN)
          {
                         down=1;
                         if(left)KT_lastKey = LEFT_DOWN;
                         else if(right)KT_lastKey = RIGHT_DOWN;
                         else if(square)KT_lastKey = DOWN_SQUARE;
                         else if(triangle)KT_lastKey = DOWN_TRIANGLE;
                         else if(circle)KT_lastKey = DOWN_CIRCLE;
                         else if(cross)KT_lastKey = DOWN_CROSS;
                         else KT_lastKey = DOWN;
          }
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_LEFT)
          {
                         left=1;
                         if(down)KT_lastKey = LEFT_DOWN;
                         else if(square)KT_lastKey = LEFT_SQUARE;
                         else if(triangle)KT_lastKey = LEFT_TRIANGLE;
                         else if(circle)KT_lastKey = LEFT_CIRCLE;
                         else if(cross)KT_lastKey = LEFT_CROSS;
                         else KT_lastKey = LEFT;
          }
          sceCtrlPeekBufferPositive(&pad, 1);
          if(pad.Buttons & PSP_CTRL_RIGHT)
          {
                         right=1;
                         if(down)KT_lastKey = RIGHT_DOWN;
                         else if(square)KT_lastKey = RIGHT_SQUARE;
                         else if(triangle)KT_lastKey = RIGHT_TRIANGLE;
                         else if(circle)KT_lastKey = RIGHT_CIRCLE;
                         else if(cross)KT_lastKey = RIGHT_CROSS;
                         else KT_lastKey = RIGHT;
          }
          return KT_lastKey;
    }
void keyTabUp(void)
{
    //////////////Zwolnienie przycisku//////////////
          if(left==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_LEFT)
          {
                         left=0;
          }
          }
          if(up==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_UP)
          {
                         up=0;
          }
          }
          if(right==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_RIGHT)
          {
                         right=0;
          }
          }
          if(down==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_DOWN)
          {
                         down=0;
          }
          }
          if(square==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_SQUARE)
          {
                         square=0;
          }
          }
          if(triangle==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_TRIANGLE)
          {
                         triangle=0;
          }
          }
          if(circle==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
          if(pad.Buttons & PSP_CTRL_CIRCLE)
          { 
                         circle=0;
          }
          }
          if(cross==1)
          {
          sceCtrlPeekBufferNegative(&pad, 1);
           if(pad.Buttons & PSP_CTRL_CROSS)
          { 
                          cross=0;
          }
          }
}
