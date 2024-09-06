#include "glwidget.h"

GLwidget::GLwidget(QWidget *parent) : QOpenGLWidget{parent} {}

GLwidget::~GLwidget() { clear_data(&vertex); };

void GLwidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  // glClearColor(0, 0, 0, 0);
}

void GLwidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glVertexPointer(3, GL_DOUBLE, 0, vertex.vertices);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  drawOBJ();
}

void GLwidget::parcing() {
  const char *filePtr = filePath.toLatin1().data();
  clear_data(&this->vertex);
  vertex = {0, 0, NULL, NULL};

  if (filePath != "-") {
    parse_file(filePtr, &vertex);
    set_normalize_coef();
    update();
    flagColor = 1;
  }
}

void GLwidget::drawOBJ() {
  if (filePath != "-") {
    if (typeProj == 1) {
      glFrustum(-1 * normalize_coef, 1 * normalize_coef, -1 * normalize_coef,
                1 * normalize_coef, normalize_coef, 1000 * normalize_coef);
      glTranslatef(0, 0, -2 * normalize_coef);
      glRotatef(30, 1, 0, 0);
    } else {
      glOrtho(-1 * normalize_coef, 1 * normalize_coef, -1 * normalize_coef,
              1 * normalize_coef, -1 * normalize_coef, 1000 * normalize_coef);
      glTranslatef(0, -normalize_coef / 2, 0);
    }

    glEnableClientState(GL_VERTEX_ARRAY);

    if (this->pView != 0) {
      drawPoints();
    }
    drawLines();

    glDisableClientState(GL_VERTEX_ARRAY);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(bgClrR, bgClrG, bgClrB, 0);
    update();
  }
}

void GLwidget::drawLines() {
  // glClearColor(bgClrR, bgClrG, bgClrB, 0);
  if (this->lView == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00FF);
  }
  glLineWidth(this->lSize);
  glColor3f(this->lClrR, this->lClrG, this->lClrB);
  glDrawElements(GL_LINES, vertex.count_index * 2, GL_UNSIGNED_INT,
                 vertex.indexes);
  if (this->lView == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void GLwidget::drawPoints() {
  if (this->pView == 2) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(this->pSize);
  glColor3f(this->pClrR, this->pClrG, this->pClrB);
  glDrawElements(GL_POINTS, vertex.count_index * 2, GL_UNSIGNED_INT,
                 vertex.indexes);
  if (this->pView == 2) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void GLwidget::set_normalize_coef() {
  normalize_coef = -10;  // scarecrow

  for (size_t i = 0; i < vertex.count_vertices * 3; i++) {
    if (abs(vertex.vertices[i]) > normalize_coef) {
      normalize_coef = abs(vertex.vertices[i]);
    }
  }
}

void GLwidget::mousePressEvent(QMouseEvent *mo) {
  // mPos = mo->pos();
  mPos = mo->globalPosition().toPoint();
}

void GLwidget::mouseMoveEvent(QMouseEvent *mo) {
  /*xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();*/
  // mPos = mo->globalPosition().toPoint();
  new_pos = QPoint(mo->globalPosition().toPoint() - mPos);
  if (mo->buttons() && Qt::LeftButton) {
    x_move(&this->vertex, new_pos.x() * this->normalize_coef / 5000);
    y_move(&this->vertex, -new_pos.y() * this->normalize_coef / 5000);
    update();
  } else if (mo->buttons() && Qt::RightButton) {
    x_rotation(&this->vertex, -new_pos.y() * 0.05);
    y_rotation(&this->vertex, new_pos.x() * 0.05);
    update();
  }
}

void GLwidget::wheelEvent(QWheelEvent *event) {
  QPoint numDegrees = event->angleDelta() / 120;
  double step = normalize_coef / 10;
  double scale_tmp = scale;
  if ((int)(scale + numDegrees.y() * step) > 0) {
    scale += numDegrees.y() * step;
    scale_t(&vertex, scale / scale_tmp);
    update();
  }
}

void GLwidget::closeObj() {
  clear_data(&vertex);
  vertex = {0, 0, NULL, NULL};
  set_normalize_coef();
  update();
}
