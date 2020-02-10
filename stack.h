#ifndef STACK_H
#define STACK_H

#include "paper.h"
#include <QFile>
#include <QTextStream>
#include <cmath>

struct Part
{
    Base* elem_;
    Part* p_;
};

class Iterator;

class Stack
{
    public:
        friend class Iterator;
        Stack();//конструктор по умолчанию
        Stack(const Stack &pile);//конструктор копирования
        ~Stack();//Деструктор класса стека
        void pop();//удаление элемента из стэка
        void push(Base* element);//добавление элемента в стэк
        void file_read(QString file_name);//чтение из файла
        void write_file(QString file_name);//запись в файл;
        void write_file_1(QString file_name);//запись в файл;
        Base* peek(int n) const;// получение определённого элемента стека
        int get_numb() const {return numb;}//возвращает число элементов в стеке
        bool balancer();//возвращает True если куча в балансе, иначе False
    private:
        bool empty() const;//проверка на то, является ли стек пустым
        int balance(Base* element);//проверка на равновесие
        Part* top = nullptr;//верхний элемент стека
        int numb;//число элементов в стеке
        int unbal;//поле для проверки на равновесие: 0 - в равновесии, 1 - не в равновесии
        double pile_height;//высота кучи (сумма толщины всех элементов, хранимых в стеке)
        bool check_falling(Base* element);//проверка на то, чтобы элемент падал на верхушку стека
        void inc_height(const Base &element) {pile_height += element.get_thick();}
        void dec_height(const Base &element) {pile_height -= element.get_thick();}
};

//Итератор для созданной коллекции, позволяет осуществлять перемещение по коллекции
//без её изменения
class Iterator
{
    public:
        Iterator(const Stack &pile){curr_ = pile.top;}
        bool atEnd(){return curr_ ? false:true;}
        void move(){curr_ = curr_->p_;}
        Base* get(){return curr_->elem_;}
    private:
        Part* curr_;
};

#endif // STACK_H
