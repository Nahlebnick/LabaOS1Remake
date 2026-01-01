#include "fileUtils.h"

vector<employee> readEmployees(istream &file)
{
    vector<employee> employees;
    employee emp;
    while (file.read((char*)&emp, sizeof(employee)))
    {
        employees.push_back(emp);
    }
    return employees;
}

vector<employee> readEmployeesFromFile(const string filename)
{
    ifstream file(filename, ios::binary);
    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    auto employees = readEmployees(file);
    return employees;
}


void writeEmployees(ostream& file, vector<employee>& employees)
{
    
    for (const auto& emp : employees)
    {
        file.write((char*)&emp, sizeof(employee));
    }
}

void writeEmployeesIntoFile(const string filename, vector<employee>& employees)
{
    ofstream file(filename, ios::binary);
    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    writeEmployees(file, employees);
}

string getFilename(istream& in, string defaultExt)
{
    string filename;

    in >> filename;

    if (filename.find('.') == std::string::npos)
    {
        filename += defaultExt;
    }
    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return filename;
}