#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setFixedSize(1294, 740);
  ui->setupUi(this);
  settings = new QSettings("ViewSet", "viewer3d", this);
  loadSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::saveSettings() {
  settings->setValue("conf", 1);
  settings->setValue("ProgectType", ui->widget->typeProj);
  settings->setValue("lClrR", ui->widget->lClrR);
  settings->setValue("lClrG", ui->widget->lClrG);
  settings->setValue("lClrB", ui->widget->lClrB);
  settings->setValue("LineSize", ui->widget->lSize);
  settings->setValue("LineType", ui->widget->lView);
  settings->setValue("pClrR", ui->widget->pClrR);
  settings->setValue("pClrG", ui->widget->pClrG);
  settings->setValue("pClrB", ui->widget->pClrB);
  settings->setValue("PointSize", ui->widget->pSize);
  settings->setValue("PointType", ui->widget->pView);
  settings->setValue("bgClrR", ui->widget->bgClrR);
  settings->setValue("bgClrG", ui->widget->bgClrG);
  settings->setValue("bgClrB", ui->widget->bgClrB);
}

void MainWindow::loadSettings() {
  if (settings->value("conf").toInt() == 1) {
    ui->widget->typeProj = settings->value("ProgectType").toInt();

    ui->widget->lClrR = settings->value("lClrR").toDouble();
    ui->widget->lClrG = settings->value("lClrG").toDouble();
    ui->widget->lClrB = settings->value("lClrB").toDouble();
    ui->widget->lSize = settings->value("LineSize").toInt();
    ui->widget->lView = settings->value("LineType").toInt();

    ui->widget->pClrR = settings->value("pClrR").toDouble();
    ui->widget->pClrG = settings->value("pClrG").toDouble();
    ui->widget->pClrB = settings->value("pClrB").toDouble();
    ui->widget->pSize = settings->value("PointSize").toInt();
    ui->widget->pView = settings->value("PointType").toInt();

    ui->widget->bgClrR = settings->value("bgClrR").toDouble();
    ui->widget->bgClrG = settings->value("bgClrG").toDouble();
    ui->widget->bgClrB = settings->value("bgClrB").toDouble();

    ui->comboBoxProjection->setCurrentIndex(ui->widget->typeProj);

    ui->SliderScale->setValue(0);

    ui->sizePSlider->setValue(ui->widget->pSize);
    ui->sizeVSlider->setValue(ui->widget->lSize);
  }
}

void MainWindow::on_pushButton_clicked() {
  ui->widget->filePath = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "", tr("OBJ Files (*.obj)"));
  ui->textEdit->setText(ui->widget->filePath);

  ui->widget->parcing();

  ui->textEdit->append("\nCount vertices:");
  ui->textEdit->append(QString::number(ui->widget->vertex.count_vertices));
  ui->textEdit->append("\nCount indexes:");
  ui->textEdit->append(QString::number(ui->widget->vertex.count_index));

  ui->widget->update();
}

void MainWindow::on_SliderScale_valueChanged(int value) {
  double scaleValue = value / ui->widget->scale;
  scale_t(&ui->widget->vertex, scaleValue);
  ui->widget->scale = value;
  ui->widget->update();
}

void MainWindow::on_SliderMoveX_valueChanged(int value) {
  double moveXValue =
      (value - ui->widget->moveing_x) * ui->widget->normalize_coef / 100;
  x_move(&ui->widget->vertex, moveXValue);
  ui->widget->moveing_x = value;
  ui->widget->update();
}

void MainWindow::on_SliderMoveY_valueChanged(int value) {
  double moveYValue =
      (value - ui->widget->moveing_y) * ui->widget->normalize_coef / 100;
  y_move(&ui->widget->vertex, moveYValue);
  ui->widget->moveing_y = value;
  ui->widget->update();
}

void MainWindow::on_SliderMoveZ_valueChanged(int value) {
  double moveZValue =
      (value - ui->widget->moveing_z) * ui->widget->normalize_coef / 100;
  z_move(&ui->widget->vertex, moveZValue);
  ui->widget->moveing_z = value;
  ui->widget->update();
}

void MainWindow::on_SliderRotateX_valueChanged(int value) {
  double rotateXValue = value - ui->widget->rotateing_x;
  x_rotation(&ui->widget->vertex, rotateXValue);
  ui->widget->rotateing_x = value;
  ui->widget->update();
}

void MainWindow::on_SliderRotateY_valueChanged(int value) {
  double rotateYValue = value - ui->widget->rotateing_y;
  y_rotation(&ui->widget->vertex, rotateYValue);
  ui->widget->rotateing_y = value;
  ui->widget->update();
}

void MainWindow::on_SliderRotateZ_valueChanged(int value) {
  double rotateZValue = value - ui->widget->rotateing_z;
  z_rotation(&ui->widget->vertex, rotateZValue);
  ui->widget->rotateing_z = value;
  ui->widget->update();
}

void MainWindow::on_backColorButton_clicked() {
  QColor choosedBGColor =
      QColorDialog::getColor(Qt::white, this->ui->tabWidget, "Xyu");
  if (choosedBGColor.isValid()) {
    ui->widget->bgClrR = choosedBGColor.redF();
    ui->widget->bgClrG = choosedBGColor.greenF();
    ui->widget->bgClrB = choosedBGColor.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", choosedBGColor.red(),
            choosedBGColor.green(), choosedBGColor.blue());
    ui->backColorButton->setStyleSheet(rgba_color);
    ui->widget->update();
  }
}

void MainWindow::on_colorVerticesButton_clicked() {
  QColor choosedVColor =
      QColorDialog::getColor(Qt::white, this->ui->tabWidget, "Xyu");
  if (choosedVColor.isValid()) {
    ui->widget->lClrR = choosedVColor.redF();
    ui->widget->lClrG = choosedVColor.greenF();
    ui->widget->lClrB = choosedVColor.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", choosedVColor.red(),
            choosedVColor.green(), choosedVColor.blue());
    ui->backColorButton->setStyleSheet(rgba_color);
    ui->widget->update();
  }
}

void MainWindow::on_colorPointsButton_clicked() {
  QColor choosedPColor =
      QColorDialog::getColor(Qt::white, this->ui->tabWidget, "Xyu");
  if (choosedPColor.isValid()) {
    ui->widget->pClrR = choosedPColor.redF();
    ui->widget->pClrG = choosedPColor.greenF();
    ui->widget->pClrB = choosedPColor.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", choosedPColor.red(),
            choosedPColor.green(), choosedPColor.blue());
    ui->backColorButton->setStyleSheet(rgba_color);
    ui->widget->update();
  }
}

void MainWindow::on_sizeVSlider_valueChanged(int value) {
  ui->widget->lSize = value;
  ui->widget->update();
}

void MainWindow::on_sizePSlider_valueChanged(int value) {
  ui->widget->pSize = value;
  ui->widget->update();
}

void MainWindow::on_comboBoxProjection_currentIndexChanged(int index) {
  ui->widget->typeProj = index;
  ui->widget->update();
}

void MainWindow::on_pushButton_3_clicked() {
  QPixmap screenshot = ui->widget->grab();
  QString filePath = QFileDialog::getSaveFileName(this, "Save Screenshot", "",
                                                  "Images (*.png *.jpg)");
  if (!filePath.isEmpty()) {
    screenshot.save(filePath);
  }
}

void MainWindow::on_pointNone_clicked() {
  ui->widget->pView = 0;
  ui->widget->update();
}

void MainWindow::on_pointQuad_clicked() {
  ui->widget->pView = 1;
  ui->widget->update();
}

void MainWindow::on_pointCircle_clicked() {
  ui->widget->pView = 2;
  ui->widget->update();
}

void MainWindow::on_solidLine_clicked() {
  ui->widget->lView = 0;
  ui->widget->update();
}

void MainWindow::on_dashedLine_clicked() {
  ui->widget->lView = 1;
  ui->widget->update();
}

void MainWindow::on_gifButton_clicked() {
  qDebug() << "push GIF";
  QString filter = "*.gif";
  gifName = "/0";
  QString name_pattern = "3dView";
  gifName = QFileDialog::getSaveFileName(this, tr("Save a gif animation"),
                                         name_pattern, tr("gif (*.gif)"));
  saveFile = new QFile(gifName);
  if (!saveFile->open(QIODevice::WriteOnly)) {
    QMessageBox::critical(this, "Warning", "ERROR");
  } else {
    ui->gifButton->setDisabled(true);
    gifKa = new QGifImage;
    gifKa->setDefaultDelay(10);
    startTimer();
  }
}

void MainWindow::startTimer() {
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::makeGif);
  timer->start(100);
  frameCounter = 0;
}

void MainWindow::makeGif() {
  qDebug() << ui->widget->width();
  qDebug() << ui->widget->height();
  QImage image = ui->widget->grabFramebuffer();
  QSize image_size(640, 480);
  QImage scaledImage = image.scaled(image_size);
  gifKa->addFrame(scaledImage);
  if (frameCounter == 50) {
    timer->stop();
    gifKa->save(gifName);
    frameCounter = 0;
    QMessageBox messageBoxGif;
    messageBoxGif.information(0, "", "Gif animation saved successfully");
    delete gifKa;
    ui->gifButton->setEnabled(true);
  }
  frameCounter++;
}

void MainWindow::on_pushButton_2_clicked() {
  ui->widget->typeProj = settings->value("ProgectType").toInt();

  ui->widget->lClrR = 1.0;
  ui->widget->lClrG = 1.0;
  ui->widget->lClrB = 1.0;
  ui->widget->lView = 0;

  ui->widget->pClrR = 1.0;
  ui->widget->pClrG = 1.0;
  ui->widget->pClrB = 1.0;
  ui->widget->pSize = 1;
  ui->widget->pView = 0;

  ui->widget->bgClrR = 0.0;
  ui->widget->bgClrG = 0.0;
  ui->widget->bgClrB = 0.0;

  ui->comboBoxProjection->setCurrentIndex(0);

  ui->SliderScale->setValue(0);

  ui->SliderMoveX->setValue(0);
  ui->SliderMoveY->setValue(0);
  ui->SliderMoveZ->setValue(0);

  ui->SliderRotateX->setValue(0);
  ui->SliderRotateY->setValue(0);
  ui->SliderRotateZ->setValue(0);

  ui->sizePSlider->setValue(0);
  ui->sizeVSlider->setValue(0);

  ui->backColorButton->setStyleSheet("background-color: rgb(0,0,0)");
  ui->colorPointsButton->setStyleSheet("background-color: rgb(1.0,1.0,1.0)");
  ui->colorVerticesButton->setStyleSheet("background-color: rgb(1.0,1.0,1.0)");

  update();
}
