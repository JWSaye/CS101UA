#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

unsigned long djb2(string str) {
    const char *ptr = str.c_str();
    unsigned long hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class Person {
private:
    string id, fName, lName, email, phoneNum, city, state, zipCode;

public:    
    Person(){}

    Person(string idin, string fNamein, string lNamein, string emailin, string phoneNumin, string cityin, string statein, string zipCodein){
        id = idin;
        fName = fNamein;
        lName = lNamein;
        email = emailin;
        phoneNum = phoneNumin;
        city = cityin;
        state = statein;
        zipCode = zipCodein;
    }

    string returnKey(string key) {
        if(key == "Id"){
            return id;
        }

        else if(key == "FirstName") {
            return fName;
        }

        else if(key == "LastName") {
            return lName;
        }

        else if(key == "Email") {
            return email;
        }

        else if(key == "Phone") {
            return phoneNum;
        }

        else if(key == "City") {
            return city;
        }

        else if(key == "State") {
            return state;
        }

        else if(key == "PostalCode") {
            return zipCode;
        }

        else{
            return "";
        }
    }

    void display(ostream &os) const{
        os << id << "," << fName << "," << lName << "," << email << "," << phoneNum << "," << city << "," << state << "," << zipCode << endl;
    }
};

ostream &operator<<(ostream &os, const Person &person){
    person.display(os);
    return os;
}

class LlNode {
public:
    Person value;
    LlNode *next;
};

class Llist {
private:
    LlNode *head;
    int _size = 0;
public:
    Llist() {
        head = NULL;
        _size = 0;
    }

    Llist &operator=(const Llist &src){
        head = src.head;
        return *this;
    }

    Person &at(int rank){
        LlNode *new1 = new LlNode;
        new1 = head;
        for(int i = 1; i <= rank; i++){
            new1 = new1->next;
        }
        return new1->value;
    }

    void append(Person who) {
        LlNode *new1 = new LlNode;
        new1->next = NULL;
        new1->value = who;

        if(_size == 0){
            head = new1;
        }
        else{
            LlNode *new2 = new LlNode;
            new2 = head;
            
            while(new2->next != NULL){
                new2 = new2->next;
            }

            new2->next = new1;

        }
        _size++;
    }

    int count() {
        LlNode *ptr;
        ptr = head;
        int count = 0;
        while(ptr != NULL) {
            count++;
            ptr = ptr->next;
        }
        return count;
    }

    void display(ostream &os) const{
        LlNode *ptr;
        ptr = head;
        while(ptr != NULL){
            os << ptr->value;
            ptr = ptr->next;
        }
    }
};

ostream &operator<<(ostream &os, const Llist &list){
    list.display(os);
    return os;
}

class HashTable {
private:
    vector<Llist> Table;
    int _size;
    vector<int> populated;
public:
    HashTable(int size) {
        Table.resize(size);
        _size = size;
        populated.resize(size);
        for(int i = 0; i < _size; i++) {
            Table.at(i) = Llist();
            populated.at(i) = 0;
        }
    }

    int find(string arr[], string key) {
        for(int i = 0; i < 8; i++) {
            if(arr[i] == key) {
                return i;
            }

            else {
                continue;
            }
        }

        return -1;
    }

    void populate(string file, string key)  {
        string outText;
        ifstream readMe(file);
        int i = 0;
        int id, fN, lN, email, phone, city, state, zip;
        string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };

        while(getline(readMe, outText)){
            string personAttr[8];
            string token;
            istringstream iss(outText);
            int j = 0;
            while (getline(iss, token, '\t')) {
                personAttr[j] = token;
                j++;
            }
                
            if(i == 0) {
                id = find(personAttr, validKeys[0]);
                fN = find(personAttr, validKeys[1]);
                lN = find(personAttr, validKeys[2]);
                email = find(personAttr, validKeys[3]);
                phone = find(personAttr, validKeys[4]);
                city = find(personAttr, validKeys[5]);
                state = find(personAttr, validKeys[6]);
                zip = find(personAttr, validKeys[7]);
                i++;
            }

            else {
                Person newPerson(personAttr[id], personAttr[fN], personAttr[lN], personAttr[email], personAttr[phone], personAttr[city], personAttr[state], personAttr[zip]);
                string hashMe = newPerson.returnKey(key);
                int mapHere = djb2(hashMe) % _size;

                Table.at(mapHere).append(newPerson);
                populated.at(mapHere)++;
            }
            
        }
        readMe.close();
    }

    Llist at(int index){
        return Table.at(index);
    }

    int population(int index) {
        return populated.at(index);
    }
};

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }

    HashTable mainTable(tableSize);

    mainTable.populate(filename, key);

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            // print code here
            for(int i = 0; i < tableSize; i++) {    
                if(mainTable.population(i) > 0){
                    string keys[mainTable.population(i)] = {""};
                    int cnts[mainTable.population(i)] = {0};
                    int index = 0;
                    cout << i << ": ";
                    for(int j = 0; j < mainTable.population(i); j++){
                        bool skip = false;
                        for(int k = 0; k < j; k++){
                            if(mainTable.at(i).at(j).returnKey(key) == keys[k]){
                                skip = true;
                                cnts[k]++;
                            }
                        }
                        if(!skip){
                            keys[index] = mainTable.at(i).at(j).returnKey(key);
                            cnts[index] = 1;
                            index++;
                        }
                    }

                    int p = 0;

                    while(p < mainTable.population(i) && cnts[p] != 0){
                        cout << keys[p] << " (" << cnts[p] << "),";
                        p++;
                    }

                    cout << endl;
                }
            }
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            // lookup code here
            int search = djb2(val) % tableSize;
            if(mainTable.population(search) > 0){
                int cnt = 0;
                bool printed = false;
                for(int i = 0; i < mainTable.population(search); i++){
                    if(mainTable.at(search).at(i).returnKey(key) == val){
                        if(cnt == 0){
                            cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                            cnt++;
                            printed = true;
                        }
                        cout << mainTable.at(search).at(i);
                    }

                    else if(i == mainTable.population(search)-1 && !printed){
                        cout << "No results" << endl;
                    }
                }
            }

            else {
                cout << "No results" << endl;
            }
            
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
