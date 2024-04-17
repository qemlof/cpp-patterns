#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include "classes.h"
using namespace std;

void input(string task);

int enumerate_species(string str);
string denumerate_species(int number);

vector<string> set_info(const string& line, char symb);
void set_pet_to_owner(string line, vector<Owner>& owners);

void task_1(vector<Owner>& owners);
void task_2(vector<Owner>& owners, string info);
void task_3(vector<Owner>& owners, string info);
void task_4(vector<Owner>& owners);
void task_5(vector<Owner>& owners, string info);
void task_6(vector<Owner>& owners);
void task_7();
void task_8();

#endif