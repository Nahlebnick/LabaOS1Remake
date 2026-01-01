#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "employee.h"
using namespace std;

vector<employee> readEmployees(istream& file);

vector<employee> readEmployeesFromFile(const string filename);

void writeEmployees(ostream& file, vector<employee>& employees);

void writeEmployeesIntoFile(const string filename, vector<employee>& employees);

string getFilename(istream& in, string defaultExt);