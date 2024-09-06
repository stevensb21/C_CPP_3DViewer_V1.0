#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qgifimage.h>

#include <QColor>
#include <QColorDialog>
#include <QDialog>>
#include <QFileDialog>
#include <QMainWindow>
#include <QRandomGenerator>
#include <QSettings>
#include <QTextEdit>
#include <QtCore>
#include <QtGui>
#include <QtMath>
#include <QtOpenGL/QtOpenGL>

#include "glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

extern "C" {
#include "../core/s21_3dviewer.h"
#include "../core/transformations.h"
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 public:
  void saveSettings();
  void loadSettings();

 private slots:
  //    void bind_slots();

  void on_pushButton_clicked();

  void on_SliderScale_valueChanged(int value);

  void on_SliderMoveX_valueChanged(int value);

  void on_SliderMoveY_valueChanged(int value);

  void on_SliderMoveZ_valueChanged(int value);

  void on_SliderRotateX_valueChanged(int value);

  void on_SliderRotateY_valueChanged(int value);

  void on_SliderRotateZ_valueChanged(int value);

  void on_backColorButton_clicked();

  void on_colorVerticesButton_clicked();

  void on_sizeVSlider_valueChanged(int value);

  void on_sizePSlider_valueChanged(int value);

  void on_colorPointsButton_clicked();

  void on_comboBoxProjection_currentIndexChanged(int index);

  void on_pushButton_3_clicked();

  void on_pointNone_clicked();

  void on_pointQuad_clicked();

  void on_pointCircle_clicked();

  void on_solidLine_clicked();

  void on_dashedLine_clicked();

  void on_gifButton_clicked();

  void makeGif();

  void startTimer();

  // QSettings *settings

  void on_pushButton_2_clicked();

 private:
  Ui::MainWindow *ui;

  QString gifName;
  QGifImage *gifKa;
  int frameCounter = 0;
  QTimer *timer;
  QFile *saveFile;
  QSettings *settings;
};
#endif  // MAINWINDOW_H
