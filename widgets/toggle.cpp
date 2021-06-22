#include <widgets/toggle.hpp>

#include <QPainter>

Toggle::Toggle(QWidget* parent,
               int width,
               const QString& bg_color,
               const QString& circle_color,
               const QString& active_color,
               enum QEasingCurve::Type  animation_curve) : QCheckBox(parent), animation(nullptr)  {
  // SET DEFAULT PARAMETERS
  this->setFixedSize(width, 28);
  this->setCursor(Qt::PointingHandCursor);

  // COLORS
  this->_bg_color = bg_color;
  this->_circle_color = circle_color;
  this->_active_color = active_color;

  // CREATE ANIMATION
  this->_circle_position = 3;
  this->animation = new QPropertyAnimation(this, "circlePosition", this);
  this->animation->setEasingCurve(animation_curve);
  this->animation->setDuration(500); // Time in milisseconds

  // CONNECT STATE CHANGED
  QObject::connect(this, &QCheckBox::stateChanged,
                   this, &Toggle::startTransition);

}

float Toggle::circlePosition() const {
  return _circle_position;
}
void Toggle::setCirclePosition(float pos) {
  this->_circle_position = pos;
  this->update();
}

bool Toggle::hitButton(const QPoint &pos) const {
  return this->contentsRect().contains(pos);
}

void Toggle::paintEvent(QPaintEvent* ev) {
  ((void)ev);
  // SET PAINTER
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  // SET AS NO PEN
  p.setPen(Qt::NoPen);

  // DRAW RECTANGLE
  QRect rect(0, 0, this->width(), this->height());

  // CHECK IF IS CHECKED
  if (!this->isChecked()) {
    // DRAW BG
    p.setBrush(QColor(this->_bg_color));
    p.drawRoundedRect(0, 0, rect.width(), rect.height(), rect.height() / 2, rect.height() / 2);

    // DRAW CIRCLE
    p.setBrush(QColor(this->_circle_color));
    p.drawEllipse(this->_circle_position, 3, 22, 22);
  } else {
    // DRAW BG
    p.setBrush(QColor(this->_active_color));
    p.drawRoundedRect(0, 0, rect.width(), rect.height(), rect.height() / 2, rect.height() / 2);

    // DRAW CIRCLE
    p.setBrush(QColor(this->_circle_color));
    p.drawEllipse(this->_circle_position, 3, 22, 22);

    // END DRAW
    p.end();
  }
}
void Toggle::startTransition(float value) {
  this->animation->stop(); // Stop animation if running
  if (value) {
    this->animation->setEndValue(this->width() - 26);
  } else {
    this->animation->setEndValue(3);
  }
  // START ANIMATION
  this->animation->start();
}

Toggle::~Toggle() {
  if (animation) {
    delete animation;
    animation = nullptr;
  }
}
