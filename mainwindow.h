#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stack.h"
#include <QDoubleValidator>
#include <QIntValidator>
#include <QFileDialog>
#include <QWidget>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QCoreApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//Класс GUI-приложения
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void reset();
    void reset_size();
    void reset_browser();

private slots:
    //Слоты для работы
    void add()
    {
        QDialog adder(this);
        adder.setWindowTitle(tr("Add element"));
        QLineEdit *ledit1 = new QLineEdit(&adder);
        QLineEdit *ledit2 = new QLineEdit(&adder);
        QLineEdit *ledit3 = new QLineEdit(&adder);
        QLineEdit *ledit4 = new QLineEdit(&adder);
        QLineEdit *ledit5 = new QLineEdit(&adder);
        QLineEdit *ledit6 = new QLineEdit(&adder);
        ledit1->setValidator(&m_intValidator);
        ledit2->setValidator(&m_intValidator);
        ledit3->setValidator(&m_doubleValidator);
        ledit4->setValidator(&m_doubleValidator);
        ledit5->setValidator(&m_doubleValidator);
        ledit6->setValidator(&m_intValidator);
        QDialogButtonBox *btn_box = new QDialogButtonBox(&adder);
        btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        connect(btn_box, &QDialogButtonBox::accepted, &adder, &QDialog::accept);
        connect(btn_box, &QDialogButtonBox::rejected, &adder, &QDialog::reject);

        QFormLayout *layout = new QFormLayout();
        layout->addRow(tr("Input height:"), ledit1);
        layout->addRow(tr("Input wideth:"), ledit2);
        layout->addRow(tr("Input thickness:"), ledit3);
        layout->addRow(tr("Input coordinate 'x':"), ledit4);
        layout->addRow(tr("Input coordinate 'y':"), ledit5);
        layout->addRow(tr("Input the number of elements:"), ledit6);
        layout->addWidget(btn_box);

        adder.setLayout(layout);
        // В случае, если пользователь нажал "Ok".
        if(adder.exec() == QDialog::Accepted) {
            int h,w;
            double x,y,t;
            bool flag = true;
            QString str;
            str = ledit1->text();
            if (str != "\n" && str.toInt() > 0 && str.toInt() < 300)
                h = str.toInt();
            else
            {
                QMessageBox error;
                error.setText("Wrong data!");
                error.setWindowTitle("Error");
                error.exec();
                flag = false;
            }
            str = ledit2->text();
            if (str != "\n" && str.toInt() > 0 && str.toInt() < 210)
                w = str.toInt();
            else
            {
                QMessageBox error;
                error.setText("Wrong data!");
                error.setWindowTitle("Error");
                error.exec();
                flag = false;
            }
            str = ledit3->text();
            if (str != "\n" && str.toFloat() > 0 && str.toFloat() < 3)
                t = str.toDouble();
            else
            {
                QMessageBox error;
                error.setText("Wrong data!");
                error.setWindowTitle("Error");
                error.exec();
                flag = false;
            }
            str = ledit4->text();
            if (str != "\n"  && str.toFloat() > -10000 && str.toFloat() < 10000)
                x = str.toDouble();
            else
            {
                QMessageBox error;
                error.setText("Wrong data!");
                error.setWindowTitle("Error");
                error.exec();
                flag = false;
            }
            str = ledit5->text();
            if (str != "\n" && str.toFloat() > -10000 && str.toFloat() < 10000)
                y = str.toDouble();
            else
            {
                QMessageBox error;
                error.setText("Wrong data!");
                error.setWindowTitle("Error");
                error.exec();
                flag = false;
            }
            str = ledit6->text();
            int n = str.toInt();
            for (int i = 0; i < n && flag; i++)
            {
                Base* elem = new Paper(h,w,t,x,y);
                pile.push(elem);
            }
            reset();
        }
    }

    void add_1()
    {
        QDialog adder(this);
        adder.setWindowTitle(tr("Add element"));
        QLineEdit *ledit2 = new QLineEdit(&adder);
        QLineEdit *ledit3 = new QLineEdit(&adder);
        QLineEdit *ledit4 = new QLineEdit(&adder);
        QLineEdit *ledit5 = new QLineEdit(&adder);
        QLineEdit *ledit6 = new QLineEdit(&adder);
        ledit2->setValidator(&m_intValidator);
        ledit3->setValidator(&m_doubleValidator);
        ledit4->setValidator(&m_doubleValidator);
        ledit5->setValidator(&m_doubleValidator);
        ledit6->setValidator(&m_intValidator);
        QDialogButtonBox *btn_box = new QDialogButtonBox(&adder);
        btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        connect(btn_box, &QDialogButtonBox::accepted, &adder, &QDialog::accept);
        connect(btn_box, &QDialogButtonBox::rejected, &adder, &QDialog::reject);

        QFormLayout *layout = new QFormLayout();
        layout->addRow(tr("Input radius:"), ledit2);
        layout->addRow(tr("Input thickness:"), ledit3);
        layout->addRow(tr("Input coordinate 'x':"), ledit4);
        layout->addRow(tr("Input coordinate 'y':"), ledit5);
        layout->addRow(tr("Input the number of elements:"), ledit6);
        layout->addWidget(btn_box);

        adder.setLayout(layout);

        // В случае, если пользователь нажал "Ok".
        if(adder.exec() == QDialog::Accepted) {
            int rad;
            double x,y,t;
            bool flag = true;
            QString str;
            str = ledit2->text();
            if (str != "\n" && str.toInt() > 0 && str.toInt() < 210)
                rad = str.toInt();
            else
            {
                QMessageBox error;
                error.setText("Wrong data!");
                error.setWindowTitle("Error");
                error.exec();
                flag = false;
            }
            str = ledit3->text();
            if (str != "\n" && str.toFloat() > 0 && str.toFloat() < 10)
                t = str.toDouble();
            else
            {
                QMessageBox error;
                error.setText("Wrong data!");
                error.setWindowTitle("Error");
                error.exec();
                flag = false;
            }
            str = ledit4->text();
            if (str != "\n"  && str.toFloat() > -10000 && str.toFloat() < 10000)
                x = str.toDouble();
            else
            {
                QMessageBox error;
                error.setText("Wrong data!");
                error.setWindowTitle("Error");
                error.exec();
                flag = false;
            }
            str = ledit5->text();
            if (str != "\n" && str.toFloat() > -10000 && str.toFloat() < 10000)
                y = str.toDouble();
            else
            {
                QMessageBox error;
                error.setText("Wrong data!");
                error.setWindowTitle("Error");
                error.exec();
                flag = false;
            }
            str = ledit6->text();
            int n = str.toInt();
            for (int i = 0; i < n && flag; i++)
            {
                Base* elem = new Paper(rad,t,x,y);
                pile.push(elem);
            }
            reset();
        }
    }

    void deleted()
    {
        pile.pop();
        reset();
    }

    void deleted_all()
    {
        pile.~Stack();
        reset();
    }

    void opened()
    {
        pile.~Stack();
        opendir(filename);
    }

    void newed()
    {
        QString fileName;
        opendir(fileName);
    }

    void saved()
    {
        QDialog dlg(this);
        dlg.setWindowTitle(tr("Save file"));

        QLineEdit *ledit1 = new QLineEdit(&dlg);

        QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
        btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
        connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

        QFormLayout *layout = new QFormLayout();
        layout->addRow(tr("Enter the name of file for saving:"), ledit1);
        layout->addWidget(btn_box);

        dlg.setLayout(layout);

        // В случае, если пользователь нажал "Ok".
        if(dlg.exec() == QDialog::Accepted) {
            QString str1 = ledit1->text();
            if (str1[0] == '/' || str1[0] == '\\')
            {
                QMessageBox error;
                error.setText("Название файла не должно\n содержать символы '\' и '/'!");
                error.setWindowTitle("Ошибка");
                error.exec();
            }
            else
                filer(str1);
        }
    }

    void saver()
    {
        if (filename.isEmpty())
        {
            QDialog dlg(this);
            dlg.setWindowTitle(tr("Save file"));

            QLineEdit *ledit1 = new QLineEdit(&dlg);

            QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
            btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

            connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
            connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

            QFormLayout *layout = new QFormLayout();
            layout->addRow(tr("Enter the name of file for saving:"), ledit1);
            layout->addWidget(btn_box);

            dlg.setLayout(layout);

            // В случае, если пользователь нажал "Ok".
            if(dlg.exec() == QDialog::Accepted) {
                QString str1 = ledit1->text();
                if (str1[0] == '/' || str1[0] == '\\')
                {
                    QMessageBox error;
                    error.setText("Название файла не должно\n содержать символы '\' и '/'!");
                    error.setWindowTitle("Ошибка");
                    error.exec();
                }
                else
                    filer(str1);
            }
        }
        else
            pile.write_file(filename);
    }

    void on_pushButton_2_clicked();

private:
    void filer(QString str)
    {
        QString dir = QCoreApplication::applicationDirPath() +"/Files";
        str = dir + str + ".txt";
        pile.write_file(str);
        filename = str;
    }
    void opendir(QString str)
    {
        QString dir = QCoreApplication::applicationDirPath() +"/Files";
        str = QFileDialog::getOpenFileName(this,tr("Open text file"), dir, tr("Text Files (*.txt)"));
        pile.file_read(str);
        reset();
    }
    Ui::MainWindow *ui;
    Stack pile;
    QDoubleValidator m_doubleValidator;
    QIntValidator m_intValidator;
    QString filename;
};

#endif // MAINWINDOW_H
