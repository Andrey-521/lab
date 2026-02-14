#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include <limits>
#include "Mushroom.h"

using namespace std;

using std::cin;
using std::cout;
using std::string;

// простая сортировка пузырьком с компаратором, принимает ссылку на вектор
void bubbleSort(vector<Mushroom> &arr, const function<bool(const Mushroom&, const Mushroom&)> &cmp) {
    size_t n = arr.size();
    for (size_t i = 0; i < n; ++i) {
        bool swapped = false;
        for (size_t j = 1; j < n - i; ++j) {
            // если cmp(arr[j], arr[j-1]) == true, то меняем местами
            if (cmp(arr[j], arr[j-1])) {
                swap(arr[j], arr[j-1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void printAll(const vector<Mushroom> &v) {
    if (v.empty()) {
        cout << "The list is empty.\n";
        return;
    }
    for (size_t i = 0; i < v.size(); ++i) {
        cout << i + 1 << ") ";
        v[i].print(cout);
    }
}

bool loadFromFile(const string &filename, vector<Mushroom> &out) {
    ifstream in(filename);
    if (!in) {
        cout << "Failed to open file: " << filename << "\n";
        return false;
    }
    out.clear();
    Mushroom m;
    while (m.readFromStream(in)) {
        out.push_back(m);
    }
        cout << "Records loaded: " << out.size() << "\n";
    return true;
}

bool saveToFile(const string &filename, const vector<Mushroom> &v) {
    ofstream out(filename);
    if (!out) {
        cout << "Failed to open file for writing: " << filename << "\n";
        return false;
    }
    for (const auto &m : v) {
        out << m.toLine() << '\n';
    }
    cout << "Data saved in " << filename << "\n";
    return true;
}

int main() {
    vector<Mushroom> mushrooms;
    string filename = "mushrooms.txt";

    // Попробуем загрузить сразу при старте (если файл есть)
    loadFromFile(filename, mushrooms);

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Пprovide a list of mushrooms\n";
        cout << "2. Load from file (specify file name)\n";
        cout << "3. Sort by weight (descending)\n";
        cout << "4. Sort by name (ascending)\n";
        cout << "5. Save to file (specify file name)\n";
        cout << "0. Exit\n";
        cout << "Select an option: ";

        int choice;
        if (!(cin >> choice)) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) break;
        else if (choice == 1) {
            printAll(mushrooms);
        }
        else if (choice == 2) {
            cout << "Enter the file name to upload (Enter For "" << filename << ""): ";
            string f;
            getline(cin, f);
            if (!f.empty()) filename = f;
            loadFromFile(filename, mushrooms);
        }
        else if (choice == 3) {
            // по весу по убыванию
            bubbleSort(mushrooms, [](const Mushroom &a, const Mushroom &b) {
                return a.weight > b.weight;
            });
            cout << "Sorted by weight (descending).\n";
        }
        else if (choice == 4) {
            // по названию по возрастанию
            bubbleSort(mushrooms, [](const Mushroom &a, const Mushroom &b) {
                return a.name < b.name;
            });
            cout << "Sorted by name (ascending).\n";
        }
        else if (choice == 5) {
            cout << "Enter a file name to save (Enter для "" << filename << ""): ";
            string f;
            getline(cin, f);
            if (!f.empty()) filename = f;
            saveToFile(filename, mushrooms);
        }
        else {
            cout << "Wrong choice.\n";
        }
    }

    cout << "Exit.\n";
    return 0;
}
