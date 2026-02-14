#include "Mushroom.h"
#include <sstream>

using namespace std;

// Конструкторы
Mushroom::Mushroom()
    : name(""), edible(false), weight(0.0), capDiameter(0.0), habitat("") {}

Mushroom::Mushroom(const string &name, bool edible, double weight, double capDiameter, const string &habitat)
    : name(name), edible(edible), weight(weight), capDiameter(capDiameter), habitat(habitat) {}

// Ввод из строки формата: name;edible;weight;capDiameter;habitat
bool Mushroom::readFromStream(istream &in) {
    string line;
    if (!getline(in, line)) return false; // EOF
    if (line.empty()) return false;

    istringstream ss(line);
    string token;

    // name
    if (!getline(ss, token, ';')) return false;
    name = token;

    // edible: ожидаем "yes"/"no" или "1"/"0"
    if (!getline(ss, token, ';')) return false;
    if (token == "yes" || token == "1" || token == "true" || token == "Yes") edible = true;
    else edible = false;

    // weight
    if (!getline(ss, token, ';')) return false;
    try { weight = stod(token); } catch (...) { weight = 0.0; }

    // capDiameter
    if (!getline(ss, token, ';')) return false;
    try { capDiameter = stod(token); } catch (...) { capDiameter = 0.0; }

    // habitat (остаток строки)
    if (!getline(ss, token)) token = "";
    habitat = token;

    return true;
}

void Mushroom::print(std::ostream &out) const {
    out << "Name: " << name
        << ", edible: " << (edible ? "Yes" : "No")
        << ", Weight: " << weight << " Grams"
        << ", Cap diameter: " << capDiameter << "cm"
        << ", Place: " << habitat << '\n';
}

std::string Mushroom::toLine() const {
    std::ostringstream ss;
    ss << name << ';' << (edible ? "yes" : "no") << ';' << weight << ';' << capDiameter << ';' << habitat;
    return ss.str();
}
