#include <iostream>
#include <string>
using namespace std;

// Creating a linked list called Node 
struct Node
{
    int jobID;
    string documentName;
    int pages;

    Node* next;
};

// Creating a class called Queue

class Queue
{
private:
    Node* front;
    Node* rear;


public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
    }

    // Function to check if the queue is empty

    bool isEmpty()
    {
        return front == nullptr;
    }

    // A function to add a job to the queue. It adds whatever is in the Node Linked list to the queue 

    void addJob(int id, string name, int numberOfPages)
    {
        Node* newNode = new Node;

        newNode->jobID = id;
        newNode->documentName = name;
        newNode->pages = numberOfPages;
        newNode->next = nullptr;

        if (isEmpty())
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        cout << "Job " << id << " added successfully." << endl;
    }

    // A function to process a job if the queue is not empty 

    void processJob()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. No job to process." << endl;
            return;
        }

        Node* temp = front;

        cout << "Processing Job " << temp->jobID
             << " (" << temp->documentName
             << ", " << temp->pages << " pages)" << endl;

        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temp;
    }

    // A function to view the next node and printing on the screen whatever has been seen 

    void viewNextJob()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. No next job." << endl;
            return;
        }

        cout << "Next Job:" << endl;
        cout << "Job ID: " << front->jobID << endl;
        cout << "Document: " << front->documentName << endl;
        cout << "Pages: " << front->pages << endl;
    }

    // A function to display the elements in the queue

    void displayQueue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return;
        }

        Node* current = front;

        cout << "\nPrinter Queue" << endl;
        cout << "-------------" << endl;

        while (current != nullptr)
        {
            cout << "Job ID: " << current->jobID
                 << " | Document: " << current->documentName
                 << " | Pages: " << current->pages << endl;

            current = current->next;
        }
    }


    // A function to count the jobs

    int countJobs()
    {
        int count = 0;

        Node* current = front;

        while (current != nullptr)
        {
            count++;
            current = current->next;
        }

        return count;
    }

    void clearQueue()
    {
        while (!isEmpty())
        {
            Node* temp = front;

            front = front->next;

            delete temp;
        }

        rear = nullptr;
    }

    ~Queue()
    {
        clearQueue();
    }
};


// -----------------------------------TEST CASES--------------------------------------

int main()
{
    Queue printerQueue;

    cout << "Printer Job Scheduling" << endl;
    cout << "======================" << endl;

    printerQueue.addJob(101, "Assignment1.pdf", 10);
    printerQueue.addJob(102, "Report.docx", 25);
    printerQueue.addJob(103, "Notes.pdf", 5);
    printerQueue.addJob(104, "LabTask.docx", 15);

    cout << "\n1. Display All Jobs" << endl;
    printerQueue.displayQueue();

    cout << "\nNumber of Jobs: "
         << printerQueue.countJobs() << endl;

    cout << "\n2. Process Two Jobs" << endl;
    printerQueue.processJob();
    printerQueue.processJob();

    cout << "\n3. Display Remaining Jobs" << endl;
    printerQueue.displayQueue();

    cout << "\n4. Add a New Job" << endl;
    printerQueue.addJob(105, "Project.pdf", 20);

    cout << "\n5. Display Next Job" << endl;
    printerQueue.viewNextJob();

    cout << "\n6. Process All Remaining Jobs" << endl;

    while (!printerQueue.isEmpty())
    {
        printerQueue.processJob();
    }

    cout << "\n7. Attempt to Process From Empty Queue" << endl;
    printerQueue.processJob();

    return 0;
}