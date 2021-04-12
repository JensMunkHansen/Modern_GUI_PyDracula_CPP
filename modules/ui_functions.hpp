#pragma once

class QIcon;
class QWidget;
class App;

enum Direction {
  Left,
  Right
};

class UIFunctions final {
public:

  static void maximize_restore(App* self);

  static bool returStatus();
  static void setStatus(App* self, bool status);
  static void enableMaximumSize(App* self, int width, int height);
  static void toggleMenu(App* self, bool enabled);
  static void removeTitleBar(App* self, bool status);
  static void labelTitle(App* self, const QString &text);
  static void labelPage(App* self, const QString& text);
  static void labelDescription(App* self, const QString &text);
  static QString selectMenu(App* self, const QString& getStyle);
  static void addNewMenu(App* self, const QString &name,
			 const QString &objName,
			 const QString &icon,
			 bool isTopMenu);
  static QString deselectMenu(App* self, QString& getStyle);

  static void resetStyle(App* self, const QString& widget);

  static void selectStandardMenu(App* self, const QString& widget);
  static void uiDefinitions(App* self);

  static void dobleClickMaximizeRestore(App* self);
  static bool GLOBAL_STATE;
  static bool GLOBAL_TITLE_BAR;
  static int count;

  static void toggleLeftBox(App* self, bool enable);
  static void toggleRightBox(App* self, bool enable);

  static void eventFilter(App* self, QObject* obj, QEvent* event);

  static void moveWindow(App* self, QMouseEvent* event);

  static void resize_grips(App* self);

  static void start_box_animation(App* self, int widthLeftBox, int widthRightBox, const enum Direction direction);

  static void theme(App* self, const std::string& file, bool useCustomTheme);
  
};

