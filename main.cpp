#include <QApplication>
#include <QSurfaceFormat>
#include <QtGlobal>

#include <app.hpp>

int main(int argc, char* argv[]) {
  QSurfaceFormat format;
  format.setMajorVersion(3);
  format.setMinorVersion(2);
  format.setDepthBufferSize(1);
  format.setStencilBufferSize(1);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

#ifdef __linux__
  if (qEnvironmentVariableIsSet("WAYLAND_DISPLAY")) {
    qputenv("QT_QPA_PLATFORM", "xcb");
  }
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  // QT Stuff
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
  //qputenv("QT_SCALE_FACTOR", "1.2");

  QApplication app( argc, argv );
  app.setApplicationName("ITK Segmentation");
  app.setOrganizationName("Sexy Soft");
  app.setOrganizationDomain("www.sexysoft.com");
  app.setWindowIcon(QIcon(":/icon.ico"));

  App myApp(argc, argv);
  myApp.show();

  return app.exec();
}
