#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept> 
#include "employee.h"
#include "fileUtils.h"

void reportEmployees(const std::vector<employee>& employees, double hourlyWage, std::ostream& out)
{
    out << fixed << setprecision(2);

    for (const auto& emp : employees)
    {
        double salary = hourlyWage * emp.hours;
        out << left << setw(10) << emp.num
            << left << setw(10) << emp.name
            << left << setw(10) << emp.hours
            << left << setw(10) << salary << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        cerr << "Usage: Reporter <binfile> <reportfile> <hourly_wage>" << endl;
        return 1;
    }

    try 
    {
        std::string binFileName = argv[1];
        std::string reportFileName = argv[2];
        double hourlyWage = 0;

        try
        {
            hourlyWage = stod(argv[3]);
        } 
        catch (...) 
        {
            throw runtime_error("Error: wage '" + string(argv[3]) + "' should be number");
        }

        auto employees = readEmployeesFromFile(binFileName);

        std::ofstream fout(reportFileName);
        if (!fout)
        {
            throw runtime_error("Faied to create report file: " + reportFileName);
        }

        fout << "=== Report " << binFileName << " ===\n\n";
        fout << left << setw(10) << "Number"
             << left << setw(10) << "Name"
             << left << setw(10) << "Hours"
             << left << setw(10) << "Wage" << std::endl;
        fout << string(40, '-') << std::endl; // Разделительная линия

        reportEmployees(employees, hourlyWage, fout);

        fout << "\n=== End of report ===\n";
        
        std::cout << "Report successfully created: " << reportFileName << std::endl;
    }
    catch (const exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
