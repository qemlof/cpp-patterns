#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include "functions.h"
#include "classes.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string s;                   //lines in input.txt
    string n = "";      //number of the task typed by user
    string info = "";      //additional information needed when doing a task
    vector<Owner> owners;
    ifstream in("input.txt");

    if (!in) {
        cout << "Ошибка вводного файла.";
        return 0;
    }

    while (getline(in, s)) {
        stringstream ss(s);
        set_pet_to_owner(s, owners);
    }

    in.close();

    cout << "Для заданного Вами файла возможны следующие запросы:" << endl;
    cout << "1. Посчитать количество различных видов животных у каждого владельца." << endl;
    cout << "2. Для конкретного вида животного, вводимого Вами, вывести всех его владельцев и клички. Владельцы и клички не будут повторяться." << endl;
    cout << "3. Определить, сколько видов животных носит введённую Вами кличку." << endl;
    cout << "4. Вывести информацию о возрасте самого старого и самого молодого животного каждого вида." << endl;
    cout << "5. Вывести информацию о навыках всех животных введённого вами владельца." << endl;
    cout << "6. Заменить данные о последнем животном в базе новыми." << endl;
    cout << "7. Fabric pattern. " << endl;
    cout << "8. Composite pattern. " << endl;
    cout << "Введите номер запроса, который Вас интересует (от 1 до 8). Когда Вы захотите завершить выполнение программы, введите \"СТОП\"." << endl;
    while (n != "СТОП") {
        cin >> n;
        input(n);
        if (n == "1") {
            task_1(owners);
        }
        else if (n == "4") {
            task_4(owners);
        }
        else if (n == "6") {
            task_6(owners);
        }
        else if (n == "7") {
            task_7();
        }
        else if (n == "8") {
            task_8();
        }
        else {
            cout << "Введите дополнительные данные для уточнения запроса." << endl;
            cin >> info;
        }
        if (n == "2") {
            task_2(owners, info);
        }
        if (n == "3") {
            task_3(owners, info);
        }
        if (n == "5") {
            task_5(owners, info);
        }
    }

    for (int i = 0; i < owners.size(); i++) {
        owners[i].get_pets().clear();
    }
    owners.clear();
    return 0;
}
