#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QFileDialog>
#include<QToolBar>
#include<QVector>
#include<opencv2/opencv.hpp>
#include<opencv2/face.hpp>
#include<opencv2/imgproc/types_c.h>
#include<opencv2/imgproc.hpp>
#include"widget.h"
#include<iostream>
#include<opencv2/highgui.hpp>

using namespace std;
using namespace cv;
using namespace face;
namespace Ui {
class mainwindow;
}

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    //QVector<QAction *> action;
    explicit mainwindow(QMainWindow *parent = nullptr);
    ~mainwindow();
    CascadeClassifier cascade;
    Ptr<FaceRecognizer> model ;
    QStringList file;
    QToolBar *toolBar = new QToolBar;
    QImage Mat2QImage(Mat cvImg);
    Mat qimage2mat(const QImage& qimage);
    Mat Cascade(Mat image);
    void ImportImage();
    //QVector<Mat> image;
private:
    Ui::mainwindow *ui;
};

#endif // MAINWINDOW_H
