#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include "stack.h"
#include "paper.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QAction>

//Методы mainwindow.h
void write_pile(Stack pile, QTextEdit* stream)
    {
        int n = 0;
        Iterator i(pile);
        while(!i.atEnd())
        {
            n++;
            if (i.get()->type_return())
            {
                Plate* res = dynamic_cast<Plate*>(i.get());
                QString str = QString::number(n);
                stream->append(str + " Element\n");
                str = QString::number(res->get_x());
                stream->append("Coordinate 'x': " + str);
                str = QString::number(res->get_y());
                stream->append("Coordinate 'y': " + str);
                str = QString::number(res->get_thick());
                stream->append("Thickness: " + str);
                str = QString::number(res->get_rad());
                stream->append("Radius: " + str);
                stream->append("");
            }
            else
            {
                Paper* res = dynamic_cast<Paper*>(i.get());
                QString str = QString::number(n);
                stream->append(str);
                stream->append(str + " Element\n");
                str = QString::number(res->get_x());
                stream->append("Coordinate 'x': " + str);
                str = QString::number(res->get_y());
                stream->append("Coordinate 'y': " + str);
                str = QString::number(res->get_thick());
                stream->append("Thickness: " + str);
                str = QString::number(res->get_height());
                stream->append("Height: " + str);
                str = QString::number(res->get_wideth());
                stream->append("Wideth: " + str);
                stream->append("");
            }
            i.move();
        }
    }

namespace Randomer
{

    int integer(int from = INT_MIN, int to = INT_MAX) {
        return QRandomGenerator::global()->bounded(from, to);
    }
};

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow),
    m_doubleValidator(-100, 1000, 2, this), m_intValidator(1,1000,this)
{
    ui->setupUi(this);
    MainWindow::setFixedSize(520,115);
    ui->textBrowser->setLineWrapColumnOrWidth(QTextEdit::NoWrap);
    ui->textBrowser->hide();
    QMenu *file = menuBar()->addMenu("File");
    QMenu *del = menuBar()->addMenu("Edit");
    QAction *adder = new QAction(tr("Add paper"), this);
    adder->setShortcut(tr("Ctrl+I"));
    QAction *adder_1 = new QAction(tr("Add plate"), this);
    adder_1->setShortcut(tr("Ctrl+P"));
    QAction *saver = new QAction(tr("Save as"), this);
    QAction *save_simple = new QAction(tr("Save"), this);
    save_simple->setShortcut(tr("Ctrl+S"));
    QAction *newFile = new QAction(tr("Read file"), this);
    QAction *openFile = new QAction(tr("Open"), this);
    openFile->setShortcut(tr("Ctrl+O"));
    QAction *deleter = new QAction(tr("Delete all"), this);
    deleter->setShortcut(tr("Ctrl+Q"));
    QAction *deleter_1 = new QAction(tr("Delete first element"), this);
    deleter_1->setShortcut(tr("Ctrl+D"));
    connect(adder, SIGNAL(triggered()), this, SLOT(add()));
    connect(adder_1, SIGNAL(triggered()), this, SLOT(add_1()));
    connect(save_simple, SIGNAL(triggered()), this, SLOT(saver()));
    connect(newFile, SIGNAL(triggered()), this, SLOT(newed()));
    connect(saver, SIGNAL(triggered()), this, SLOT(saved()));
    connect(openFile, SIGNAL(triggered()), this, SLOT(opened()));
    connect(deleter, SIGNAL(triggered()), this, SLOT(deleted_all()));
    connect(deleter_1, SIGNAL(triggered()), this, SLOT(deleted()));
    file->addAction(save_simple);
    file->addAction(saver);
    file->addAction(newFile); // Привязка экшена к меню File
    file->addAction(openFile); // Привязка экшена к меню File
    del->addAction(deleter); // Привязка экшена к меню Delete
    del->addAction(deleter_1); // Привязка экшена к меню Delete
    del->addAction(adder);
    del->addAction(adder_1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    ui->lcdNumber->display(pile.get_numb());
    if (pile.balancer())
    {
        ui->label_13->setStyleSheet("QLabel { color : green; }");
        ui->label_13->setText("Куча \nнаходится\nв балансе");
    }
    else
    {
        ui->label_13->setStyleSheet("QLabel { color : red; }");
        ui->label_13->setText("Куча \nне находится\nв балансе");
    }
    reset_browser();
}

void MainWindow::reset_browser()
{
    ui->textBrowser->clear();
    QTextBrowser* stream = ui->textBrowser;
    int n = 0;
    Iterator i(pile);
    while(!i.atEnd())
    {
        n++;
        if (i.get()->type_return())
        {
            Plate* res = dynamic_cast<Plate*>(i.get());
            QString str = QString::number(n);
            stream->append(str + " Element");
            stream->append("Plate");
            str = QString::number(res->get_x());
            stream->append("Coordinate 'x': " + str);
            str = QString::number(res->get_y());
            stream->append("Coordinate 'y': " + str);
            str = QString::number(res->get_thick());
            stream->append("Thickness: " + str);
            str = QString::number(res->get_rad());
            stream->append("Radius: " + str);
            stream->append("\n");
        }
        else
        {
            Paper* res = dynamic_cast<Paper*>(i.get());
            QString str = QString::number(n);
            stream->append(str + " Element");
            stream->append("Paper");
            str = QString::number(res->get_x());
            stream->append("Coordinate 'x': " + str);
            str = QString::number(res->get_y());
            stream->append("Coordinate 'y': " + str);
            str = QString::number(res->get_thick());
            stream->append("Thickness: " + str);
            str = QString::number(res->get_height());
            stream->append("Height: " + str);
            str = QString::number(res->get_wideth());
            stream->append("Wideth: " + str);
            stream->append("\n");
        }
        i.move();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->textBrowser->isHidden())
    {
        MainWindow::setFixedSize(520,425);
        ui->frame_4->show();
        ui->textBrowser->show();
        ui->pushButton_2->setText("Hide elements of stack");
    }
    else
    {
        MainWindow::setFixedSize(520,115);
        ui->frame_4->hide();
        ui->textBrowser->hide();
        ui->pushButton_2->setText("Show elements of stack");
    }
}
