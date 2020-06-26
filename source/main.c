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

#include "callback.h"
#include "menu.h"
#include "moveSelect.h"
#include "sound.h"
#include "graphics.h"
#include "mp3player.h"
#include "bop.h"
#include "stage.h"

PSP_MODULE_INFO("Bop N Rumble", 0, 1, 1);

int main()
      {
          scePowerSetClockFrequency(333, 333, 166);
          pspDebugScreenInit();
          SetupCallbacks();
          initGraphics();
          pspAudioInit();
          //mainThemeStart();
          Start_Screen();
          while(1)
          {
                  sceDisplayWaitVblankStart();
                  Menu_Screen();
                  Stage_Main();
          }
          //mainThemeStop();
          sceKernelSleepThread(); 
          return 0;
      }
