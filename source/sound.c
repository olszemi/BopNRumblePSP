#include <pspaudio.h>
#include <pspaudiolib.h>

#include "sound.h"
#include "mp3player.h"

void mainThemeStart(void)
    {
          MP3_Init(1);
          MP3_Load("BNR_Main_Theme.mp3");
          MP3_Play(1);
    }
void mainThemeStop(void)    
    {
          MP3_Stop(1);
          MP3_FreeTune(1);
    }
    
    
    
    
    
