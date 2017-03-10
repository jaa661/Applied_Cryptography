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

map<char,int> LETTERS_FREQUENCY = { {'a',5}, {'b',1}, {'c',2}, {'d',2}, {'e',8}, {'f',1} ,{'g',1} ,{'h',4} , {'i',4},{'j',1},{'k',1},{'l',2},{'m',1},{'n',4},{'o',5},{'p',1},{'q',1},{'r',3},{'s',4},{'t',5},{'u',1} ,{'v',1},{'w',1},{'x',1},{'y',1},{'z',1} };
map<char,int> LETTERS_VALUE = {{'a',0}, {'b',1}, {'c',2}, {'d',3}, {'e',4}, {'f',5} ,{'g',6} ,{'h',7} , {'i',8},{'j',9},{'k',10},{'l',11},{'m',12},{'n',13},{'o',14},{'p',15},{'q',16},{'r',17},{'s',18},{'t',19},{'u',20} ,{'v',21},{'w',22},{'x',23},{'y',24},{'z',25} };

class key{
public:
    key();//generates a random key
    key mutate(int mutate = 2);//mutates the key by specified value
    void printKey();
    vector<char> getKey();
private:
    vector<char> keyVals;
    int keyLength = 62;
};


void decryptString(string& encryptedString, ifstream& ifs, int rotation, string& decryptedString);
string readFromFile(string filename);
vector<int> toVector(string cypher);
string decrypt(vector<string> dict, vector<int> cypher, vector<char> key);
void printGuess(string guess);
vector<string> readFromFileLines(string filename);




int main(){

    string encrypted = ""; // store the original text in a string
    vector<string> dict;
    vector<int> cypher;
    string decryptedString = ""; // assemble the decrypted text here
    string input = "1";
    bool done = false;
    
    while(!done){
        cout<<"Enter option:\n(1)load file 'Cypher.txt'\n(2)enter via keyboard"<<endl;
        //cin>>input;
        cout<<"ROIPIPRIOPOI"<<endl;
        key firstKey;
        cout<<"RAIPIPI"<<endl;
        if (input == "1"){
            encrypted = readFromFile("/Users/pierules53/Desktop/Current\ Homework/Crypto/CypherZ.txt");
            dict = readFromFileLines("/Users/pierules53/Desktop/Current\ Homework/Crypto/english_words.txt");
            cypher = toVector(encrypted);
            firstKey.printKey();
            string guess = decrypt(dict,cypher,firstKey.getKey());
            printGuess(guess);
            done = true;
        }
        else if (input == "2"){
            cin>>encrypted;
            dict = readFromFileLines("/Users/pierules53/Desktop/Current\ Homework/Crypto/english_words.txt");
            cypher = toVector(encrypted);
            string guess = decrypt(dict,cypher,firstKey.getKey());
            printGuess(guess);
            done = true;
        }
        else{
            cout<<"not a valid option"<<endl;
        }
    }
return 0;
}
////////////////////////////////////////
key::key(void){
    map<char, int>::iterator it;
    map<char, int>::iterator it2;
    int randomIndex;
    int possibleValues = keyLength;
    vector<int> listTo105;
    vector<char> temp;
    it2 = LETTERS_VALUE.begin();
    cout<<"RIPPP";
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
void key::printKey(){
    for(int i = 0; i < keyVals.size(); i++){
            cout <<keyVals[i]<<", ";
    }
    cout <<endl;
}
////////////////////////////////////////
vector<char> key::getKey(){
    return keyVals;
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
string decrypt(vector<string> dict, vector<int> cypher, vector<char> key){
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
