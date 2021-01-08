#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPainter>
#include<QCamera>
#include<QCameraViewfinder>
#include<QHBoxLayout>
#include<QPainter>
#include<QPen>
#include<QCameraImageCapture>
#include<QPixmap>
#include<QString>
#include<QDir>
#include<QMessageBox>
#include<QDebug>


namespace Ui { class Widget; }


class Widget : public QWidget
{
    Q_OBJECT

public:
    QCamera *camera;
    QCameraImageCapture *imagecapture;
    QCameraViewfinder *viewfinder;

    int i=0;
    QString *name = new QString("请输入姓名");
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //void paintEvent(QPaintEvent *event) override;
    void saveimage();
private:
    Ui::Widget *ui;
    void closeEvent(QCloseEvent *event) override;
};
#endif // WIDGET_H
