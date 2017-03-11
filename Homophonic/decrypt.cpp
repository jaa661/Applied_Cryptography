// HW00
// Jacob Abbott 
// cs 1124

#include <iostream> 
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>


using namespace std;

map<char,int> LETTERS_FREQUENCY = { {' ', 19}, {'a',7}, {'b',1}, {'c',2}, {'d',4}, {'e',10}, {'f',2} ,{'g',2} ,{'h',5} , {'i',6},{'j',1},{'k',1},{'l',3},{'m',2},{'n',6},{'o',6},{'p',2},{'q',1},{'r',5},{'s',5},{'t',7},{'u',2} ,{'v',1},{'w',2},{'x',1},{'y',2},{'z',1} };
map<char,int> LETTERS_VALUE = { {' ', 0}, {'a',1}, {'b',2}, {'c',3}, {'d',4}, {'e',5}, {'f',6} ,{'g',7} ,{'h',8} , {'i',9},{'j',10},{'k',11},{'l',12},{'m',13},{'n',14},{'o',15},{'p',16},{'q',17},{'r',18},{'s',19},{'t',20},{'u',21} ,{'v',22},{'w',23},{'x',24},{'y',25},{'z',26} };

class key{
public:
    key();//generates a random key
    void mutate(int mutate);//mutates the key by specified value
    void optimize();//use the score to mutate a better key
    void printKey();
    vector<char> getKey();
private:
    vector<char> keyVals;
    vector<char> newKey;
    int keyLength = 106;
};

class matrix{
public:
    matrix(string dict);//generates a random key
    void genKeyMatrix(int index);//generate the frequency matrix for the current key
    void genFreqMatrix();//generate the frequency matrix for the dictionary(only necessary once)
    double score(int index);//score for keyMatrix[index]
    bool compare(key A, key B);//compare score of A and B return true if A is better
    void printMatrix(int index);
    void printFreqMatrix();
private:
    double freqMatrix[27][27];
    double keyMatrix[4][27][27];
    string dictionary;
};


void decryptString(string& encryptedString, ifstream& ifs, int rotation, string& decryptedString);
string readFromFile(string filename);
vector<int> toVector(string cypher);
string decrypt(vector<int> cypher, vector<char> key);
void printGuess(string guess);
vector<string> readFromFileLines(string filename);




int main(){

    string encrypted = ""; // store the original text in a string
    string dict = "";
    vector<int> cypher;
    string decryptedString = ""; // assemble the decrypted text here
    string input = "0";
    bool done = false;
    
    while(!done){
        cout<<"Enter option:\n(1)load file 'Cypher.txt'\n(2)enter via keyboard"<<endl;
        cin>>input;
        key firstKey;
        if (input == "1"){
            encrypted = readFromFile("/Users/pierules53/Desktop/Current\ Homework/Crypto/Homophonic/Cypher.txt");
            dict = readFromFile("/Users/pierules53/Desktop/Current\ Homework/Crypto/Homophonic/english_words.txt");
            matrix compare(dict);
            cypher = toVector(encrypted);
            firstKey.printKey();
            compare.printFreqMatrix();
            string guess = decrypt(cypher,firstKey.getKey());
            //printGuess(guess);
            done = true;
        }
        else if (input == "2"){
            cin>>encrypted;
            dict = readFromFile("/Users/pierules53/Desktop/Current\ Homework/Crypto/Homophonic/english_words.txt");
            cypher = toVector(encrypted);
            string guess = decrypt(cypher,firstKey.getKey());
            printGuess(guess);
            done = true;
        }
        else{
            cout<<"not a valid option"<<endl;
        }
    }
return 0;
}
/////////////////////////////////////////////////////////////////////////////////
key::key(void){
    map<char, int>::iterator it;
    map<char, int>::iterator it2;
    int randomIndex;
    int possibleValues = keyLength;
    vector<int> listTo105;
    vector<char> temp;
    it2 = LETTERS_VALUE.begin();
    for ( it = LETTERS_FREQUENCY.begin(); it != LETTERS_FREQUENCY.end(); it++ ){
        for ( int i = 0; i < it->second; i++ ){
            temp.push_back(it->first);
        }
        it2++;
    }
    for (int i =0; i < keyLength; i++){
            randomIndex = rand() % (possibleValues);
            possibleValues--;
            keyVals.push_back(temp[randomIndex]);
            temp.erase(temp.begin() + randomIndex);
    }
}
////////////////////////////////////////
matrix::matrix(string dict){
    dictionary = dict;
    genFreqMatrix();
}
////////////////////////////////////////
void key::printKey(){
    for(int i = 0; i < keyVals.size(); i++){
            cout <<keyVals[i]<<", ";
    }
    cout <<endl;
}
////////////////////////////////////////
void matrix::genKeyMatrix(int index){
    double first = 1;
    int second = 0;
    char uno, dos;
    while(first < dictionary.size()){
        if(dictionary[first] == '\n')
            uno = ' ';
        else
            uno = dictionary[first];
        if(dictionary[second] == '\n')
            dos = ' ';
        else
            dos = dictionary[second];
        
        keyMatrix[index][LETTERS_VALUE.find(uno)->second][LETTERS_VALUE.find(dos)->second] =
        keyMatrix[index][LETTERS_VALUE.find(uno)->second][LETTERS_VALUE.find(dos)->second] + 1;
        first++;
        second++;
        //printFreqMatrix();
        //cout<<uno<<dos<<endl;
    }
    for(int i=0;i<27;i++){
        for(int j=0;j<27;j++)
            keyMatrix[index][i][j] = keyMatrix[index][i][j] / first;
    }
}
////////////////////////////////////////
void matrix::genFreqMatrix(){
    double first = 1;
    int second = 0;
    char uno, dos;
    while(first < dictionary.size()){
        if(dictionary[first] == '\n')
            uno = ' ';
        else
            uno = dictionary[first];
        if(dictionary[second] == '\n')
            dos = ' ';
        else
            dos = dictionary[second];
        
        freqMatrix[LETTERS_VALUE.find(uno)->second][LETTERS_VALUE.find(dos)->second] =
            freqMatrix[LETTERS_VALUE.find(uno)->second][LETTERS_VALUE.find(dos)->second] + 1;
        first++;
        second++;
        //printFreqMatrix();
        //cout<<uno<<dos<<endl;
    }
    for(int i=0;i<27;i++){
        for(int j=0;j<27;j++)
            freqMatrix[i][j] = freqMatrix[i][j] / first;
    }
}
////////////////////////////////////////
void matrix::printMatrix(int index){
    for(int i=0;i<27;i++){
        for(int j=0;j<27;j++)
            cout<<keyMatrix[index][i][j]<< ", ";
        cout<<endl;
    }
}
////////////////////////////////////////
void matrix::printFreqMatrix(){
    for(int i=0;i<27;i++){
        for(int j=0;j<27;j++)
            cout<<freqMatrix[i][j]<< ", ";
        cout<<endl;
    }
}
////////////////////////////////////////
vector<char> key::getKey(){
    return keyVals;
}
////////////////////////////////////////
double matrix::score(int index){
    int score = 0;
    //compare keyMatrix[ to frequency matrix
    //for each value add absolute value of (frequency matrix - key matrix) to score
    return score;
}
////////////////////////////////////////
bool matrix::compare(key A, key B){
    int score1,score2;
    //generate both matrixes
    //compare key matrix score to frequency matrix score
    if (score1<score2)
        return true;
    else
        return false;
}
////////////////////////////////////////
void key::mutate(int mutation){
    //mutate the cipher by a given mutation key
    //swap
    int score = 0;
}
////////////////////////////////////////
void key::optimize(){
    int score = 0;
    //generate score
    //swap one row
    //if new score higher, keep
    //else trash
    //continue
}
///////////////////////////////////////
string readFromFile(string filename){
    ifstream is (filename);
    if (is) {
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);
        
        char * buffer = new char [length];

        is.read (buffer,length);
        
        if (is)
            cout << "all characters read successfully."<<endl<<endl;
        else
            cout << "error"<<endl;
        
        is.close();
        filename = buffer;
        delete[] buffer;
    }
    else{
        cout<<"file could not be found"<<endl;
        filename="";
    }
    return filename;
}
//////////////////////////////////////////
vector<string> readFromFileLines(string filename){
    ifstream is (filename);
    string line;
    vector<string> lines;
    while (getline(is, line))
    {
        lines.push_back(line);
    }
    return lines;
}

/////////////////////////////////////////////
vector<int> toVector(string cypher){
    vector<int> out;
    stringstream ss(cypher);
    int i;
        
    while (ss >> i)
    {
        out.push_back(i);
            
        if (ss.peek() == ',')
            ss.ignore();
    }
    return out;
}
/////////////////////////////////////////////
string decrypt(vector<int> cypher, vector<char> key){
    string out = "";
    for(int i = 0; i < cypher.size();i++){
        out =out + key[cypher[i]] ;
    }
    return out;
}
/////////////////////////////////////////////
void printGuess(string guess){
    cout<<"Our best guess for the plaintext of the cypher given is:\n"<<guess<<endl;
}
/////////////////////////////////////////////
