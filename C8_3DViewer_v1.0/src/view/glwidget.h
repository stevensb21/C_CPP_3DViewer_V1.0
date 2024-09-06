#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <gl.h>
#include <glu.h>

#include <QMessageBox>
#include <QOpenGLWindow>
#include <QWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGLWidgets/QOpenGLWidget>
//#include <GLUT/glut.h>

extern "C" {
#include "../core/s21_3dviewer.h"
#include "../core/transformations.h"
}

class GLwidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 private:
  int flagColor = 0;
  float xRot, yRot, zRot;
  QPoint mPos, new_pos;
  QTimer tmr;
  void drawOBJ();
  void drawLines();
  void drawPoints();
  void set_normalize_coef();
  void closeObj();
  void wheelEvent(QWheelEvent *event) override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void initializeGL() override;
  void paintGL() override;

 public:
  int lSize = 1;
  int lView = 0;
  int pSize = 1;
  int pView = 0;
  int typeProj;
  double bgClrR = 1.0, bgClrG = 1.0, bgClrB = 1.0;
  double lClrR = 1.0, lClrG = 1.0, lClrB = 1.0;
  double pClrR = 1.0, pClrG = 1.0, pClrB = 1.0;

  explicit GLwidget(QWidget *parent = Q_NULLPTR);
  ~GLwidget() override;
  struct data vertex = {0, 0, NULL, NULL};
  QString filePath = "-";
  double scale = 1.0;
  double rotateing_x, rotateing_y, rotateing_z;
  double moveing_x, moveing_y, moveing_z;
  double normalize_coef;
  void parcing();
};

#endif  // GLWIDGET_H
