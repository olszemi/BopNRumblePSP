#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <png.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <time.h>
#include <stdio.h>
#include <malloc.h>

#include "enum.h"
#include "kong.h"
#include "graphics.h"
#include "keys.h"
#include "bop.h"
#include "preloader.h"
#include "stage.h"

void Kong_Logic_Left_Position(Stage* KLLP_stage, Kong* KLLP_kong, Bop* KLLP_bop, int KLLP_Count, int KLLP_stageX);
void Kong_Logic_Right_Position(Stage* KLRP_stage, Kong* KLRP_kong, Bop* KLRP_bop, int KLRP_Count, int KLRP_stageX);
void Kong_Attack_Right(Stage* KAR_stage, Kong* KAR_kong, Bop* KAR_bop, int KAR_Count);
void Kong_Attack_Left(Stage* KAL_stage, Kong* KAL_kong, Bop* KAL_bop, int KAL_Count);
void Kong_Check_Colisions(Stage* KCC_stage, Kong* KCC_kong, Bop* KCC_bop, int KCC_Count);

Kong* Kong_Create(int KC_Count, int KC_kongX[], int KC_kong_agrX[], int KC_kong_activ[])
{
     Kong* KC_kong = (Kong*) malloc(sizeof(Kong));
	 if (!KC_kong) return NULL;
	 
     KC_kong->K_image[0] = loadImage("Sety/GORYL/gorylSet1.png");
     KC_kong->K_image[1] = loadImage("Sety/GORYL/gorylSet2.png");
     KC_kong->K_image[2] = loadImage("Sety/GORYL/gorylSet3.png");
     
     KC_kong->K_kong_value = (Kong_Value*) malloc(sizeof(Kong_Value[KC_Count]));
     
     while(KC_Count)
     {
           KC_Count-=1;
	       KC_kong->K_kong_value[KC_Count].KV_anim = 0;
           KC_kong->K_kong_value[KC_Count].KV_frame = 0;
           KC_kong->K_kong_value[KC_Count].KV_x = KC_kongX[KC_Count];
           KC_kong->K_kong_value[KC_Count].KV_y = 0;
           KC_kong->K_kong_value[KC_Count].KV_energy = 8;
           KC_kong->K_kong_value[KC_Count].KV_life = 1;
           KC_kong->K_kong_value[KC_Count].KV_kong_agrX = KC_kong_agrX[KC_Count];
           KC_kong->K_kong_value[KC_Count].KV_kong_hbox[0] = -9999;
           KC_kong->K_kong_value[KC_Count].KV_kong_hbox[1] = -9999;
           KC_kong->K_kong_value[KC_Count].KV_kong_hbox[2] = -9999;
           KC_kong->K_kong_value[KC_Count].KV_kong_activ = KC_kong_activ[KC_Count];
     }
     return KC_kong;
}
void Kong_Destroy(Kong* KD_kong)
{
     freeImage(KD_kong->K_image[0]);
     freeImage(KD_kong->K_image[1]);
     freeImage(KD_kong->K_image[2]);
     free(KD_kong->K_kong_value);
     free(KD_kong);
}
void Kong_Logic(Stage* KL_stage, Kong* KL_kong, Bop* KL_bop, int KL_Count, int KL_stageX)
{
     while(KL_Count)
     {
          KL_Count-=1;
          if(KL_kong->K_kong_value[KL_Count].KV_life)
          {
               if(KL_stageX>KL_kong->K_kong_value[KL_Count].KV_kong_activ)
               {
                    KL_kong->K_kong_value[KL_Count].KV_kong_activ = -9999;
                    if(KL_kong->K_kong_value[KL_Count].KV_x+48>KL_stageX)
                    {
                         if(KL_kong->K_kong_value[KL_Count].KV_x+48-KL_stageX<=KL_kong->K_kong_value[KL_Count].KV_kong_agrX)
                         {
                              Kong_Check_Colisions(KL_stage, KL_kong, KL_bop, KL_Count);
                              Stage_HUD_ADD_Normal(KL_stage, HUD_KONG, KL_Count, 0);
                              Kong_Logic_Right_Position(KL_stage, KL_kong, KL_bop, KL_Count, KL_stageX);
                         }
                         else
                         {
                              Stage_HUD_DEL(KL_stage, HUD_KONG, KL_Count, 0);
                              KL_kong->K_kong_value[KL_Count].KV_frame =0;
                              KL_kong->K_kong_value[KL_Count].KV_anim = 0;
                              KL_kong->K_kong_value[KL_Count].KV_y = 0;
                         }
                    }
                    else
                    {
                         if(KL_stageX-KL_kong->K_kong_value[KL_Count].KV_x-48<=KL_kong->K_kong_value[KL_Count].KV_kong_agrX)
                         {
                              Kong_Check_Colisions(KL_stage, KL_kong, KL_bop, KL_Count);
                              Stage_HUD_ADD_Normal(KL_stage, HUD_KONG, KL_Count, 0);
                              Kong_Logic_Left_Position(KL_stage, KL_kong, KL_bop, KL_Count, KL_stageX);
                         }
                         else
                         {
                              Stage_HUD_DEL(KL_stage, HUD_KONG, KL_Count, 0);
                              KL_kong->K_kong_value[KL_Count].KV_frame =0;
                              KL_kong->K_kong_value[KL_Count].KV_anim = 0;
                              KL_kong->K_kong_value[KL_Count].KV_y = 0;
                         }
                    }
               }
          }
     }
}
void Kong_Logic_Left_Position(Stage* KLLP_stage, Kong* KLLP_kong, Bop* KLLP_bop, int KLLP_Count, int KLLP_stageX)
{
     switch(KLLP_kong->K_kong_value[KLLP_Count].KV_anim)
          {
               case 0:
                    KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_PRAWO;
                    KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                    KLLP_kong->K_kong_value[KLLP_Count].KV_x +=3;
                    break;
               case IDZIE_LEWO:
                    if(KLLP_stageX-KLLP_kong->K_kong_value[KLLP_Count].KV_x-48>=KLLP_kong->K_kong_value[KLLP_Count].KV_kong_agrX-20)
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_PRAWO;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_x +=3;
                    }
                    else
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_frame += 1;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_x -=3;
                         if(KLLP_kong->K_kong_value[KLLP_Count].KV_frame==46) KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                    }
                    break;
               case IDZIE_PRAWO:
                    if(Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-KLLP_kong->K_kong_value[KLLP_Count].KV_x-96<=0)
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_anim = ATAKUJE_PRAWO;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 0;
                         Kong_Attack_Right(KLLP_stage, KLLP_kong, KLLP_bop, KLLP_Count);
                    }
                    else
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_frame += 1;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_x +=3;
                         if(KLLP_kong->K_kong_value[KLLP_Count].KV_frame==46) KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                    }
                    break;
               case ATAKUJE_PRAWO:
                    Kong_Attack_Right(KLLP_stage, KLLP_kong, KLLP_bop, KLLP_Count);
                    break;
               case ATAKUJE_LEWO:
                    Kong_Attack_Left(KLLP_stage, KLLP_kong, KLLP_bop, KLLP_Count);
                    break;
               case LEZY_PRAWO:
                    KLLP_kong->K_kong_value[KLLP_Count].KV_frame += 1;
                    if(KLLP_kong->K_kong_value[KLLP_Count].KV_frame==1)KLLP_kong->K_kong_value[KLLP_Count].KV_x -= 10;
                    if(KLLP_kong->K_kong_value[KLLP_Count].KV_frame>30)
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_x -=14;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_LEWO;
                         if(KLLP_kong->K_kong_value[KLLP_Count].KV_energy<=0)
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_life -= 1;
                              Stage_HUD_DEL(KLLP_stage, HUD_KONG, KLLP_Count, 0);
                              Stage_enemy_nr(KLLP_stage);
                         }
                    }
                    break;
               case TRAFIONY_H_PRAWO:
               case TRAFIONY_H_LEWO:
                    KLLP_kong->K_kong_value[KLLP_Count].KV_frame += 1;
                    if(KLLP_kong->K_kong_value[KLLP_Count].KV_frame>12)
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_y = 0;
                         if(KLLP_kong->K_kong_value[KLLP_Count].KV_energy<=0) KLLP_kong->K_kong_value[KLLP_Count].KV_anim = LEZY_PRAWO;
                         else KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_LEWO;
                    }
                    else if(KLLP_kong->K_kong_value[KLLP_Count].KV_frame>5) KLLP_kong->K_kong_value[KLLP_Count].KV_x -=15;
                    break;
               case DYNKA_PRAWO:
               case DYNKA_LEWO:
                    if(Bop_HB_Get(KLLP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLLP_bop, 'F')<12)
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-136;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_anim = DYNKA_PRAWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLLP_bop, 'F'))
                              {
                                   case 12:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-140;
                                        break;
                                   case 22:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 2;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-70;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_energy -=1;
                                        break;
                                   case 32:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 5;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-140;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_anim = TRAFIONY_H_PRAWO;
                                        break;
                              }
                         }
                    }
                    else
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_x -= 3;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_LEWO;
                    }
                    break;
               case KOLANO_PRAWO:
               case KOLANO_LEWO:
                    if(Bop_HB_Get(KLLP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLLP_bop, 'F')<12)
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-136;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_anim = KOLANO_PRAWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLLP_bop, 'F'))
                              {
                                   case 12:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-140;
                                        break;
                                   case 22:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 5;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-122;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_y = -15;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_anim = TRAFIONY_H_PRAWO;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_energy -=1;
                                        break;
                              }
                         }
                    }
                    else
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_x -= 3;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_LEWO;
                    }
                    break;
               case ZIEMIA_PRAWO:
               case ZIEMIA_LEWO:
                    if(Bop_HB_Get(KLLP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLLP_bop, 'F')<12)
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-136;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_anim = ZIEMIA_PRAWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLLP_bop, 'F'))
                              {
                                   case 12:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-140;
                                        break;
                                   case 22:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-64;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_y = -96;
                                        break;
                                   case 32:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-140;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_y = 0;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_anim = BURIED_PRAWO;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_energy -=2;
                                        break;
                              }
                         }
                    }
                    else
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_x -= 3;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_y = 0;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_LEWO;
                    }
                    break;
               case BURIED_PRAWO:
               case BURIED_LEWO:
                    KLLP_kong->K_kong_value[KLLP_Count].KV_frame += 1;
                    if(KLLP_kong->K_kong_value[KLLP_Count].KV_frame>15)
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_x -= 32;
                         if(KLLP_kong->K_kong_value[KLLP_Count].KV_energy<=0) KLLP_kong->K_kong_value[KLLP_Count].KV_anim = LEZY_PRAWO;
                         else KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_LEWO;
                    }
                    break;
               case SNIF_PRAWO:
               case SNIF_LEWO:
                    if(Bop_HB_Get(KLLP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLLP_bop, 'F')<12)
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-136;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_anim = SNIF_PRAWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLLP_bop, 'F'))
                              {
                                   case 12:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-104;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 2;
                                        if(KLLP_kong->K_kong_value[KLLP_Count].KV_energy)KLLP_kong->K_kong_value[KLLP_Count].KV_energy -=1;
                                        break;
                                   case 22:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-136;
                                        break;
                              }
                         }
                    }
                    else
                    {
                         if(KLLP_kong->K_kong_value[KLLP_Count].KV_energy)
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_x += 3;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_LEWO;
                         }
                         else
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_anim = LEZY_PRAWO;
                         }
                    }
                    break;
               case CHMURKA_PRAWO:
               case CHMURKA_LEWO:
                    if(Bop_HB_Get(KLLP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLLP_bop, 'F')<12)
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-136;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_anim = CHMURKA_PRAWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLLP_bop, 'F'))
                              {
                                   case 12:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-140;
                                        break;
                                   case 22:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-64;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_y = -96;
                                        break;
                                   case 32:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 6;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_y = -10;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-44;
                                        break;
                                   case 37:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 11;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_y = -10;
                                        break;
                                   case 42:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 16;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_y = -10;
                                        break;
                                   case 47:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 21;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_y = -10;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_energy -=1;
                                        break;
                                   case 62:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_anim = LECI_PRAWO;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x += 10;
                                        break;
                              }
                         }
                    }
                    else
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-99;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_y = 0;
                         KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_LEWO;
                    }
                    break;
               case LECI_PRAWO:
                    KLLP_kong->K_kong_value[KLLP_Count].KV_frame += 1;
                    KLLP_kong->K_kong_value[KLLP_Count].KV_x += 10;
                    if(KLLP_kong->K_kong_value[KLLP_Count].KV_frame>25) KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 6;
                    if(KLLP_kong->K_kong_value[KLLP_Count].KV_x>KLLP_stageX+250)
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_energy -=4;
                         if(KLLP_kong->K_kong_value[KLLP_Count].KV_energy<=0)
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_life -= 1;
                              Stage_HUD_DEL(KLLP_stage, HUD_KONG, KLLP_Count, 0);
                              Stage_enemy_nr(KLLP_stage);
                         }
                         else
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_y = 0;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_LEWO;
                         }
                    }
                    break;
               case LECI_LEWO:
                    KLLP_kong->K_kong_value[KLLP_Count].KV_frame += 1;
                    KLLP_kong->K_kong_value[KLLP_Count].KV_x -= 10;
                    if(KLLP_kong->K_kong_value[KLLP_Count].KV_frame>25) KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 6;
                    if(KLLP_kong->K_kong_value[KLLP_Count].KV_x<KLLP_stageX-346)
                    {
                         KLLP_kong->K_kong_value[KLLP_Count].KV_energy -=4;
                         if(KLLP_kong->K_kong_value[KLLP_Count].KV_energy<=0)
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_life -= 1;
                              Stage_HUD_DEL(KLLP_stage, HUD_KONG, KLLP_Count, 0);
                              Stage_enemy_nr(KLLP_stage);
                         }
                         else
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_y = 0;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_anim = IDZIE_PRAWO;
                         }
                    }
                    break;
               case KARUZELA_PRAWO:
               case KARUZELA_LEWO:
                    if(Bop_HB_Get(KLLP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLLP_bop, 'F')<11)
                         {
                              KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-136;
                              KLLP_kong->K_kong_value[KLLP_Count].KV_anim = KARUZELA_PRAWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLLP_bop, 'F'))
                              {
                                   case 112://
                                   case 32:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-140;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 1;
                                        if(KLLP_kong->K_kong_value[KLLP_Count].KV_energy)KLLP_kong->K_kong_value[KLLP_Count].KV_energy -=1;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_anim = KARUZELA_PRAWO;
                                        break;
                                   case 122:
                                   case 42:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 2;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-30;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_anim = KARUZELA_LEWO;
                                        break;
                                   case 22:
                                   case 142:
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 2;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_x = Bop_BB_Get(KLLP_bop, 'X', 0)+Stage_XY_Get(KLLP_stage, 'X')-30;
                                        KLLP_kong->K_kong_value[KLLP_Count].KV_anim = KARUZELA_PRAWO;
                                        break;
                              }
                         }
                    }
                    else
                    {
                              if(KLLP_kong->K_kong_value[KLLP_Count].KV_anim == KARUZELA_LEWO)
                              {
                                   KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 6;
                                   KLLP_kong->K_kong_value[KLLP_Count].KV_x += 15;
                                   KLLP_kong->K_kong_value[KLLP_Count].KV_anim = TRAFIONY_H_LEWO;
                              }
                              else
                              {
                                   KLLP_kong->K_kong_value[KLLP_Count].KV_frame = 6;
                                   KLLP_kong->K_kong_value[KLLP_Count].KV_x -= 15;
                                   KLLP_kong->K_kong_value[KLLP_Count].KV_anim = TRAFIONY_H_PRAWO;
                              }       
                    }
                    break;
          }
}
void Kong_Logic_Right_Position(Stage* KLRP_stage, Kong* KLRP_kong, Bop* KLRP_bop, int KLRP_Count, int KLRP_stageX)
{
     switch(KLRP_kong->K_kong_value[KLRP_Count].KV_anim)
          {
               case 0:
                    KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_LEWO;
                    KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                    KLRP_kong->K_kong_value[KLRP_Count].KV_x -=3;
                    break;
               case IDZIE_PRAWO:
                    if(KLRP_kong->K_kong_value[KLRP_Count].KV_x+48-KLRP_stageX>=KLRP_kong->K_kong_value[KLRP_Count].KV_kong_agrX-20)
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_LEWO;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_x -=3;
                    }
                    else
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_frame += 1;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_x +=3;
                         if(KLRP_kong->K_kong_value[KLRP_Count].KV_frame==46) KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                    }
                    break;
               case IDZIE_LEWO:
                    if(KLRP_kong->K_kong_value[KLRP_Count].KV_x-Bop_BB_Get(KLRP_bop, 'X', 1)-Stage_XY_Get(KLRP_stage, 'X')<=0)
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_anim = ATAKUJE_LEWO;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 0;
                         Kong_Attack_Left(KLRP_stage, KLRP_kong, KLRP_bop, KLRP_Count);
                    }
                    else
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_frame += 1;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_x -=3;
                         if(KLRP_kong->K_kong_value[KLRP_Count].KV_frame==46) KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                    }
                    break;
               case ATAKUJE_PRAWO:
                    Kong_Attack_Right(KLRP_stage, KLRP_kong, KLRP_bop, KLRP_Count);
                    break;
               case ATAKUJE_LEWO:
                    Kong_Attack_Left(KLRP_stage, KLRP_kong, KLRP_bop, KLRP_Count);
                    break;
               case LEZY_PRAWO:
                    KLRP_kong->K_kong_value[KLRP_Count].KV_frame += 1;
                    if(KLRP_kong->K_kong_value[KLRP_Count].KV_frame==1)KLRP_kong->K_kong_value[KLRP_Count].KV_x += 10;
                    if(KLRP_kong->K_kong_value[KLRP_Count].KV_frame>30)
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_x +=14;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_PRAWO;
                         if(KLRP_kong->K_kong_value[KLRP_Count].KV_energy<=0)
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_life -= 1;
                              Stage_HUD_DEL(KLRP_stage, HUD_KONG, KLRP_Count, 0);
                              Stage_enemy_nr(KLRP_stage);
                         }
                    }
                    break;
               case TRAFIONY_H_PRAWO:
               case TRAFIONY_H_LEWO:
                    KLRP_kong->K_kong_value[KLRP_Count].KV_frame += 1;
                    if(KLRP_kong->K_kong_value[KLRP_Count].KV_frame>12)
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_y = 0;
                         if(KLRP_kong->K_kong_value[KLRP_Count].KV_energy<=0) KLRP_kong->K_kong_value[KLRP_Count].KV_anim = LEZY_PRAWO;
                         else KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_PRAWO;
                    }
                    else if(KLRP_kong->K_kong_value[KLRP_Count].KV_frame>5) KLRP_kong->K_kong_value[KLRP_Count].KV_x +=15;
                    break;
               case DYNKA_LEWO:
               case DYNKA_PRAWO:
                    if(Bop_HB_Get(KLRP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLRP_bop, 'F')<12)
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+40;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_anim = DYNKA_LEWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLRP_bop, 'F'))
                              {
                                   case 12:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+44;
                                        break;
                                   case 22:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 2;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')-26;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_energy -=1;
                                        break;
                                   case 32:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 5;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+44;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_anim = TRAFIONY_H_LEWO;
                                        break;
                              }
                         }
                    }
                    else
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_x += 3;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_PRAWO;
                    }
                    break;
               case KOLANO_PRAWO:
               case KOLANO_LEWO:
                    if(Bop_HB_Get(KLRP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLRP_bop, 'F')<12)
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+40;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_anim = KOLANO_LEWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLRP_bop, 'F'))
                              {
                                   case 12:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+44;
                                        break;
                                   case 22:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 5;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+26;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_y = -15;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_anim = TRAFIONY_H_LEWO;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_energy -=1;
                                        break;
                              }
                         }
                    }
                    else
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_x += 3;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_PRAWO;
                    }
                    break;
               case ZIEMIA_PRAWO:
               case ZIEMIA_LEWO:
                    if(Bop_HB_Get(KLRP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLRP_bop, 'F')<12)
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+40;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_anim = ZIEMIA_LEWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLRP_bop, 'F'))
                              {
                                   case 12:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+44;
                                        break;
                                   case 22:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')-32;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_y = -96;
                                        break;
                                   case 32:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+44;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_y = 0;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_anim = BURIED_LEWO;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_energy -=2;
                                        break;
                              }
                         }
                    }
                    else
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_x += 3;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_y = 0;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_PRAWO;
                    }
                    break;
               case CHMURKA_PRAWO:
               case CHMURKA_LEWO:
                    if(Bop_HB_Get(KLRP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLRP_bop, 'F')<12)
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+40;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_anim = CHMURKA_LEWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLRP_bop, 'F'))
                              {
                                   case 12:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+44;
                                        break;
                                   case 22:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')-32;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_y = -96;
                                        break;
                                   case 32:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 6;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_y = -10;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 0)+Stage_XY_Get(KLRP_stage, 'X')-44;
                                        break;
                                   case 37:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 11;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_y = -10;
                                        break;
                                   case 42:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 16;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_y = -10;
                                        break;
                                   case 47:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 21;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_y = -10;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_energy -=1;
                                        break;
                                   case 62:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_anim = LECI_LEWO;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x -= 10;
                                        break;
                              }
                         }
                    }
                    else
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+3;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_y = 0;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_PRAWO;
                    }
                    break;
               case LECI_PRAWO:
                    KLRP_kong->K_kong_value[KLRP_Count].KV_frame += 1;
                    KLRP_kong->K_kong_value[KLRP_Count].KV_x += 10;
                    if(KLRP_kong->K_kong_value[KLRP_Count].KV_frame>25) KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 6;
                    if(KLRP_kong->K_kong_value[KLRP_Count].KV_x>KLRP_stageX+250)
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_energy -=4;
                         if(KLRP_kong->K_kong_value[KLRP_Count].KV_energy<=0)
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_life -= 1;
                              Stage_HUD_DEL(KLRP_stage, HUD_KONG, KLRP_Count, 0);
                              Stage_enemy_nr(KLRP_stage);
                         }
                         else
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_y = 0;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_LEWO;
                         }
                    }
                    break;
               case LECI_LEWO:
                    KLRP_kong->K_kong_value[KLRP_Count].KV_frame += 1;
                    KLRP_kong->K_kong_value[KLRP_Count].KV_x -= 10;
                    if(KLRP_kong->K_kong_value[KLRP_Count].KV_frame>25) KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 6;
                    if(KLRP_kong->K_kong_value[KLRP_Count].KV_x<KLRP_stageX-346)
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_energy -=4;
                         if(KLRP_kong->K_kong_value[KLRP_Count].KV_energy<=0)
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_life -= 1;
                              Stage_HUD_DEL(KLRP_stage, HUD_KONG, KLRP_Count, 0);
                              Stage_enemy_nr(KLRP_stage);
                         }
                         else
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_y = 0;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_PRAWO;
                         }
                    }
                    break;
               case BURIED_PRAWO:
               case BURIED_LEWO:
                    KLRP_kong->K_kong_value[KLRP_Count].KV_frame += 1;
                    if(KLRP_kong->K_kong_value[KLRP_Count].KV_frame>15)
                    {
                         KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                         KLRP_kong->K_kong_value[KLRP_Count].KV_x += 32;
                         if(KLRP_kong->K_kong_value[KLRP_Count].KV_energy<=0) KLRP_kong->K_kong_value[KLRP_Count].KV_anim = LEZY_PRAWO;
                         else KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_PRAWO;
                    }
                    break;
               case SNIF_PRAWO:
               case SNIF_LEWO:
                    if(Bop_HB_Get(KLRP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLRP_bop, 'F')<12)
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+40;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_anim = SNIF_LEWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLRP_bop, 'F'))
                              {
                                   case 12:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+8;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 2;
                                        if(KLRP_kong->K_kong_value[KLRP_Count].KV_energy)KLRP_kong->K_kong_value[KLRP_Count].KV_energy -=1;
                                        break;
                                   case 22:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+40;
                                        break;
                              }
                         }
                    }
                    else
                    {
                         if(KLRP_kong->K_kong_value[KLRP_Count].KV_energy)
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_x += 3;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_anim = IDZIE_PRAWO;
                         }
                         else
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_anim = LEZY_PRAWO;
                         }
                    }
                    break;
               case KARUZELA_PRAWO:
               case KARUZELA_LEWO:
                    if(Bop_HB_Get(KLRP_bop)!=-9999)
                    {
                         if(Bop_FA_Get(KLRP_bop, 'F')<11)
                         {
                              KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+40;
                              KLRP_kong->K_kong_value[KLRP_Count].KV_anim = KARUZELA_LEWO;
                         }
                         else
                         {
                              switch(Bop_FA_Get(KLRP_bop, 'F'))
                              {
                                   case 12:
                                   case 132:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 1)+Stage_XY_Get(KLRP_stage, 'X')+44;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 1;
                                        if(KLRP_kong->K_kong_value[KLRP_Count].KV_energy)KLRP_kong->K_kong_value[KLRP_Count].KV_energy -=1;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_anim = KARUZELA_LEWO;
                                        break;
                                   case 122:
                                   case 42:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 0)+Stage_XY_Get(KLRP_stage, 'X')-30;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 2;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_anim = KARUZELA_LEWO;
                                        break;
                                   case 22:
                                   case 142:
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_x = Bop_BB_Get(KLRP_bop, 'X', 0)+Stage_XY_Get(KLRP_stage, 'X')-30;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 2;
                                        KLRP_kong->K_kong_value[KLRP_Count].KV_anim = KARUZELA_PRAWO;
                                        break;
                              }
                         }
                    }
                    else
                    {
                              if(KLRP_kong->K_kong_value[KLRP_Count].KV_anim == KARUZELA_LEWO)
                              {
                                   KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 6;
                                   KLRP_kong->K_kong_value[KLRP_Count].KV_x += 15;
                                   KLRP_kong->K_kong_value[KLRP_Count].KV_anim = TRAFIONY_H_LEWO;
                              }
                              else
                              {
                                   KLRP_kong->K_kong_value[KLRP_Count].KV_frame = 6;
                                   KLRP_kong->K_kong_value[KLRP_Count].KV_x -= 15;
                                   KLRP_kong->K_kong_value[KLRP_Count].KV_anim = TRAFIONY_H_PRAWO;
                              }                    
                    }
                    break;
          }
}
void Kong_Attack_Right(Stage* KAR_stage, Kong* KAR_kong, Bop* KAR_bop, int KAR_Count)
{
     KAR_kong->K_kong_value[KAR_Count].KV_frame += 1;
     switch(KAR_kong->K_kong_value[KAR_Count].KV_frame)
     {
          case 1:
          case 31:
               KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[0] = KAR_kong->K_kong_value[KAR_Count].KV_x-Stage_XY_Get(KAR_stage, 'X')+140;
               KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[1] = KAR_kong->K_kong_value[KAR_Count].KV_y+Stage_XY_Get(KAR_stage, 'Y')+126;
               KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[2] = KAR_kong->K_kong_value[KAR_Count].KV_y+Stage_XY_Get(KAR_stage, 'Y')+142;
               break;
          case 16:
          case 46:
               KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[0] = KAR_kong->K_kong_value[KAR_Count].KV_x-Stage_XY_Get(KAR_stage, 'X')+132;
               KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[1] = KAR_kong->K_kong_value[KAR_Count].KV_y+Stage_XY_Get(KAR_stage, 'Y')+126;
               KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[2] = KAR_kong->K_kong_value[KAR_Count].KV_y+Stage_XY_Get(KAR_stage, 'Y')+142;
               break;
          case 61:
               KAR_kong->K_kong_value[KAR_Count].KV_frame = 1;
               KAR_kong->K_kong_value[KAR_Count].KV_x +=3;
               KAR_kong->K_kong_value[KAR_Count].KV_anim = IDZIE_LEWO;
               KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[0] = -9999;
               KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[1] = -9999;
               KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[2] = -9999;
               break;
     }
     if(KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[0]!=9999)
     {
          if(KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[0]!=-9999)
          {     
               if(Bop_XY_Get(KAR_bop, 'Y')<72)
               {
                    if(Bop_Check_Hit(KAR_stage, KAR_bop, KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox, 2)==9999) KAR_kong->K_kong_value[KAR_Count].KV_kong_hbox[0] = 9999;
               }
          }
     }
}
void Kong_Attack_Left(Stage* KAL_stage, Kong* KAL_kong, Bop* KAL_bop, int KAL_Count)
{
     KAL_kong->K_kong_value[KAL_Count].KV_frame += 1;
     switch(KAL_kong->K_kong_value[KAL_Count].KV_frame)
     {
          case 1:
          case 31:
               KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[0] = KAL_kong->K_kong_value[KAL_Count].KV_x-Stage_XY_Get(KAL_stage, 'X')-44;
               KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[1] = KAL_kong->K_kong_value[KAL_Count].KV_y+Stage_XY_Get(KAL_stage, 'Y')+126;
               KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[2] = KAL_kong->K_kong_value[KAL_Count].KV_y+Stage_XY_Get(KAL_stage, 'Y')+142;
               break;
          case 16:
          case 46:
               KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[0] = KAL_kong->K_kong_value[KAL_Count].KV_x-Stage_XY_Get(KAL_stage, 'X')-36;
               KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[1] = KAL_kong->K_kong_value[KAL_Count].KV_y+Stage_XY_Get(KAL_stage, 'Y')+126;
               KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[2] = KAL_kong->K_kong_value[KAL_Count].KV_y+Stage_XY_Get(KAL_stage, 'Y')+142;
               break;
          case 61:
               KAL_kong->K_kong_value[KAL_Count].KV_frame = 1;
               KAL_kong->K_kong_value[KAL_Count].KV_x +=3;
               KAL_kong->K_kong_value[KAL_Count].KV_anim = IDZIE_PRAWO;
               KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[0] = -9999;
               KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[1] = -9999;
               KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[2] = -9999;
     }
     if(KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[0]!=9999)
     {
          if(KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[0]!=-9999)
          {     
               if(Bop_XY_Get(KAL_bop, 'Y')<72)
               {
                    if(Bop_Check_Hit(KAL_stage, KAL_bop, KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox, 2)==9999) KAL_kong->K_kong_value[KAL_Count].KV_kong_hbox[0] = 9999;
               }
          }
     }
}
void Kong_Check_Colisions(Stage* KCC_stage, Kong* KCC_kong, Bop* KCC_bop, int KCC_Count)
{
     switch(Bop_FA_Get(KCC_bop, 'A'))
     {
          case PODCIECIE_PRAWO:
          case PODCIECIE_LEWO:
               switch(KCC_kong->K_kong_value[KCC_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                    case IDZIE_LEWO:
                    case ATAKUJE_PRAWO:
                    case ATAKUJE_LEWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 0;
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = LEZY_PRAWO;
                         }
                         break;
               }
          case OBRKOP_PRAWO:
          case OBRKOP_LEWO:
               switch(KCC_kong->K_kong_value[KCC_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                    case ATAKUJE_PRAWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_energy -= 3;
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 0;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = TRAFIONY_H_PRAWO;
                         }
                         break;
                    case ATAKUJE_LEWO:
                    case IDZIE_LEWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_energy -= 3;
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 0;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = TRAFIONY_H_LEWO;
                         }
                         break;
               }
               break;
          case KLATA_PRAWO:
          case KLATA_LEWO:
          case SUPERFLY_PRAWO:
          case SUPERFLY_LEWO:
               switch(KCC_kong->K_kong_value[KCC_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                    case ATAKUJE_PRAWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_energy -= 1;
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 0;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = TRAFIONY_H_PRAWO;
                         }
                         break;
                    case ATAKUJE_LEWO:
                    case IDZIE_LEWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_energy -= 1;
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 0;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = TRAFIONY_H_LEWO;
                         }
                         break;
               }
               break;
          case FISTS_PRAWO:
          case FISTS_LEWO:
               switch(KCC_kong->K_kong_value[KCC_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                    case ATAKUJE_PRAWO:
                    case TRAFIONY_H_PRAWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_energy -= 1;
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 0;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = TRAFIONY_H_PRAWO;
                         }
                         break;
                    case ATAKUJE_LEWO:
                    case IDZIE_LEWO:
                    case TRAFIONY_H_LEWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_energy -= 1;
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 0;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = TRAFIONY_H_LEWO;
                         }
                         break;
               }
               break;
          case LAPY_PRAWO:
          case LAPY_LEWO:
               switch(KCC_kong->K_kong_value[KCC_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                    case ATAKUJE_PRAWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_energy -= 2;
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 0;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = TRAFIONY_H_PRAWO;
                         }
                         break;
                    case ATAKUJE_LEWO:
                    case IDZIE_LEWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_energy -= 2;
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 0;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = TRAFIONY_H_LEWO;
                         }
                         break;
               }
               break;
          case DYNKA_PRAWO:
          case DYNKA_LEWO:
               switch(KCC_kong->K_kong_value[KCC_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                    case ATAKUJE_PRAWO:
                    case ATAKUJE_LEWO:
                    case IDZIE_LEWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 1;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = DYNKA_PRAWO;
                         }
                         break;
               }
               break;
          case KOLANO_PRAWO:
          case KOLANO_LEWO:
               switch(KCC_kong->K_kong_value[KCC_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                    case ATAKUJE_PRAWO:
                    case ATAKUJE_LEWO:
                    case IDZIE_LEWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 1;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = KOLANO_PRAWO;
                         }
                         break;
               }
               break;
          case ZIEMIA_PRAWO:
          case ZIEMIA_LEWO:
               switch(KCC_kong->K_kong_value[KCC_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                    case ATAKUJE_PRAWO:
                    case ATAKUJE_LEWO:
                    case IDZIE_LEWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 1;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = ZIEMIA_PRAWO;
                         }
                         break;
               }
               break;
          case SNIF_PRAWO:
          case SNIF_LEWO:
               switch(KCC_kong->K_kong_value[KCC_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                    case ATAKUJE_PRAWO:
                    case ATAKUJE_LEWO:
                    case IDZIE_LEWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 1;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = SNIF_PRAWO;
                         }
                         break;
               }
               break;
          case KARUZELA_PRAWO:
          case KARUZELA_LEWO:
               switch(KCC_kong->K_kong_value[KCC_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                    case ATAKUJE_PRAWO:
                    case ATAKUJE_LEWO:
                    case IDZIE_LEWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 1;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = KARUZELA_PRAWO;
                         }
                         break;
               }
               break;
          case CHMURKA_PRAWO:
          case CHMURKA_LEWO:
               switch(KCC_kong->K_kong_value[KCC_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                    case ATAKUJE_PRAWO:
                    case ATAKUJE_LEWO:
                    case IDZIE_LEWO:
                         if((Bop_HB_Get(KCC_bop)>(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X')) &&
                             Bop_HB_Get(KCC_bop)<(KCC_kong->K_kong_value[KCC_Count].KV_x-Stage_XY_Get(KCC_stage, 'X'))+96))
                         {
                              KCC_kong->K_kong_value[KCC_Count].KV_frame = 1;
                              Bop_Hit_Enemy(KCC_bop);
                              KCC_kong->K_kong_value[KCC_Count].KV_anim = CHMURKA_PRAWO;
                         }
                         break;
               }
               break;
     }
}
void Kong_Draw(Kong* KD_kong, Bop* KD_bop, int KD_Count, int KD_stageX, int KD_stageY)
{
     while(KD_Count)
     {
          KD_Count-=1;
          if(KD_kong->K_kong_value[KD_Count].KV_life)
          {
               switch(KD_kong->K_kong_value[KD_Count].KV_anim)
               {
                    case IDZIE_PRAWO:
                         if(KD_kong->K_kong_value[KD_Count].KV_frame<16)      blitAlphaImageToScreen(0, 0, 96, 136, KD_kong->K_image[0], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 104+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame<31) blitAlphaImageToScreen(288, 0, 96, 144, KD_kong->K_image[2], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 96+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame<46) blitAlphaImageToScreen(0, 136, 96, 136, KD_kong->K_image[0], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 104+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case IDZIE_LEWO:
                         if(KD_kong->K_kong_value[KD_Count].KV_frame<16)      blitAlphaImageToScreen(96, 0, 96, 136, KD_kong->K_image[0], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 104+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame<31) blitAlphaImageToScreen(384, 0, 96, 144, KD_kong->K_image[2], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 96+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame<46) blitAlphaImageToScreen(96, 136, 96, 136, KD_kong->K_image[0], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 104+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case ATAKUJE_PRAWO:
                         if(KD_kong->K_kong_value[KD_Count].KV_frame<16)      blitAlphaImageToScreen(0, 0, 144, 164, KD_kong->K_image[2], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame<31) blitAlphaImageToScreen(0, 0, 136, 164, KD_kong->K_image[1], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame<46) blitAlphaImageToScreen(0, 0, 144, 164, KD_kong->K_image[2], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame<61) blitAlphaImageToScreen(0, 0, 136, 164, KD_kong->K_image[1], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case ATAKUJE_LEWO:
                         if(KD_kong->K_kong_value[KD_Count].KV_frame<16)      blitAlphaImageToScreen(144, 0, 144, 164, KD_kong->K_image[2], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX-48, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame<31) blitAlphaImageToScreen(136, 0, 136, 164, KD_kong->K_image[1], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX-40, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame<46) blitAlphaImageToScreen(144, 0, 144, 164, KD_kong->K_image[2], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX-48, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame<61) blitAlphaImageToScreen(136, 0, 136, 164, KD_kong->K_image[1], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX-40, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case LEZY_PRAWO:
                         blitAlphaImageToScreen(192, 136, 96, 84, KD_kong->K_image[0], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 156+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case ZLAPANY_PRAWO:
                         blitAlphaImageToScreen(192, 0, 96, 136, KD_kong->K_image[0], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 104+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case ZLAPANY_LEWO:
                         blitAlphaImageToScreen(288, 0, 96, 136, KD_kong->K_image[0], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 104+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case TRAFIONY_H_PRAWO:
                         blitAlphaImageToScreen(272, 0, 92, 164, KD_kong->K_image[1], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX+2, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case TRAFIONY_H_LEWO:
                         blitAlphaImageToScreen(364, 0, 92, 164, KD_kong->K_image[1], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX+2, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case DYNKA_LEWO:
                    case KOLANO_LEWO:
                    case ZIEMIA_LEWO:
                    case SNIF_LEWO:
                    case KARUZELA_LEWO:
                         if(KD_kong->K_kong_value[KD_Count].KV_frame==2) blitAlphaImageToScreen(364, 0, 92, 164, KD_kong->K_image[1], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX+2, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else                                           blitAlphaImageToScreen(288, 0, 96, 136, KD_kong->K_image[0], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 104+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case DYNKA_PRAWO:
                    case KOLANO_PRAWO:
                    case ZIEMIA_PRAWO:
                    case SNIF_PRAWO:
                    case KARUZELA_PRAWO:
                         if(KD_kong->K_kong_value[KD_Count].KV_frame==2) blitAlphaImageToScreen(272, 0, 92, 164, KD_kong->K_image[1], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX+2, 76+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         else                                           blitAlphaImageToScreen(192, 0, 96, 136, KD_kong->K_image[0], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 104+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case BURIED_PRAWO:
                         blitAlphaImageToScreen(272, 0, 92, 50, KD_kong->K_image[1], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX+2, 190+KD_stageY);
                         break;
                    case BURIED_LEWO:
                         blitAlphaImageToScreen(364, 0, 92, 50, KD_kong->K_image[1], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX+2, 190+KD_stageY);
                         break;
                    case CHMURKA_PRAWO:
                    case LECI_PRAWO:
                         if(KD_kong->K_kong_value[KD_Count].KV_frame>20) Bop_Chmurka_Draw_Left(KD_bop, KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY, 4);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame>15) Bop_Chmurka_Draw_Left(KD_bop, KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY, 3);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame>10) Bop_Chmurka_Draw_Left(KD_bop, KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY, 2);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame>5) Bop_Chmurka_Draw_Left(KD_bop, KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY, 1);
                         else                                           blitAlphaImageToScreen(192, 0, 96, 136, KD_kong->K_image[0], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 104+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
                    case CHMURKA_LEWO:
                    case LECI_LEWO:
                         if(KD_kong->K_kong_value[KD_Count].KV_frame>20) Bop_Chmurka_Draw(KD_bop, KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY, 4);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame>15) Bop_Chmurka_Draw(KD_bop, KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY, 3);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame>10) Bop_Chmurka_Draw(KD_bop, KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY, 2);
                         else if(KD_kong->K_kong_value[KD_Count].KV_frame>5) Bop_Chmurka_Draw(KD_bop, KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY, 1);
                         else                                           blitAlphaImageToScreen(288, 0, 96, 136, KD_kong->K_image[0], KD_kong->K_kong_value[KD_Count].KV_x-KD_stageX, 104+KD_kong->K_kong_value[KD_Count].KV_y+KD_stageY);
                         break;
               }
          }
     }
}
void Kong_HUD_Draw(Kong* KHD_kong, Image* KHD_hud, int KHD_kong_pos, int KHD_n, int KHD_kong_nr)
{ 
     switch(KHD_kong_pos)
     {
          case 0:
          case 1:                              
               blitAlphaImageToScreen(43, 0, 17, 12, KHD_hud, (KHD_kong_pos*109)+354, 0);
               for(KHD_n=0;KHD_n<KHD_kong->K_kong_value[KHD_kong_nr].KV_energy;KHD_n+=1)
               blitImageToScreen(119, 17, 10, 7, KHD_hud, (KHD_kong_pos*109)+341-(KHD_n*8), 3);
               break;
          case 2:
          case 3:               
               blitAlphaImageToScreen(43, 0, 17, 12, KHD_hud, ((KHD_kong_pos-2)*109)+354, 13);
               for(KHD_n=0;KHD_n<KHD_kong->K_kong_value[KHD_kong_nr].KV_energy;KHD_n+=1)
               blitImageToScreen(119, 17, 10, 7, KHD_hud, ((KHD_kong_pos-2)*109)+341-(KHD_n*8), 16);
               break;
          case 4:
               blitAlphaImageToScreen(43, 0, 17, 12, KHD_hud, 463, 26);
               for(KHD_n=0;KHD_n<KHD_kong->K_kong_value[KHD_kong_nr].KV_energy;KHD_n+=1)
               blitImageToScreen(119, 17, 10, 7, KHD_hud, 450-(KHD_n*8), 29);
               break;
     }
}
