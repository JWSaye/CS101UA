#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Node {
    public:
        int key;
        class Node *left;
        class Node *right;
};

int searchArr(int arr[], int val, int start, int end) {
    for(int i = start; i <= end; i++) {
        if(arr[i] == val) {
            return i;
        }
    }
    return -1;
}

Node* createNewNode(int key) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int* createLevel(int inorder[], int levelorder[], int inSize, int lvlSize) {
    int *newLevel = new int[inSize], j = 0;

    for(int i = 0; i < lvlSize; i++){
        if(searchArr(inorder, levelorder[i], 0, inSize - 1) != -1) {
            newLevel[j] = levelorder[i];
            j++;
        }
    }

    return newLevel;
}

Node* buildBinTree(int inorder[], int level[], int inorderStart, int inorderEnd, int size) {
    if(inorderStart > inorderEnd) {
        return NULL;
    }

    Node* root = createNewNode(level[0]);

    if(inorderStart == inorderEnd) {
        return root;
    }

    int inorderIndex = searchArr(inorder, root->key, inorderStart, inorderEnd);

    int* leftLevel = createLevel(inorder, level, inorderIndex, size);

    int* rightLevel = createLevel(inorder + inorderIndex + 1, level, size-1, size);
        
    root->left = buildBinTree(inorder, leftLevel, inorderStart, inorderIndex - 1, inorderIndex - inorderStart);

    root->right = buildBinTree(inorder, rightLevel, inorderIndex + 1, inorderEnd, inorderEnd - inorderIndex);

    return root;
}

vector<int> extractVect(string fileName) {
    ifstream file;
    string str;
    file.open(fileName);
    vector<int> vect;
    while(getline(file, str)) {
        istringstream iss(str);
        int val;
        while(iss >> val){
            vect.push_back(val);
        }
        
    }

    file.close();

    return vect;
}

bool treeTraverse(Node* tree, string code) {
    Node* currNode = tree;
    for(int i = 0; i < code.length(); i++) {
        if(code[i] == '1'){
            currNode = currNode->right;
        }

        else if(code[i] == '0'){
            currNode = currNode->left;
        }
    }

    if(currNode->left == NULL && currNode->right == NULL) {
        return true;
    }

    else {
        return false;
    }
}

char decodeSeg(Node* tree, string decode){
    Node* currNode = tree;
    for(int i = 0; i < decode.length(); i++) {
        if(decode[i] == '1'){
            currNode = currNode->right;
        }

        else if(decode[i] == '0'){
            currNode = currNode->left;
        }
    }
    return char(currNode->key);
}


int main(int argc, char** argv){

    if (argc != 4) {
        cout << "Usage: ./a.out inorder.txt level.txt encode.txt" << endl;
        return 1;
    }

    string inorderFile = argv[1];
    string levelFile = argv[2];
    string encodedFile = argv[3];
    string answer = "";
    string code = "";
    string decode = "";
    string codeTemp;
    
    vector<int> inorderVec = extractVect(inorderFile);
    vector<int> levelVec = extractVect(levelFile);

    int inorderArr[inorderVec.size()];
    int levelArr[levelVec.size()];

    for(int i = 0; i < inorderVec.size(); i++) {
        inorderArr[i] = inorderVec.at(i);
        levelArr[i] = levelVec.at(i);
    }

    fstream codeFile;
    codeFile.open(encodedFile);

    while(getline(codeFile, codeTemp)) {
        code = code + codeTemp;
    }

    
    Node* tree = buildBinTree(inorderArr, levelArr, 0, inorderVec.size() - 1, inorderVec.size());

    for(int i = 0; i < code.length(); i++) {
        decode.push_back(code[i]);
        if(treeTraverse(tree, decode)){
            answer.push_back(decodeSeg(tree, decode));
            decode = "";
        }
    }

    cout << answer;
    
}