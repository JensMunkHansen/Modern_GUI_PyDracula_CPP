#pragma once
#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QSizeGrip>
#include <QMouseEvent>

class Widgets;

class CustomGrip : public QWidget {
  Q_OBJECT
public:
  CustomGrip(QWidget *parent = nullptr, enum Qt::Edge position = Qt::TopEdge,
	     bool disable_color = false);
  ~CustomGrip();

  void resizeEvent(QResizeEvent *event) override;

  void resize_top(QMouseEvent* event);
  void resize_bottom(QMouseEvent* event);
  void resize_left(QMouseEvent* event);
  void resize_right(QMouseEvent* event);

  bool eventFilter(QObject* obj, QEvent* event);
  
private:
  QWidget* parent;
  Widgets* wi;
  QSizeGrip *top_left, *top_right;
  QSizeGrip *bottom_left, *bottom_right;
  QSizeGrip *leftgrip, *rightgrip;
};

class Widgets {
 public:
  Widgets();
  void top(QWidget* Form);
  void bottom(QWidget* Form);
  void left(QWidget* Form);
  void right(QWidget* Form);
 public:
  QFrame *m_container_top, *m_container_bottom;
  QFrame* m_top;
  QFrame *m_top_left, *m_top_right;
  QFrame *m_rightgrip, *m_leftgrip;
  QFrame* m_bottom;
  QFrame *m_bottom_right, *m_bottom_left;
  QHBoxLayout* m_top_layout, *m_bottom_layout;
};

