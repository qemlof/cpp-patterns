#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include "classes.h"
#include "functions.h"
using namespace std;

void input(string task) {
    vector <string> possible = { "СТОП", "1", "2", "3", "4", "5", "6", "7", "8"};
    string error = " является некорректным значением запроса.";
    bool is_possible = false;
    for (int i = 0; i < 9; i++) {
        if (task == possible[i]) {
            is_possible = true;
        }
    }
    if (!is_possible) {
        cout << task << error;
    }
}

int enumerate_species(string str) {
    if (str == "кот") {
        return 0;
    }
    if (str == "собака") {
        return 1;
    }
    if (str == "попугай") {
        return 2;
    }
    if (str == "хомяк") {
        return 3;
    }
}

string denumerate_species(int number) {
    vector <string> species_vec = { "кот", "собака", "попугай", "хомяк" };
    return species_vec[number];
}

vector<string> set_info(const string& line, char symb) {
    vector<string> form;
    string field;
    istringstream strstream(line);
    while (getline(strstream, field, symb)) {
        form.push_back(field);
    }
    return form;
}

void set_pet_to_owner(string line, vector<Owner>& owners) {
    vector<string> pet_info = set_info(line, ',');
    Owner owner(pet_info[0], pet_info[1], pet_info[2], stoi(pet_info[3]));
    int index = -1;

    if (owners.size() > 0) {
        for (int f = 0; f < owners.size(); f++) {
            if (owner.get_name() == owners[f].get_name()) {
                index = f;
                owners[index].add_pet(pet_info[4], pet_info[5], stoi(pet_info[6]));
            }
        }
    }

    if (index < 0) {
        owners.push_back(owner);
        owners[owners.size() - 1].add_pet(pet_info[4], pet_info[5], stoi(pet_info[6]));
    }


}

//1. Посчитать количество различных видов животных у каждого владельца.
void task_1(vector<Owner>& owners) {
    for (int i = 0; i < owners.size(); i++) {
        cout << "У владельца по имени " << owners[i].get_name() << " " << owners[i].get_num_of_species() << " различных видов животных." << endl;
    }
};


//2. Для конкретного вида животного, вводимого Вами, вывести всех 
//его владельцев и клички. Владельцы и клички не будут повторяться.
void task_2(vector<Owner>& owners, string info) {
    //    info = "кот";
    set<string> names;
    set<string> species_owners;
    for (int i = 0; i < owners.size(); i++) {
        for (int j = 0; j < owners[i].get_pets().size(); j++) {
            if (owners[i].get_pets()[j]->get_species() == enumerate_species(info)) {
                names.insert(owners[i].get_pets()[j]->get_pet_name());
                species_owners.insert(owners[i].get_name());
            }
        }
    }
    set<string>::iterator it;
    cout << "Клички всех животных этого вида: ";
    for (it = names.begin(); it != names.end(); it++) {
        cout << (*it) << " ";
    }
    cout << endl;
    cout << "Имена всех владельцев у которых есть " << info << ": ";
    for (it = species_owners.begin(); it != species_owners.end(); it++) {
        cout << (*it) << "   ";
    }
    cout << endl;
}


// 3. Определить, сколько видов животных носит введённую Вами кличку.
void task_3(vector<Owner>& owners, string info) {
    //    info = "Джуля";
    vector <bool> spcs = { 0, 0, 0, 0 };
    for (int i = 0; i < owners.size(); i++) {
        for (int j = 0; j < owners[i].get_pets().size(); j++) {
            if (owners[i].get_pets()[j]->get_pet_name() == info) {
                spcs[owners[i].get_pets()[j]->get_species()] = 1;
            }
        }
    }
    int num = spcs[0] + spcs[1] + spcs[2] + spcs[3];
    cout << num << " видов животных носит введённую Вами кличку." << endl;
};


//4. Вывести информацию о возрасте самого старого и самого молодого 
// животного каждого вида
void task_4(vector<Owner>& owners) {
    vector <vector<int>> ages = { {0, 1000},{0, 1000},{0, 1000},{0, 1000} };
    int age = 0;
    for (int i = 0; i < owners.size(); i++) {
        for (int j = 0; j < owners[i].get_pets().size(); j++) {
            age = owners[i].get_pets()[j]->get_age();
            if (age > ages[owners[i].get_pets()[j]->get_species()][0]) {
                ages[owners[i].get_pets()[j]->get_species()][0] = age;
            }
            if (age < ages[owners[i].get_pets()[j]->get_species()][1]) {
                ages[owners[i].get_pets()[j]->get_species()][1] = age;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        cout << "Возраст самого старого животного вида " << denumerate_species(i) << " равен " << ages[i][0] << " лет." << endl;
        cout << "Возраст самого молодого животного вида " << denumerate_species(i) << " равен " << ages[i][1] << " лет." << endl;
    }
};

void task_5(vector<Owner>& owners, string info) {
    //    info = "Иванов Иван Иванович";
    for (int i = 0; i < owners.size(); i++) {
        if (owners[i].get_name() == info) {
            for (int j = 0; j < owners[i].get_pets().size(); j++) {
                cout << "Информация о питомце по имени " << owners[i].get_pets()[j]->get_pet_name() << ":" << endl;
                owners[i].get_pets()[j]->get_features();
                cout << endl;
            }
            break;
        }
    }
};


void task_6(vector<Owner>& owners) {
    Cat cat("новый котик", 8);
    cout << "Данные о последнем животном - id: " << cat.get_id() << ", кличка: " << cat.get_pet_name() << ", возраст: " << cat.get_age() << endl;
    Cat new_cat(move(cat));
    cout << "Данные о новом животном - id: " << new_cat.get_id() << ", кличка: " << new_cat.get_pet_name() << ", возраст: " << new_cat.get_age() << endl;
    cout << "Данные о прошлом последнем животном - id: " << cat.get_id() << ", кличка: " << cat.get_pet_name() << ", возраст: " << cat.get_age() << endl;
    Cat cat2("ещё новый котёнок", 2);
    cout << "Данные о последнем животном - id: " << cat2.get_id() << ", кличка: " << cat2.get_pet_name() << ", возраст: " << cat2.get_age() << endl;
    Cat new_cat2 = move(cat2);
    cout << "Данные о новом животном - id: " << new_cat2.get_id() << ", кличка: " << new_cat2.get_pet_name() << ", возраст: " << new_cat2.get_age() << endl;
    cout << "Данные о прошлом животном - id: " << cat2.get_id() << ", кличка: " << cat2.get_pet_name() << ", возраст: " << cat2.get_age() << endl;
};


void task_7() {
    AnimalFactory* catFactory = new CatFactory();
    AnimalFactory* dogFactory = new DogFactory();
    AnimalFactory* parrotFactory = new ParrotFactory();

    Animal* cat = catFactory->CreateAnimal();
    Animal* dog = dogFactory->CreateAnimal();
    Animal* parrot = parrotFactory->CreateAnimal();
    cout << "Имя кошки: " << cat->get_pet_name() << endl;
    cout << "Возраст собаки: " << dog->get_age() << endl;
    cout << "Id попугая: " << parrot->get_id() << endl;
    delete cat;
    delete dog;
    delete parrot;
    delete catFactory;
    delete dogFactory;
    delete parrotFactory;
}

CompositePetClinic* createPetClinic(int NumOfCats, int NumOfDogs, int NumOfParrots, int NumOfHamsters) {
    CompositePetClinic* NewClinic = new CompositePetClinic;
    for (int i = 0; i < NumOfCats; i++) {
        NewClinic->AddPetClinic(new Cat);
    }
    for (int i = 0; i < NumOfDogs; i++) {
        NewClinic->AddPetClinic(new Dog);
    }
    for (int i = 0; i < NumOfParrots; i++) {
        NewClinic->AddPetClinic(new Parrot);
    }
    for (int i = 0; i < NumOfHamsters; i++) {
        NewClinic->AddPetClinic(new Hamster);
    }
    return NewClinic;
}

void task_8() {
    CompositePetClinic* ClinicUnion = new CompositePetClinic;
    int NumOfClinics = 0;
    int NumOfCats = 0;
    int NumOfDogs = 0;
    int NumOfParrots = 0;
    int NumOfHamsters = 0;
    cout << "В нашем городе появится новая сеть ветеринарных клиник. Введите количество новых клиник в этой сети: ";
    cin >> NumOfClinics;
    cout << "Стоимость недели содержания одного кота составляет " << Cat().GetUpkeep() << " рублей, одной собаки " << Dog().GetUpkeep() << " рублей, одного попугая " << Parrot().GetUpkeep() << " рублей, одного хомяка " << Hamster().GetUpkeep() << " рублей." << endl;
    cout << "Введите количество котов в одной новой клинике: ";
    cin >> NumOfCats;
    cout << "Введите количество собак в одной новой клинике: ";
    cin >> NumOfDogs;
    cout << "Введите количество попугаев в одной новой клинике: ";
    cin >> NumOfParrots;
    cout << "Введите количество хомяков в одной новой клинике: ";
    cin >> NumOfHamsters;
    for (int i = 0; i < NumOfClinics; i++) {
        ClinicUnion->AddPetClinic(createPetClinic(NumOfCats, NumOfDogs, NumOfParrots, NumOfHamsters));
    }

    cout << "Стоимость содержания новой сети ветеринарных клиник составляет " << ClinicUnion->GetUpkeep() << " рублей в неделю." << endl;
    delete ClinicUnion;
