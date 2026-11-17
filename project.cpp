#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <ctime>
using namespace std;

//----------------------classes---------------
class University;
class course;
class Department;
class Teacher;
class Student;

//----------------------------------------------

class University {
protected:
    string uname;
    time_t registrationTime;
public:
void presskey(){
    cout<<"Press any key to continue."<<endl;
    cin.ignore();
    cin.get();
    }
    void setRegistrationTime() { registrationTime = time(0); }
    void set(string n) { uname = n; cout << "Your University is now registered\n"; }
    void reg_display() { cout << "The University registered with this system is:\n" << uname << endl; }
    void detail_display();
    void clearScreen();
};

void University::clearScreen() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear"); // Linux/macOS
#endif
}

class course {
public:
    int course_id;
    string cname;
    static int coursecount;
    static int cremovecount;
    bool active;
    void add();
    void cdisplay();
};

int course::coursecount = 0;
int course::cremovecount = 0;

void course::add() {
    coursecount++;
    course_id = coursecount;
    cout << "Enter course name: ";
    getline(cin, cname);
    active = true;
}

void course::cdisplay() {
    cout << course_id << " " << cname << endl;
}

class Department : public University {
public:
    int id;
    static int departmentcount;
    static int dremovecount;
    bool active;
    string depname;
    vector<course> courses;
    void add();
    void ddisplay();
    void addCourseToDepartment();
};

int Department::departmentcount = 0;
int Department::dremovecount = 0;

void Department::add() {
    departmentcount++;
    id = departmentcount;
    cout << "Enter Department name: ";
    getline(cin, depname);
    active = true;
}

void Department::ddisplay() {
    cout << id << " " << depname << endl;
}

void Department::addCourseToDepartment() {
    course c;
    c.add();
    courses.push_back(c);
}

class Teacher {
public:
    int emp_id;
    string empname;
    long long tcontact_no;
    int grade;
    double salary;
    string dep_name;
    static int tremovecount;
    static int teachercount;
    bool active;
    void add();
    void tdisplay();
};

int Teacher::teachercount = 0;
int Teacher::tremovecount = 0;

void Teacher::add() {
    teachercount++;
    emp_id = teachercount;

    cout << "Enter employee name: ";
    getline(cin, empname);

    cout << "Enter Department: ";
    getline(cin, dep_name);

    cout << "Enter Grade: ";
    while (!(cin >> grade)) {
        cout << "Invalid input. Enter an integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter Salary: ";
    while (!(cin >> salary)) {
        cout << "Invalid input. Enter an integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

cout<<"Enter Mobile Number:"<<endl;
while(!(cin>>tcontact_no) || tcontact_no <3000000000 || tcontact_no>99999999999){
    cout<<"Please enter a valid Mobile Number:"<<endl;
    cin.clear();
    cin.ignore(10000,'\n');
}
    active = true;
}
void Teacher::tdisplay() {
    cout << "  "<<emp_id << "    " << empname << " " << dep_name << "  " << grade << "  " << salary <<" "<<tcontact_no<<endl;
}

class Student {
public:
    int std_id;
    string stdname;
    string fname;
    string scourse;
    long long scontact_no;
    static int sremovecount;
    static int studentcount;
    bool active;
    void add();
    void sdisplay();
};

int Student::studentcount = 0;
int Student::sremovecount = 0;

void Student::add() {
    studentcount++;
    std_id = studentcount;
    cout << "Enter student name: ";
    getline(cin, stdname);
    cout << "Enter student's Father/Guardian name: ";
    getline(cin, fname);
    cout << "Enter course selected for enrollment: ";
    getline(cin, scourse);
    cout<<" Enter Mobile Number:"<<endl;
    while(!(cin>>scontact_no) || scontact_no<3000000000 || scontact_no>99999999999){
        cout<<"please enter a valid mobile number:"<<endl;
        cin.clear();
        cin.ignore(10000 , '\n'); }
    active = true;
}

void Student::sdisplay() {
    cout << std_id << " " << stdname << " " << fname << " " << scourse <<" "<<scontact_no<<endl;
}

//-----------------------------------------------------------
void University::detail_display() {
    cout << "University Name: " << uname << endl;
    cout << "Registration Date: " << ctime(&registrationTime);
    cout << "Number of Departments: " << Department::departmentcount - Department::dremovecount << endl;
    cout << "Total number of Staff members: " << Teacher::teachercount - Teacher::tremovecount << endl;
    cout << "Currently enrolled students: " << Student::studentcount - Student::sremovecount << endl;
    cout << "Number of Courses currently offering: " << course::coursecount - course::cremovecount << endl;
}

// Global vectors
vector<Student> students;
vector<Teacher> staff;
vector<Department> departments;

//-------------------------------------------
int main() {
    int choice;
    cout << "          Welcome to University Management System.\n" << endl;

    cout << "Enter the name of the University to register: ";
    University u1;
    string uname;
    getline(cin, uname);
    u1.set(uname);
    u1.setRegistrationTime();
    u1.reg_display();

    bool mmenu = true;

    while (mmenu) {
        u1.clearScreen();
        cout << "\n----- University Management System -----\n";
        cout << "1. Manage Departments.\n";
        cout << "2. Manage Staff.\n";
        cout << "3. Manage Student Admissions.\n";
        cout << "4. Manage Courses.\n";
        cout << "5. Display University details.\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {

        // ---------------- Departments ----------------
        case 1: {
            bool dmenu = true;
            while (dmenu) {
                u1.clearScreen();
                cout << "\n----- Department Management -----\n";
                cout << "1. View Departments.\n";
                cout << "2. Add Departments.\n";
                cout << "3. Remove Departments.\n";
                cout << "4. Back\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice) {
                case 1: {
                    u1.clearScreen();
                    bool hasActive = false;
                    for (auto &dep : departments)
                        if (dep.active) hasActive = true;

                    if (!hasActive) {
                        cout << "No active departments found.\n";
                        u1.presskey();
                        break;
                    }

                    for (auto &dep : departments)
                        if (dep.active) dep.ddisplay();                       u1.presskey();
                    break;
                }
                case 2:
                    u1.clearScreen();
                    departments.emplace_back();
                    departments.back().add();
                    cout << "Department added successfully.\n";
                    u1.presskey();
                    break;
                case 3:
                    u1.clearScreen();
                    cout << "Enter Department ID to remove: ";
                    int rd;
                    cin >> rd;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    {
                        bool removed = false;
                        for (auto &dep : departments) {
                            if (dep.id == rd && dep.active) {
                                dep.active = false;
                                Department::dremovecount++;
                                removed = true;
                                cout << "Department removed successfully.\n";
                                u1.presskey();
                                break;
                            }
                        }
                        if (!removed) cout << "Invalid Department ID.\n";
                         u1.presskey();
                    }
                   
                    break;
                case 4:
                    dmenu = false;
                    break;
                default:
                    cout << "Invalid choice.\n";
                    u1.presskey();
                }
            }
            break;
        }

        // ---------------- Staff ----------------
        case 2: {
            bool tmenu = true;
            while (tmenu) {
                u1.clearScreen();
                cout << "\n----- Staff Management -----\n";
                cout << "1. Add staff member.\n";
                cout << "2. Remove staff member\n";
                cout << "3. Search staff record\n";
                cout << "4. Display Staff list.\n";
                cout << "5. Back\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice) {
                case 1:
                    u1.clearScreen();
                    staff.emplace_back();
                    staff.back().add();
                    u1.presskey();
                    break;
                case 2:
                    u1.clearScreen();
                    if (staff.empty()) { cout << "No staff available.\n";
                    u1.presskey();
                     break; }
                    cout << "Enter staff employee ID to remove: ";
                    int rt;
                    cin >> rt;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    {
                        bool removed = false;
                        for (auto &t : staff) {
                            if (t.emp_id == rt && t.active) {
                                t.active = false;
                                Teacher::tremovecount++;
                                removed = true;
                                cout << "Staff removed successfully.\n";
                                u1.presskey();
                                break;
                            }
                        }
                        if (!removed) cout << "Invalid Staff ID.\n";
                         u1.presskey();
                         break;
                    }
                case 3:
                    u1.clearScreen();
                    if (staff.empty()) { cout << "No staff available.\n";
                    u1.presskey();
                     break; }
                    cout << "Enter staff name or ID to search: ";
                    {
                        string searchTerm;
                        getline(cin, searchTerm);
                        bool found = false;
                        for (auto &t : staff) {
                            if (t.active && (to_string(t.emp_id) == searchTerm || t.empname == searchTerm)) {cout<<" id  | Name | Department | Grade | Salary | Contact no"<<endl;
                                t.tdisplay();
                                found = true;
                            }
                        }
                        if (!found) cout << "No matching staff found.\n";
                    }
                    u1.presskey();
                    break;
                case 4:
                    u1.clearScreen();
                    {
                        bool hasActive = false;
                        for (auto &t : staff)
                            if (t.active) hasActive = true;
                        if (!hasActive) { cout << "No staff available.\n";
                        u1.presskey();
                         break; }
                         cout<<" id  | Name | Department | Grade | Salary | Contact no"<<endl;
                        for (auto &t : staff)
                            if (t.active) t.tdisplay();
                    }
                    u1.presskey();
                    break;
                case 5:
                    tmenu = false;
                    break;
                default:
                    cout << "Invalid choice.\n";
                    u1.presskey();
                }
            }
            break;
        }

        // ---------------- Students ----------------
        case 3: {
            bool smenu = true;
            while (smenu) {
                u1.clearScreen();
                cout << "\n----- Student Management -----\n";
                cout << "1. Add student.\n";
                cout << "2. Remove Student.\n";
                cout << "3. Search Student info.\n";
                cout << "4. Display Students list.\n";
                cout << "5. Back\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice) {
                case 1:
                    u1.clearScreen();
                    students.emplace_back();
                    students.back().add();
                    u1.presskey();
                    break;
                case 2:
                    u1.clearScreen();
                    if (students.empty()) { cout << "No students available.\n"; 
                   u1.presskey();
                    break; }
                    cout << "Enter Student ID to remove: ";
                    int rs;
                    cin >> rs;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    {
                        bool removed = false;
                        for (auto &s : students) {
                            if (s.std_id == rs && s.active) {
                                s.active = false;
                                Student::sremovecount++;
                                removed = true;
                                cout << "Student removed successfully.\n";
                                u1.presskey();
                                break;
                            }
                        }
                        if (!removed) cout << "Invalid Student ID.\n";
                         u1.presskey();
                         break;
                    }
                case 3:
                    u1.clearScreen();
                    if (students.empty()) { cout << "No students available.\n";
                    u1.presskey();
                     break; }
                    cout << "Enter student name or ID to search: ";
                    {
                        string searchTerm;
                        getline(cin, searchTerm);
                        bool found = false;
                        for (auto &s : students) {
                            if (s.active && (to_string(s.std_id) == searchTerm || s.stdname == searchTerm)) {
                                cout<<" id  | Name | Father/Guardian | Course | Contact.no"<<endl;
                                s.sdisplay();
                                found = true;
                            }
                        }
                        if (!found) cout << "No matching student found.\n";
                    }
                    u1.presskey();
                    break;
                case 4:
                    u1.clearScreen();
                    {
                        bool hasActive = false;
                        for (auto &s : students)
                            if (s.active) hasActive = true;
                        if (!hasActive) { cout << "No students available.\n"; 
                        u1.presskey();break; }
                        cout<<" id  | Name | Father/Guardian | Course | Contact.no"<<endl;
                        for (auto &s : students)
                            if (s.active) s.sdisplay();
                    }
                    u1.presskey();
                    break;
                case 5:
                    smenu = false;
                    break;
                default:
                    cout << "Invalid choice.\n";
                    u1.presskey();
                }
            }
            break;
        }

        // ---------------- Courses ----------------
        case 4: {
            bool cmenu = true;
            while (cmenu) {
                u1.clearScreen();
                cout << "\n----- Course Management -----\n";
                cout << "1. Add Course.\n";
                cout << "2. Remove Course.\n";
                cout << "3. Search Course.\n";
                cout << "4. Display Courses.\n";
                cout << "5. Back\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice) {
                case 1: {
                    vector<int> activeDeps;
                    for (int i = 0; i < departments.size(); i++)
                        if (departments[i].active) activeDeps.push_back(i);
                    if (activeDeps.empty()) { cout << "No active departments. Add a department first.\n";
                    u1.presskey();
                     break; }

                    cout << "Select Department:\n";
                    for (int i = 0; i < activeDeps.size(); i++)
                        cout << i + 1 << ". " << departments[activeDeps[i]].depname << endl;

                    int depChoice; cin >> depChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (depChoice >= 1 && depChoice <= activeDeps.size()) {
                        departments[activeDeps[depChoice - 1]].addCourseToDepartment();
                    } else { cout << "Invalid department choice.\n"; }
                    u1.presskey();
                    break;
                }
                case 2: {
                    vector<int> activeDeps;
                    for (int i = 0; i < departments.size(); i++)
                        if (departments[i].active) activeDeps.push_back(i);
                    if (activeDeps.empty()) { cout << "No active departments.\n";
                    u1.presskey(); break; }

                    cout << "Select Department:\n";
                    for (int i = 0; i < activeDeps.size(); i++)
                        cout << i + 1 << ". " << departments[activeDeps[i]].depname << endl;

                    int depChoice; cin >> depChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (depChoice < 1 || depChoice > activeDeps.size()) { cout << "Invalid department choice.\n"; 
                    u1.presskey();break; }

                    auto &courseList = departments[activeDeps[depChoice - 1]].courses;
                    vector<int> activeCourses;
                    for (int i = 0; i < courseList.size(); i++)
                        if (courseList[i].active) activeCourses.push_back(i);
                    if (activeCourses.empty()) { cout << "No active courses in this department.\n";
                    u1.presskey(); break; }

                    cout << "Select course to remove:\n";
                    for (int i = 0; i < activeCourses.size(); i++)
                        cout << i + 1 << ". " << courseList[activeCourses[i]].cname << endl;

                    int courseChoice; cin >> courseChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (courseChoice < 1 || courseChoice > activeCourses.size()) { cout << "Invalid course choice.\n"; 
                    u1.presskey();
                    break; }

                    courseList[activeCourses[courseChoice - 1]].active = false;
                    course::cremovecount++;
                    cout << "Course removed successfully.\n";
                    
                    u1.presskey();
                    break;
                }
                case 3: {
                    cout << "Enter course name or ID to search: ";
                    string searchTerm;
                    getline(cin, searchTerm);
                    bool found = false;
                    for (auto &dep : departments) {
                        if (!dep.active) continue;
                        for (auto &c : dep.courses) {
                            if (!c.active) continue;
                            if (to_string(c.course_id) == searchTerm || c.cname == searchTerm) {
                                cout << "Department: " << dep.depname << " | ";
                                c.cdisplay();
                                found = true;
                            }
                        }
                    }
                    if (!found) cout << "No matching course found.\n";
                    u1.presskey();
                    break;
                }
                case 4: {
                    bool hasActiveDep = false;
                    for (auto &dep : departments) {
                        if (!dep.active) continue;
                        hasActiveDep = true;
                        cout << "Department: " << dep.depname << endl;
                        bool hasActiveCourse = false;
                        for (auto &c : dep.courses) {
                            if (c.active) { c.cdisplay(); hasActiveCourse = true; }
                        }
                        if (!hasActiveCourse) cout << "  No active courses in this department.\n";
                    }
                    if (!hasActiveDep) cout << "No active departments found.\n";
                    u1.presskey();
                    break;
                }
                case 5: cmenu = false; break;
                default: cout << "Invalid choice.\n";
                u1.presskey();
                }
            }
            break;
        }

        case 5:
            u1.clearScreen();
            u1.detail_display();
            u1.presskey();
            break;
        case 6:
            mmenu = false;
            break;
        default:
            cout << "Invalid choice.\n";
            u1.presskey();
        }
    }

    return 0;
}
