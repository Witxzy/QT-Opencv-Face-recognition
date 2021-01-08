#include "mainwindow.h"
#include "ui_mainwindow.h"

mainwindow::mainwindow(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    cascade.load("D:/opencv/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");
    model = EigenFaceRecognizer::create();
    model->read("D:/QT/textimage/model1.xml");
    ui->setupUi(this);
    ui->label->setScaledContents(true);
//    Mat image=imread("D:/QT/textimage/430/3.jpg");
//    imshow("123",this->Cascade(image));
    toolBar->setParent(this);
    toolBar->setAllowedAreas(Qt::LeftToolBarArea);
    addToolBar(Qt::LeftToolBarArea,toolBar);

    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        Widget *camera = new Widget;
        camera->show();
    });

    connect(ui->pushButton_2,&QPushButton::clicked,this,&mainwindow::ImportImage);

    connect(ui->pushButton_3,&QPushButton::clicked,this,[=](){
         qDebug()<<file<<endl;
         qDebug()<<"1"<<endl;
         qDebug()<<QString("D:/QT/textimage/").append("0.jpg")<<endl;
         qDebug()<<"1"<<endl;
         qDebug()<<"2"<<endl;
         cout<<QString("D:/QT/textimage/").append("0.jpg").toStdString()<<endl;
         qDebug()<<"2"<<endl;

     });
}

mainwindow::~mainwindow()
{
    delete ui;
}

QImage mainwindow::Mat2QImage(Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)                             //3 channels color image
    {

        cv::cvtColor(cvImg,cvImg,CV_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols, cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    return qImg;
}
Mat mainwindow::qimage2mat(const QImage& qimage)
{
      Mat mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, (uchar*)qimage.bits(), qimage.bytesPerLine());
      Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
      int from_to[] = { 0,0, 1,1, 2,2 };
      mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
      return mat2;
}
Mat mainwindow::Cascade(Mat image)
{
    Mat transformImage;
    vector<Rect> faceRect;
    int a=-1;
    //int a = model->predict(imread("D:/1.jpg",IMREAD_GRAYSCALE));
    cvtColor(image,transformImage,COLOR_BGRA2GRAY);
    equalizeHist(transformImage,transformImage);
    cascade.detectMultiScale(transformImage,faceRect,1.1,3,0,Size(100,100),Size(300,300));
    for( int i=0;i<faceRect.size();++i)
    {
        int x=faceRect.at(i).x;
        int y=faceRect.at(i).y;
        Mat setSizeImage = image(Rect(x-50,y-50,240,240));
        cvtColor(setSizeImage,setSizeImage,COLOR_BGR2GRAY);
        rectangle(image,faceRect.at(i),Scalar(255,0,0));
        a = model->predict(setSizeImage);
        if(a==1)
        {
            putText(image,"this is xzy",Point(faceRect.at(i).x,faceRect.at(i).y),FONT_HERSHEY_SIMPLEX ,2,Scalar(0,255,255));
        }else if(a==2)
        {
            putText(image,"this is ljc",Point(faceRect.at(i).x,faceRect.at(i).y),FONT_HERSHEY_SIMPLEX ,2,Scalar(0,0,255));
        }
    }

    return image;
}
void mainwindow::ImportImage()
{
    QFileDialog *fileDialog = new QFileDialog;
    fileDialog->setParent(this);
    fileDialog->setWindowTitle("导入照片文件");
    fileDialog->setDirectory(QDir(QString("D:/QT/textimage")));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    if(fileDialog->exec() == QDialog::Accepted)
    {
         file = fileDialog->selectedFiles();
         for (int i=0;i<file.count();++i)
         {
              //qDebug()<<action;
              connect(toolBar->addAction(file[i].remove("D:/QT/textimage/")),&QAction::triggered,[=](){
                  Mat displayImage = imread(QString("D:/QT/textimage/").append(file[i]).toStdString().data());
                  ui->label->setPixmap(QPixmap::fromImage(Mat2QImage(Cascade(displayImage))));
                  qDebug()<<file[i];
              });
         }
    }
}
