#ifndef PAPER_H
#define PAPER_H

#include <iostream>
#include <QTextStream>

/*Базовый класс, класс родитель для классов Paper и Plate*/
class Base
{
    public:
        double get_x() const{ return x_;}
        void set_x(double x){set_double(&x_,x,-10000,10000,x_);}
        double get_y() const{ return y_;}
        void set_y(double y){set_double(&y_,y,-10000,10000,y_);}
        double get_thick() const{ return thick_;}
        virtual void set_thick(double thick) = 0;
        virtual void show(QTextStream *stream) = 0;
        virtual bool read(QTextStream *stream) = 0;
        bool input();
        virtual bool type_return() = 0;
        virtual ~Base();
    protected:
        double x_,y_,thick_;
        unsigned int mass;
        void set_double(double* k_, double k, int a, int b, double n);
        void set_natural(int* k_, int k, int a, int b, int n);
        QString only_number(QString str)//проверка на то, является ли строка числом
        {
            while (!str[0].isDigit() && !str.isEmpty())
                str.remove(0,1);
            return str;
        }
};

/*Класс бумаги, наследуется от Base*/
class Paper: public Base
{
   public:
       Paper(int height = 1, int wideth = 1, double thick = 1, double x = 0, double y = 0);//конструктор по умолчанию
       Paper(const Paper &paper);
       ~Paper() override {}
       //Методы доступа к полям класса
       int get_height() const{ return height_; }
       void set_height(int height);
       int get_wideth() const{ return wideth_; }
       void set_wideth(int wideth);
       bool type_return() override {return 0;}
       void set_thick(double thick) override {set_double(&thick_,thick,0,3,thick_);}
       void show(QTextStream *stream) override;
       bool read(QTextStream *stream) override;
   private:
       int height_, wideth_;//свойства класса: высота, ширина и толщина соответственно
};

/*Класс тарелки, наследуется от Base*/
class Plate: public Base
{
    public:
        Plate(int rad = 1, double thick = 1, double x = 0, double y = 0);
        Plate(const Plate &plate);
        ~Plate() override {}
        int get_rad() const{ return rad_; }
        void set_rad(int rad);
        void show(QTextStream *stream) override;
        bool read(QTextStream *stream) override;
        bool type_return() override {return 1;}
        void set_thick(double thick) override {set_double(&thick_,thick,0,10,thick_);}
    private:
        int rad_;
};

#endif // PAPER_H
