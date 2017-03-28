// HW00
// Jacob Abbott 
// cs 1124

#include <iostream> 
#include <string>
#include <fstream>
#include <vector>
#include <map>


using namespace std;

string readFromFile(string filename);
void writeToFile(string cypher);
void encryptString(string& encryptedString, ifstream& ifs, int rotation, string& decryptedString);
string encrypt(string plain, vector<int> maps[]);


int main(){

    map<char,int> LETTERS_FREQUENCY = { {' ', 19}, {'a',7}, {'b',1}, {'c',2}, {'d',4}, {'e',10}, {'f',2} ,{'g',2} ,{'h',5} , {'i',6},{'j',1},{'k',1},{'l',3},{'m',2},{'n',6},{'o',6},{'p',2},{'q',1},{'r',5},{'s',5},{'t',7},{'u',2} ,{'v',1},{'w',2},{'x',1},{'y',2},{'z',1} };
    
    vector<int> listTo105;
    for(int i = 0; i < 19; i++){
        listTo105.push_back(0);
    }
    for(int i = 0; i < 7; i++){
        listTo105.push_back(1);
        listTo105.push_back(20);
    }
    for(int i = 0; i < 6; i++){
        listTo105.push_back(9);
        listTo105.push_back(14);
        listTo105.push_back(15);
    }
    for(int i = 0; i < 5; i++){
        listTo105.push_back(8);
        listTo105.push_back(18);
        listTo105.push_back(19);
    }
    for(int i = 0; i < 10; i++){
        listTo105.push_back(5);
    }
    for(int i = 0; i < 4; i++){
            listTo105.push_back(4);
    }
    for(int i = 0; i < 3; i++){
        listTo105.push_back(12);
    }
    for(int i = 0; i < 2; i++){
        listTo105.push_back(3);
        listTo105.push_back(6);
        listTo105.push_back(7);
        listTo105.push_back(13);
        listTo105.push_back(16);
        listTo105.push_back(21);
        listTo105.push_back(23);
        listTo105.push_back(25);
    }
    for(int i = 0; i < 1; i++){
        listTo105.push_back(2);
        listTo105.push_back(10);
        listTo105.push_back(11);
        listTo105.push_back(17);
        listTo105.push_back(22);
        listTo105.push_back(24);
        listTo105.push_back(26);
    }
    vector<int> maps[27];
    int randomIndex = 0;
    for(int i= 0;i<106; i++){
        randomIndex = rand() % (106-i);
        maps[listTo105[randomIndex]].push_back(i);
        listTo105.erase(listTo105.begin() + randomIndex);
    }
    
    //for(int i = 0;i<27;i++){
        //for(int j=0;j<maps[i].size();j++){
         //   cout<< maps[i][j]<<" ";
       // }
       // cout<<endl;
   // }
    string plain = ""; // store the original text in a string
    string cypher = ""; // assemble the decrypted text here
    string input = "";
    bool done = false;
    
    while(!done){
    cout<<"Enter option:\n(1)load file 'Plaintext.txt'\n(2)enter via keyboard"<<endl;
    cin>>input;
    if (input == "1"){
        plain = readFromFile("/Users/pierules53/Desktop/Current\ Homework/Crypto/Homophonic/Plaintext2.txt");
        cypher = encrypt(plain, maps);
        cout<<"Enter option:\n(1)output to file 'Cypher.txt'\n(2)output via keyboard"<<endl;
        cin>>input;
        if (input == "1"){
        writeToFile(cypher);
        }
        else if (input == "2"){
            cout<< cypher;
        }
        else{}
        done = true;
    }
    else if (input == "2"){
        cin>>plain;
        cypher = encrypt(plain, maps);
        cout<<"Enter option:\n(1)output to file 'Cypher.txt'\n(2)output via keyboard"<<endl;
        cin>>input;
        if (input == "1"){
            writeToFile(cypher);
        }
        else if (input == "2"){
            cout<< cypher;
        }
        else{}
        done = true;
        done = true;

    }
    else{
        cout<<"not a valid option"<<endl;
    }
    }
return 0;
}
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
////////////////////////////////////////////////////
void writeToFile(string cypher){
    ofstream myfile;
    myfile.open ("/Users/pierules53/Desktop/Current\ Homework/Crypto/Homophonic/Cypher.txt");
    myfile << cypher;
    myfile.close();
}
////////////////////////////////////////////////////
string encrypt(string plain, vector<int> maps[]){
    vector<char> plainV(plain.begin(), plain.end());
    string out = "";
    int ch;
    //cout<< plain<<endl;
    for(int i = 0; i < plainV.size(); i++){
        ch = (int(plainV[i])-96);
        if((int(plainV[i])-96) > 0){
            out = out + to_string(maps[ch][rand()%maps[ch].size()]) + ",";
        }
        else{
            out = out + to_string(maps[0][rand()%maps[0].size()]) + ",";
        }
    }
    return out;
}
////////////////////////////////////////////////////

