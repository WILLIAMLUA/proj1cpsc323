/*
* William Lua
* CPSC 323-03 13570
* Project Assignment 1
*/

#include <iostream>
#include <fstream>
using namespace std;

// Keywords
bool isKeyword(string key) {
    string keywords[32] = {"auto","break","case","char","const","continue","default",
                            "do","double","else","enum","extern","float","for","goto",
                            "if","int","long","register","return","short","signed",
                            "sizeof","static","struct","switch","typedef","union",
                            "unsigned","void","volatile","while"};
    for(int i = 0; i < 32; ++i) {
        if(keywords[i] == key) {
            return true;
        }
    }
    return false;
}

int main() {
    char ch;
    string key = "", k = "";
    int read[256] = {0};
    
    // operators 
    string logical_op = "><", math_op = "+-*/=", numer = ".0123456789", other = ",;\()[]''";
    ifstream fin("input_scode.txt");
    
    // opens and reads txt file 
    if(!fin.is_open()){
        cout<<"error while opening the file\n";
        return 1;
    }
    ofstream fout("output.txt");
    fout << "token" << "                " << "lexeme\n";
    fout << "---------------------------\n";
    
    // loop through/test conditions i.e if operator and output to txt file
    while(fin.get(ch)) {
        if(isalnum(ch)) {
            key += ch;
        }
        else if((ch == ' ' || ch == '\n') && (!key.empty())) {
            if(isKeyword(key)) {
                fout << "keyword" << "              " << key << "\n";
            }
            else {
                if(isalpha(key[0]) && !read[key[0]]) {
                    fout << "identifier" << "           " << key[0] << "\n";
                    read[key[0]] = 1;
                }
            }
            key = "";
        }
        if(numer.find(ch) != string::npos) {
            k += ch;
        }
        else if(!k.empty()) {
            fout << "real" << "                  " << k << "\n";
            k = "";
        }
        if(math_op.find(ch) != string::npos && !read[ch]) {
            fout << "operator" << "             " << ch << "\n";
            read[ch] = 1;
        }
        if(logical_op.find(ch) != string::npos && !read[ch]) {
            fout << "operator" << "             " << ch << "\n";
            read[ch] = 1;
        }
        if(other.find(ch) != string::npos && !read[ch]) {
            fout << "separator" << "            " << ch << "\n";
            read[ch] = 1;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
