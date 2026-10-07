#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Creating a linked list called Node with a char data and a pointer called next 

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

    // Checking if the stack is empty by seeing if the top node is pointed to the null ptr

    bool isEmpty()
    {
        return topNode == nullptr;
    }

    // A function that is used to push values onto the stack

    void push(char value)
    {
        Node* newNode = new Node;

        newNode->data = value;
        newNode->next = topNode;

        topNode = newNode;
    }

    // Funtion used to pop the elements from the stack if the stack isn't already empty

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

    // Function that returns the value at the top of the stack

    char top()
    {
        if (isEmpty())
        {
            return '\0';
        }

        return topNode->data;
    }

    // Function that runs the pop function in a loop until the stack is empty

    void clear()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    // DESTRUCTOR
    ~Stack()
    {
        clear();
    }
};


// Creating another linked list called NumberNode with data of datatype double and a pointer 

struct NumberNode
{
    double data;
    NumberNode* next;
};

// Creating a second stack called NumberStack that will now be using the struct NumberNode

// The same functions will be created for this as had been created for the previous stack

class NumberStack
{
private:
    NumberNode* topNode;

public:
    NumberStack()
    {
        topNode = nullptr;
    }

    bool isEmpty()
    {
        return topNode == nullptr;
    }

    void push(double value)
    {
        NumberNode* newNode = new NumberNode;

        newNode->data = value;
        newNode->next = topNode;

        topNode = newNode;
    }

    double pop()
    {
        if (isEmpty())
        {
            return 0;
        }

        NumberNode* temp = topNode;

        double value = topNode->data;

        topNode = topNode->next;

        delete temp;

        return value;
    }

    void clear()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    ~NumberStack()
    {
        clear();
    }
};

// helper function to check if something is an operator or not

bool isOperator(char ch)
{
    return ch == '+' ||
           ch == '-' ||
           ch == '*' ||
           ch == '/' ||
           ch == '%';
}

// Another helper function that will check the precendence of an operator

int precedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }

    if (op == '*' || op == '/' || op == '%')
    {
        return 2;
    }

    return 0;
}


// Funtion to check is a specific mathematical expression is valid or not

bool isValidExpression(string expression)
{
    if (expression.empty())
    {
        return false;
    }

    bool expectingOperand = true;

    int bracketCount = 0;

    for (int i = 0; i < expression.length(); i++)
    {
        char ch = expression[i];

        if (ch == ' ')
        {
            continue;
        }

        if (isdigit(ch))
        {
            expectingOperand = false;
        }
        else if (ch == '(')
        {
            bracketCount++;
            expectingOperand = true;
        }
        else if (ch == ')')
        {
            if (bracketCount == 0)
            {
                return false;
            }

            if (expectingOperand)
            {
                return false;
            }

            bracketCount--;
            expectingOperand = false;
        }
        else if (isOperator(ch))
        {
            if (expectingOperand)
            {
                return false;
            }

            expectingOperand = true;
        }
        else
        {
            return false;
        }
    }

    if (bracketCount != 0)
    {
        return false;
    }

    if (expectingOperand)
    {
        return false;
    }

    return true;
}



string infixToPostfix(string expression)
{
    Stack operators;

    string postfix = "";

    for (int i = 0; i < expression.length(); i++)
    {
        char ch = expression[i];

        if (ch == ' ')
        {
            continue;
        }

        if (isdigit(ch))
        {
            postfix += ch;
            postfix += ' ';
        }
        else if (ch == '(')
        {
            operators.push(ch);
        }
        else if (ch == ')')
        {
            while (!operators.isEmpty() &&
                   operators.top() != '(')
            {
                postfix += operators.pop();
                postfix += ' ';
            }

            if (!operators.isEmpty() &&
                operators.top() == '(')
            {
                operators.pop();
            }
        }
        else if (isOperator(ch))
        {
            while (!operators.isEmpty() &&
                   operators.top() != '(' &&
                   precedence(operators.top()) >= precedence(ch))
            {
                postfix += operators.pop();
                postfix += ' ';
            }

            operators.push(ch);
        }
    }

    while (!operators.isEmpty())
    {
        postfix += operators.pop();
        postfix += ' ';
    }

    return postfix;
}


double applyOperation(double a, double b, char op, bool& valid)
{
    if (op == '+')
    {
        return a + b;
    }

    if (op == '-')
    {
        return a - b;
    }

    if (op == '*')
    {
        return a * b;
    }

    if (op == '/')
    {
        if (b == 0)
        {
            valid = false;
            return 0;
        }

        return a / b;
    }

    if (op == '%')
    {
        if (b == 0)
        {
            valid = false;
            return 0;
        }

        return static_cast<int>(a) % static_cast<int>(b);
    }

    valid = false;
    return 0;
}


double evaluatePostfix(string postfix, bool& valid)
{
    NumberStack numbers;

    valid = true;

    for (int i = 0; i < postfix.length(); i++)
    {
        char ch = postfix[i];

        if (ch == ' ')
        {
            continue;
        }

        if (isdigit(ch))
        {
            numbers.push(ch - '0');
        }
        else if (isOperator(ch))
        {
            if (numbers.isEmpty())
            {
                valid = false;
                return 0;
            }

            double b = numbers.pop();

            if (numbers.isEmpty())
            {
                valid = false;
                return 0;
            }

            double a = numbers.pop();

            double result = applyOperation(a, b, ch, valid);

            if (!valid)
            {
                return 0;
            }

            numbers.push(result);
        }
    }

    if (numbers.isEmpty())
    {
        valid = false;
        return 0;
    }

    double result = numbers.pop();

    if (!numbers.isEmpty())
    {
        valid = false;
        return 0;
    }

    return result;
}


// --------------------------------------TEST CASES------------------------------------ 
int main()
{
    string expressions[] =
    {
        "2 + 3 * 4",
        "(2 + 3) * 4",
        "10 + 2 * 6",
        "(10 + 2) * (6 - 3)",
        "20 / 5 + 3"
    };

    int size = 5;

    cout << "Infix to Postfix Conversion and Evaluation" << endl;
    cout << "===========================================" << endl;

    for (int i = 0; i < size; i++)
    {
        cout << "\nExpression: "
             << expressions[i] << endl;

        if (!isValidExpression(expressions[i]))
        {
            cout << "Invalid expression." << endl;
            continue;
        }

        string postfix = infixToPostfix(expressions[i]);

        cout << "Postfix: " << postfix << endl;

        bool valid;

        double result = evaluatePostfix(postfix, valid);

        if (!valid)
        {
            cout << "Invalid expression or division by zero." << endl;
        }
        else
        {
            cout << "Result: " << result << endl;
        }
    }

    return 0;
}