#include <iostream>
#include <string>
using namespace std;

// THIS NODE STORES ONE BINARY BIT AND POINTERS TO BOTH SIDES
struct Node {
    int bit;
    Node* next;
    Node* prev;
};

// THIS CLASS HANDLES THE BINARY NUMBER USING A DOUBLY LINKED LIST
class BinaryNumber {
private:
    Node* head;
    Node* tail;

public:

    // START WITH AN EMPTY BINARY NUMBER
    BinaryNumber() {
        head = nullptr;
        tail = nullptr;
    }

    // DELETE ALL NODES WHEN THE OBJECT IS DESTROYED
    ~BinaryNumber() {
        clear();
    }

    // REMOVE ALL BITS FROM THE LIST
    void clear() {
        Node* temp = head;

        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        head = nullptr;
        tail = nullptr;
    }

    // ADD A BIT TO THE END OF THE LIST
    void addBit(int bit) {
        Node* newNode = new Node;

        newNode->bit = bit;
        newNode->next = nullptr;
        newNode->prev = tail;

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // STORE A BINARY NUMBER ENTERED BY THE USER
    void inputBinary() {
        string binary;

        cout << "Enter binary number: ";
        cin >> binary;

        clear();

        // CHECK EACH CHARACTER AND STORE IT AS A SEPARATE NODE
        for (char c : binary) {
            if (c == '0' || c == '1') {
                addBit(c - '0');
            }
            else {
                cout << "Invalid binary number!\n";
                clear();
                return;
            }
        }

        cout << "Binary number stored successfully.\n";
    }

    // CHECK WHETHER THE LIST IS EMPTY
    bool isEmpty() {
        return head == nullptr;
    }

    // RETURN THE NUMBER OF BITS IN THE LIST
    int size() {
        int count = 0;
        Node* temp = head;

        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }

        return count;
    }

    // DISPLAY THE BINARY NUMBER IN 8-BIT GROUPS
    void display() {
        if (head == nullptr) {
            cout << "Binary number is empty.\n";
            return;
        }

        cout << "Binary Number: ";

        Node* temp = head;
        int totalBits = size();

        // ADD LEADING ZEROES SO THE NUMBER IS GROUPED INTO 8-BIT BLOCKS
        int extra = (8 - (totalBits % 8)) % 8;

        for (int i = 0; i < extra; i++) {
            cout << "0";
        }

        int count = extra;

        while (temp != nullptr) {
            cout << temp->bit;
            count++;

            // ADD A SPACE AFTER EVERY 8 BITS
            if (count % 8 == 0 && temp->next != nullptr) {
                cout << " ";
            }

            temp = temp->next;
        }

        cout << endl;
    }

    // MAKE A COPY OF THE CURRENT BINARY NUMBER
    BinaryNumber copy() {
        BinaryNumber result;

        Node* temp = head;

        while (temp != nullptr) {
            result.addBit(temp->bit);
            temp = temp->next;
        }

        return result;
    }

    // 1'S COMPLEMENT MEANS FLIPPING EVERY BIT
    void onesComplement() {
        Node* temp = head;

        while (temp != nullptr) {
            temp->bit = 1 - temp->bit;
            temp = temp->next;
        }
    }

    // ADD ONE TO THE BINARY NUMBER TO GET THE 2'S COMPLEMENT
    void addOne() {
        Node* temp = tail;
        int carry = 1;

        // START FROM THE RIGHTMOST BIT AND ADD ONE
        while (temp != nullptr && carry == 1) {

            if (temp->bit == 0) {
                temp->bit = 1;
                carry = 0;
            }
            else {
                temp->bit = 0;
                carry = 1;
            }

            temp = temp->prev;
        }

        // IF THERE IS STILL A CARRY, ADD A NEW BIT AT THE FRONT
        if (carry == 1) {
            Node* newNode = new Node;

            newNode->bit = 1;
            newNode->prev = nullptr;
            newNode->next = head;

            head->prev = newNode;
            head = newNode;
        }
    }

    // 2'S COMPLEMENT IS CALCULATED BY FLIPPING THE BITS AND THEN ADDING ONE
    void twosComplement() {
        onesComplement();
        addOne();
    }

    // ADD A ZERO TO THE RIGHT SIDE TO PERFORM A LEFT SHIFT
    void leftShift() {
        if (head == nullptr)
            return;

        addBit(0);
    }

    // REMOVE LEADING ZEROES WHILE KEEPING AT LEAST ONE BIT
    void removeLeadingZeroes() {
        while (head != nullptr &&
               head != tail &&
               head->bit == 0) {

            Node* temp = head;
            head = head->next;

            head->prev = nullptr;

            delete temp;
        }
    }

    // BINARY ADDITION USING THE DLL
    BinaryNumber add(BinaryNumber& other) {

        BinaryNumber result;

        Node* p = tail;
        Node* q = other.tail;

        int carry = 0;

        // ADD BOTH NUMBERS FROM RIGHT TO LEFT
        while (p != nullptr || q != nullptr || carry != 0) {

            int bit1 = 0;
            int bit2 = 0;

            if (p != nullptr) {
                bit1 = p->bit;
                p = p->prev;
            }

            if (q != nullptr) {
                bit2 = q->bit;
                q = q->prev;
            }

            // CALCULATE THE SUM OF THE TWO BITS AND THE CARRY
            int sum = bit1 + bit2 + carry;

            int resultBit = sum % 2;
            carry = sum / 2;

            // ADD THE RESULT TO THE FRONT OF THE LIST
            Node* newNode = new Node;

            newNode->bit = resultBit;
            newNode->prev = nullptr;
            newNode->next = result.head;

            if (result.head != nullptr) {
                result.head->prev = newNode;
            }
            else {
                result.tail = newNode;
            }

            result.head = newNode;
        }

        return result;
    }

    // BINARY MULTIPLICATION USING REPEATED ADDITION AND LEFT SHIFTING
    BinaryNumber multiply(BinaryNumber& other) {

        BinaryNumber result;
        result.addBit(0);

        // START FROM THE RIGHTMOST BIT OF THE SECOND NUMBER
        Node* multiplier = other.tail;

        BinaryNumber shifted = copy();

        // CHECK EACH BIT OF THE MULTIPLIER
        while (multiplier != nullptr) {

            // IF THE CURRENT MULTIPLIER BIT IS 1, ADD THE SHIFTED VALUE
            if (multiplier->bit == 1) {
                result = result.add(shifted);
            }

            // MOVE TO THE NEXT BIT TO THE LEFT
            multiplier = multiplier->prev;

            // SHIFT THE MULTIPLICAND LEFT FOR THE NEXT POSITION
            if (multiplier != nullptr) {
                shifted.leftShift();
            }
        }

        result.removeLeadingZeroes();

        return result;
    }

    // CONVERT THE BINARY NUMBER INTO A DECIMAL INTEGER
    unsigned long long toDecimal() {

        unsigned long long decimal = 0;

        Node* temp = head;

        while (temp != nullptr) {

            // SHIFT THE CURRENT VALUE LEFT AND ADD THE NEW BIT
            decimal = decimal * 2 + temp->bit;

            temp = temp->next;
        }

        return decimal;
    }
};

int main() {

    BinaryNumber binary1;
    BinaryNumber binary2;

    int choice;

    do {
        cout << "\n========================================\n";
        cout << "       BINARY ARITHMETIC USING DLL\n";
        cout << "========================================\n";
        cout << "1. Store Binary Number\n";
        cout << "2. Display Binary Number\n";
        cout << "3. 1's Complement\n";
        cout << "4. 2's Complement\n";
        cout << "5. Binary Addition\n";
        cout << "6. Binary Multiplication\n";
        cout << "7. Convert To Decimal\n";
        cout << "8. Exit\n";
        cout << "========================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // ASK THE USER WHICH BINARY NUMBER SHOULD BE STORED
            int numberChoice;

            cout << "\n1. Store Binary Number 1\n";
            cout << "2. Store Binary Number 2\n";
            cout << "Enter choice: ";
            cin >> numberChoice;

            if (numberChoice == 1) {
                binary1.inputBinary();
            }
            else if (numberChoice == 2) {
                binary2.inputBinary();
            }
            else {
                cout << "Invalid choice!\n";
            }

            break;

        case 2:
            // DISPLAY BOTH STORED BINARY NUMBERS
            cout << "\nBinary Number 1:\n";
            binary1.display();

            cout << "Binary Number 2:\n";
            binary2.display();

            break;

        case 3:
            // APPLY 1'S COMPLEMENT TO THE SELECTED NUMBER
            cout << "\n1. Complement Binary Number 1\n";
            cout << "2. Complement Binary Number 2\n";
            cout << "Enter choice: ";
            cin >> numberChoice;

            if (numberChoice == 1) {
                binary1.onesComplement();
                cout << "1's Complement: ";
                binary1.display();
            }
            else if (numberChoice == 2) {
                binary2.onesComplement();
                cout << "1's Complement: ";
                binary2.display();
            }
            else {
                cout << "Invalid choice!\n";
            }

            break;

        case 4:
            // APPLY 2'S COMPLEMENT TO THE SELECTED NUMBER
            cout << "\n1. Complement Binary Number 1\n";
            cout << "2. Complement Binary Number 2\n";
            cout << "Enter choice: ";
            cin >> numberChoice;

            if (numberChoice == 1) {
                binary1.twosComplement();
                cout << "2's Complement: ";
                binary1.display();
            }
            else if (numberChoice == 2) {
                binary2.twosComplement();
                cout << "2's Complement: ";
                binary2.display();
            }
            else {
                cout << "Invalid choice!\n";
            }

            break;

        case 5:
            // ADD THE TWO STORED BINARY NUMBERS
            if (binary1.isEmpty() || binary2.isEmpty()) {
                cout << "Please store both binary numbers first.\n";
            }
            else {
                BinaryNumber sum = binary1.add(binary2);

                cout << "\nBinary Number 1: ";
                binary1.display();

                cout << "Binary Number 2: ";
                binary2.display();

                cout << "Sum: ";
                sum.display();
            }

            break;

        case 6:
            // MULTIPLY THE TWO STORED BINARY NUMBERS
            if (binary1.isEmpty() || binary2.isEmpty()) {
                cout << "Please store both binary numbers first.\n";
            }
            else {
                BinaryNumber product = binary1.multiply(binary2);

                cout << "\nBinary Number 1: ";
                binary1.display();

                cout << "Binary Number 2: ";
                binary2.display();

                cout << "Product: ";
                product.display();
            }

            break;

        case 7:
            // CONVERT THE SELECTED BINARY NUMBER INTO DECIMAL
            cout << "\n1. Convert Binary Number 1\n";
            cout << "2. Convert Binary Number 2\n";
            cout << "Enter choice: ";
            cin >> numberChoice;

            if (numberChoice == 1) {

                if (binary1.isEmpty()) {
                    cout << "Binary Number 1 is empty.\n";
                }
                else {
                    cout << "Binary: ";
                    binary1.display();

                    cout << "Decimal: "
                         << binary1.toDecimal() << endl;
                }
            }
            else if (numberChoice == 2) {

                if (binary2.isEmpty()) {
                    cout << "Binary Number 2 is empty.\n";
                }
                else {
                    cout << "Binary: ";
                    binary2.display();

                    cout << "Decimal: "
                         << binary2.toDecimal() << endl;
                }
            }
            else {
                cout << "Invalid choice!\n";
            }

            break;

        case 8:
            // END THE PROGRAM
            cout << "Exiting program...\n";
            break;

        default:
            // HANDLE AN INVALID MENU OPTION
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}
S