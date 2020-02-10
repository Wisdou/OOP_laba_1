#include "paper.h"

Base::~Base(){}//деструктор класса Base

/*Проверка на то, что число k находится в определённых границах: a - верхняя
граница, b - нижняя граница, n - значение которое присваивается полю k_ по
умолчанию (то есть когда k не удовлетворяет условиям k<=a и k>=b)*/
inline void Base::set_double(double* k_, double k, int a, int b, double n){
    if (k <= a || k > b)
        *k_ = n;
    else
        *k_ = k;
}

/*Проверка на то, что число k находится в определённых границах: a - верхняя
граница, b - нижняя граница, n - значение которое присваивается полю k_ по
умолчанию (то есть когда k не удовлетворяет условиям k<=a и k>=b)*/
inline void Base::set_natural(int* k_, int k, int a, int b, int n){
    if (k <= a || k >= b)
        *k_ = n;
    else
        *k_ = k;
}


//Конструктор инициализации//
Paper::Paper(int height, int wideth, double thick, double x, double y)
{
     set_double(&x_,x,-10000,10000,0);
     set_double(&y_,y,-10000,10000,0);
     set_double(&thick_,thick,0,3,1);
     set_natural(&wideth_,wideth,0,210,1);
     set_natural(&height_,height,0,300,1);
}

//Конструктор копирования
/*Значение переносится по ссылке для того, чтобы избежать копирования объекта
const указывает на то, что значение объекта не изменяется внутри метода*/
Paper::Paper(const Paper &sheet)
{
   x_ = sheet.x_;
   y_ = sheet.y_;
   wideth_ = sheet.wideth_;
   height_ = sheet.height_;
   thick_ = sheet.thick_;
}

void Paper::show(QTextStream *stream)/*вывод элементов в текстовый поток, создан
для того, что выводить элементы в консоль, файл или Qt виджеты*/
{
    *stream << "Paper" << "\n";
    *stream << "Height: " << QString::number(this->get_height()) << "\n";
    *stream << "Thickness: " << QString::number(this->get_thick()) << "\n";
    *stream << "Wideth: " << QString::number(this->get_wideth()) << "\n";
    *stream << "Coordinate 'x': " << QString::number(this->get_x()) << "\n";
    *stream << "Coordinate 'y': " << QString::number(this->get_y()) << "\n\n";
}

bool Paper::read(QTextStream *stream)//чтение элементов из текстового потока
{
    int h,w;
    double x,y,t;
    QString str;
    str = stream->readLine();
    str = only_number(str);
    if (str != "\n" && str.toInt() > 0 && str.toInt() < 300)
        h = str.toInt();
    else
        return 0;
    str = stream->readLine();
    str = only_number(str);
    if (str != "\n" && str.toDouble() > 0 && str.toDouble() < 3)
        t = str.toDouble();
    else
        return 0;
    str = stream->readLine();
    str = only_number(str);
    if (str != "\n" && str.toInt() > 0 && str.toInt() < 210)
        w = str.toInt();
    else
        return 0;
    str = stream->readLine();
    str = only_number(str);
    if (str != "\n"  && str.toFloat() > -10000 && str.toFloat() < 10000)
        x = str.toDouble();
    else
        return 0;
    str = stream->readLine();
    str = only_number(str);
    if (str != "\n" && str.toFloat() > -10000 && str.toFloat() < 10000)
        y = str.toDouble();
    else
        return 0;
    set_wideth(w);
    set_height(h);
    set_x(x);
    set_thick(t);
    set_y(y);
    return 1;
}

//Геттеры и сеттеры для полей класса Paper
//***//
void Paper::set_height(int height){
    set_natural(&height_,height,0,300,height_);
}

void Paper::set_wideth(int wideth){
    set_natural(&wideth_,wideth,0,210,wideth_);
}
//***//

void Plate::show(QTextStream *stream)/*вывод элементов в текстовый поток, создан
для того, что выводить элементы в консоль, файл или Qt виджеты*/
{
    *stream << "Plate" << "\n";
    *stream << "Thickness: " << QString::number(this->get_thick()) << "\n";
    *stream << "Radius: " << QString::number(this->get_rad()) << "\n";
    *stream << "Coordinate 'x': " << QString::number(this->get_x()) << "\n";
    *stream << "Coordinate 'y': " << QString::number(this->get_y()) << "\n\n";
}

bool Plate::read(QTextStream *stream)//чтение элементов из текстового потока
{
    int rad;
    double x,y,t;
    QString str;
    str = stream->readLine();
    str = only_number(str);
    if (str != "\n" && str.toDouble() > 0 && str.toDouble() < 10)
        t = str.toDouble();
    else
        return 0;
    str = stream->readLine();
    str = only_number(str);
    if (str != "\n" && str.toInt() > 0 && str.toInt() < 1000)
        rad = str.toInt();
    else
        return 0;
    str = stream->readLine();
    str = only_number(str);
    if (str != "\n"  && str.toFloat() > -10000 && str.toFloat() < 10000)
        x = str.toDouble();
    else
        return 0;
    str = stream->readLine();
    str = only_number(str);
    if (str != "\n" && str.toFloat() > -10000 && str.toFloat() < 10000)
        y = str.toDouble();
    else
        return 0;
    set_rad(rad);
    set_x(x);
    set_thick(t);
    set_y(y);
    return 1;
}

Plate::Plate(int rad, double thick, double x, double y){//конструктор инициализации
    set_thick(thick);
    set_rad(rad);
    set_x(x);
    set_y(y);
}

/*Значение переносится по ссылке для того, чтобы избежать копирования объекта
const указывает на то, что значение объекта не изменяется внутри метода*/
Plate::Plate(const Plate &plate){//конструктор копирования
    x_ = plate.x_;
    y_ = plate.y_;
    thick_ = plate.thick_;
    rad_ = plate.rad_;
}

/*Геттеры и сеттеры*/
//***//
void Plate::set_rad(int rad){
    set_natural(&rad_,rad,0,1000,rad_);
}
//***//
