#include "employee.h"

std::istream& operator>>(std::istream& in, employee& emp)
{
    std::cout << "Enter employee data" << std::endl;
    std::cout << "Number: ";
    while (!(in >> emp.num) || emp.num < 0) {
        std::cout << "Invalid number: ";
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }    

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Name: ";
    in.get(emp.name, 10); 
    if (in.fail() && !in.eof()) in.clear(); 
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Hours: ";
    while (!(in >> emp.hours) || emp.hours < 0) {
        std::cout << "Invalid hours. Enter a positive number: ";
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const employee& emp)
{
    out << "Name: " << emp.name << std::endl;
    out << "Number: " << emp.num << std::endl;
    out << "Hours: " << emp.hours << std::endl;

    return out;
}

bool operator<(const employee& emp1, const employee& emp2)
{
    return emp1.num < emp2.num;
}

bool operator>(const employee& emp1, const employee& emp2)
{
    return emp1.num > emp2.num;
}