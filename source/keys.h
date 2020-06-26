#ifndef KEYS_H
#define KEYS_H

extern int keyDown(void);
extern int key(void);
extern int keyUp(void);
extern int keyTab(int KT_lastKey);
extern void K_set_keys(int tab[12]);
extern int* K_get_keys(void);
extern void keys_Default(void);
extern void keyTabUp(void);

#endif
