#include <png.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <time.h>
#include <stdio.h>

#include "preloader.h"
#include "graphics.h"

Image* Pr_background;
Image* Pr_load;

void Preload(int Pr_loaded, int Pr_max)
{
     Pr_max = 10*Pr_loaded/Pr_max;
     blitImageToScreen(0, 0, 480, 272, Pr_background, 0, 0);
     for(Pr_loaded=0;Pr_loaded<Pr_max;Pr_loaded++)
     {
          blitImageToScreen(0, 0, 20, 14, Pr_load, 158+(Pr_loaded*16), 139);
     }
     flipScreen();
}
void Preload_Init(void)
{
     Pr_background=loadImage("loading.png");
     Pr_load=loadImage("healthbar.png");
}
void Preload_End(void)
{
     freeImage(Pr_background);
     freeImage(Pr_load);
}
