
// BST is going to be used as the base of the student record because it allows us to get to any student in a lower amount of time
// A stack is going to be used for the search history because it allows us to take out the most recent search from the top of the stack

// Time complexity for BST is O(h) for searching where h is the height of the tree
// Time complexity for BST is O(h) for inserting where h is the height of the tree 
// Time complexity for a stack is O(1) for inserting, deleting, peeking and checking if it is empty.
// Time complexity for a stack when it comes to traversal is O(n)
 
#include <iostream>
#include <string>
#include <stack>
using namespace std;

stack <int> st;

// A structure for the Student BST
struct Student {
    int rollNumber;
    string name;
    Student* left;
    Student* right;

};


// The function to create the node for the BST    
Student* createStudent(int rollNumber, string name)
{
    Student* newStudent = new Student;

    newStudent->rollNumber = rollNumber;
    newStudent->name = name;
    newStudent->left = NULL;
    newStudent->right = NULL;

    return newStudent;
}



// Inserting a Student into the BST
Student* insertStudent(Student* root, int rollNumber, string name)
{
    if (root == NULL)
    {
        cout << "\nStudent added successfully!\n";
        return createStudent(rollNumber, name);
    }

    if (rollNumber < root->rollNumber)
    {
        root->left = insertStudent(root->left, rollNumber, name);
    }
    else if (rollNumber > root->rollNumber)
    {
        root->right = insertStudent(root->right, rollNumber, name);
    }
    else
    {
        cout << "\nError! Roll number already exists.\n";
    }

    return root;
}



// Searching an Item in BST

Student* searchStudent(Student* root, int rollNumber)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->rollNumber == rollNumber)
    {
        return root;
    }

    if (rollNumber < root->rollNumber)
    {
        return searchStudent(root->left, rollNumber);
    }

    return searchStudent(root->right, rollNumber);
}


// Displaying all the items in the BST

void displayStudents(Student* root)
{
    if (root == NULL)
    {
        return;
    }

    displayStudents(root->left);

    cout << "Roll Number: " << root->rollNumber
         << " | Name: " << root->name << endl;

    displayStudents(root->right);
}


// The Implementation below is for the stack using the built in stack library in c++


// Display Search History
void displayHistory(stack<int> history)
{
    if (history.empty())
    {
        cout << "\nSearch history is empty!\n";
        return;
    }

    cout << "\nSEARCH HISTORY\n";

    int position = 1;

    while (!history.empty())
    {
        cout << position << ". Roll Number: "
             << history.top() << endl;

        history.pop();
        position++;
    }

    cout << "\n";
}

// Remove Most Recent Search
void removeHistory(stack<int>& history)
{
    if (history.empty())
    {
        cout << "\nSearch history is empty!\n";
        return;
    }

    cout << "\nRemoved Roll Number: "
         << history.top() << endl;

    history.pop();

    cout << "History entry removed successfully!\n";
}

// Search History Menu
void historyMenu(stack<int>& history)
{
    int choice;

    do
    {
        cout << "\nSEARCH HISTORY MENU \n";
        cout << "1. Display Search History\n";
        cout << "2. Remove Most Recent Search\n";
        cout << "3. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                displayHistory(history);
                break;

            case 2:
                removeHistory(history);
                break;

            case 3:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 3);
}

// Free all BST nodes
void deleteBST(Student* root)
{
    if (root == NULL)
    {
        return;
    }

    deleteBST(root->left);
    deleteBST(root->right);

    delete root;
}



int main() 
{
    Student* root = NULL;

    // Built-in STL Stack
    stack<int> history;

    int choice;
    int rollNumber;
    string name;

    do
    {
        cout << "\nSTUDENT HELP DESK\n";
        cout << "1. Add Student\n";
        cout << "2. Search Student\n";
        cout << "3. Display All Students\n";
        cout << "4. Manage Search History\n";
        cout << "5. Exit\n";
        

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cout << "\nEnter Student Roll Number: ";
                cin >> rollNumber;

                // Check for duplicate roll number
                if (searchStudent(root, rollNumber) != NULL)
                {
                    cout << "\nError! Roll number already exists.\n";
                    break;
                }

                cout << "Enter Student Name: ";
                cin.ignore();
                getline(cin, name);

                root = insertStudent(root, rollNumber, name);

                break;
            }

            case 2:
            {
                cout << "\nEnter Roll Number to Search: ";
                cin >> rollNumber;

                Student* result = searchStudent(root, rollNumber);

                if (result != NULL)
                {
                    cout << "\nStudent Found!\n";
                    cout << "Roll Number: " << result->rollNumber << endl;
                    cout << "Name: " << result->name << endl;

                    // Add successful search to stack
                    history.push(rollNumber);

                    cout << "Search added to history!\n";
                }
                else
                {
                    cout << "\nStudent Not Found!\n";
                }

                break;
            }

            case 3:
            {
                if (root == NULL)
                {
                    cout << "\nNo student records available!\n";
                }
                else
                {
                    cout << "\nALL STUDENT RECORDS\n";

                    displayStudents(root);

                
                }

                break;
            }

            case 4:
            {
                historyMenu(history);
                break;
            }

            case 5:
            {
                cout << "\nExiting Student Help Desk...\n";
                break;
            }

            default:
            {
                cout << "\nInvalid choice! Please try again.\n";
            }
        }

    } while (choice != 5);

    // Release dynamically allocated BST memory
    deleteBST(root);

    cout << "\nMemory released successfully.\n";
    cout << "Program terminated successfully.\n";

    return 0;

}