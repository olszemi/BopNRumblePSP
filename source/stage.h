#ifndef STAGE_H
#define STAGE_H

#include <time.h>

#include "graphics.h"

typedef struct
{
	Image* S_background_image[9];
    Image* S_foreground_image;
    Image* S_menu_image;
    Image* S_hud_image;
	int S_stage, S_anim, S_frame, S_x, S_y, S_width, S_key, S_enemy_nr, S_time, S_recovery;
	int HUD_enemy_list[5][2];
    clock_t S_time_start;
} Stage;

extern void Stage_Main(void);
extern int Stage_XY_Get(Stage* SXYG_stage, int SXYG_xy);
extern void Stage_HUD_ADD_Normal(Stage* SHAN_stage, int SHAN_enemy, int SHAN_enemy_numb, int SHAN_n);
extern void Stage_HUD_ADD_Forced(Stage* SHAF_stage, int SHAF_enemy, int SHAF_enemy_numb, int SHAF_n);
extern void Stage_HUD_DEL(Stage* SHD_stage, int SHD_enemy, int SHD_enemy_numb, int SHD_n);
extern void Stage_enemy_nr(Stage* SEN_stage);
extern void Stage_Bop_Trafiony(Stage* SBT_stage, int SBT_strength);

#endif
