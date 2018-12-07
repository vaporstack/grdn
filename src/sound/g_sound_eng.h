//
//  g_sound_eng.h
//  grdn-ios
//
//  Created by vs on 11/5/17.
//  Copyright © 2017 ruminant. All rights reserved.
//

#ifndef g_sound_eng_h
#define g_sound_eng_h

#include <stdio.h>

int g_sound_eng_init(void);
int g_sound_eng_deinit(void);
int g_sound_eng_play(const char* snd);

#endif /* g_sound_eng_h */
