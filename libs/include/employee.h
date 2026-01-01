#pragma once
#include <iostream>
#include <iomanip>


struct employee
{
    int num;    
    double hours;
    char name[10]{};

    friend std::istream& operator>>(std::istream&, employee&);
    friend std::ostream& operator<<(std::ostream&, const employee&);
    friend bool operator<(const employee& emp1, const employee& emp2);
    friend bool operator>(const employee& emp1, const employee& emp2);
};