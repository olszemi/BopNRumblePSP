#include <malloc.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <png.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <time.h>
#include <stdio.h>
#include <pspaudio.h>
#include <pspaudiolib.h>
#include <psppower.h>
#include <time.h>

#include "enum.h"
#include "kong.h"
#include "timebnr.h"
#include "printImage.h"
#include "moveSelect.h"
#include "stage.h"
#include "bop.h"
#include "dog.h"
#include "graphics.h"
#include "keys.h"
#include "preloader.h"

void Stage_1(Bop* S1_bop,int* S1_continue);
void Stage_2(Bop* S2_bop,int* S2_continue);
void Stage_3(Bop* S3_bop,int* S3_continue);
void Stage_4(Bop* S4_bop,int* S4_continue);
void Stage_5(Bop* S5_bop,int* S5_continue);
void Stage_Destroy(Stage* SD_stage);
void Stage_Logic(Stage* SL_stage, Bop* SL_bop);
void Stage_Pause_Menu_Screen(Stage* SPMS_stage);
void Stage_EndGame_Screen(int* SEDS_continue);
Stage* Stage_Create(int SC_stagenr);
void Stage_Background_Draw(Stage* SBD_stage);
void Stage_Foreground_Draw(Stage* SFD_stage);
void Stage_HUD_Draw(Stage* SHD_stage, Bop* SHD_bop, Dog* SHD_dog, Kong* SHD_kong, int SHD_n);
void Stage_Anim_Select(Stage* SAS_stage, Bop* SAS_bop, int SAS_key_move, int SAS_LR);

void Stage_Main()
{
     
     Bop* SM_bop = Bop_Create();
     int SM_continue = POWTORKA;
     /*
     while(SM_continue==POWTORKA)
     {
          Move_Select(1);
          Stage_1(SM_bop, &SM_continue);
     }
     if(SM_continue==PRZEJSCIE)SM_continue=POWTORKA;
     while(SM_continue==POWTORKA)
     {
          Move_Select(2);
          Stage_2(SM_bop, &SM_continue);
     }*/
     if(SM_continue==PRZEJSCIE)SM_continue=POWTORKA;
     while(SM_continue==POWTORKA)
     {
          Move_Select(3);
          Stage_3(SM_bop, &SM_continue);
     }/*
     if(SM_continue==PRZEJSCIE)SM_continue=POWTORKA;
     while(SM_continue==POWTORKA)
     {
          Move_Select(4);
          Stage_4(SM_bop, &SM_continue);
     }*/
     if(SM_continue==PRZEJSCIE)SM_continue=POWTORKA;
     while(SM_continue==POWTORKA)
     {
          Move_Select(5);
          Stage_5(SM_bop, &SM_continue);
     }
     
     keys_Default();
     Bop_Destroy(SM_bop);
     if(SM_continue != WYJSCIE) Stage_EndGame_Screen(&SM_continue);
}
void Stage_1(Bop* S1_bop,int* S1_continue)
{
     int S1_Enemy_X[] = {0, 650, 800, 300, 1400, 1000, 1700};
     int S1_Enemy_Agrr[] = {350, 350, 350, 350, 350, 350, 350};
     int S1_Enemy_activ[] = {0, 350, 550, 550, 1100, 1300, 1350};
     
     Stage* S1_stage = Stage_Create(1);
     Print_Number_Init();
     
     Dog* S1_dog = Dog_Create(7, S1_Enemy_X, S1_Enemy_Agrr, S1_Enemy_activ); 
     S1_Enemy_X[0] = 350;
     S1_Enemy_activ[0] = 0;
     S1_Enemy_X[1] = 700;
     S1_Enemy_activ[1] = 400;
     S1_Enemy_X[2] = 350;
     S1_Enemy_activ[2] = 700;
     S1_Enemy_X[3] = 1000;
     S1_Enemy_activ[3] = 700;
     S1_Enemy_X[4] = 750;
     S1_Enemy_activ[4] = 1100;
     S1_Enemy_X[5] = 1550;
     S1_Enemy_activ[5] = 1200;
     S1_Enemy_X[6] = 1650;
     S1_Enemy_activ[6] = 1300;
     Kong* S1_kong = Kong_Create(7, S1_Enemy_X, S1_Enemy_Agrr, S1_Enemy_activ); 
     //////////////////////Framerate test//////////////////////////
     int framerate = 0;
     int framerateact = 0;
     clock_t S1_framerate_start = 0;
     //////////////////////////////////////////////////////////////
     
     *S1_continue=4;
     S1_stage->S_time_start = sceKernelLibcClock();
     
     while(*S1_continue==4)
     {
             sceDisplayWaitVblankStart();

             if(Bop_LE_Get(S1_bop, 'E')< 0)
             {
                  if(!Bop_LE_Get(S1_bop, 'L')) *S1_continue = PRZEGRANA;
                  else *S1_continue = POWTORKA;
             }
             else if(S1_stage->S_enemy_nr==0 && S1_stage->S_x>(S1_stage->S_width-481))
             {
                  *S1_continue = PRZEJSCIE;
             }
             else if(!S1_stage->S_time)
             {
                  Bop_Time_Over(S1_bop);
             }
             else if(key()==START || S1_stage->S_anim!=0)
             {
                  Stage_Pause_Menu_Screen(S1_stage);
                  if(S1_stage->S_anim == 0) S1_stage->S_anim = 1;
                  else if(S1_stage->S_anim == 3) S1_stage->S_anim = 0;
                  else if(S1_stage->S_anim == 4) *S1_continue = WYJSCIE;
             }
             else
             {
                  Stage_Logic(S1_stage, S1_bop);
                  Bop_Logic(S1_bop, S1_stage->S_key);
                  //Dog_Logic(S1_stage, S1_dog, S1_bop, 7, (S1_stage->S_x+Bop_MiddleX_Get(S1_bop)));
                  //Kong_Logic(S1_stage, S1_kong, S1_bop, 7, (S1_stage->S_x+Bop_MiddleX_Get(S1_bop)));
             }     
              
             Stage_Background_Draw(S1_stage);
             Stage_HUD_Draw(S1_stage, S1_bop, S1_dog, S1_kong, 0);
             Kong_Draw(S1_kong, S1_bop, 7, S1_stage->S_x, S1_stage->S_y);
             Bop_Draw(S1_bop);
             Dog_Draw(S1_dog, 7, S1_stage->S_x, S1_stage->S_y);
             Stage_Foreground_Draw(S1_stage);
             
             //////////////////////Framerate test//////////////////////////
             if((sceKernelLibcClock()-S1_framerate_start)>=1000000)
             {
                 S1_framerate_start=sceKernelLibcClock();
                 framerateact = framerate;
                 framerate=1;
             }
             else framerate+=1;
             Print_Number(framerateact, 430, 255, 'L');
             Print_Number(S1_stage->S_enemy_nr, 10, 255, 'L');
             /////////////////////////////////////////////////////////////
             
             flipScreen();
     }
     
     Bop_Energy_Fill(S1_bop, 11);
     Print_Number_End();
     Dog_Destroy(S1_dog);
     Kong_Destroy(S1_kong);
     Stage_Destroy(S1_stage);
}
void Stage_2(Bop* S2_bop,int* S2_continue)
{
     int S2_Enemy_X[] = {0, 650, 800, 300, 1400, 1000, 1700};
     int S2_Enemy_Agrr[] = {350, 350, 350, 350, 350, 350, 350};
     int S2_Enemy_activ[] = {0, 350, 550, 550, 1100, 1300, 1350};
     
     Stage* S2_stage = Stage_Create(2);
     Print_Number_Init();
     
     Dog* S2_dog = Dog_Create(7, S2_Enemy_X, S2_Enemy_Agrr, S2_Enemy_activ); 
     S2_Enemy_X[0] = 350;
     S2_Enemy_activ[0] = 0;
     S2_Enemy_X[1] = 700;
     S2_Enemy_activ[1] = 400;
     S2_Enemy_X[2] = 350;
     S2_Enemy_activ[2] = 700;
     S2_Enemy_X[3] = 1000;
     S2_Enemy_activ[3] = 700;
     S2_Enemy_X[4] = 750;
     S2_Enemy_activ[4] = 1100;
     S2_Enemy_X[5] = 1550;
     S2_Enemy_activ[5] = 1200;
     S2_Enemy_X[6] = 1650;
     S2_Enemy_activ[6] = 1300;
     Kong* S2_kong = Kong_Create(7, S2_Enemy_X, S2_Enemy_Agrr, S2_Enemy_activ); 
     //////////////////////Framerate test//////////////////////////
     int framerate = 0;
     int framerateact = 0;
     clock_t S2_framerate_start = 0;
     //////////////////////////////////////////////////////////////
     
     *S2_continue=4;
     S2_stage->S_time_start = sceKernelLibcClock();
     
     while(*S2_continue==4)
     {
             sceDisplayWaitVblankStart();

             if(Bop_LE_Get(S2_bop, 'E')< 0)
             {
                  if(!Bop_LE_Get(S2_bop, 'L')) *S2_continue = PRZEGRANA;
                  else *S2_continue = POWTORKA;
             }
             else if(S2_stage->S_enemy_nr==0 && S2_stage->S_x>(S2_stage->S_width-481))
             {
                  *S2_continue = PRZEJSCIE;
             }
             else if(!S2_stage->S_time)
             {
                  Bop_Time_Over(S2_bop);
             }
             else if(key()==START || S2_stage->S_anim!=0)
             {
                  Stage_Pause_Menu_Screen(S2_stage);
                  if(S2_stage->S_anim == 0) S2_stage->S_anim = 1;
                  else if(S2_stage->S_anim == 3) S2_stage->S_anim = 0;
                  else if(S2_stage->S_anim == 4) *S2_continue = WYJSCIE;
             }
             else
             {
                  Stage_Logic(S2_stage, S2_bop);
                  Bop_Logic(S2_bop, S2_stage->S_key);
                  //Dog_Logic(S2_stage, S2_dog, S2_bop, 7, (S2_stage->S_x+Bop_MiddleX_Get(S2_bop)));
                  //Kong_Logic(S2_stage, S2_kong, S2_bop, 7, (S2_stage->S_x+Bop_MiddleX_Get(S2_bop)));
             }     
              
             Stage_Background_Draw(S2_stage);
             Stage_HUD_Draw(S2_stage, S2_bop, S2_dog, S2_kong, 0);
             Kong_Draw(S2_kong, S2_bop, 7, S2_stage->S_x, S2_stage->S_y);
             Bop_Draw(S2_bop);
             Dog_Draw(S2_dog, 7, S2_stage->S_x, S2_stage->S_y);
             Stage_Foreground_Draw(S2_stage);
             
             //////////////////////Framerate test//////////////////////////
             if((sceKernelLibcClock()-S2_framerate_start)>=1000000)
             {
                 S2_framerate_start=sceKernelLibcClock();
                 framerateact = framerate;
                 framerate=1;
             }
             else framerate+=1;
             Print_Number(framerateact, 430, 255, 'L');
             Print_Number(S2_stage->S_enemy_nr, 10, 255, 'L');
             /////////////////////////////////////////////////////////////
             
             flipScreen();
     }
     
     Bop_Energy_Fill(S2_bop, 11);
     Print_Number_End();
     Dog_Destroy(S2_dog);
     Kong_Destroy(S2_kong);
     Stage_Destroy(S2_stage);
}
void Stage_3(Bop* S3_bop,int* S3_continue)
{
     int S3_Enemy_X[] = {0, 650, 800, 300, 1400, 1000, 1700};
     int S3_Enemy_Agrr[] = {350, 350, 350, 350, 350, 350, 350};
     int S3_Enemy_activ[] = {0, 350, 550, 550, 1100, 1300, 1350};
     
     Stage* S3_stage = Stage_Create(3);
     Print_Number_Init();
     
     Dog* S3_dog = Dog_Create(7, S3_Enemy_X, S3_Enemy_Agrr, S3_Enemy_activ); 
     S3_Enemy_X[0] = 350;
     S3_Enemy_activ[0] = 0;
     S3_Enemy_X[1] = 700;
     S3_Enemy_activ[1] = 400;
     S3_Enemy_X[2] = 350;
     S3_Enemy_activ[2] = 700;
     S3_Enemy_X[3] = 1000;
     S3_Enemy_activ[3] = 700;
     S3_Enemy_X[4] = 750;
     S3_Enemy_activ[4] = 1100;
     S3_Enemy_X[5] = 1550;
     S3_Enemy_activ[5] = 1200;
     S3_Enemy_X[6] = 1650;
     S3_Enemy_activ[6] = 1300;
     Kong* S3_kong = Kong_Create(7, S3_Enemy_X, S3_Enemy_Agrr, S3_Enemy_activ); 
     //////////////////////Framerate test//////////////////////////
     int framerate = 0;
     int framerateact = 0;
     clock_t S3_framerate_start = 0;
     //////////////////////////////////////////////////////////////
     
     *S3_continue=4;
     S3_stage->S_time_start = sceKernelLibcClock();
     
     while(*S3_continue==4)
     {
             sceDisplayWaitVblankStart();

             if(Bop_LE_Get(S3_bop, 'E')< 0)
             {
                  if(!Bop_LE_Get(S3_bop, 'L')) *S3_continue = PRZEGRANA;
                  else *S3_continue = POWTORKA;
             }
             else if(S3_stage->S_enemy_nr==0 && S3_stage->S_x>(S3_stage->S_width-481))
             {
                  *S3_continue = PRZEJSCIE;
             }
             else if(!S3_stage->S_time)
             {
                  Bop_Time_Over(S3_bop);
             }
             else if(key()==START || S3_stage->S_anim!=0)
             {
                  Stage_Pause_Menu_Screen(S3_stage);
                  if(S3_stage->S_anim == 0) S3_stage->S_anim = 1;
                  else if(S3_stage->S_anim == 3) S3_stage->S_anim = 0;
                  else if(S3_stage->S_anim == 4) *S3_continue = WYJSCIE;
             }
             else
             {
                  Stage_Logic(S3_stage, S3_bop);
                  Bop_Logic(S3_bop, S3_stage->S_key);
                  //Dog_Logic(S3_stage, S3_dog, S3_bop, 7, (S3_stage->S_x+Bop_MiddleX_Get(S3_bop)));
                  //Kong_Logic(S3_stage, S3_kong, S3_bop, 7, (S3_stage->S_x+Bop_MiddleX_Get(S3_bop)));
             }     
              
             Stage_Background_Draw(S3_stage);
             Stage_HUD_Draw(S3_stage, S3_bop, S3_dog, S3_kong, 0);
             Kong_Draw(S3_kong, S3_bop, 7, S3_stage->S_x, S3_stage->S_y);
             Bop_Draw(S3_bop);
             Dog_Draw(S3_dog, 7, S3_stage->S_x, S3_stage->S_y);
             Stage_Foreground_Draw(S3_stage);
             
             //////////////////////Framerate test//////////////////////////
             if((sceKernelLibcClock()-S3_framerate_start)>=1000000)
             {
                 S3_framerate_start=sceKernelLibcClock();
                 framerateact = framerate;
                 framerate=1;
             }
             else framerate+=1;
             Print_Number(framerateact, 430, 255, 'L');
             Print_Number(S3_stage->S_enemy_nr, 10, 255, 'L');
             /////////////////////////////////////////////////////////////
             
             flipScreen();
     }
     
     Bop_Energy_Fill(S3_bop, 11);
     Print_Number_End();
     Dog_Destroy(S3_dog);
     Kong_Destroy(S3_kong);
     Stage_Destroy(S3_stage);
}
void Stage_4(Bop* S4_bop,int* S4_continue)
{
     int S4_Enemy_X[] = {0, 650, 800, 300, 1400, 1000, 1700};
     int S4_Enemy_Agrr[] = {350, 350, 350, 350, 350, 350, 350};
     int S4_Enemy_activ[] = {0, 350, 550, 550, 1100, 1300, 1350};
     
     Stage* S4_stage = Stage_Create(4);
     Print_Number_Init();
     
     Dog* S4_dog = Dog_Create(7, S4_Enemy_X, S4_Enemy_Agrr, S4_Enemy_activ); 
     S4_Enemy_X[0] = 350;
     S4_Enemy_activ[0] = 0;
     S4_Enemy_X[1] = 700;
     S4_Enemy_activ[1] = 400;
     S4_Enemy_X[2] = 350;
     S4_Enemy_activ[2] = 700;
     S4_Enemy_X[3] = 1000;
     S4_Enemy_activ[3] = 700;
     S4_Enemy_X[4] = 750;
     S4_Enemy_activ[4] = 1100;
     S4_Enemy_X[5] = 1550;
     S4_Enemy_activ[5] = 1200;
     S4_Enemy_X[6] = 1650;
     S4_Enemy_activ[6] = 1300;
     Kong* S4_kong = Kong_Create(7, S4_Enemy_X, S4_Enemy_Agrr, S4_Enemy_activ); 
     //////////////////////Framerate test//////////////////////////
     int framerate = 0;
     int framerateact = 0;
     clock_t S4_framerate_start = 0;
     //////////////////////////////////////////////////////////////
     
     *S4_continue=4;
     S4_stage->S_time_start = sceKernelLibcClock();
     
     while(*S4_continue==4)
     {
             sceDisplayWaitVblankStart();

             if(Bop_LE_Get(S4_bop, 'E')< 0)
             {
                  if(!Bop_LE_Get(S4_bop, 'L')) *S4_continue = PRZEGRANA;
                  else *S4_continue = POWTORKA;
             }
             else if(S4_stage->S_enemy_nr==0 && S4_stage->S_x>(S4_stage->S_width-481))
             {
                  *S4_continue = PRZEJSCIE;
             }
             else if(!S4_stage->S_time)
             {
                  Bop_Time_Over(S4_bop);
             }
             else if(key()==START || S4_stage->S_anim!=0)
             {
                  Stage_Pause_Menu_Screen(S4_stage);
                  if(S4_stage->S_anim == 0) S4_stage->S_anim = 1;
                  else if(S4_stage->S_anim == 3) S4_stage->S_anim = 0;
                  else if(S4_stage->S_anim == 4) *S4_continue = WYJSCIE;
             }
             else
             {
                  Stage_Logic(S4_stage, S4_bop);
                  Bop_Logic(S4_bop, S4_stage->S_key);
                  //Dog_Logic(S4_stage, S4_dog, S4_bop, 7, (S4_stage->S_x+Bop_MiddleX_Get(S4_bop)));
                  //Kong_Logic(S4_stage, S4_kong, S4_bop, 7, (S4_stage->S_x+Bop_MiddleX_Get(S4_bop)));
             }     
              
             Stage_Background_Draw(S4_stage);
             Stage_HUD_Draw(S4_stage, S4_bop, S4_dog, S4_kong, 0);
             Kong_Draw(S4_kong, S4_bop, 7, S4_stage->S_x, S4_stage->S_y);
             Bop_Draw(S4_bop);
             Dog_Draw(S4_dog, 7, S4_stage->S_x, S4_stage->S_y);
             Stage_Foreground_Draw(S4_stage);
             
             //////////////////////Framerate test//////////////////////////
             if((sceKernelLibcClock()-S4_framerate_start)>=1000000)
             {
                 S4_framerate_start=sceKernelLibcClock();
                 framerateact = framerate;
                 framerate=1;
             }
             else framerate+=1;
             Print_Number(framerateact, 430, 255, 'L');
             Print_Number(S4_stage->S_enemy_nr, 10, 255, 'L');
             /////////////////////////////////////////////////////////////
             
             flipScreen();
     }
     
     Bop_Energy_Fill(S4_bop, 11);
     Print_Number_End();
     Dog_Destroy(S4_dog);
     Kong_Destroy(S4_kong);
     Stage_Destroy(S4_stage);
}
void Stage_5(Bop* S5_bop,int* S5_continue)
{
     int S5_Enemy_X[] = {0, 650, 800, 300, 1400, 1000, 1700};
     int S5_Enemy_Agrr[] = {350, 350, 350, 350, 350, 350, 350};
     int S5_Enemy_activ[] = {0, 350, 550, 550, 1100, 1300, 1350};
     
     Stage* S5_stage = Stage_Create(5);
     Print_Number_Init();
     
     Dog* S5_dog = Dog_Create(7, S5_Enemy_X, S5_Enemy_Agrr, S5_Enemy_activ); 
     S5_Enemy_X[0] = 350;
     S5_Enemy_activ[0] = 0;
     S5_Enemy_X[1] = 700;
     S5_Enemy_activ[1] = 400;
     S5_Enemy_X[2] = 350;
     S5_Enemy_activ[2] = 700;
     S5_Enemy_X[3] = 1000;
     S5_Enemy_activ[3] = 700;
     S5_Enemy_X[4] = 750;
     S5_Enemy_activ[4] = 1100;
     S5_Enemy_X[5] = 1550;
     S5_Enemy_activ[5] = 1200;
     S5_Enemy_X[6] = 1650;
     S5_Enemy_activ[6] = 1300;
     Kong* S5_kong = Kong_Create(7, S5_Enemy_X, S5_Enemy_Agrr, S5_Enemy_activ); 
     //////////////////////Framerate test//////////////////////////
     int framerate = 0;
     int framerateact = 0;
     clock_t S5_framerate_start = 0;
     //////////////////////////////////////////////////////////////
     
     *S5_continue=4;
     S5_stage->S_time_start = sceKernelLibcClock();
     
     while(*S5_continue==4)
     {
             sceDisplayWaitVblankStart();

             if(Bop_LE_Get(S5_bop, 'E')< 0)
             {
                  if(!Bop_LE_Get(S5_bop, 'L')) *S5_continue = PRZEGRANA;
                  else *S5_continue = POWTORKA;
             }
             else if(S5_stage->S_enemy_nr==0 && S5_stage->S_x>(S5_stage->S_width-481))
             {
                  *S5_continue = PRZEJSCIE;
             }
             else if(!S5_stage->S_time)
             {
                  Bop_Time_Over(S5_bop);
             }
             else if(key()==START || S5_stage->S_anim!=0)
             {
                  Stage_Pause_Menu_Screen(S5_stage);
                  if(S5_stage->S_anim == 0) S5_stage->S_anim = 1;
                  else if(S5_stage->S_anim == 3) S5_stage->S_anim = 0;
                  else if(S5_stage->S_anim == 4) *S5_continue = WYJSCIE;
             }
             else
             {
                  Stage_Logic(S5_stage, S5_bop);
                  Bop_Logic(S5_bop, S5_stage->S_key);
                  //Dog_Logic(S5_stage, S5_dog, S5_bop, 7, (S5_stage->S_x+Bop_MiddleX_Get(S5_bop)));
                  //Kong_Logic(S5_stage, S5_kong, S5_bop, 7, (S5_stage->S_x+Bop_MiddleX_Get(S5_bop)));
             }     
              
             Stage_Background_Draw(S5_stage);
             Stage_HUD_Draw(S5_stage, S5_bop, S5_dog, S5_kong, 0);
             Kong_Draw(S5_kong, S5_bop, 7, S5_stage->S_x, S5_stage->S_y);
             Bop_Draw(S5_bop);
             Dog_Draw(S5_dog, 7, S5_stage->S_x, S5_stage->S_y);
             Stage_Foreground_Draw(S5_stage);
             
             //////////////////////Framerate test//////////////////////////
             if((sceKernelLibcClock()-S5_framerate_start)>=1000000)
             {
                 S5_framerate_start=sceKernelLibcClock();
                 framerateact = framerate;
                 framerate=1;
             }
             else framerate+=1;
             Print_Number(framerateact, 430, 255, 'L');
             Print_Number(S5_stage->S_enemy_nr, 10, 255, 'L');
             /////////////////////////////////////////////////////////////
             
             flipScreen();
     }
     
     Bop_Energy_Fill(S5_bop, 11);
     Print_Number_End();
     Dog_Destroy(S5_dog);
     Kong_Destroy(S5_kong);
     Stage_Destroy(S5_stage);
}
void Stage_Logic(Stage* SL_stage, Bop* SL_bop)
{
     if(SL_stage->S_recovery != 0)SL_stage->S_recovery -= 1;
     if(sceKernelLibcClock()-SL_stage->S_time_start>999999)
     {
          SL_stage->S_time_start = sceKernelLibcClock();
          SL_stage->S_time -= 1;
     }
     if(!SL_stage->S_frame)SL_stage->S_key=keyTab(SL_stage->S_key);
             switch(SL_stage->S_key)
             {
                   case LEFT:
                        if(SL_stage->S_x==0) SL_stage->S_key = LEFT_X;
                        else if(Bop_XY_Get(SL_bop, 'X')!=0) SL_stage->S_key = LEFT_X;
                        else SL_stage->S_x -= 2;
                        break;
                   case RIGHT:
                        if(SL_stage->S_x==(SL_stage->S_width-480)) SL_stage->S_key = RIGHT_X;
                        else if(Bop_XY_Get(SL_bop, 'X')!=0) SL_stage->S_key = RIGHT_X;
                        else SL_stage->S_x += 2;
                        break;
                   case CROSS:
                        SL_stage->S_frame += 1;
                        if(SL_stage->S_frame>12)
                        {
                             if(SL_stage->S_frame<15)SL_stage->S_y += 5;
                             else if(SL_stage->S_frame<21)SL_stage->S_y += 4;
                             else if(SL_stage->S_frame<26)SL_stage->S_y += 3;
                             else if(SL_stage->S_frame<31)SL_stage->S_y += 2;
                             else if(SL_stage->S_frame<36)SL_stage->S_y += 1;
                             else if(SL_stage->S_frame<46)SL_stage->S_y += 0;
                             else if(SL_stage->S_frame<51)SL_stage->S_y -= 1;
                             else if(SL_stage->S_frame<56)SL_stage->S_y -= 2;
                             else if(SL_stage->S_frame<61)SL_stage->S_y -= 3;
                             else if(SL_stage->S_frame<67)SL_stage->S_y -= 4;
                             else if(SL_stage->S_frame<69)SL_stage->S_y -= 5;
                             else if(SL_stage->S_frame==80)
                             {
                                  SL_stage->S_frame = 0;
                             }
                        }
                        break;
                   case RIGHT_CROSS:
                   case RIGHT_CROSS_X:
                   case RIGHT_CROSS_XX:
                        SL_stage->S_frame += 1;
                        
                             if(SL_stage->S_x==(SL_stage->S_width-480)) SL_stage->S_key = RIGHT_CROSS_XX;
                             else if(SL_stage->S_x==(SL_stage->S_width-482)) {SL_stage->S_x += 2; SL_stage->S_key = RIGHT_CROSS_X;}
                             else if(Bop_XY_Get(SL_bop, 'X')==-2) {SL_stage->S_x += 2; SL_stage->S_key = RIGHT_CROSS_X;}
                             else if(Bop_XY_Get(SL_bop, 'X')!=0) SL_stage->S_key = RIGHT_CROSS_XX;
                             else {SL_stage->S_x += 4; SL_stage->S_key = RIGHT_CROSS;}
                        
                        if(SL_stage->S_frame>12)
                        {
                             if(SL_stage->S_frame<15)SL_stage->S_y += 5;
                             else if(SL_stage->S_frame<21)SL_stage->S_y += 4;
                             else if(SL_stage->S_frame<26)SL_stage->S_y += 3;
                             else if(SL_stage->S_frame<31)SL_stage->S_y += 2;
                             else if(SL_stage->S_frame<36)SL_stage->S_y += 1;
                             else if(SL_stage->S_frame<46)SL_stage->S_y += 0;
                             else if(SL_stage->S_frame<51)SL_stage->S_y -= 1;
                             else if(SL_stage->S_frame<56)SL_stage->S_y -= 2;
                             else if(SL_stage->S_frame<61)SL_stage->S_y -= 3;
                             else if(SL_stage->S_frame<67)SL_stage->S_y -= 4;
                             else if(SL_stage->S_frame<69)SL_stage->S_y -= 5;
                             else if(SL_stage->S_frame==80)
                             {
                                  SL_stage->S_frame = 0;
                             }
                        }
                        break;
                   case LEFT_CROSS:
                   case LEFT_CROSS_X:
                   case LEFT_CROSS_XX:
                        SL_stage->S_frame += 1;
                        
                             if(SL_stage->S_x==0) SL_stage->S_key = LEFT_CROSS_XX;
                             else if(SL_stage->S_x==2) {SL_stage->S_x -= 2; SL_stage->S_key = LEFT_CROSS_X;}
                             else if(Bop_XY_Get(SL_bop, 'X')==2) {SL_stage->S_x -= 2; SL_stage->S_key = LEFT_CROSS_X;}
                             else if(Bop_XY_Get(SL_bop, 'X')!=0) SL_stage->S_key = LEFT_CROSS_XX;
                             else {SL_stage->S_x -= 4; SL_stage->S_key = LEFT_CROSS;}
                                                
                        if(SL_stage->S_frame>12)
                        {
                             if(SL_stage->S_frame<15)SL_stage->S_y += 5;
                             else if(SL_stage->S_frame<21)SL_stage->S_y += 4;
                             else if(SL_stage->S_frame<26)SL_stage->S_y += 3;
                             else if(SL_stage->S_frame<31)SL_stage->S_y += 2;
                             else if(SL_stage->S_frame<36)SL_stage->S_y += 1;
                             else if(SL_stage->S_frame<46)SL_stage->S_y += 0;
                             else if(SL_stage->S_frame<51)SL_stage->S_y -= 1;
                             else if(SL_stage->S_frame<56)SL_stage->S_y -= 2;
                             else if(SL_stage->S_frame<61)SL_stage->S_y -= 3;
                             else if(SL_stage->S_frame<67)SL_stage->S_y -= 4;
                             else if(SL_stage->S_frame<69)SL_stage->S_y -= 5;
                             else if(SL_stage->S_frame==80)
                             {
                                  SL_stage->S_frame = 0;
                             }
                        }
                        break;
                   default:
                        if(SL_stage->S_key>999)
                        {
                              switch(Bop_FA_Get(SL_bop, 'A'))
                              {
                                      case STOI_PRAWO:
                                      case STOI_LEWO:
                                           SL_stage->S_frame = 0;  
                                           break;
                                           
                              }
                        }
                        else if(SL_stage->S_key>299)
                        {
                             switch(SL_stage->S_key)
                             {
                                      case KEY_KLATA_RIGHT_X:
                                      case KEY_KLATA_RIGHT_XX:
                                      case KEY_KLATA_RIGHT_N:
                                           if(!SL_stage->S_recovery)Stage_Anim_Select(SL_stage, SL_bop, KEY_KLATA, 'R');
                                           break;
                                      case KEY_KLATA_LEFT_XX:
                                      case KEY_KLATA_LEFT_X:
                                      case KEY_KLATA_LEFT_N:
                                           if(!SL_stage->S_recovery)Stage_Anim_Select(SL_stage, SL_bop, KEY_KLATA, 'L');
                                           break;
                                      case KEY_SUPERFLY_RIGHT_X:
                                      case KEY_SUPERFLY_RIGHT_XX:
                                      case KEY_SUPERFLY_RIGHT_N:
                                           if(!SL_stage->S_recovery)Stage_Anim_Select(SL_stage, SL_bop, KEY_SUPERFLY, 'R');
                                           break;
                                      case KEY_SUPERFLY_LEFT_XX:
                                      case KEY_SUPERFLY_LEFT_X:
                                      case KEY_SUPERFLY_LEFT_N:
                                           if(!SL_stage->S_recovery)Stage_Anim_Select(SL_stage, SL_bop, KEY_SUPERFLY, 'L');
                                           break;
                                      case KEY_CHMURKA_LAST_LEFT:
                                           if(!SL_stage->S_recovery)Stage_Anim_Select(SL_stage, SL_bop, KEY_CHMURKA_LAST_LEFT, 'L');
                                           break;
                                      case KEY_CHMURKA_LAST_RIGHT:
                                           if(!SL_stage->S_recovery)Stage_Anim_Select(SL_stage, SL_bop, KEY_CHMURKA_LAST_RIGHT, 'R');
                                           break;
                             }
                        }
                        else if(SL_stage->S_key>99)
                        {
                              switch(Bop_FA_Get(SL_bop, 'A'))
                              {
                                      case STOI_PRAWO:
                                      case KUCA_PRAWO:
                                      case IDZIE_PRAWO:
                                      case IDZIE_X_PRAWO:
                                      case OBRKOP_PRAWO:
                                      case LAPY_PRAWO:
                                      case FISTS_PRAWO:
                                      case DYNKA_PRAWO:
                                      case KOLANO_PRAWO:
                                      case ZIEMIA_PRAWO:
                                      case KLATA_PRAWO:
                                      case SUPERFLY_PRAWO:
                                      case CHMURKA_PRAWO:
                                      case SNIF_PRAWO:
                                      case KARUZELA_PRAWO:
                                           if(!SL_stage->S_recovery)Stage_Anim_Select(SL_stage, SL_bop, Bop_Anim_Select(SL_stage->S_key), 'R');
                                           break;
                                      case STOI_LEWO:
                                      case KUCA_LEWO:
                                      case IDZIE_LEWO:
                                      case IDZIE_X_LEWO:
                                      case OBRKOP_LEWO:
                                      case LAPY_LEWO:
                                      case FISTS_LEWO:
                                      case DYNKA_LEWO:
                                      case KOLANO_LEWO:
                                      case ZIEMIA_LEWO:
                                      case KLATA_LEWO:
                                      case SUPERFLY_LEWO:
                                      case CHMURKA_LEWO:
                                      case SNIF_LEWO:
                                      case KARUZELA_LEWO:
                                           if(!SL_stage->S_recovery)Stage_Anim_Select(SL_stage, SL_bop, Bop_Anim_Revers_Select(SL_stage->S_key), 'L');
                                           break;
                              }
                        }
                        break;
                        
             }
}
void Stage_Anim_Select(Stage* SAS_stage, Bop* SAS_bop, int SAS_key_move, int SAS_LR)
{
     switch(SAS_key_move)
          {
               
               case KEY_SUPERFLY:
               case KEY_SUPERFLY_RIGHT_X:
               case KEY_SUPERFLY_RIGHT_XX:
               case KEY_SUPERFLY_LEFT_XX:
               case KEY_SUPERFLY_LEFT_X:
               case KEY_SUPERFLY_RIGHT_N:
               case KEY_SUPERFLY_LEFT_N:
                    SAS_stage->S_frame += 1;
                    if(SAS_stage->S_frame == 30)
                    {
                         SAS_stage->S_recovery = 30;
                         SAS_stage->S_frame = 0;
                    }
                    else
                    {
                         if(SAS_LR == 'R')
                         {
                              if(SAS_stage->S_x==(SAS_stage->S_width-480)) SAS_stage->S_key = KEY_SUPERFLY_RIGHT_XX;
                              else if(SAS_stage->S_x==(SAS_stage->S_width-482)) {SAS_stage->S_x += 2; SAS_stage->S_key = KEY_SUPERFLY_RIGHT_X;}
                              else if(Bop_XY_Get(SAS_bop, 'X')==-2) {SAS_stage->S_x += 2; SAS_stage->S_key = KEY_SUPERFLY_RIGHT_X;}
                              else if(Bop_XY_Get(SAS_bop, 'X')!=0) SAS_stage->S_key = KEY_SUPERFLY_RIGHT_XX;
                              else {SAS_stage->S_x += 4; SAS_stage->S_key = KEY_SUPERFLY_RIGHT_N;}
                         }
                         else
                         {
                              if(SAS_stage->S_x==0) SAS_stage->S_key = KEY_SUPERFLY_LEFT_XX;
                              else if(SAS_stage->S_x==2) {SAS_stage->S_x -= 2; SAS_stage->S_key = KEY_SUPERFLY_LEFT_X;}
                              else if(Bop_XY_Get(SAS_bop, 'X')==2) {SAS_stage->S_x -= 2; SAS_stage->S_key = KEY_SUPERFLY_LEFT_X;}
                              else if(Bop_XY_Get(SAS_bop, 'X')!=0) SAS_stage->S_key = KEY_SUPERFLY_LEFT_XX;
                              else {SAS_stage->S_x -= 4; SAS_stage->S_key = KEY_SUPERFLY_LEFT_N;}
                         }
                    }
                    break;
               case KEY_OBRKOP:
                    SAS_stage->S_frame += 1;
                    if(SAS_stage->S_frame == 41)
                    {
                         if(Bop_HB_Get(SAS_bop) != 9999)SAS_stage->S_recovery = 30;
                         SAS_stage->S_frame = 0;
                    }
                    break;
               case KEY_PODCIECIE:
                    break;
               case KEY_KLATA:
               case KEY_KLATA_RIGHT_X:
               case KEY_KLATA_RIGHT_XX:
               case KEY_KLATA_LEFT_XX:
               case KEY_KLATA_LEFT_X:
               case KEY_KLATA_RIGHT_N:
               case KEY_KLATA_LEFT_N:
                    SAS_stage->S_frame += 1;
                    if(SAS_stage->S_frame == 21)
                    {
                         SAS_stage->S_recovery = 10;
                         SAS_stage->S_frame = 0;
                         SAS_stage->S_key = 0;
                    }
                    else
                    {
                         if(SAS_LR == 'R')
                         {
                              if(SAS_stage->S_x==(SAS_stage->S_width-480)) SAS_stage->S_key = KEY_KLATA_RIGHT_XX;
                              else if(SAS_stage->S_x==(SAS_stage->S_width-482)) {SAS_stage->S_x += 2; SAS_stage->S_key = KEY_KLATA_RIGHT_X;}
                              else if(Bop_XY_Get(SAS_bop, 'X')==-2) {SAS_stage->S_x += 2; SAS_stage->S_key = KEY_KLATA_RIGHT_X;}
                              else if(Bop_XY_Get(SAS_bop, 'X')!=0) SAS_stage->S_key = KEY_KLATA_RIGHT_XX;
                              else {SAS_stage->S_x += 4; SAS_stage->S_key = KEY_KLATA_RIGHT_N;}
                         }
                         else
                         {
                              if(SAS_stage->S_x==0) SAS_stage->S_key = KEY_KLATA_LEFT_XX;
                              else if(SAS_stage->S_x==2) {SAS_stage->S_x -= 2; SAS_stage->S_key = KEY_KLATA_LEFT_X;}
                              else if(Bop_XY_Get(SAS_bop, 'X')==2) {SAS_stage->S_x -= 2; SAS_stage->S_key = KEY_KLATA_LEFT_X;}
                              else if(Bop_XY_Get(SAS_bop, 'X')!=0) SAS_stage->S_key = KEY_KLATA_LEFT_XX;
                              else {SAS_stage->S_x -= 4; SAS_stage->S_key = KEY_KLATA_LEFT_N;}
                         }
                    }
                    break;
               case KEY_FISTS:
               case KEY_LAPY:
                    SAS_stage->S_frame += 1;
                    if(SAS_stage->S_frame == 21)
                    {
                         if(Bop_HB_Get(SAS_bop) != 9999)SAS_stage->S_recovery = 30;
                         SAS_stage->S_frame = 0;
                    }
                    break;
               case KEY_KOLANO:
               case KEY_DYNKA:
               case KEY_ZIEMIA:
                    SAS_stage->S_frame += 1;
                    if(SAS_stage->S_frame == 41) SAS_stage->S_frame = 0;
                    else if(SAS_stage->S_frame > 10 && Bop_HB_Get(SAS_bop)!= 9999) {SAS_stage->S_recovery = 30; SAS_stage->S_frame = 0;}
                    break;
               case KEY_CHMURKA:
               case KEY_CHMURKA_LAST_RIGHT:
               case KEY_CHMURKA_LAST_LEFT:
                    SAS_stage->S_frame += 1;
                    if(SAS_stage->S_frame > 70){SAS_stage->S_frame = 0; SAS_stage->S_key = 0;}
                    else if(SAS_stage->S_frame > 60);
                    else if(SAS_stage->S_frame > 30)
                    {
                         if(SAS_LR == 'R')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Select(SAS_stage->S_key)!=KEY_CHMURKA) {SAS_stage->S_frame = 61; SAS_stage->S_key = KEY_CHMURKA_LAST_RIGHT;}
                              else if(SAS_stage->S_frame == 51) SAS_stage->S_frame = 31;
                         }
                         else if(SAS_LR == 'L')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Revers_Select(SAS_stage->S_key)!=KEY_CHMURKA) {SAS_stage->S_frame = 61; SAS_stage->S_key = KEY_CHMURKA_LAST_LEFT;}
                              else if(SAS_stage->S_frame == 51) SAS_stage->S_frame = 31;
                         }
                    }
                    else if(SAS_stage->S_frame > 10)
                    {
                         if(Bop_HB_Get(SAS_bop)!= 9999) {SAS_stage->S_recovery = 30; SAS_stage->S_frame = 0; SAS_stage->S_key = 0;}
                         else if(SAS_LR == 'R')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Select(SAS_stage->S_key)!=KEY_CHMURKA) {SAS_stage->S_frame = 0; SAS_stage->S_key = 0;}
                         }
                         else if(SAS_LR == 'L')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Revers_Select(SAS_stage->S_key)!=KEY_CHMURKA) { SAS_stage->S_frame = 0; SAS_stage->S_key = 0;}
                         }
                    }
                    break;
               case KEY_SNIF:
                    SAS_stage->S_frame += 1;
                    if(SAS_stage->S_frame > 10)
                    {
                         if(Bop_HB_Get(SAS_bop)!= 9999) {SAS_stage->S_recovery = 30; SAS_stage->S_frame = 0; SAS_stage->S_key = 0;}
                         else if(SAS_LR == 'R')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Select(SAS_stage->S_key)!=KEY_SNIF) {SAS_stage->S_frame = 0; SAS_stage->S_key = 0;}
                         }
                         else if(SAS_LR == 'L')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Revers_Select(SAS_stage->S_key)!=KEY_SNIF) { SAS_stage->S_frame = 0; SAS_stage->S_key = 0;}
                         }
                         else SAS_stage->S_frame = 11;
                    }
                    break;
               case KEY_KARUZELA:
                    SAS_stage->S_frame += 1;
                    if(SAS_stage->S_frame > 50)
                    {
                         if(SAS_LR == 'R')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Select(SAS_stage->S_key)!=KEY_KARUZELA)
                              {
                                   SAS_stage->S_frame = 0;
                                   SAS_stage->S_key = 0;
                              }
                              else SAS_stage->S_frame = 11;
                         }
                         else if(SAS_LR == 'L')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Revers_Select(SAS_stage->S_key)!=KEY_KARUZELA)
                              {
                                   SAS_stage->S_frame = 0;
                                   SAS_stage->S_key = 0;
                              }
                              else SAS_stage->S_frame = 11;
                         }
                    }
                    else if(SAS_stage->S_frame > 40);
                    else if(SAS_stage->S_frame > 30)
                    {
                         if(SAS_LR == 'R')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Select(SAS_stage->S_key)!=KEY_KARUZELA)
                              {
                                   SAS_stage->S_frame = 0;
                                   SAS_stage->S_key = 0;
                              }
                         }
                         else if(SAS_LR == 'L')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Revers_Select(SAS_stage->S_key)!=KEY_KARUZELA)
                              {
                                   SAS_stage->S_frame = 0;
                                   SAS_stage->S_key = 0;
                              }
                         }
                    }
                    else if(SAS_stage->S_frame > 20);
                    else if(SAS_stage->S_frame > 10)
                    {
                         if(Bop_HB_Get(SAS_bop)!= 9999)
                         {                      
                              SAS_stage->S_recovery = 30;
                              SAS_stage->S_frame = 0;
                              SAS_stage->S_key = 0;
                         }
                         else if(SAS_LR == 'R')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Select(SAS_stage->S_key)!=KEY_KARUZELA)
                              {
                                   SAS_stage->S_frame = 0;
                                   SAS_stage->S_key = 0;
                              }
                         }
                         else if(SAS_LR == 'L')
                         {                      
                              SAS_stage->S_key=keyTab(SAS_stage->S_key);
                              if(Bop_Anim_Revers_Select(SAS_stage->S_key)!=KEY_KARUZELA)
                              {
                                   SAS_stage->S_frame = 0;
                                   SAS_stage->S_key = 0;
                              }
                         }
                    }
                    break;
          }
}
void Stage_Pause_Menu_Screen(Stage* SPMS_stage)
{
     
     switch(keyUp())
     {
           case CROSS:
                SPMS_stage->S_anim+=2;
                break;
     }
     switch(keyDown())
     {
           case UP:
           case DOWN:
                if(SPMS_stage->S_anim==2) SPMS_stage->S_anim-=1;
                else if(SPMS_stage->S_anim==1) SPMS_stage->S_anim+=1;
                break;
     }
}
void Stage_HUD_Draw(Stage* SHD_stage, Bop* SHD_bop, Dog* SHD_dog, Kong* SHD_kong, int SHD_n)
{
     Print_Number(SHD_stage->S_time, 197, 6, 'L');
     blitAlphaImageToScreen(92, 12, 27, 23, SHD_stage->S_hud_image,  162, 1);
     Bop_HUD_Draw(SHD_bop, SHD_stage->S_hud_image, 0);
     
     for(SHD_n=0;SHD_n<5;SHD_n+=1)
     {
          switch(SHD_stage->HUD_enemy_list[SHD_n][0])
          {
               case 0:
                    break;
               case HUD_DOG:
                    Dog_HUD_Draw(SHD_dog, SHD_stage->S_hud_image, SHD_n, 0, SHD_stage->HUD_enemy_list[SHD_n][1]);
                    break;
               case HUD_KONG:
                    Kong_HUD_Draw(SHD_kong, SHD_stage->S_hud_image, SHD_n, 0, SHD_stage->HUD_enemy_list[SHD_n][1]);
                    break;
          }
     }  
}
void Stage_Background_Draw(Stage* SBD_stage)
{
     switch(SBD_stage->S_stage)
     {
           case 1:
                blitImageToScreen(0, 0, 480, 112-SBD_stage->S_y, SBD_stage->S_background_image[0], 0, 160+SBD_stage->S_y);
     
                if(SBD_stage->S_x<480) blitImageToScreen(SBD_stage->S_x, 64-SBD_stage->S_y, 480-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[1], 0, 0);
     
                if(SBD_stage->S_x>0 && SBD_stage->S_x<=480) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[2], 480-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>480 && SBD_stage->S_x<960) blitImageToScreen(SBD_stage->S_x-480, 64-SBD_stage->S_y, 960-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[2], 0, 0);
     
                if(SBD_stage->S_x>480 && SBD_stage->S_x<=960) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-480, 160+SBD_stage->S_y, SBD_stage->S_background_image[3], 960-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>960 && SBD_stage->S_x<1440) blitImageToScreen(SBD_stage->S_x-960, 64-SBD_stage->S_y, 1440-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[3], 0, 0);
     
                if(SBD_stage->S_x>960 && SBD_stage->S_x<=1440) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-960, 160+SBD_stage->S_y, SBD_stage->S_background_image[4], 1440-SBD_stage->S_x, 0);
                break;
           case 2:
                blitImageToScreen(0, 0, 480, 112-SBD_stage->S_y, SBD_stage->S_background_image[0], 0, 160+SBD_stage->S_y);
     
                if(SBD_stage->S_x<480) blitImageToScreen(SBD_stage->S_x, 64-SBD_stage->S_y, 480-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[1], 0, 0);
     
                if(SBD_stage->S_x>0 && SBD_stage->S_x<=480) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[2], 480-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>480 && SBD_stage->S_x<960) blitImageToScreen(SBD_stage->S_x-480, 64-SBD_stage->S_y, 960-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[2], 0, 0);
     
                if(SBD_stage->S_x>480 && SBD_stage->S_x<=960) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-480, 160+SBD_stage->S_y, SBD_stage->S_background_image[3], 960-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>960 && SBD_stage->S_x<1440) blitImageToScreen(SBD_stage->S_x-960, 64-SBD_stage->S_y, 1440-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[3], 0, 0);
     
                if(SBD_stage->S_x>960 && SBD_stage->S_x<=1440) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-960, 160+SBD_stage->S_y, SBD_stage->S_background_image[4], 1440-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>1440 && SBD_stage->S_x<1920) blitImageToScreen(SBD_stage->S_x-1440, 64-SBD_stage->S_y, 1920-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[4], 0, 0);
                
                if(SBD_stage->S_x>1440 && SBD_stage->S_x<=1920) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-1440, 160+SBD_stage->S_y, SBD_stage->S_background_image[5], 1920-SBD_stage->S_x, 0);
                break;
           case 3:
                blitImageToScreen(0, 0, 480, 112-SBD_stage->S_y, SBD_stage->S_background_image[0], 0, 160+SBD_stage->S_y);
     
                if(SBD_stage->S_x<480) blitImageToScreen(SBD_stage->S_x, 64-SBD_stage->S_y, 480-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[1], 0, 0);
     
                if(SBD_stage->S_x>0 && SBD_stage->S_x<=480) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[2], 480-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>480 && SBD_stage->S_x<960) blitImageToScreen(SBD_stage->S_x-480, 64-SBD_stage->S_y, 960-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[2], 0, 0);
     
                if(SBD_stage->S_x>480 && SBD_stage->S_x<=960) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-480, 160+SBD_stage->S_y, SBD_stage->S_background_image[3], 960-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>960 && SBD_stage->S_x<1440) blitImageToScreen(SBD_stage->S_x-960, 64-SBD_stage->S_y, 1440-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[3], 0, 0);
     
                if(SBD_stage->S_x>960 && SBD_stage->S_x<=1440) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-960, 160+SBD_stage->S_y, SBD_stage->S_background_image[4], 1440-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>1440 && SBD_stage->S_x<1920) blitImageToScreen(SBD_stage->S_x-1440, 64-SBD_stage->S_y, 1920-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[4], 0, 0);
                
                if(SBD_stage->S_x>1440 && SBD_stage->S_x<=1920) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-1440, 160+SBD_stage->S_y, SBD_stage->S_background_image[5], 1920-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>1920 && SBD_stage->S_x<2400) blitImageToScreen(SBD_stage->S_x-1920, 64-SBD_stage->S_y, 2400-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[5], 0, 0);
                
                if(SBD_stage->S_x>1920 && SBD_stage->S_x<=2400) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-1920, 160+SBD_stage->S_y, SBD_stage->S_background_image[6], 2400-SBD_stage->S_x, 0);
                break;
           case 4:
           case 5:
                blitImageToScreen(0, 0, 480, 112-SBD_stage->S_y, SBD_stage->S_background_image[0], 0, 160+SBD_stage->S_y);
     
                if(SBD_stage->S_x<480) blitImageToScreen(SBD_stage->S_x, 64-SBD_stage->S_y, 480-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[1], 0, 0);
     
                if(SBD_stage->S_x>0 && SBD_stage->S_x<=480) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[2], 480-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>480 && SBD_stage->S_x<960) blitImageToScreen(SBD_stage->S_x-480, 64-SBD_stage->S_y, 960-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[2], 0, 0);
     
                if(SBD_stage->S_x>480 && SBD_stage->S_x<=960) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-480, 160+SBD_stage->S_y, SBD_stage->S_background_image[3], 960-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>960 && SBD_stage->S_x<1440) blitImageToScreen(SBD_stage->S_x-960, 64-SBD_stage->S_y, 1440-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[3], 0, 0);
     
                if(SBD_stage->S_x>960 && SBD_stage->S_x<=1440) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-960, 160+SBD_stage->S_y, SBD_stage->S_background_image[4], 1440-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>1440 && SBD_stage->S_x<1920) blitImageToScreen(SBD_stage->S_x-1440, 64-SBD_stage->S_y, 1920-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[4], 0, 0);
                
                if(SBD_stage->S_x>1440 && SBD_stage->S_x<=1920) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-1440, 160+SBD_stage->S_y, SBD_stage->S_background_image[5], 1920-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>1920 && SBD_stage->S_x<2400) blitImageToScreen(SBD_stage->S_x-1920, 64-SBD_stage->S_y, 2400-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[5], 0, 0);
                
                if(SBD_stage->S_x>1920 && SBD_stage->S_x<=2400) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-1920, 160+SBD_stage->S_y, SBD_stage->S_background_image[6], 2400-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>2400 && SBD_stage->S_x<2880) blitImageToScreen(SBD_stage->S_x-2400, 64-SBD_stage->S_y, 2880-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[6], 0, 0);
                
                if(SBD_stage->S_x>2400 && SBD_stage->S_x<=2880) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-2400, 160+SBD_stage->S_y, SBD_stage->S_background_image[7], 2880-SBD_stage->S_x, 0);
                else if(SBD_stage->S_x>2880 && SBD_stage->S_x<3360) blitImageToScreen(SBD_stage->S_x-2880, 64-SBD_stage->S_y, 3360-SBD_stage->S_x, 160+SBD_stage->S_y, SBD_stage->S_background_image[7], 0, 0);
                
                if(SBD_stage->S_x>2880 && SBD_stage->S_x<=3360) blitImageToScreen(0, 64-SBD_stage->S_y, SBD_stage->S_x-2880, 160+SBD_stage->S_y, SBD_stage->S_background_image[8], 3360-SBD_stage->S_x, 0);
                break;
     }
}
void Stage_Foreground_Draw(Stage* SFD_stage)
{ 
     switch(SFD_stage->S_stage)
     {
           case 1:
                if(SFD_stage->S_x<=40)                            blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 40-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>40 && SFD_stage->S_x<136)  blitAlphaImageToScreen(SFD_stage->S_x-40, 0, 136-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
                if(SFD_stage->S_x<=136)                           blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 136-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>136 && SFD_stage->S_x<232) blitAlphaImageToScreen(SFD_stage->S_x-136, 0, 232-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
                //////////////////////////////
                if(SFD_stage->S_x<=40)                             blitAlphaImageToScreen(0, 0, 56+SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 424-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>40 && SFD_stage->S_x<=424)  blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 424-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>424 && SFD_stage->S_x<520)  blitAlphaImageToScreen(SFD_stage->S_x-424, 0, 520-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
     
                if(SFD_stage->S_x>40 && SFD_stage->S_x<=136)       blitAlphaImageToScreen(0, 0, SFD_stage->S_x-40, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 520-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>136 && SFD_stage->S_x<=520) blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 520-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>520 && SFD_stage->S_x<616)  blitAlphaImageToScreen(SFD_stage->S_x-520, 0, 616-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
                //////////////////////////
                if(SFD_stage->S_x>444 && SFD_stage->S_x<=540)      blitAlphaImageToScreen(0, 0, SFD_stage->S_x-444, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 924-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>540 && SFD_stage->S_x<=924) blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 924-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>924 && SFD_stage->S_x<1020) blitAlphaImageToScreen(SFD_stage->S_x-924, 0, 1020-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
     
                if(SFD_stage->S_x>540 && SFD_stage->S_x<=636)       blitAlphaImageToScreen(0, 0, SFD_stage->S_x-540, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1020-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>636 && SFD_stage->S_x<=1020) blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1020-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>1020 && SFD_stage->S_x<1116) blitAlphaImageToScreen(SFD_stage->S_x-1020, 0, 1116-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
                //////////////////////////
                if(SFD_stage->S_x>790 && SFD_stage->S_x<=886)       blitAlphaImageToScreen(0, 0, SFD_stage->S_x-790, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1270-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>886 && SFD_stage->S_x<=1270) blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1270-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>1270 && SFD_stage->S_x<1366) blitAlphaImageToScreen(SFD_stage->S_x-1270, 0, 1366-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
                /////////////////////////
                if(SFD_stage->S_x>1044 && SFD_stage->S_x<=1140) blitAlphaImageToScreen(0, 0, SFD_stage->S_x-1044, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1524-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>1140)                    blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1524-SFD_stage->S_x, 184+SFD_stage->S_y);
                if(SFD_stage->S_x>1140 && SFD_stage->S_x<=1236) blitAlphaImageToScreen(0, 0, SFD_stage->S_x-1140, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1620-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>1236)                    blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1620-SFD_stage->S_x, 184+SFD_stage->S_y);
                if(SFD_stage->S_x>1236)                         blitAlphaImageToScreen(0, 0, SFD_stage->S_x-1236, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1716-SFD_stage->S_x, 184+SFD_stage->S_y);
                break;
           case 3:
                if(SFD_stage->S_x<400) blitAlphaImageToScreen(SFD_stage->S_x, 0, 400-SFD_stage->S_x, 96-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 176+SFD_stage->S_y);
                //////////////////////
                if(SFD_stage->S_x>632 && SFD_stage->S_x<=1032)      blitAlphaImageToScreen(0, 0, SFD_stage->S_x-632, 96-SFD_stage->S_y, SFD_stage->S_foreground_image, 1112-SFD_stage->S_x, 176+SFD_stage->S_y);
                else if(SFD_stage->S_x>1032 && SFD_stage->S_x<=1112)  blitAlphaImageToScreen(0, 0, 400, 96-SFD_stage->S_y, SFD_stage->S_foreground_image, 1112-SFD_stage->S_x, 176+SFD_stage->S_y);
                else if(SFD_stage->S_x>1112 && SFD_stage->S_x<1512)  blitAlphaImageToScreen(SFD_stage->S_x-1112, 0, 1512-SFD_stage->S_x, 96-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 176+SFD_stage->S_y);
                //////////////////////
                if(SFD_stage->S_x>1864) blitAlphaImageToScreen(0, 0, SFD_stage->S_x-1864, 96-SFD_stage->S_y, SFD_stage->S_foreground_image, 2344-SFD_stage->S_x, 176+SFD_stage->S_y);
                break;
           case 5:
                if(SFD_stage->S_x<=40)                            blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 40-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>40 && SFD_stage->S_x<136)  blitAlphaImageToScreen(SFD_stage->S_x-40, 0, 136-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
                if(SFD_stage->S_x<=136)                           blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 136-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>136 && SFD_stage->S_x<232) blitAlphaImageToScreen(SFD_stage->S_x-136, 0, 232-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
                //////////////////////////////
                if(SFD_stage->S_x<=40)                             blitAlphaImageToScreen(0, 0, 56+SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 424-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>40 && SFD_stage->S_x<=424)  blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 424-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>424 && SFD_stage->S_x<520)  blitAlphaImageToScreen(SFD_stage->S_x-424, 0, 520-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
     
                if(SFD_stage->S_x>40 && SFD_stage->S_x<=136)       blitAlphaImageToScreen(0, 0, SFD_stage->S_x-40, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 520-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>136 && SFD_stage->S_x<=520) blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 520-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>520 && SFD_stage->S_x<616)  blitAlphaImageToScreen(SFD_stage->S_x-520, 0, 616-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
                //////////////////////////
                if(SFD_stage->S_x>444 && SFD_stage->S_x<=540)      blitAlphaImageToScreen(0, 0, SFD_stage->S_x-444, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 924-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>540 && SFD_stage->S_x<=924) blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 924-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>924 && SFD_stage->S_x<1020) blitAlphaImageToScreen(SFD_stage->S_x-924, 0, 1020-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
     
                if(SFD_stage->S_x>540 && SFD_stage->S_x<=636)       blitAlphaImageToScreen(0, 0, SFD_stage->S_x-540, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1020-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>636 && SFD_stage->S_x<=1020) blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1020-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>1020 && SFD_stage->S_x<1116) blitAlphaImageToScreen(SFD_stage->S_x-1020, 0, 1116-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
                //////////////////////////
                if(SFD_stage->S_x>790 && SFD_stage->S_x<=886)       blitAlphaImageToScreen(0, 0, SFD_stage->S_x-790, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1270-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>886 && SFD_stage->S_x<=1270) blitAlphaImageToScreen(0, 0, 96, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 1270-SFD_stage->S_x, 184+SFD_stage->S_y);
                else if(SFD_stage->S_x>1270 && SFD_stage->S_x<1366) blitAlphaImageToScreen(SFD_stage->S_x-1270, 0, 1366-SFD_stage->S_x, 88-SFD_stage->S_y, SFD_stage->S_foreground_image, 0, 184+SFD_stage->S_y);
                /////////////////////////
                break;
     }
     switch(SFD_stage->S_anim)
     {
          case 1:
               blitAlphaImageToScreen(0, 0, 120, 61, SFD_stage->S_menu_image, 180, 106);
               blitAlphaImageToScreen(0, 61, 120, 16, SFD_stage->S_menu_image, 180, 118);
               break;
          case 2:
               blitAlphaImageToScreen(0, 0, 120, 61, SFD_stage->S_menu_image, 180, 106);
               blitAlphaImageToScreen(0, 77, 120, 16, SFD_stage->S_menu_image, 180, 139);
               break;
               
     }
}
int Stage_XY_Get(Stage* SXYG_stage, int SXYG_xy)
{
     if(SXYG_xy=='x' || SXYG_xy=='X') return SXYG_stage->S_x;
     else if(SXYG_xy=='y' || SXYG_xy=='Y') return SXYG_stage->S_y;
     else return -1;
}

void Stage_HUD_ADD_Normal(Stage* SHAN_stage, int SHAN_enemy, int SHAN_enemy_numb, int SHAN_n)
{
     for(SHAN_n=0;SHAN_n<5;SHAN_n+=1)
     {
          if(SHAN_stage->HUD_enemy_list[SHAN_n][0] == SHAN_enemy && SHAN_stage->HUD_enemy_list[SHAN_n][1] == SHAN_enemy_numb)
          {
               SHAN_enemy = 0;
          }
     }
     for(SHAN_n=0;SHAN_n<5;SHAN_n+=1)
     {
          if(SHAN_stage->HUD_enemy_list[SHAN_n][0] == 0 && SHAN_enemy)
          {
               SHAN_stage->HUD_enemy_list[SHAN_n][0] = SHAN_enemy;
               SHAN_stage->HUD_enemy_list[SHAN_n][1] = SHAN_enemy_numb;
               SHAN_enemy = 0;
          }
     }
}
void Stage_HUD_ADD_Forced(Stage* SHAF_stage, int SHAF_enemy, int SHAF_enemy_numb, int SHAF_n)
{
     for(SHAF_n=0;SHAF_n<5;SHAF_n+=1)
     {
          if(SHAF_stage->HUD_enemy_list[SHAF_n][0] == SHAF_enemy && SHAF_stage->HUD_enemy_list[SHAF_n][1] == SHAF_enemy_numb)
          {
               SHAF_enemy = 0;
          }
     }
     if(SHAF_enemy)
     {
          for(SHAF_n=4;SHAF_n>0;SHAF_n-=1)
          {
               SHAF_stage->HUD_enemy_list[SHAF_n][0] = SHAF_stage->HUD_enemy_list[SHAF_n-1][0];
               SHAF_stage->HUD_enemy_list[SHAF_n][1] = SHAF_stage->HUD_enemy_list[SHAF_n-1][1];
          }
          SHAF_stage->HUD_enemy_list[0][0] = SHAF_enemy;
          SHAF_stage->HUD_enemy_list[0][1] = SHAF_enemy_numb;
     }
}
Stage* Stage_Create(int SC_stagenr)
{
     Preload_Init();
     Preload(0, 4);
     Stage* SC_stage = (Stage*) malloc(sizeof(Stage));
	 if(!SC_stage) return NULL;
	 Preload(1, 4);
     SC_stage->S_hud_image = loadImage("Sety/HUD/hudSet.png");
     SC_stage->S_menu_image = loadImage("resum_exit.png");
     SC_stage->S_background_image[0] = loadImage("Sety/TLA/tloBottom.png");
     switch(SC_stagenr)
     {
           case 1:
                SC_stage->S_background_image[1] = loadImage("Sety/TLA/STAGE_1/stage1Set1.png");
                SC_stage->S_background_image[2] = loadImage("Sety/TLA/STAGE_1/stage1Set2.png");
                Preload(2, 4);
                SC_stage->S_background_image[3] = loadImage("Sety/TLA/STAGE_1/stage1Set3.png");
                SC_stage->S_background_image[4] = loadImage("Sety/TLA/STAGE_1/stage1Set4.png");
                SC_stage->S_background_image[5] = NULL;
                SC_stage->S_background_image[6] = NULL;
                SC_stage->S_background_image[7] = NULL;
                SC_stage->S_background_image[8] = NULL;
                SC_stage->S_foreground_image = loadImage("Sety/TLA/STAGE_1/stage1Set5.png");
                Preload(3, 4);
                SC_stage->S_width = 1812;
                SC_stage->S_enemy_nr = 0;//14;
                SC_stage->S_time = 150;
                break;
           case 2:
                SC_stage->S_background_image[1] = loadImage("Sety/TLA/STAGE_2/stage2Set1.png");
                SC_stage->S_background_image[2] = loadImage("Sety/TLA/STAGE_2/stage2Set2.png");
                Preload(2, 4);
                SC_stage->S_background_image[3] = loadImage("Sety/TLA/STAGE_2/stage2Set3.png");
                SC_stage->S_background_image[4] = loadImage("Sety/TLA/STAGE_2/stage2Set4.png");
                SC_stage->S_background_image[5] = loadImage("Sety/TLA/STAGE_2/stage2Set5.png");
                SC_stage->S_background_image[6] = NULL;
                SC_stage->S_background_image[7] = NULL;
                SC_stage->S_background_image[8] = NULL;
                SC_stage->S_foreground_image = NULL;
                Preload(3, 4);
                SC_stage->S_width = 2336;
                SC_stage->S_enemy_nr = 0;//14;
                SC_stage->S_time = 150;
                break;
           case 3:
                SC_stage->S_background_image[1] = loadImage("Sety/TLA/STAGE_3/stage3Set1.png");
                SC_stage->S_background_image[2] = loadImage("Sety/TLA/STAGE_3/stage3Set2.png");
                Preload(2, 4);
                SC_stage->S_background_image[3] = loadImage("Sety/TLA/STAGE_3/stage3Set3.png");
                SC_stage->S_background_image[4] = loadImage("Sety/TLA/STAGE_3/stage3Set4.png");
                SC_stage->S_background_image[5] = loadImage("Sety/TLA/STAGE_3/stage3Set5.png");
                SC_stage->S_background_image[6] = loadImage("Sety/TLA/STAGE_3/stage3Set6.png");
                SC_stage->S_background_image[7] = NULL;
                SC_stage->S_background_image[8] = NULL;
                SC_stage->S_foreground_image = loadImage("Sety/TLA/STAGE_3/stage3Set7.png");
                Preload(3, 4);
                SC_stage->S_width = 2744;
                SC_stage->S_enemy_nr = 0;//14;
                SC_stage->S_time = 150;
                break;
           case 4:
                SC_stage->S_background_image[1] = loadImage("Sety/TLA/STAGE_4/stage4Set1.png");
                SC_stage->S_background_image[2] = loadImage("Sety/TLA/STAGE_4/stage4Set2.png");
                Preload(2, 4);
                SC_stage->S_background_image[3] = loadImage("Sety/TLA/STAGE_4/stage4Set3.png");
                SC_stage->S_background_image[4] = loadImage("Sety/TLA/STAGE_4/stage4Set4.png");
                SC_stage->S_background_image[5] = loadImage("Sety/TLA/STAGE_4/stage4Set5.png");
                SC_stage->S_background_image[6] = loadImage("Sety/TLA/STAGE_4/stage4Set6.png");
                SC_stage->S_background_image[7] = loadImage("Sety/TLA/STAGE_4/stage4Set7.png");
                SC_stage->S_background_image[8] = loadImage("Sety/TLA/STAGE_4/stage4Set8.png");
                SC_stage->S_foreground_image = NULL;
                Preload(3, 4);
                SC_stage->S_width = 3736;
                SC_stage->S_enemy_nr = 0;//14;
                SC_stage->S_time = 150;
                break;
           case 5:
                SC_stage->S_background_image[1] = loadImage("Sety/TLA/STAGE_5/stage5Set1.png");
                SC_stage->S_background_image[2] = loadImage("Sety/TLA/STAGE_5/stage5Set2.png");
                Preload(2, 4);
                SC_stage->S_background_image[3] = loadImage("Sety/TLA/STAGE_5/stage5Set3.png");
                SC_stage->S_background_image[4] = loadImage("Sety/TLA/STAGE_5/stage5Set4.png");
                SC_stage->S_background_image[5] = loadImage("Sety/TLA/STAGE_5/stage5Set5.png");
                SC_stage->S_background_image[6] = loadImage("Sety/TLA/STAGE_5/stage5Set6.png");
                SC_stage->S_background_image[7] = loadImage("Sety/TLA/STAGE_5/stage5Set7.png");
                SC_stage->S_background_image[8] = loadImage("Sety/TLA/STAGE_5/stage5Set8.png");
                SC_stage->S_foreground_image = loadImage("Sety/TLA/STAGE_1/stage1Set5.png");
                Preload(3, 4);
                SC_stage->S_width = 3688;
                SC_stage->S_enemy_nr = 0;//14;
                SC_stage->S_time = 150;
                break;
     }
     SC_stage->S_stage = SC_stagenr;
     SC_stage->S_anim = 0;
     SC_stage->S_frame = 0;
     SC_stage->S_x = 0;
     SC_stage->S_y = 0;
     SC_stage->S_recovery = 0;
     SC_stage->HUD_enemy_list[0][0] = 0;
     SC_stage->HUD_enemy_list[0][1] = 0;
     SC_stage->HUD_enemy_list[1][0] = 0;
     SC_stage->HUD_enemy_list[1][1] = 0;
     SC_stage->HUD_enemy_list[2][0] = 0;
     SC_stage->HUD_enemy_list[2][1] = 0;
     SC_stage->HUD_enemy_list[3][0] = 0;
     SC_stage->HUD_enemy_list[3][1] = 0;
     SC_stage->HUD_enemy_list[4][0] = 0;
     SC_stage->HUD_enemy_list[4][1] = 0;
     SC_stage->S_key = 0;
     SC_stage->S_time_start = 0;
     Preload(4, 4);
     Preload_End();
     return SC_stage;
}
void Stage_Destroy(Stage* SD_stage)
{
     switch(SD_stage->S_stage)
     {
           case 1:
                freeImage(SD_stage->S_background_image[0]);
                freeImage(SD_stage->S_background_image[1]);
                freeImage(SD_stage->S_background_image[2]);
                freeImage(SD_stage->S_background_image[3]);
                freeImage(SD_stage->S_background_image[4]);
                freeImage(SD_stage->S_foreground_image);
	            break;
           case 2:
                freeImage(SD_stage->S_background_image[0]);
                freeImage(SD_stage->S_background_image[1]);
                freeImage(SD_stage->S_background_image[2]);
                freeImage(SD_stage->S_background_image[3]);
                freeImage(SD_stage->S_background_image[4]);
                freeImage(SD_stage->S_background_image[5]);
                break;
           case 3:
                freeImage(SD_stage->S_background_image[0]);
                freeImage(SD_stage->S_background_image[1]);
                freeImage(SD_stage->S_background_image[2]);
                freeImage(SD_stage->S_background_image[3]);
                freeImage(SD_stage->S_background_image[4]);
                freeImage(SD_stage->S_background_image[5]);
                freeImage(SD_stage->S_background_image[6]);
                freeImage(SD_stage->S_foreground_image);
                break;
           case 4:
                freeImage(SD_stage->S_background_image[0]);
                freeImage(SD_stage->S_background_image[1]);
                freeImage(SD_stage->S_background_image[2]);
                freeImage(SD_stage->S_background_image[3]);
                freeImage(SD_stage->S_background_image[4]);
                freeImage(SD_stage->S_background_image[5]);
                freeImage(SD_stage->S_background_image[6]);
                freeImage(SD_stage->S_background_image[7]);
                freeImage(SD_stage->S_background_image[8]);
                break;
           case 5:
                freeImage(SD_stage->S_background_image[0]);
                freeImage(SD_stage->S_background_image[1]);
                freeImage(SD_stage->S_background_image[2]);
                freeImage(SD_stage->S_background_image[3]);
                freeImage(SD_stage->S_background_image[4]);
                freeImage(SD_stage->S_background_image[5]);
                freeImage(SD_stage->S_background_image[6]);
                freeImage(SD_stage->S_background_image[7]);
                freeImage(SD_stage->S_background_image[8]);
                freeImage(SD_stage->S_foreground_image);
                break;
     }
     freeImage(SD_stage->S_hud_image);
     freeImage(SD_stage->S_menu_image);
     free(SD_stage);
}

void Stage_HUD_DEL(Stage* SHD_stage, int SHD_enemy, int SHD_enemy_numb, int SHD_n)
{
     for(SHD_n=0;SHD_n<5;SHD_n+=1)
     {
          if(SHD_stage->HUD_enemy_list[SHD_n][0] == SHD_enemy && SHD_stage->HUD_enemy_list[SHD_n][1] == SHD_enemy_numb)
          {
               SHD_stage->HUD_enemy_list[SHD_n][0] = 0;
               SHD_stage->HUD_enemy_list[SHD_n][1] = 0;
          }
     }
     for(SHD_n=0;SHD_n<4;SHD_n+=1)
     {
          if(SHD_stage->HUD_enemy_list[SHD_n][0] == 0)
          {
               SHD_stage->HUD_enemy_list[SHD_n][0] = SHD_stage->HUD_enemy_list[SHD_n+1][0];
               SHD_stage->HUD_enemy_list[SHD_n][1] = SHD_stage->HUD_enemy_list[SHD_n+1][1];
               SHD_stage->HUD_enemy_list[SHD_n+1][0] = 0;
               SHD_stage->HUD_enemy_list[SHD_n+1][1] = 0;
          }
     }
}
void Stage_enemy_nr(Stage* SEN_stage)
{
     SEN_stage->S_enemy_nr -= 1;
}
void Stage_Bop_Trafiony(Stage* SBT_stage, int SBT_strength)
{
     SBT_stage->S_recovery = 0;
     SBT_stage->S_key = 9999;
     SBT_stage->S_frame = 1;
}
void Stage_EndGame_Screen(int* SEDS_continue)
{
     Image* SEDS_image_game_over = loadImage("game_over.png");
     Image* SEDS_image_text = loadImage("push_any_button.png");
     int SEDS_n = 1;
     clock_t SEDS_timestart;
     clock_t SEDS_timenow;
              
     blitImageToScreen(0 ,0 ,480 , 272, SEDS_image_game_over, 0, 0);
     if(*SEDS_continue == PRZEJSCIE)blitImageToScreen(0 ,272 ,480 , 35, SEDS_image_game_over, 0, 140);
     flipScreen();
     
     SEDS_timestart = sceKernelLibcClock();
              
     while(!keyDown())
     {
          sceDisplayWaitVblankStart(); 
          SEDS_timenow = sceKernelLibcClock();
                     
          if(SEDS_timenow - SEDS_timestart > 750000)
          {
               blitImageToScreen(0 ,0 ,480 , 272, SEDS_image_game_over, 0, 0);
               if(*SEDS_continue == PRZEJSCIE)blitImageToScreen(0 ,272 ,480 , 35, SEDS_image_game_over, 0, 140);
               
               switch(SEDS_n)
               {
                    case 0:
                         SEDS_n=1;
                         break;
                    case 1:
                         blitImageToScreen(0 ,0 ,342 , 14, SEDS_image_text, 69, 251);
                         SEDS_n =0;
                         break;
               }
               flipScreen();
               SEDS_timestart = sceKernelLibcClock();
          }
     }
     freeImage(SEDS_image_game_over);
     freeImage(SEDS_image_text);
}
