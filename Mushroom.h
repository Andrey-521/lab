#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <string>
#include <iostream>

using namespace std;

struct Mushroom {
    string name;       // название
    bool edible;            // съедобность (true = съедобный)
    double weight;          // вес (граммы)
    double capDiameter;     // диаметр шляпки (cm)
    string habitat;    // место обитания

    // Конструкторы
    Mushroom();
    Mushroom(const string &name, bool edible, double weight, double capDiameter, const string &habitat);

    // ввод/вывод
    bool readFromStream(istream &in);
    void print(ostream &out) const;
    string toLine() const;
};

#endif // MUSHROOM_H