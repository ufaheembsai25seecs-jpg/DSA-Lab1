#include <iostream>
#include <string>

using namespace std;

class StringPool {
private:
	string* stringpool;
	int currentsize;
	int maxsize;

public: 
	StringPool() {
		maxsize = 5;
		currentsize = 0;
		stringpool = new string[maxsize];
	}

	// Add string function which checks if the current size is less than maxsize and adds the string to the available location
	void addstring(string str) {
		if (currentsize < maxsize) {
			stringpool[currentsize] = str;
			currentsize++;
			cout << str << " Has been added to the string pool" << endl;
		}
		else {
			cout << "The string pool is full. Cannot add" << endl;
		}
	}

	// Remove string function which goes through the array and deletes the string which equals the string we want to delete and then moves everything else to the left 
	void removeString(string str)
	{
		for (int i = 0; i < currentsize; i++)
		{
			if (stringpool[i] == str)
			{

				for (int j = i; j < currentsize - 1; j++)
				{
					stringpool[j] = stringpool[j + 1];
				}

				currentsize--;

				cout << str << " Has been removed" << endl;
				return;
			}
		}

		cout << str << " Wasn't found" << endl;
	}

	// Display function which allows us to be able to see the result of whatever we do in main
	void displayPool()
	{
		cout << "\n--- Pool Status ---" << endl;
		cout << "Current Size: " << currentsize << endl;
		cout << "Maximum Size: " << maxsize << endl;

		cout << "Strings in pool:" << endl;

		for (int i = 0; i < currentsize; i++)
		{
			cout << i << ": " << stringpool[i] << endl;
		}
	}

	// Destructor for the purpose of being able to free memory later 
	~StringPool()
	{
		delete[] stringpool;
		stringpool = nullptr;

		cout << "\nMemory successfully freed." << endl;
	}
};

//	Main function for the testing

int main() {

	StringPool* pool1 = new StringPool(); 

	cout << "--------------WITHOUT FREEING MEMORY--------------" << endl;

	// Adding multiple strings
	pool1->addstring("Unais");
	pool1->addstring("sethi");
	pool1->addstring("moiz");
	pool1->addstring("rishi");
	pool1->addstring("Abdullah");
	pool1->addstring("Minhal");
	pool1->addstring("Mohad");
	

	// Deleting without freeing memory

	pool1 ->removeString("Unais");
	pool1 ->removeString("sethi");

	pool1->displayPool();

	cout << "Memory Leak has been caused" << endl;
	cout << "--------------WITH FREEING MEMORY--------------" << endl;

	StringPool* pool2 = new StringPool();
	// Adding multiple strings
	pool2->addstring("Unais");
	pool2->addstring("sethi");
	pool2->addstring("moiz");
	pool2->addstring("rishi");
	pool2->addstring("Abdullah");
	pool2->addstring("Minhal");
	pool2->addstring("Mohad");


	// Deleting without freeing memory

	pool2->removeString("Unais");
	pool2->removeString("sethi");

	pool2->displayPool();

	delete pool2;
}