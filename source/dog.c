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
#include "dog.h"
#include "graphics.h"
#include "keys.h"
#include "bop.h"
#include "preloader.h"
#include "stage.h"

void Dog_Logic_Left_Position(Stage* DLLP_stage, Dog* DLLP_dog, Bop* DLLP_bop, int DLLP_Count, int DLLP_stageX);
void Dog_Logic_Right_Position(Stage* DLRP_stage, Dog* DLRP_dog, Bop* DLRP_bop, int DLRP_Count, int DLRP_stageX);
void Dog_Attack_Right(Stage* DAR_stage, Dog* DAR_dog, Bop* DAR_bop, int DAR_Count);
void Dog_Attack_Left(Stage* DAL_stage, Dog* DAL_dog, Bop* DAL_bop, int DAL_Count);
void Dog_Check_Colisions(Stage* DCC_stage, Dog* DCC_dog, Bop* DCC_bop, int DCC_Count);

Dog* Dog_Create(int DC_Count, int DC_dogX[], int DC_dog_agrX[], int DC_dog_activ[])
{
     Dog* DC_dog = (Dog*) malloc(sizeof(Dog));
	 if (!DC_dog) return NULL;
	 
     DC_dog->D_image[0] = loadImage("Sety/PIES/piesSet1.png");
     DC_dog->D_image[1] = loadImage("Sety/PIES/piesSet2.png");
     
     DC_dog->D_dog_value = (Dog_Value*) malloc(sizeof(Dog_Value[DC_Count]));
     
     while(DC_Count)
     {
           DC_Count-=1;
	       DC_dog->D_dog_value[DC_Count].DV_anim = 0;
           DC_dog->D_dog_value[DC_Count].DV_frame = 0;
           DC_dog->D_dog_value[DC_Count].DV_x = DC_dogX[DC_Count];
           DC_dog->D_dog_value[DC_Count].DV_y = 0;
           DC_dog->D_dog_value[DC_Count].DV_energy = 2;
           DC_dog->D_dog_value[DC_Count].DV_life = 1;
           DC_dog->D_dog_value[DC_Count].DV_dog_agrX = DC_dog_agrX[DC_Count];
           DC_dog->D_dog_value[DC_Count].DV_dog_hbox[0] = -9999;
           DC_dog->D_dog_value[DC_Count].DV_dog_hbox[1] = -9999;
           DC_dog->D_dog_value[DC_Count].DV_dog_hbox[2] = -9999;
           DC_dog->D_dog_value[DC_Count].DV_dog_activ = DC_dog_activ[DC_Count];
     }
     return DC_dog;
}
void Dog_Destroy(Dog* DD_dog)
{
     freeImage(DD_dog->D_image[0]);
     freeImage(DD_dog->D_image[1]);
     free(DD_dog->D_dog_value);
     free(DD_dog);
}
void Dog_Logic(Stage* DL_stage, Dog* DL_dog, Bop* DL_bop, int DL_Count, int DL_stageX)
{
     while(DL_Count)
     {
          DL_Count-=1;
          if(DL_dog->D_dog_value[DL_Count].DV_life)
          {
               if(DL_stageX>DL_dog->D_dog_value[DL_Count].DV_dog_activ)
               {
                    DL_dog->D_dog_value[DL_Count].DV_dog_activ = -9999;
                    if(DL_dog->D_dog_value[DL_Count].DV_x+42>DL_stageX)
                    {
                         if(DL_dog->D_dog_value[DL_Count].DV_x+42-DL_stageX<=DL_dog->D_dog_value[DL_Count].DV_dog_agrX)
                         {
                              Dog_Check_Colisions(DL_stage, DL_dog, DL_bop, DL_Count);
                              Stage_HUD_ADD_Normal(DL_stage, HUD_DOG, DL_Count, 0);
                              Dog_Logic_Right_Position(DL_stage, DL_dog, DL_bop, DL_Count, DL_stageX);
                         }
                         else
                         {
                              Stage_HUD_DEL(DL_stage, HUD_DOG, DL_Count, 0);
                              DL_dog->D_dog_value[DL_Count].DV_frame =0;
                              DL_dog->D_dog_value[DL_Count].DV_anim = 0;
                              DL_dog->D_dog_value[DL_Count].DV_y = 0;
                         }
                    }
                    else
                    {
                         if(DL_stageX-DL_dog->D_dog_value[DL_Count].DV_x-42<=DL_dog->D_dog_value[DL_Count].DV_dog_agrX)
                         {
                              Dog_Check_Colisions(DL_stage, DL_dog, DL_bop, DL_Count);
                              Stage_HUD_ADD_Normal(DL_stage, HUD_DOG, DL_Count, 0);
                              Dog_Logic_Left_Position(DL_stage, DL_dog, DL_bop, DL_Count, DL_stageX);
                         }
                         else
                         {
                              Stage_HUD_DEL(DL_stage, HUD_DOG, DL_Count, 0);
                              DL_dog->D_dog_value[DL_Count].DV_frame =0;
                              DL_dog->D_dog_value[DL_Count].DV_anim = 0;
                              DL_dog->D_dog_value[DL_Count].DV_y = 0;
                         }
                    }
               }
          }
     }
}
void Dog_Logic_Right_Position(Stage* DLRP_stage, Dog* DLRP_dog, Bop* DLRP_bop, int DLRP_Count, int DLRP_stageX)
{
     switch(DLRP_dog->D_dog_value[DLRP_Count].DV_anim)
          {
               case 0:
                    DLRP_dog->D_dog_value[DLRP_Count].DV_frame = 1;
                    DLRP_dog->D_dog_value[DLRP_Count].DV_x -=3;
                    DLRP_dog->D_dog_value[DLRP_Count].DV_anim = IDZIE_LEWO;
                    break;
               case IDZIE_PRAWO:
                    if(DLRP_dog->D_dog_value[DLRP_Count].DV_x+42-DLRP_stageX>=DLRP_dog->D_dog_value[DLRP_Count].DV_dog_agrX-20)
                    {
                         DLRP_dog->D_dog_value[DLRP_Count].DV_anim = IDZIE_LEWO;
                         DLRP_dog->D_dog_value[DLRP_Count].DV_frame = 1;
                         DLRP_dog->D_dog_value[DLRP_Count].DV_x -=3;
                    }
                    else
                    {
                         DLRP_dog->D_dog_value[DLRP_Count].DV_frame += 1;
                         DLRP_dog->D_dog_value[DLRP_Count].DV_x +=3;
                         if(DLRP_dog->D_dog_value[DLRP_Count].DV_frame<16)DLRP_dog->D_dog_value[DLRP_Count].DV_y = 0;
                         else if(DLRP_dog->D_dog_value[DLRP_Count].DV_frame<36)DLRP_dog->D_dog_value[DLRP_Count].DV_y = -4;
                         else
                         {
                              DLRP_dog->D_dog_value[DLRP_Count].DV_frame = 1;
                              DLRP_dog->D_dog_value[DLRP_Count].DV_y = 0;
                         }
                    }
                    break;
               case IDZIE_LEWO:
                    if(DLRP_dog->D_dog_value[DLRP_Count].DV_x-Bop_BB_Get(DLRP_bop, 'X', 1)-Stage_XY_Get(DLRP_stage, 'X')<=40)
                    {
                         DLRP_dog->D_dog_value[DLRP_Count].DV_anim = ATAKUJE_LEWO;
                         DLRP_dog->D_dog_value[DLRP_Count].DV_frame = 0;
                         DLRP_dog->D_dog_value[DLRP_Count].DV_y = 0;
                         Dog_Attack_Left(DLRP_stage, DLRP_dog, DLRP_bop, DLRP_Count);
                    }
                    else
                    {
                         DLRP_dog->D_dog_value[DLRP_Count].DV_frame += 1;
                         DLRP_dog->D_dog_value[DLRP_Count].DV_x -=3;
                         if(DLRP_dog->D_dog_value[DLRP_Count].DV_frame<16)DLRP_dog->D_dog_value[DLRP_Count].DV_y = 0;
                         else if(DLRP_dog->D_dog_value[DLRP_Count].DV_frame<36)DLRP_dog->D_dog_value[DLRP_Count].DV_y = -4;
                         else
                         {
                              DLRP_dog->D_dog_value[DLRP_Count].DV_frame = 1;
                              DLRP_dog->D_dog_value[DLRP_Count].DV_y = 0;
                         }
                    }
                    break;
               case ATAKUJE_LEWO:
                    Dog_Attack_Left(DLRP_stage, DLRP_dog, DLRP_bop, DLRP_Count);
                    break;
               case ATAKUJE_PRAWO:
                    Dog_Attack_Right(DLRP_stage, DLRP_dog, DLRP_bop, DLRP_Count);
                    break;
               case SZCZEKA_PRAWO:
                    break;
               case SZCZEKA_LEWO:
                    break;
               case LEZY_PRAWO:
               case LEZY_LEWO:
                    DLRP_dog->D_dog_value[DLRP_Count].DV_frame += 1;
                    if(DLRP_dog->D_dog_value[DLRP_Count].DV_frame==1)DLRP_dog->D_dog_value[DLRP_Count].DV_x += 10;
                    if(DLRP_dog->D_dog_value[DLRP_Count].DV_frame>30)
                    {
                         DLRP_dog->D_dog_value[DLRP_Count].DV_frame = 1;
                         DLRP_dog->D_dog_value[DLRP_Count].DV_x +=14;
                         DLRP_dog->D_dog_value[DLRP_Count].DV_anim = IDZIE_PRAWO;
                         if(!DLRP_dog->D_dog_value[DLRP_Count].DV_energy)
                         {
                              DLRP_dog->D_dog_value[DLRP_Count].DV_life -= 1;
                              Stage_HUD_DEL(DLRP_stage, HUD_DOG, DLRP_Count, 0);
                              Stage_enemy_nr(DLRP_stage);
                         }
                    }
                    break;
          }
}
void Dog_Logic_Left_Position(Stage* DLLP_stage, Dog* DLLP_dog, Bop* DLLP_bop, int DLLP_Count, int DLLP_stageX)
{
     switch(DLLP_dog->D_dog_value[DLLP_Count].DV_anim)
          {
               case 0:
                    DLLP_dog->D_dog_value[DLLP_Count].DV_anim = IDZIE_PRAWO;
                    DLLP_dog->D_dog_value[DLLP_Count].DV_frame = 1;
                    DLLP_dog->D_dog_value[DLLP_Count].DV_x +=3;
                    break;
               case IDZIE_LEWO:
                    if(DLLP_stageX-DLLP_dog->D_dog_value[DLLP_Count].DV_x-42>=DLLP_dog->D_dog_value[DLLP_Count].DV_dog_agrX-20)
                    {
                         DLLP_dog->D_dog_value[DLLP_Count].DV_anim = IDZIE_PRAWO;
                         DLLP_dog->D_dog_value[DLLP_Count].DV_frame = 1;
                         DLLP_dog->D_dog_value[DLLP_Count].DV_x +=3;
                    }
                    else
                    {
                         DLLP_dog->D_dog_value[DLLP_Count].DV_frame += 1;
                         DLLP_dog->D_dog_value[DLLP_Count].DV_x -=3;
                         if(DLLP_dog->D_dog_value[DLLP_Count].DV_frame<16)DLLP_dog->D_dog_value[DLLP_Count].DV_y = 0;
                         else if(DLLP_dog->D_dog_value[DLLP_Count].DV_frame<36)DLLP_dog->D_dog_value[DLLP_Count].DV_y = -4;
                         else
                         {
                              DLLP_dog->D_dog_value[DLLP_Count].DV_frame = 1;
                              DLLP_dog->D_dog_value[DLLP_Count].DV_y = 0;
                         }
                    }
                    break;
               case IDZIE_PRAWO:
                    if(Bop_BB_Get(DLLP_bop, 'X', 0)+Stage_XY_Get(DLLP_stage, 'X')-DLLP_dog->D_dog_value[DLLP_Count].DV_x-84<=40)
                    {
                         DLLP_dog->D_dog_value[DLLP_Count].DV_anim = ATAKUJE_PRAWO;
                         DLLP_dog->D_dog_value[DLLP_Count].DV_frame = 0;
                         DLLP_dog->D_dog_value[DLLP_Count].DV_y = 0;
                         Dog_Attack_Right(DLLP_stage, DLLP_dog, DLLP_bop, DLLP_Count);
                    }
                    else
                    {
                         DLLP_dog->D_dog_value[DLLP_Count].DV_frame += 1;
                         DLLP_dog->D_dog_value[DLLP_Count].DV_x +=3;
                         if(DLLP_dog->D_dog_value[DLLP_Count].DV_frame<16)DLLP_dog->D_dog_value[DLLP_Count].DV_y = 0;
                         else if(DLLP_dog->D_dog_value[DLLP_Count].DV_frame<36)DLLP_dog->D_dog_value[DLLP_Count].DV_y = -4;
                         else
                         {
                              DLLP_dog->D_dog_value[DLLP_Count].DV_frame = 1;
                              DLLP_dog->D_dog_value[DLLP_Count].DV_y = 0;
                         }
                    }
                    break;
               case ATAKUJE_PRAWO:
                    Dog_Attack_Right(DLLP_stage, DLLP_dog, DLLP_bop, DLLP_Count);
                    break;
               case ATAKUJE_LEWO:
                    Dog_Attack_Left(DLLP_stage, DLLP_dog, DLLP_bop, DLLP_Count);
                    break;
               case SZCZEKA_PRAWO:
                    break;
               case SZCZEKA_LEWO:
                    break;
               case LEZY_PRAWO:
               case LEZY_LEWO:
                    DLLP_dog->D_dog_value[DLLP_Count].DV_frame += 1;
                    if(DLLP_dog->D_dog_value[DLLP_Count].DV_frame==1)DLLP_dog->D_dog_value[DLLP_Count].DV_x -= 10;
                    if(DLLP_dog->D_dog_value[DLLP_Count].DV_frame>30)
                    {
                         DLLP_dog->D_dog_value[DLLP_Count].DV_frame = 1;
                         DLLP_dog->D_dog_value[DLLP_Count].DV_x -=14;
                         DLLP_dog->D_dog_value[DLLP_Count].DV_anim = IDZIE_LEWO;
                         if(!DLLP_dog->D_dog_value[DLLP_Count].DV_energy)
                         {
                              DLLP_dog->D_dog_value[DLLP_Count].DV_life -= 1;
                              Stage_HUD_DEL(DLLP_stage, HUD_DOG, DLLP_Count, 0);
                              Stage_enemy_nr(DLLP_stage);
                         }
                    }
                    break;
                    }
}
void Dog_Attack_Right(Stage* DAR_stage, Dog* DAR_dog, Bop* DAR_bop, int DAR_Count)
{
     DAR_dog->D_dog_value[DAR_Count].DV_frame += 1;
     DAR_dog->D_dog_value[DAR_Count].DV_x +=5;
     if(DAR_dog->D_dog_value[DAR_Count].DV_frame<4)DAR_dog->D_dog_value[DAR_Count].DV_y -=8;
     else if(DAR_dog->D_dog_value[DAR_Count].DV_frame<7)DAR_dog->D_dog_value[DAR_Count].DV_y -= 6;
     else if(DAR_dog->D_dog_value[DAR_Count].DV_frame<10)DAR_dog->D_dog_value[DAR_Count].DV_y -= 4;
     else if(DAR_dog->D_dog_value[DAR_Count].DV_frame<13)DAR_dog->D_dog_value[DAR_Count].DV_y -= 2;
     else if(DAR_dog->D_dog_value[DAR_Count].DV_frame<25)DAR_dog->D_dog_value[DAR_Count].DV_y += 0;
     else if(DAR_dog->D_dog_value[DAR_Count].DV_frame<28)DAR_dog->D_dog_value[DAR_Count].DV_y += 2;
     else if(DAR_dog->D_dog_value[DAR_Count].DV_frame<31)DAR_dog->D_dog_value[DAR_Count].DV_y += 4;
     else if(DAR_dog->D_dog_value[DAR_Count].DV_frame<34)DAR_dog->D_dog_value[DAR_Count].DV_y += 6;
     else if(DAR_dog->D_dog_value[DAR_Count].DV_frame<37)DAR_dog->D_dog_value[DAR_Count].DV_y += 8;
     else
     {
          DAR_dog->D_dog_value[DAR_Count].DV_frame = 1;
          DAR_dog->D_dog_value[DAR_Count].DV_x +=3;
          DAR_dog->D_dog_value[DAR_Count].DV_anim = IDZIE_PRAWO;
          DAR_dog->D_dog_value[DAR_Count].DV_dog_hbox[0] = -9999;
          DAR_dog->D_dog_value[DAR_Count].DV_dog_hbox[1] = -9999;
          DAR_dog->D_dog_value[DAR_Count].DV_dog_hbox[2] = -9999;
     }
     if(DAR_dog->D_dog_value[DAR_Count].DV_frame<37)
     {
          if(DAR_dog->D_dog_value[DAR_Count].DV_dog_hbox[0]!=9999)
          {
               DAR_dog->D_dog_value[DAR_Count].DV_dog_hbox[0] = DAR_dog->D_dog_value[DAR_Count].DV_x-Stage_XY_Get(DAR_stage, 'X')+82;
               DAR_dog->D_dog_value[DAR_Count].DV_dog_hbox[1] = DAR_dog->D_dog_value[DAR_Count].DV_y+Stage_XY_Get(DAR_stage, 'Y')+168;
               DAR_dog->D_dog_value[DAR_Count].DV_dog_hbox[2] = DAR_dog->D_dog_value[DAR_Count].DV_y+Stage_XY_Get(DAR_stage, 'Y')+180;
               if(Bop_XY_Get(DAR_bop, 'Y')<72)DAR_dog->D_dog_value[DAR_Count].DV_dog_hbox[0] = Bop_Check_Hit(DAR_stage, DAR_bop, DAR_dog->D_dog_value[DAR_Count].DV_dog_hbox, 1);
          }
     }
}
void Dog_Attack_Left(Stage* DAL_stage, Dog* DAL_dog, Bop* DAL_bop, int DAL_Count)
{
     
     DAL_dog->D_dog_value[DAL_Count].DV_frame += 1;
     DAL_dog->D_dog_value[DAL_Count].DV_x -=5;
     if(DAL_dog->D_dog_value[DAL_Count].DV_frame<4)DAL_dog->D_dog_value[DAL_Count].DV_y -=8;
     else if(DAL_dog->D_dog_value[DAL_Count].DV_frame<7)DAL_dog->D_dog_value[DAL_Count].DV_y -= 6;
     else if(DAL_dog->D_dog_value[DAL_Count].DV_frame<10)DAL_dog->D_dog_value[DAL_Count].DV_y -= 4;
     else if(DAL_dog->D_dog_value[DAL_Count].DV_frame<13)DAL_dog->D_dog_value[DAL_Count].DV_y -= 2;
     else if(DAL_dog->D_dog_value[DAL_Count].DV_frame<25)DAL_dog->D_dog_value[DAL_Count].DV_y += 0;
     else if(DAL_dog->D_dog_value[DAL_Count].DV_frame<28)DAL_dog->D_dog_value[DAL_Count].DV_y += 2;
     else if(DAL_dog->D_dog_value[DAL_Count].DV_frame<31)DAL_dog->D_dog_value[DAL_Count].DV_y += 4;
     else if(DAL_dog->D_dog_value[DAL_Count].DV_frame<34)DAL_dog->D_dog_value[DAL_Count].DV_y += 6;
     else if(DAL_dog->D_dog_value[DAL_Count].DV_frame<37)DAL_dog->D_dog_value[DAL_Count].DV_y += 8;
     else
     {
          DAL_dog->D_dog_value[DAL_Count].DV_frame = 1;
          DAL_dog->D_dog_value[DAL_Count].DV_x -=3;
          DAL_dog->D_dog_value[DAL_Count].DV_anim = IDZIE_LEWO;
          DAL_dog->D_dog_value[DAL_Count].DV_dog_hbox[0] = -9999;
          DAL_dog->D_dog_value[DAL_Count].DV_dog_hbox[1] = -9999;
          DAL_dog->D_dog_value[DAL_Count].DV_dog_hbox[2] = -9999;
     }
     if(DAL_dog->D_dog_value[DAL_Count].DV_frame<37)
     {
          if(DAL_dog->D_dog_value[DAL_Count].DV_dog_hbox[0]!=9999)
          {
               DAL_dog->D_dog_value[DAL_Count].DV_dog_hbox[0] = DAL_dog->D_dog_value[DAL_Count].DV_x-Stage_XY_Get(DAL_stage, 'X')+2;
               DAL_dog->D_dog_value[DAL_Count].DV_dog_hbox[1] = DAL_dog->D_dog_value[DAL_Count].DV_y+Stage_XY_Get(DAL_stage, 'Y')+168;
               DAL_dog->D_dog_value[DAL_Count].DV_dog_hbox[2] = DAL_dog->D_dog_value[DAL_Count].DV_y+Stage_XY_Get(DAL_stage, 'Y')+180;
               if(Bop_XY_Get(DAL_bop, 'Y')<72)DAL_dog->D_dog_value[DAL_Count].DV_dog_hbox[0] = Bop_Check_Hit(DAL_stage, DAL_bop, DAL_dog->D_dog_value[DAL_Count].DV_dog_hbox, 1);
          }
     }
}
void Dog_Check_Colisions(Stage* DCC_stage, Dog* DCC_dog, Bop* DCC_bop, int DCC_Count)
{
     if(Bop_FA_Get(DCC_bop, 'A') == PODCIECIE_PRAWO || Bop_FA_Get(DCC_bop, 'A') == PODCIECIE_LEWO)
     {
          switch(DCC_dog->D_dog_value[DCC_Count].DV_anim)
          {
               case IDZIE_PRAWO:
                    if((Bop_HB_Get(DCC_bop)>(DCC_dog->D_dog_value[DCC_Count].DV_x-Stage_XY_Get(DCC_stage, 'X')) &&
                        Bop_HB_Get(DCC_bop)<(DCC_dog->D_dog_value[DCC_Count].DV_x-Stage_XY_Get(DCC_stage, 'X'))+84))
                    {
                         DCC_dog->D_dog_value[DCC_Count].DV_y = 0;
                         DCC_dog->D_dog_value[DCC_Count].DV_frame = 0;
                         DCC_dog->D_dog_value[DCC_Count].DV_anim = LEZY_PRAWO;
                         DCC_dog->D_dog_value[DCC_Count].DV_energy -= 1;
                    }
                    break;
               case IDZIE_LEWO:
                    if((Bop_HB_Get(DCC_bop)>(DCC_dog->D_dog_value[DCC_Count].DV_x-Stage_XY_Get(DCC_stage, 'X')) &&
                        Bop_HB_Get(DCC_bop)<(DCC_dog->D_dog_value[DCC_Count].DV_x-Stage_XY_Get(DCC_stage, 'X'))+84))
                    {
                         DCC_dog->D_dog_value[DCC_Count].DV_y = 0;
                         DCC_dog->D_dog_value[DCC_Count].DV_frame = 0;
                         DCC_dog->D_dog_value[DCC_Count].DV_anim = LEZY_LEWO;
                         DCC_dog->D_dog_value[DCC_Count].DV_energy -= 1;
                    }
                    break;
          }
     }
}
void Dog_Draw(Dog* DD_dog, int DD_Count, int DD_stageX, int DD_stageY)
{
     while(DD_Count)
     {
          DD_Count-=1;
          if(DD_dog->D_dog_value[DD_Count].DV_life)
          {
               switch(DD_dog->D_dog_value[DD_Count].DV_anim)
               {
                    case IDZIE_PRAWO:
                         if(DD_dog->D_dog_value[DD_Count].DV_frame<16)      blitAlphaImageToScreen(0, 168, 88, 80, DD_dog->D_image[0], DD_dog->D_dog_value[DD_Count].DV_x-DD_stageX-2, 160+DD_dog->D_dog_value[DD_Count].DV_y+DD_stageY);
                         else if(DD_dog->D_dog_value[DD_Count].DV_frame<36) blitAlphaImageToScreen(176, 84, 84, 84, DD_dog->D_image[0], DD_dog->D_dog_value[DD_Count].DV_x-DD_stageX, 156+DD_dog->D_dog_value[DD_Count].DV_y+DD_stageY);
                         break;
                    case IDZIE_LEWO:
                         if(DD_dog->D_dog_value[DD_Count].DV_frame<16)      blitAlphaImageToScreen(88, 168, 88, 80, DD_dog->D_image[0], DD_dog->D_dog_value[DD_Count].DV_x-DD_stageX-2, 160+DD_dog->D_dog_value[DD_Count].DV_y+DD_stageY);
                         else if(DD_dog->D_dog_value[DD_Count].DV_frame<36) blitAlphaImageToScreen(0, 84, 84, 84, DD_dog->D_image[1], DD_dog->D_dog_value[DD_Count].DV_x-DD_stageX, 156+DD_dog->D_dog_value[DD_Count].DV_y+DD_stageY);
                         break;
                    case ATAKUJE_PRAWO:
                         blitAlphaImageToScreen(88, 0, 88, 108, DD_dog->D_image[1], DD_dog->D_dog_value[DD_Count].DV_x-DD_stageX-2, 132+DD_dog->D_dog_value[DD_Count].DV_y+DD_stageY);
                         break;
                    case ATAKUJE_LEWO:
                         blitAlphaImageToScreen(176, 0, 88, 108, DD_dog->D_image[1], DD_dog->D_dog_value[DD_Count].DV_x-DD_stageX-2, 132+DD_dog->D_dog_value[DD_Count].DV_y+DD_stageY);
                         break;
                    case LEZY_PRAWO:
                         blitAlphaImageToScreen(84, 108, 92, 60, DD_dog->D_image[1], DD_dog->D_dog_value[DD_Count].DV_x-DD_stageX-4, 180+DD_dog->D_dog_value[DD_Count].DV_y+DD_stageY);
                         break;
                    case LEZY_LEWO:
                         blitAlphaImageToScreen(176, 108, 92, 60, DD_dog->D_image[1], DD_dog->D_dog_value[DD_Count].DV_x-DD_stageX-4, 180+DD_dog->D_dog_value[DD_Count].DV_y+DD_stageY);
                         break;
               }
          }
     }
}
void Dog_HUD_Draw(Dog* DHD_dog, Image* DHD_hud, int DHD_dog_pos, int DHD_n, int DHD_dog_nr)
{ 
     switch(DHD_dog_pos)
     {
          case 0:
          case 1:                              
               blitAlphaImageToScreen(0, 0, 17, 12, DHD_hud, (DHD_dog_pos*109)+354, 0);
               for(DHD_n=0;DHD_n<DHD_dog->D_dog_value[DHD_dog_nr].DV_energy;DHD_n+=1)
               blitImageToScreen(119, 17, 10, 7, DHD_hud, (DHD_dog_pos*109)+341-(DHD_n*8), 3);
               break;
          case 2:
          case 3:               
               blitAlphaImageToScreen(0, 0, 17, 12, DHD_hud, ((DHD_dog_pos-2)*109)+354, 13);
               for(DHD_n=0;DHD_n<DHD_dog->D_dog_value[DHD_dog_nr].DV_energy;DHD_n+=1)
               blitImageToScreen(119, 17, 10, 7, DHD_hud, ((DHD_dog_pos-2)*109)+341-(DHD_n*8), 16);
               break;
          case 4:
               blitAlphaImageToScreen(0, 0, 17, 12, DHD_hud, 463, 26);
               for(DHD_n=0;DHD_n<DHD_dog->D_dog_value[DHD_dog_nr].DV_energy;DHD_n+=1)
               blitImageToScreen(119, 17, 10, 7, DHD_hud, 450-(DHD_n*8), 29);
               break;
     }
}
