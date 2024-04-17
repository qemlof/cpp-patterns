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
    vector <string> possible = { "����", "1", "2", "3", "4", "5", "6", "7", "8"};
    string error = " �������� ������������ ��������� �������.";
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
    if (str == "���") {
        return 0;
    }
    if (str == "������") {
        return 1;
    }
    if (str == "�������") {
        return 2;
    }
    if (str == "�����") {
        return 3;
    }
}

string denumerate_species(int number) {
    vector <string> species_vec = { "���", "������", "�������", "�����" };
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

//1. ��������� ���������� ��������� ����� �������� � ������� ���������.
void task_1(vector<Owner>& owners) {
    for (int i = 0; i < owners.size(); i++) {
        cout << "� ��������� �� ����� " << owners[i].get_name() << " " << owners[i].get_num_of_species() << " ��������� ����� ��������." << endl;
    }
};


//2. ��� ����������� ���� ���������, ��������� ����, ������� ���� 
//��� ���������� � ������. ��������� � ������ �� ����� �����������.
void task_2(vector<Owner>& owners, string info) {
    //    info = "���";
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
    cout << "������ ���� �������� ����� ����: ";
    for (it = names.begin(); it != names.end(); it++) {
        cout << (*it) << " ";
    }
    cout << endl;
    cout << "����� ���� ���������� � ������� ���� " << info << ": ";
    for (it = species_owners.begin(); it != species_owners.end(); it++) {
        cout << (*it) << "   ";
    }
    cout << endl;
}


// 3. ����������, ������� ����� �������� ����� �������� ���� ������.
void task_3(vector<Owner>& owners, string info) {
    //    info = "�����";
    vector <bool> spcs = { 0, 0, 0, 0 };
    for (int i = 0; i < owners.size(); i++) {
        for (int j = 0; j < owners[i].get_pets().size(); j++) {
            if (owners[i].get_pets()[j]->get_pet_name() == info) {
                spcs[owners[i].get_pets()[j]->get_species()] = 1;
            }
        }
    }
    int num = spcs[0] + spcs[1] + spcs[2] + spcs[3];
    cout << num << " ����� �������� ����� �������� ���� ������." << endl;
};


//4. ������� ���������� � �������� ������ ������� � ������ �������� 
// ��������� ������� ����
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
        cout << "������� ������ ������� ��������� ���� " << denumerate_species(i) << " ����� " << ages[i][0] << " ���." << endl;
        cout << "������� ������ �������� ��������� ���� " << denumerate_species(i) << " ����� " << ages[i][1] << " ���." << endl;
    }
};

void task_5(vector<Owner>& owners, string info) {
    //    info = "������ ���� ��������";
    for (int i = 0; i < owners.size(); i++) {
        if (owners[i].get_name() == info) {
            for (int j = 0; j < owners[i].get_pets().size(); j++) {
                cout << "���������� � ������� �� ����� " << owners[i].get_pets()[j]->get_pet_name() << ":" << endl;
                owners[i].get_pets()[j]->get_features();
                cout << endl;
            }
            break;
        }
    }
};


void task_6(vector<Owner>& owners) {
    Cat cat("����� �����", 8);
    cout << "������ � ��������� �������� - id: " << cat.get_id() << ", ������: " << cat.get_pet_name() << ", �������: " << cat.get_age() << endl;
    Cat new_cat(move(cat));
    cout << "������ � ����� �������� - id: " << new_cat.get_id() << ", ������: " << new_cat.get_pet_name() << ", �������: " << new_cat.get_age() << endl;
    cout << "������ � ������� ��������� �������� - id: " << cat.get_id() << ", ������: " << cat.get_pet_name() << ", �������: " << cat.get_age() << endl;
    Cat cat2("��� ����� ������", 2);
    cout << "������ � ��������� �������� - id: " << cat2.get_id() << ", ������: " << cat2.get_pet_name() << ", �������: " << cat2.get_age() << endl;
    Cat new_cat2 = move(cat2);
    cout << "������ � ����� �������� - id: " << new_cat2.get_id() << ", ������: " << new_cat2.get_pet_name() << ", �������: " << new_cat2.get_age() << endl;
    cout << "������ � ������� �������� - id: " << cat2.get_id() << ", ������: " << cat2.get_pet_name() << ", �������: " << cat2.get_age() << endl;
};


void task_7() {
    AnimalFactory* catFactory = new CatFactory();
    AnimalFactory* dogFactory = new DogFactory();
    AnimalFactory* parrotFactory = new ParrotFactory();

    Animal* cat = catFactory->CreateAnimal();
    Animal* dog = dogFactory->CreateAnimal();
    Animal* parrot = parrotFactory->CreateAnimal();
    cout << "��� �����: " << cat->get_pet_name() << endl;
    cout << "������� ������: " << dog->get_age() << endl;
    cout << "Id �������: " << parrot->get_id() << endl;
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
    cout << "� ����� ������ �������� ����� ���� ������������ ������. ������� ���������� ����� ������ � ���� ����: ";
    cin >> NumOfClinics;
    cout << "��������� ������ ���������� ������ ���� ���������� " << Cat().GetUpkeep() << " ������, ����� ������ " << Dog().GetUpkeep() << " ������, ������ ������� " << Parrot().GetUpkeep() << " ������, ������ ������ " << Hamster().GetUpkeep() << " ������." << endl;
    cout << "������� ���������� ����� � ����� ����� �������: ";
    cin >> NumOfCats;
    cout << "������� ���������� ����� � ����� ����� �������: ";
    cin >> NumOfDogs;
    cout << "������� ���������� �������� � ����� ����� �������: ";
    cin >> NumOfParrots;
    cout << "������� ���������� ������� � ����� ����� �������: ";
    cin >> NumOfHamsters;
    for (int i = 0; i < NumOfClinics; i++) {
        ClinicUnion->AddPetClinic(createPetClinic(NumOfCats, NumOfDogs, NumOfParrots, NumOfHamsters));
    }

    cout << "��������� ���������� ����� ���� ������������ ������ ���������� " << ClinicUnion->GetUpkeep() << " ������ � ������." << endl;
    delete ClinicUnion;
}