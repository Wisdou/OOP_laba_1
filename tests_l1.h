#ifndef TESTS_H
#define TESTS_H

#include <float.h>
#include <iostream> //Библиотека ввода/ вывода в C++. Потоковый ввод/ вывод.
#include <QRandomGenerator>
#include <QDateTime>
#include <QStringList>
#include "paper.h"
#include "stack.h"

namespace Random
{

double realNumber(double from = -DBL_MAX/2, double to = DBL_MAX/2) {
    return from + (to - from) * QRandomGenerator::global()->generateDouble();
}

int integer(int from = INT_MIN, int to = INT_MAX) {
    return QRandomGenerator::global()->bounded(from, to);
}

QDateTime dateTime(QDateTime from, QDateTime to) {
    return from.addSecs(static_cast<qint64>(QRandomGenerator::global()->
                                            generate64()) % from.secsTo(to));
}

const QString& itemFrom(const QStringList &list) {
    return list.at(QRandomGenerator::global()->bounded(list.length()));
}

QString ingredient() {
    static QStringList ingredients = {"Вода", "Яйцо", "Сахар", "Молоко",
                                      "Картофель", "Соль", "Кефир", "Яблоко",
                                      "Мука", "Масло", "Сосиска", "Хлопья"};
    return itemFrom(ingredients);
}

QString material() {
    static QStringList woodTypes = {"Дуб", "Вишня", "Клён", "Орех",
                                    "Палисандр", "Сосна", "Бук",
                                    "Ясень", "Берёза", "Кедр"};
    return itemFrom(woodTypes);
}

QString aminoacidName() {
    static QStringList aminoacids = {"Глицин", "Аланин", "Валин", "Изолейцин",
                                    "Лейцин", "Пролин", "Серин", "Треонин",
                                    "Цистеин", "Метионин",
                                     "Аспарагиновая кислота", "Аспарагин",
                                    "Глутаминовая кислота", "Глутамин",
                                    "Лизин", "Аргинин", "Гистидин",
                                    "Фенилаланин", "Тирозин", "Триптофан"};
    return itemFrom(aminoacids);
}

QChar aminoacidLetter() {
    static QString letters = "GAVILPSTCMDNEQKRHFYW";
    return letters.at(QRandomGenerator::global()->bounded(letters.length()));
}

QString studentFIO() {
    static QStringList names = {"Алексей", "Анатолий", "Вячеслав", "Георгий",
                                "Евгений", "Кирилл", "Матвей", "Мухаммад",
                                "Никита", "Роман", "Сергей"},
            surnames = {"Игнатьев", "Кабисов", "Кожевников", "Лернер",
                        "Лясковский", "Сафронов", "Умбрас", "Шадько",
                        "Штырлин", "Юсупов", "Якубов"},
            patronymic = {"Александрович", "Андреевич", "Даниилович",
                          "Иванович", "Ильич", "Максимович",
                          "Павлович", "Романович", "Сергеевич", "Юрьевич", ""};
    auto randomGenerator = QRandomGenerator::global();
    return surnames.at(randomGenerator->bounded(surnames.size())) + " " +
            names.at(randomGenerator->bounded(names.size())) + " " +
            patronymic.at(randomGenerator->bounded(patronymic.size()));
}
};

inline std::string stdString(const QString &qstring) {
    return qstring.toLocal8Bit().toStdString();
}

inline char stdChar(const QChar &qchar) {
    return qchar.toLatin1();
}

/*
class Paper
{
   public:
       Paper(int height = 1, int wideth = 1, int thick = 1, int x = 0, int y = 0);//конструктор по умолчанию
       Paper(const Paper &paper);
       ~Paper();//деструктор
       //Методы доступа к полям класса
       unsigned int get_height(){
           return height_;}
       void set_height(int height);
       unsigned int get_wideth(){ return wideth_;}
       void set_wideth(int wideth);
       unsigned int get_thick(){ return thick_;}
       void set_thick(int thick);
       float get_x(){ return x_;}
       void set_x(float x);
       float get_y(){ return y_;}
       void set_y(float y);
   private://тип доступа по умолчанию
       unsigned int height_, wideth_, thick_;//свойства класса: высота, ширина и толщина соответственно
       float x_,y_;//координаты по двум осям
};
*/

#define MIN_PARAM1_VALUE 0
#define MAX_PARAM1_VALUE +210
#define MIN_PARAM2_VALUE -10000.
#define MAX_PARAM2_VALUE +10000.

namespace Test
{
    void assertComparison(const Stack &pile)
    {
        Stack new_pile(pile);
        Iterator i(pile);
        Iterator k(new_pile);
        while(!i.atEnd() && !k.atEnd())
        {
            Base* first = (i.get());
            Base* second = (k.get());
            assert(first->get_x() == second->get_x());
            assert(first->get_thick() == second->get_thick());
            assert(first->get_y() == second->get_y());
            i.move();
            k.move();
        }
    }

    void assertAddDelete(Stack pile)
    {
        Base* sheet(pile.peek(1));
        int wideth_1 = (pile.peek(1))->get_x();
        pile.push(sheet);
        pile.pop();
        int wideth_2 = (pile.peek(1))->get_x();
        assert(wideth_1 == wideth_2);
    }

    void assertValidity(const Paper &object)
    {
        assert(object.get_wideth() > MIN_PARAM1_VALUE);
        assert(object.get_wideth() < MAX_PARAM1_VALUE);
        assert(object.get_x() > MIN_PARAM2_VALUE);
        assert(object.get_x() < MAX_PARAM2_VALUE);
    }

    void assertEquality(Paper &first, Paper &second)
    {
        assert(first.get_x() == second.get_x());
        assert(first.get_y() == second.get_y());

        assert(first.get_thick() == second.get_thick());
        assert(first.get_wideth() == second.get_wideth());
    }

    void assertStability(Paper &object)
    {
        int value1 = Random::integer(MIN_PARAM1_VALUE+1, MAX_PARAM1_VALUE-1);
        object.set_wideth(value1);
        assert(object.get_wideth() == value1);
        int error1 = Random::integer(MAX_PARAM1_VALUE);
        object.set_wideth(error1);
        assert(object.get_wideth() != error1);
        assert(object.get_wideth() == value1);

        double value2 = Random::realNumber(MIN_PARAM2_VALUE+1, MAX_PARAM2_VALUE-1);
        object.set_x(value2);
        assert(object.get_x() == value2);
        double error2 = Random::realNumber(MAX_PARAM2_VALUE);
        assert(object.get_x() != error2);
        assert(object.get_x() == value2);
    }

    void write_console(Stack pile)
    {
        int n = 0;
        Iterator i(pile);
        while(!i.atEnd())
        {
            n++;
            std::cout.precision(4);
            std::cout << "Element " << n << std::endl;
            Base* new_sheet = i.get();
            QTextStream stream(stdout);
            new_sheet->show(&stream);
            std::cout << std::endl;
            i.move();
        }
    }

    void checker(char* str1, char* str2, char* str3, Stack pile)
    {
        std::cout << "Before reading the file: " << std::endl;
        write_console(pile);
        pile.write_file(str2);
        pile.file_read(str1);
        std::cout << "After reading the file: " << std::endl;
        write_console(pile);
        pile.write_file(str3);
    }

    void run()
    {
        Paper defaultObject;
        Stack pile;
        char read_file[80] = "C:\\Users\\User\\Desktop\\Qtcodes\\Project 1\\Laba3_Qt\\Laba3\\balance_s.txt";
        char write_file1[80] = "C:\\Users\\User\\Desktop\\Qtcodes\\Project 1\\Laba3_Qt\\output1.txt";
        char write_file2[80] = "C:\\Users\\User\\Desktop\\Qtcodes\\Project 1\\Laba3_Qt\\output2.txt";
        assertValidity(defaultObject);
        for (int i = 0; i < 10; i++)
        {
            Paper randomObject(Random::integer(100, 290),
                               Random::integer(150, 200),
                               Random::realNumber(1, 2),
                               Random::realNumber(15,20),
                               Random::realNumber(1, 5));
            Base* elem_1 = &randomObject;
            pile.push(elem_1);
            Plate randomObject_1(Random::integer(150, 200),
                               Random::realNumber(1, 5),
                               Random::realNumber(15,20),
                               Random::realNumber(1, 5));
            Base* elem_2 = &randomObject_1;
            pile.push(elem_2);
        }
        std::cout << "\nTests for first task are completed!\n";
        write_console(pile);
        checker(read_file,write_file1,write_file2,pile);
        std::cout <<"\n\n\nTests for second task are completed!" << std::endl;
    }
};

#endif // TESTS_H
