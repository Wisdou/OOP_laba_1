#include <stdlib.h> //Содержит функции выделения памяти(new, malloc, calloc); преобразования типов (atoi,atof); контроль процесса выполнения(exit,system)
#include <iostream> //Библиотека ввода/ вывода в C++. Потоковый ввод/ вывод.
#include <QApplication>
#include "mainwindow.h"
#include "stack.h"

int main(int argc, char* argv[])
{   
    QApplication app(argc,argv);
    MainWindow w;
    w.show();
    return app.exec();
}
