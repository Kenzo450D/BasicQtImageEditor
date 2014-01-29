#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPixmap>
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1130,700);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_released()   //Open Button
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("*.*"));

    if (fileName == "")
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open File"));
        return;
    }
    QImage img;
    img.load(fileName);
    this->scene = new QGraphicsScene;
    this->item.setPixmap(QPixmap::fromImage(img));
    this->scene->addItem(&(this->item));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    this->fileName = fileName;
    this->img = img;
}

void MainWindow::on_pushButton_2_released()    //"Save As" Button
{

}

void MainWindow::on_pushButton_3_released()     //"Save" Button
{
    this->img.save(this->fileName);
}

void MainWindow::on_pushButton_4_released()     //"Brighter" Button
{

    QColor c;
    int pixelData[3];
    //load Image Data (till previous filter)
    QString filePathName = this->fileName;
    QImage img = this->img;

    //Make Image brighter

    for (int y = 0 ; y < img.height(); y++)
    {
        for (int x = 0 ; x < img.width(); x++)
        {
            c = QColor::fromRgba(img.pixel(x,y));
            pixelData[0] = c.red();
            pixelData[1] = c.green();
            pixelData[2] = c.blue();

            for (int i = 0 ; i < 3 ; i ++ )
            {
                pixelData[i] = pixelData[i]+20;
                if (pixelData[i] > 255)
                    pixelData[i] = 255;
            }
            c.setRed(pixelData[0]);
            c.setGreen(pixelData[1]);
            c.setBlue(pixelData[2]);
            if (img.hasAlphaChannel())
            {
                img.setPixel(x,y,c.rgba());
            }
            else
            {
                img.setPixel(x,y,c.rgb());
            }
        }
    }
    this->scene = new QGraphicsScene;
    this->item.setPixmap(QPixmap::fromImage(img));
    this->scene->addItem(&(this->item));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    this->img = img;

}

void MainWindow::on_pushButton_5_released()     //"Darker" Button
{
    QColor c;
    int pixelData[3];
    //load Image Data (till previous filter)
    QString filePathName = this->fileName;
    QImage img = this->img;

    //Make Image brighter

    for (int y = 0 ; y < img.height(); y++)
    {
        for (int x = 0 ; x < img.width(); x++)
        {
            c = QColor::fromRgba(img.pixel(x,y));
            pixelData[0] = c.red();
            pixelData[1] = c.green();
            pixelData[2] = c.blue();

            for (int i = 0 ; i < 3 ; i ++ )
            {
                pixelData[i] = pixelData[i]-20;
                if (pixelData[i] < 0)
                    pixelData[i] = 0;
            }
            c.setRed(pixelData[0]);
            c.setGreen(pixelData[1]);
            c.setBlue(pixelData[2]);
            if (img.hasAlphaChannel())
            {
                img.setPixel(x,y,c.rgba());
            }
            else
            {
                img.setPixel(x,y,c.rgb());
            }
        }
    }
    this->scene = new QGraphicsScene;
    this->item.setPixmap(QPixmap::fromImage(img));
    this->scene->addItem(&(this->item));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    this->img = img;
}

void MainWindow::on_pushButton_6_released()     //"Contrast ++ " Button
{

}

void MainWindow::on_pushButton_7_released()     //"Contrast --" Button
{

}

void MainWindow::on_pushButton_8_released()     //"Blur" Button
{

}

void MainWindow::on_pushButton_9_released()     //"Sharpen" Button
{

}

void MainWindow::on_pushButton_10_released()    //"Warmer" Button
{

}

void MainWindow::on_pushButton_11_released()    //"Cooler" Button
{

}

void MainWindow::on_pushButton_12_released()    //"Saturate" Button
{
    QColor c;
    int pixelData[3];
    //load Image Data (till previous filter)
    QString filePathName = this->fileName;
    QImage img = this->img;

    //Make Image brighter

    for (int y = 0 ; y < img.height(); y++)
    {
        for (int x = 0 ; x < img.width(); x++)
        {
            //read pixel data
            c = QColor::fromRgba(img.pixel(x,y));

            //convert pixel data from rgb to hsl
            c = c.toHsl();
            pixelData[0] = c.hue();
            pixelData[1] = c.saturation();
            pixelData[2] = c.lightness();

            //increase saturation value
            pixelData[1] = pixelData[1] + 20;

            //check for overflow
            if (pixelData[1] > 255)
            {
                pixelData[1] = 255;
            }

            c.setHsl(pixelData[0],pixelData[1], pixelData[2]);
            c = c.toRgb();
            c.setAlpha(QColor::fromRgba(img.pixel(x,y)).alpha());
            if (img.hasAlphaChannel())
            {
                img.setPixel(x,y,c.rgba());
            }
            else
            {
                img.setPixel(x,y,c.rgb());
            }
        }
    }
    this->scene = new QGraphicsScene;
    this->item.setPixmap(QPixmap::fromImage(img));
    this->scene->addItem(&(this->item));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    this->img = img;
}

void MainWindow::on_pushButton_13_released()    //"Desaturate" Button
{
    QColor c;
    int pixelData[3];
    //load Image Data (till previous filter)
    QString filePathName = this->fileName;
    QImage img = this->img;

    //Make Image brighter

    for (int y = 0 ; y < img.height(); y++)
    {
        for (int x = 0 ; x < img.width(); x++)
        {
            //read pixel data
            c = QColor::fromRgba(img.pixel(x,y));

            //convert pixel data from rgb to hsl
            c = c.toHsl();
            pixelData[0] = c.hue();
            pixelData[1] = c.saturation();
            pixelData[2] = c.lightness();

            //decrease saturation value
            pixelData[1] = pixelData[1] - 50;


            //check for overflow
            if (pixelData[1] < 0)
            {
                pixelData[1] = 0;
            }

            c.setHsl(pixelData[0],pixelData[1], pixelData[2]);
            c = c.toRgb();
            c.setAlpha(QColor::fromRgba(img.pixel(x,y)).alpha());
            if (img.hasAlphaChannel())
            {
                img.setPixel(x,y,c.rgba());
            }
            else
            {
                img.setPixel(x,y,c.rgb());
            }
        }
    }
    this->scene = new QGraphicsScene;
    this->item.setPixmap(QPixmap::fromImage(img));
    this->scene->addItem(&(this->item));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    this->img = img;
}

void MainWindow::on_pushButton_14_released()    //"Sepia" Button
{
    QColor c;
    int pixelData[3], red, green, blue;
    //load Image Data (till previous filter)
    QString filePathName = this->fileName;
    QImage img = this->img;

    //Make Image brighter

    for (int y = 0 ; y < img.height(); y++)
    {
        for (int x = 0 ; x < img.width(); x++)
        {
            c = QColor::fromRgba(img.pixel(x,y));
            red = c.red();
            green = c.green();
            blue = c.blue();


            //edit pixel data to convert to sepia tone
            pixelData[0] = (red * .393) + (green *.769) + (blue * .189);
            pixelData[1] = (red * .349) + (green *.686) + (blue * .168);
            pixelData[2] = (red * .272) + (green *.534) + (blue * .131);

            for (int i = 0 ; i < 3 ; i ++ )
            {
                if (pixelData[i] > 255)
                    pixelData[i] = 255;
            }
            c.setRed(pixelData[0]);
            c.setGreen(pixelData[1]);
            c.setBlue(pixelData[2]);
            if (img.hasAlphaChannel())
            {
                img.setPixel(x,y,c.rgba());
            }
            else
            {
                img.setPixel(x,y,c.rgb());
            }
        }
    }
    this->scene = new QGraphicsScene;
    this->item.setPixmap(QPixmap::fromImage(img));
    this->scene->addItem(&(this->item));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    this->img = img;
}

void MainWindow::on_pushButton_15_released()    //"Negative" Button
{
    QColor c;
    int pixelData[3];
    //load Image Data (till previous filter)
    QString filePathName = this->fileName;
    QImage img = this->img;

    //Make Image negative

    for (int y = 0 ; y < img.height(); y++)
    {
        for (int x = 0 ; x < img.width(); x++)
        {
            c = QColor::fromRgba(img.pixel(x,y));
            pixelData[0] = c.red();
            pixelData[1] = c.green();
            pixelData[2] = c.blue();

            for (int i = 0 ; i < 3 ; i ++ )
            {
                pixelData[i] = 255 - pixelData[i];
            }
            c.setRed(pixelData[0]);
            c.setGreen(pixelData[1]);
            c.setBlue(pixelData[2]);
            if (img.hasAlphaChannel())
            {
                img.setPixel(x,y,c.rgba());
            }
            else
            {
                img.setPixel(x,y,c.rgb());
            }
        }
    }
    this->scene = new QGraphicsScene;
    this->item.setPixmap(QPixmap::fromImage(img));
    this->scene->addItem(&(this->item));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    this->img = img;
}

void MainWindow::on_pushButton_16_released() // "Grayscale" button
{
    QColor c;
    int pixelData[3];
    //load Image Data (till previous filter)
    QString filePathName = this->fileName;
    QImage img = this->img;



    for (int y = 0 ; y < img.height(); y++)
    {
        for (int x = 0 ; x < img.width(); x++)
        {
            c = QColor::fromRgba(img.pixel(x,y));
            pixelData[0] = c.red();
            pixelData[1] = c.green();
            pixelData[2] = c.blue();

            int grayPixel = (pixelData[0] + pixelData[1] +pixelData[2]) / 3;

            for (int i = 0 ; i < 3 ; i ++ )
            {
                pixelData[i] = grayPixel;
            }
            c.setRed(pixelData[0]);
            c.setGreen(pixelData[1]);
            c.setBlue(pixelData[2]);
            if (img.hasAlphaChannel())
            {
                img.setPixel(x,y,c.rgba());
            }
            else
            {
                img.setPixel(x,y,c.rgb());
            }
        }
    }
    this->scene = new QGraphicsScene;
    this->item.setPixmap(QPixmap::fromImage(img));
    this->scene->addItem(&(this->item));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    this->img = img;
}

void MainWindow::on_pushButton_17_released() // "Black and White" button
{
    QColor c;
    int pixelData[3];
    //load Image Data (till previous filter)
    QString filePathName = this->fileName;
    QImage img = this->img;



    for (int y = 0 ; y < img.height(); y++)
    {
        for (int x = 0 ; x < img.width(); x++)
        {
            c = QColor::fromRgba(img.pixel(x,y));
            pixelData[0] = c.red();
            pixelData[1] = c.green();
            pixelData[2] = c.blue();

            int grayPixel = (pixelData[0] + pixelData[1] +pixelData[2]) / 3;

            if(grayPixel < 128)
                grayPixel = 0;
            else
                grayPixel = 255;

            for (int i = 0 ; i < 3 ; i ++ )
            {
                pixelData[i] = grayPixel;
            }

            c.setRed(pixelData[0]);
            c.setGreen(pixelData[1]);
            c.setBlue(pixelData[2]);
            if (img.hasAlphaChannel())
            {
                img.setPixel(x,y,c.rgba());
            }
            else
            {
                img.setPixel(x,y,c.rgb());
            }
        }
    }
    this->scene = new QGraphicsScene;
    this->item.setPixmap(QPixmap::fromImage(img));
    this->scene->addItem(&(this->item));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    this->img = img;
}
