#include <iostream>
#include <vector>
#include <string>
#include "classes.h"
#include "functions.h"
using namespace std;


//creating an owner
Owner::Owner(string name, string birth_date, string address, int phone_number) {
    this->name = name;
    this->birth_date = birth_date;
    this->address = address;
    this->phone_number = phone_number;
}

//getters for owners

string Owner::get_name() {
    return this->name;
}

string Owner::get_birth_date() {
    return this->birth_date;
}

string Owner::get_address() {
    return this->address;
}

int Owner::get_phone_number() {
    return this->phone_number;
}

vector<Animal*> Owner::get_pets() {
    return this->pets;
}

int Owner::get_num_of_species() {
    vector <bool> spcs = { 0, 0, 0, 0 };
    for (int i = 0; i < pets.size(); i++) {
        if (pets[i]->get_species() == 0) {
            spcs[0] = 1;
        }
        else if (pets[i]->get_species() == 1) {
            spcs[1] = 1;
        }
        else if (pets[i]->get_species() == 2) {
            spcs[2] = 1;
        }
        else if (pets[i]->get_species() == 3) {
            spcs[3] = 1;
        }
    }
    int num = spcs[0] + spcs[1] + spcs[2] + spcs[3];
    return num;
}

//adding a pet
void Owner::add_pet(string species, string name, int age) {
    if (species == "кот") {
        this->pets.push_back(new Cat(name, age));
    }
    else if (species == "собака") {
        this->pets.push_back(new Dog(name, age));
    }
    else if (species == "попугай") {
        this->pets.push_back(new Parrot(name, age));
    }
    else if (species == "хомяк") {
        this->pets.push_back(new Hamster(name, age));
    }
}

int Animal::static_id = 0;

//creating a pet
Animal::Animal(string pet_name, int age) {
    this->pet_name = pet_name;
    this->age = age;
}

//setters for species
Cat::Cat(string name, int age) {
    this->pet_name = name;
    this->age = age;
}

Dog::Dog(string name, int age) {
    this->pet_name = name;
    this->age = age;
}

Parrot::Parrot(string name, int age) {
    this->pet_name = name;
    this->age = age;
}

Hamster::Hamster(string name, int age) {
    this->pet_name = name;
    this->age = age;
}

//getters for animals
int Animal::get_id() {
    return this->pet_id;
}

string Animal::get_pet_name() {
    return this->pet_name;
}

int Animal::get_age() {
    return this->age;
}

void Animal::get_features() {
    ability_1();
    ability_2();
    ability_3();
}

