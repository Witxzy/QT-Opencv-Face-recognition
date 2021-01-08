#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label->setFixedSize(200,150);
    ui->label->setScaledContents(true);
    camera = new QCamera();
    imagecapture = new QCameraImageCapture(camera);
    viewfinder = new QCameraViewfinder(ui->cramerWidget);

    imagecapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(viewfinder);
    camera->start();

    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        imagecapture->capture();
    });
    connect(imagecapture,&QCameraImageCapture::imageCaptured,this,[=](int,QImage i){
        ui->label->setPixmap(QPixmap::fromImage(i));
    });
    connect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::saveimage);
    connect(ui->pushButton_3,&QPushButton::clicked,this,[=](){
        camera->stop();
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::saveimage()
{
    QDir *temp = new QDir;
    if(QString::compare(*name,ui->lineEdit->displayText())!=0)
    {
        i=0;
        *name=ui->lineEdit->displayText();
        qDebug()<<*name<<endl;
    }
    bool exist = temp->exists(QString("D:\\QT\\textimage\\%1").arg(ui->lineEdit->displayText()));
    if(!exist)
    {
        bool ok = temp->mkdir(QString("D:\\QT\\textimage\\%1").arg(ui->lineEdit->displayText()));
        if( ok )
            QMessageBox::warning(this,tr("创建文件夹"),QString("该对象第一次存入图像，为其设置新文件夹路径，D:\\QT\\textimage\\%1").arg(ui->lineEdit->displayText()));
    }
    const QPixmap *pixmap = ui->label->pixmap();
    pixmap->save(QString("D:\\QT\\textimage\\%1\\%2.jpg").arg(ui->lineEdit->displayText()).arg(i));
    i++;
}

void Widget::closeEvent(QCloseEvent *)
{
    camera->stop();
}

//void Widget::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//    QPen pen;
//    pen.setColor(QColor(0,255,0));
//    painter.setPen(pen);
//    painter.drawRect(0,0,100,100);

//}
