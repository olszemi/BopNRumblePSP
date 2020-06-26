#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <png.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <time.h>
#include <stdio.h>

#include "menu.h"
#include "keys.h"
#include "timebnr.h"
#include "graphics.h"
#include "sound.h"

void Start_Screen(void)
    {
              Image* image_tlo = loadImage("lassar_presents.png");
              Image* image_text = loadImage("push_any_button.png");
              int SS_n = 1;
              clock_t SS_timestart;
              clock_t SS_timenow;
              
              blitImageToScreen(0 ,0 ,480 , 272, image_tlo, 0, 0);
              flipScreen();
              SS_timestart = sceKernelLibcClock();
              
              while(!keyDown())
              {
                     sceDisplayWaitVblankStart(); 
                     SS_timenow = sceKernelLibcClock();
                     
                     if(SS_timenow - SS_timestart > 750000)
                        {
                            blitImageToScreen(0 ,0 ,480 , 272, image_tlo, 0, 0);
                            switch(SS_n)
                            {
                                     case 0:
                                                 SS_n=1;
                                                 break;
                                     case 1:
                                                 blitImageToScreen(0 ,0 ,342 , 14, image_text, 69, 251);
                                                 SS_n =0;
                                                 break;
                            }
                            flipScreen();
                            SS_timestart = sceKernelLibcClock();
                        }
              }
              freeImage(image_tlo);
              freeImage(image_text);
    }

void Menu_Screen(void)
    {
             Image* MS_image_tlo = loadImage("start_menu.png");
             Image* MS_image_text = loadImage("selected_text.png");
             int MS_n = 2;
             
             blitImageToScreen(0 ,0 ,480 , 272, MS_image_tlo, 0, 0);
             blitImageToScreen(0 ,(MS_n)*16 ,122 , 16, MS_image_text, 179, (MS_n-2)*21 + 205);
             flipScreen();  
             while(MS_n)
             {
                   sceDisplayWaitVblankStart();
                   switch(key())
                   {
                         case UP:
                              MS_n--;
                              if(MS_n==1) MS_n = 4;
                              blitImageToScreen(0 ,0 ,480 , 272, MS_image_tlo, 0, 0);
                              blitImageToScreen(0 ,(MS_n)*16 ,122 , 16, MS_image_text, 179, (MS_n-2)*21 + 205);
                              flipScreen();  
                              Wait_us(150000);
                              break;
                         case DOWN:
                              MS_n++;
                              if(MS_n==5) MS_n = 2;
                              blitImageToScreen(0 ,0 ,480 , 272, MS_image_tlo, 0, 0);
                              blitImageToScreen(0 ,(MS_n)*16 ,122 , 16, MS_image_text, 179, (MS_n-2)*21 + 205);
                              flipScreen();  
                              Wait_us(150000);
                               break;
                   }
                   if(keyDown()==CROSS)
                   {
                         switch(MS_n)
                         {
                               case 2:
                                    MS_n = 0;
                                    break;
                               case 3:
                                    //load
                                    
                                    break;
                               case 4:
                                    //option
                                    Option_Screen(0, 0);
                                    blitImageToScreen(0 ,0 ,480 , 272, MS_image_tlo, 0, 0);
                                    blitImageToScreen(0 ,(MS_n)*16 ,122 , 16, MS_image_text, 179, (MS_n-2)*21 + 205);
                                    flipScreen();
                                    break;
                         }
                   }
             }
             freeImage(MS_image_tlo);
             freeImage(MS_image_text);
    }
void Option_Screen(int OS_music_volume, int OS_efects_volume)
     {
             Image* OS_image_tlo = loadImage("option_background.png");
             Image* OS_image_text = loadImage("selected_options.png");
             Image* OS_image_slider = loadImage("slide_button_horizontal.png");
             int OS_selected_text = 0;
             int OS_n=1;
             
             blitImageToScreen(0 ,0 ,480 , 272, OS_image_tlo, 0, 0);
             blitImageToScreen(0 ,OS_selected_text*16 ,127 , 16, OS_image_text, 7, (OS_selected_text*21) + 61);
             blitImageToScreen(0 ,0 ,21 , 9, OS_image_slider, (OS_music_volume*3)+144, 65);
             blitImageToScreen(0 ,0 ,21 , 9, OS_image_slider, (OS_efects_volume*3)+144, 86);
             flipScreen(); 
             while(OS_n)
             {
                     sceDisplayWaitVblankStart();
                     switch(key())
                     {
                         case LEFT:
                              if(OS_selected_text)
                              {
                                    if(OS_efects_volume>0)OS_efects_volume--;
                              }
                              else
                              {
                                    if(OS_music_volume>0)OS_music_volume--;
                              }
                              blitImageToScreen(0 ,0 ,480 , 272, OS_image_tlo, 0, 0);
                              blitImageToScreen(0 ,(OS_selected_text)*16 ,127 , 16, OS_image_text, 7, (OS_selected_text)*21 + 61);
                              blitImageToScreen(0 ,0 ,21 , 9, OS_image_slider, (OS_music_volume*3)+144, 65);
                              blitImageToScreen(0 ,0 ,21 , 9, OS_image_slider, (OS_efects_volume*3)+144, 86);
                              flipScreen();
                              Wait_us(150000);
                              break;
                         case RIGHT:
                              if(OS_selected_text)
                              {
                                    if(OS_efects_volume<100)OS_efects_volume++;
                              }
                              else
                              {
                                    if(OS_music_volume<100)OS_music_volume++;
                              }
                              blitImageToScreen(0 ,0 ,480 , 272, OS_image_tlo, 0, 0);
                              blitImageToScreen(0 ,(OS_selected_text)*16 ,127 , 16, OS_image_text, 7, (OS_selected_text)*21 + 61);
                              blitImageToScreen(0 ,0 ,21 , 9, OS_image_slider, (OS_music_volume*3)+144, 65);
                              blitImageToScreen(0 ,0 ,21 , 9, OS_image_slider, (OS_efects_volume*3)+144, 86);
                              flipScreen();
                              Wait_us(150000);
                              break;
                     }
                     switch(keyDown())
                     {
                         case UP:
                              OS_selected_text++;
                              if(OS_selected_text==2)OS_selected_text=0;
                              blitImageToScreen(0 ,0 ,480 , 272, OS_image_tlo, 0, 0);
                              blitImageToScreen(0 ,(OS_selected_text)*16 ,127 , 16, OS_image_text, 7, (OS_selected_text)*21 + 61);
                              blitImageToScreen(0 ,0 ,21 , 9, OS_image_slider, (OS_music_volume*3)+144, 65);
                              blitImageToScreen(0 ,0 ,21 , 9, OS_image_slider, (OS_efects_volume*3)+144, 86);
                              flipScreen(); 
                              break;
                         case DOWN:
                              OS_selected_text--;
                              if(OS_selected_text<0)OS_selected_text=1;
                              blitImageToScreen(0 ,0 ,480 , 272, OS_image_tlo, 0, 0);
                              blitImageToScreen(0 ,(OS_selected_text)*16 ,127 , 16, OS_image_text, 7, (OS_selected_text)*21 + 61);
                              blitImageToScreen(0 ,0 ,21 , 9, OS_image_slider, (OS_music_volume*3)+144, 65);
                              blitImageToScreen(0 ,0 ,21 , 9, OS_image_slider, (OS_efects_volume*3)+144, 86);
                              flipScreen(); 
                              break;
                         case TRIANGLE:
                              OS_n=0;
                              break;
                         case CROSS:
                              /*mainThemePause();
                              testThemeStart();
                              Wait_us(4000000);
                              testThemeStop();
                              mainThemeStart();*/
                              break;
                   }
             }
             
             freeImage(OS_image_tlo);
             freeImage(OS_image_text);
             freeImage(OS_image_slider);
     }
