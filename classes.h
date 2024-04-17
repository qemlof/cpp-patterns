#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
using namespace std;

class Animal {
protected:
    int pet_id;
    string pet_name;
    int age;
    const string ab1 = "Первым, чему научился этот питомец, было ";
    const string ab2 = "Вторым, чему научился этот питомец, было  ";
    const string ab3 = "Третьим, чему научился этот питомец, было ";
public:
    Animal() {
        pet_id = ++static_id;
        pet_name = "";
        age = 0;
    };
    Animal(string pet_name, int age);

    Animal(const Animal& other_pet) {
        pet_name = other_pet.pet_name;
        age = other_pet.age;
    }
    Animal& operator=(const Animal& other_pet) {
        if (this == &other_pet) return *this;
        pet_name = other_pet.pet_name;
        age = other_pet.age;
        return *this;
    }
    ~Animal() {};

    Animal(Animal&& other_pet) noexcept {
        pet_name = move(other_pet.pet_name);
        age = move(other_pet.age);
    }
    Animal& operator=(Animal&& other_pet) noexcept {
        if (this == &other_pet) return *this;
        pet_name = move(other_pet.pet_name);
        age = move(other_pet.age);
        return *this;
    }

    virtual void ability_1() = 0;
    virtual void ability_2() = 0;
    virtual void ability_3() = 0;
    virtual int get_species() = 0;
    static int static_id;
    int get_id();
    void get_features();
    string get_pet_name();
    int get_age();
};


class Owner {
protected:
    string name;
    string birth_date;
    string address;
    int phone_number;
    vector<Animal*> pets;
public:
    Owner() {
        this->name = "";
        this->birth_date = "";
        this->address = "";
        this->phone_number = 0;
    };
    Owner(string name, string birth_date, string address, int phone_number);

    Owner(const Owner& other_owner) {
        name = other_owner.name;
        birth_date = other_owner.birth_date;
        address = other_owner.address;
        phone_number = other_owner.phone_number;
        pets = other_owner.pets;
    }
    Owner& operator=(const Owner& other_owner) {
        if (this == &other_owner) return *this;
        name = other_owner.name;
        birth_date = other_owner.birth_date;
        address = other_owner.address;
        phone_number = other_owner.phone_number;
        pets = other_owner.pets;
        return *this;
    }
    ~Owner() {};

    Owner(Owner&& other_owner) noexcept {
        name = move(other_owner.name);
        birth_date = move(other_owner.birth_date);
        address = move(other_owner.address);
        phone_number = move(other_owner.phone_number);
        pets = move(other_owner.pets);
    }
    Owner& operator=(Owner&& other_owner) noexcept {
        if (this == &other_owner) return *this;
        name = move(other_owner.name);
        birth_date = move(other_owner.birth_date);
        address = move(other_owner.address);
        phone_number = move(other_owner.phone_number);
        pets = move(other_owner.pets);
        return *this;
    }

    string get_name();
    string get_birth_date();
    string get_address();
    int get_phone_number();
    vector<Animal*> get_pets();
    int get_num_of_species();
    void add_pet(string species, string name, int age);
};


class PetClinic {
public:
    virtual int GetUpkeep() = 0;
    virtual void AddPetClinic(PetClinic* clinic) {
        assert(false);
    }
    virtual ~PetClinic() {};
};

class CompositePetClinic : public PetClinic {
    vector<PetClinic*> c;
public:
    int GetUpkeep() {
        int total = 0;
        for (int i = 0; i < c.size(); i++) {
            total += c[i]->GetUpkeep();
        }
        return total;
    }
    void AddPetClinic(PetClinic* clinic) {
        c.push_back(clinic);
    }
    ~CompositePetClinic() {
        for (int i = 0; i < c.size(); i++) {
            delete c[i];
        }
    }
};


class Cat : public Animal, public PetClinic {
public:
    Cat() {};
    Cat(string name, int age);

    Cat(const Cat& other) {
        pet_name = other.pet_name;
        age = other.age;
    }
    Cat& operator=(const Cat& other) {
        if (this == &other) return *this;
        pet_name = other.pet_name;
        age = other.age;
        return *this;
    }
    ~Cat() {};

    Cat(Cat&& other) noexcept {
        pet_name = move(other.pet_name);
        age = move(other.age);
    }
    Cat& operator=(Cat&& other) noexcept {
        if (this == &other) return *this;
        pet_name = move(other.pet_name);
        age = move(other.age);
        return *this;
    }


    int get_species() override {
        return 0;
    }
    void ability_1() override {
        cout << this->ab1 << "мяукать." << endl;
    }
    void ability_2() override {
        cout << this->ab2 << "лежать на коленях хозяина." << endl;
    }
    void ability_3() override {
        cout << this->ab3 << "самостоятельно гулять по улице." << endl;
    }

    virtual int GetUpkeep() {
        return 20;
    }
};


class Dog : public Animal, public PetClinic {
public:
    Dog() {};
    Dog(string name, int age);

    Dog(const Dog& other) {
        pet_name = other.pet_name;
        age = other.age;
    }
    Dog& operator=(const Dog& other) {
        if (this == &other) return *this;
        pet_name = other.pet_name;
        age = other.age;
        return *this;
    }
    ~Dog() {};

    Dog(Dog&& other) noexcept {
        pet_name = move(other.pet_name);
        age = move(other.age);
    }
    Dog& operator=(Dog&& other) noexcept {
        if (this == &other) return *this;
        pet_name = move(other.pet_name);
        age = move(other.age);
        return *this;
    }

    int get_species() override {
        return 1;
    }
    void ability_1() override {
        cout << this->ab1 << "лаять на незнакомцев." << endl;
    }
    void ability_2() override {
        cout << this->ab2 << "команда \"Сидеть\"." << endl;
    }
    void ability_3() override {
        cout << this->ab3 << "команда \"Дай лапу\"." << endl;
    }

    virtual int GetUpkeep() {
        return 30;
    }
};


class Parrot : public Animal, public PetClinic {
public:
    Parrot() {};
    Parrot(string name, int age);

    Parrot(const Parrot& other) {
        pet_name = other.pet_name;
        age = other.age;
    }
    Parrot& operator=(const Parrot& other) {
        if (this == &other) return *this;
        pet_name = other.pet_name;
        age = other.age;
        return *this;
    }
    ~Parrot() {};

    Parrot(Parrot&& other) noexcept {
        pet_name = move(other.pet_name);
        age = move(other.age);
    }
    Parrot& operator=(Parrot&& other) noexcept {
        if (this == &other) return *this;
        pet_name = move(other.pet_name);
        age = move(other.age);
        return *this;
    }


    int get_species() override {
        return 2;
    }
    void ability_1() override {
        cout << this->ab1 << "чистить перья." << endl;
    }
    void ability_2() override {
        cout << this->ab2 << "чирикать." << endl;
    }
    void ability_3() override {
        cout << this->ab3 << "повторять слова за хозяином." << endl;
    }

    virtual int GetUpkeep() {
        return 7;
    }
};


class Hamster : public Animal, public PetClinic {
public:
    Hamster() {};
    Hamster(string name, int age);

    Hamster(const Hamster& other) {
        pet_name = other.pet_name;
        age = other.age;
    }
    Hamster& operator=(const Hamster& other) {
        if (this == &other) return *this;
        pet_name = other.pet_name;
        age = other.age;
        return *this;
    }
    ~Hamster() {};

    Hamster(Hamster&& other) noexcept {
        pet_name = move(other.pet_name);
        age = move(other.age);
    }
    Hamster& operator=(Hamster&& other) noexcept {
        if (this == &other) return *this;
        pet_name = move(other.pet_name);
        age = move(other.age);
        return *this;
    }

    int get_species() override {
        return 3;
    }
    void ability_1() override {
        cout << this->ab1 << "шуршать опилками." << endl;
    }
    void ability_2() override {
        cout << this->ab2 << "прятать еду за щёки." << endl;
    }
    void ability_3() override {
        cout << this->ab3 << "бегать в колесе." << endl;
    }

    virtual int GetUpkeep() {
        return 10;
    }
};

class AnimalFactory {
public:
    virtual Animal* CreateAnimal() = 0;
};


class CatFactory : public AnimalFactory {
public:
    Animal* CreateAnimal() override {
        return new Cat();
    }
};


class DogFactory : public AnimalFactory {
public:
    Animal* CreateAnimal() override {
        return new Dog();
    }
};


class ParrotFactory : public AnimalFactory {
public:
    Animal* CreateAnimal() override {
        return new Parrot();
    }
};


class HamsterFactory : public AnimalFactory {
public:
    Animal* CreateAnimal() override {
        return new Hamster();
    }
};
