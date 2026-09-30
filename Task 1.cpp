```cpp
#include <iostream>
#include <string>
using namespace std;

// THIS NODE HOLDS ALL THE INFORMATION ABOUT ONE SONG
struct Song {
    int id;
    string name;
    string duration;

    Song* prev;
    Song* next;
};

// THIS CLASS MANAGES THE ENTIRE PLAYLIST
class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;   // THIS KEEPS TRACK OF THE SONG THAT IS CURRENTLY PLAYING

public:

    // START WITH AN EMPTY PLAYLIST
    Playlist() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    // THIS FUNCTION ADDS A NEW SONG AT THE END OF THE PLAYLIST
    void addSong() {
        Song* newSong = new Song;

        cout << "Enter Song ID: ";
        cin >> newSong->id;

        cin.ignore();

        cout << "Enter Song Name: ";
        getline(cin, newSong->name);

        cout << "Enter Duration (mm:ss): ";
        cin >> newSong->duration;

        // THE NEW SONG WILL INITIALLY NOT POINT TO ANYTHING AFTER IT
        newSong->next = nullptr;

        // THE NEW SONG WILL POINT BACK TO THE CURRENT LAST SONG
        newSong->prev = tail;

        // IF THE PLAYLIST IS EMPTY, THIS SONG BECOMES THE FIRST AND LAST SONG
        if (head == nullptr) {
            head = newSong;
            tail = newSong;
            current = newSong;
        }
        else {
            // CONNECT THE OLD LAST SONG TO THE NEW SONG
            tail->next = newSong;

            // MOVE THE TAIL TO THE NEW LAST SONG
            tail = newSong;
        }

        cout << "Song added successfully!\n";
    }

    // THIS FUNCTION FINDS A SONG BY ID AND REMOVES IT FROM THE PLAYLIST
    void deleteSong() {
        int id;

        cout << "Enter Song ID to delete: ";
        cin >> id;

        Song* temp = head;

        // KEEP MOVING FORWARD UNTIL WE FIND THE SONG OR REACH THE END
        while (temp != nullptr && temp->id != id) {
            temp = temp->next;
        }

        // IF TEMP IS NULL, THE SONG DOES NOT EXIST
        if (temp == nullptr) {
            cout << "Song not found!\n";
            return;
        }

        // IF WE ARE DELETING THE CURRENT SONG, MOVE THE PLAYER TO ANOTHER SONG
        if (current == temp) {
            if (temp->next != nullptr)
                current = temp->next;
            else
                current = temp->prev;
        }

        // CONNECT THE PREVIOUS SONG TO THE NEXT SONG
        if (temp->prev != nullptr)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        // CONNECT THE NEXT SONG BACK TO THE PREVIOUS SONG
        if (temp->next != nullptr)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        // REMOVE THE SONG FROM MEMORY
        delete temp;

        // IF THERE ARE NO SONGS LEFT, RESET THE CURRENT POINTER
        if (head == nullptr)
            current = nullptr;

        cout << "Song deleted successfully!\n";
    }

    // THIS FUNCTION DISPLAYS THE PLAYLIST FROM THE FIRST SONG TO THE LAST
    void displayForward() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        Song* temp = head;

        cout << "\n--- PLAYLIST FORWARD ---\n";

        // MOVE FORWARD USING THE NEXT POINTER
        while (temp != nullptr) {

            cout << "ID: " << temp->id
                 << " | Name: " << temp->name
                 << " | Duration: " << temp->duration;

            // MARK THE SONG THAT IS CURRENTLY BEING PLAYED
            if (temp == current)
                cout << "  <-- CURRENTLY PLAYING";

            cout << endl;

            temp = temp->next;
        }
    }

    // THIS FUNCTION DISPLAYS THE PLAYLIST FROM THE LAST SONG BACK TO THE FIRST
    void displayBackward() {
        if (tail == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        Song* temp = tail;

        cout << "\n--- PLAYLIST BACKWARD ---\n";

        // MOVE BACKWARD USING THE PREV POINTER
        while (temp != nullptr) {

            cout << "ID: " << temp->id
                 << " | Name: " << temp->name
                 << " | Duration: " << temp->duration;

            // MARK THE SONG THAT IS CURRENTLY BEING PLAYED
            if (temp == current)
                cout << "  <-- CURRENTLY PLAYING";

            cout << endl;

            temp = temp->prev;
        }
    }

    // THIS FUNCTION SEARCHES FOR A SONG USING ITS ID
    void searchSong() {
        int id;

        cout << "Enter Song ID to search: ";
        cin >> id;

        Song* temp = head;

        // CHECK EACH SONG UNTIL THE REQUIRED ID IS FOUND
        while (temp != nullptr) {

            if (temp->id == id) {
                cout << "\n--- SONG FOUND ---\n";
                cout << "Song ID: " << temp->id << endl;
                cout << "Song Name: " << temp->name << endl;
                cout << "Duration: " << temp->duration << endl;

                return;
            }

            temp = temp->next;
        }

        cout << "Song not found!\n";
    }

    // THIS FUNCTION MOVES THE PLAYER TO THE NEXT SONG
    void playNext() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        // MOVE TO THE NEXT SONG IF ONE EXISTS
        if (current->next != nullptr) {
            current = current->next;

            cout << "Now Playing: "
                 << current->name
                 << " (" << current->duration << ")\n";
        }
        else {
            cout << "Already at the last song!\n";
        }
    }

    // THIS FUNCTION MOVES THE PLAYER TO THE PREVIOUS SONG
    void playPrevious() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        // MOVE TO THE PREVIOUS SONG IF ONE EXISTS
        if (current->prev != nullptr) {
            current = current->prev;

            cout << "Now Playing: "
                 << current->name
                 << " (" << current->duration << ")\n";
        }
        else {
            cout << "Already at the first song!\n";
        }
    }

    // THIS FUNCTION REVERSES THE ENTIRE PLAYLIST BY CHANGING THE POINTERS
    void reversePlaylist() {
        if (head == nullptr || head == tail) {
            cout << "Playlist does not need to be reversed.\n";
            return;
        }

        Song* temp = nullptr;
        Song* currentNode = head;

        // SWAP THE NEXT AND PREVIOUS POINTERS OF EVERY SONG
        while (currentNode != nullptr) {

            temp = currentNode->prev;
            currentNode->prev = currentNode->next;
            currentNode->next = temp;

            // MOVE TO THE NEXT NODE USING THE NEW PREV POINTER
            currentNode = currentNode->prev;
        }

        // AFTER REVERSING, THE OLD HEAD BECOMES THE TAIL AND VICE VERSA
        temp = head;
        head = tail;
        tail = temp;

        cout << "Playlist reversed successfully!\n";
    }

    // THIS FUNCTION FREES ALL THE MEMORY USED BY THE PLAYLIST
    ~Playlist() {
        Song* temp;

        while (head != nullptr) {
            temp = head;
            head = head->next;

            delete temp;
        }
    }
};

int main() {

    Playlist playlist;
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "       PLAYLIST MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Search Song\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Reverse Playlist\n";
        cout << "9. Exit\n";
        cout << "====================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // LET THE USER ADD A NEW SONG TO THE PLAYLIST
            playlist.addSong();
            break;

        case 2:
            // LET THE USER REMOVE A SONG USING ITS ID
            playlist.deleteSong();
            break;

        case 3:
            // SHOW THE PLAYLIST FROM START TO END
            playlist.displayForward();
            break;

        case 4:
            // SHOW THE PLAYLIST FROM END TO START
            playlist.displayBackward();
            break;

        case 5:
            // SEARCH FOR A PARTICULAR SONG USING ITS ID
            playlist.searchSong();
            break;

        case 6:
            // MOVE THE CURRENT SONG FORWARD
            playlist.playNext();
            break;

        case 7:
            // MOVE THE CURRENT SONG BACKWARD
            playlist.playPrevious();
            break;

        case 8:
            // REVERSE THE ORDER OF ALL SONGS
            playlist.reversePlaylist();
            break;

        case 9:
            // END THE PROGRAM
            cout << "Exiting playlist...\n";
            break;

        default:
            // SHOW AN ERROR IF THE USER ENTERS AN INVALID OPTION
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}
```
