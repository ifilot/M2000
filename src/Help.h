/*** M2000: Portable P2000 emulator *****************************************/
/***                                                                      ***/
/***                                Help.h                                ***/
/***                                                                      ***/
/*** This file contains the messages printed when the -help command line  ***/
/*** option is used                                                       ***/
/***                                                                      ***/
/*** Copyright (C) Marcel de Kogel 1996,1997                              ***/
/***     You are not allowed to distribute this software commercially     ***/
/***     Please, notify me, if you make any changes to this file          ***/
/****************************************************************************/

char *HelpText[] =
{
  "Usage: m2000 [-option1 [-option2...]] [filename]",
  "[filename] = name of the file to load as a cartridge [BASIC.bin]",
  "[-option]  =",
#ifdef DEBUG
  "  -trap [-tr] <address>      - Trap execution when PC reaches address [-1]",
#endif
  "  -help                      - Print this help page",
  "  -verbose <flags>           - Select debugging messages [1]",
  "                               0 - Silent     1 - Startup messages",
  "                               4 - Tape",
  "  -romfile <file>            - Select P2000 ROM dump file [P2000ROM.bin]",
  "  -cpuspeed <speed>          - Set Z80 CPU speed [100%]",
  "  -ifreq <frequency>         - Set interrupt frequency [50Hz]",
  "  -sync <value>              - Sync/Do not sync emulation [1]",
  "                               0 - Dot no sync   1 - Sync",
#ifndef ALLEGRO
  "  -uperiod <value>           - Set number of interrupts per screen update [1]",
#endif
  "  -t / -m                    - Select P2000 model [-t]",
#ifdef ALLEGRO
  "  -keymap <mode>             - Select keyboard mapping [1]",
  "                                0 - Positional mapping",
  "                                1 - Symbolic mapping",
#endif
#if defined(MSDOS) || defined(ALLEGRO)
  "  -video <mode>              - Select video mode (T-model emulation only) [0]",
#ifdef ALLEGRO
  "                               0 - 960x720",
  "                               1 - 960x720 [CRT scanlines]",
#else
  "                               0 - 256x240   1 - 640x480",
#endif
#else // Linux/X
  "  -video <mode>              - Select window size [0]",
  "                               0 - 500x300   1 - 520x490",
#endif
  "  -ram <size>                - Select amount of RAM installed [32KB]",
  "  -printer <filename>        - Select file for printer output "
#if defined(MSDOS) || defined(WIN32)
                                 "[PRN]",
#else
                                 "[stdout]",
#endif
  "  -printertype <value>       - Select printer type [0]",
  "                               0 - Daisy wheel   1 - Matrix",
  "",
  "  -tape <filename>           - Select tape image to use [P2000.cas]",
  "  -boot <value>              - Allow/Don't allow BASIC to boot from tape [0]",
  "                               0 - Don't allow booting",
  "                               1 - Allow booting",
  "  -font <filename>           - Select font to use [Default.fnt]",
  "  -sound <mode>              - Select sound mode [255]",
  "                               0 - No sound",
#ifdef MSDOS
  "                               1 - PC Speaker",
  "                               2 - SoundBlaster",
#else
#ifdef UNIX_X
  "                               1 - /dev/dsp",
#endif
#endif
  "                               255 - Detect",
  "  -volume <value>            - Select initial volume [10]",
  "                               0 - Silent    15 - Maximum",
#ifdef JOYSTICK
  "  -joystick <mode>           - Select joystick mode [1]",
  "                               0 - No joystick support  1 - Joystick support",
  "  -joymap <mode>             - Select joystick mapping [0]",
  "                               0 - Moving the joystick emulates the cursorkeys",
  "                                   The main button emulates the spacebar",
  "                               1 - Fraxxon mode: Moving left/right does left/up",
  "                                   The main button emulates the spacebar",
#endif
#ifdef MITSHM
  "  -shm <mode>                - Use/Don't use MITSHM extensions for X [1]",
  "                               0 - Don't use SHM   1 - Use SHM",
#endif
#ifdef UNIX_X
  "  -savecpu <mode>            - Save/Don't save CPU when inactive [1]",
  "                               0 - Don't save CPU   1 - Save CPU",
#endif
  NULL
};
