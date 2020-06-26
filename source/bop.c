#include <bop.h>
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
#include "graphics.h"
#include "keys.h"
#include "bop.h"
#include "preloader.h"
#include "stage.h"

void Bop_Anim_Stoi_Prawo(Bop* BASP_bop, int BASP_key);
void Bop_Anim_Stoi_Lewo(Bop* BASL_bop, int BASL_key);
void Bop_Anim_Skacze_Prawo(Bop* BASkP_bop, int BASkP_key);
void Bop_Anim_Skacze_Lewo(Bop* BASkL_bop, int BASkL_key);
void Bop_Anim_Skacze_Up_Prawo(Bop* BASkXP_bop);
void Bop_Anim_Skacze_Up_Lewo(Bop* BASkXL_bop);
void Bop_Anim_Podciecie_Prawo(Bop* BAPP_bop, int BAPP_key);
void Bop_Anim_Podciecie_Lewo(Bop* BAPL_bop, int BAPL_key);
void Bop_Anim_Obrkop_Prawo(Bop* BAOP_bop);
void Bop_Anim_Obrkop_Lewo(Bop* BAOL_bop);
void Bop_Anim_Dynka_Prawo(Bop* BADP_bop);
void Bop_Anim_Dynka_Lewo(Bop* BADL_bop);
void Bop_Anim_Chmurka_Prawo(Bop* BACP_bop, int BACP_key);
void Bop_Anim_Chmurka_Lewo(Bop* BACL_bop, int BACL_key);
void Bop_Anim_Trafiony_Prawo(Bop* BATP_bop);
void Bop_Anim_Trafiony_Lewo(Bop* BATL_bop);
void Bop_Anim_Lezy_Prawo(Bop* BALP_bop);
void Bop_Anim_Lezy_Lewo(Bop* BALL_bop);
void Bop_Anim_Kolano_Prawo(Bop* BAKP_bop);
void Bop_Anim_Kolano_Lewo(Bop* BAKL_bop);
void Bop_Anim_Lapy_Prawo(Bop* BALP_bop);
void Bop_Anim_Lapy_Lewo(Bop* BALL_bop);
void Bop_Anim_Fists_Prawo(Bop* BAFP_bop);
void Bop_Anim_Fists_Lewo(Bop* BAFL_bop);
void Bop_Anim_Ziemia_Prawo(Bop* BAZP_bop);
void Bop_Anim_Ziemia_Lewo(Bop* BAZL_bop);
void Bop_Anim_Klata_Prawo(Bop* BAKP_bop, int BAKP_key);
void Bop_Anim_Klata_Lewo(Bop* BAKL_bop, int BAKL_key);
void Bop_Anim_Superfly_Prawo(Bop* BASP_bop, int BASP_key);
void Bop_Anim_Superfly_Lewo(Bop* BASL_bop, int BASL_key);
void Bop_Anim_Snif_Prawo(Bop* BASP_bop, int BASP_key);
void Bop_Anim_Snif_Lewo(Bop* BASL_bop, int BASL_key);
void Bop_Anim_Karuzela_Prawo(Bop* BAKP_bop, int BAKP_key);
void Bop_Anim_Karuzela_Lewo(Bop* BAKL_bop, int BAKL_key);

Bop* Bop_Create(void)
{
     Preload_Init();
     Preload(0, 15);
     Bop* BC_bop = (Bop*) malloc(sizeof(Bop));
	 if (!BC_bop) return NULL;
     
	 BC_bop->B_image[0] = loadImage("Sety/BOP/bopSet1.png");
	 BC_bop->B_image[1] = loadImage("Sety/BOP/bopSet1a.png");
	 BC_bop->B_image[2] = loadImage("Sety/BOP/bopSet2.png");
	 Preload(1, 15);
     BC_bop->B_image[3] = loadImage("Sety/BOP/bopSet2a.png");
	 BC_bop->B_image[4] = loadImage("Sety/BOP/bopSet3.png");
	 BC_bop->B_image[5] = loadImage("Sety/BOP/bopSet3a.png");
	 Preload(2, 15);
     BC_bop->B_image[6] = loadImage("Sety/BOP/bopSet4.png");
	 BC_bop->B_image[7] = loadImage("Sety/BOP/bopSet4a.png");
	 BC_bop->B_image[8] = loadImage("Sety/BOP/bopSet5.png");
	 Preload(3, 15);
     BC_bop->B_image[9] = loadImage("Sety/BOP/bopSet5a.png");
	 BC_bop->B_image[10] = loadImage("Sety/BOP/bopSet6.png");
	 BC_bop->B_image[11] = loadImage("Sety/BOP/bopSet6a.png");
	 Preload(4, 15);
	 BC_bop->B_anim = 0;
	 BC_bop->B_last_anim = 0;
     BC_bop->B_frame = 0;
     BC_bop->B_recovery = 0;
     BC_bop->B_x = 0;
     BC_bop->B_y = 0;
     BC_bop->B_bbox[0][0] = -9999;
     BC_bop->B_bbox[0][1] = -9999;
     BC_bop->B_bbox[1][0] = -9999;
     BC_bop->B_bbox[1][1] = -9999;
     BC_bop->B_hbox = -9999;
     BC_bop->B_live = 5;
     BC_bop->B_energy = 10;
     Preload(5, 15);
     Preload_End();
     return BC_bop;
}
void Bop_Destroy(Bop* BD_bop)
{
     freeImage(BD_bop->B_image[0]);
     freeImage(BD_bop->B_image[1]);
     freeImage(BD_bop->B_image[2]);
     freeImage(BD_bop->B_image[3]);
     freeImage(BD_bop->B_image[4]);
     freeImage(BD_bop->B_image[5]);
     freeImage(BD_bop->B_image[6]);
     freeImage(BD_bop->B_image[7]);
     freeImage(BD_bop->B_image[8]);
     freeImage(BD_bop->B_image[9]);
     freeImage(BD_bop->B_image[10]);
     freeImage(BD_bop->B_image[11]);
	 free(BD_bop);
}
void Bop_Logic(Bop* BL_bop, int BL_key)
{
     if(BL_bop->B_recovery != 0)BL_bop->B_recovery -= 1;
     switch(BL_bop->B_anim)
     {
           case STOI_PRAWO:
           case KUCA_PRAWO:
           case IDZIE_PRAWO:
                Bop_Anim_Stoi_Prawo(BL_bop, BL_key);
                break;
           case STOI_LEWO:
           case KUCA_LEWO:
           case IDZIE_LEWO:
                Bop_Anim_Stoi_Lewo(BL_bop, BL_key);
                break;
           case SKACZE_UP_PRAWO:
                Bop_Anim_Skacze_Up_Prawo(BL_bop);
                break;
           case SKACZE_UP_LEWO:
                Bop_Anim_Skacze_Up_Lewo(BL_bop);
                break;
           case SKACZE_PRAWO:
                Bop_Anim_Skacze_Prawo(BL_bop, BL_key);
                break;
           case SKACZE_LEWO:
                Bop_Anim_Skacze_Lewo(BL_bop, BL_key);
                break;
           case PODCIECIE_PRAWO:
                Bop_Anim_Podciecie_Prawo(BL_bop, BL_key);
                break;
           case PODCIECIE_LEWO:
                Bop_Anim_Podciecie_Lewo(BL_bop, BL_key);
                break;
           case OBRKOP_PRAWO:
                Bop_Anim_Obrkop_Prawo(BL_bop);
                break;
           case OBRKOP_LEWO:
                Bop_Anim_Obrkop_Lewo(BL_bop);
                break;
           case DYNKA_PRAWO:
                Bop_Anim_Dynka_Prawo(BL_bop);
                break;
           case DYNKA_LEWO:
                Bop_Anim_Dynka_Lewo(BL_bop);
                break;
           case CHMURKA_PRAWO:
                Bop_Anim_Chmurka_Prawo(BL_bop, BL_key);
                break;
           case CHMURKA_LEWO:
                Bop_Anim_Chmurka_Lewo(BL_bop, BL_key);
                break;
           case TRAFIONY_PRAWO:
                Bop_Anim_Trafiony_Prawo(BL_bop);
                break;
           case TRAFIONY_LEWO:
                Bop_Anim_Trafiony_Lewo(BL_bop);
                break;
           case LEZY_PRAWO:
                Bop_Anim_Lezy_Prawo(BL_bop);
                break;
           case LEZY_LEWO:
                Bop_Anim_Lezy_Lewo(BL_bop);
                break;
           case KOLANO_PRAWO:
                Bop_Anim_Kolano_Prawo(BL_bop);
                break;
           case KOLANO_LEWO:
                Bop_Anim_Kolano_Lewo(BL_bop);
                break;
           case LAPY_PRAWO:
                Bop_Anim_Lapy_Prawo(BL_bop);
                break;
           case LAPY_LEWO:
                Bop_Anim_Lapy_Lewo(BL_bop);
                break;
           case FISTS_PRAWO:
                Bop_Anim_Fists_Prawo(BL_bop);
                break;
           case FISTS_LEWO:
                Bop_Anim_Fists_Lewo(BL_bop);
                break;
           case ZIEMIA_PRAWO:
                Bop_Anim_Ziemia_Prawo(BL_bop);
                break;
           case ZIEMIA_LEWO:
                Bop_Anim_Ziemia_Lewo(BL_bop);
                break;
           case KLATA_PRAWO:
                Bop_Anim_Klata_Prawo(BL_bop, BL_key);
                break;
           case KLATA_LEWO:
                Bop_Anim_Klata_Lewo(BL_bop, BL_key);
                break;
           case SUPERFLY_PRAWO:
                Bop_Anim_Superfly_Prawo(BL_bop, BL_key);
                break;
           case SUPERFLY_LEWO:
                Bop_Anim_Superfly_Lewo(BL_bop, BL_key);
                break;
           case SNIF_PRAWO:
                Bop_Anim_Snif_Prawo(BL_bop, BL_key);
                break;
           case SNIF_LEWO:
                Bop_Anim_Snif_Lewo(BL_bop, BL_key);
                break;
           case KARUZELA_PRAWO:
                Bop_Anim_Karuzela_Prawo(BL_bop, BL_key);
                break;
           case KARUZELA_LEWO:
                Bop_Anim_Karuzela_Lewo(BL_bop, BL_key);
                break;
     }
}
void Bop_Anim_Stoi_Prawo(Bop* BASP_bop, int BASP_key)
{
     switch(BASP_key)
                {
                      case LEFT:
                           BASP_bop->B_anim = IDZIE_LEWO;
                           BASP_bop->B_frame =1;
                           break;
                      case LEFT_X:
                           if(BASP_bop->B_x>-200)BASP_bop->B_x -= 2;
                           BASP_bop->B_anim = IDZIE_LEWO;
                           BASP_bop->B_frame =1;
                           break;
                      case RIGHT:
                           BASP_bop->B_anim = IDZIE_PRAWO;
                           BASP_bop->B_frame +=1;
                           if(BASP_bop->B_frame==97)BASP_bop->B_frame=1;
                           break;
                      case RIGHT_X:
                           if(BASP_bop->B_x<200)BASP_bop->B_x += 2;
                           BASP_bop->B_anim = IDZIE_PRAWO;
                           BASP_bop->B_frame +=1;
                           if(BASP_bop->B_frame==97)BASP_bop->B_frame=1;
                           break;
                      case DOWN:
                      case RIGHT_DOWN:
                      case DOWN_CROSS:
                           BASP_bop->B_anim = KUCA_PRAWO;
                           break;   
                      case LEFT_DOWN:
                           BASP_bop->B_anim = KUCA_LEWO;
                           break;   
                      case CROSS:
                           BASP_bop->B_frame = 0;
                           BASP_bop->B_anim = SKACZE_UP_PRAWO;
                           Bop_Anim_Skacze_Up_Prawo(BASP_bop);
                           break;   
                      case RIGHT_CROSS:
                      case RIGHT_CROSS_X:
                      case RIGHT_CROSS_XX:
                           BASP_bop->B_frame = 0;
                           BASP_bop->B_anim = SKACZE_PRAWO;
                           Bop_Anim_Skacze_Prawo(BASP_bop, BASP_key);
                           break;
                      case LEFT_CROSS:
                      case LEFT_CROSS_X:
                      case LEFT_CROSS_XX:
                           BASP_bop->B_frame = 0;
                           BASP_bop->B_anim = SKACZE_LEWO;
                           Bop_Anim_Skacze_Lewo(BASP_bop, BASP_key);
                           break; 
                      default:
                           if(BASP_key>999){}
                           else if(BASP_key>299)
                           {
                                switch(BASP_key)
                                     {
                                          case KEY_KLATA_RIGHT_X:
                                          case KEY_KLATA_RIGHT_XX:
                                          case KEY_KLATA_RIGHT_N:
                                               if(BASP_bop->B_recovery == 0)
                                               {
                                                    BASP_bop->B_frame = 0;
                                                    BASP_bop->B_anim = KLATA_PRAWO;
                                                    Bop_Anim_Klata_Prawo(BASP_bop, BASP_key);
                                               }
                                               break;
                                          case KEY_SUPERFLY_RIGHT_X:
                                          case KEY_SUPERFLY_RIGHT_XX:
                                          case KEY_SUPERFLY_RIGHT_N:
                                               if(BASP_bop->B_recovery == 0)
                                               {
                                                    BASP_bop->B_frame = 0;
                                                    BASP_bop->B_anim = SUPERFLY_PRAWO;
                                                    Bop_Anim_Superfly_Prawo(BASP_bop, BASP_key);
                                               }
                                               break;
                                     }
                           }
                           else if(BASP_key>99)
                           {
                                 switch(Bop_Anim_Select(BASP_key))
                                 {
                                         case KEY_OBRKOP:
                                              if(BASP_bop->B_recovery == 0)
                                              {
                                                   BASP_bop->B_frame = 0;
                                                   BASP_bop->B_anim = OBRKOP_PRAWO;
                                                   Bop_Anim_Obrkop_Prawo(BASP_bop);
                                              }
                                              break;
                                         case KEY_PODCIECIE:
                                              if(BASP_bop->B_recovery == 0)
                                              {
                                                   BASP_bop->B_frame = 0;
                                                   BASP_bop->B_anim = PODCIECIE_PRAWO;
                                                   Bop_Anim_Podciecie_Prawo(BASP_bop, BASP_key);
                                              }
                                              break;
                                         case KEY_KOLANO:
                                              if(BASP_bop->B_recovery == 0)
                                              {
                                                   BASP_bop->B_frame = 0;
                                                   BASP_bop->B_anim = KOLANO_PRAWO;
                                                   Bop_Anim_Kolano_Prawo(BASP_bop);
                                              }
                                              break;
                                         case KEY_KLATA:
                                              if(BASP_bop->B_recovery == 0)
                                              {
                                                   BASP_bop->B_frame = 0;
                                                   BASP_bop->B_anim = KLATA_PRAWO;
                                                   Bop_Anim_Klata_Prawo(BASP_bop, BASP_key);
                                              }
                                              break;
                                         case KEY_FISTS:
                                              if(BASP_bop->B_recovery == 0)
                                              {
                                                   BASP_bop->B_frame = 0;
                                                   BASP_bop->B_anim = FISTS_PRAWO;
                                                   Bop_Anim_Fists_Prawo(BASP_bop);
                                              }
                                              break;
                                         case KEY_LAPY:
                                              if(BASP_bop->B_recovery == 0)
                                              {
                                                   BASP_bop->B_frame = 0;
                                                   BASP_bop->B_anim = LAPY_PRAWO;
                                                   Bop_Anim_Lapy_Prawo(BASP_bop);
                                              }
                                              break;
                                         case KEY_DYNKA:
                                              if(BASP_bop->B_recovery == 0)
                                              {
                                                   BASP_bop->B_frame = 0;
                                                   BASP_bop->B_anim = DYNKA_PRAWO;
                                                   Bop_Anim_Dynka_Prawo(BASP_bop);
                                              }
                                              break;
                                         case KEY_CHMURKA:
                                              if(BASP_bop->B_recovery == 0)
                                              {
                                                   BASP_bop->B_frame = 0;
                                                   BASP_bop->B_anim = CHMURKA_PRAWO;
                                                   Bop_Anim_Chmurka_Prawo(BASP_bop, BASP_key);
                                              }
                                              break;
                                         case KEY_ZIEMIA:
                                              if(BASP_bop->B_recovery == 0)
                                              {
                                                   BASP_bop->B_frame = 0;
                                                   BASP_bop->B_anim = ZIEMIA_PRAWO;
                                                   Bop_Anim_Ziemia_Prawo(BASP_bop);
                                              }
                                              break;
                                         case KEY_SNIF:
                                              if(BASP_bop->B_recovery == 0)
                                              {
                                                   BASP_bop->B_frame = 0;
                                                   BASP_bop->B_anim = SNIF_PRAWO;
                                                   Bop_Anim_Snif_Prawo(BASP_bop, BASP_key);
                                              }
                                              break;
                                         case KEY_KARUZELA:
                                              if(BASP_bop->B_recovery == 0)
                                              {
                                                   BASP_bop->B_frame = 0;
                                                   BASP_bop->B_anim = KARUZELA_PRAWO;
                                                   Bop_Anim_Karuzela_Prawo(BASP_bop, BASP_key);
                                              }
                                              break;
                                         default:
                                              BASP_bop->B_frame = 0;
                                              BASP_bop->B_anim = STOI_PRAWO;
                                              break;
                                 }
                           }
                           else
                           {
                               BASP_bop->B_frame = 0;
                               BASP_bop->B_anim = STOI_PRAWO;
                           }
                           break;
                }
}
void Bop_Anim_Stoi_Lewo(Bop* BASL_bop, int BASL_key)
{
     switch(BASL_key)
                {
                      case LEFT:
                           BASL_bop->B_anim = IDZIE_LEWO;
                           BASL_bop->B_frame +=1;
                           if(BASL_bop->B_frame==97)BASL_bop->B_frame=1;
                           break;
                      case LEFT_X:
                           if(BASL_bop->B_x>-200)BASL_bop->B_x -= 2;
                           BASL_bop->B_anim = IDZIE_LEWO;
                           BASL_bop->B_frame +=1;
                           if(BASL_bop->B_frame==97)BASL_bop->B_frame=1;
                           break;
                      case RIGHT:
                           BASL_bop->B_anim = IDZIE_PRAWO;
                           BASL_bop->B_frame =1;
                           break;
                      case RIGHT_X:
                           if(BASL_bop->B_x<200)BASL_bop->B_x += 2;
                           BASL_bop->B_anim = IDZIE_PRAWO;
                           BASL_bop->B_frame =1;
                           break;
                      case RIGHT_DOWN:
                           BASL_bop->B_anim = KUCA_PRAWO;
                           break; 
                      case DOWN:  
                      case LEFT_DOWN:
                      case DOWN_CROSS:
                           BASL_bop->B_anim = KUCA_LEWO;
                           break;   
                      case CROSS:
                           BASL_bop->B_frame = 0;
                           BASL_bop->B_anim = SKACZE_UP_LEWO;
                           Bop_Anim_Skacze_Up_Lewo(BASL_bop);
                           break;
                      case LEFT_CROSS:
                      case LEFT_CROSS_X:
                      case LEFT_CROSS_XX:
                           BASL_bop->B_frame = 0;
                           BASL_bop->B_anim = SKACZE_LEWO;
                           Bop_Anim_Skacze_Lewo(BASL_bop, BASL_key);
                           break;    
                      case RIGHT_CROSS:
                      case RIGHT_CROSS_X:
                      case RIGHT_CROSS_XX:
                           BASL_bop->B_frame = 0;
                           BASL_bop->B_anim = SKACZE_PRAWO;
                           Bop_Anim_Skacze_Prawo(BASL_bop, BASL_key);
                           break;
                      default:
                           if(BASL_key>999){}
                           else if(BASL_key>299)
                           {
                                switch(BASL_key)
                                     {
                                          case KEY_KLATA_LEFT_X:
                                          case KEY_KLATA_LEFT_XX:
                                          case KEY_KLATA_LEFT_N:
                                               if(BASL_bop->B_recovery == 0)
                                               {
                                                    BASL_bop->B_frame = 0;
                                                    BASL_bop->B_anim = KLATA_LEWO;
                                                    Bop_Anim_Klata_Lewo(BASL_bop, BASL_key);
                                               }
                                               break;
                                          case KEY_SUPERFLY_LEFT_X:
                                          case KEY_SUPERFLY_LEFT_XX:
                                          case KEY_SUPERFLY_LEFT_N:
                                               if(BASL_bop->B_recovery == 0)
                                               {
                                                    BASL_bop->B_frame = 0;
                                                    BASL_bop->B_anim = SUPERFLY_LEWO;
                                                    Bop_Anim_Superfly_Lewo(BASL_bop, BASL_key);
                                               }
                                               break;
                                     }
                           }
                           else if(BASL_key>99)
                           {
                                 
                                 switch(Bop_Anim_Revers_Select(BASL_key))
                                 {
                                         case KEY_OBRKOP:
                                              if(BASL_bop->B_recovery == 0)
                                              {
                                                   BASL_bop->B_frame = 0;
                                                   BASL_bop->B_anim = OBRKOP_LEWO;
                                                   Bop_Anim_Obrkop_Lewo(BASL_bop);
                                              }
                                              break;
                                         case KEY_PODCIECIE:
                                              if(BASL_bop->B_recovery == 0)
                                              {
                                                   BASL_bop->B_frame = 0;
                                                   BASL_bop->B_anim = PODCIECIE_LEWO;
                                                   Bop_Anim_Podciecie_Lewo(BASL_bop, BASL_key);
                                              }
                                              break;
                                         case KEY_KOLANO:
                                              if(BASL_bop->B_recovery == 0)
                                              {
                                                   BASL_bop->B_frame = 0;
                                                   BASL_bop->B_anim = KOLANO_LEWO;
                                                   Bop_Anim_Kolano_Lewo(BASL_bop);
                                              }
                                              break;
                                         case KEY_KLATA:
                                              if(BASL_bop->B_recovery == 0)
                                              {
                                                   BASL_bop->B_frame = 0;
                                                   BASL_bop->B_anim = KLATA_LEWO;
                                                   Bop_Anim_Klata_Lewo(BASL_bop, BASL_key);
                                              }
                                              break;
                                         case KEY_FISTS:
                                              if(BASL_bop->B_recovery == 0)
                                              {
                                                   BASL_bop->B_frame = 0;
                                                   BASL_bop->B_anim = FISTS_LEWO;
                                                   Bop_Anim_Fists_Lewo(BASL_bop);
                                              }
                                              break;
                                         case KEY_LAPY:
                                              if(BASL_bop->B_recovery == 0)
                                              {
                                                   BASL_bop->B_frame = 0;
                                                   BASL_bop->B_anim = LAPY_LEWO;
                                                   Bop_Anim_Lapy_Lewo(BASL_bop);
                                              }
                                              break;
                                         case KEY_DYNKA:
                                              if(BASL_bop->B_recovery == 0)
                                              {
                                                   BASL_bop->B_frame = 0;
                                                   BASL_bop->B_anim = DYNKA_LEWO;
                                                   Bop_Anim_Dynka_Lewo(BASL_bop);
                                              }
                                              break;
                                         case KEY_CHMURKA:
                                              if(BASL_bop->B_recovery == 0)
                                              {
                                                   BASL_bop->B_frame = 0;
                                                   BASL_bop->B_anim = CHMURKA_LEWO;
                                                   Bop_Anim_Chmurka_Lewo(BASL_bop, BASL_key);
                                              }
                                              break;
                                         case KEY_ZIEMIA:
                                              if(BASL_bop->B_recovery == 0)
                                              {
                                                   BASL_bop->B_frame = 0;
                                                   BASL_bop->B_anim = ZIEMIA_LEWO;
                                                   Bop_Anim_Ziemia_Lewo(BASL_bop);
                                              }
                                              break;
                                         case KEY_SNIF:
                                              if(BASL_bop->B_recovery == 0)
                                              {
                                                   BASL_bop->B_frame = 0;
                                                   BASL_bop->B_anim = SNIF_LEWO;
                                                   Bop_Anim_Snif_Lewo(BASL_bop, BASL_key);
                                              }
                                              break;
                                         case KEY_KARUZELA:
                                              if(BASL_bop->B_recovery == 0)
                                              {
                                                   BASL_bop->B_frame = 100;
                                                   BASL_bop->B_anim = KARUZELA_LEWO;
                                                   Bop_Anim_Karuzela_Lewo(BASL_bop, BASL_key);
                                              }
                                              break;
                                         default:
                                              BASL_bop->B_frame = 0;
                                              BASL_bop->B_anim = STOI_LEWO;
                                              break;
                                 }
                           }
                           else
                           {
                               BASL_bop->B_frame = 0;
                               BASL_bop->B_anim = STOI_LEWO;
                           }
                           break;
                }
}
void Bop_Anim_Skacze_Up_Prawo(Bop* BASkXP_bop)
{
     BASkXP_bop->B_frame +=1;
     if(BASkXP_bop->B_frame<5)BASkXP_bop->B_y += 7;
     else if(BASkXP_bop->B_frame<9)BASkXP_bop->B_y += 6;
     else if(BASkXP_bop->B_frame<13)BASkXP_bop->B_y += 5;///
     else if(BASkXP_bop->B_frame>68)
     {
          if(BASkXP_bop->B_frame<73)BASkXP_bop->B_y -= 5;///
          else if(BASkXP_bop->B_frame<77)BASkXP_bop->B_y -= 6;
          else if(BASkXP_bop->B_frame<80)BASkXP_bop->B_y -= 7;
          else if(BASkXP_bop->B_frame==80)
          {
               BASkXP_bop->B_y -= 7;
               BASkXP_bop->B_frame = 0;
               BASkXP_bop->B_anim = STOI_PRAWO;
          }
     }
}
void Bop_Anim_Skacze_Up_Lewo(Bop* BASkXL_bop)
{
     BASkXL_bop->B_frame +=1;
     if(BASkXL_bop->B_frame<5)BASkXL_bop->B_y += 7;
     else if(BASkXL_bop->B_frame<9)BASkXL_bop->B_y += 6;
     else if(BASkXL_bop->B_frame<13)BASkXL_bop->B_y += 5;///
     else if(BASkXL_bop->B_frame>68)
     {
          if(BASkXL_bop->B_frame<73)BASkXL_bop->B_y -= 5;///
          else if(BASkXL_bop->B_frame<77)BASkXL_bop->B_y -= 6;
          else if(BASkXL_bop->B_frame<80)BASkXL_bop->B_y -= 7;
          else if(BASkXL_bop->B_frame==80)
          {
               BASkXL_bop->B_y -= 7;
               BASkXL_bop->B_frame = 0;
               BASkXL_bop->B_anim = STOI_LEWO;
          }
     }
}
void Bop_Anim_Skacze_Prawo(Bop* BASkP_bop, int BASkP_key)
{
     BASkP_bop->B_frame +=1;
     if(BASkP_bop->B_frame<5)BASkP_bop->B_y += 7;
     else if(BASkP_bop->B_frame<9)BASkP_bop->B_y += 6;
     else if(BASkP_bop->B_frame<13)BASkP_bop->B_y += 5;///
     else if(BASkP_bop->B_frame>68)
     {
          if(BASkP_bop->B_frame<73)BASkP_bop->B_y -= 5;///
          else if(BASkP_bop->B_frame<77)BASkP_bop->B_y -= 6;
          else if(BASkP_bop->B_frame<80)BASkP_bop->B_y -= 7;
          else if(BASkP_bop->B_frame==80)
          {
               BASkP_bop->B_y -= 7;
               BASkP_bop->B_frame = 0;
               BASkP_bop->B_anim = STOI_PRAWO;
          }
     }
     if(BASkP_key==RIGHT_CROSS_XX)
     {
          if(BASkP_bop->B_x<198)BASkP_bop->B_x += 4;
          else if(BASkP_bop->B_x<200)BASkP_bop->B_x += 2;
     }
     else if(BASkP_key==RIGHT_CROSS_X) BASkP_bop->B_x += 2;
}
void Bop_Anim_Skacze_Lewo(Bop* BASkL_bop, int BASkL_key)
{
     BASkL_bop->B_frame +=1;
     if(BASkL_bop->B_frame<5)BASkL_bop->B_y += 7;
     else if(BASkL_bop->B_frame<9)BASkL_bop->B_y += 6;
     else if(BASkL_bop->B_frame<13)BASkL_bop->B_y += 5;///
     else if(BASkL_bop->B_frame>68)
     {
          if(BASkL_bop->B_frame<73)BASkL_bop->B_y -= 5;///
          else if(BASkL_bop->B_frame<77)BASkL_bop->B_y -= 6;
          else if(BASkL_bop->B_frame<80)BASkL_bop->B_y -= 7;
          else if(BASkL_bop->B_frame==80)
          {
               BASkL_bop->B_y -= 7;
               BASkL_bop->B_frame = 0;
               BASkL_bop->B_anim = STOI_LEWO;
          }
     }
     if(BASkL_key==LEFT_CROSS_XX)
     {
          if(BASkL_bop->B_x>-198)BASkL_bop->B_x -= 4;
          else if(BASkL_bop->B_x>-200)BASkL_bop->B_x -= 2;
     }
     else if(BASkL_key==LEFT_CROSS_X) BASkL_bop->B_x -= 2;
}
void Bop_Anim_Podciecie_Prawo(Bop* BAPP_bop, int BAPP_key)
{
     BAPP_bop->B_hbox = -9999;
     switch(BAPP_key)
                {
                      case LEFT:
                           BAPP_bop->B_anim = IDZIE_LEWO;
                           BAPP_bop->B_frame =1;
                           break;
                      case LEFT_X:
                           if(BAPP_bop->B_x>-200)BAPP_bop->B_x -= 2;
                           BAPP_bop->B_anim = IDZIE_LEWO;
                           BAPP_bop->B_frame =1;
                           break;
                      case RIGHT:
                           BAPP_bop->B_anim = IDZIE_PRAWO;
                           BAPP_bop->B_frame =1;
                           break;
                      case RIGHT_X:
                           if(BAPP_bop->B_x<200)BAPP_bop->B_x += 2;
                           BAPP_bop->B_anim = IDZIE_PRAWO;
                           BAPP_bop->B_frame =1;
                           break;
                      case DOWN:
                      case RIGHT_DOWN:
                      case DOWN_CROSS:
                           BAPP_bop->B_anim = KUCA_PRAWO;
                           break;   
                      case LEFT_DOWN:
                           BAPP_bop->B_anim = KUCA_LEWO;
                           break;   
                      case CROSS:
                           BAPP_bop->B_frame = 0;
                           BAPP_bop->B_anim = SKACZE_UP_PRAWO;
                           Bop_Anim_Skacze_Up_Prawo(BAPP_bop);
                           break;   
                      case RIGHT_CROSS:
                      case RIGHT_CROSS_X:
                      case RIGHT_CROSS_XX:
                           BAPP_bop->B_frame = 0;
                           BAPP_bop->B_anim = SKACZE_PRAWO;
                           Bop_Anim_Skacze_Prawo(BAPP_bop, BAPP_key);
                           break;
                      case LEFT_CROSS:
                      case LEFT_CROSS_X:
                      case LEFT_CROSS_XX:
                           BAPP_bop->B_frame = 0;
                           BAPP_bop->B_anim = SKACZE_LEWO;
                           Bop_Anim_Skacze_Lewo(BAPP_bop, BAPP_key);
                           break; 
                      default:
                           if(BAPP_key>999){}
                           else if(BAPP_key>299)
                           {
                                switch(BAPP_key)
                                     {
                                          case KEY_KLATA_RIGHT_X:
                                          case KEY_KLATA_RIGHT_XX:
                                          case KEY_KLATA_RIGHT_N:
                                               if(BAPP_bop->B_recovery == 0)
                                               {
                                                    BAPP_bop->B_frame = 0;
                                                    BAPP_bop->B_anim = KLATA_PRAWO;
                                                    Bop_Anim_Klata_Prawo(BAPP_bop, BAPP_key);
                                               }
                                               break;
                                          case KEY_SUPERFLY_RIGHT_X:
                                          case KEY_SUPERFLY_RIGHT_XX:
                                          case KEY_SUPERFLY_RIGHT_N:
                                               if(BAPP_bop->B_recovery == 0)
                                               {
                                                    BAPP_bop->B_frame = 0;
                                                    BAPP_bop->B_anim = SUPERFLY_PRAWO;
                                                    Bop_Anim_Superfly_Prawo(BAPP_bop, BAPP_key);
                                               }
                                               break;
                                     }
                           }
                           else if(BAPP_key>99)
                           {
                                 switch(Bop_Anim_Select(BAPP_key))
                                 {
                                         case KEY_OBRKOP:
                                              if(BAPP_bop->B_recovery == 0)
                                              {
                                                   BAPP_bop->B_frame = 0;
                                                   BAPP_bop->B_anim = OBRKOP_PRAWO;
                                                   Bop_Anim_Obrkop_Prawo(BAPP_bop);
                                              }
                                              break;
                                         case KEY_PODCIECIE:
                                              BAPP_bop->B_frame +=1;
                                              if(BAPP_bop->B_frame<21) BAPP_bop->B_hbox = 316+BAPP_bop->B_x;
                                              else if(BAPP_bop->B_frame<41) BAPP_bop->B_hbox = 324+BAPP_bop->B_x;
                                              else if(BAPP_bop->B_frame ==41)
                                              {
                                                   BAPP_bop->B_frame=1;
                                                   BAPP_bop->B_hbox = 316+BAPP_bop->B_x;
                                              }
                                              break;
                                         case KEY_KOLANO:
                                              if(BAPP_bop->B_recovery == 0)
                                              {
                                                   BAPP_bop->B_frame = 0;
                                                   BAPP_bop->B_anim = KOLANO_PRAWO;
                                                   Bop_Anim_Kolano_Prawo(BAPP_bop);
                                              }
                                              break;
                                         case KEY_KLATA:
                                              if(BAPP_bop->B_recovery == 0)
                                              {
                                                   BAPP_bop->B_frame = 0;
                                                   BAPP_bop->B_anim = KLATA_PRAWO;
                                                   Bop_Anim_Klata_Prawo(BAPP_bop, BAPP_key);
                                              }
                                              break;
                                         case KEY_FISTS:
                                              if(BAPP_bop->B_recovery == 0)
                                              {
                                                   BAPP_bop->B_frame = 0;
                                                   BAPP_bop->B_anim = FISTS_PRAWO;
                                                   Bop_Anim_Fists_Prawo(BAPP_bop);
                                              }
                                              break;
                                         case KEY_LAPY:
                                              if(BAPP_bop->B_recovery == 0)
                                              {
                                                   BAPP_bop->B_frame = 0;
                                                   BAPP_bop->B_anim = LAPY_PRAWO;
                                                   Bop_Anim_Lapy_Prawo(BAPP_bop);
                                              }
                                              break;
                                         case KEY_DYNKA:
                                              if(BAPP_bop->B_recovery == 0)
                                              {
                                                   BAPP_bop->B_frame = 0;
                                                   BAPP_bop->B_anim = DYNKA_PRAWO;
                                                   Bop_Anim_Dynka_Prawo(BAPP_bop);
                                              }
                                              break;
                                         case KEY_CHMURKA:
                                              if(BAPP_bop->B_recovery == 0)
                                              {
                                                   BAPP_bop->B_frame = 0;
                                                   BAPP_bop->B_anim = CHMURKA_PRAWO;
                                                   Bop_Anim_Chmurka_Prawo(BAPP_bop, BAPP_key);
                                              }
                                              break;
                                         case KEY_ZIEMIA:
                                              if(BAPP_bop->B_recovery == 0)
                                              {
                                                   BAPP_bop->B_frame = 0;
                                                   BAPP_bop->B_anim = ZIEMIA_PRAWO;
                                                   Bop_Anim_Ziemia_Prawo(BAPP_bop);
                                              }
                                              break;
                                         case KEY_SNIF:
                                              if(BAPP_bop->B_recovery == 0)
                                              {
                                                   BAPP_bop->B_frame = 0;
                                                   BAPP_bop->B_anim = SNIF_PRAWO;
                                                   Bop_Anim_Snif_Prawo(BAPP_bop, BAPP_key);
                                              }
                                              break;
                                         case KEY_KARUZELA:
                                              if(BAPP_bop->B_recovery == 0)
                                              {
                                                   BAPP_bop->B_frame = 0;
                                                   BAPP_bop->B_anim = KARUZELA_PRAWO;
                                                   Bop_Anim_Karuzela_Prawo(BAPP_bop, BAPP_key);
                                              }
                                              break;
                                         default:
                                              BAPP_bop->B_frame = 0;
                                              BAPP_bop->B_anim = STOI_PRAWO;
                                              break;                                         
                                 }
                           }
                           else
                           {
                               BAPP_bop->B_frame = 0;
                               BAPP_bop->B_anim = STOI_PRAWO;
                           }
                           break;
                }
}
void Bop_Anim_Podciecie_Lewo(Bop* BAPL_bop, int BAPL_key)
{
     BAPL_bop->B_hbox = -9999;
     switch(BAPL_key)
                {
                      case LEFT:
                           BAPL_bop->B_anim = IDZIE_LEWO;
                           BAPL_bop->B_frame =1;
                           break;
                      case LEFT_X:
                           if(BAPL_bop->B_x>-200)BAPL_bop->B_x -= 2;
                           BAPL_bop->B_anim = IDZIE_LEWO;
                           BAPL_bop->B_frame =1;
                           break;
                      case RIGHT:
                           BAPL_bop->B_anim = IDZIE_PRAWO;
                           BAPL_bop->B_frame =1;
                           break;
                      case RIGHT_X:
                           if(BAPL_bop->B_x<200)BAPL_bop->B_x += 2;
                           BAPL_bop->B_anim = IDZIE_PRAWO;
                           BAPL_bop->B_frame =1;
                           break;
                      case RIGHT_DOWN:
                           BAPL_bop->B_anim = KUCA_PRAWO;
                           break; 
                      case DOWN:  
                      case LEFT_DOWN:
                      case DOWN_CROSS:
                           BAPL_bop->B_anim = KUCA_LEWO;
                           break;   
                      case CROSS:
                           BAPL_bop->B_frame = 0;
                           BAPL_bop->B_anim = SKACZE_UP_LEWO;
                           Bop_Anim_Skacze_Up_Lewo(BAPL_bop);
                           break;
                      case LEFT_CROSS:
                      case LEFT_CROSS_X:
                      case LEFT_CROSS_XX:
                           BAPL_bop->B_frame = 0;
                           BAPL_bop->B_anim = SKACZE_LEWO;
                           Bop_Anim_Skacze_Lewo(BAPL_bop, BAPL_key);
                           break;    
                      case RIGHT_CROSS:
                      case RIGHT_CROSS_X:
                      case RIGHT_CROSS_XX:
                           BAPL_bop->B_frame = 0;
                           BAPL_bop->B_anim = SKACZE_PRAWO;
                           Bop_Anim_Skacze_Prawo(BAPL_bop, BAPL_key);
                           break;
                      default:
                           if(BAPL_key>999){}
                           else if(BAPL_key>299)
                           {
                                switch(BAPL_key)
                                     {
                                          case KEY_KLATA_LEFT_X:
                                          case KEY_KLATA_LEFT_XX:
                                          case KEY_KLATA_LEFT_N:
                                               if(BAPL_bop->B_recovery == 0)
                                               {
                                                    BAPL_bop->B_frame = 0;
                                                    BAPL_bop->B_anim = KLATA_LEWO;
                                                    Bop_Anim_Klata_Lewo(BAPL_bop, BAPL_key);
                                               }
                                               break;
                                          case KEY_SUPERFLY_LEFT_X:
                                          case KEY_SUPERFLY_LEFT_XX:
                                          case KEY_SUPERFLY_LEFT_N:
                                               if(BAPL_bop->B_recovery == 0)
                                               {
                                                    BAPL_bop->B_frame = 0;
                                                    BAPL_bop->B_anim = SUPERFLY_LEWO;
                                                    Bop_Anim_Superfly_Lewo(BAPL_bop, BAPL_key);
                                               }
                                               break;
                                     }
                           }
                           else if(BAPL_key>99)
                           {
                                 
                                 switch(Bop_Anim_Revers_Select(BAPL_key))
                                 {
                                         case KEY_OBRKOP:
                                              if(BAPL_bop->B_recovery == 0)
                                              {
                                                   BAPL_bop->B_frame = 0;
                                                   BAPL_bop->B_anim = OBRKOP_LEWO;
                                                   Bop_Anim_Obrkop_Lewo(BAPL_bop);
                                              }
                                              break;
                                         case KEY_PODCIECIE:
                                              BAPL_bop->B_frame +=1;
                                              if(BAPL_bop->B_frame<21) BAPL_bop->B_hbox = 164+BAPL_bop->B_x;
                                              else if(BAPL_bop->B_frame<41) BAPL_bop->B_hbox = 156+BAPL_bop->B_x;
                                              else if(BAPL_bop->B_frame == 41)
                                              {
                                                   BAPL_bop->B_frame=1;
                                                   BAPL_bop->B_hbox = 164+BAPL_bop->B_x;
                                              }
                                              break;
                                         case KEY_KOLANO:
                                              if(BAPL_bop->B_recovery == 0)
                                              {
                                                   BAPL_bop->B_frame = 0;
                                                   BAPL_bop->B_anim = KOLANO_LEWO;
                                                   Bop_Anim_Kolano_Lewo(BAPL_bop);
                                              }
                                              break;
                                         case KEY_KLATA:
                                              if(BAPL_bop->B_recovery == 0)
                                              {
                                                   BAPL_bop->B_frame = 0;
                                                   BAPL_bop->B_anim = KLATA_LEWO;
                                                   Bop_Anim_Klata_Lewo(BAPL_bop, BAPL_key);
                                              }
                                              break;
                                         case KEY_FISTS:
                                              if(BAPL_bop->B_recovery == 0)
                                              {
                                                   BAPL_bop->B_frame = 0;
                                                   BAPL_bop->B_anim = FISTS_LEWO;
                                                   Bop_Anim_Fists_Lewo(BAPL_bop);
                                              }
                                              break;
                                         case KEY_LAPY:
                                              if(BAPL_bop->B_recovery == 0)
                                              {
                                                   BAPL_bop->B_frame = 0;
                                                   BAPL_bop->B_anim = LAPY_LEWO;
                                                   Bop_Anim_Lapy_Lewo(BAPL_bop);
                                              }
                                              break;
                                         case KEY_DYNKA:
                                              if(BAPL_bop->B_recovery == 0)
                                              {
                                                   BAPL_bop->B_frame = 0;
                                                   BAPL_bop->B_anim = DYNKA_LEWO;
                                                   Bop_Anim_Dynka_Lewo(BAPL_bop);
                                              }
                                              break;
                                         case KEY_CHMURKA:
                                              if(BAPL_bop->B_recovery == 0)
                                              {
                                                   BAPL_bop->B_frame = 0;
                                                   BAPL_bop->B_anim = CHMURKA_LEWO;
                                                   Bop_Anim_Chmurka_Lewo(BAPL_bop, BAPL_key);
                                              }
                                              break;
                                         case KEY_ZIEMIA:
                                              if(BAPL_bop->B_recovery == 0)
                                              {
                                                   BAPL_bop->B_frame = 0;
                                                   BAPL_bop->B_anim = ZIEMIA_LEWO;
                                                   Bop_Anim_Ziemia_Lewo(BAPL_bop);
                                              }
                                              break;
                                         case KEY_SNIF:
                                              if(BAPL_bop->B_recovery == 0)
                                              {
                                                   BAPL_bop->B_frame = 0;
                                                   BAPL_bop->B_anim = SNIF_LEWO;
                                                   Bop_Anim_Snif_Lewo(BAPL_bop, BAPL_key);
                                              }
                                              break;
                                         case KEY_KARUZELA:
                                              if(BAPL_bop->B_recovery == 0)
                                              {
                                                   BAPL_bop->B_frame = 100;
                                                   BAPL_bop->B_anim = KARUZELA_LEWO;
                                                   Bop_Anim_Karuzela_Lewo(BAPL_bop, BAPL_key);
                                              }
                                              break;
                                         default:
                                              BAPL_bop->B_frame = 0;
                                              BAPL_bop->B_anim = STOI_LEWO;
                                              break;
                                 }
                           }
                           else
                           {
                               BAPL_bop->B_frame = 0;
                               BAPL_bop->B_anim = STOI_LEWO;
                           }
                           break;
                }
}
void Bop_Anim_Obrkop_Prawo(Bop* BAOP_bop)
{
     BAOP_bop->B_frame +=1;     
     if(BAOP_bop->B_frame == 31) BAOP_bop->B_hbox = 340+BAOP_bop->B_x;
     else if(BAOP_bop->B_frame == 41)
     {
         if(BAOP_bop->B_hbox != 9999)BAOP_bop->B_recovery = 30;
         BAOP_bop->B_frame = 0;
         BAOP_bop->B_hbox = -9999;
         BAOP_bop->B_anim = STOI_PRAWO;
     }
}
void Bop_Anim_Obrkop_Lewo(Bop* BAOL_bop)
{
     BAOL_bop->B_frame +=1;
     if(BAOL_bop->B_frame == 31) BAOL_bop->B_hbox = 140+BAOL_bop->B_x;
     else if(BAOL_bop->B_frame == 41)
     {
         if(BAOL_bop->B_hbox != 9999)BAOL_bop->B_recovery = 30;
         BAOL_bop->B_frame = 0;
         BAOL_bop->B_hbox = -9999;
         BAOL_bop->B_anim = STOI_LEWO;
     }
}
void Bop_Anim_Dynka_Prawo(Bop* BADP_bop)
{
     BADP_bop->B_frame +=1;
     if(BADP_bop->B_frame ==1) BADP_bop->B_hbox = 344+BADP_bop->B_x;
     else if(BADP_bop->B_frame >10 && BADP_bop->B_hbox != 9999)
     {
         BADP_bop->B_recovery = 30;
         BADP_bop->B_frame = 0;
         BADP_bop->B_hbox = -9999;
         BADP_bop->B_anim = STOI_PRAWO;
     }
     else if(BADP_bop->B_frame ==41)
     {
         BADP_bop->B_frame = 0;
         BADP_bop->B_hbox = -9999;
         BADP_bop->B_anim = STOI_PRAWO;
     }
}
void Bop_Anim_Dynka_Lewo(Bop* BADL_bop)
{
     BADL_bop->B_frame +=1;
     if(BADL_bop->B_frame ==1) BADL_bop->B_hbox = 136+BADL_bop->B_x;
     else if(BADL_bop->B_frame >10 && BADL_bop->B_hbox != 9999)
     {
         BADL_bop->B_recovery = 30;
         BADL_bop->B_frame = 0;
         BADL_bop->B_hbox = -9999;
         BADL_bop->B_anim = STOI_LEWO;
     }
     else if(BADL_bop->B_frame ==41)
     {
         BADL_bop->B_frame = 0;
         BADL_bop->B_hbox = -9999;
         BADL_bop->B_anim = STOI_LEWO;
     }
}
void Bop_Anim_Kolano_Prawo(Bop* BAKP_bop)
{
     BAKP_bop->B_frame +=1;
     if(BAKP_bop->B_frame ==1) BAKP_bop->B_hbox = 344+BAKP_bop->B_x;
     else if(BAKP_bop->B_frame >10 && BAKP_bop->B_hbox != 9999)
     {
         BAKP_bop->B_recovery = 30;
         BAKP_bop->B_frame = 0;
         BAKP_bop->B_hbox = -9999;
         BAKP_bop->B_anim = STOI_PRAWO;
     }
     else if(BAKP_bop->B_frame ==41)
     {
         BAKP_bop->B_frame = 0;
         BAKP_bop->B_hbox = -9999;
         BAKP_bop->B_anim = STOI_PRAWO;
     }
}
void Bop_Anim_Kolano_Lewo(Bop* BAKL_bop)
{
     BAKL_bop->B_frame +=1;
     if(BAKL_bop->B_frame ==1) BAKL_bop->B_hbox = 136+BAKL_bop->B_x;
     else if(BAKL_bop->B_frame >10 && BAKL_bop->B_hbox != 9999)
     {
         BAKL_bop->B_recovery = 30;
         BAKL_bop->B_frame = 0;
         BAKL_bop->B_hbox = -9999;
         BAKL_bop->B_anim = STOI_LEWO;
     }
     else if(BAKL_bop->B_frame ==41)
     {
         BAKL_bop->B_frame = 0;
         BAKL_bop->B_hbox = -9999;
         BAKL_bop->B_anim = STOI_LEWO;
     }
}
void Bop_Anim_Lapy_Prawo(Bop* BALP_bop)
{
     BALP_bop->B_frame +=1;
     if(BALP_bop->B_frame == 11) BALP_bop->B_hbox = 316+BALP_bop->B_x;
     else if(BALP_bop->B_frame == 21)
     {
         if(BALP_bop->B_hbox != 9999)BALP_bop->B_recovery = 30;
         BALP_bop->B_frame = 0;
         BALP_bop->B_hbox = -9999;
         BALP_bop->B_anim = STOI_PRAWO;
     }  
}
void Bop_Anim_Lapy_Lewo(Bop* BALL_bop)
{
     BALL_bop->B_frame +=1;
     if(BALL_bop->B_frame == 11) BALL_bop->B_hbox = 164+BALL_bop->B_x;
     else if(BALL_bop->B_frame == 21)
     {
         if(BALL_bop->B_hbox != 9999)BALL_bop->B_recovery = 30;
         BALL_bop->B_frame = 0;
         BALL_bop->B_hbox = -9999;
         BALL_bop->B_anim = STOI_LEWO;
     }
}
void Bop_Anim_Fists_Prawo(Bop* BAFP_bop)
{
     BAFP_bop->B_frame +=1;
     if(BAFP_bop->B_frame == 1) BAFP_bop->B_hbox = 328+BAFP_bop->B_x;
     else if(BAFP_bop->B_frame == 11) BAFP_bop->B_hbox = 340+BAFP_bop->B_x;
     else if(BAFP_bop->B_frame == 21)
     {
         if(BAFP_bop->B_hbox != 9999)BAFP_bop->B_recovery = 30;
         BAFP_bop->B_frame = 0;
         BAFP_bop->B_hbox = -9999;
         BAFP_bop->B_anim = STOI_PRAWO;
     }  
}
void Bop_Anim_Fists_Lewo(Bop* BAFL_bop)
{
     BAFL_bop->B_frame +=1;
     if(BAFL_bop->B_frame == 1) BAFL_bop->B_hbox = 152+BAFL_bop->B_x;
     else if(BAFL_bop->B_frame == 11) BAFL_bop->B_hbox = 140+BAFL_bop->B_x;
     else if(BAFL_bop->B_frame == 21)
     {
         if(BAFL_bop->B_hbox != 9999)BAFL_bop->B_recovery = 30;
         BAFL_bop->B_frame = 0;
         BAFL_bop->B_hbox = -9999;
         BAFL_bop->B_anim = STOI_LEWO;
     }
}
void Bop_Anim_Ziemia_Prawo(Bop* BAZP_bop)
{
     BAZP_bop->B_frame +=1;
     if(BAZP_bop->B_frame ==1) BAZP_bop->B_hbox = 344+BAZP_bop->B_x;
     else if(BAZP_bop->B_frame >10 && BAZP_bop->B_hbox != 9999)
     {
         BAZP_bop->B_recovery = 30;
         BAZP_bop->B_frame = 0;
         BAZP_bop->B_hbox = -9999;
         BAZP_bop->B_anim = STOI_PRAWO;
     }
     else if(BAZP_bop->B_frame ==41)
     {
         BAZP_bop->B_frame = 0;
         BAZP_bop->B_hbox = -9999;
         BAZP_bop->B_anim = STOI_PRAWO;
     }
}
void Bop_Anim_Ziemia_Lewo(Bop* BAZL_bop)
{
     BAZL_bop->B_frame +=1;
     if(BAZL_bop->B_frame ==1) BAZL_bop->B_hbox = 136+BAZL_bop->B_x;
     else if(BAZL_bop->B_frame >10 && BAZL_bop->B_hbox != 9999)
     {
         BAZL_bop->B_recovery = 30;
         BAZL_bop->B_frame = 0;
         BAZL_bop->B_hbox = -9999;
         BAZL_bop->B_anim = STOI_LEWO;
     }
     else if(BAZL_bop->B_frame ==41)
     {
         BAZL_bop->B_frame = 0;
         BAZL_bop->B_hbox = -9999;
         BAZL_bop->B_anim = STOI_LEWO;
     }
}
void Bop_Anim_Klata_Prawo(Bop* BAKP_bop, int BAKP_key)
{
     BAKP_bop->B_frame +=1;
     if(BAKP_bop->B_frame ==1)
     {
         BAKP_bop->B_hbox = 278+BAKP_bop->B_x;
         BAKP_bop->B_y = 2;
     }
     else if(BAKP_bop->B_frame ==21)
     {
         BAKP_bop->B_recovery = 10;
         BAKP_bop->B_frame = 0;
         BAKP_bop->B_y = 0;
         BAKP_bop->B_hbox = -9999;
         BAKP_bop->B_anim = STOI_PRAWO;
     }
     else if(BAKP_bop->B_frame <11) BAKP_bop->B_y += 2;
     else if(BAKP_bop->B_frame <21) BAKP_bop->B_y -= 2;
     
     if(BAKP_key==KEY_KLATA_RIGHT_XX)
     {
          if(BAKP_bop->B_x<198)BAKP_bop->B_x += 4;
          else if(BAKP_bop->B_x<200)BAKP_bop->B_x += 2;
     }
     else if(BAKP_key==KEY_KLATA_RIGHT_X) BAKP_bop->B_x += 2;
}
void Bop_Anim_Klata_Lewo(Bop* BAKL_bop, int BAKL_key)
{
     BAKL_bop->B_frame +=1;
     if(BAKL_bop->B_frame ==1)
     {
         BAKL_bop->B_hbox = 202+BAKL_bop->B_x;
         BAKL_bop->B_y = 2;
     }
     else if(BAKL_bop->B_frame ==21)
     {
         BAKL_bop->B_recovery = 10;
         BAKL_bop->B_frame = 0;
         BAKL_bop->B_y = 0;
         BAKL_bop->B_hbox = -9999;
         BAKL_bop->B_anim = STOI_LEWO;
     }
     else if(BAKL_bop->B_frame <11) BAKL_bop->B_y += 2;
     else if(BAKL_bop->B_frame <21) BAKL_bop->B_y -= 2;
     
     if(BAKL_key==KEY_KLATA_LEFT_XX)
     {
          if(BAKL_bop->B_x>-198)BAKL_bop->B_x -= 4;
          else if(BAKL_bop->B_x>-200)BAKL_bop->B_x -= 2;
     }
     else if(BAKL_key==KEY_KLATA_LEFT_X) BAKL_bop->B_x -= 2;
}
void Bop_Anim_Superfly_Prawo(Bop* BASP_bop, int BASP_key)
{
     BASP_bop->B_frame +=1;
     if(BASP_key==KEY_SUPERFLY_RIGHT_XX)
     {
          if(BASP_bop->B_x<198) BASP_bop->B_x += 4;
          else if(BASP_bop->B_x<200) BASP_bop->B_x += 2;
     }
     else if(BASP_key==KEY_SUPERFLY_RIGHT_X) BASP_bop->B_x += 2;
     
     if(BASP_bop->B_frame<5)BASP_bop->B_y += 7;
     else if(BASP_bop->B_frame<9)BASP_bop->B_y += 6;
     else if(BASP_bop->B_frame<23) BASP_bop->B_hbox = 332+BASP_bop->B_x;
     else if(BASP_bop->B_frame>22)
     {
          BASP_bop->B_hbox = -9999;
          if(BASP_bop->B_frame<27)BASP_bop->B_y -= 6;
          else if(BASP_bop->B_frame<30)BASP_bop->B_y -= 7;
          else if(BASP_bop->B_frame==30)
          {
               BASP_bop->B_recovery = 30;
               BASP_bop->B_y -= 7;
               BASP_bop->B_frame = 0;
               BASP_bop->B_anim = STOI_PRAWO;
          }
     }
}
void Bop_Anim_Superfly_Lewo(Bop* BASL_bop, int BASL_key)
{
     BASL_bop->B_frame +=1;
     if(BASL_key==KEY_SUPERFLY_LEFT_XX)
     {
          if(BASL_bop->B_x>-198) BASL_bop->B_x -= 4;
          else if(BASL_bop->B_x>-200) BASL_bop->B_x -= 2;
     }
     else if(BASL_key==KEY_SUPERFLY_LEFT_X) BASL_bop->B_x -= 2;
     
     if(BASL_bop->B_frame<5)BASL_bop->B_y += 7;
     else if(BASL_bop->B_frame<9)BASL_bop->B_y += 6;
     else if(BASL_bop->B_frame<23) BASL_bop->B_hbox = 148+BASL_bop->B_x;
     else if(BASL_bop->B_frame>22)
     {
          BASL_bop->B_hbox = -9999;
          if(BASL_bop->B_frame<27)BASL_bop->B_y -= 6;
          else if(BASL_bop->B_frame<30)BASL_bop->B_y -= 7;
          else if(BASL_bop->B_frame==30)
          {
               BASL_bop->B_recovery = 30;
               BASL_bop->B_y -= 7;
               BASL_bop->B_frame = 0;
               BASL_bop->B_anim = STOI_LEWO;
          }
     }
}
void Bop_Anim_Snif_Prawo(Bop* BASP_bop, int BASP_key)
{
     BASP_bop->B_frame +=1;
     if(BASP_bop->B_frame ==1) BASP_bop->B_hbox = 344+BASP_bop->B_x;
     else if(BASP_bop->B_frame >10)
     {
         if(Bop_Anim_Select(BASP_key)!=KEY_SNIF)
         {
             BASP_bop->B_frame = 0;
             BASP_bop->B_hbox = -9999;
             BASP_bop->B_anim = STOI_PRAWO;
         }
         else if(BASP_bop->B_hbox != 9999)
         {
             BASP_bop->B_recovery = 30;
             BASP_bop->B_frame = 0;
             BASP_bop->B_hbox = -9999;
             BASP_bop->B_anim = STOI_PRAWO;
         }
         else
         {
             if(BASP_bop->B_frame >30) BASP_bop->B_frame = 11;
         }
     }
}
void Bop_Anim_Snif_Lewo(Bop* BASL_bop, int BASL_key)
{
     BASL_bop->B_frame +=1;
     if(BASL_bop->B_frame ==1) BASL_bop->B_hbox = 136+BASL_bop->B_x;
     else if(BASL_bop->B_frame >10)
     {
         if(Bop_Anim_Revers_Select(BASL_key)!=KEY_SNIF)
         {
             BASL_bop->B_frame = 0;
             BASL_bop->B_hbox = -9999;
             BASL_bop->B_anim = STOI_LEWO;
         }
         else if(BASL_bop->B_hbox != 9999) 
         {
             BASL_bop->B_recovery = 30;
             BASL_bop->B_frame = 0;
             BASL_bop->B_hbox = -9999;
             BASL_bop->B_anim = STOI_LEWO;
         }
         else
         {
             if(BASL_bop->B_frame >30) BASL_bop->B_frame = 11;
         }
     }
}
void Bop_Anim_Karuzela_Prawo(Bop* BAKP_bop, int BAKP_key)
{
     BAKP_bop->B_frame +=1;
     if(BAKP_bop->B_frame ==1) BAKP_bop->B_hbox = 344+BAKP_bop->B_x;
     else if(BAKP_bop->B_frame >50)
     {
         if(Bop_Anim_Select(BAKP_key)!=KEY_KARUZELA)
         {
             BAKP_bop->B_anim = STOI_PRAWO;
             BAKP_bop->B_frame = 0;
             BAKP_bop->B_hbox = -9999;
         }
         else BAKP_bop->B_frame = 11;
     }
     else if(BAKP_bop->B_frame >40);
     else if(BAKP_bop->B_frame >30)
     {
         if(Bop_Anim_Select(BAKP_key)!=KEY_KARUZELA)
         {
             BAKP_bop->B_anim = STOI_LEWO;
             BAKP_bop->B_frame = 0;
             BAKP_bop->B_hbox = -9999;
         }
     }
     else if(BAKP_bop->B_frame >20);
     else if(BAKP_bop->B_frame >10)
     {
         if(BAKP_bop->B_hbox != 9999)
         {
             BAKP_bop->B_recovery = 30;
             BAKP_bop->B_anim = STOI_PRAWO;
             BAKP_bop->B_frame = 0;
             BAKP_bop->B_hbox = -9999;
         }
         else if(Bop_Anim_Select(BAKP_key)!=KEY_KARUZELA)
         {
             BAKP_bop->B_anim = STOI_PRAWO;
             BAKP_bop->B_frame = 0;
             BAKP_bop->B_hbox = -9999;
         }
     }
}
void Bop_Anim_Karuzela_Lewo(Bop* BAKL_bop, int BAKL_key)
{
     BAKL_bop->B_frame +=1;
     if(BAKL_bop->B_frame ==111) BAKL_bop->B_hbox = 136+BAKL_bop->B_x;
     else if(BAKL_bop->B_frame >150)
     {
         if(Bop_Anim_Revers_Select(BAKL_key)!=KEY_KARUZELA)
         {
             BAKL_bop->B_anim = STOI_LEWO;
             BAKL_bop->B_frame = 0;
             BAKL_bop->B_hbox = -9999;
         }
         else BAKL_bop->B_frame = 111;
     }
     else if(BAKL_bop->B_frame >140);
     else if(BAKL_bop->B_frame >130)
     {
         if(Bop_Anim_Revers_Select(BAKL_key)!=KEY_KARUZELA)
         {
             BAKL_bop->B_anim = STOI_PRAWO;
             BAKL_bop->B_frame = 0;
             BAKL_bop->B_hbox = -9999;
         }
     }
     else if(BAKL_bop->B_frame >120);
     else if(BAKL_bop->B_frame >110)
     {
         if(BAKL_bop->B_hbox != 9999)
         {
             BAKL_bop->B_recovery = 30;
             BAKL_bop->B_anim = STOI_LEWO;
             BAKL_bop->B_frame = 0;
             BAKL_bop->B_hbox = -9999;
         }
         else if(Bop_Anim_Revers_Select(BAKL_key)!=KEY_KARUZELA)
         {
             BAKL_bop->B_anim = STOI_LEWO;
             BAKL_bop->B_frame = 0;
             BAKL_bop->B_hbox = -9999;
         }
     }
}
void Bop_Anim_Chmurka_Prawo(Bop* BACP_bop, int BACP_key)
{
     BACP_bop->B_frame +=1;
     if(BACP_bop->B_frame ==1) BACP_bop->B_hbox = 344+BACP_bop->B_x;
     else if(BACP_bop->B_frame >70)
     {
         BACP_bop->B_frame = 0;
         BACP_bop->B_hbox = -9999;
         BACP_bop->B_anim = STOI_PRAWO;
     }
     else if(BACP_bop->B_frame >60);
     else if(BACP_bop->B_frame >30)
     {
         if(Bop_Anim_Select(BACP_key)==KEY_CHMURKA)
         {
             if(BACP_bop->B_frame ==51) BACP_bop->B_frame = 31;
         }
         else
         {
             BACP_bop->B_frame = 61;
         }
     }
     else if(BACP_bop->B_frame >10)
     {
         if(BACP_bop->B_hbox != 9999)
         {
             BACP_bop->B_recovery = 30;
             BACP_bop->B_frame = 0;
             BACP_bop->B_hbox = -9999;
             BACP_bop->B_anim = STOI_PRAWO;
         }
         else if(Bop_Anim_Select(BACP_key)!=KEY_CHMURKA)
         {
             BACP_bop->B_frame = 0;
             BACP_bop->B_hbox = -9999;
             BACP_bop->B_anim = STOI_PRAWO;
         }
     }
}
void Bop_Anim_Chmurka_Lewo(Bop* BACL_bop, int BACL_key)
{
     BACL_bop->B_frame +=1;
     if(BACL_bop->B_frame ==1) BACL_bop->B_hbox = 136+BACL_bop->B_x;
     else if(BACL_bop->B_frame >70)
     {
         BACL_bop->B_frame = 0;
         BACL_bop->B_hbox = -9999;
         BACL_bop->B_anim = STOI_LEWO;
     }
     else if(BACL_bop->B_frame >60);
     else if(BACL_bop->B_frame >30)
     {
         if(Bop_Anim_Revers_Select(BACL_key)==KEY_CHMURKA)
         {
             if(BACL_bop->B_frame ==51) BACL_bop->B_frame = 31;
         }
         else
         {
             BACL_bop->B_frame = 61;
         }
     }
     else if(BACL_bop->B_frame >10)
     {
         if(BACL_bop->B_hbox != 9999)
         {
             BACL_bop->B_recovery = 30;
             BACL_bop->B_frame = 0;
             BACL_bop->B_hbox = -9999;
             BACL_bop->B_anim = STOI_LEWO;
         }
         else if(Bop_Anim_Revers_Select(BACL_key)!=KEY_CHMURKA)
         {
             BACL_bop->B_frame = 0;
             BACL_bop->B_hbox = -9999;
             BACL_bop->B_anim = STOI_LEWO;
         }
     }
}
void Bop_Anim_Trafiony_Prawo(Bop* BATP_bop)
{
     BATP_bop->B_frame +=1;
     if(BATP_bop->B_y>0) BATP_bop->B_y-=8;
     else if(BATP_bop->B_y<0) BATP_bop->B_y = 0;
     if(BATP_bop->B_frame ==21)
     {
          BATP_bop->B_frame = 0;
          BATP_bop->B_y = 0;
          if(BATP_bop->B_energy)BATP_bop->B_anim = STOI_PRAWO;
          else BATP_bop->B_anim = LEZY_PRAWO;
     }
}
void Bop_Anim_Trafiony_Lewo(Bop* BATL_bop)
{
     BATL_bop->B_frame +=1;
     if(BATL_bop->B_y>0) BATL_bop->B_y-=8;
     else if(BATL_bop->B_y<0) BATL_bop->B_y = 0;
     if(BATL_bop->B_frame ==21)
     {
          BATL_bop->B_frame = 0;
          BATL_bop->B_y = 0;
          if(BATL_bop->B_energy)BATL_bop->B_anim = STOI_LEWO;
          else BATL_bop->B_anim = LEZY_LEWO;
     }
}
void Bop_Anim_Lezy_Prawo(Bop* BALP_bop)
{
     BALP_bop->B_frame +=1;
     if(BALP_bop->B_frame == 30)
     {
          if(BALP_bop->B_energy <= 0)
          {
               BALP_bop->B_energy = -1;
               BALP_bop->B_live -= 1;
          }
          else
          {
               BALP_bop->B_frame = 0;
               BALP_bop->B_anim = STOI_PRAWO;
          }
     }
}
void Bop_Anim_Lezy_Lewo(Bop* BALL_bop)
{
     BALL_bop->B_frame +=1;
     if(BALL_bop->B_frame == 30)
     {
          if(BALL_bop->B_energy <= 0)
          {
               BALL_bop->B_energy = -1;
               BALL_bop->B_live -= 1;
          }
          else
          {
               BALL_bop->B_frame = 0;
               BALL_bop->B_anim = STOI_LEWO;
          }
     }
}
void Bop_Hit_Enemy(Bop* BHE_bop)
{
     switch(BHE_bop->B_anim)
     {
          case SUPERFLY_LEWO:
          case SUPERFLY_PRAWO:
          case OBRKOP_LEWO:
          case OBRKOP_PRAWO:
          case KOLANO_LEWO:
          case KOLANO_PRAWO:
          case FISTS_LEWO:
          case FISTS_PRAWO:
          case LAPY_LEWO:
          case LAPY_PRAWO:
          case DYNKA_LEWO:
          case DYNKA_PRAWO:
          case CHMURKA_PRAWO:
          case CHMURKA_LEWO:
          case SNIF_PRAWO:
          case SNIF_LEWO:
          case ZIEMIA_LEWO:
          case ZIEMIA_PRAWO:
          case KARUZELA_LEWO:
          case KARUZELA_PRAWO:
               BHE_bop->B_hbox = 9999;
               break;
     }
}
void Bop_Demage(Bop* BD_bop, int BD_strength)
{
     switch(BD_bop->B_anim)
     {
           case STOI_PRAWO:
           case KUCA_PRAWO:
           case IDZIE_PRAWO:
           case SKACZE_UP_PRAWO:
           case SKACZE_PRAWO:
           case SUPERFLY_PRAWO:
           case OBRKOP_PRAWO:
           case PODCIECIE_PRAWO:
           case KOLANO_PRAWO:
           case KLATA_PRAWO:
           case FISTS_PRAWO:
           case LAPY_PRAWO:
           case DYNKA_PRAWO:
           case CHMURKA_PRAWO:
           case SNIF_PRAWO:
           case ZIEMIA_PRAWO:
           case KARUZELA_PRAWO:
                BD_bop->B_recovery = 0;
                BD_bop->B_frame = 0;
                BD_bop->B_hbox = -9999;
                BD_bop->B_energy -= BD_strength;
                if(BD_bop->B_energy<0) BD_bop->B_energy = 0;
                BD_bop->B_anim = TRAFIONY_PRAWO;
                Bop_Anim_Trafiony_Prawo(BD_bop);
                break;
           case STOI_LEWO:
           case KUCA_LEWO:
           case IDZIE_LEWO:
           case SKACZE_UP_LEWO:
           case SKACZE_LEWO:
           case SUPERFLY_LEWO:
           case OBRKOP_LEWO:
           case PODCIECIE_LEWO:
           case KOLANO_LEWO:
           case KLATA_LEWO:
           case FISTS_LEWO:
           case LAPY_LEWO:
           case DYNKA_LEWO:
           case CHMURKA_LEWO:
           case SNIF_LEWO:
           case ZIEMIA_LEWO:
           case KARUZELA_LEWO:
                BD_bop->B_recovery = 0;
                BD_bop->B_frame = 0;
                BD_bop->B_hbox = -9999;
                BD_bop->B_energy -= BD_strength;
                if(BD_bop->B_energy<0) BD_bop->B_energy = 0;
                BD_bop->B_anim = TRAFIONY_LEWO;
                Bop_Anim_Trafiony_Lewo(BD_bop);
                break;
     }
}
extern int Bop_Check_Hit(Stage* BCH_stage, Bop* BCH_bop, int BCH_enemy_HB[3], int BCH_strength)
{
     if(BCH_enemy_HB[0]>=BCH_bop->B_bbox[0][0])
     {
          if(BCH_enemy_HB[0]<=BCH_bop->B_bbox[1][0])
          {
               if(BCH_enemy_HB[1]>BCH_bop->B_bbox[0][1])
               {
                    if(BCH_enemy_HB[1]<BCH_bop->B_bbox[1][1])
                    {
                         Bop_Demage(BCH_bop, BCH_strength);
                         Stage_Bop_Trafiony(BCH_stage, BCH_strength);
                         BCH_strength = 9999;
                    }
               }
               else if(BCH_enemy_HB[2]>BCH_bop->B_bbox[0][1])
               {
                    if(BCH_enemy_HB[2]<BCH_bop->B_bbox[1][1])
                    {
                         Bop_Demage(BCH_bop, BCH_strength);
                         Stage_Bop_Trafiony(BCH_stage, BCH_strength);
                         BCH_strength = 9999;
                    }
               }
               else if(BCH_enemy_HB[1]<BCH_bop->B_bbox[0][1])
               {
                    if(BCH_enemy_HB[2]>BCH_bop->B_bbox[1][1])
                    {
                         Bop_Demage(BCH_bop, BCH_strength);
                         Stage_Bop_Trafiony(BCH_stage, BCH_strength);
                         BCH_strength = 9999;
                    }
               }
          }
     }
     return BCH_strength;
}
void Bop_Time_Over(Bop* BTO_bop)
{
     switch(BTO_bop->B_anim)
     {
           case STOI_PRAWO:
           case KUCA_PRAWO:
           case IDZIE_PRAWO:
           case SKACZE_UP_PRAWO:
           case SKACZE_PRAWO:
           case SUPERFLY_PRAWO:
           case OBRKOP_PRAWO:
           case PODCIECIE_PRAWO:
           case KOLANO_PRAWO:
           case KLATA_PRAWO:
           case FISTS_PRAWO:
           case LAPY_PRAWO:
           case DYNKA_PRAWO:
           case CHMURKA_PRAWO:
           case SNIF_PRAWO:
           case ZIEMIA_PRAWO:
           case KARUZELA_PRAWO:
                BTO_bop->B_recovery = 0;
                BTO_bop->B_frame = 0;
                BTO_bop->B_hbox = -9999;
                BTO_bop->B_energy = 0;
                BTO_bop->B_anim = TRAFIONY_PRAWO;
                Bop_Anim_Trafiony_Prawo(BTO_bop);
                break;
           case STOI_LEWO:
           case KUCA_LEWO:
           case IDZIE_LEWO:
           case SKACZE_UP_LEWO:
           case SKACZE_LEWO:
           case SUPERFLY_LEWO:
           case OBRKOP_LEWO:
           case PODCIECIE_LEWO:
           case KOLANO_LEWO:
           case KLATA_LEWO:
           case FISTS_LEWO:
           case LAPY_LEWO:
           case DYNKA_LEWO:
           case CHMURKA_LEWO:
           case SNIF_LEWO:
           case ZIEMIA_LEWO:
           case KARUZELA_LEWO:
                BTO_bop->B_recovery = 0;
                BTO_bop->B_frame = 0;
                BTO_bop->B_hbox = -9999;
                BTO_bop->B_energy = 0;
                BTO_bop->B_anim = TRAFIONY_LEWO;
                Bop_Anim_Trafiony_Lewo(BTO_bop);
                break;
           case TRAFIONY_LEWO:
                BTO_bop->B_recovery = 0;
                BTO_bop->B_energy = 0;
                Bop_Anim_Trafiony_Lewo(BTO_bop);
                break;
           case TRAFIONY_PRAWO:
                BTO_bop->B_recovery = 0;
                BTO_bop->B_energy = 0;
                Bop_Anim_Trafiony_Prawo(BTO_bop);
                break;
           case LEZY_LEWO:
                BTO_bop->B_recovery = 0;
                BTO_bop->B_energy = 0;
                Bop_Anim_Lezy_Lewo(BTO_bop);
                break;
           case LEZY_PRAWO:
                BTO_bop->B_recovery = 0;
                BTO_bop->B_energy = 0;
                Bop_Anim_Lezy_Prawo(BTO_bop);
                break;
     }
}
void Bop_Draw(Bop* BD_bop)
{
     switch(BD_bop->B_anim)
     {
           case STOI_PRAWO:
                blitAlphaImageToScreen(0, 0, 80, 168, BD_bop->B_image[0], 200+BD_bop->B_x, 72);
                BD_bop->B_bbox[0][0] = 212+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 72;
                BD_bop->B_bbox[1][0] = 276+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 240;
                break;
           case STOI_LEWO:
                blitAlphaImageToScreen(400, 0, 80, 168, BD_bop->B_image[1], 200+BD_bop->B_x, 72);
                BD_bop->B_bbox[0][0] = 204+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 76;
                BD_bop->B_bbox[1][0] = 268+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 240;
                break;
           case KUCA_PRAWO:
                blitAlphaImageToScreen(380, 152, 96, 84, BD_bop->B_image[2], 192+BD_bop->B_x, 156);
                BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 160;
                BD_bop->B_bbox[1][0] = 288+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 240;
                break;
           case KUCA_LEWO:
                blitAlphaImageToScreen(0, 152, 96, 84, BD_bop->B_image[3], 192+BD_bop->B_x, 156);
                BD_bop->B_bbox[0][0] = 192+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 160;
                BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 240;
                break;
           case IDZIE_PRAWO:
                if(BD_bop->B_frame<25)
                {
                     blitAlphaImageToScreen(320, 0, 64, 168, BD_bop->B_image[0], 208+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 212+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 268+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<49)
                {
                     blitAlphaImageToScreen(80, 0, 84, 168, BD_bop->B_image[0], 198+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 202+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 262+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<73)
                {
                     blitAlphaImageToScreen(164, 0, 64, 168, BD_bop->B_image[0], 208+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 212+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 268+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<97)
                {
                     blitAlphaImageToScreen(228, 0, 92, 168, BD_bop->B_image[0], 194+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 198+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 274+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case IDZIE_LEWO:
                if(BD_bop->B_frame<25)
                {
                     blitAlphaImageToScreen(96, 0, 64, 168, BD_bop->B_image[1], 208+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 212+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 268+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<49)
                {
                     blitAlphaImageToScreen(316, 0, 84, 168, BD_bop->B_image[1], 198+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 218+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 278+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<73)
                {
                     blitAlphaImageToScreen(252, 0, 64, 168, BD_bop->B_image[1], 208+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 212+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 268+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<97)
                {
                     blitAlphaImageToScreen(160, 0, 92, 168, BD_bop->B_image[1], 194+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 206+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 282+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case SKACZE_UP_PRAWO:
                blitAlphaImageToScreen(352, 0, 96, 148, BD_bop->B_image[10], 192+BD_bop->B_x, 72-BD_bop->B_y);
                BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 216-BD_bop->B_y;
                break;
           case SKACZE_UP_LEWO:
                blitAlphaImageToScreen(0, 0, 96, 148, BD_bop->B_image[11], 192+BD_bop->B_x, 72-BD_bop->B_y);
                BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 216-BD_bop->B_y;
                break;
           case SKACZE_PRAWO:
                blitAlphaImageToScreen(352, 0, 96, 148, BD_bop->B_image[10], 192+BD_bop->B_x, 72-BD_bop->B_y);
                BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 216-BD_bop->B_y;
                break;
           case SKACZE_LEWO:
                blitAlphaImageToScreen(0, 0, 96, 148, BD_bop->B_image[11], 192+BD_bop->B_x, 72-BD_bop->B_y);
                BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 216-BD_bop->B_y;
                break;
           case PODCIECIE_PRAWO:
                if(BD_bop->B_frame>20) blitAlphaImageToScreen(0, 0, 132, 128, BD_bop->B_image[10], 192+BD_bop->B_x, 112);
                else blitAlphaImageToScreen(132, 0, 124, 128, BD_bop->B_image[10], 192+BD_bop->B_x, 112);
                BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 116;
                BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 240;
                break;
           case PODCIECIE_LEWO:
                if(BD_bop->B_frame>20) blitAlphaImageToScreen(316, 0, 132, 128, BD_bop->B_image[11], 156+BD_bop->B_x, 112);
                else blitAlphaImageToScreen(192, 0, 124, 128, BD_bop->B_image[11], 164+BD_bop->B_x, 112);
                BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 116;
                BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 240;
                break;
           case OBRKOP_PRAWO:
                if(BD_bop->B_frame<11)
                {
                     blitAlphaImageToScreen(84, 0, 84, 168, BD_bop->B_image[2], 196+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 200+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 268+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)      
                {
                     blitAlphaImageToScreen(212, 0, 88, 156, BD_bop->B_image[4], 156+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 164+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 240+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<31)      
                {
                     blitAlphaImageToScreen(0, 128, 96, 144, BD_bop->B_image[10], 200+BD_bop->B_x, 96);
                     BD_bop->B_bbox[0][0] = 204+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 100;
                     BD_bop->B_bbox[1][0] = 288+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<41)      
                {
                     blitAlphaImageToScreen(300, 0, 144, 156, BD_bop->B_image[4], 196+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 200+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 260+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case OBRKOP_LEWO:
                if(BD_bop->B_frame<11)                 
                {
                     blitAlphaImageToScreen(308, 0, 84, 168, BD_bop->B_image[3], 200+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 212+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 280+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)            
                {
                     blitAlphaImageToScreen(144, 0, 88, 156, BD_bop->B_image[5], 236+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 240+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 316+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<31)                 
                {
                     blitAlphaImageToScreen(352, 128, 96, 144, BD_bop->B_image[11], 184+BD_bop->B_x, 96);
                     BD_bop->B_bbox[0][0] = 192+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 100;
                     BD_bop->B_bbox[1][0] = 276+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<41)                 
                {
                     blitAlphaImageToScreen(0, 0, 144, 156, BD_bop->B_image[5], 140+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 220+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 280+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case DYNKA_PRAWO:
                if(BD_bop->B_frame<11)              
                {
                     blitAlphaImageToScreen(144, 0, 144, 164, BD_bop->B_image[6], 200+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 232+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 292+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)              
                {
                     blitAlphaImageToScreen(96, 0, 116, 156, BD_bop->B_image[4], 140+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 144+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<31)              
                {
                     blitAlphaImageToScreen(256, 0, 96, 148, BD_bop->B_image[10], 200+BD_bop->B_x, 92);
                     BD_bop->B_bbox[0][0] = 216+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 96;
                     BD_bop->B_bbox[1][0] = 288+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<41)              
                {
                     blitAlphaImageToScreen(96, 0, 116, 156, BD_bop->B_image[4], 140+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 144+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case DYNKA_LEWO:
                if(BD_bop->B_frame<11)                
                {
                     blitAlphaImageToScreen(140, 0, 144, 164, BD_bop->B_image[7], 136+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 188+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 248+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)                
                {
                     blitAlphaImageToScreen(232, 0, 116, 156, BD_bop->B_image[5], 224+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 336+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<31)                
                {
                     blitAlphaImageToScreen(96, 0, 96, 148, BD_bop->B_image[11], 184+BD_bop->B_x, 92);
                     BD_bop->B_bbox[0][0] = 192+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 96;
                     BD_bop->B_bbox[1][0] = 264+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<41)                
                {
                     blitAlphaImageToScreen(232, 0, 116, 156, BD_bop->B_image[5], 224+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 336+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           
           case KOLANO_PRAWO:
                if(BD_bop->B_frame<11)              
                {
                     blitAlphaImageToScreen(144, 0, 144, 164, BD_bop->B_image[6], 200+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 232+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 292+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)              
                {
                     blitAlphaImageToScreen(96, 0, 116, 156, BD_bop->B_image[4], 140+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 144+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<31)              
                {
                     blitAlphaImageToScreen(384, 0, 96, 168, BD_bop->B_image[0], 144+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 148+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 72;
                     BD_bop->B_bbox[1][0] = 204+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<41)              
                {
                     blitAlphaImageToScreen(96, 0, 116, 156, BD_bop->B_image[4], 140+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 144+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case KOLANO_LEWO:
                if(BD_bop->B_frame<11)                
                {
                     blitAlphaImageToScreen(140, 0, 144, 164, BD_bop->B_image[7], 136+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 188+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 248+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)                
                {
                     blitAlphaImageToScreen(232, 0, 116, 156, BD_bop->B_image[5], 224+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 336+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<31)                
                {
                     blitAlphaImageToScreen(0, 0, 96, 168, BD_bop->B_image[1], 240+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 276+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 72;
                     BD_bop->B_bbox[1][0] = 332+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<41)                
                {
                     blitAlphaImageToScreen(232, 0, 116, 156, BD_bop->B_image[5], 224+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 336+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case TRAFIONY_PRAWO:
                blitAlphaImageToScreen(0, 0, 96, 156, BD_bop->B_image[4], 192+BD_bop->B_x, 84-BD_bop->B_y);
                break;
           case TRAFIONY_LEWO:
                blitAlphaImageToScreen(348, 0, 96, 156, BD_bop->B_image[5], 192+BD_bop->B_x, 84-BD_bop->B_y);
                break;
           case LEZY_PRAWO:
                if(BD_bop->B_frame<15) blitAlphaImageToScreen(224, 0, 92, 152, BD_bop->B_image[8], 194+BD_bop->B_x, 88-BD_bop->B_y);
                else blitAlphaImageToScreen(92, 164, 96, 52, BD_bop->B_image[8], 192+BD_bop->B_x, 188-BD_bop->B_y);
                break;
           case LEZY_LEWO:
                if(BD_bop->B_frame<15) blitAlphaImageToScreen(160, 0, 92, 152, BD_bop->B_image[9], 194+BD_bop->B_x, 88-BD_bop->B_y);
                else blitAlphaImageToScreen(288, 164, 96, 52, BD_bop->B_image[9], 192+BD_bop->B_x, 188-BD_bop->B_y);
                break;
           case SUPERFLY_PRAWO:
                if(BD_bop->B_frame>22)
                {
                     blitAlphaImageToScreen(352, 0, 96, 148, BD_bop->B_image[10], 192+BD_bop->B_x, 72-BD_bop->B_y);
                     BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                     BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 216-BD_bop->B_y;
                }
                else if(BD_bop->B_frame>8)
                {
                     blitAlphaImageToScreen(96, 128, 144, 140, BD_bop->B_image[10], 192+BD_bop->B_x, 72-BD_bop->B_y);
                     BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                     BD_bop->B_bbox[1][0] = 264+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 188-BD_bop->B_y;
                }
                else
                {
                     blitAlphaImageToScreen(352, 0, 96, 148, BD_bop->B_image[10], 192+BD_bop->B_x, 72-BD_bop->B_y);
                     BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                     BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 216-BD_bop->B_y;
                }
                break;
           case SUPERFLY_LEWO:
                if(BD_bop->B_frame>22)
                {
                     blitAlphaImageToScreen(0, 0, 96, 148, BD_bop->B_image[11], 192+BD_bop->B_x, 72-BD_bop->B_y);
                     BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                     BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 216-BD_bop->B_y;
                }
                else if(BD_bop->B_frame>8)
                {
                     blitAlphaImageToScreen(208, 128, 144, 140, BD_bop->B_image[11], 144+BD_bop->B_x, 72-BD_bop->B_y);
                     BD_bop->B_bbox[0][0] = 148+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                     BD_bop->B_bbox[1][0] = 216+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 188-BD_bop->B_y;
                }
                else
                {
                     blitAlphaImageToScreen(0, 0, 96, 148, BD_bop->B_image[11], 192+BD_bop->B_x, 72-BD_bop->B_y);
                     BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                     BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 216-BD_bop->B_y;
                }
                break;
           case KLATA_PRAWO:
                blitAlphaImageToScreen(0, 0, 84, 168, BD_bop->B_image[2], 198+BD_bop->B_x, 72-BD_bop->B_y);
                BD_bop->B_bbox[0][0] = 202+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                BD_bop->B_bbox[1][0] = 278+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 236-BD_bop->B_y;
                break;
           case KLATA_LEWO:
                blitAlphaImageToScreen(392, 0, 84, 168, BD_bop->B_image[3], 198+BD_bop->B_x, 72-BD_bop->B_y);
                BD_bop->B_bbox[0][0] = 202+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 76-BD_bop->B_y;
                BD_bop->B_bbox[1][0] = 278+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 236-BD_bop->B_y;
                break;
           case LAPY_PRAWO:
                if(BD_bop->B_frame<11)                
                {
                     blitAlphaImageToScreen(0, 0, 92, 216, BD_bop->B_image[8], 188+BD_bop->B_x, 24);
                     BD_bop->B_bbox[0][0] = 232+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 272+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)                
                {
                     blitAlphaImageToScreen(244, 0, 136, 168, BD_bop->B_image[2], 184+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 192+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 264+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case LAPY_LEWO:
                if(BD_bop->B_frame<11)                
                {
                     blitAlphaImageToScreen(384, 0, 92, 216, BD_bop->B_image[9], 200+BD_bop->B_x, 24);
                     BD_bop->B_bbox[0][0] = 208+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 248+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)                
                {
                     blitAlphaImageToScreen(96, 0, 136, 168, BD_bop->B_image[3], 160+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 216+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 288+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case FISTS_PRAWO:
                if(BD_bop->B_frame<11)                
                {
                     blitAlphaImageToScreen(92, 0, 132, 164, BD_bop->B_image[8], 200+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 216+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 276+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)                
                {
                     blitAlphaImageToScreen(0, 0, 144, 164, BD_bop->B_image[6], 200+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 236+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 288+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case FISTS_LEWO:
                if(BD_bop->B_frame<11)                
                {
                     blitAlphaImageToScreen(252, 0, 132, 164, BD_bop->B_image[9], 148+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 204+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 264+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)                
                {
                     blitAlphaImageToScreen(284, 0, 144, 164, BD_bop->B_image[7], 136+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 192+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 244+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case ZIEMIA_PRAWO:
                if(BD_bop->B_frame<11)              
                {
                     blitAlphaImageToScreen(144, 0, 144, 164, BD_bop->B_image[6], 200+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 232+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 292+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)              
                {
                     blitAlphaImageToScreen(96, 0, 116, 156, BD_bop->B_image[4], 140+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 144+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<31)              
                {
                     blitAlphaImageToScreen(316, 0, 80, 212, BD_bop->B_image[8], 200+BD_bop->B_x, 28);
                     BD_bop->B_bbox[0][0] = 212+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 256+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<41)              
                {
                     blitAlphaImageToScreen(380, 0, 96, 152, BD_bop->B_image[2], 192+BD_bop->B_x, 88);
                     BD_bop->B_bbox[0][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 92;
                     BD_bop->B_bbox[1][0] = 268+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 224;
                }
                break;
           case ZIEMIA_LEWO:
                if(BD_bop->B_frame<11)                
                {
                     blitAlphaImageToScreen(140, 0, 144, 164, BD_bop->B_image[7], 136+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 188+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 248+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)                
                {
                     blitAlphaImageToScreen(232, 0, 116, 156, BD_bop->B_image[5], 224+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 336+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<31)              
                {
                     blitAlphaImageToScreen(80, 0, 80, 212, BD_bop->B_image[9], 200+BD_bop->B_x, 28);
                     BD_bop->B_bbox[0][0] = 224+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 268+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<41)              
                {
                     blitAlphaImageToScreen(0, 0, 96, 152, BD_bop->B_image[3], 192+BD_bop->B_x, 88);
                     BD_bop->B_bbox[0][0] = 212+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 92;
                     BD_bop->B_bbox[1][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 224;
                }
                break;
           case SNIF_PRAWO:
                if(BD_bop->B_frame >20) blitAlphaImageToScreen(144, 0, 144, 164, BD_bop->B_image[6], 200+BD_bop->B_x, 76);
                else if(BD_bop->B_frame >10) blitAlphaImageToScreen(288, 0, 140, 164, BD_bop->B_image[6], 200+BD_bop->B_x, 76);
                else blitAlphaImageToScreen(144, 0, 144, 164, BD_bop->B_image[6], 200+BD_bop->B_x, 76);
                BD_bop->B_bbox[0][0] = 232+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 80;
                BD_bop->B_bbox[1][0] = 292+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 240;
                break;
           case SNIF_LEWO:
                if(BD_bop->B_frame >20) blitAlphaImageToScreen(140, 0, 144, 164, BD_bop->B_image[7], 136+BD_bop->B_x, 76);
                else if(BD_bop->B_frame >10) blitAlphaImageToScreen(0, 0, 140, 164, BD_bop->B_image[7], 140+BD_bop->B_x, 76);
                else blitAlphaImageToScreen(140, 0, 144, 164, BD_bop->B_image[7], 136+BD_bop->B_x, 76);
                BD_bop->B_bbox[0][0] = 188+BD_bop->B_x;
                BD_bop->B_bbox[0][1] = 80;
                BD_bop->B_bbox[1][0] = 248+BD_bop->B_x;
                BD_bop->B_bbox[1][1] = 240;
                break;
           case KARUZELA_PRAWO:
                if(BD_bop->B_frame >40)
                {
                     blitAlphaImageToScreen(168, 0, 76, 168, BD_bop->B_image[2], 202+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 222+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 72;
                     BD_bop->B_bbox[1][0] = 258+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame >30)
                {
                     blitAlphaImageToScreen(232, 0, 116, 156, BD_bop->B_image[5], 224+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 336+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame >20)
                {
                     //blitAlphaImageToScreen(168, 0, 76, 168, BD_bop->B_image[2], 202+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 222+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 72;
                     BD_bop->B_bbox[1][0] = 258+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame >10)
                {
                     blitAlphaImageToScreen(96, 0, 116, 156, BD_bop->B_image[4], 140+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 144+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else
                {
                     blitAlphaImageToScreen(144, 0, 144, 164, BD_bop->B_image[6], 200+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 232+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 292+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case KARUZELA_LEWO:
                if(BD_bop->B_frame >140)
                {
                     //blitAlphaImageToScreen(232, 0, 76, 168, BD_bop->B_image[3], 202+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 222+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 72;
                     BD_bop->B_bbox[1][0] = 258+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame >130)
                {
                     blitAlphaImageToScreen(96, 0, 116, 156, BD_bop->B_image[4], 140+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 144+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame >120)
                {
                     blitAlphaImageToScreen(232, 0, 76, 168, BD_bop->B_image[3], 202+BD_bop->B_x, 72);
                     BD_bop->B_bbox[0][0] = 222+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 72;
                     BD_bop->B_bbox[1][0] = 258+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame >110)
                {
                     blitAlphaImageToScreen(232, 0, 116, 156, BD_bop->B_image[5], 224+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 336+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else
                {
                     blitAlphaImageToScreen(140, 0, 144, 164, BD_bop->B_image[7], 136+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 188+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 248+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case CHMURKA_PRAWO:
                if(BD_bop->B_frame<11)              
                {
                     blitAlphaImageToScreen(144, 0, 144, 164, BD_bop->B_image[6], 200+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 232+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 292+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)              
                {
                     blitAlphaImageToScreen(96, 0, 116, 156, BD_bop->B_image[4], 140+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 144+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 196+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<31)              
                {
                     blitAlphaImageToScreen(316, 0, 80, 212, BD_bop->B_image[8], 200+BD_bop->B_x, 28);
                     BD_bop->B_bbox[0][0] = 212+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 256+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<41)              
                {
                     blitAlphaImageToScreen(396, 0, 80, 212, BD_bop->B_image[8], 200+BD_bop->B_x, 28);
                     BD_bop->B_bbox[0][0] = 212+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 256+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<51)              
                {
                     blitAlphaImageToScreen(316, 0, 80, 212, BD_bop->B_image[8], 200+BD_bop->B_x, 28);
                     BD_bop->B_bbox[0][0] = 212+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 256+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<71)              
                {
                     blitAlphaImageToScreen(144, 0, 144, 164, BD_bop->B_image[6], 200+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 232+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 292+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
           case CHMURKA_LEWO:
                if(BD_bop->B_frame<11)                
                {
                     blitAlphaImageToScreen(140, 0, 144, 164, BD_bop->B_image[7], 136+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 188+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 248+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<21)                
                {
                     blitAlphaImageToScreen(232, 0, 116, 156, BD_bop->B_image[5], 224+BD_bop->B_x, 84);
                     BD_bop->B_bbox[0][0] = 284+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 88;
                     BD_bop->B_bbox[1][0] = 336+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<31)              
                {
                     blitAlphaImageToScreen(80, 0, 80, 212, BD_bop->B_image[9], 200+BD_bop->B_x, 28);
                     BD_bop->B_bbox[0][0] = 224+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 268+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<41)              
                {
                     blitAlphaImageToScreen(0, 0, 80, 212, BD_bop->B_image[9], 200+BD_bop->B_x, 28);
                     BD_bop->B_bbox[0][0] = 224+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 268+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<51)              
                {
                     blitAlphaImageToScreen(80, 0, 80, 212, BD_bop->B_image[9], 200+BD_bop->B_x, 28);
                     BD_bop->B_bbox[0][0] = 224+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 76;
                     BD_bop->B_bbox[1][0] = 268+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                else if(BD_bop->B_frame<71)                
                {
                     blitAlphaImageToScreen(140, 0, 144, 164, BD_bop->B_image[7], 136+BD_bop->B_x, 76);
                     BD_bop->B_bbox[0][0] = 188+BD_bop->B_x;
                     BD_bop->B_bbox[0][1] = 80;
                     BD_bop->B_bbox[1][0] = 248+BD_bop->B_x;
                     BD_bop->B_bbox[1][1] = 240;
                }
                break;
     }
}
void Bop_HUD_Draw(Bop* BHD_bop, Image* BHD_hud, int BHD_n)
{
     blitAlphaImageToScreen(0, 12, 34, 24, BHD_hud, 0, 1);
     blitAlphaImageToScreen(77, 12, 15, 12, BHD_hud, 40, 0);
     blitImageToScreen(77, 24, 15, 12, BHD_hud, 40, 13);
     for(BHD_n=0;BHD_n<BHD_bop->B_energy;BHD_n+=1)
     blitImageToScreen(119, 17, 10, 7, BHD_hud, BHD_n*8+58, 3);
     for(BHD_n=0;BHD_n<BHD_bop->B_live;BHD_n+=1)
     blitImageToScreen(119, 12, 10, 5, BHD_hud, BHD_n*8+58, 17);
}
extern void Bop_Chmurka_Draw(Bop* BCD_bop, int BCD_x, int BCD_y, int BCD_frame)
{
     switch(BCD_frame)
     {
          case 1:
               blitAlphaImageToScreen(0, 168, 132, 80, BCD_bop->B_image[2], BCD_x, BCD_y);
               break;
          case 2:
               blitAlphaImageToScreen(132, 168, 116, 76, BCD_bop->B_image[2], BCD_x+8, BCD_y+4);
               break;
          case 3:
               blitAlphaImageToScreen(240, 148, 128, 80, BCD_bop->B_image[10], BCD_x+2, BCD_y);
               break;
          case 4:
               blitAlphaImageToScreen(248, 168, 132, 76, BCD_bop->B_image[2], BCD_x, BCD_y+4);
               break;
     }
}
extern void Bop_Chmurka_Draw_Left(Bop* BCDL_bop, int BCDL_x, int BCDL_y, int BCDL_frame)
{
     switch(BCDL_frame)
     {
          case 1:
               blitAlphaImageToScreen(344, 168, 132, 80, BCDL_bop->B_image[3], BCDL_x, BCDL_y);
               break;
          case 2:
               blitAlphaImageToScreen(228, 168, 116, 76, BCDL_bop->B_image[3], BCDL_x+8, BCDL_y+4);
               break;
          case 3:
               blitAlphaImageToScreen(80, 148, 128, 80, BCDL_bop->B_image[11], BCDL_x+2, BCDL_y);
               break;
          case 4:
               blitAlphaImageToScreen(96, 168, 132, 76, BCDL_bop->B_image[3], BCDL_x, BCDL_y+4);
               break;
     }
}
void Bop_Energy_Fill(Bop* BEF_bop, int BEF_count)
{
     if(BEF_count<10-BEF_bop->B_energy)BEF_bop->B_energy += BEF_count;
     else if(BEF_count>10) {BEF_bop->B_energy = 10; BEF_bop->B_anim = 0; BEF_bop->B_frame = 0; BEF_bop->B_x=0; BEF_bop->B_y=0;}
     else BEF_bop->B_energy = 10;
}
int Bop_XY_Get(Bop* BXYG_bop, int BXYG_xy)
{
     if(BXYG_xy=='x' || BXYG_xy=='X') return BXYG_bop->B_x;
     else if(BXYG_xy=='y' || BXYG_xy=='Y') return BXYG_bop->B_y;
     else return -1;
}
int Bop_FA_Get(Bop* BFAG_bop, int BFAG_fa)
{
     if(BFAG_fa=='f' || BFAG_fa=='F') return BFAG_bop->B_frame;
     else if(BFAG_fa=='a' || BFAG_fa=='A') return BFAG_bop->B_anim;
     else return -1;
}
int Bop_LE_Get(Bop* BLEG_bop, int BLEG_le)
{
     if(BLEG_le=='l' || BLEG_le=='L') return BLEG_bop->B_live;
     else if(BLEG_le=='e' || BLEG_le=='E') return BLEG_bop->B_energy;
     else return -1; 
}
extern int Bop_BB_Get(Bop* BBBG_bop, int BBBG_XY, int BBBG_01)
{
     if(BBBG_XY == 'x' || BBBG_XY == 'X')return BBBG_bop->B_bbox[BBBG_01][0];
     else if(BBBG_XY == 'y' || BBBG_XY == 'Y')return BBBG_bop->B_bbox[BBBG_01][1];
     else return -1; 
}
extern int Bop_MiddleX_Get(Bop* BMXG_bop)
{
     return (BMXG_bop->B_bbox[0][0]+BMXG_bop->B_bbox[1][0])/2;
}
int Bop_HB_Get(Bop* BHBG_bop)
{
     return BHBG_bop->B_hbox;
}
int Bop_Anim_Select(int BAS_key)
{
     switch(K_get_keys()[BAS_key-100])
                           {
                                  case 1:
                                       return KEY_SUPERFLY;
                                       break;
                                  case 2:
                                       return KEY_OBRKOP;
                                       break;
                                  case 3:
                                       return KEY_PODCIECIE;
                                       break; 
                                  case 4:
                                       return KEY_KOLANO;
                                       break; 
                                  case 5:
                                       return KEY_KLATA;
                                       break; 
                                  case 6:
                                       return KEY_FISTS;
                                       break; 
                                  case 7:
                                       return KEY_LAPY;
                                       break;  
                                  case 8:
                                       return KEY_DYNKA;
                                       break; 
                                  case 9:
                                       return KEY_CHMURKA;
                                       break; 
                                  case 10:
                                       return KEY_SNIF;
                                       break; 
                                  case 11:
                                       return KEY_ZIEMIA;
                                       break; 
                                  case 12:
                                       return KEY_KARUZELA;
                                       break; 
                                  default:
                                          return 155;
                                          break;
                           }
}
int Bop_Anim_Revers_Select(int BARS_key)
{
     switch(BARS_key)
     {
             case LEFT_SQUARE:
             case LEFT_TRIANGLE:
             case LEFT_CIRCLE:
                           switch(K_get_keys()[BARS_key-102])
                           {
                                  case 1:
                                       return KEY_SUPERFLY;
                                       break;
                                  case 2:
                                       return KEY_OBRKOP;
                                       break;
                                  case 3:
                                       return KEY_PODCIECIE;
                                       break; 
                                  case 4:
                                       return KEY_KOLANO;
                                       break; 
                                  case 5:
                                       return KEY_KLATA;
                                       break; 
                                  case 6:
                                       return KEY_FISTS;
                                       break; 
                                  case 7:
                                       return KEY_LAPY;
                                       break;  
                                  case 8:
                                       return KEY_DYNKA;
                                       break; 
                                  case 9:
                                       return KEY_CHMURKA;
                                       break; 
                                  case 10:
                                       return KEY_SNIF;
                                       break; 
                                  case 11:
                                       return KEY_ZIEMIA;
                                       break; 
                                  case 12:
                                       return KEY_KARUZELA;
                                       break; 
                                  default:
                                          return 155;
                                          break;
                           }
                           break;
             case RIGHT_SQUARE:
             case RIGHT_TRIANGLE:
             case RIGHT_CIRCLE:
                           switch(K_get_keys()[BARS_key-98])
                           {
                                  case 1:
                                       return KEY_SUPERFLY;
                                       break;
                                  case 2:
                                       return KEY_OBRKOP;
                                       break;
                                  case 3:
                                       return KEY_PODCIECIE;
                                       break; 
                                  case 4:
                                       return KEY_KOLANO;
                                       break; 
                                  case 5:
                                       return KEY_KLATA;
                                       break; 
                                  case 6:
                                       return KEY_FISTS;
                                       break; 
                                  case 7:
                                       return KEY_LAPY;
                                       break;  
                                  case 8:
                                       return KEY_DYNKA;
                                       break; 
                                  case 9:
                                       return KEY_CHMURKA;
                                       break; 
                                  case 10:
                                       return KEY_SNIF;
                                       break; 
                                  case 11:
                                       return KEY_ZIEMIA;
                                       break; 
                                  case 12:
                                       return KEY_KARUZELA;
                                       break; 
                                  default:
                                          return 155;
                                          break;
                           }
                           break;
             default:
                    switch(K_get_keys()[BARS_key-100])
                           {
                                  case 1:
                                       return KEY_SUPERFLY;
                                       break;
                                  case 2:
                                       return KEY_OBRKOP;
                                       break;
                                  case 3:
                                       return KEY_PODCIECIE;
                                       break; 
                                  case 4:
                                       return KEY_KOLANO;
                                       break; 
                                  case 5:
                                       return KEY_KLATA;
                                       break; 
                                  case 6:
                                       return KEY_FISTS;
                                       break; 
                                  case 7:
                                       return KEY_LAPY;
                                       break;  
                                  case 8:
                                       return KEY_DYNKA;
                                       break; 
                                  case 9:
                                       return KEY_CHMURKA;
                                       break; 
                                  case 10:
                                       return KEY_SNIF;
                                       break; 
                                  case 11:
                                       return KEY_ZIEMIA;
                                       break; 
                                  case 12:
                                       return KEY_KARUZELA;
                                       break; 
                                  default:
                                          return 155;
                                          break;
                           }
                           break; 
             
     }
}
