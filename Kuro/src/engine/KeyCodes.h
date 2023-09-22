#pragma once

// From glfw3
#define KURO_KEY_UNKNOWN            -1

/* Printable keys */
#define KURO_KEY_SPACE              32
#define KURO_KEY_APOSTROPHE         39  /* ' */
#define KURO_KEY_COMMA              44  /* , */
#define KURO_KEY_MINUS              45  /* - */
#define KURO_KEY_PERIOD             46  /* . */
#define KURO_KEY_SLASH              47  /* / */
#define KURO_KEY_0                  48
#define KURO_KEY_1                  49
#define KURO_KEY_2                  50
#define KURO_KEY_3                  51
#define KURO_KEY_4                  52
#define KURO_KEY_5                  53
#define KURO_KEY_6                  54
#define KURO_KEY_7                  55
#define KURO_KEY_8                  56
#define KURO_KEY_9                  57
#define KURO_KEY_SEMICOLON          59  /* ; */
#define KURO_KEY_EQUAL              61  /* = */
#define KURO_KEY_A                  65
#define KURO_KEY_B                  66
#define KURO_KEY_C                  67
#define KURO_KEY_D                  68
#define KURO_KEY_E                  69
#define KURO_KEY_F                  70
#define KURO_KEY_G                  71
#define KURO_KEY_H                  72
#define KURO_KEY_I                  73
#define KURO_KEY_J                  74
#define KURO_KEY_K                  75
#define KURO_KEY_L                  76
#define KURO_KEY_M                  77
#define KURO_KEY_N                  78
#define KURO_KEY_O                  79
#define KURO_KEY_P                  80
#define KURO_KEY_Q                  81
#define KURO_KEY_R                  82
#define KURO_KEY_S                  83
#define KURO_KEY_T                  84
#define KURO_KEY_U                  85
#define KURO_KEY_V                  86
#define KURO_KEY_W                  87
#define KURO_KEY_X                  88
#define KURO_KEY_Y                  89
#define KURO_KEY_Z                  90
#define KURO_KEY_LEFT_BRACKET       91  /* [ */
#define KURO_KEY_BACKSLASH          92  /* \ */
#define KURO_KEY_RIGHT_BRACKET      93  /* ] */
#define KURO_KEY_GRAVE_ACCENT       96  /* ` */
#define KURO_KEY_WORLD_1            161 /* non-US #1 */
#define KURO_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KURO_KEY_ESCAPE             256
#define KURO_KEY_ENTER              257
#define KURO_KEY_TAB                258
#define KURO_KEY_BACKSPACE          259
#define KURO_KEY_INSERT             260
#define KURO_KEY_DELETE             261
#define KURO_KEY_RIGHT              262
#define KURO_KEY_LEFT               263
#define KURO_KEY_DOWN               264
#define KURO_KEY_UP                 265
#define KURO_KEY_PAGE_UP            266
#define KURO_KEY_PAGE_DOWN          267
#define KURO_KEY_HOME               268
#define KURO_KEY_END                269
#define KURO_KEY_CAPS_LOCK          280
#define KURO_KEY_SCROLL_LOCK        281
#define KURO_KEY_NUM_LOCK           282
#define KURO_KEY_PRINT_SCREEN       283
#define KURO_KEY_PAUSE              284
#define KURO_KEY_F1                 290
#define KURO_KEY_F2                 291
#define KURO_KEY_F3                 292
#define KURO_KEY_F4                 293
#define KURO_KEY_F5                 294
#define KURO_KEY_F6                 295
#define KURO_KEY_F7                 296
#define KURO_KEY_F8                 297
#define KURO_KEY_F9                 298
#define KURO_KEY_F10                299
#define KURO_KEY_F11                300
#define KURO_KEY_F12                301
#define KURO_KEY_F13                302
#define KURO_KEY_F14                303
#define KURO_KEY_F15                304
#define KURO_KEY_F16                305
#define KURO_KEY_F17                306
#define KURO_KEY_F18                307
#define KURO_KEY_F19                308
#define KURO_KEY_F20                309
#define KURO_KEY_F21                310
#define KURO_KEY_F22                311
#define KURO_KEY_F23                312
#define KURO_KEY_F24                313
#define KURO_KEY_F25                314
#define KURO_KEY_KP_0               320
#define KURO_KEY_KP_1               321
#define KURO_KEY_KP_2               322
#define KURO_KEY_KP_3               323
#define KURO_KEY_KP_4               324
#define KURO_KEY_KP_5               325
#define KURO_KEY_KP_6               326
#define KURO_KEY_KP_7               327
#define KURO_KEY_KP_8               328
#define KURO_KEY_KP_9               329
#define KURO_KEY_KP_DECIMAL         330
#define KURO_KEY_KP_DIVIDE          331
#define KURO_KEY_KP_MULTIPLY        332
#define KURO_KEY_KP_SUBTRACT        333
#define KURO_KEY_KP_ADD             334
#define KURO_KEY_KP_ENTER           335
#define KURO_KEY_KP_EQUAL           336
#define KURO_KEY_LEFT_SHIFT         340
#define KURO_KEY_LEFT_CONTROL       341
#define KURO_KEY_LEFT_ALT           342
#define KURO_KEY_LEFT_SUPER         343
#define KURO_KEY_RIGHT_SHIFT        344
#define KURO_KEY_RIGHT_CONTROL      345
#define KURO_KEY_RIGHT_ALT          346
#define KURO_KEY_RIGHT_SUPER        347
#define KURO_KEY_MENU               348
		
#define KURO_KEY_LAST               KURO_KEY_MENU