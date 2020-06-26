#ifndef KONG_H
#define KONG_H

#include "graphics.h"
#include "bop.h"
#include "stage.h"

typedef struct
{
	int KV_anim, KV_frame, KV_x, KV_y, KV_energy, KV_life, KV_agrX, KV_kong_agrX, KV_kong_hbox[3], KV_kong_activ;
} Kong_Value;

typedef struct
{
	Image* K_image[3];
	Kong_Value* K_kong_value;
} Kong;

extern Kong* Kong_Create(int KC_Count, int KC_kongX[], int KC_kong_agrX[], int KC_kong_activ[]);
extern void Kong_Destroy(Kong* KD_kong);
extern void Kong_Logic(Stage* KL_stage, Kong* KL_kong, Bop* KL_bop, int KL_Count, int KL_stageX);
extern void Kong_XY_Set(Kong* KXYS_kong, int KXYS_x, int KXYS_y);
extern int Kong_XY_Get(Kong* KXYG_kong, int KXYG_xy);
extern int Kong_FA_Get(Kong* KFAG_kong, int KFAG_fa);
extern void Kong_Draw(Kong* KD_kong, Bop* KD_bop, int KD_Count, int KD_stageX, int KD_stageY);
extern void Kong_HUD_Draw(Kong* KHD_kong, Image* KHD_hud, int KHD_kong_pos, int KHD_n, int KHD_kong_nr);

#endif
