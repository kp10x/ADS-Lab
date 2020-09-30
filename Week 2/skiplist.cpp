#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define MAX_LEVEL 3
const float P = 0.5;
using namespace std;

struct Node {
    int value;
    Node **forw;
    Node(int level, int &value) {
        forw = new Node * [level + 1];
        memset(forw, 0, sizeof(Node*) * (level + 1));
        this -> value = value; 
    }
    ~Node() {
        delete [] forw;        
    } 
};

struct skiplist {
    Node *header;
    int value;
    int level;
    skiplist() {
        header = new Node(MAX_LEVEL, value); //call node for each list header
        level = 0;
    }
    ~skiplist() {
        delete header;
    }

    void display();
    bool contains(int &);
    void insert_element(int &);
    void delete_element(int &);        
};

int random_level() {
    static bool first = true;
    if (first) {
        srand((unsigned)time(NULL));
        first = false;
    }
    int lvl = (int) (log((float) rand() / RAND_MAX) / log(1.-P));
    return lvl < MAX_LEVEL ? lvl : MAX_LEVEL; //random val generated from 0 to n
}
 
void skiplist::insert_element(int &value) {
    Node *x = header;	
    Node *update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(Node*) * (MAX_LEVEL + 1));
    for (int i = level;i >= 0;i--) {
        while (x->forw[i] != NULL && x->forw[i]->value < value) {   //check position of element if before or after and then proceed
            x = x->forw[i];
        }
        update[i] = x; 
    }
    x = x -> forw[0];
    if (x == NULL || x -> value != value) {        // insert and update respective values at a random lvl
        int lvl = random_level();
        if (lvl > level) {
            for (int i = level + 1;i <= lvl;i++) {
                update[i] = header;
            }
            level = lvl;
        }
        x = new Node(lvl, value);
        for (int i = 0;i <= lvl;i++) {
            x -> forw[i] = update[i] -> forw[i];
            update[i] -> forw[i] = x;
        }
    }
}
 
void skiplist::delete_element(int &value) {
    Node *x = header;	
    Node *update[MAX_LEVEL + 1];
    memset (update, 0, sizeof(Node*) * (MAX_LEVEL + 1));
    for (int i = level;i >= 0;i--) {
        while (x -> forw[i] != NULL && x -> forw[i] -> value < value) { //find posistion of where to delete from
            x = x -> forw[i];
        }
        update[i] = x; 
    }
    x = x -> forw[0];
    if (x -> value == value) {
        for (int i = 0;i <= level;i++) {
            if (update[i] -> forw[i] != x) break;   //delete val and alter pointers based on it
            update[i] -> forw[i] = x -> forw[i];
        }
        delete x;
        while (level > 0 && header -> forw[level] == NULL) {
            level--;
        }
    }
}

void skiplist::display() {
    const Node *x = header -> forw[0];
    while (x != NULL) {
        cout << x->value;
        x = x->forw[0];
        if (x != NULL)
            cout << " - ";
    }
    cout << endl;
}

bool skiplist::contains(int &s_value) { //search for element in list
    Node *x = header;
    for (int i = level;i >= 0;i--) {
        while (x -> forw[i] != NULL && x -> forw[i] -> value < s_value) {
            x = x -> forw[i];
        }
    }
    x = x -> forw[0];
    return x != NULL && x -> value == s_value;
}

int main() {    //driver code
    skiplist ss;
    int choice, n;
    while (1) {
        cout << "\n1.Insert Element" << endl;
        cout << "2.Delete Element" << endl;
        cout << "3.Search Element" << endl;
        cout << "4.Display List " << endl;
        cout << "5.Exit " << endl;
        cout << "Enter your choice : ";
        cin >> choice;
        switch(choice) {
        case 1:
             cout << "Enter the element to be inserted: ";
             cin >> n;
             ss.insert_element(n);
             if(ss.contains(n)) cout<<"Element Inserted"<<endl;
             break;
        case 2:
             cout << "Enter the element to be deleted: ";
             cin >> n;
             if(!ss.contains(n)) {
                 cout << "Element not found" << endl;
                 break;
             }
             ss.delete_element(n);
             if(!ss.contains(n)) cout<<"Element Deleted"<<endl;
             break;
        case 3:
             cout << "Enter the element to be searched: ";
             cin >> n; 
             if(ss.contains(n)) cout << "Element " << n << " is in the list" << endl;
             else cout << "Element not found" << endl;
        case 4:
             cout << "The List is: ";
             ss.display();
             break;
        case 5:
             exit(1);
             break;
        default:
             cout << "Wrong Choice" << endl;
        }
    }
    return 0;
}