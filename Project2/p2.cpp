#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int Partition(int numbers[], int i, int k) {
   int l;
   int h;
   int midpoint;
   int pivot;
   int temp;
   bool done;
   
   midpoint = i + (k - i) / 2;
   pivot = numbers[midpoint];
   
   done = false;
   l = i;
   h = k;
   
   while (!done) {
      while (numbers[l] < pivot) {
         ++l;
      }
      
      while (pivot < numbers[h]) {
         --h;
      }
      
      if (l >= h) {
         done = true;
      }
      else {
         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}

void Quicksort(int numbers[], int i, int k) {
   int j;
   
   if (i >= k) {
      return;
   }
   
   j = Partition(numbers, i, k);
   
   Quicksort(numbers, i, j);
   Quicksort(numbers, j + 1, k);
}

int Partition(string numbers[], int i, int k) {
   int l;
   int h;
   int midpoint;
   string pivot;
   string temp;
   bool done;
   
   midpoint = i + (k - i) / 2;
   pivot = numbers[midpoint];
   
   done = false;
   l = i;
   h = k;
   
   while (!done) {
      while (numbers[l].compare(pivot) < 0) {
         ++l;
      }
      
      while (pivot.compare(numbers[h]) < 0) {
         --h;
      }
      
      if (l >= h) {
         done = true;
      }
      else {
         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}

void Quicksort(string words[], int i, int k) {
   int j;
   
   if (i >= k) {
      return;
   }
   
   j = Partition(words, i, k);
   
   Quicksort(words, i, j);
   Quicksort(words, j + 1, k);
}

bool BiSearch(int arr[], int size, int find){
    int beg = 0;
    int end = size;
    while(beg <= end){
        int mid = (end + beg)/2;
        if(arr[mid] == find){
            return true;
        }
        else if(arr[mid] > find){
            end = mid - 1;
        }
        else {
            beg = mid + 1;
        }
    }
    return false;
}

bool BiSearch(string arr[], int size, string find){
    int beg = 0;
    int end = size;
    while(beg <= end){
        int mid = (end + beg)/2;
        if(arr[mid] == find){
            return true;
        }
        else if(arr[mid] > find){
            end = mid - 1;
        }
        else {
            beg = mid + 1;
        }
    }
    return false;
}
int main(int argc, char* argv[]) {
    string sel;
    string file_1_name;
    string file_2_name;
    fstream opentxt1;
    fstream opentxt2;
    int linenum1 = 0;
    int linenum2 = 0;

    if (argc != 4) {
        cout << "Usage: ./a (\"i\", \"s\") file1.txt file2.txt" << endl;
        return 1;
    }

    sel = argv[1];
    file_1_name = argv[2];
    file_2_name = argv[3];

    opentxt1.open(file_1_name);
    if(opentxt1.is_open()){
        string line;
        while(getline(opentxt1, line)){
            linenum1++;
        }
        opentxt1.close();
    }

    else{
        cout << "Failed to open \"" << file_1_name << "\"" << endl;
        return 1;
    }

    opentxt2.open(file_2_name);
    if(opentxt2.is_open()){
        string line;
        while(getline(opentxt2, line)){
            linenum2++;
        }
        opentxt2.close();
    }

    else{
        cout << "Failed to open \"" << file_2_name << "\"" << endl;
        return 1;
    }
    
    if(sel == "i"){
        int sortmeint1[linenum1];
        int sortmeint2[linenum2];
        int sameArr[linenum1];
        string line1;
        string line2;
        int count1 = 0;
        int count2 = 0;
        int sameCount = 0;
        opentxt1.open(file_1_name);
        opentxt2.open(file_2_name);

        while(getline(opentxt1, line1)){
            sortmeint1[count1] = stoi(line1);
            count1++;
        }

        Quicksort(sortmeint1, 0, count1-1);

        int size = linenum1-1;
        while(getline(opentxt2, line2)){
            sortmeint2[count2] = stoi(line2);
            if (BiSearch(sortmeint1, size, sortmeint2[count2])){
                sameArr[sameCount] = stoi(line2);
                sameCount++;
            }
            count2++;
        }

        Quicksort(sortmeint2, 0, count2-1);

        Quicksort(sameArr, 0, sameCount-1);

        for(int i = 0; i < sameCount; i++){

            if(i > 0 && sameArr[i] == sameArr[i-1]){
                continue;
            }
            else {
                cout << sameArr[i] << endl;
            }
        }
    }

    else if(sel == "s"){       
        string sortmestr1[linenum1];
        string sortmestr2[linenum2];
        string sameArr[linenum1];
        string line1;
        string line2;
        int count1 = 0;
        int count2 = 0;
        int sameCount = 0;
        opentxt1.open(file_1_name);
        opentxt2.open(file_2_name);

        while(getline(opentxt1, line1)){
            sortmestr1[count1] = line1;
            count1++;
        }

        Quicksort(sortmestr1, 0, count1-1);

        int size = linenum1-1;

        while(getline(opentxt2, line2)){
            sortmestr2[count2] = line2;
            if (BiSearch(sortmestr1, size, sortmestr2[count2])){
                sameArr[sameCount] = line2;
                sameCount++;
            }
            count2++;
        }

        Quicksort(sortmestr2, 0, count2-1);

        Quicksort(sameArr, 0, sameCount-1);

        for(int i = 0; i < sameCount; i++){

            if(i > 0 && sameArr[i] == sameArr[i-1]){
                continue;
            }
            else {
                cout << sameArr[i] << endl;
            }
        }
    }

    else {
        cout << "Usage: ./a (\"i\", \"s\") file1.txt file2.txt" << endl;
        return 1;
    }

    return 0;
}