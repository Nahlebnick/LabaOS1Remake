#include <gtest/gtest.h>
#include <sstream>
#include "employee.h"

TEST(EmployeeTest, ComparisonOperators) {
    employee emp1;
    emp1.num = 10;
    
    employee emp2;
    emp2.num = 20;

    employee emp3;
    emp3.num = 10;

    EXPECT_TRUE(emp1 < emp2);
    EXPECT_FALSE(emp2 < emp1);
    EXPECT_FALSE(emp1 < emp3);

    EXPECT_TRUE(emp2 > emp1);
    EXPECT_FALSE(emp1 > emp2);
    EXPECT_FALSE(emp1 > emp3);
}

TEST(EmployeeTest, OutputOperator) {
    employee emp;
    emp.num = 101;
    emp.hours = 40.5;
    std::string name = "Ivan";
    std::copy(name.begin(), name.end(), emp.name);
    emp.name[name.length()] = '\0';

    std::stringstream ss;
    ss << emp;

    std::string output = ss.str();

    EXPECT_NE(output.find("Name: Ivan"), std::string::npos);
    EXPECT_NE(output.find("Number: 101"), std::string::npos);
    EXPECT_NE(output.find("Hours: 40.5"), std::string::npos);
}

TEST(EmployeeTest, InputOperatorValid) {
    employee emp;
    std::string input_data = "55\nAnna\n\n30.5\n"; 
    
    std::stringstream ss(input_data);
    std::stringstream output_capture;

    std::streambuf* old_cout = std::cout.rdbuf(output_capture.rdbuf());

    ss >> emp;

    std::cout.rdbuf(old_cout);

    EXPECT_EQ(emp.num, 55);
    EXPECT_STREQ(emp.name, "Anna");
    EXPECT_DOUBLE_EQ(emp.hours, 30.5);
}

TEST(EmployeeTest, InputOperatorValidation) {
    employee emp;
    
    std::string input_data = "-1\n10\nBob\n\n-5\n8\n";
    
    std::stringstream ss(input_data);
    std::stringstream output_capture;
    std::streambuf* old_cout = std::cout.rdbuf(output_capture.rdbuf());

    ss >> emp;

    std::cout.rdbuf(old_cout);

    EXPECT_EQ(emp.num, 10);
    EXPECT_STREQ(emp.name, "Bob");
    EXPECT_DOUBLE_EQ(emp.hours, 8.0);
}

/**/