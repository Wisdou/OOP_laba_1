#ifndef STACKER_H
#define STACKER_H

#include "stack.h"

double distance(double x1, double x2, double y1, double y2)
{
    double res_x = pow((x1 - x2),2);
    double res_y = pow((y1 - y2),2);
    double res = pow((res_x+res_y),0.5);
    return res;
}

//Проверка на баланс
bool Stack::balancer()
{
    if (unbal == 0)
        return 1;
    else
        return 0;
}

//Проверка на то, падает ли новый элемент на предыдущий: если да - добавляется в стек
//Возвращает True - если новый элемент падает на предыдущий, False - в другом случае
bool Stack::check_falling(Base* element)//element - новый элемент
{
    Base* previous_element = top->elem_;
    //Если первый элемент в стеке и новый элемент - тарелки
    if (previous_element->type_return() && element->type_return())
    {
        Plate* element_up = dynamic_cast<Plate*>(element);
        Plate* previous_element_up = dynamic_cast<Plate*>(previous_element);
        if (distance(previous_element->get_x(),element_up->get_x(),previous_element->get_y(),element_up->get_y())
                > (previous_element_up->get_rad() + element_up->get_rad()))
            return 0;
    }

    //Если первый элемент в стеке - листок бумаги и новый элемент - тарелка
    if (!previous_element->type_return() && element->type_return())
    {
        Plate* element_up = dynamic_cast<Plate*>(element);
        Paper* previous_element_up = dynamic_cast<Paper*>(previous_element);
        double point_1 = previous_element_up->get_x() + previous_element_up->get_wideth();
        double point_2 = previous_element_up->get_x();
        double point_3 = previous_element_up->get_y() + previous_element_up->get_height();
        double point_4 = previous_element_up->get_y();
        if (element_up->get_y() > point_3)
        {
            if (element_up->get_x() < point_2)
                if (distance(element_up->get_x(),point_2,element_up->get_y(),point_3) < element_up->get_rad())
                    return 1;
            if (element_up->get_x() >= point_2 && element_up->get_x() <= point_1)
                if (point_3 < (element_up->get_y() - element_up->get_rad()))
                    return 1;
            if (element_up->get_x() > point_1)
                if (distance(element_up->get_x(),point_1,element_up->get_y(),point_3) < element_up->get_rad())
                    return 1;
        }
        if (element_up->get_y() <= point_3 && element_up->get_y() >= point_4)
        {
            if (element_up->get_x() < point_2)
                if (point_2 < (element_up->get_rad() + element_up->get_x()))
                    return 1;
            if (element_up->get_x() >= point_2 && element_up->get_x() <= point_1)
                return 1;
            if (element_up->get_x() > point_1)
                if ((element_up->get_x() - element_up->get_rad()) < point_1)
                    return 1;
        }
        if (element_up->get_y() < point_4)
        {
            if (element_up->get_x() < point_2)
                if (distance(element_up->get_x(),point_2,element_up->get_y(),point_4) < element_up->get_rad())
                    return 1;
            if (element_up->get_x() >= point_2 && element_up->get_x() <= point_1)
                if (point_4 < (element_up->get_y() + element_up->get_rad()))
                    return 1;
            if (element_up->get_x() > point_1)
                if (distance(element_up->get_x(),point_1,element_up->get_y(),point_4) < element_up->get_rad())
                    return 1;
        }
        return 0;
    }

    //Если первый элемент в стеке - тарелка и новый элемент - листок бумаги
    if (previous_element->type_return() && !element->type_return())
    {
        Paper* element_up = dynamic_cast<Paper*>(element);
        Plate* previous_element_up = dynamic_cast<Plate*>(previous_element);
        double point_1 = element_up->get_x() + element_up->get_wideth();
        double point_2 = element_up->get_x();
        double point_3 = element_up->get_y() + element_up->get_height();
        double point_4 = element_up->get_y();
        if (previous_element_up->get_y() > point_3)
        {
            if (previous_element_up->get_x() < point_2)
                if (distance(previous_element_up->get_x(),point_2,previous_element_up->get_y(),point_3) < previous_element_up->get_rad())
                    return 1;
            if (previous_element_up->get_x() >= point_2 && previous_element_up->get_x() <= point_1)
                if (point_3 < (previous_element_up->get_y() - previous_element_up->get_rad()))
                    return 1;
            if (previous_element_up->get_x() > point_1)
                if (distance(previous_element_up->get_x(),point_1,previous_element_up->get_y(),point_3) < previous_element_up->get_rad())
                    return 1;
        }
        if (previous_element_up->get_y() <= point_3 && previous_element_up->get_y() >= point_4)
        {
            if (previous_element_up->get_x() < point_2)
                if (point_2 < (previous_element_up->get_rad() + previous_element_up->get_x()))
                    return 1;
            if (previous_element_up->get_x() >= point_2 && previous_element_up->get_x() <= point_1)
                return 1;
            if (previous_element_up->get_x() > point_1)
                if ((previous_element_up->get_x() - previous_element_up->get_rad()) < point_1)
                    return 1;
        }
        if (previous_element_up->get_y() < point_4)
        {
            if (previous_element_up->get_x() < point_2)
                if (distance(previous_element_up->get_x(),point_2,previous_element_up->get_y(),point_4) < previous_element_up->get_rad())
                    return 1;
            if (previous_element_up->get_x() >= point_2 && previous_element_up->get_x() <= point_1)
                if (point_4 < (previous_element_up->get_y() + previous_element_up->get_rad()))
                    return 1;
            if (previous_element_up->get_x() > point_1)
                if (distance(previous_element_up->get_x(),point_1,previous_element_up->get_y(),point_4) < previous_element_up->get_rad())
                    return 1;
        }
        return 0;
    }

    //Если первый элемент в стеке и новый - листки бумаги
    if (!previous_element->type_return() && !element->type_return())
    {
        Paper* element_up = dynamic_cast<Paper*>(element);
        Paper* previous_element_up = dynamic_cast<Paper*>(previous_element);
        if ((previous_element_up->get_x() > (element_up->get_x() + element_up->get_wideth())) ||
                ((previous_element_up->get_x() + previous_element_up->get_wideth()) <
                 element_up->get_x()))
            return 0;
        else if ((previous_element_up->get_y() > (element_up->get_y() + element_up->get_height())) ||
                 ((previous_element_up->get_y() + previous_element_up->get_height()) <
                  element_up->get_y()))
            return 0;
    }
    return 1;
}


int Stack::balance(Base* element)
{
    if (empty())
        return 0;
    int n = 0;
    Base* previous_element = top->elem_;
    //Если первый элемент в стеке и новый элемент - тарелки
    if (previous_element->type_return() && element->type_return())
    {
        /*Баланс нарушается, если расстояние между центрами двух тарелок
        превышает радиус одной из них*/
        Plate* element_up = dynamic_cast<Plate*>(element);
        Plate* previous_element_up = dynamic_cast<Plate*>(previous_element);
        if ((distance(previous_element_up->get_x(),element_up->get_x(),previous_element_up->get_y(),element_up->get_y()) > element_up->get_rad()) &&
           distance(previous_element_up->get_x(),element_up->get_x(),previous_element_up->get_y(),element_up->get_y()) > previous_element_up->get_rad())
            n++;
    }

    //Если первый элемент в стеке - листок бумаги и новый элемент - тарелка
    if (!previous_element->type_return() && element->type_return())
    {
        /*Баланс нарушается, если расстояние между центрами листа бумаги и тарелки
        превышает радиус тарелки*/
        Plate* element_up = dynamic_cast<Plate*>(element);
        Paper* previous_element_up = dynamic_cast<Paper*>(previous_element);
        double middle_x = (2*previous_element_up->get_x() + previous_element_up->get_wideth())/2;
        double middle_y = (2*previous_element_up->get_y() + previous_element_up->get_height())/2;
        if (distance(middle_x,element_up->get_x(),middle_y,element_up->get_y()) > element_up->get_rad())
            n++;
    }

    //Если первый элемент в стеке - тарелка и новый элемент - листок бумаги
    if (previous_element->type_return() && !element->type_return())
    {
        /*Баланс нарушается, если расстояние между центрами листа бумаги и тарелки
        превышает радиус тарелки*/
        Paper* element_up = dynamic_cast<Paper*>(element);
        Plate* previous_element_up = dynamic_cast<Plate*>(previous_element);
        double middle_x = (2*element_up->get_x() + element_up->get_wideth())/2;
        double middle_y = (2*element_up->get_y() + element_up->get_height())/2;
        if (distance(middle_x,previous_element_up->get_x(),middle_y,previous_element_up->get_y()) > previous_element_up->get_rad())
            n++;
    }

    //Если первый элемент в стеке и новый - листки бумаги
    if (!previous_element->type_return() && !element->type_return())
    {
        Paper* element_up = dynamic_cast<Paper*>(element);
        Paper* previous_element_up = dynamic_cast<Paper*>(previous_element);
        double middle_x = (2*element_up->get_x() + element_up->get_wideth())/2;
        /*Баланс нарушается, если левый нижний уголок нового листка (координата x объекта
         element) находится правее центра листа в стеке или правый нижний уголок
        находится левее центра листа в стеке*/
        if (previous_element_up->get_x() > middle_x)
            n++;
        if (middle_x > (previous_element_up->get_x() + previous_element_up->get_wideth()))
            n++;

        /*Баланс также нарушается, если нижний уголок нового листка (координата y объекта
         element) находится выше центра листа в стеке или верхний уголок
        находится ниже центра листа в стеке*/
        double middle_y = (2*element_up->get_y() + element_up->get_height())/2;
        if (previous_element_up->get_y() > middle_y)
            n++;
        if (middle_y > (previous_element_up->get_y() + previous_element_up->get_height()))
            n++;
    }

    //Если суммарная высота стека превышает сто, равновесие нарушается
    if (Stack::pile_height > 100)
        n++;

    unbal += n;
    return n;
}
//Конец проверки на баланс

//Конструктор по умолчанию
Stack::Stack()
{
    top = nullptr;
    unbal = 0;
    pile_height = 0;
    numb = 0;
}

//Конструктор копирования класса Stack
/*Значение переносится по ссылке для того, чтобы избежать копирования объекта
const указывает на то, что значение объекта не изменяется внутри метода*/
Stack::Stack(const Stack &pile)
{
    top = nullptr;
    unbal = 0;
    pile_height = 0;
    numb = 0;
    for (int i = 0; i < pile.get_numb(); i++)
        push(pile.peek(pile.get_numb()-i));
}

//Деструктор класса Stack
Stack::~Stack()
{
    //Все элемента в стеке удаляются, пока он не станет пустым
    while(!empty())
        pop();
}

//Метод доступа к элементам стека, n - номер элемента. Если n превышает число
//элементов в стеке, вернётся указатель на последний элемент
Base* Stack::peek(int n) const
{
    int num_iter = 1;
    Iterator i(*this);
    while (!i.atEnd() && num_iter < n)
    {
        i.move();
        num_iter++;
    }
    return i.get();
}

//Метод записи в файл
void Stack::write_file(QString file_name)
{
    QFile file(file_name);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    if (empty())
    {
        stream << "The stack is empty.";
        return;
    }
    Iterator i(*this);
    int n = 0;
    while (!i.atEnd())
    {
        Base* new_element = i.get();
        n++;
        stream << QString::number(n) << " element of Stack\n";
        new_element->show(&stream);
        i.move();
    }
    if (balancer())
        stream << "The stack is in balance.\n";
    else
        stream << "The stack is not in balance.\n";
    file.close();
}

//Метод чтения из файла
void Stack::file_read(QString file_name)
{
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        QString str;
        str = stream.readLine();
        if (str == "Paper")
        {
            Base *element = new Paper;
            if (element->read(&stream))
                push(element);
            else
                continue;
        }
        else if (str == "Plate")
        {
            Base *element = new Plate;
            if (element->read(&stream))
                push(element);
            else
                continue;
        }
        else
            continue;
    }
    file.close();
}

//Удаление первого элемента стека
void Stack::pop()
{
   if (!empty())
   {
       numb--;
       if (top->elem_->type_return())
       {
           Base* element = new Plate(*(dynamic_cast<Plate*>(top->elem_)));
           delete top->elem_;
           Part* x = top->p_;
           delete top;
           top = x;
           unbal -= 2*balance(element);
           dec_height(*element);
           delete element;
       }
       else
       {
           Base* element = new Paper(*(dynamic_cast<Paper*>(top->elem_)));
           delete top->elem_;
           Part* x = top->p_;
           delete top;
           top = x;
           unbal -= 2*balance(element);
           dec_height(*element);
           delete element;
       }
   }
}

//Добавление элемента в стек
void Stack::push(Base* element)
{
    if (empty())
    {
        inc_height(*element);
        Part* part_1 = new Part;
        if (element->type_return())
            part_1->elem_ = new Plate(*(dynamic_cast<Plate*>(element)));
        else
            part_1->elem_ = new Paper(*(dynamic_cast<Paper*>(element)));
        part_1->p_ = top;
        top = part_1;
        numb++;
        return;
    }
    if (check_falling(element))
    {
        inc_height(*element);
        balance(element);
        numb++;
        Part* part_1 = new Part;
        if (element->type_return())
            part_1->elem_ = new Plate(*(dynamic_cast<Plate*>(element)));
        else
            part_1->elem_ = new Paper(*(dynamic_cast<Paper*>(element)));
        part_1->p_ = top;
        top = part_1;
        return;
    }
}

//Проверка на то, является ли стек пустым: True - если является, False - если не
//является пустым
bool Stack::empty() const
{
    return top ? false:true;
}

#endif // STACK_H
