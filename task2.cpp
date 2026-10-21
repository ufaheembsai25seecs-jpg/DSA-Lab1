#include <iostream>
#include <string>
using namespace std;

struct Student {
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;

    Student(int id, const string& studentName, float gpa) {
        studentID = id;
        name = studentName;
        GPA = gpa;
        left = nullptr;
        right = nullptr;
    }
};

class StudentBST {
private:
    Student* root;

    Student* insert(Student* node, int id, const string& name, float gpa) {
        if (node == nullptr) {
            return new Student(id, name, gpa);
        }

        if (id < node->studentID) {
            node->left = insert(node->left, id, name, gpa);
        } else if (id > node->studentID) {
            node->right = insert(node->right, id, name, gpa);
        } else {
            cout << "Student ID already exists: " << id << endl;
        }

        return node;
    }

    Student* search(Student* node, int id) {
        if (node == nullptr || node->studentID == id) {
            return node;
        }

        if (id < node->studentID) {
            return search(node->left, id);
        }

        return search(node->right, id);
    }

    Student* findMin(Student* node) {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }

        return node;
    }

    Student* remove(Student* node, int id) {
        if (node == nullptr) {
            return nullptr;
        }

        if (id < node->studentID) {
            node->left = remove(node->left, id);
        } else if (id > node->studentID) {
            node->right = remove(node->right, id);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            if (node->left == nullptr) {
                Student* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                Student* temp = node->left;
                delete node;
                return temp;
            }

            Student* successor = findMin(node->right);
            node->studentID = successor->studentID;
            node->name = successor->name;
            node->GPA = successor->GPA;
            node->right = remove(node->right, successor->studentID);
        }

        return node;
    }

    void displayInorder(Student* node) {
        if (node == nullptr) {
            return;
        }

        displayInorder(node->left);
        cout << "ID: " << node->studentID
             << " | Name: " << node->name
             << " | GPA: " << node->GPA << endl;
        displayInorder(node->right);
    }

    int countStudents(Student* node) {
        if (node == nullptr) {
            return 0;
        }

        return 1 + countStudents(node->left) + countStudents(node->right);
    }

    void findGPAExtremes(Student* node, Student*& highest, Student*& lowest) {
        if (node == nullptr) {
            return;
        }

        if (highest == nullptr || node->GPA > highest->GPA) {
            highest = node;
        }

        if (lowest == nullptr || node->GPA < lowest->GPA) {
            lowest = node;
        }

        findGPAExtremes(node->left, highest, lowest);
        findGPAExtremes(node->right, highest, lowest);
    }

    void displayAboveThreshold(Student* node, float threshold, bool& found) {
        if (node == nullptr) {
            return;
        }

        displayAboveThreshold(node->left, threshold, found);

        if (node->GPA > threshold) {
            cout << "ID: " << node->studentID
                 << " | Name: " << node->name
                 << " | GPA: " << node->GPA << endl;
            found = true;
        }

        displayAboveThreshold(node->right, threshold, found);
    }

    void destroyTree(Student* node) {
        if (node == nullptr) {
            return;
        }

        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    StudentBST() {
        root = nullptr;
    }

    ~StudentBST() {
        destroyTree(root);
    }

    void insertStudent(int id, const string& name, float gpa) {
        if (gpa < 0.0f || gpa > 4.0f) {
            cout << "Invalid GPA. Enter a value from 0.0 to 4.0." << endl;
            return;
        }

        root = insert(root, id, name, gpa);
    }

    void searchStudent(int id) {
        Student* result = search(root, id);

        if (result == nullptr) {
            cout << "Student not found." << endl;
        } else {
            cout << "Student found:" << endl;
            cout << "ID: " << result->studentID << endl;
            cout << "Name: " << result->name << endl;
            cout << "GPA: " << result->GPA << endl;
        }
    }

    void deleteStudent(int id) {
        if (search(root, id) == nullptr) {
            cout << "Student not found. Nothing deleted." << endl;
            return;
        }

        root = remove(root, id);
        cout << "Student deleted successfully." << endl;
    }

    void displayAllStudents() {
        if (root == nullptr) {
            cout << "No student records available." << endl;
            return;
        }

        displayInorder(root);
    }

    void displayCount() {
        cout << "Total students: " << countStudents(root) << endl;
    }

    void displayGPAExtremes() {
        if (root == nullptr) {
            cout << "No student records available." << endl;
            return;
        }

        Student* highest = nullptr;
        Student* lowest = nullptr;
        findGPAExtremes(root, highest, lowest);

        cout << "Highest GPA:" << endl;
        cout << highest->name << " (ID " << highest->studentID
             << "), GPA: " << highest->GPA << endl;

        cout << "Lowest GPA:" << endl;
        cout << lowest->name << " (ID " << lowest->studentID
             << "), GPA: " << lowest->GPA << endl;
    }

    void displayStudentsAboveGPA(float threshold) {
        bool found = false;
        cout << "Students with GPA above " << threshold << ":" << endl;
        displayAboveThreshold(root, threshold, found);

        if (!found) {
            cout << "No students found above this threshold." << endl;
        }
    }
};

int main() {
    StudentBST students;

    students.insertStudent(103, "Ali", 3.50f);
    students.insertStudent(101, "Sara", 3.90f);
    students.insertStudent(105, "Ahmed", 2.80f);
    students.insertStudent(102, "Ayesha", 3.20f);
    students.insertStudent(104, "Hamza", 3.75f);

    int choice;
    int id;
    string name;
    float gpa;
    float threshold;

    do {
        cout << "\n===== STUDENT RECORD SYSTEM =====" << endl;
        cout << "1. Insert Student" << endl;
        cout << "2. Search Student by ID" << endl;
        cout << "3. Delete Student by ID" << endl;
        cout << "4. Display Students Sorted by ID" << endl;
        cout << "5. Count Students" << endl;
        cout << "6. Highest and Lowest GPA" << endl;
        cout << "7. Display Students Above GPA Threshold" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting." << endl;
            break;
        }

        switch (choice) {
            case 1:
                cout << "Enter student ID: ";
                cin >> id;

                cout << "Enter student name: ";
                getline(cin >> ws, name);

                cout << "Enter GPA (0.0 to 4.0): ";
                cin >> gpa;

                if (!cin) {
                    cout << "Invalid GPA input." << endl;
                    return 1;
                }

                students.insertStudent(id, name, gpa);
                break;

            case 2:
                cout << "Enter student ID to search: ";
                cin >> id;
                students.searchStudent(id);
                break;

            case 3:
                cout << "Enter student ID to delete: ";
                cin >> id;
                students.deleteStudent(id);
                break;

            case 4:
                students.displayAllStudents();
                break;

            case 5:
                students.displayCount();
                break;

            case 6:
                students.displayGPAExtremes();
                break;

            case 7:
                cout << "Enter GPA threshold: ";
                cin >> threshold;
                students.displayStudentsAboveGPA(threshold);
                break;

            case 0:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
