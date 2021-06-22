#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QFont>
#include <QList>
#include <QPushButton>
#include <QSharedPointer>
#include <QGraphicsDropShadowEffect>
#include <QSizeGrip>

#include <string>
#include <regex>
#include <fstream>
#include <streambuf>


#include <ui_functions.hpp>
#include <ui_styles.hpp>

// GUI FILE
#include <app.hpp>
#include <ui_app.h>

#include <modules/app_settings.hpp>
#include <widgets/custom_grips.hpp>

// GLOBALS
bool UIFunctions::GLOBAL_STATE = false;
bool UIFunctions::GLOBAL_TITLE_BAR = true;
int UIFunctions::count = 1;

void UIFunctions::maximize_restore(App* self) {
  int status = UIFunctions::GLOBAL_STATE;
  if (status == 0) {
    self->showMaximized();
    UIFunctions::GLOBAL_STATE = true;
    self->ui->appMargins->setContentsMargins(0, 0, 0, 0);
    self->ui->maximizeRestoreAppBtn->setToolTip("Restore");
    self->ui->maximizeRestoreAppBtn->setIcon(QIcon(":/icons/images/icons/icon_restore.png"));
    self->ui->frame_size_grip->hide();

    self->left_grip->hide();
    self->right_grip->hide();
    self->bottom_grip->hide();
    self->top_grip->hide();
  } else {
    UIFunctions::GLOBAL_STATE = false;
    self->showNormal();
    self->resize(self->width()+1, self->height()+1);
    self->ui->appMargins->setContentsMargins(10, 10, 10, 10);
    self->ui->maximizeRestoreAppBtn->setToolTip("Maximize");
    self->ui->maximizeRestoreAppBtn->setIcon(QIcon(":/icons/images/icons/icon_maximize.png"));
    self->ui->frame_size_grip->show();


    self->left_grip->show();
    self->right_grip->show();
    self->bottom_grip->show();
    self->top_grip->show();
  }
}

void UIFunctions::theme(App* self, const std::string& file, bool useCustomTheme) {
  if (useCustomTheme) {
    std::ifstream t(file.c_str());
    if (t.good()) {
      std::string str;

      t.seekg(0, std::ios::end);
      str.reserve(t.tellg());
      t.seekg(0, std::ios::beg);

      str.assign((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

      self->ui->styleSheet->setStyleSheet(str.c_str());
    }
  }
}

void UIFunctions::toggleMenu(App* self, bool enabled) {
  self->ui->toggleButton->setEnabled(false);
  if (enabled) {
    // GET WIDTH
    int width = self->ui->leftMenuBg->width();
    int maxExtend = Settings::MENU_WIDTH;
    const int standard = 60; // As defined in UI file
    int widthExtended = 0;

    // SET MAX WIDTH
    if (width == standard) {
      widthExtended = maxExtend;
    } else {
      widthExtended = standard;
    }

    // ANIMATION
    if (self->animation) {
      delete self->animation;
      self->animation = nullptr;
    }

    self->animation = new QPropertyAnimation(self->ui->leftMenuBg, "minimumWidth");
    self->animation->setDuration(Settings::TIME_ANIMATION);
    self->animation->setStartValue(width);
    self->animation->setEndValue(widthExtended);
    self->animation->setEasingCurve(QEasingCurve::InOutQuart);
    self->animation->start();
  }
  self->ui->toggleButton->setEnabled(true);
}

bool UIFunctions::returStatus() {
  return UIFunctions::GLOBAL_STATE;
}



void UIFunctions::setStatus(App* self, bool status) {
  ((void)self);
  UIFunctions::GLOBAL_STATE = status;
}

void UIFunctions::enableMaximumSize(App* self, int width, int height) {
  if (width != 0 && height != 0) {
    self->setMaximumSize(QSize(width, height));
    self->ui->frame_size_grip->hide();
  }
}

void UIFunctions::removeTitleBar(App* self, bool status) {
  ((void)self);
  UIFunctions::GLOBAL_TITLE_BAR = (int) status;
}

void UIFunctions::labelTitle(App* self, const QString &text) {
  ((void)self);
  ((void)text);
}

void UIFunctions::labelDescription(App* self, const QString &text) {
  ((void)self);
  ((void)text);
}

void UIFunctions::addNewMenu(App* self, const QString &name,
                             const QString &objName,
                             const QString &icon,
                             bool isTopMenu) {
  ((void)isTopMenu);
  QFont font{};
  font.setFamily("Segoe UI");
  QPushButton* button = new QPushButton(QString::number(count), self);
  button->setObjectName(objName);
  QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
  sizePolicy3.setHorizontalStretch(0);
  sizePolicy3.setVerticalStretch(0);
  sizePolicy3.setHeightForWidth(button->sizePolicy().hasHeightForWidth());
  button->setSizePolicy(sizePolicy3);
  button->setMinimumSize(QSize(0, 70));
  button->setLayoutDirection(Qt::LeftToRight);
  button->setFont(font);

  std::string styleSheet = std::regex_replace(Style::style_bt_standard, std::regex("ICON_REPLACE"), icon.toStdString());

  button->setStyleSheet(QString(styleSheet.c_str()));
  button->setText(name);
  button->setToolTip(name);
  // Do we need to store this as a member?
  //  QObject::connect(button, &QPushButton::clicked, self, &App::Button);

}
QString UIFunctions::selectMenu(App* self, const QString& getStyle) {
  ((void)self);
  QString select = getStyle + Settings::MENU_SELECTED_STYLESHEET.c_str();
  return select;
}

QString UIFunctions::deselectMenu(App* self, const QString &getStyle) {
  ((void)self);
  QString styleSheet = getStyle;
  QString deselect = styleSheet.replace(Settings::MENU_SELECTED_STYLESHEET.c_str(), "");
  return deselect;
}

void UIFunctions::selectStandardMenu(App* self, const QString& widget) {
  for (auto& w : self->ui->topMenu->findChildren<QPushButton*>(QString())) {
    if (w->objectName() != widget) {
      w->setStyleSheet(UIFunctions::selectMenu(self, w->styleSheet()));
    }
  }
}

void UIFunctions::resetStyle(App* self, const QString& widget) {

  for (auto& w : self->ui->topMenu->findChildren<QPushButton*>(QString())) {
    if (w->objectName() != widget) {
      w->setStyleSheet(UIFunctions::deselectMenu(self, w->styleSheet()));
    }
  }
}

void UIFunctions::labelPage(App* self, const QString& text) {
  ((void)self);
  ((void)text);
}

void UIFunctions::dobleClickMaximizeRestore(App* self) {
  if (UIFunctions::GLOBAL_TITLE_BAR) {
    QTimer::singleShot(250, [self]() {
      UIFunctions::maximize_restore(self);
    });
  }
}

void UIFunctions::eventFilter(App* self, QObject* obj, QEvent* event) {
  if (event->type() == QEvent::MouseMove &&
      obj == self->ui->titleRightInfo) {
    if (Settings::ENABLE_CUSTOM_TITLE_BAR) {
      UIFunctions::moveWindow(self, static_cast<QMouseEvent*>(event));
    }
  }
  if (event->type() == QEvent::MouseButtonDblClick &&
      obj == self->ui->titleRightInfo) {
    if (Settings::ENABLE_CUSTOM_TITLE_BAR) {
      UIFunctions::dobleClickMaximizeRestore(self);
    }
  }
}
void UIFunctions::resize_grips(App* self) {
  if (Settings::ENABLE_CUSTOM_TITLE_BAR) {
    self->left_grip->setGeometry(0, 10, 10, self->height());
    self->right_grip->setGeometry(self->width() - 10, 10, 10, self->height());
    self->top_grip->setGeometry(0, 0, self->width(), 10);
    self->bottom_grip->setGeometry(0, self->height() - 10, self->width(), 10);
  }
}
void UIFunctions::moveWindow(App* self, QMouseEvent* event) {
  // IF MAXIMIZED CHANGE TO NORMAL
  if (UIFunctions::returStatus() == 1) {
    UIFunctions::maximize_restore(self);
  }

  // MOVE WINDOW
  if (event->buttons() == Qt::LeftButton) {
    self->move(self->pos() + event->globalPos() - self->dragPos);
    self->dragPos = event->globalPos();
    event->accept();
  }
}

void UIFunctions::uiDefinitions(App* self) {
  if (Settings::ENABLE_CUSTOM_TITLE_BAR) {
    // STANDARD TITLE BAR
    self->setWindowFlags(Qt::FramelessWindowHint);
    self->setAttribute(Qt::WA_TranslucentBackground);
  }

  self->ui->titleRightInfo->installEventFilter(self);

  if (Settings::ENABLE_CUSTOM_TITLE_BAR) {
    // Handled in eventFilter

    // CUSTOM GRIPS
    self->left_grip = new CustomGrip(self, Qt::LeftEdge, true);
    self->right_grip = new CustomGrip(self, Qt::RightEdge, true);
    self->bottom_grip = new CustomGrip(self, Qt::BottomEdge, true);
    self->top_grip = new CustomGrip(self, Qt::TopEdge, true);

  } else {
    self->ui->appMargins->setContentsMargins(0, 0, 0, 0);
    self->ui->minimizeAppBtn->hide();
    self->ui->maximizeRestoreAppBtn->hide();
    self->ui->closeAppBtn->hide();

    self->ui->frame_size_grip->hide();
  }

  // DROP SHADOW
  self->shadow = new QGraphicsDropShadowEffect(self);
  self->shadow->setBlurRadius(17);
  self->shadow->setXOffset(0);
  self->shadow->setYOffset(0);
  self->shadow->setColor(QColor(0, 0, 0, 150));
  self->ui->bgApp->setGraphicsEffect(self->shadow);

  // RESIZE WINDOW
  self->sizegrip = new QSizeGrip(self->ui->frame_size_grip);
  self->sizegrip->setStyleSheet("width: 20px; height: 20px; margin 0px; padding: 0px;");

  // MINIMIZE
  QObject::connect(self->ui->minimizeAppBtn, &QPushButton::clicked,
                   self, &App::showMinimized);

  // MAXIMIZE/RESTORE
  QObject::connect(self->ui->maximizeRestoreAppBtn, &QPushButton::clicked,
  self, [self]() {
    UIFunctions::maximize_restore(self);
  });

  // CLOSE APPLICATION
  QObject::connect(self->ui->closeAppBtn, &QPushButton::clicked,
  self, []() {
    qApp->exit();
  });

}


void UIFunctions::toggleLeftBox(App* self, bool enable) {
  // TODO: Color not enabled when selected!!!
  if (enable) {
    // GET WIDTH
    int width = self->ui->extraLeftBox->width();
    int widthRightBox = self->ui->extraRightBox->width();
    //int maxExtend = Settings::LEFT_BOX_WIDTH;
    std::string color = Settings::BTN_LEFT_BOX_COLOR;
    //    int standard = 0;

    // GET BTN STYLE;
    std::string style = self->ui->toggleLeftBox->styleSheet().toStdString().c_str();

    // SET MAX WIDTH;
    if (width == 0) {
      // SELECT BTN;
      self->ui->toggleLeftBox->setStyleSheet(QString((style + color).c_str()));
      if (widthRightBox != 0) {
        style = self->ui->settingsTopBtn->styleSheet().toStdString().c_str();
        std::string styleSheet = std::regex_replace(style, std::regex(Settings::BTN_RIGHT_BOX_COLOR), "");
        self->ui->settingsTopBtn->setStyleSheet(QString(styleSheet.c_str()));
        self->ui->extraRightBox->setMinimumWidth(0);
      }
    } else {

      // RESET BTN;
      std::string styleSheet = std::regex_replace(style, std::regex(Settings::BTN_LEFT_BOX_COLOR), "");
      self->ui->toggleLeftBox->setStyleSheet(QString(styleSheet.c_str()));
    }
    UIFunctions::start_box_animation(self, width, widthRightBox, Direction::Left);
  }
}

void UIFunctions::toggleRightBox(App* self, bool enable) {
  if (enable) {
    // GET WIDTH;
    int width = self->ui->extraRightBox->width();
    int widthLeftBox = self->ui->extraLeftBox->width();
    std::string color = Settings::BTN_RIGHT_BOX_COLOR;

    // GET BTN STYLE;
    std::string style = self->ui->settingsTopBtn->styleSheet().toStdString().c_str();

    // SET MAX WIDTH;
    if (width == 0) {
      // SELECT BTN;
      self->ui->settingsTopBtn->setStyleSheet(QString((style + color).c_str()));

      if (widthLeftBox != 0) {
        style = self->ui->toggleLeftBox->styleSheet().toStdString().c_str();
        std::string styleSheet = std::regex_replace(style, std::regex(Settings::BTN_LEFT_BOX_COLOR), "");
        self->ui->toggleLeftBox->setStyleSheet(QString(styleSheet.c_str()));
        self->ui->extraLeftBox->setMinimumWidth(0);
      }
    } else {
      // RESET BTN;
      std::string styleSheet = std::regex_replace(style, std::regex(Settings::BTN_RIGHT_BOX_COLOR), "");
      self->ui->settingsTopBtn->setStyleSheet(QString(styleSheet.c_str()));
    }
    UIFunctions::start_box_animation(self, widthLeftBox, width, Direction::Right);
  }
}

void UIFunctions::start_box_animation(App* self, int left_box_width, int right_box_width, const enum Direction direction) {
  int right_width = 0;
  int left_width = 0;

  // Check values
  if (left_box_width == 0 && direction == Direction::Left) {
    left_width = Settings::LEFT_BOX_WIDTH;
  } else {
    left_width = 0;
  }
  // Check values
  if (right_box_width == 0 && direction == Direction::Right) {
    right_width = Settings::RIGHT_BOX_WIDTH;
  } else {
    right_width = 0;
  }

  if (self->left_box) {
    delete self->left_box;
  }
  if (self->right_box) {
    delete self->right_box;
  }
  if (self->group) {
    delete self->group;
  }

  // ANIMATION LEFT BOX
  self->left_box = new QPropertyAnimation(self->ui->extraLeftBox, "minimumWidth");
  self->left_box->setDuration(Settings::TIME_ANIMATION);
  self->left_box->setStartValue(left_box_width);
  self->left_box->setEndValue(left_width);
  self->left_box->setEasingCurve(QEasingCurve::InOutQuart);

  // ANIMATION RIGHT BOX
  self->right_box = new QPropertyAnimation(self->ui->extraRightBox, "minimumWidth");
  self->right_box->setDuration(Settings::TIME_ANIMATION);
  self->right_box->setStartValue(right_box_width);
  self->right_box->setEndValue(right_width);
  self->right_box->setEasingCurve(QEasingCurve::InOutQuart);

  // GROUP ANIMATION
  self->group = new QParallelAnimationGroup();
  self->group->addAnimation(self->left_box);
  self->group->addAnimation(self->right_box);
  self->group->start();
}

