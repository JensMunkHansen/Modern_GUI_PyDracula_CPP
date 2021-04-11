#pragma once

class Settings final {
public:
  // APP SETTINGS
  ///////////////////////////////////////////////////////////////
  static bool ENABLE_CUSTOM_TITLE_BAR;
  static int MENU_WIDTH;

  static int  LEFT_BOX_WIDTH;
  static int  RIGHT_BOX_WIDTH;
  static int  TIME_ANIMATION;

  // BTNS LEFT AND RIGHT BOX COLORS
  static char  BTN_LEFT_BOX_COLOR[];
  static char  BTN_RIGHT_BOX_COLOR[];

  // MENU SELECTED STYLESHEET
  static char MENU_SELECTED_STYLESHEET[];
};
