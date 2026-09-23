#include <iostream>
using namespace std;

// Creating a node structure which has data and a pointer to the next node
struct Node
{
    int data;
    Node* next;
};

// Inserting a node at the head of the linked list
void insertAtHead(Node*& head, int value)
{
    Node* newNode = new Node;

    newNode->data = value;
    newNode->next = head;

    head = newNode;

    cout << value << " inserted at the head.\n";
}

// Creating a function to insert a node at the third position as required in the document
void insertAtThird(Node*& head, int value)
{
    // Case in which the linked list has fewer than 2 nodes
    if (head == nullptr || head->next == nullptr)
    {
        cout << "Cannot insert at the 3rd position.\n";
        cout << "The list has fewer than 2 nodes.\n";
        return;
    }

    Node* newNode = new Node;

    newNode->data = value;

    // Moving to the second node
    Node* current = head->next;

    // Inserting a new node after the second position
    newNode->next = current->next;
    current->next = newNode;

    cout << value << " inserted at the 3rd position.\n";
}

// Funtion created for the purpose of displaying a linked list
void displayList(Node* head)
{
    if (head == nullptr)
    {
        cout << "List is empty.\n";
        return;
    }

    Node* current = head;

    while (current != nullptr)
    {
        cout << current->data << " -> ";
        current = current->next;
    }

    cout << "NULL\n";
}

// Creating a function to delete the last node as required by the document
void deleteLast(Node*& head)
{
    // Empty list
    if (head == nullptr)
    {
        cout << "List is empty. Nothing to delete.\n";
        return;
    }

    // In case that there is only one node we will need to point the head to nullptr after deletion
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;

        cout << "Last node deleted.\n";
        return;
    }

    // Traversing until the second-last node
    Node* current = head;

    while (current->next->next != nullptr)
    {
        current = current->next;
    }

    // current node is now the second last node
    delete current->next;

    current->next = nullptr;

    cout << "Last node deleted.\n";
}

// Funtion to count the number of nodes as highlighted in the document
int countNodes(Node* head)
{
    int count = 0;

    Node* current = head;

    while (current != nullptr)
    {
        count++;
        current = current->next;
    }

    return count;
}

// Funtion to reverse the linked list iteratilvely as highlited by the document
void reverseList(Node*& head)
{
    Node* previous = nullptr;
    Node* current = head;
    Node* nextNode = nullptr;

    while (current != nullptr)
    {
       
        nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    // Previous becomes the new head
    head = previous;

    cout << "Linked list reversed successfully.\n";
}

// Search for a value
void searchValue(Node* head, int value)
{
    Node* current = head;

    int position = 1;

    while (current != nullptr)
    {
        if (current->data == value)
        {
            cout << value << " found at position "
                << position << ".\n";
            return;
        }

        current = current->next;
        position++;
    }

    cout << value << " was not found in the list.\n";
}

// Free all memory before program exits
void deleteList(Node*& head)
{
    Node* current = head;

    while (current != nullptr)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
}

// Main function creating the menu for all the functions that we have created 
int main()
{
    Node* head = nullptr;

    int choice;
    int value;

    do
    {
        cout << "\n====================================\n";
        cout << "       SINGLY LINKED LIST MENU\n";
        cout << "====================================\n";
        cout << "1. Insert at Head\n";
        cout << "2. Insert at 3rd Position\n";
        cout << "3. Display List\n";
        cout << "4. Delete Last Node\n";
        cout << "5. Count Nodes\n";
        cout << "6. Reverse List\n";
        cout << "7. Search Value\n";
        cout << "8. Exit\n";
        cout << "====================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;

            insertAtHead(head, value);
            break;

        case 2:
            cout << "Enter value: ";
            cin >> value;

            insertAtThird(head, value);
            break;

        case 3:
            cout << "\nLinked List:\n";
            displayList(head);
            break;

        case 4:
            deleteLast(head);

            cout << "Updated List:\n";
            displayList(head);
            break;

        case 5:
            cout << "Number of nodes: "
                << countNodes(head) << endl;
            break;

        case 6:
            reverseList(head);

            cout << "Updated List:\n";
            displayList(head);
            break;

        case 7:
            cout << "Enter value to search: ";
            cin >> value;

            searchValue(head, value);
            break;

        case 8:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 8);

    // Free dynamically allocated memory
    deleteList(head);

    return 0;
}