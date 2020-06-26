#ifndef CALLBACK_H
#define CALLBACK_H

extern int exit_callback(int arg1, int arg2, void *common);
extern int CallbackThread(SceSize args, void *argp);
extern int SetupCallbacks(void);

#endif
