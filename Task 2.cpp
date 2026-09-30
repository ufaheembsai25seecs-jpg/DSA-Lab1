```cpp
#include <iostream>
using namespace std;

// THIS NODE STORES ONE PERSON'S ID AND THE LINK TO THE NEXT PERSON
struct Node {
    int id;
    Node* next;
};

// THIS FUNCTION CREATES THE CIRCULAR LINKED LIST WITH N PEOPLE
Node* createList(int N) {
    Node* head = nullptr;
    Node* tail = nullptr;

    // ADD EACH PERSON TO THE LIST ONE BY ONE
    for (int i = 1; i <= N; i++) {
        Node* newNode = new Node;

        newNode->id = i;
        newNode->next = nullptr;

        // IF THIS IS THE FIRST PERSON, MAKE IT THE HEAD
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            // ADD THE NEW PERSON AFTER THE CURRENT LAST PERSON
            tail->next = newNode;
            tail = newNode;
        }
    }

    // CONNECT THE LAST PERSON BACK TO THE FIRST PERSON
    // THIS MAKES THE LINKED LIST CIRCULAR
    tail->next = head;

    return head;
}

// THIS FUNCTION DISPLAYS EVERY PERSON IN THE CIRCLE
void displayList(Node* head) {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    Node* temp = head;

    cout << "People in the circle: ";

    // KEEP MOVING UNTIL WE REACH THE HEAD AGAIN
    do {
        cout << temp->id << " ";
        temp = temp->next;
    } while (temp != head);

    cout << endl;
}

// THIS FUNCTION SIMULATES THE JOSEPHUS PROBLEM
void josephus(int N, int k) {

    // CREATE THE CIRCULAR LIST OF PEOPLE
    Node* head = createList(N);

    // FIND THE LAST PERSON SO WE CAN KEEP TRACK OF THE PREVIOUS NODE
    Node* previous = head;

    while (previous->next != head) {
        previous = previous->next;
    }

    Node* current = head;

    cout << "\nElimination Order:\n";

    // KEEP ELIMINATING PEOPLE UNTIL ONLY ONE PERSON IS LEFT
    while (current->next != current) {

        // MOVE K-1 STEPS BECAUSE THE CURRENT PERSON COUNTS AS THE FIRST STEP
        for (int count = 1; count < k; count++) {
            previous = current;
            current = current->next;
        }

        // DISPLAY THE PERSON WHO IS ABOUT TO BE REMOVED
        cout << "Person " << current->id << " is eliminated.\n";

        // SKIP OVER THE PERSON BEING REMOVED
        previous->next = current->next;

        // SAVE THE NODE, MOVE TO THE NEXT PERSON, AND THEN DELETE THE OLD NODE
        Node* temp = current;
        current = current->next;

        delete temp;
    }

    // THE ONLY PERSON LEFT IN THE CIRCLE IS THE SURVIVOR
    cout << "\nSurvivor: Person " << current->id << endl;

    // FREE THE MEMORY USED BY THE LAST REMAINING NODE
    delete current;
}

int main() {

    int N, k;

    // ASK THE USER HOW MANY PEOPLE ARE IN THE CIRCLE
    cout << "Enter number of people (N): ";
    cin >> N;

    // ASK THE USER FOR THE NUMBER OF STEPS USED FOR ELIMINATION
    cout << "Enter step count (k): ";
    cin >> k;

    // MAKE SURE THE USER ENTERS VALID POSITIVE VALUES
    if (N <= 0 || k <= 0) {
        cout << "N and k must be greater than 0.\n";
        return 0;
    }

    // CREATE THE LIST SO WE CAN SHOW THE INITIAL CIRCLE
    Node* head = createList(N);

    cout << endl;
    displayList(head);

    // DELETE THE TEMPORARY LIST BEFORE RUNNING THE ACTUAL SIMULATION
    Node* temp = head->next;

    while (temp != head) {
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    delete head;

    // RUN THE JOSEPHUS SIMULATION
    josephus(N, k);

    return 0;
}
```
