

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <map>

using namespace std;

#define STRING_EQUAL_STRING(str1, str2) str1.compare(str2) == 0

enum PersonType {
    PersonTypeStudent,
    PersonTypeEmployee,
    PersonTypeTA,
    PersonTypeInstructor,
    PersonTypeAdministrator,
    PersonTypeHead
};

enum EmployeeType {
    EmployeeTypeNone,
    EmployeeTypeTeachingAssistant,
    EmployeeTypeInstructor,
    EmployeeTypeAdmin,
    EmployeeTypeHead
};

enum IncomeType {
    IncomeTypeSalary,
    IncomeTypeWage
};

class Person {
public:
    string identifier;
    string name;
    
    virtual string getInformation() = 0;
};

class Student : public virtual Person {
public:
    double GPA;
    
    Student() {}
    Student(string identifier, string name) {
        this->identifier = identifier;
        this->name = name;
    }
    
    Student(string identifier, string name, double GPA) {
        this->identifier = identifier;
        this->name = name;
        this->GPA = GPA;
    }
    
    virtual string getInformation() override {
        string infor = "";
        infor += this->name;
        infor += " Student #";
        infor += this->identifier;
        infor += " GPA: ";
        infor += to_string(this->GPA);
        return infor;
    }
};

class Employee : virtual public Person {
private:
    double getWeeklySalary() {
        return anualSalary / totalWeekPerYear;
    }
    
    double getWeeklyWage() {
        return hourlyWage * weeklyWorkedHours;
    }
public:
    EmployeeType eType;
    IncomeType incomeType;
    
    // For Salary
    const int totalWeekPerYear = 52;
    double anualSalary;
    
    // For Wage
    double hourlyWage;
    double weeklyWorkedHours;
    
    double getWeeklyIncome() {
        switch (incomeType) {
            case IncomeTypeSalary:
                return getWeeklySalary();
            case IncomeTypeWage:
                return getWeeklyWage();
        }
    }
    
    Employee() {}
    Employee(string identifier, string name) {
        this->identifier = identifier;
        this->name = name;
    }
    Employee(string identifier, string name, IncomeType incomeType) {
        this->identifier = identifier;
        this->name = name;
        this->incomeType = incomeType;
    }
    
    virtual string getInformation() override {
        string infor = "";
        infor += this->name;
        infor += " Employee #";
        infor += this->identifier;
        infor += " Weekly Pay: $";
        string income = to_string(getWeeklyIncome());
        infor += income;
        return infor;
    }
    
    virtual string getInformationWithoutIncome() {
        string infor = "";
        infor += this->name;
        infor += " Employee #";
        infor += this->identifier;
        return infor;
    }
};

class TeachingAssistant : public Employee, public Student {
public:
    string studentId;
    string employeeId;
    TeachingAssistant(string identifier, string name) {
        this->identifier = identifier;
        this->name = name;
        this->incomeType = IncomeTypeWage;
    }
    
    virtual string getInformation() override {
        string infor = "";
        infor += this->name;
        infor += " TA\n";
        infor += " Student #";
        infor += this->studentId;
        infor += " GPA : ";
        infor += to_string(this->GPA);
        infor += "\n";
        infor += " Employee #";
        infor += this->employeeId;
        infor += " Weekly Pay: $";
        string income = to_string(getWeeklyIncome());
        infor += income;
        return infor;
    }
    
    virtual string getInformationWithoutIncome() override {
        string infor = "";
        infor += this->name;
        infor += " TA #";
        infor += this->employeeId;
        return infor;
    }
};

class Admin : virtual public Employee {
public:
    vector<Employee *> employees;
    
    Admin() {
        this->eType = EmployeeTypeAdmin;
        this->incomeType = IncomeTypeWage;
    }
    
    Admin(string identifier, string name) : Employee(identifier, name) {
        this->eType = EmployeeTypeAdmin;
        this->incomeType = IncomeTypeWage;
    }
    
    virtual string getInformation() override {
        string infor = "";
        infor += this->name;
        infor += " Administrator #";
        infor += this->identifier;
        infor += " Weekly Pay: $";
        string income = to_string(getWeeklyIncome());
        infor += income;
        infor += " Supervises:\n";
        for (int i = 0; i < this->employees.size(); ++i) {
            infor += " ";
            infor += this->employees[i]->getInformationWithoutIncome();
            if (i != employees.size() - 1) {
                infor += "\n";
            }
        }
        return infor;
    }
    
    virtual string getInformationWithoutIncome() override {
        string infor = "";
        infor += this->name;
        infor += " Administrator #";
        infor += this->identifier;
        return infor;
    }
};

class Instructor : virtual public Employee {
public:
    Instructor() {
        this->eType = EmployeeTypeInstructor;
        this->incomeType = IncomeTypeSalary;
    }
    
    Instructor(string identifier, string name) : Employee(identifier, name) {
        this->eType = EmployeeTypeInstructor;
        this->incomeType = IncomeTypeSalary;
    }
    
    virtual string getInformation() override {
        string infor = "";
        infor += this->name;
        infor += " Instructor #";
        infor += this->identifier;
        infor += " Weekly Pay: $";
        string income = to_string(getWeeklyIncome());
        infor += income;
        return infor;
    }
    
    virtual string getInformationWithoutIncome() override {
        string infor = "";
        infor += this->name;
        infor += " Instructor #";
        infor += this->identifier;
        return infor;
    }
};

class Head : public Admin, public Instructor {
public:
    Head() {
        this->eType = EmployeeTypeHead;
        this->incomeType = IncomeTypeSalary;
    }
    
    Head(string identifier, string name) : Employee(identifier, name) {
        this->eType = EmployeeTypeHead;
        this->incomeType = IncomeTypeSalary;
    }
    
    virtual string getInformation() override {
        string infor = "";
        infor += this->name;
        infor += " Head #";
        infor += this->identifier;
        infor += " Weekly Pay: $";
        string income = to_string(getWeeklyIncome());
        infor += income;
        infor += " Supervises:\n";
        for (int i = 0; i < this->employees.size(); ++i) {
            infor += " ";
            infor += this->employees[i]->getInformationWithoutIncome();
            if (i != employees.size() - 1) {
                infor += "\n";
            }
        }
        return infor;
    }
    
    virtual string getInformationWithoutIncome() override {
        string infor = "";
        infor += this->name;
        infor += " Head #";
        infor += this->identifier;
        return infor;
    }
};

vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}

class PersonFactory {
private:
    
public:
    PersonFactory() {}
    
    Student *createStudent(vector<string> personInfor) {
        Student *student = new Student(personInfor[2], personInfor[1], stof(personInfor[3]));
        return student;
    }
    
    Employee *createEmployee(vector<string> employeeInfor) {
        Employee *employee = new Employee(employeeInfor[2], employeeInfor[1], IncomeTypeWage);
        employee->hourlyWage = stof(employeeInfor[3]);
        employee->weeklyWorkedHours = stof(employeeInfor[4]);
        
        return employee;
    }
    
    TeachingAssistant *createTA(vector<string> taInfor) {
        string taId = taInfor[2] + "-" + taInfor[4];
        TeachingAssistant *ta = new TeachingAssistant(taId, taInfor[1]);
        ta->studentId = taInfor[2];
        ta->GPA = stof(taInfor[3]);
        ta->employeeId = taInfor[4];
        ta->hourlyWage = stof(taInfor[5]);
        ta->weeklyWorkedHours = stof(taInfor[6]);
        
        return ta;
    }
    
    Instructor *createInstructor(vector<string> instructorInfor) {
        Instructor *instructor = new Instructor(instructorInfor[2], instructorInfor[1]);
        instructor->anualSalary = stof(instructorInfor[3]);
        return instructor;
    }
    
    Admin *createAdmin(vector<string> adminInfor, map<string, Employee *> employeeCache) {
        Admin *admin = new Admin(adminInfor[2], adminInfor[1]);
        admin->hourlyWage = stof(adminInfor[3]);
        admin->weeklyWorkedHours = stof(adminInfor[4]);
        
        unsigned long totalSupervisedEmployee = adminInfor.size();
        for (int i = 5; i < totalSupervisedEmployee; ++i) {
            admin->employees.push_back(employeeCache[adminInfor[i]]);
        }
        
        return admin;
    }
    
    Head *createHead(vector<string> headInfor, map<string, Employee *> employeeCache) {
        Head *head = new Head(headInfor[2], headInfor[1]);
        head->anualSalary = stof(headInfor[3]);
        
        unsigned long totalSupervisedEmployee = headInfor.size();
        for (int i = 4; i < totalSupervisedEmployee; ++i) {
            head->employees.push_back(employeeCache[headInfor[i]]);
        }
        
        return head;
    }
};

int main(int argc, const char * argv[]) {
    map<string, PersonType> PTypeMaping;
    PTypeMaping.insert(pair<string, PersonType>("ta", PersonTypeTA));
    PTypeMaping.insert(pair<string, PersonType>("student", PersonTypeStudent));
    PTypeMaping.insert(pair<string, PersonType>("employee", PersonTypeEmployee));
    PTypeMaping.insert(pair<string, PersonType>("instructor", PersonTypeInstructor));
    PTypeMaping.insert(pair<string, PersonType>("administrator", PersonTypeAdministrator));
    PTypeMaping.insert(pair<string, PersonType>("head", PersonTypeHead));
    
    string line;
    ifstream testcaseFile("a5q3.txt");
    ofstream outputFile ("output.txt");
    
    map<string, Employee *> employeeCache;
    
    if (testcaseFile.is_open() && outputFile.is_open()) {
        PersonFactory personFactory = PersonFactory();
        
        while (getline(testcaseFile, line)) {
            vector<string> personInfor = split(line, ',');
            PersonType ptype = PTypeMaping[personInfor[0]];
            switch (ptype) {
                case PersonTypeStudent: {
                    Student *student = personFactory.createStudent(personInfor);
                    cout << student->getInformation() << endl;
                    outputFile << student->getInformation() << endl;
                    break;
                }
                case PersonTypeEmployee: {
                    Employee *employee = personFactory.createEmployee(personInfor);
                    cout << employee->getInformation() << endl;
                    outputFile << employee->getInformation() << endl;
                    employeeCache.insert(pair<string, Employee *>(employee->identifier, employee));
                    break;
                }
                case PersonTypeTA: {
                    TeachingAssistant *ta = personFactory.createTA(personInfor);
                    cout << ta->getInformation() << endl;
                    outputFile << ta->getInformation() << endl;
                    employeeCache.insert(pair<string, Employee *>(ta->employeeId, ta));
                    break;
                }
                case PersonTypeInstructor: {
                    Instructor *instructor = personFactory.createInstructor(personInfor);
                    cout << instructor->getInformation() << endl;
                    outputFile << instructor->getInformation() << endl;
                    employeeCache.insert(pair<string, Employee *>(instructor->identifier, instructor));
                    break;
                }
                case PersonTypeAdministrator: {
                    Admin *admin = personFactory.createAdmin(personInfor, employeeCache);
                    cout << admin->getInformation() << endl;
                    outputFile << admin->getInformation() << endl;
                    employeeCache.insert(pair<string, Employee *>(admin->identifier, admin));
                    break;
                }
                case PersonTypeHead: {
                    Head *head = personFactory.createHead(personInfor, employeeCache);
                    cout << head->getInformation() << endl;
                    outputFile << head->getInformation() << endl;
                    employeeCache.insert(pair<string, Employee *>(head->identifier, head));
                    break;
                }
                default:
                    break;
            }
            
        }
        outputFile.close();
        testcaseFile.close();
    } else {
        cout << "Unable to open file" << endl;
    }
    return 0;
}
