#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <png.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <time.h>
#include <stdio.h>

#include "moveSelect.h"
#include "keys.h"
#include "printImage.h"
#include "timebnr.h"
#include "graphics.h"
#include "preloader.h"
 
void Move_Select_Get_Keys(int MSGK_moves[12], int MSGK_keys[12], int* MSGK_n, int* MSGK_m);

void Move_Select_Set_Keys(int MSSK_moves[12], int MSSK_keys[12], int* MSSK_n);

void Move_Select_Draw(int *MSD_credit, int MSD_moves[12], int MSD_keys[12], int *MSD_move_list_n, int *MSD_command_list_n, int *MSD_key_list_n, int *MSD_selected_list, int *MSD_incr,
Image* MSD_image_arrow, Image* MSD_image_bop_ciosy, Image* MSD_image_buttons, Image* MSD_image_key_background, Image* MSD_image_litle_red_frame,
Image* MSD_image_move_background, Image* MSD_image_red_frame, Image* MSD_image_slide_button, Image* MSD_image_selected_text, Image* MSD_image_command_menu,
Image* MSD_image_text_backgrounds, Image* MSD_image_text_moves[12]);

void Move_Select_Comand(int *MSC_credit, int MSC_moves[12], int MSC_keys[12], int *MSC_move_list_n, int *MSC_command_list_n, int *MSC_key_list_n, int *MSC_selected_list, int *MSC_incr,
Image* MSC_image_arrow, Image* MSC_image_bop_ciosy, Image* MSC_image_buttons, Image* MSC_image_key_background, Image* MSC_image_litle_red_frame, 
Image* MSC_image_move_background, Image* MSC_image_red_frame, Image* MSC_image_slide_button, Image* MSC_image_selected_text, Image* MSC_image_command_menu, 
Image* MSC_image_text_backgrounds, Image* MSC_image_text_moves[12]);     

void Move_Select_Keylist(int *MSK_credit, int MSK_moves[12], int MSK_keys[12], int *MSK_move_list_n, int *MSK_command_list_n, int *MSK_key_list_n, int *MSK_selected_list,
int *MSK_incr, Image* MSK_image_arrow, Image* MSK_image_bop_ciosy, Image* MSK_image_buttons, Image* MSK_image_key_background, Image* MSK_image_litle_red_frame, 
Image* MSK_image_move_background, Image* MSK_image_red_frame, Image* MSK_image_slide_button, Image* MSK_image_selected_text, Image* MSK_image_command_menu, 
Image* MSK_image_text_backgrounds, Image* MSK_image_text_moves[12]);    

void Move_Select_Get_Keys_Moves(int MSGK_moves[12], int MSGK_keys[12], int* MSGK_n, int* MSGK_m)
{
     MSGK_keys[0]=K_get_keys()[0];MSGK_keys[1]=K_get_keys()[1];MSGK_keys[2]=K_get_keys()[2];
     MSGK_keys[3]=K_get_keys()[3];MSGK_keys[4]=K_get_keys()[4];MSGK_keys[5]=K_get_keys()[5];
     MSGK_keys[6]=K_get_keys()[6];MSGK_keys[7]=K_get_keys()[7];MSGK_keys[8]=K_get_keys()[8];
     MSGK_keys[9]=K_get_keys()[9];MSGK_keys[10]=K_get_keys()[10];MSGK_keys[11]=K_get_keys()[11];
     *MSGK_m=0;
     for(*MSGK_n=0;*MSGK_n<12;*MSGK_n+=1)
          {
                 MSGK_moves[*MSGK_n]=0;
          }
     for(*MSGK_n=0;*MSGK_n<12;*MSGK_n+=1)
          {
                 if(MSGK_keys[*MSGK_n])
                 {
                        MSGK_moves[MSGK_keys[*MSGK_n]-1] = *MSGK_n+1;
                        *MSGK_m+=1;
                 }
          }
}
void Move_Select_Set_Moves(int MSSM_moves[12], int MSSM_keys[12], int* MSSM_n, int* MSSM_m)
{
     *MSSM_m=0;
     for(*MSSM_n=0;*MSSM_n<12;*MSSM_n+=1)
          {
                 MSSM_keys[*MSSM_n]=0;
          }
     for(*MSSM_n=0;*MSSM_n<12;*MSSM_n+=1)
          {
                 if(MSSM_moves[*MSSM_n])
                 {
                        MSSM_keys[MSSM_moves[*MSSM_n]-1] = *MSSM_n+1;
                        *MSSM_m+=1;
                 }
          }
     K_set_keys(MSSM_keys);
}
void Move_Select(int MSe_stage)
    {
          Preload_Init();
          int L_max;
          if(MSe_stage == 1) L_max = 15;
          else L_max = 10;
          Preload(L_max-10, L_max);
          Image* image_arrow = loadImage("arrowbar.png");
          Image* image_bop_ciosy = loadImage("bop_ciosy.png");
          Image* image_buttons = loadImage("buttons.png");
          Preload(L_max-9, L_max);
          Image* image_key_background = loadImage("key_background.png");
          Image* image_litle_red_frame = loadImage("litle_red_frame.png");
          Image* image_move_background = loadImage("move_background.png");
          Preload(L_max-8, L_max);
          Image* image_red_frame = loadImage("red_frame.png");
          Image* image_slide_button = loadImage("slide_button.png");
          Image* image_selected_text = loadImage("selected_text.png"); 
          Preload(L_max-7, L_max);
          Image* image_command_menu = loadImage("command_menu.png");
          Image* image_text_backgrounds = loadImage("text_backgrounds.png");
          Image* image_text_moves[12];
          Preload(L_max-6, L_max);
          image_text_moves[0] = loadImage("text_moves_1.png");
          image_text_moves[1] = loadImage("text_moves_2.png");
          image_text_moves[2] = loadImage("text_moves_3.png");
          Preload(L_max-5, L_max);
          image_text_moves[3] = loadImage("text_moves_4.png");
          image_text_moves[4] = loadImage("text_moves_5.png");
          image_text_moves[5] = loadImage("text_moves_6.png");
          Preload(L_max-4, L_max);
          image_text_moves[6] = loadImage("text_moves_7.png");
          image_text_moves[7] = loadImage("text_moves_8.png");
          image_text_moves[8] = loadImage("text_moves_9.png");
          Preload(L_max-3, L_max);
          image_text_moves[9] = loadImage("text_moves_10.png");
          image_text_moves[10] = loadImage("text_moves_11.png");
          image_text_moves[11] = loadImage("text_moves_12.png");
          Preload(L_max-2, L_max);
          
          int MSe_incr=0;
          int MSe_move_list_n = 0;
          int MSe_command_list_n = 0;
          int MSe_key_list_n=1;
          int MSe_selected_list = 1;
          int MSe_credit=0;
          int MSe_moves[12]={0,0,0,0,0,0,0,0,0,0,0,0};
          int MSe_keys[12]={0,0,0,0,0,0,0,0,0,0,0,0};
          
          Move_Select_Get_Keys_Moves(MSe_moves, MSe_keys, &MSe_incr, &MSe_move_list_n);
          MSe_credit = 2+((MSe_stage*2)-MSe_move_list_n);
          MSe_incr = 1;
          MSe_move_list_n = 2;
          Preload(L_max-1, L_max);
          
          Print_Number_Init();
                    
          Preload(L_max, L_max);
          Preload_End();
          
          Move_Select_Draw(&MSe_credit, MSe_moves, MSe_keys, &MSe_move_list_n, &MSe_command_list_n, &MSe_key_list_n, &MSe_selected_list, &MSe_incr, image_arrow, image_bop_ciosy, image_buttons,
          image_key_background, image_litle_red_frame, image_move_background, image_red_frame, image_slide_button, image_selected_text, image_command_menu, image_text_backgrounds, image_text_moves);
          
          while(MSe_incr)
          {
                 sceDisplayWaitVblankStart();
                            switch(key())
                            {
                                  case UP:
                                       while(MSe_selected_list)
                                       {
                                                MSe_incr+=2;
                                                Move_Select_Draw(&MSe_credit, MSe_moves, MSe_keys, &MSe_move_list_n, &MSe_command_list_n, &MSe_key_list_n, &MSe_selected_list, &MSe_incr, image_arrow, image_bop_ciosy, image_buttons,
                                                image_key_background, image_litle_red_frame, image_move_background, image_red_frame, image_slide_button, image_selected_text, image_command_menu, image_text_backgrounds, image_text_moves);
                                                if(MSe_incr>=53) 
                                                {
                                                     MSe_incr=1;
                                                     MSe_selected_list=0;
                                                }
                                       }
                                       MSe_selected_list=1;
                                       MSe_move_list_n--;
                                       if(MSe_move_list_n<1)MSe_move_list_n=12;
                                       Move_Select_Draw(&MSe_credit, MSe_moves, MSe_keys, &MSe_move_list_n, &MSe_command_list_n, &MSe_key_list_n, &MSe_selected_list, &MSe_incr, image_arrow, image_bop_ciosy, image_buttons,
                                       image_key_background, image_litle_red_frame, image_move_background, image_red_frame, image_slide_button, image_selected_text, image_command_menu, image_text_backgrounds, image_text_moves);
                                       break;
                                  case DOWN:
                                       while(MSe_selected_list)
                                       {
                                                MSe_incr-=2;
                                                Move_Select_Draw(&MSe_credit, MSe_moves, MSe_keys, &MSe_move_list_n, &MSe_command_list_n, &MSe_key_list_n, &MSe_selected_list, &MSe_incr, image_arrow, image_bop_ciosy, image_buttons,
                                                image_key_background, image_litle_red_frame, image_move_background, image_red_frame, image_slide_button, image_selected_text, image_command_menu, image_text_backgrounds, image_text_moves);
                                                if(MSe_incr<=-51) 
                                                {
                                                     MSe_incr=1;
                                                     MSe_selected_list=0;
                                                }
                                       }
                                       MSe_selected_list=1;
                                       MSe_move_list_n++;
                                       if(MSe_move_list_n>12)MSe_move_list_n=1;
                                       Move_Select_Draw(&MSe_credit, MSe_moves, MSe_keys, &MSe_move_list_n, &MSe_command_list_n, &MSe_key_list_n, &MSe_selected_list, &MSe_incr, image_arrow, image_bop_ciosy, image_buttons,
                                       image_key_background, image_litle_red_frame, image_move_background, image_red_frame, image_slide_button, image_selected_text, image_command_menu, image_text_backgrounds, image_text_moves);
                                       break;
                            }
                            switch(keyDown())
                            {
                                  case RIGHT:
                                       MSe_selected_list=2;
                                       Move_Select_Comand(&MSe_credit, MSe_moves, MSe_keys, &MSe_move_list_n, &MSe_command_list_n, &MSe_key_list_n, &MSe_selected_list, &MSe_incr, image_arrow, image_bop_ciosy, image_buttons,
                                       image_key_background, image_litle_red_frame, image_move_background, image_red_frame, image_slide_button, image_selected_text, image_command_menu, image_text_backgrounds, image_text_moves);
                                       if(MSe_incr!=0)Move_Select_Draw(&MSe_credit, MSe_moves, MSe_keys, &MSe_move_list_n, &MSe_command_list_n, &MSe_key_list_n, &MSe_selected_list, &MSe_incr, image_arrow, image_bop_ciosy, image_buttons,
                                       image_key_background, image_litle_red_frame, image_move_background, image_red_frame, image_slide_button, image_selected_text, image_command_menu, image_text_backgrounds, image_text_moves);
                                       break;
                                  case SQUARE:
                                       MSe_selected_list=3;
                                       Move_Select_Keylist(&MSe_credit, MSe_moves, MSe_keys, &MSe_move_list_n, &MSe_command_list_n, &MSe_key_list_n, &MSe_selected_list, &MSe_incr, image_arrow, image_bop_ciosy, image_buttons,
                                       image_key_background, image_litle_red_frame, image_move_background, image_red_frame, image_slide_button, image_selected_text, image_command_menu, image_text_backgrounds, image_text_moves);
                                       MSe_key_list_n=1;
                                       Move_Select_Draw(&MSe_credit, MSe_moves, MSe_keys, &MSe_move_list_n, &MSe_command_list_n, &MSe_key_list_n, &MSe_selected_list, &MSe_incr, image_arrow, image_bop_ciosy, image_buttons,
                                       image_key_background, image_litle_red_frame, image_move_background, image_red_frame, image_slide_button, image_selected_text, image_command_menu, image_text_backgrounds, image_text_moves);
                                       break;
                                  case TRIANGLE://TRIANGLE
                                       if((MSe_move_list_n<2) || (MSe_move_list_n>3))
                                       {
                                              if(MSe_moves[MSe_move_list_n-1]>0)
                                              {
                                                     MSe_moves[MSe_move_list_n-1]=0;
                                                     MSe_credit++;
                                                     Move_Select_Draw(&MSe_credit, MSe_moves, MSe_keys, &MSe_move_list_n, &MSe_command_list_n, &MSe_key_list_n, &MSe_selected_list, &MSe_incr, image_arrow, image_bop_ciosy, image_buttons,
                                                     image_key_background, image_litle_red_frame, image_move_background, image_red_frame, image_slide_button, image_selected_text, image_command_menu, image_text_backgrounds, image_text_moves);
                                              }
                                       }
                                       break;
                                  case CROSS://CROSS
                                       if(MSe_credit)
                                       {
                                              if(!MSe_moves[MSe_move_list_n-1])
                                              {
                                                     for(MSe_selected_list=0;MSe_selected_list<12;MSe_selected_list++)
                                                     {
                                                            if(MSe_move_list_n==MSe_moves[MSe_selected_list])MSe_incr=0;
                                                     }
                                                     if(MSe_incr)
                                                     {
                                                            MSe_moves[MSe_move_list_n-1]=MSe_move_list_n;
                                                            MSe_credit--;
                                                     }
                                                     else
                                                     {
                                                            MSe_incr=1;
                                                            do
                                                            {
                                                                   sceDisplayWaitVblankStart();
                                                                   for(MSe_selected_list=0;MSe_selected_list<12;MSe_selected_list++)
                                                                   {
                                                                          if(MSe_incr==MSe_moves[MSe_selected_list])MSe_key_list_n=0;
                                                                   }
                                                                   if(MSe_key_list_n)
                                                                   {
                                                                          MSe_moves[MSe_move_list_n-1]=MSe_incr;
                                                                          MSe_credit--;
                                                                          MSe_incr=0;
                                                                   }
                                                                   else 
                                                                   {
                                                                          MSe_incr+=1;
                                                                          MSe_key_list_n=1;
                                                                   }
                                                            }while(MSe_incr);
                                                     }
                                              }
                                       }
                                       MSe_key_list_n=1;
                                       MSe_selected_list=1;
                                       MSe_incr=1;
                                       Move_Select_Draw(&MSe_credit, MSe_moves, MSe_keys, &MSe_move_list_n, &MSe_command_list_n, &MSe_key_list_n, &MSe_selected_list, &MSe_incr, image_arrow, image_bop_ciosy, image_buttons,
                                       image_key_background, image_litle_red_frame, image_move_background, image_red_frame, image_slide_button, image_selected_text, image_command_menu, image_text_backgrounds, image_text_moves);
                                       break; 
                            }    
          }
          Move_Select_Set_Moves(MSe_moves, MSe_keys, &MSe_incr, &MSe_selected_list);
          
          Print_Number_End();
                    
          freeImage(image_text_moves[0]);freeImage(image_text_moves[1]);freeImage(image_text_moves[2]);
          freeImage(image_text_moves[3]);freeImage(image_text_moves[4]);freeImage(image_text_moves[5]);
          freeImage(image_text_moves[6]);freeImage(image_text_moves[7]);freeImage(image_text_moves[8]);
          freeImage(image_text_moves[9]);freeImage(image_text_moves[10]);freeImage(image_text_moves[11]);
          freeImage(image_arrow);
          freeImage(image_bop_ciosy);
          freeImage(image_buttons);
          freeImage(image_key_background);
          freeImage(image_litle_red_frame);
          freeImage(image_move_background);
          freeImage(image_red_frame);
          freeImage(image_slide_button);
          freeImage(image_selected_text);
          freeImage(image_command_menu);
          freeImage(image_text_backgrounds);
    }
void Move_Select_Keylist(int *MSK_credit, int MSK_moves[12], int MSK_keys[12], int *MSK_move_list_n, int *MSK_command_list_n, int *MSK_key_list_n, int *MSK_selected_list,
int *MSK_incr, Image* MSK_image_arrow, Image* MSK_image_bop_ciosy, Image* MSK_image_buttons, Image* MSK_image_key_background, Image* MSK_image_litle_red_frame, 
Image* MSK_image_move_background, Image* MSK_image_red_frame, Image* MSK_image_slide_button, Image* MSK_image_selected_text, Image* MSK_image_command_menu, 
Image* MSK_image_text_backgrounds, Image* MSK_image_text_moves[12])
    {
          Move_Select_Set_Moves(MSK_moves, MSK_keys, MSK_incr, MSK_key_list_n);
          if(*MSK_key_list_n==12){*MSK_key_list_n=0;*MSK_selected_list = 1;}
          else *MSK_key_list_n=1;
          *MSK_incr=1;
          Move_Select_Draw(MSK_credit, MSK_moves, MSK_keys, MSK_move_list_n, MSK_command_list_n, MSK_key_list_n, MSK_selected_list, MSK_incr, MSK_image_arrow, MSK_image_bop_ciosy, MSK_image_buttons,
          MSK_image_key_background, MSK_image_litle_red_frame, MSK_image_move_background, MSK_image_red_frame, MSK_image_slide_button, MSK_image_selected_text, MSK_image_command_menu, MSK_image_text_backgrounds, MSK_image_text_moves);
          while(*MSK_key_list_n)
          {
                sceDisplayWaitVblankStart();
                switch(key())
                {
                     case UP://UP
                          *MSK_key_list_n-=1;
                          for(*MSK_selected_list=0;*MSK_selected_list<12;*MSK_selected_list+=1)
                          {
                                if(!MSK_keys[*MSK_selected_list])
                                {
                                      *MSK_incr+=1;
                                }
                          }
                          if(*MSK_key_list_n<1)*MSK_key_list_n=*MSK_incr-1;
                          *MSK_incr=1;
                          *MSK_selected_list = 3;
                          Move_Select_Draw(MSK_credit, MSK_moves, MSK_keys, MSK_move_list_n, MSK_command_list_n, MSK_key_list_n, MSK_selected_list, MSK_incr, MSK_image_arrow, MSK_image_bop_ciosy, MSK_image_buttons,
                          MSK_image_key_background, MSK_image_litle_red_frame, MSK_image_move_background, MSK_image_red_frame, MSK_image_slide_button, MSK_image_selected_text, MSK_image_command_menu, MSK_image_text_backgrounds, MSK_image_text_moves);
                          Wait_us(150000);
                          break;
                     case DOWN://DOWN
                          *MSK_key_list_n+=1;
                          for(*MSK_selected_list=0;*MSK_selected_list<12;*MSK_selected_list+=1)
                          {
                                if(!MSK_keys[*MSK_selected_list])
                                {
                                      *MSK_incr+=1;
                                }
                          }
                          if(*MSK_key_list_n>*MSK_incr-1)*MSK_key_list_n=1;
                          *MSK_incr=1;
                          *MSK_selected_list = 3;
                          Move_Select_Draw(MSK_credit, MSK_moves, MSK_keys, MSK_move_list_n, MSK_command_list_n, MSK_key_list_n, MSK_selected_list, MSK_incr, MSK_image_arrow, MSK_image_bop_ciosy, MSK_image_buttons,
                          MSK_image_key_background, MSK_image_litle_red_frame, MSK_image_move_background, MSK_image_red_frame, MSK_image_slide_button, MSK_image_selected_text, MSK_image_command_menu, MSK_image_text_backgrounds, MSK_image_text_moves);
                          Wait_us(150000);
                          break;
                }
                switch(keyDown())
                {
                     case LEFT://LEFT 
                          *MSK_selected_list=1;
                          *MSK_key_list_n=0;
                          break;
                     case TRIANGLE://TRIANGLE
                          *MSK_selected_list=1;
                          *MSK_key_list_n=0;
                          break; 
                     case CROSS://CROSS
                          *MSK_incr=0;
                          for(*MSK_selected_list=0;*MSK_selected_list<12;*MSK_selected_list+=1)
                          {
                                if(!MSK_keys[*MSK_selected_list])
                                {
                                      *MSK_incr+=1;
                                      if(*MSK_incr==*MSK_key_list_n)
                                      {
                                            if(MSK_moves[*MSK_move_list_n-1]==0)
                                            {
                                                  if(*MSK_credit)
                                                  {
                                                  *MSK_credit-=1;
                                                  MSK_keys[*MSK_selected_list]=*MSK_move_list_n;
                                                  *MSK_selected_list=12;
                                                  }
                                            }
                                            else
                                            {
                                                  MSK_keys[MSK_moves[*MSK_move_list_n-1]-1]=0;
                                                  MSK_keys[*MSK_selected_list]=*MSK_move_list_n;
                                                  *MSK_selected_list=12;
                                            }
                                      }
                                }
                          }
                          K_set_keys(MSK_keys);
                          Move_Select_Get_Keys_Moves(MSK_moves, MSK_keys, MSK_incr, MSK_selected_list);
                          *MSK_incr=1;
                          *MSK_key_list_n=0;
                          *MSK_selected_list = 1;
                          break; 
                     }
          }
    }
void Move_Select_Comand(int *MSC_credit, int MSC_moves[12], int MSC_keys[12], int *MSC_move_list_n, int *MSC_command_list_n, int *MSC_key_list_n, int *MSC_selected_list, int *MSC_incr,
     Image* MSC_image_arrow, Image* MSC_image_bop_ciosy, Image* MSC_image_buttons, Image* MSC_image_key_background, Image* MSC_image_litle_red_frame, 
     Image* MSC_image_move_background, Image* MSC_image_red_frame, Image* MSC_image_slide_button, Image* MSC_image_selected_text, Image* MSC_image_command_menu, 
     Image* MSC_image_text_backgrounds, Image* MSC_image_text_moves[12])
    {
          *MSC_command_list_n = 3;
          Move_Select_Draw(MSC_credit, MSC_moves, MSC_keys, MSC_move_list_n, MSC_command_list_n, MSC_key_list_n, MSC_selected_list, MSC_incr, MSC_image_arrow, MSC_image_bop_ciosy, MSC_image_buttons,
          MSC_image_key_background, MSC_image_litle_red_frame, MSC_image_move_background, MSC_image_red_frame, MSC_image_slide_button, MSC_image_selected_text, MSC_image_command_menu, MSC_image_text_backgrounds, MSC_image_text_moves);
          while(*MSC_command_list_n)
          {
                sceDisplayWaitVblankStart();
                switch(key())
                {
                     case UP://UP
                          *MSC_command_list_n=*MSC_command_list_n+1;
                          if(*MSC_command_list_n==4) *MSC_command_list_n = 1;
                          Move_Select_Draw(MSC_credit, MSC_moves, MSC_keys, MSC_move_list_n, MSC_command_list_n, MSC_key_list_n, MSC_selected_list, MSC_incr, MSC_image_arrow, MSC_image_bop_ciosy, MSC_image_buttons,
                          MSC_image_key_background, MSC_image_litle_red_frame, MSC_image_move_background, MSC_image_red_frame, MSC_image_slide_button, MSC_image_selected_text, MSC_image_command_menu, MSC_image_text_backgrounds, MSC_image_text_moves);
                          Wait_us(150000);
                          break;
                     case DOWN://DOWN
                          *MSC_command_list_n=*MSC_command_list_n-1;
                          if(*MSC_command_list_n==0) *MSC_command_list_n = 3;
                          Move_Select_Draw(MSC_credit, MSC_moves, MSC_keys, MSC_move_list_n, MSC_command_list_n, MSC_key_list_n, MSC_selected_list, MSC_incr, MSC_image_arrow, MSC_image_bop_ciosy, MSC_image_buttons,
                          MSC_image_key_background, MSC_image_litle_red_frame, MSC_image_move_background, MSC_image_red_frame, MSC_image_slide_button, MSC_image_selected_text, MSC_image_command_menu, MSC_image_text_backgrounds, MSC_image_text_moves);
                          Wait_us(150000);
                          break;
                }
                switch(keyDown())
                {
                     case LEFT://LEFT
                          *MSC_selected_list=1;
                          *MSC_command_list_n=0;
                          break;
                     case CROSS://CROSS
                          switch(*MSC_command_list_n)
                          {
                                case 1://clear
                                     for(*MSC_command_list_n=0;*MSC_command_list_n<12;*MSC_command_list_n+=1)
                                     {
                                            if(MSC_moves[*MSC_command_list_n])*MSC_credit+=1;
                                            MSC_moves[*MSC_command_list_n] = 0;
                                     }
                                     MSC_moves[1] = 2;
                                     MSC_moves[2] = 3;
                                     *MSC_credit-=2;
                                     *MSC_command_list_n = 1;
                                     Move_Select_Draw(MSC_credit, MSC_moves, MSC_keys, MSC_move_list_n, MSC_command_list_n, MSC_key_list_n, MSC_selected_list, MSC_incr, MSC_image_arrow, MSC_image_bop_ciosy, MSC_image_buttons,
                                     MSC_image_key_background, MSC_image_litle_red_frame, MSC_image_move_background, MSC_image_red_frame, MSC_image_slide_button, MSC_image_selected_text, MSC_image_command_menu, MSC_image_text_backgrounds, MSC_image_text_moves);
                                     break;
                                case 2://random
                                     while(*MSC_credit)
                                     {
                                           sceDisplayWaitVblankStart();
                                           *MSC_selected_list = 0;
                                           *MSC_incr = 0;
                                           for(*MSC_command_list_n=0;*MSC_command_list_n<12;*MSC_command_list_n+=1)
                                           {
                                                  if(!MSC_moves[*MSC_command_list_n])*MSC_selected_list+=1;
                                           }
                                           *MSC_selected_list = (sceKernelLibcClock()%(*MSC_selected_list-1));
                                           for(*MSC_command_list_n=0;*MSC_command_list_n<12;*MSC_command_list_n+=1)
                                           {
                                                  if(!MSC_moves[*MSC_command_list_n])*MSC_incr+=1;
                                                  if(*MSC_incr==*MSC_selected_list+1)
                                                  {
                                                         *MSC_selected_list=*MSC_command_list_n;
                                                         *MSC_command_list_n=12;
                                                  }
                                           }
                                           for(*MSC_command_list_n=0;*MSC_command_list_n<12;*MSC_command_list_n+=1)
                                           {
                                                  if((*MSC_selected_list+1)==MSC_moves[*MSC_command_list_n])*MSC_incr=0;
                                           }
                                           if(*MSC_incr)
                                           {
                                                  MSC_moves[*MSC_selected_list]=*MSC_selected_list+1;
                                                  *MSC_credit-=1;
                                           }
                                           else
                                           {
                                                  *MSC_incr=1;
                                                  do
                                                  {
                                                         sceDisplayWaitVblankStart();
                                                         for(*MSC_command_list_n=0;*MSC_command_list_n<12;*MSC_command_list_n+=1)
                                                         {
                                                                if(*MSC_incr==MSC_moves[*MSC_command_list_n])*MSC_key_list_n=0;
                                                         }
                                                         if(*MSC_key_list_n)
                                                         {
                                                                MSC_moves[*MSC_selected_list]=*MSC_incr;
                                                                *MSC_credit-=1;
                                                                *MSC_incr=0;
                                                         }
                                                         else 
                                                         {
                                                                *MSC_incr+=1;
                                                                *MSC_key_list_n=1;
                                                         }
                                                  }while(*MSC_incr);
                                           }                                                                                                                                                                                 
                                     }
                                     *MSC_command_list_n = 2;
                                     *MSC_selected_list = 2;
                                     *MSC_incr = 1;
                                     *MSC_key_list_n=1;
                                     Move_Select_Draw(MSC_credit, MSC_moves, MSC_keys, MSC_move_list_n, MSC_command_list_n, MSC_key_list_n, MSC_selected_list, MSC_incr, MSC_image_arrow, MSC_image_bop_ciosy, MSC_image_buttons,
                                     MSC_image_key_background, MSC_image_litle_red_frame, MSC_image_move_background, MSC_image_red_frame, MSC_image_slide_button, MSC_image_selected_text, MSC_image_command_menu, MSC_image_text_backgrounds, MSC_image_text_moves);
                                     break;
                                case 3://start
                                     *MSC_selected_list=1;
                                     *MSC_command_list_n=0;
                                     *MSC_incr=0;
                                     break;
                          }
                          break; 
                     }
          }
    }
void Move_Select_Draw(int *MSD_credit, int MSD_moves[12], int MSD_keys[12], int *MSD_move_list_n, int *MSD_command_list_n, int *MSD_key_list_n, int *MSD_selected_list, int *MSD_incr,
     Image* MSD_image_arrow, Image* MSD_image_bop_ciosy, Image* MSD_image_buttons, Image* MSD_image_key_background, Image* MSD_image_litle_red_frame,
     Image* MSD_image_move_background, Image* MSD_image_red_frame, Image* MSD_image_slide_button, Image* MSD_image_selected_text, Image* MSD_image_command_menu,
     Image* MSD_image_text_backgrounds, Image* MSD_image_text_moves[12])
    {  
          blitImageToScreen(0, 0, 9 , 272, MSD_image_arrow, 0, 0);
          blitImageToScreen(0, 0, 9 , 21, MSD_image_slide_button, 0, (*MSD_move_list_n-1)*21 + 10);
          blitImageToScreen(0, 0, 158 , 136, MSD_image_command_menu, 322, 0);
          
          blitImageToScreen(0, 0, 313, 54, MSD_image_move_background, 9, *MSD_incr+54);
          blitImageToScreen(0, 0, 313, 54, MSD_image_move_background, 9, *MSD_incr+108);
          blitImageToScreen(0, 0, 313, 54, MSD_image_move_background, 9, *MSD_incr+162);
                         
          if(*MSD_move_list_n<2)       blitImageToScreen((*MSD_move_list_n+10)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+57);
          else                         blitImageToScreen((*MSD_move_list_n-2)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+57);
          blitImageToScreen((*MSD_move_list_n-1)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+111);
          if(*MSD_move_list_n>11)      blitImageToScreen((*MSD_move_list_n-12)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+165);
          else                         blitImageToScreen((*MSD_move_list_n)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+165);
          
          if(*MSD_move_list_n<2)       blitImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n+10], 54, *MSD_incr+57);
          else                         blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-2], 54, *MSD_incr+57);
          blitImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-1], 54, *MSD_incr+111);
          if(*MSD_move_list_n>11)      blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-12], 54, *MSD_incr+165);
          else                         blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n], 54, *MSD_incr+165);
          
          if(*MSD_move_list_n<2) {if(MSD_moves[*MSD_move_list_n+10]>0)     blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+10]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+72);}
          else if(MSD_moves[*MSD_move_list_n-2]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-2]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+72);
          if(MSD_moves[*MSD_move_list_n-1]>0)                              blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-1]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+126);
          if(*MSD_move_list_n>11) {if(MSD_moves[*MSD_move_list_n-12]>0)    blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-12]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+180);}
          else if(MSD_moves[*MSD_move_list_n]>0)                           blitImageToScreen(0, (MSD_moves[*MSD_move_list_n]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+180);
                   
          if(*MSD_incr==1)
          {
               blitImageToScreen(0, 53, 313, 1, MSD_image_move_background, 9, 0);
               blitImageToScreen(0, 0, 313, 54, MSD_image_move_background, 9, *MSD_incr);
               blitImageToScreen(0, 0, 313, 54, MSD_image_move_background, 9, *MSD_incr+216);
               blitImageToScreen(0, 0, 313, 1, MSD_image_move_background, 9, 271);
               
               if(*MSD_move_list_n<3)      blitImageToScreen((*MSD_move_list_n+9)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+3);
               else                        blitImageToScreen((*MSD_move_list_n-3)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+3);
               if(*MSD_move_list_n>10)     blitImageToScreen((*MSD_move_list_n-11)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+219);
               else                        blitImageToScreen((*MSD_move_list_n+1)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+219);
               
               if(*MSD_move_list_n<3)      blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n+9], 54, *MSD_incr+3);
               else                        blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-3], 54, *MSD_incr+3);
               if(*MSD_move_list_n>10)     blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-11], 54, *MSD_incr+219);
               else                        blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n+1], 54, *MSD_incr+219);
               
               if(*MSD_move_list_n<3) {if(MSD_moves[*MSD_move_list_n+9]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+9]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+18);}
               else if(MSD_moves[*MSD_move_list_n-3]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-3]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+18);
               if(*MSD_move_list_n>10) {if(MSD_moves[*MSD_move_list_n-11]>0)    blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-11]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+234);}
               else if(MSD_moves[*MSD_move_list_n+1]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+1]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+234);
          }
          else if(*MSD_incr<1)
          {
               if(*MSD_incr<0)
               {
                    blitImageToScreen(0, 0-*MSD_incr, 313, 54+*MSD_incr, MSD_image_move_background, 9, 0);
               }
               else
               {
                    blitImageToScreen(0, 0, 313, 54, MSD_image_move_background, 9, 0);
               }
                    blitImageToScreen(0, 0, 313, 54, MSD_image_move_background, 9, *MSD_incr+216);
                    blitImageToScreen(0, 0, 313, -*MSD_incr+2, MSD_image_move_background, 9, *MSD_incr+270);
               
               if(*MSD_incr<-50)
               {
                    if(*MSD_move_list_n>9)blitImageToScreen((*MSD_move_list_n-10)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+273);
                    else                 blitImageToScreen((*MSD_move_list_n+2)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+273);
                    
                    if(*MSD_move_list_n>9)blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-10], 54, *MSD_incr+273);
                    else                 blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n+2], 54, *MSD_incr+273);
               }
               else if(*MSD_incr==-50)
               {
                    if(*MSD_move_list_n<3)blitImageToScreen((*MSD_move_list_n+9)*36, 0-*MSD_incr-3, 36, 48+*MSD_incr+3, MSD_image_bop_ciosy, 12, 0);
                    else                 blitImageToScreen((*MSD_move_list_n-3)*36, 0-*MSD_incr-3, 36, 48+*MSD_incr+3, MSD_image_bop_ciosy, 12, 0);
                    if(*MSD_move_list_n>9)blitImageToScreen((*MSD_move_list_n-10)*36, 0, 36, -*MSD_incr+2-3, MSD_image_bop_ciosy, 12, *MSD_incr+273);
                    else                 blitImageToScreen((*MSD_move_list_n+2)*36, 0, 36, -*MSD_incr+2-3, MSD_image_bop_ciosy, 12, *MSD_incr+273);
                    
                    if(*MSD_move_list_n<3)blitAlphaImageToScreen(0, 0-*MSD_incr-3, 208, 48+*MSD_incr+3, MSD_image_text_moves[*MSD_move_list_n+9], 54, 0);
                    else                 blitAlphaImageToScreen(0, 0-*MSD_incr-3, 208, 48+*MSD_incr+3, MSD_image_text_moves[*MSD_move_list_n-3], 54, 0);
                    if(*MSD_move_list_n>9)blitAlphaImageToScreen(0, 0, 208, -*MSD_incr+2-3, MSD_image_text_moves[*MSD_move_list_n-10], 54, *MSD_incr+273);
                    else                 blitAlphaImageToScreen(0, 0, 208, -*MSD_incr+2-3, MSD_image_text_moves[*MSD_move_list_n+2], 54, *MSD_incr+273);
               }
               else if(*MSD_incr<-2)
               {
                    if(*MSD_move_list_n<3)blitImageToScreen((*MSD_move_list_n+9)*36, 0-*MSD_incr-3, 36, 48+*MSD_incr+3, MSD_image_bop_ciosy, 12, 0);
                    else                 blitImageToScreen((*MSD_move_list_n-3)*36, 0-*MSD_incr-3, 36, 48+*MSD_incr+3, MSD_image_bop_ciosy, 12, 0);
                    if(*MSD_move_list_n>9)blitImageToScreen((*MSD_move_list_n-10)*36, 0, 36, -*MSD_incr+2-3, MSD_image_bop_ciosy, 12, *MSD_incr+273);
                    else                 blitImageToScreen((*MSD_move_list_n+2)*36, 0, 36, -*MSD_incr+2-3, MSD_image_bop_ciosy, 12, *MSD_incr+273);
                    
                    if(*MSD_move_list_n<3)blitAlphaImageToScreen(0, 0-*MSD_incr-3, 208, 48+*MSD_incr+3, MSD_image_text_moves[*MSD_move_list_n+9], 54, 0);
                    else                 blitAlphaImageToScreen(0, 0-*MSD_incr-3, 208, 48+*MSD_incr+3, MSD_image_text_moves[*MSD_move_list_n-3], 54, 0);
                    if(*MSD_move_list_n>9)blitAlphaImageToScreen(0, 0, 208, -*MSD_incr+2-3, MSD_image_text_moves[*MSD_move_list_n-10], 54, *MSD_incr+273);
                    else                 blitAlphaImageToScreen(0, 0, 208, -*MSD_incr+2-3, MSD_image_text_moves[*MSD_move_list_n+2], 54, *MSD_incr+273);
               }
               else
               {
                    if(*MSD_move_list_n<3)blitImageToScreen((*MSD_move_list_n+9)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+3);
                    else                 blitImageToScreen((*MSD_move_list_n-3)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+3);
                    
                    if(*MSD_move_list_n<3)blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n+9], 54, *MSD_incr+3);
                    else                 blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-3], 54, *MSD_incr+3);
               }
                    if(*MSD_move_list_n>10)blitImageToScreen((*MSD_move_list_n-11)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+219);
                    else                 blitImageToScreen((*MSD_move_list_n+1)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+219);
                    
                    if(*MSD_move_list_n>10)blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-11], 54, *MSD_incr+219);
                    else                 blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n+1], 54, *MSD_incr+219);
               
               if(*MSD_move_list_n>10) {if(MSD_moves[*MSD_move_list_n-11]>0)    blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-11]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+234);}
               else if(MSD_moves[*MSD_move_list_n+1]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+1]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+234);
               
               if(*MSD_incr<-34)
               {
                    if(*MSD_move_list_n>9) {if(MSD_moves[*MSD_move_list_n-10]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-10]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+288);}
                    else if(MSD_moves[*MSD_move_list_n+2]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+2]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+288);
               }
               else if(*MSD_incr<-32)
               {
                    if(*MSD_move_list_n>9) {if(MSD_moves[*MSD_move_list_n-10]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-10]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+288);}
                    else if(MSD_moves[*MSD_move_list_n+2]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+2]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+288);
                    if(*MSD_move_list_n<3) {if(MSD_moves[*MSD_move_list_n+9]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+9]-1)*17-*MSD_incr-18, 51, 17+*MSD_incr+18, MSD_image_buttons, 268, 0);}
                    else if(MSD_moves[*MSD_move_list_n-3]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-3]-1)*17-*MSD_incr-18, 51, 17+*MSD_incr+18, MSD_image_buttons, 268, 0);
               }
               else if(*MSD_incr<-17)
               {
                    if(*MSD_move_list_n<3) {if(MSD_moves[*MSD_move_list_n+9]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+9]-1)*17-*MSD_incr-18, 51, 17+*MSD_incr+18, MSD_image_buttons, 268, 0);}
                    else if(MSD_moves[*MSD_move_list_n-3]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-3]-1)*17-*MSD_incr-18, 51, 17+*MSD_incr+18, MSD_image_buttons, 268, 0);
                    if(*MSD_move_list_n>9) {if(MSD_moves[*MSD_move_list_n-10]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-10]-1)*17, 51, -*MSD_incr+2-18, MSD_image_buttons, 268, *MSD_incr+288);}
                    else if(MSD_moves[*MSD_move_list_n+2]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+2]-1)*17, 51, -*MSD_incr+2-18, MSD_image_buttons, 268, *MSD_incr+288);
               }
               else if(*MSD_incr==-17)
               {
                    if(*MSD_move_list_n>9) {if(MSD_moves[*MSD_move_list_n-10]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-10]-1)*17, 51, -*MSD_incr+2-18, MSD_image_buttons, 268, *MSD_incr+288);}
                    else if(MSD_moves[*MSD_move_list_n+2]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+2]-1)*17, 51, -*MSD_incr+2-18, MSD_image_buttons, 268, *MSD_incr+288);
                    if(*MSD_move_list_n<3) {if(MSD_moves[*MSD_move_list_n+9]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+9]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+18);}
                    else if(MSD_moves[*MSD_move_list_n-3]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-3]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+18);
               }
               else
               {
                    if(*MSD_move_list_n<3) {if(MSD_moves[*MSD_move_list_n+9]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+9]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+18);}
                    else if(MSD_moves[*MSD_move_list_n-3]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-3]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+18);
               }
          }
          else if(*MSD_incr>1)
          {
               blitImageToScreen(0, 0, 313, 54-*MSD_incr+2, MSD_image_move_background, 9, *MSD_incr+216);
               blitImageToScreen(0, 54-*MSD_incr, 313, *MSD_incr, MSD_image_move_background, 9, 0);
               blitImageToScreen(0, 0, 313, 54, MSD_image_move_background, 9, *MSD_incr);
               
               if(*MSD_incr>52)
               {
                    if(*MSD_move_list_n<4)blitImageToScreen((*MSD_move_list_n+8)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, 0);
                    else                 blitImageToScreen((*MSD_move_list_n-4)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, 0);
                    
                    if(*MSD_move_list_n<4)blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n+8], 54, 0);
                    else                 blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-4], 54, 0);
               }
               else if(*MSD_incr>50)
               {
                    if(*MSD_move_list_n<4)blitImageToScreen((*MSD_move_list_n+8)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, 0);
                    else                 blitImageToScreen((*MSD_move_list_n-4)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, 0);
                    if(*MSD_move_list_n>10)blitImageToScreen((*MSD_move_list_n-11)*36, 0, 36, 48-*MSD_incr+2+3, MSD_image_bop_ciosy, 12, *MSD_incr+219);
                    else                 blitImageToScreen((*MSD_move_list_n+1)*36, 0, 36, 48-*MSD_incr+2+3, MSD_image_bop_ciosy, 12, *MSD_incr+219);
                    
                    if(*MSD_move_list_n<4)blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n+8], 54, 0);
                    else                 blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-4], 54, 0);
                    if(*MSD_move_list_n>10)blitAlphaImageToScreen(0, 0, 208, 48-*MSD_incr+2+3, MSD_image_text_moves[*MSD_move_list_n-11], 54, *MSD_incr+219);
                    else                 blitAlphaImageToScreen(0, 0, 208, 48-*MSD_incr+2+3, MSD_image_text_moves[*MSD_move_list_n+1], 54, *MSD_incr+219);
               }
               else if(*MSD_incr>4)
               {
                    if(*MSD_move_list_n<4)blitImageToScreen((*MSD_move_list_n+8)*36, 48-*MSD_incr+3, 36, *MSD_incr-3, MSD_image_bop_ciosy, 12, 0);
                    else                 blitImageToScreen((*MSD_move_list_n-4)*36, 48-*MSD_incr+3, 36, *MSD_incr-3, MSD_image_bop_ciosy, 12, 0);
                    if(*MSD_move_list_n>10)blitImageToScreen((*MSD_move_list_n-11)*36, 0, 36, 48-*MSD_incr+2+3, MSD_image_bop_ciosy, 12, *MSD_incr+219);
                    else                 blitImageToScreen((*MSD_move_list_n+1)*36, 0, 36, 48-*MSD_incr+2+3, MSD_image_bop_ciosy, 12, *MSD_incr+219);
                    
                    if(*MSD_move_list_n<4)blitAlphaImageToScreen(0, 48-*MSD_incr+3, 208, *MSD_incr-3, MSD_image_text_moves[*MSD_move_list_n+8], 54, 0);
                    else                 blitAlphaImageToScreen(0, 48-*MSD_incr+3, 208, *MSD_incr-3, MSD_image_text_moves[*MSD_move_list_n-4], 54, 0);
                    if(*MSD_move_list_n>10)blitAlphaImageToScreen(0, 0, 208, 48-*MSD_incr+2+3, MSD_image_text_moves[*MSD_move_list_n-11], 54, *MSD_incr+219);
                    else                 blitAlphaImageToScreen(0, 0, 208, 48-*MSD_incr+2+3, MSD_image_text_moves[*MSD_move_list_n+1], 54, *MSD_incr+219);
               }
               else if(*MSD_incr>3)
               {
                    if(*MSD_move_list_n<4)blitImageToScreen((*MSD_move_list_n+8)*36, 48-*MSD_incr+3, 36, *MSD_incr-3, MSD_image_bop_ciosy, 12, 0);
                    else                 blitImageToScreen((*MSD_move_list_n-4)*36, 48-*MSD_incr+3, 36, *MSD_incr-3, MSD_image_bop_ciosy, 12, 0);
                    if(*MSD_move_list_n>10)blitImageToScreen((*MSD_move_list_n-11)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+219);
                    else                 blitImageToScreen((*MSD_move_list_n+1)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+219);
                    
                    if(*MSD_move_list_n<4)blitAlphaImageToScreen(0, 48-*MSD_incr+3, 208, *MSD_incr-3, MSD_image_text_moves[*MSD_move_list_n+8], 54, 0);
                    else                 blitAlphaImageToScreen(0, 48-*MSD_incr+3, 208, *MSD_incr-3, MSD_image_text_moves[*MSD_move_list_n-4], 54, 0);
                    if(*MSD_move_list_n>10)blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-11], 54, *MSD_incr+219);
                    else                 blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n+1], 54, *MSD_incr+219);
               }
               else
               {
                    if(*MSD_move_list_n>10)blitImageToScreen((*MSD_move_list_n-11)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+219);
                    else                 blitImageToScreen((*MSD_move_list_n+1)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+219);
                    
                    if(*MSD_move_list_n>10)blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-11], 54, *MSD_incr+219);
                    else                 blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n+1], 54, *MSD_incr+219);
               }
                   
               if(*MSD_move_list_n<3)blitImageToScreen((*MSD_move_list_n+9)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+3);
               else                 blitImageToScreen((*MSD_move_list_n-3)*36, 0, 36, 48, MSD_image_bop_ciosy, 12, *MSD_incr+3);
               
               if(*MSD_move_list_n<3)blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n+9], 54, *MSD_incr+3);
               else                 blitAlphaImageToScreen(0, 0, 208, 48, MSD_image_text_moves[*MSD_move_list_n-3], 54, *MSD_incr+3);
                         
               if(*MSD_move_list_n<3) {if(MSD_moves[*MSD_move_list_n+9]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+9]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+18);}
               else if(MSD_moves[*MSD_move_list_n-3]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-3]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+18);
               
               if(*MSD_incr>37)
               {                
                    if(*MSD_move_list_n<4) {if(MSD_moves[*MSD_move_list_n+8]>0)    blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+8]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr-36);}
                    else if(MSD_moves[*MSD_move_list_n-4]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-4]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr-36);
               }
               else if(*MSD_incr>35)
               {                
                    if(*MSD_move_list_n<4) {if(MSD_moves[*MSD_move_list_n+8]>0)    blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+8]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr-36);}
                    else if(MSD_moves[*MSD_move_list_n-4]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-4]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr-36);
                    if(*MSD_move_list_n>10) {if(MSD_moves[*MSD_move_list_n-11]>0)    blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-11]-1)*17, 51, 17-*MSD_incr+3+18, MSD_image_buttons, 268, *MSD_incr+234);}
                    else if(MSD_moves[*MSD_move_list_n+1]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+1]-1)*17, 51, 17-*MSD_incr+3+18, MSD_image_buttons, 268, *MSD_incr+234);
               }
               else if(*MSD_incr>21)
               {               
                    if(*MSD_move_list_n<4) {if(MSD_moves[*MSD_move_list_n+8]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+8]-1)*17-*MSD_incr+18+17, 51, *MSD_incr-18, MSD_image_buttons, 268, 0);}
                    else if(MSD_moves[*MSD_move_list_n-4]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-4]-1)*17-*MSD_incr+18+17, 51, *MSD_incr-18, MSD_image_buttons, 268, 0);
                    if(*MSD_move_list_n>10) {if(MSD_moves[*MSD_move_list_n-11]>0)    blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-11]-1)*17, 51, 17-*MSD_incr+3+18, MSD_image_buttons, 268, *MSD_incr+234);}
                    else if(MSD_moves[*MSD_move_list_n+1]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+1]-1)*17, 51, 17-*MSD_incr+3+18, MSD_image_buttons, 268, *MSD_incr+234);
              }
               else if(*MSD_incr>18)
               {               
                    if(*MSD_move_list_n<4) {if(MSD_moves[*MSD_move_list_n+8]>0)      blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+8]-1)*17-*MSD_incr+18+17, 51, *MSD_incr-18, MSD_image_buttons, 268, 0);}
                    else if(MSD_moves[*MSD_move_list_n-4]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-4]-1)*17-*MSD_incr+18+17, 51, *MSD_incr-18, MSD_image_buttons, 268, 0);
                    if(*MSD_move_list_n>10) {if(MSD_moves[*MSD_move_list_n-11]>0)    blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-11]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+234);}
                    else if(MSD_moves[*MSD_move_list_n+1]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+1]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+234);
               }
               else
               {                
                    if(*MSD_move_list_n>10) {if(MSD_moves[*MSD_move_list_n-11]>0)    blitImageToScreen(0, (MSD_moves[*MSD_move_list_n-11]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+234);}
                    else if(MSD_moves[*MSD_move_list_n+1]>0)                         blitImageToScreen(0, (MSD_moves[*MSD_move_list_n+1]-1)*17, 51, 17, MSD_image_buttons, 268, *MSD_incr+234);
               }
          }
          
          switch(*MSD_selected_list)
          {
                 case 1:
                      blitImageToScreen(0, 0, 158, 136, MSD_image_text_backgrounds, 322, 136);
                      blitAlphaImageToScreen(0, 0, 313, 54, MSD_image_red_frame, 9, 109);
                      break;
                 case 2:
                      blitImageToScreen(158, 0, 158, 136, MSD_image_text_backgrounds, 322, 136);
                      blitImageToScreen(0, (*MSD_command_list_n-1)*16, 122, 16, MSD_image_selected_text, 340, (3-(*MSD_command_list_n))*21 + 39);
                      break;  
                 case 3:
                      *MSD_incr = 0;
                      blitImageToScreen(316, 0, 158, 136, MSD_image_text_backgrounds, 322, 136);
                      for(*MSD_selected_list=0;*MSD_selected_list<12;*MSD_selected_list+=1)
                      {
                           if(!MSD_keys[*MSD_selected_list])
                           {
                                blitImageToScreen(0, 0, 57, 23, MSD_image_key_background, 322, *MSD_incr*23+8);
                                blitAlphaImageToScreen(0, *MSD_selected_list*17, 51, 17, MSD_image_buttons, 325, *MSD_incr*23+11);
                                *MSD_incr+=1;
                           }
                      }
                      blitAlphaImageToScreen(0, 0, 57, 23, MSD_image_litle_red_frame, 322, (*MSD_key_list_n-1)*23+8);
                      *MSD_incr=1;
                      *MSD_selected_list = 3;
                      break;
          }
          
          Print_Number(*MSD_credit, 422, 10, 's');
          
          flipScreen(); 
    }
