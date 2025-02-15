#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro_native_dialog.h>

#define FILE_EXIT_ID 1
#define FILE_INSERT_CASSETTE_ID 2
#define FILE_INSERTRUN_CASSETTE_ID 3
#define FILE_REMOVE_CASSETTE_ID 4
#define FILE_INSERT_CARTRIDGE_ID 5
#define FILE_REMOVE_CARTRIDGE_ID 6
#define FILE_RESET_ID 7
#define FILE_SAVE_SCREENSHOT_ID 8
#define FILE_LOAD_VIDEORAM_ID 9
#define FILE_SAVE_VIDEORAM_ID 10

#define VIEW_SHOW_SCANLINES_ID 20
#define VIEW_WINDOW_SIZE_960_720 21

#define KEYBOARD_SYMBOLIC_ID 30
#define KEYBOARD_POSITIONAL_ID 31
#define KEYBOARD_ZOEK_ID 32
#define KEYBOARD_START_ID 33
#define KEYBOARD_STOP_ID 34
#define KEYBOARD_CLEARCAS_ID 35

#define OPTIONS_SOUND_ID 40
#define OPTIONS_VOLUME_OFFSET 200
#define OPTIONS_VOLUME_HIGH_ID (10 + OPTIONS_VOLUME_OFFSET)
#define OPTIONS_VOLUME_MEDIUM_ID (4 + OPTIONS_VOLUME_OFFSET)
#define OPTIONS_VOLUME_LOW_ID (1 + OPTIONS_VOLUME_OFFSET)
#define OPTIONS_JOYSTICK_ID 44
#define OPTIONS_JOYSTICK_MAP_0_ID 45
#define OPTIONS_JOYSTICK_MAP_1_ID 46
#define OPTIONS_JOYSTICK_MAP 47

#define SPEED_SYNC 50
#define SPEED_PAUSE 51
#define FPS_50_ID 52
#define FPS_60_ID 53
#define SPEED_OFFSET 1000
#define SPEED_500_ID (500 + SPEED_OFFSET)
#define SPEED_200_ID (200 + SPEED_OFFSET)
#define SPEED_120_ID (120 + SPEED_OFFSET)
#define SPEED_100_ID (100 + SPEED_OFFSET)
#define SPEED_50_ID  (50 + SPEED_OFFSET)
#define SPEED_20_ID  (20 + SPEED_OFFSET)
#define SPEED_10_ID  (10 + SPEED_OFFSET)

#define HELP_ABOUT_ID 100

void UpdateVolumeMenu (ALLEGRO_MENU *menu, int mastervolume) {
  al_set_menu_item_flags(menu, OPTIONS_VOLUME_HIGH_ID, (OPTIONS_VOLUME_HIGH_ID == mastervolume + OPTIONS_VOLUME_OFFSET) ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX);
  al_set_menu_item_flags(menu, OPTIONS_VOLUME_MEDIUM_ID, (OPTIONS_VOLUME_MEDIUM_ID == mastervolume + OPTIONS_VOLUME_OFFSET) ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX);
  al_set_menu_item_flags(menu, OPTIONS_VOLUME_LOW_ID, (OPTIONS_VOLUME_LOW_ID == mastervolume + OPTIONS_VOLUME_OFFSET) ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX);
}

void UpdateCpuSpeedMenu (ALLEGRO_MENU *menu, int cpuSpeed) {
  al_set_menu_item_flags(menu, SPEED_500_ID, (SPEED_500_ID == cpuSpeed + SPEED_OFFSET) ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX);
  al_set_menu_item_flags(menu, SPEED_200_ID, (SPEED_200_ID == cpuSpeed + SPEED_OFFSET) ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX);
  al_set_menu_item_flags(menu, SPEED_120_ID, (SPEED_120_ID == cpuSpeed + SPEED_OFFSET) ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX);
  al_set_menu_item_flags(menu, SPEED_100_ID, (SPEED_100_ID == cpuSpeed + SPEED_OFFSET) ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX);
  al_set_menu_item_flags(menu, SPEED_50_ID, (SPEED_50_ID == cpuSpeed + SPEED_OFFSET) ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX);
  al_set_menu_item_flags(menu, SPEED_20_ID, (SPEED_20_ID == cpuSpeed + SPEED_OFFSET) ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX);
  al_set_menu_item_flags(menu, SPEED_10_ID, (SPEED_10_ID == cpuSpeed + SPEED_OFFSET) ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX);
}

ALLEGRO_MENU * CreateEmulatorMenu(ALLEGRO_DISPLAY *display, 
  int videomode,
  int keyboardmap,
  int soundmode,
  int mastervolume,
  int joymode,
  int joymap,
  int cpuSpeed,
  int Sync,
  int IFreq
) {
  ALLEGRO_MENU_INFO menu_info[] = {
    ALLEGRO_START_OF_MENU("File", 0),
      { "Insert Cassette...", FILE_INSERT_CASSETTE_ID, 0, NULL },
      { "Insert, Load and Run Cassette...", FILE_INSERTRUN_CASSETTE_ID, 0, NULL },
      { "Remove Cassette...", FILE_REMOVE_CASSETTE_ID, 0, NULL },
      ALLEGRO_MENU_SEPARATOR,
      { "Insert Cartridge...", FILE_INSERT_CARTRIDGE_ID, 0, NULL },
      { "Remove Cartridge...", FILE_REMOVE_CARTRIDGE_ID, 0, NULL },
      ALLEGRO_MENU_SEPARATOR,
      { "Reset", FILE_RESET_ID, 0, NULL },
      ALLEGRO_MENU_SEPARATOR,
      { "Save Screenshot...", FILE_SAVE_SCREENSHOT_ID, 0, NULL },
      { "Load Video RAM...", FILE_LOAD_VIDEORAM_ID, 0, NULL },
      { "Save Video RAM...", FILE_SAVE_VIDEORAM_ID, 0, NULL },
      ALLEGRO_MENU_SEPARATOR,
      { "Exit", FILE_EXIT_ID, 0, NULL },
      ALLEGRO_END_OF_MENU,

    ALLEGRO_START_OF_MENU("View", 0),
      { "Show Scanlines", VIEW_SHOW_SCANLINES_ID, videomode ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
      ALLEGRO_MENU_SEPARATOR,
      ALLEGRO_START_OF_MENU("Window Sizes", 0),
        { "960x720", VIEW_WINDOW_SIZE_960_720, 0, NULL },
        ALLEGRO_END_OF_MENU,
      ALLEGRO_END_OF_MENU,

    ALLEGRO_START_OF_MENU("Speed", 0),
      ALLEGRO_START_OF_MENU("CPU Speed", 0),
        { "500%", SPEED_500_ID, ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
        { "200%", SPEED_200_ID, ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
        { "120%", SPEED_120_ID, ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
        { "100%", SPEED_100_ID, ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
        { "50%",  SPEED_50_ID , ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
        { "20%",  SPEED_20_ID , ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
        { "10%",  SPEED_10_ID , ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
        ALLEGRO_END_OF_MENU,
      ALLEGRO_MENU_SEPARATOR,
      { "50 Hz", FPS_50_ID, IFreq == 50 ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
      { "60 Hz", FPS_60_ID, IFreq == 60 ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
      ALLEGRO_MENU_SEPARATOR,
      { "Sync On/Off", SPEED_SYNC, Sync ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
      ALLEGRO_MENU_SEPARATOR,
      { "Pause Emulation", SPEED_PAUSE, ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
      ALLEGRO_END_OF_MENU,

    ALLEGRO_START_OF_MENU("Keyboard", 0),
      {"[ZOEK] - Show Cassette Index in BASIC", KEYBOARD_ZOEK_ID, 0, NULL },
      {"[START] - Start Loaded Program in BASIC", KEYBOARD_START_ID, 0, NULL },
      {"[STOP] - Pause/Halt Program in BASIC", KEYBOARD_STOP_ID, 0, NULL },
      {"[WIS] - Clear Cassette in BASIC", KEYBOARD_CLEARCAS_ID, 0, NULL },
      ALLEGRO_MENU_SEPARATOR,
      {"Symbolic Key Mapping", KEYBOARD_SYMBOLIC_ID, keyboardmap==1 ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
      {"Positional Key Mapping", KEYBOARD_POSITIONAL_ID, keyboardmap==0 ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
      ALLEGRO_END_OF_MENU,

    ALLEGRO_START_OF_MENU("Options", 0),
      {soundmode ? "Sound On/Off" : "Sound Card Not Detected", OPTIONS_SOUND_ID, soundmode ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_DISABLED, NULL },
      ALLEGRO_START_OF_MENU("Sound Volume", 0),
        { "High", OPTIONS_VOLUME_HIGH_ID, ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
        { "Medium", OPTIONS_VOLUME_MEDIUM_ID, ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
        { "Low", OPTIONS_VOLUME_LOW_ID, ALLEGRO_MENU_ITEM_CHECKBOX, NULL },
        ALLEGRO_END_OF_MENU,
      ALLEGRO_MENU_SEPARATOR,
      {joymode ? "Joystick On/Off" : "Joystick Not Detected", OPTIONS_JOYSTICK_ID, joymode ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_DISABLED, NULL },
      ALLEGRO_START_OF_MENU("Joystick Mapping", OPTIONS_JOYSTICK_MAP),
        { "Emulate Cursorkeys + Spacebar", OPTIONS_JOYSTICK_MAP_0_ID, joymode ? (joymap==0 ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX) : ALLEGRO_MENU_ITEM_DISABLED, NULL },
        { "Fraxxon Mode (Left/Up/Spacebar)", OPTIONS_JOYSTICK_MAP_1_ID, joymode ? (joymap==1 ? ALLEGRO_MENU_ITEM_CHECKED : ALLEGRO_MENU_ITEM_CHECKBOX) : ALLEGRO_MENU_ITEM_DISABLED, NULL },
        ALLEGRO_END_OF_MENU,
      ALLEGRO_END_OF_MENU,

    ALLEGRO_START_OF_MENU("Help", 0),
      {"About M2000", HELP_ABOUT_ID, 0, NULL },
      ALLEGRO_END_OF_MENU,
    ALLEGRO_END_OF_MENU
  };

  ALLEGRO_MENU *menu = al_build_menu(menu_info);
  if (!joymode) al_remove_menu_item(menu, OPTIONS_JOYSTICK_MAP);
  UpdateVolumeMenu(menu, mastervolume);
  UpdateCpuSpeedMenu(menu, cpuSpeed);
  al_set_display_menu(display, menu);
  return menu;
}