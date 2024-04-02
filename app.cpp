#include <QIcon>
#include <QPushButton>
#include <Qt>
#include <QMouseEvent>
#include <QEvent>

#include <app.hpp>
#include <ui_app.h>
#include <ui_functions.hpp>

#include <modules/app_settings.hpp>
#include <modules/app_functions.hpp>

#include <widgets/toggle.hpp>
App::~App() {}

App::App(int argc, char* argv[]) : animation(nullptr),
  shadow(nullptr),
  sizegrip(nullptr) {
  ((void) argc);
  ((void) argv);
  left_box = right_box = nullptr;
  group = nullptr;
  this->SetupUI();
}

void App::buttonClick() {
  // GET BT CLICKED
  QPushButton* btn = dynamic_cast<QPushButton*>(this->sender());
  const QString& btnName = btn->objectName();

  Ui_MainWindow* widgets = this->ui;

  // SHOW HOME PAGE
  if (btnName == "btn_home") {
    widgets->stackedWidget->setCurrentWidget(widgets->home);
    UIFunctions::resetStyle(this, btnName);
    btn->setStyleSheet(UIFunctions::selectMenu(this, btn->styleSheet()));
  }

  // SHOW WIDGETS PAGE
  if (btnName == "btn_widgets") {
    widgets->stackedWidget->setCurrentWidget(widgets->widgets);
    UIFunctions::resetStyle(this, btnName);
    btn->setStyleSheet(UIFunctions::selectMenu(this, btn->styleSheet()));
  }
  // SHOW NEW PAGE
  if (btnName == "btn_new") {
    widgets->stackedWidget->setCurrentWidget(widgets->new_page); // SET PAGE
    UIFunctions::resetStyle(this, btnName); // RESET ANOTHERS BUTTONS SELECTED
    btn->setStyleSheet(UIFunctions::selectMenu(this, btn->styleSheet())); // SELECT MENU
  }
  if (btnName == "btn_exit") {
    
  }
  // PRINT BTN NAME
  printf("Button %s pressed!\n", btnName.toStdString().c_str());
}

void App::SetupUI() {
  this->ui = new Ui_MainWindow;
  this->ui->setupUi(this);

  Ui_MainWindow* widgets = this->ui;

  // USE CUSTOM TITLE BAR | USE AS "False" FOR MAC OR LINUX
  ///////////////////////////////////////////////////////////////
  Settings::ENABLE_CUSTOM_TITLE_BAR = true;

#if 0 //def __linux__
  Settings::ENABLE_CUSTOM_TITLE_BAR = false;
#endif

  // APP NAME
  // ///////////////////////////////////////////////////////////////
  title = "PyDracula - Modern GUI";
  description = "PyDracula APP - Theme with colors based on Dracula for Python.";
  // APPLY TEXTS
  this->setWindowTitle(title.c_str());
  widgets->titleRightInfo->setText(description.c_str());

  // TOGGLE MENU
  // ///////////////////////////////////////////////////////////////
  connect(this->ui->toggleButton, &QPushButton::clicked,
  [this]() {
    UIFunctions::toggleMenu(this, true);
  });

  // SET UI DEFINITIONS
  // ///////////////////////////////////////////////////////////////
  UIFunctions::uiDefinitions(this);

  // QTableWidget PARAMETERS
  // ///////////////////////////////////////////////////////////////
  widgets->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  // BUTTONS CLICK
  // ///////////////////////////////////////////////////////////////

  // LEFT MENUS
  connect(widgets->btn_home, &QPushButton::clicked,
          this, &App::buttonClick);
  connect(widgets->btn_widgets, &QPushButton::clicked,
          this, &App::buttonClick);
  connect(widgets->btn_new, &QPushButton::clicked,
          this, &App::buttonClick);
  connect(widgets->btn_save, &QPushButton::clicked,
          this, &App::buttonClick);

  connect(widgets->toggleLeftBox, &QPushButton::clicked,
          this, &App::openCloseLeftBox);

  connect(widgets->extraCloseColumnBtn, &QPushButton::clicked,
          this, &App::openCloseLeftBox);

  connect(widgets->settingsTopBtn, &QPushButton::clicked,
          this, &App::openCloseRightBox);


  QObject::connect(widgets->btn_exit, &QPushButton::clicked,
  this, []() {
    qApp->exit();
  });

  
  QString bg("#777");
  QString circle("#DDD");
  //  QString active("#00BCFF");
  QString active("#FF79C6");
  this->toggleWidget = new Toggle(this,
                                  60,
                                  bg,
                                  circle,
                                  active);

  //  active = 255, 121, 198

  widgets->verticalLayout_20->addWidget(this->toggleWidget);

  // SHOW APP
  // ///////////////////////////////////////////////////////////////
  this->show();


  // SET CUSTOM THEME
  // ///////////////////////////////////////////////////////////////
  useCustomTheme = false;
  themeFile = "themes/py_dracula_dark.qss";

  // SET THEME AND HACKS
  if (useCustomTheme) {
    // LOAD AND APPLY STYLE
    std::string themeFileWithPath = QCoreApplication::applicationDirPath().toStdString();
    themeFileWithPath += "/";
    themeFileWithPath += themeFile;
    UIFunctions::theme(this,
                       themeFileWithPath,
                       true);
    // SET HACKS
    AppFunctions::setThemeHack(this);
  }

  // SET HOME PAGE AND SELECT MENU
  // ///////////////////////////////////////////////////////////////;
  widgets->stackedWidget->setCurrentWidget(widgets->home);
  widgets->btn_home->setStyleSheet(UIFunctions::selectMenu(this, widgets->btn_home->styleSheet()));
}


void App::openCloseLeftBox() {
  UIFunctions::toggleLeftBox(this, true);
}

void App::openCloseRightBox() {
  UIFunctions::toggleRightBox(this, true);
}

void App::resizeEvent(QResizeEvent *event) {
  ((void)event);
  this->resizeFunction();
  UIFunctions::resize_grips(this);
  QMainWindow::resizeEvent(event);
}

void App::resizeFunction() {
  //printf("Height: %d Width: %d\n", this->height(), this->width());
}


void App::keyPressEvent(QKeyEvent* event) {
  printf("Key: %s | Text Press %s\n", std::to_string(event->key()).c_str(), event->text().toStdString().c_str());
}


void App::mousePressEvent(QMouseEvent* event) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  this->dragPos = event->globalPos();
#else
  this->dragPos = event->globalPosition().toPoint();
#endif
  if (event->buttons() == Qt::LeftButton) {
    printf("Mouse click: LEFT CLICK\n");
  }
  if (event->buttons() == Qt::RightButton) {
    printf("Mouse click: RIGHT CLICK\n");
  }
  if (event->buttons() == Qt::MiddleButton) {
    printf("Mouse click: MIDDLE BUTTON\n");
  }
}

bool App::eventFilter(QObject* obj, QEvent* event) {
  UIFunctions::eventFilter(this, obj, event);
  return QMainWindow::eventFilter(obj, event);
}
