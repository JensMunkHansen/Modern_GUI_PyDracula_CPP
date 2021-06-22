#include <widgets/custom_grips.hpp>

CustomGrip::CustomGrip(QWidget *parent, enum Qt::Edge position,
                       bool disable_color) : QWidget(parent), wi(nullptr),
  top_left(nullptr), top_right(nullptr), bottom_left(nullptr), bottom_right(nullptr),
  leftgrip(nullptr), rightgrip(nullptr) {

  this->parent = parent;
  this->setParent(parent);
  this->wi = new Widgets();


  if (position == Qt::TopEdge) {
    this->wi->top(this);
    this->setGeometry(0, 0, this->parent->width(), 10);
    this->setMaximumHeight(10);
    this->wi->m_top->installEventFilter(this);

    // GRIPS
    top_left = new QSizeGrip(this->wi->m_top_left);
    top_right = new QSizeGrip(this->wi->m_top_right);

    // ENABLE COLOR
    if (disable_color) {
      this->wi->m_top_left->setStyleSheet("background: transparent");
      this->wi->m_top_right->setStyleSheet("background: transparent");
      this->wi->m_top->setStyleSheet("background: transparent");
    }
  } else if (position == Qt::BottomEdge) {
    this->wi->bottom(this);
    this->setGeometry(0, this->parent->height() - 10, this->parent->width(), 10);
    this->setMaximumHeight(10);
    this->wi->m_bottom->installEventFilter(this);

    // GRIPS
    bottom_left = new QSizeGrip(this->wi->m_bottom_left);
    bottom_right = new QSizeGrip(this->wi->m_bottom_right);

    // ENABLE COLOR
    if (disable_color) {
      this->wi->m_bottom_left->setStyleSheet("background: transparent");
      this->wi->m_bottom_right->setStyleSheet("background: transparent");
      this->wi->m_bottom->setStyleSheet("background: transparent");
    }
  }
  if (position == Qt::LeftEdge) {
    this->wi->left(this);
    this->setGeometry(0, 10, 10, this->parent->height());
    this->setMaximumWidth(10);
    this->wi->m_leftgrip->installEventFilter(this);

    // ENABLE COLOR;
    if (disable_color) {
      this->wi->m_leftgrip->setStyleSheet("background: transparent");
    }
  }
  if (position == Qt::RightEdge) {
    this->wi->right(this);
    this->setGeometry(this->parent->width() - 10, 10, 10, this->parent->height());
    this->setMaximumWidth(10);
    this->wi->m_rightgrip->installEventFilter(this);

    // ENABLE COLOR;
    if (disable_color) {
      this->wi->m_rightgrip->setStyleSheet("background: transparent");
    }
  }
}

bool CustomGrip::eventFilter(QObject* obj, QEvent* event) {
  if (event->type() == QEvent::MouseMove &&
      obj == this->wi->m_top) {
    this->resize_top(static_cast<QMouseEvent*>(event));
  }
  if (event->type() == QEvent::MouseMove &&
      obj == this->wi->m_bottom) {
    this->resize_bottom(static_cast<QMouseEvent*>(event));
  }
  if (event->type() == QEvent::MouseMove &&
      obj == this->wi->m_leftgrip) {
    this->resize_left(static_cast<QMouseEvent*>(event));
  }
  if (event->type() == QEvent::MouseMove &&
      obj == this->wi->m_rightgrip) {
    this->resize_right(static_cast<QMouseEvent*>(event));
  }
  return QWidget::eventFilter(obj, event);
}

void CustomGrip::resize_right(QMouseEvent* event) {
  auto delta = event->pos();
  int width = std::max(this->parent->minimumWidth(), this->parent->width() + delta.x());
  this->parent->resize(width, this->parent->height());
  event->accept();
}

void CustomGrip::resize_left(QMouseEvent* event) {
  auto delta = event->pos();
  int width = std::max(this->parent->minimumWidth(), this->parent->width() - delta.x());
  auto geo = this->parent->geometry();
  geo.setLeft(geo.right() - width);
  this->parent->setGeometry(geo);
  event->accept();
}

void CustomGrip::resize_bottom(QMouseEvent* event) {
  auto delta = event->pos();
  int height = std::max(this->parent->minimumHeight(), this->parent->height() + delta.y());
  this->parent->resize(this->parent->width(), height);
  event->accept();
}

void CustomGrip::resize_top(QMouseEvent* event) {
  auto delta = event->pos();
  int height = std::max(this->parent->minimumHeight(), this->parent->height() - delta.y());
  auto geo = this->parent->geometry();
  geo.setTop(geo.bottom() - height);
  this->parent->setGeometry(geo);
  event->accept();
}


CustomGrip::~CustomGrip() {
  if (this->wi) {
    delete this->wi;
    this->wi = nullptr;
  }
}

void CustomGrip::resizeEvent(QResizeEvent *event) {
  ((void)event);
  if (this->wi->m_container_top) {
    this->wi->m_container_top->setGeometry(0, 0, this->width(), 10);
  } else if (this->wi->m_container_bottom) {
    this->wi->m_container_bottom->setGeometry(0, 0, this->width(), 10);
  } else if (this->wi->m_leftgrip) {
    this->wi->m_leftgrip->setGeometry(0, 0, 10, this->height() - 20);
  } else if (this->wi->m_rightgrip) {
    this->wi->m_rightgrip->setGeometry(0, 0, 10, this->height() - 20);
  }
}

Widgets::Widgets() : m_container_top(nullptr), m_container_bottom(nullptr),
  m_top(nullptr), m_top_left(nullptr), m_top_right(nullptr),
  m_rightgrip(nullptr), m_leftgrip(nullptr),
  m_bottom(nullptr), m_bottom_right(nullptr), m_bottom_left(nullptr) {

}

void Widgets::top(QWidget* Form) {
  if (Form->objectName().isEmpty()) {
    Form->setObjectName("Form");
  }
  this->m_container_top = new QFrame(Form);
  this->m_container_top->setObjectName("container_top");
  this->m_container_top->setGeometry(QRect(0, 0, 500, 10));
  this->m_container_top->setMinimumSize(QSize(0, 10));
  this->m_container_top->setMaximumSize(QSize((2 << 23) - 1, 10));
  this->m_container_top->setFrameShape(QFrame::NoFrame);
  this->m_container_top->setFrameShadow(QFrame::Raised);
  this->m_top_layout = new QHBoxLayout(this->m_container_top);
  this->m_top_layout->setSpacing(0);
  this->m_top_layout->setObjectName("top_layout");
  this->m_top_layout->setContentsMargins(0, 0, 0, 0);
  this->m_top_left = new QFrame(this->m_container_top);
  this->m_top_left->setObjectName("top_left");
  this->m_top_left->setMinimumSize(QSize(10, 10));
  this->m_top_left->setMaximumSize(QSize(10, 10));
  this->m_top_left->setCursor(QCursor(Qt::SizeFDiagCursor));
  this->m_top_left->setStyleSheet("background-color: rgb(33, 37, 43);");
  this->m_top_left->setFrameShape(QFrame::NoFrame);
  this->m_top_left->setFrameShadow(QFrame::Raised);
  this->m_top_layout->addWidget(this->m_top_left);
  this->m_top = new QFrame(this->m_container_top);
  this->m_top->setObjectName("top");
  this->m_top->setCursor(QCursor(Qt::SizeVerCursor));
  this->m_top->setStyleSheet("background-color: rgb(85, 255, 255);");
  this->m_top->setFrameShape(QFrame::NoFrame);
  this->m_top->setFrameShadow(QFrame::Raised);
  this->m_top_layout->addWidget(this->m_top);
  this->m_top_right = new QFrame(this->m_container_top);
  this->m_top_right->setObjectName("top_right");
  this->m_top_right->setMinimumSize(QSize(10, 10));
  this->m_top_right->setMaximumSize(QSize(10, 10));
  this->m_top_right->setCursor(QCursor(Qt::SizeBDiagCursor));
  this->m_top_right->setStyleSheet("background-color: rgb(33, 37, 43);");
  this->m_top_right->setFrameShape(QFrame::NoFrame);
  this->m_top_right->setFrameShadow(QFrame::Raised);
  this->m_top_layout->addWidget(this->m_top_right);
}
;
void Widgets::bottom(QWidget* Form) {
  if (Form->objectName().isEmpty()) {
    Form->setObjectName("Form");
  }
  this->m_container_bottom = new QFrame(Form);
  this->m_container_bottom->setObjectName("container_bottom");
  this->m_container_bottom->setGeometry(QRect(0, 0, 500, 10));
  this->m_container_bottom->setMinimumSize(QSize(0, 10));
  this->m_container_bottom->setMaximumSize(QSize((2 << 23) - 1, 10));
  this->m_container_bottom->setFrameShape(QFrame::NoFrame);
  this->m_container_bottom->setFrameShadow(QFrame::Raised);
  this->m_bottom_layout = new QHBoxLayout(this->m_container_bottom);
  this->m_bottom_layout->setSpacing(0);
  this->m_bottom_layout->setObjectName("bottom_layout");
  this->m_bottom_layout->setContentsMargins(0, 0, 0, 0);
  this->m_bottom_left = new QFrame(this->m_container_bottom);
  this->m_bottom_left->setObjectName("bottom_left");
  this->m_bottom_left->setMinimumSize(QSize(10, 10));
  this->m_bottom_left->setMaximumSize(QSize(10, 10));
  this->m_bottom_left->setCursor(QCursor(Qt::SizeBDiagCursor));
  this->m_bottom_left->setStyleSheet("background-color: rgb(33, 37, 43);");
  this->m_bottom_left->setFrameShape(QFrame::NoFrame);
  this->m_bottom_left->setFrameShadow(QFrame::Raised);
  this->m_bottom_layout->addWidget(this->m_bottom_left);
  this->m_bottom = new QFrame(this->m_container_bottom);
  this->m_bottom->setObjectName("bottom");
  this->m_bottom->setCursor(QCursor(Qt::SizeVerCursor));
  this->m_bottom->setStyleSheet("background-color: rgb(85, 170, 0);");
  this->m_bottom->setFrameShape(QFrame::NoFrame);
  this->m_bottom->setFrameShadow(QFrame::Raised);
  this->m_bottom_layout->addWidget(this->m_bottom);
  this->m_bottom_right = new QFrame(this->m_container_bottom);
  this->m_bottom_right->setObjectName("bottom_right");
  this->m_bottom_right->setMinimumSize(QSize(10, 10));
  this->m_bottom_right->setMaximumSize(QSize(10, 10));
  this->m_bottom_right->setCursor(QCursor(Qt::SizeFDiagCursor));
  this->m_bottom_right->setStyleSheet("background-color: rgb(33, 37, 43);");
  this->m_bottom_right->setFrameShape(QFrame::NoFrame);
  this->m_bottom_right->setFrameShadow(QFrame::Raised);
  this->m_bottom_layout->addWidget(this->m_bottom_right);
}
void Widgets::left(QWidget* Form) {
  if (Form->objectName().isEmpty()) {
    Form->setObjectName("Form");
  }
  this->m_leftgrip = new QFrame(Form);
  this->m_leftgrip->setObjectName("left");
  this->m_leftgrip->setGeometry(QRect(0, 10, 10, 480));
  this->m_leftgrip->setMinimumSize(QSize(10, 0));
  this->m_leftgrip->setCursor(QCursor(Qt::SizeHorCursor));
  this->m_leftgrip->setStyleSheet("background-color: rgb(255, 121, 198);");
  this->m_leftgrip->setFrameShape(QFrame::NoFrame);
  this->m_leftgrip->setFrameShadow(QFrame::Raised);
}
void Widgets::right(QWidget* Form) {
  if (Form->objectName().isEmpty()) {
    Form->setObjectName("Form");
  }
  Form->resize(500, 500);
  this->m_rightgrip = new QFrame(Form);
  this->m_rightgrip->setObjectName("right");
  this->m_rightgrip->setGeometry(QRect(0, 0, 10, 500));
  this->m_rightgrip->setMinimumSize(QSize(10, 0));
  this->m_rightgrip->setCursor(QCursor(Qt::SizeHorCursor));
  this->m_rightgrip->setStyleSheet("background-color: rgb(255, 0, 127);");
  this->m_rightgrip->setFrameShape(QFrame::NoFrame);
  this->m_rightgrip->setFrameShadow(QFrame::Raised);
}
