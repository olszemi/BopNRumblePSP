#ifndef DOG_H
#define DOG_H

#include "graphics.h"
#include "bop.h"
#include "stage.h"

typedef struct
{
	int DV_anim, DV_frame, DV_x, DV_y, DV_energy, DV_life, DV_agrX, DV_dog_agrX, DV_dog_hbox[3], DV_dog_activ;
} Dog_Value;

typedef struct
{
	Image* D_image[2];
	Dog_Value* D_dog_value;
} Dog;

extern Dog* Dog_Create(int DC_Count, int DC_dogX[], int DC_dog_agrX[], int DC_dog_activ[]);
extern void Dog_Destroy(Dog* DD_dog);
extern void Dog_Logic(Stage* DL_stage, Dog* DL_dog, Bop* DL_bop, int DL_Count, int DL_stageX);
extern void Dog_Draw(Dog* DD_dog, int DD_Count, int DD_stageX, int DD_stageY);
extern void Dog_HUD_Draw(Dog* DHD_dog, Image* DHD_hud, int DHD_dog_pos, int DHD_n, int DHD_dog_nr);

#endif
