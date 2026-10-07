#include <iostream>
#include <string>
using namespace std;

// Creating a linked list called Node with some character data and a pointer

struct Node
{
    char data;
    Node* next;
};

// Creating a class called stack

class Stack
{

private:
    Node* topNode;


public:
    Stack()
    {
        topNode = nullptr;
    }

    // Function within the class Stack that will push the value onto the stack

    void push(char value)
    {
        Node* newNode = new Node;

        newNode->data = value;
        newNode->next = topNode;

        topNode = newNode;
    }


    // Function within the class Stack that will pop the value from the stack

    char pop()
    {
        if (isEmpty())
        {
            return '\0';
        }

        Node* temp = topNode;
        char value = topNode->data;

        topNode = topNode->next;

        delete temp;

        return value;
    }

    // Function That finds the element at the top of the stack

    char top()
    {
        if (isEmpty())
        {
            return '\0';
        }

        return topNode->data;
    }

    // Function that checks if the stack is empty

    bool isEmpty()
    {
        return topNode == nullptr;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return;
        }

        Node* current = topNode;

        cout << "Stack: ";

        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }

    // Function to clears the stack of all the values

    void clear()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    bool checkBalance(string expression)
    {
        clear();

        for (int i = 0; i < expression.length(); i++)
        {
            char current = expression[i];

            if (current == '(' || current == '[' || current == '{')
            {
                push(current);
            }
            else if (current == ')' || current == ']' || current == '}')
            {
                if (isEmpty())
                {
                    return false;
                }

                char opening = pop();

                if (current == ')' && opening != '(')
                {
                    clear();
                    return false;
                }

                if (current == ']' && opening != '[')
                {
                    clear();
                    return false;
                }

                if (current == '}' && opening != '{')
                {
                    clear();
                    return false;
                }
            }
        }

        bool balanced = isEmpty();

        clear();

        return balanced;
    }

    ~Stack()
    {
        clear();
    }
};


// --------------------------- TEST CASES ----------------------------------------
int main()
{
    Stack stack;

    string expressions[] =
    {
        "(A+B)",
        "{A+[B*C]}",
        "(A+B]",
        "((A+B)",
        "{[()]}",
        "A+B*C",
        "([A+B])"
    };

    int size = 7;

    cout << "Expression Parentheses Checker" << endl;
    cout << "================================" << endl;

    for (int i = 0; i < size; i++)
    {
        cout << expressions[i] << " -> ";

        if (stack.checkBalance(expressions[i]))
        {
            cout << "Balanced" << endl;
        }
        else
        {
            cout << "Not Balanced" << endl;
        }
    }

    return 0;
}