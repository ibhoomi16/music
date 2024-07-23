#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct node {
    string song;
    node *next;
    node *prev;
};

node *top = nullptr, *temp = nullptr, *top1 = nullptr;

void tofile(const string& a) {
    ofstream f1("playlist.txt", ios::out | ios::app);
    f1 << a << endl;
    f1.close();
}

void add_node(node *first) {
    string a;
    while (first->next != nullptr) {
        first = first->next;
    }
    node *new_node = new node;
    first->next = new_node;
    new_node->prev = first;
    cout << "\nEnter Song name- ";
    cin >> a;
    new_node->song = a;
    tofile(a);
    new_node->next = nullptr;
}

void add_node_file(node *first, const string& a) {
    while (first->next != nullptr) {
        first = first->next;
    }
    node *new_node = new node;
    first->next = new_node;
    new_node->prev = first;
    new_node->song = a;
    new_node->next = nullptr;
}

void delete_file(const string& a) {
    ifstream f1("playlist.txt");
    ofstream f2("temp.txt");
    string line;
    bool found = false;
    while (getline(f1, line)) {
        if (a != line)
            f2 << line << endl;
        else
            found = true;
    }
    f1.close();
    f2.close();
    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");
    if (!found) {
        cout << "There is no song with the name you entered." << endl;
    } else {
        cout << "Song has been deleted." << endl;
    }
}

void del_node(node *first) {
    while (first->next->next != nullptr) {
        first = first->next;
    }
    node *temp = first->next;
    first->next = nullptr;
    delete temp;
    cout << "Deleted" << endl;
}

void printlist(node *first) {
    cout << "\nPlaylist: " << endl;
    while (first != nullptr) {
        cout << first->song << endl;
        first = first->next;
    }
}

void count_nodes(node *first) {
    int count = 0;
    while (first != nullptr) {
        first = first->next;
        count++;
    }
    cout << "\nTotal songs: " << count << endl;
}

node* del_pos(node *pointer, int pos) {
    if (pos == 1) {
        node *temp = pointer;
        delete_file(temp->song);
        pointer = pointer->next;
        if (pointer != nullptr) pointer->prev = nullptr;
        delete temp;
        cout << "\nThe list is updated\nUse the display function to check\n";
        return pointer;
    }

    node *current = pointer;
    for (int i = 1; i < pos && current != nullptr; i++) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "\nPosition out of range\n";
        return pointer;
    }

    delete_file(current->song);
    if (current->prev != nullptr) current->prev->next = current->next;
    if (current->next != nullptr) current->next->prev = current->prev;

    delete current;
    cout << "\nThe list is updated\nUse the display function to check\n";
    return pointer;
}

void search1(node *first) {
    string song;
    cout << "\nEnter song to be searched: ";
    cin >> song;

    while (first != nullptr) {
        if (first->song == song) {
            cout << "\nSong Found" << endl;
            return;
        }
        first = first->next;
    }
    cout << "\nSong Not found" << endl;
}

void create() {
    top = nullptr;
}

void push(const string& data) {
    node *new_node = new node;
    new_node->song = data;
    new_node->next = top;
    if (top != nullptr) top->prev = new_node;
    top = new_node;
}

void display() {
    top1 = top;
    if (top1 == nullptr) {
        cout << "\nNo recently played tracks." << endl;
        return;
    }
    cout << "\nRecently played tracks: " << endl;
    while (top1 != nullptr) {
        cout << top1->song << endl;
        top1 = top1->next;
    }
}

void play(node *first) {
    string song;
    printlist(first);
    cout << "\nChoose song you wish to play: ";
    cin >> song;

    while (first != nullptr) {
        if (first->song == song) {
            cout << "\nNow Playing: " << song << endl;
            push(song);
            return;
        }
        first = first->next;
    }
    cout << "\nSong Not found" << endl;
}

void recent() {
    display();
}

void topelement() {
    if (top == nullptr) {
        cout << "\nNo last played tracks." << endl;
        return;
    }
    cout << "\nLast Played Song: " << top->song << endl;
}

void sort(node *&pointer) {
    if (pointer == nullptr || pointer->next == nullptr) return;

    bool swapped;
    node *ptr1;
    node *lptr = nullptr;

    do {
        swapped = false;
        ptr1 = pointer;

        while (ptr1->next != lptr) {
            if (ptr1->song > ptr1->next->song) {
                swap(ptr1->song, ptr1->next->song);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


void del_search(node *start) {
    string song;
    printlist(start);
    cout << "\nChoose song you wish to delete: ";
    cin >> song;

    while (start != nullptr) {
        if (start->song == song) {
            cout << "\nSong Found" << endl;
            delete_file(start->song);
            if (start->prev != nullptr) start->prev->next = start->next;
            if (start->next != nullptr) start->next->prev = start->prev;
            delete start;
            return;
        }
        start = start->next;
    }
    cout << "\nSong Not found" << endl;
}

void deletemenu(node *start) {
    int choice;
    cout << "Which type of delete do you want?\n1. By Search\n2. By Position" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            del_search(start);
            break;
        case 2:
            int pos;
            cout << "\nEnter the position of the song: ";
            cin >> pos;
            start = del_pos(start, pos);
            break;
        default:
            cout << "\nInvalid choice" << endl;
    }
}

int main() {
    int choice;
    string song;
    node *start = new node;
    cout << "\t\t\t*WELCOME*" << endl;
    cout << "\n**please use '_' for space." << endl;
    cout << "\nEnter your playlist name: ";
    cin.ignore();
    getline(cin, start->song);
    start->next = nullptr;
    start->prev = nullptr;

    create();

    do {
        cout << "\n1. Add New Song\n2. Delete Song\n3. Display Entered Playlist\n4. Total Songs\n5. Search Song\n6. Play Song\n7. Recently Played List\n8. Last Played\n9. Sorted playlist\n10. Add From File\n11. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add_node(start);
                break;
            case 2:
                deletemenu(start);
                break;
            case 3:
                printlist(start);
                break;
            case 4:
                count_nodes(start);
                break;
            case 5:
                search1(start);
                break;
            case 6:
                play(start);
                break;
            case 7:
                recent();
                break;
            case 8:
                topelement();
                break;
            case 9:
                sort(start->next);
                printlist(start);
                break;

            case 10:
                exit(0);
        }
    } while (choice != 10);

    return 0;
}
   
