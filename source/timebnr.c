#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <png.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <time.h>
#include <stdio.h>

#include "timebnr.h"

void Wait_us(int microsec)
      {
            clock_t Wu_timestart;
            clock_t Wu_timenow;
            
            Wu_timestart = sceKernelLibcClock();
            while(1)
            {
                sceDisplayWaitVblankStart();
                Wu_timenow = sceKernelLibcClock();
                if(Wu_timenow - Wu_timestart > microsec)
                break;
            }
      }
