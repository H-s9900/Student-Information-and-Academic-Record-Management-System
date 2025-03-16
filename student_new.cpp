#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class Admin
{
private:
    string password = "admin";
    friend class Password;
};

class Password : private Admin
{
public:
    Password(Admin a, string pasword)
    {
        if (a.password == pasword)
        {
            system("cls");
            cout << "\n\n\tLogin successful!" << endl;
        }
        else
        {
            cout << "\n\n\tInvalid password!" << endl;
            exit(0);
        }
    }
};

class Person
{
public:
    string name, ph_no, resident;
    int id;
    int age;
    string branch;
    string gender;
    Person *next;
    Person *next1;
};

struct AttendanceRecord
{
    int roll_num;
    double total_days;
    double days_present;
    double percentage;
};

struct AcademicRecord
{
    int roll_num;
    float marks[5];
    float percentage;
    string grade;
    string status;
};

class Student : public Person
{
public:
    void CheckInFees();
    void StudentFees(int roll_num);
    void displayStudent(int roll_num);
    void addStudent();
    void generateAttendanceReport(int roll_num);
    void generateFine(int roll_number);
    void validateSubjectMarks(int index);
    void generateAcademicReport(int roll_number);
    void saveAttendanceRecord(int roll_num, double total_days, double days_present, double percentage);
    void saveAcademicRecord(int roll_num, float marks[], float percentage, string grade, string status);
    void displayAttendanceHistory(int roll_num);
    void displayAcademicHistory(int roll_num);
};

int count = 0;
Person *head = NULL;
Person *head1 = NULL;

void readDetail()
{
    fstream display;
    display.open("btech_students.txt", ios::app | ios::in);
    if (display.fail())
    {
        cout << "\nError Opening File\n";
        return;
    }
    while (!display.eof())
    {
        Person *temp = new Person;
        display.ignore();
        getline(display, temp->name);
        getline(display, temp->resident);
        getline(display, temp->ph_no);
        display >> temp->id;
        display >> temp->gender;
        display >> temp->age;
        display >> temp->branch;
        temp->next = NULL;
        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            Person *temp1 = head;
            while (temp1->next != NULL)
            {
                temp1 = temp1->next;
            }
            temp1->next = temp;
        }
    }
    display.close();
}

void Student::addStudent()
{
    ofstream out;
    out.open("btech_students.txt", ios::out | ios::app);
    if (out.fail())
    {
        cout << "\nError Opening File." << endl;
        return;
    }
    Person *temp = new Person;
    cout << "Enter the name: ";
    cin.ignore();
    getline(cin, temp->name);
    out << temp->name << endl;
    cout << "Enter the residence of student: ";
    getline(cin, temp->resident);
    out << temp->resident << endl;
    cout << "Enter the phone number of student: ";
    getline(cin, temp->ph_no);
    out << temp->ph_no << endl;
    cout << "Enter the roll number (ID): ";
    cin >> temp->id;
    Person *ptr = head;
    while (ptr != NULL)
    {
        if (ptr->id == temp->id)
        {
            cout << "This roll number already exists!";
            exit(0);
        }
        ptr = ptr->next;
    }
    out << temp->id << endl;
    cout << "Enter the gender: ";
    cin >> temp->gender;
    out << temp->gender << endl;
    cout << "Enter the age: ";
    cin >> temp->age;
    out << temp->age << endl;
    cout << "Enter the branch (CSE/CSIT/IOT&CS/CC/AI&ML): ";
    cin >> temp->branch;
    if (temp->branch != "CSE" && temp->branch != "CSIT" && temp->branch != "IOT&CS" &&
        temp->branch != "CC" && temp->branch != "AI&ML")
    {
        cout << "Invalid branch! Please enter CSE, CSIT, IOT&CS, CC, or AI&ML.\n";
        out.close();
        return;
    }
    out << temp->branch << endl;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        Person *temp1 = head;
        while (temp1->next != NULL)
        {
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
    out.close();
    cout << "\nStudent added successfully!";
}

void Student::displayStudent(int roll_num)
{
    Person *temp = head;
    bool found = false;
    while (temp != NULL)
    {
        if (temp->id == roll_num)
        {
            cout << "\n\n\t------Student Details-------\n\n";
            cout << "\t\tRoll Number: " << temp->id << endl;
            cout << "\t\tName: " << temp->name << endl;
            cout << "\t\tPhone Number: " << temp->ph_no << endl;
            cout << "\t\tResidence: " << temp->resident << endl;
            cout << "\t\tAge: " << temp->age << endl;
            cout << "\t\tBranch: " << temp->branch << endl;
            cout << "\t\tGender: " << temp->gender << endl;
            cout << "\n\t----------------------------\n";
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (!found)
        cout << "\nStudent not found!\n";
}

void Student::CheckInFees()
{
    Person *temp = head;
    int countCSE = 0, countCSIT = 0, countIOTCS = 0, countCC = 0, countAIML = 0;
    while (temp != NULL)
    {
        if (temp->branch == "CSE")
            countCSE++;
        else if (temp->branch == "CSIT")
            countCSIT++;
        else if (temp->branch == "IOT&CS")
            countIOTCS++;
        else if (temp->branch == "CC")
            countCC++;
        else if (temp->branch == "AI&ML")
            countAIML++;
        temp = temp->next;
    }
    int feePerStudent = 150000;
    if (countCSE > 0)
    {
        cout << "\n\n\t\t---------------CSE STUDENTS------------------\n\n";
        cout << "\t\tTotal Admitted Students: " << countCSE << endl;
        cout << "\t\tTotal Fees: " << countCSE * feePerStudent << " INR\n";
    }
    if (countCSIT > 0)
    {
        cout << "\n\n\t\t---------------CSIT STUDENTS-------------------\n\n";
        cout << "\t\tTotal Admitted Students: " << countCSIT << endl;
        cout << "\t\tTotal Fees: " << countCSIT * feePerStudent << " INR\n";
    }
    if (countIOTCS > 0)
    {
        cout << "\n\n\t\t---------------IOT&CS STUDENTS-------------------\n\n";
        cout << "\t\tTotal Admitted Students: " << countIOTCS << endl;
        cout << "\t\tTotal Fees: " << countIOTCS * feePerStudent << " INR\n";
    }
    if (countCC > 0)
    {
        cout << "\n\n\t\t---------------CC STUDENTS--------------------\n\n";
        cout << "\t\tTotal Admitted Students: " << countCC << endl;
        cout << "\t\tTotal Fees: " << countCC * feePerStudent << " INR\n";
    }
    if (countAIML > 0)
    {
        cout << "\n\n\t\t---------------AI&ML STUDENTS--------------------\n\n";
        cout << "\t\tTotal Admitted Students: " << countAIML << endl;
        cout << "\t\tTotal Fees: " << countAIML * feePerStudent << " INR\n";
    }
    cout << "\n\n\t\t-------------------------------------------------\n\n";
}

void Student::StudentFees(int roll_num)
{
    Person *temp = head;
    bool found = false;
    while (temp != NULL)
    {
        if (temp->id == roll_num)
        {
            cout << "\n\n\t-----------------" << temp->branch << " STUDENT----------------------\n\n";
            cout << "\t  Roll Number: " << temp->id << endl;
            cout << "\t  Student Name: " << temp->name << endl;
            cout << "\t  Branch: " << temp->branch << endl;
            cout << "\t  Phone Number: " << temp->ph_no << endl;
            cout << "\n\t-------------------------------------------------------\n";
            cout << "\t       Student Fees Received Successfully (150,000 INR)\n";
            cout << "\t-------------------------------------------------------\n";
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (!found)
        cout << "\nSorry! Student not found or fees not received yet.\n";
}

double attendancePercentage;
void Student::generateAttendanceReport(int roll_num)
{
    system("cls");
    double totalWorkingDays, daysPresent;
    Person *temp = head;
    bool found = false;
    while (temp != NULL)
    {
        if (roll_num == temp->id)
        {
            cout << " NAME: \n \t" << temp->name << endl;
            cout << " BRANCH: \n \t" << temp->branch << endl
                 << endl;
            cout << "\nEnter total number of working days (1 - 240): ";
            cin >> totalWorkingDays;
            cout << "Enter number of days student " << temp->id << " was present (1 - 240): ";
            cin >> daysPresent;
            attendancePercentage = ((daysPresent / totalWorkingDays) * 100.00);
            cout << "Attendance Percentage = " << attendancePercentage << "%" << endl;
            if (attendancePercentage >= 75)
            {
                cout << "\nAttendance above 75%, eligible for exams without fine.\n\n";
            }
            else if (attendancePercentage >= 70)
            {
                cout << "\nAttendance below 75%, fine of 10,000 INR required.\n\n";
            }
            else
            {
                cout << "\nAttendance below 70%, student is detained from exams.\n\n";
            }
            saveAttendanceRecord(roll_num, totalWorkingDays, daysPresent, attendancePercentage);
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (found)
        cout << "\nAttendance report generated and saved successfully!\n\n";
    else
        cout << "\nStudent not found!\n";
}

void Student::generateFine(int roll_number)
{
    system("cls");
    Person *temp = head;
    bool found = false;
    while (temp != NULL)
    {
        if (temp->id == roll_number)
        {
            cout << "Name: " << temp->name << endl;
            cout << "Branch: " << temp->branch << endl;
            cout << "Roll Number: " << temp->id << endl;
            cout << "Attendance Percentage: " << attendancePercentage << "%" << endl;
            if (attendancePercentage >= 75)
            {
                cout << "\nNo fine required.\n\n";
            }
            else if (attendancePercentage >= 70)
            {
                cout << "\nFine of 10,000 INR applicable.\n\n";
            }
            else
            {
                cout << "\nStudent detained due to low attendance.\n\n";
            }
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (!found)
        cout << "Sorry! Student not found.\n";
}

float marks[5];
void Student::validateSubjectMarks(int index)
{
    string subject[5] = {"DS", "OOP", "DBMS", "OS", "Maths"};
    if (marks[index] < 0 || marks[index] > 100)
    {
        cout << "\nInvalid marks for " << subject[index] << ". Enter between 0 and 100: ";
        cin >> marks[index];
    }
}

void Student::generateAcademicReport(int roll_number)
{
    system("cls");
    float obtainingMarks, totalMarks = 500.0, percentage;
    string grade, status;
    Person *temp = head;
    bool found = false;
    while (temp != NULL)
    {
        if (temp->id == roll_number)
        {
            cout << "\nEnter marks for student (" << temp->id << ") in 5 subjects (0-100):\n";
            cout << "1. Data Structures = ";
            cin >> marks[0];
            validateSubjectMarks(0);
            cout << "2. Object-Oriented Programming = ";
            cin >> marks[1];
            validateSubjectMarks(1);
            cout << "3. Database Management Systems = ";
            cin >> marks[2];
            validateSubjectMarks(2);
            cout << "4. Operating Systems = ";
            cin >> marks[3];
            validateSubjectMarks(3);
            cout << "5. Mathematics = ";
            cin >> marks[4];
            validateSubjectMarks(4);
            obtainingMarks = (marks[0] + marks[1] + marks[2] + marks[3] + marks[4]);
            percentage = (obtainingMarks / totalMarks) * 100;
            cout << "Total Marks: " << totalMarks << "\nObtained Marks: " << obtainingMarks << endl;
            cout << "Percentage: " << percentage << "%" << endl;
            if (percentage >= 90)
                grade = "A+";
            else if (percentage >= 80)
                grade = "A";
            else if (percentage >= 70)
                grade = "B";
            else if (percentage >= 60)
                grade = "C";
            else if (percentage >= 50)
                grade = "D";
            else
                grade = "F";
            cout << "Grade: " << grade << endl;
            status = (grade != "F") ? "Pass" : "Fail";
            cout << "Status: " << status << endl
                 << endl;
            saveAcademicRecord(roll_number, marks, percentage, grade, status);
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (!found)
        cout << "\nStudent not found!\n";
    else
        cout << "\nAcademic report generated and saved successfully!\n\n";
}

void Student::saveAttendanceRecord(int roll_num, double total_days, double days_present, double percentage)
{
    ofstream out;
    out.open("attendance_records.txt", ios::app);
    if (out.fail())
    {
        cout << "\nError opening attendance file!" << endl;
        return;
    }
    out << roll_num << endl;
    out << fixed << setprecision(2) << total_days << endl;
    out << fixed << setprecision(2) << days_present << endl;
    out << fixed << setprecision(2) << percentage << endl;
    out.close();
}

void Student::saveAcademicRecord(int roll_num, float marks[], float percentage, string grade, string status)
{
    ofstream out;
    out.open("academic_reports.txt", ios::app);
    if (out.fail())
    {
        cout << "\nError opening academic file!" << endl;
        return;
    }
    out << roll_num << endl;
    for (int i = 0; i < 5; i++)
    {
        out << fixed << setprecision(2) << marks[i] << endl;
    }
    out << fixed << setprecision(2) << percentage << endl;
    out << grade << endl;
    out << status << endl;
    out.close();
}

void Student::displayAttendanceHistory(int roll_num)
{
    ifstream in;
    in.open("attendance_records.txt");
    if (in.fail())
    {
        cout << "\nNo attendance records found!" << endl;
        return;
    }

    bool found = false;
    AttendanceRecord record;
    while (in >> record.roll_num)
    {
        in >> record.total_days >> record.days_present >> record.percentage;
        if (record.roll_num == roll_num)
        {
            cout << "\n\n\t------Attendance History-------\n\n";
            cout << "\tRoll Number: " << record.roll_num << endl;
            cout << "\tTotal Working Days: " << record.total_days << endl;
            cout << "\tDays Present: " << record.days_present << endl;
            cout << "\tAttendance Percentage: " << record.percentage << "%" << endl;
            cout << "\n\t----------------------------\n";
            found = true;
        }
    }
    in.close();
    if (!found)
    {
        cout << "\nNo attendance history found for this student!" << endl;
    }
}

void Student::displayAcademicHistory(int roll_num)
{
    ifstream in;
    in.open("academic_reports.txt");
    if (in.fail())
    {
        cout << "\nNo academic records found!" << endl;
        return;
    }

    bool found = false;
    AcademicRecord record;
    string subjects[5] = {"DS", "OOP", "DBMS", "OS", "Maths"};
    while (in >> record.roll_num)
    {
        for (int i = 0; i < 5; i++)
        {
            in >> record.marks[i];
        }
        in >> record.percentage;
        in >> record.grade;
        in >> record.status;

        if (record.roll_num == roll_num)
        {
            cout << "\n\n\t------Academic History-------\n\n";
            cout << "\tRoll Number: " << record.roll_num << endl;
            for (int i = 0; i < 5; i++)
            {
                cout << "\t" << subjects[i] << ": " << record.marks[i] << endl;
            }
            cout << "\tPercentage: " << record.percentage << "%" << endl;
            cout << "\tGrade: " << record.grade << endl;
            cout << "\tStatus: " << record.status << endl;
            cout << "\n\t----------------------------\n";
            found = true;
        }
    }
    in.close();
    if (!found)
    {
        cout << "\nNo academic history found for this student!" << endl;
    }
}

void searchStudent(int roll_num)
{
    Person *temp = head;
    bool found = false;
    if (temp == NULL)
    {
        cout << "No student data available." << endl;
        return;
    }
    while (temp != NULL)
    {
        if (temp->id == roll_num)
        {
            cout << "\n\n\t------Student Found-------\n\n";
            cout << "\t\tRoll Number: " << temp->id << endl;
            cout << "\t\tName: " << temp->name << endl;
            cout << "\t\tPhone Number: " << temp->ph_no << endl;
            cout << "\t\tResidence: " << temp->resident << endl;
            cout << "\t\tAge: " << temp->age << endl;
            cout << "\t\tBranch: " << temp->branch << endl;
            cout << "\t\tGender: " << temp->gender << endl;
            cout << "\n\t----------------------------\n";
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (!found)
        cout << "\nStudent not found!\n";
}

void deleteStd(int roll_num)
{
    ofstream write;
    write.open("new.txt", ios::app | ios::out);
    ifstream dlt;
    dlt.open("btech_students.txt", ios::app | ios::in);
    if (write.fail() || dlt.fail())
    {
        cout << "\nError Opening File." << endl;
        return;
    }
    bool found = false;
    while (dlt >> ws)
    {
        Person *temp = new Person;
        dlt.ignore();
        getline(dlt, temp->name);
        getline(dlt, temp->resident);
        getline(dlt, temp->ph_no);
        dlt >> temp->id;
        dlt >> temp->gender;
        dlt >> temp->age;
        dlt >> temp->branch;
        temp->next1 = NULL;
        if (temp->id == roll_num)
        {
            Person *ptr = head;
            if (ptr == NULL)
            {
                cout << "No students to delete." << endl;
                return;
            }
            if (ptr->id == roll_num)
            {
                head = ptr->next;
                delete ptr;
                found = true;
                continue;
            }
            while (ptr->next != NULL)
            {
                if (ptr->next->id == roll_num)
                {
                    Person *ptr1 = ptr->next;
                    ptr->next = ptr1->next;
                    delete ptr1;
                    found = true;
                    break;
                }
                ptr = ptr->next;
            }
        }
        else
        {
            write << temp->name << endl;
            write << temp->resident << endl;
            write << temp->ph_no << endl;
            write << temp->id << endl;
            write << temp->gender << endl;
            write << temp->age << endl;
            write << temp->branch << endl;
            if (head1 == NULL)
            {
                head1 = temp;
            }
            else
            {
                Person *temp1 = head1;
                while (temp1->next1 != NULL)
                {
                    temp1 = temp1->next1;
                }
                temp1->next1 = temp;
            }
        }
    }
    dlt.close();
    write.close();
    remove("btech_students.txt");
    rename("new.txt", "btech_students.txt");
    if (found)
        cout << "\nStudent record deleted successfully!\n\n";
    else
        cout << "\nStudent not found!\n";
}

void updateStd(int roll_num)
{
    Person *temp = head;
    bool found = false;
    while (temp != NULL)
    {
        if (temp->id == roll_num)
        {
            cout << "Enter the name: ";
            cin.ignore();
            getline(cin, temp->name);
            cout << "Enter the residence of student: ";
            getline(cin, temp->resident);
            cout << "Enter the phone number of student: ";
            getline(cin, temp->ph_no);
            cout << "Enter the roll number (ID): ";
            cin >> temp->id;
            cout << "Enter the gender: ";
            cin >> temp->gender;
            cout << "Enter the age: ";
            cin >> temp->age;
            cout << "Enter the branch (CSE/CSIT/IOT&CS/CC/AI&ML): ";
            cin >> temp->branch;
            if (temp->branch != "CSE" && temp->branch != "CSIT" && temp->branch != "IOT&CS" &&
                temp->branch != "CC" && temp->branch != "AI&ML")
            {
                cout << "Invalid branch! Please enter CSE, CSIT, IOT&CS, CC, or AI&ML.\n";
                return;
            }
            found = true;
            cout << "\nStudent record updated successfully!\n";
            break;
        }
        temp = temp->next;
    }
    if (!found)
        cout << "\nStudent not found!\n";
}

void menu()
{
    cout << "\n\n\tSelect an option to proceed:\n\n";
    cout << "\t1. Add B.Tech Student Details\n";
    cout << "\t2. Check Total Fees\n";
    cout << "\t3. Verify Fee Payment\n";
    cout << "\t4. Generate Attendance Report\n";
    cout << "\t5. Generate Attendance Fine\n";
    cout << "\t6. Generate Academic Report\n";
    cout << "\t7. View Attendance History\n";
    cout << "\t8. View Academic History\n";
    cout << "\t0. Return to Main Menu\n";
}

int main()
{
    int choice;
    Student s;
    readDetail();
    int student_id;
    cout << "\n\n";
    cout << "       ======================================\n";
    cout << "       ==== WELCOME TO C.V. RAMAN GLOBAL ====\n";
    cout << "       ======= UNIVERSITY,BHUBANESWAR =======\n";
    cout << "       ======================================\n";
    string password;
    cout << "\n\nPlease enter the admin password: ";
    cin >> password;
    Admin ad;
    Password p1(ad, password);
    cout << "\nPress Enter to continue...";
    getch();
    system("cls");

    cout << "\n\t\t\t\t*************************";
    cout << "\n\t\t\t\tB.Tech STUDENT MANAGEMENT";
    cout << "\n\t\t\t\t      * MAIN MENU *      ";
    cout << "\n\t\t\t\t*************************";
B:
    cout << "\n\n\n\t\t\t1. Manage Student Details\n";
    cout << "\t\t\t2. Display Student Record\n";
    cout << "\t\t\t3. Search Student Record\n";
    cout << "\t\t\t4. Update Student Record\n";
    cout << "\t\t\t5. Delete Student Record\n";
    cout << "\t\t\t0. Exit\n";
    cout << "\n\t\t\tEnter Your Choice: ";
    cin >> choice;
    system("cls");

    switch (choice)
    {
    case 1:
    A:
        menu();
        cout << "\n\tEnter your choice: ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            s.addStudent();
            cout << "\n\tPress Enter to continue...";
            while (getch() != 13)
                ;
            system("cls");
            goto A;
        case 2:
            s.CheckInFees();
            cout << "\n\tPress Enter to continue...";
            while (getch() != 13)
                ;
            system("cls");
            goto A;
        case 3:
            cout << "Enter the roll number to verify fee payment: ";
            cin >> student_id;
            s.StudentFees(student_id);
            cout << "\n\tPress Enter to continue...";
            while (getch() != 13)
                ;
            system("cls");
            goto A;
        case 4:
            cout << "Enter roll number for attendance report: ";
            cin >> student_id;
            s.generateAttendanceReport(student_id);
            cout << "\n\tPress Enter to continue...";
            while (getch() != 13)
                ;
            system("cls");
            goto A;
        case 5:
            cout << "Enter roll number for attendance fine: ";
            cin >> student_id;
            s.generateFine(student_id);
            cout << "\n\tPress Enter to continue...";
            while (getch() != 13)
                ;
            system("cls");
            goto A;
        case 6:
            cout << "Enter roll number for academic report: ";
            cin >> student_id;
            s.generateAcademicReport(student_id);
            cout << "\n\tPress Enter to continue...";
            while (getch() != 13)
                ;
            system("cls");
            goto A;
        case 7:
            cout << "Enter roll number for attendance history: ";
            cin >> student_id;
            s.displayAttendanceHistory(student_id);
            cout << "\n\tPress Enter to continue...";
            while (getch() != 13)
                ;
            system("cls");
            goto A;
        case 8:
            cout << "Enter roll number for academic history: ";
            cin >> student_id;
            s.displayAcademicHistory(student_id);
            cout << "\n\tPress Enter to continue...";
            while (getch() != 13)
                ;
            system("cls");
            goto A;
        case 0:
            system("cls");
            goto B;
        default:
            cout << "\n\tInvalid choice! Press Enter to try again...";
            while (getch() != 13)
                ;
            system("cls");
            goto A;
        }
        break;
    case 2:
        cout << "Enter the roll number to display: ";
        cin >> student_id;
        s.displayStudent(student_id);
        cout << "\n\tPress Enter to continue...";
        while (getch() != 13)
            ;
        system("cls");
        goto B;
    case 3:
        cout << "Enter the roll number to search: ";
        cin >> student_id;
        searchStudent(student_id);
        cout << "\n\tPress Enter to continue...";
        while (getch() != 13)
            ;
        system("cls");
        goto B;
    case 4:
        cout << "Enter the roll number to update: ";
        cin >> student_id;
        updateStd(student_id);
        cout << "\n\tPress Enter to continue...";
        while (getch() != 13)
            ;
        system("cls");
        goto B;
    case 5:
        cout << "Enter the roll number to delete: ";
        cin >> student_id;
        deleteStd(student_id);
        cout << "\n\tPress Enter to continue...";
        while (getch() != 13)
            ;
        system("cls");
        goto B;
    case 0:
        cout << "\n\nThank you for using the C.V. Raman Global University Student Management System!\n";
        exit(0);
    default:
        cout << "\n\tInvalid choice! Press Enter to try again...";
        while (getch() != 13)
            ;
        system("cls");
        goto B;
    }
}