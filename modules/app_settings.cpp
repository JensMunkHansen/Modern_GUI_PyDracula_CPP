#include <modules/app_settings.hpp>

bool Settings::ENABLE_CUSTOM_TITLE_BAR = true;
int Settings::MENU_WIDTH = 240;

int  Settings::LEFT_BOX_WIDTH = 240;
int  Settings::RIGHT_BOX_WIDTH = 240;
int  Settings::TIME_ANIMATION = 500;
  
char Settings::BTN_LEFT_BOX_COLOR[] = "background-color: rgb(44, 49, 58);";
char Settings::BTN_RIGHT_BOX_COLOR[] = "background-color: #ff79c6;";

char Settings::MENU_SELECTED_STYLESHEET[] = ""
  "border-left: 22px solid qlineargradient(spread:pad, x1:0.034, y1:0, x2:0.216, y2:0, stop:0.499 rgba(255, 121, 198, 255), stop:0.5 rgba(85, 170, 255, 0));"
  "background-color: rgb(40, 44, 52);"
  "";
