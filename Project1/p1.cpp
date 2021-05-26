#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <climits>
#include <math.h>
using namespace std;

//Function to open file or return error if it does not exist
fstream openf(string filename) {
    fstream database;

    database.open(filename);

    if (!database) {
        cout << "Failed to open \"" << filename << "\"" << endl;
    }

    return database;
}

//Function for help
void help() {
    cout << "command list:" << endl;
    cout << "        print" << endl;
    cout << "        cols " << endl;
    cout << "        search *|col_name val" << endl;
    cout << "        min col_name" << endl;
    cout << "        max col_name" << endl;
    cout << "        avg col_name" << endl;
}

//Function for print
void printcsv(string filename, int width) {
    fstream file = openf(filename);
    string line;

    while(getline(file, line)){
        vector<string> tempList;
        string tempStr;

        for(int i = 0; i <= line.length(); i++){

            if (i == line.length()) {
                tempList.push_back(tempStr);
            }

            else if(line[i] != ','){
                tempStr += line[i];
            }

            else {
                tempList.push_back(tempStr);
                tempStr = "";
            }
        }

        for(int i = 0; i < tempList.size(); i++) {
            cout << setw(width) << tempList[i];
        }
        cout << endl;
    }
    file.close();
}

//Function for cols
void colList(string filename) {
    fstream file = openf(filename);
    string line;
    string tempStr;

    getline(file, line);

    for(int i = 0; i <= line.length(); i++){

        if (i == line.length()) {
            cout << tempStr << endl;
        }

        else if(line[i] != ','){
            tempStr += line[i];
        }

        else {
            cout << tempStr << endl;
            tempStr = "";
        }
    }
    file.close();

}

//Function for search *|col_name value
void Search(string filename, int width, string col_name, string val){
    fstream file = openf(filename);

    if(col_name == "*") {
        string line;
        int lineNum = 0;
        bool found = false;
        bool colHeadersPrinted = false;
        ostringstream cols;

        while(getline(file, line)){
            vector<string> tempList;
            string tempStr;

            for(int i = 0; i <= line.length(); i++){

                if (i == line.length()) {
                    tempList.push_back(tempStr);
                }

                else if(line[i] != ','){
                    tempStr += line[i];
                }

                else {
                    tempList.push_back(tempStr);
                    tempStr = "";
                }
            }

            if(lineNum == 0) {
                for(int i = 0; i < tempList.size(); i++) {
                    cols << setw(width) << tempList[i];
                }
                cols << endl;
                lineNum++;
            }

            else {
                for(int i = 0; i < tempList.size(); i++) {
                    if(tempList[i] == val){
                        found = true;
                        if(!colHeadersPrinted){
                            string colPrint = cols.str();
                            cout << colPrint;
                            colHeadersPrinted = true;
                        }
                        for(int i = 0; i < tempList.size(); i++) {
                            cout << setw(width) << tempList[i];
                        }
                        cout << endl;
                        break;
                    }

                    else {
                        continue;
                    }
                }
            }
        }

        if(!found) {
            cout << "No results" << endl;
        }
    }

    else {
        string line;
        int lineNum = 0;
        bool valid = false;
        int colIndex;
        bool found = false;
        bool colHeadersPrinted = false;
        ostringstream cols;

        while(getline(file, line)){
            vector<string> tempList;
            string tempStr;

            for(int i = 0; i <= line.length(); i++){

                if (i == line.length()) {
                    tempList.push_back(tempStr);
                }

                else if(line[i] != ','){
                    tempStr += line[i];
                }

                else {
                    tempList.push_back(tempStr);
                    tempStr = "";
                }
            }

            if(lineNum == 0) {
                for(int i = 0; i < tempList.size(); i++) {
                    if(tempList[i] == col_name){
                        colIndex = i;
                        valid = true;
                        for(int i = 0; i < tempList.size(); i++) {
                            cols << setw(width) << tempList[i];
                        }
                        cols << endl;
                        break;
                    }

                    else {
                        continue;
                    }
                }
                
                if(valid) {
                    lineNum++;
                }
                
                else {
                    cout << "Invalid command" << endl;
                    break;
                }
            }

            else {
                if(tempList[colIndex] == val) {
                    found = true;
                    if(!colHeadersPrinted){
                        string colPrint = cols.str();
                        cout << colPrint;
                        colHeadersPrinted = true;
                    }
                    for(int i = 0; i < tempList.size(); i++) {
                        cout << setw(width) << tempList[i];
                    }
                    cout << endl;
                }

                else {
                    continue;
                }
            }
        }

        if(!found && valid) {
            cout << "No results" << endl;
        }
    }

    file.close();
}

//Function for min col_name
void minCol(string filename, int width, string col_name) {
    string line;
    int lineNum = 0;
    bool valid = false;
    int colIndex;
    double min = (double) INT_MAX;
    fstream file = openf(filename);

    while(getline(file, line)){
        vector<string> tempList;
        string tempStr;

        for(int i = 0; i <= line.length(); i++){

            if (i == line.length()) {
                tempList.push_back(tempStr);
            }

            else if(line[i] != ','){
                tempStr += line[i];
            }

            else {
                tempList.push_back(tempStr);
                tempStr = "";
            }
        }

        if(lineNum == 0) {
            for(int i = 0; i < tempList.size(); i++) {
                if(tempList[i] == col_name){
                    colIndex = i;
                    valid = true;
                    break;
                }

                else {
                    continue;
                }
            }
                
            if(valid) {
                lineNum++;
            }
                
            else {
                cout << "Invalid command" << endl;
                break;
            }
        }

        else {
            if(tempList[colIndex] != ""){
                double tempComp = stod(tempList[colIndex]);
                if(tempComp <= min) {
                    min = tempComp;
                }

                else {
                    continue;
                }
            }
        }
    }

    if(valid){
        if(min != (double) INT_MAX){
            cout << "The min for col \"" << col_name << "\" = " << min << endl;
        }

        else{
            cout << "The min for col \"" << col_name << "\" = N/A" << endl;
        }
    }
    file.close();
}

//Function for max col_name
void maxCol(string filename, int width, string col_name) {
    string line;
    int lineNum = 0;
    bool valid = false;
    int colIndex;
    double max = (double) INT_MIN;
    fstream file = openf(filename);

    while(getline(file, line)){
        vector<string> tempList;
        string tempStr;

        for(int i = 0; i <= line.length(); i++){

            if (i == line.length()) {
                tempList.push_back(tempStr);
            }

            else if(line[i] != ','){
                tempStr += line[i];
            }

            else {
                tempList.push_back(tempStr);
                tempStr = "";
            }
        }

        if(lineNum == 0) {
            for(int i = 0; i < tempList.size(); i++) {
                if(tempList[i] == col_name){
                    colIndex = i;
                    valid = true;
                    break;
                }

                else {
                    continue;
                }
            }
                
            if(valid) {
                lineNum++;
            }
                
            else {
                cout << "Invalid command" << endl;
                break;
            }
        }

        else {
            if(tempList[colIndex] != ""){
                double tempComp = stod(tempList[colIndex]);
                if(tempComp >= max) {
                    max = tempComp;
                }

                else {
                    continue;
                }
            }
        }
    }
    if(valid){
        if(max != (double) INT_MIN){
            cout << "The max for col \"" << col_name << "\" = " << max << endl;
        }

        else{
            cout << "The max for col \"" << col_name << "\" = N/A" << endl;
        }
    }
    
    file.close();
}

//Function for avg col_name
void avgCol(string filename, int width, string col_name) {
    string line;
    int lineNum = -1;
    bool valid = false;
    int colIndex;
    double avg = 0.0;
    fstream file = openf(filename);

    while(getline(file, line)){
        vector<string> tempList;
        string tempStr;

        for(int i = 0; i <= line.length(); i++){

            if (i == line.length()) {
                tempList.push_back(tempStr);
            }

            else if(line[i] != ','){
                tempStr += line[i];
            }

            else {
                tempList.push_back(tempStr);
                tempStr = "";
            }
        }

        if(lineNum == -1) {
            for(int i = 0; i < tempList.size(); i++) {
                if(tempList[i] == col_name){
                    colIndex = i;
                    valid = true;
                    break;
                }

                else {
                    continue;
                }
            }
                
            if(valid) {
                lineNum++;
            }
                
            else {
                cout << "Invalid column \"" << col_name << "\"" << endl;
                break;
            }
        }

        else {
            if(tempList[colIndex] != ""){
                avg = avg + stod(tempList[colIndex]);
                lineNum++;
            }

            else{
                continue;
            }
        }
    }

    avg /= (double) lineNum;

    if(valid){
        if(!(isnan(avg))){
            cout << "The avg for col \"" << col_name << "\" = " << avg << endl;
        }

        else{
            cout << "The avg for col \"" << col_name << "\" = N/A" << endl;
        }
    }
    
    file.close();
}

//Function to get and interpret user input
void UserInterface(string csvfile, int width) {
    while (true) {
        string user1;
        cout << "Enter a command or \"help\" for a command list:" << endl;
        getline(cin, user1);

        //Quit program
        if (user1 == "quit") {
            break;
        }

        //Print the help menu
        else if (user1 == "help") {
            help();
        }

        //Print the CSV table
        else if (user1 == "print") {
            printcsv(csvfile, width);
        }

        //Print a list of the column names
        else if (user1 == "cols") {
            colList(csvfile);
        }
        
        //Search Command
        else if (user1.substr(0,6) == "search") {
            //Makes sure there is a space after the search command
            if (user1.substr(6, 1) == " ") {
                //Creates a substring from the remaining input after the search command and the space
                string usersub = user1.substr(7);
                string col;
                string val;

                //Checks if the column input is a * for all columns
                if(usersub.substr(0,1) == "*") {
                    //Gets the * as to column variable
                    col = usersub.substr(0,1);
                    //Account for quotes in value
                    if(usersub.find("\"") != std::string::npos){
                        val = usersub.substr(usersub.find("\"") + 1, usersub.substr(usersub.find("\"") + 1).length()-1); 
                    }

                    else {
                        val = usersub.substr(usersub.find(" ") + 1, usersub.substr(usersub.substr(1).find(" ") + 1).length()-1);
                    }
                }
                //Checks for a quotation mark before the column name
                else if(usersub.substr(0,1) == "\"") {
                    col = usersub.substr(1, usersub.substr(1, usersub.length()-2).find("\""));
                    if(usersub.substr(usersub.substr(1).find("\"") + 3, 1) != "\"") {
                        val = usersub.substr(usersub.substr(1).find("\"") + 3);
                    }

                    else {
                        val = usersub.substr(usersub.substr(1).find("\"") + 4, usersub.substr(usersub.substr(1).find("\"") + 3).length()-2);
                    }
                }

                else {
                    col = usersub.substr(0, usersub.find(" "));
                    if(usersub.find("\"") != std::string::npos){
                        val = usersub.substr(usersub.find("\"") + 1, usersub.substr(usersub.find("\"") + 1).length()-1); 
                    }

                    else {
                        val = usersub.substr(usersub.find(" ") + 1, usersub.substr(usersub.substr(1).find(" ") + 1).length()-1);
                    }
                }
                Search(csvfile, width, col, val);
            }
            else {
                cout << "Invalid command" << endl;
            }
        }

        //Takes the min of a column
        else if(user1.substr(0, 3) == "min") {
            string usersub = user1.substr(4);
            if(usersub.substr(0,1) != "\""){
                minCol(csvfile, width, usersub);
            }

            else {
                string col = usersub.substr(1, usersub.substr(1).length()-1);
                minCol(csvfile, width, col);
            }
        }

        //Takes the max of a column
        else if(user1.substr(0, 3) == "max") {
            string usersub = user1.substr(4);
            if(usersub.substr(0,1) != "\""){
                maxCol(csvfile, width, usersub);
            }

            else {
                string col = usersub.substr(1, usersub.substr(1).length()-1);
                maxCol(csvfile, width, col);
            }
        }

        //Takes the avg of a column
        else if(user1.substr(0, 3) == "avg") {
            string usersub = user1.substr(4);
            if(usersub.substr(0,1) != "\""){
                avgCol(csvfile, width, usersub);
            }

            else {
                string col = usersub.substr(1, usersub.substr(1).length()-1);
                avgCol(csvfile, width, col);
            }
        }

        //Invalid command input
        else {
            cout << "Invalid command" << endl;
        }

        cout << endl;
    }
}

//Main function
int main(int argc, char* argv[]) {

    string databasecsv;
    int col_width;
    fstream opencsv;

    if (argc != 3) {
        cout << "Usage: ./a database.csv #col_width" << endl;
        return 1;
    }

    databasecsv = argv[1];
    col_width = atoi(argv[2]);

    opencsv.open(databasecsv);
    if(opencsv.is_open()){
        opencsv.close();
    }

    else{
        cout << "Failed to open \"" << databasecsv << "\"" << endl;
        return 1;
    }
    
    UserInterface(databasecsv, col_width);

    return 0;
}