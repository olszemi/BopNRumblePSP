#ifndef BOP_H
#define BOP_H

#include "graphics.h"
#include "stage.h"

typedef struct
{
	Image* B_image[12];
	int B_anim, B_frame, B_x, B_y, B_bbox[2][2], B_hbox, B_live, B_energy, B_last_anim, B_recovery;
} Bop;

extern Bop* Bop_Create(void);
extern void Bop_Destroy(Bop* BD_bop);
extern void Bop_Logic(Bop* BL_bop, int BL_key);
extern int Bop_XY_Get(Bop* BXYG_bop, int BXYG_xy);
extern void Bop_Hit_Enemy(Bop* BHE_bop);
extern void Bop_Demage(Bop* BD_bop, int BD_strength);
extern int Bop_BB_Get(Bop* BBBG_bop, int BBBG_XY, int BBBG_12);
extern int Bop_HB_Get(Bop* BHBG_bop);
extern int Bop_FA_Get(Bop* BFAG_bop, int BFAG_fa);
extern int Bop_MiddleX_Get(Bop* BMXG_bop);
extern int Bop_LE_Get(Bop* BLEG_bop, int BLEG_le);
extern void Bop_Energy_Fill(Bop* BEF_bop, int BEF_count);
extern void Bop_Time_Over(Bop* BTO_bop);
extern void Bop_Draw(Bop* BD_bop);
extern void Bop_HUD_Draw(Bop* BHD_bop, Image* BHD_hud, int BHD_n);
extern int Bop_Check_Hit(Stage* BCH_stage, Bop* BCH_bop, int BCH_enemy_HB[3], int BCH_strength);
extern int Bop_Anim_Select(int BAS_key);
extern int Bop_Anim_Revers_Select(int BAS_key);
extern void Bop_Chmurka_Draw(Bop* BCD_bop, int BCD_x, int BCD_y, int BCD_frame);
extern void Bop_Chmurka_Draw_Left(Bop* BCDL_bop, int BCDL_x, int BCDL_y, int BCDL_frame);
#endif
