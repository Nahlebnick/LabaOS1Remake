#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <stdexcept>
#include "employee.h"
#include "fileUtils.h"

std::vector<employee> getEmployees(int empCount)
{
    std::vector<employee> employees;
    for (int i = 0; i < empCount; ++i)
    {
        employee emp;
        if (!(std::cin >> emp)) break; 
        employees.push_back(emp);
    }
    return employees;
}   

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <filename> <empCount>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    int empCount = 0;

    try 
    {
        try
        {
            empCount = std::stoi(argv[2]);
        } 
        catch (...)
        {
            throw std::runtime_error("Incorrent employee count: " + string(argv[2]));
        }
        
        std::cout << "Enter data about employees" << std::endl;
        auto employees = getEmployees(empCount);

        writeEmployeesIntoFile(filename, employees);
        
        std::cout << "Data passed " << filename << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}