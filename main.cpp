#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

struct Employee {
std::string name;
int employeeNumber;
double hourlyRate;
double hoursWorked;
double grossPay;
};

void ParseString(std::string &line, std::string &field);
void PrintTable(const std::vector<Employee> &employees);

int main() {
    std::ifstream csvFile;
    csvFile.open("/home/administrator/CLionProjects/EmployeeReport/EmployeeData.csv");

    if (!csvFile.is_open()) {
        std::cerr << "Can't open file" << std::endl;
        return 1;
    }

    std::vector<Employee> employees;

    std::string line;
    std::string name;
    std::string empNumber;
    std::string hourRate;
    std::string hourTime;

// Ignore the first line because it contains the CSV headers.
    getline(csvFile, line);

// Read each employee from the CSV file.
    while (getline(csvFile, line)) {
        ParseString(line, name);
        ParseString(line, empNumber);
        ParseString(line, hourRate);
        ParseString(line, hourTime);

        Employee employee;

        employee.name = name;
        employee.employeeNumber = stoi(empNumber);
        employee.hourlyRate = stod(hourRate);
        employee.hoursWorked = stod(hourTime);

// Calculate gross pay.
        employee.grossPay =
        employee.hourlyRate * employee.hoursWorked;

        employees.push_back(employee);
    }

csvFile.close();

// Table 1: Original order
    std::cout << "\nTable 1 - Original Employee Order\n";
    PrintTable(employees);

// Randomize the vector.
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(employees.begin(), employees.end(), generator);

// Table 2: Randomized order
    std::cout << "\nTable 2 - Randomized Employee Order\n";
    PrintTable(employees);

// Sort by gross pay, highest to lowest.
    std::sort(employees.begin(), employees.end(),
    [](const Employee &a, const Employee &b) {
    return a.grossPay > b.grossPay;
});

// Table 3: Sorted by gross pay
    std::cout << "\nTable 3 - Sorted by Gross Pay (Descending)\n";
    PrintTable(employees);

    return 0;
}

void ParseString(std::string &line, std::string &field) {
int comma;

comma = line.find(',');

field = line.substr(0, comma);
line = line.substr(comma + 1, line.length());
}

void PrintTable(const std::vector<Employee> &employees) {
    std::cout << "--------------------------------------------------------------------------"
    << std::endl;

    std::cout << std::setw(20) << std::left << "Name"
    << std::setw(15) << std::left << "Employee #"
    << std::setw(15) << std::left << "Hourly Rate"
    << std::setw(15) << std::left << "Hours"
    << std::setw(15) << std::left << "Gross Pay"
    << std::endl;

    std::cout << "--------------------------------------------------------------------------"
    << std::endl;

    for (const Employee &employee : employees) {
        std::cout << std::setw(20) << std::left << employee.name
        << std::setw(15) << std::left << employee.employeeNumber
        << std::setw(15) << std::fixed << std::setprecision(2)
        << employee.hourlyRate
        << std::setw(15) << std::left << employee.hoursWorked
        << std::setw(15) << std::left << employee.grossPay
        << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------"
    << std::endl;
}
