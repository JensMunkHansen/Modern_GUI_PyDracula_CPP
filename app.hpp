#pragma once

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>

class Ui_MainWindow;

class UIFunctions;
class AppFunctions;

class QPropertyAnimation;
class QParallelAnimationGroup;

class QGraphicsDropShadowEffect;
class QSizeGrip;

class CustomGrip;

class Toggle;

class App : public QMainWindow {
  Q_OBJECT
 public:
  App(int argc, char *argv[]);
  ~App() override;

  //  void moveWindow(QMouseEvent* event);

  void mousePressEvent(QMouseEvent* event) override;

  void keyPressEvent(QKeyEvent* event) override;

  void resizeEvent(QResizeEvent *event) override;



 private Q_SLOTS:
  void buttonClick();
  void openCloseLeftBox();
  void openCloseRightBox();

 private:
  void resizeFunction();

  bool eventFilter(QObject* obj, QEvent* event) override;

  void SetupUI();


 public:
  // Designer form
  Ui_MainWindow *ui;
 private:
  std::string title;
  std::string description;
  bool useCustomTheme;
  std::string themeFile;
  
  int GLOBAL_STATE = 0;
  bool GLOBAL_TITLE_BAR = true;
  QPoint dragPos;

  friend class UIFunctions;
  friend class AppFunctions;

  // UIFunctions members
  QPropertyAnimation* animation;
  QGraphicsDropShadowEffect* shadow;
  QSizeGrip* sizegrip;

  QPropertyAnimation *left_box;
  QPropertyAnimation *right_box;
  QParallelAnimationGroup *group;
  
  CustomGrip*  left_grip;
  CustomGrip*  right_grip;
  CustomGrip*  top_grip;
  CustomGrip*  bottom_grip;
  Toggle* toggleWidget;
};
