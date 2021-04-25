#pragma once

#include <QMetaType>
#include <QString>
#include <QWidget>
#include <QCheckBox>
#include <QPropertyAnimation>

class Toggle : public QCheckBox {
  Q_OBJECT
  Q_PROPERTY(float circlePosition READ circlePosition WRITE setCirclePosition)
public:
  Toggle(QWidget* parent,
	 int width = 60,
        const QString& bg_color = "#777",
        const QString& circle_color = "#DDD",
        const QString& active_color = "#00BCff",
	enum QEasingCurve::Type  animation_curve = QEasingCurve::OutBounce);
  ~Toggle();

  /// Set/Get the circle position
  float circlePosition() const;
  void setCirclePosition(float pos);
protected:
  bool hitButton(const QPoint &pos) const override;
  void paintEvent(QPaintEvent* ev) override;
public Q_SLOTS:

private Q_SLOTS:
  void startTransition(float value);
  
private:
  QPropertyAnimation *animation;
  QString _bg_color;
  QString _circle_color;
  QString _active_color;
  float _circle_position;
};
