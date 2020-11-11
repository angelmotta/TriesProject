#ifndef RADIX_H
#define RADIX_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

const int SIZE = 256; 

class RadixNode;

class RadixTree{
    RadixNode* root;
public: 
    void insert(string n){
        root = root->insert(n, 0);
    }
};

class RadixNode{
    vector <RadixNode*> nodos;
    bool isEnd = false;
    string word;
    //vector<char> inserted; 

public:
    RadixNode(string cname):nodos(SIZE,nullptr), word(cname) {};

    

    RadixNode* insert(string word,int pos){    
        RadixNode * temp = this;
        int idx = pos;
        string common; /*comun*/
        string tempString = temp->word;

        while(idx < temp->word.size() && idx < word.size()){
            if(tempString[idx] == word[idx]){
                common.push_back(tempString[idx]);
            }
            else{
                auto newnode = new RadixNode(common); //padre
                string notCommon = temp->word.substr(common.size(), (temp->word.size() - common.size());
                temp->word = notCommon;
                string notCommon2 = word.substr(pos + common.size(), (word.size() - common.size());
                newnode->nodos[notCommon2[0]] = new RadixNode(notCommon2);
                newnode->nodos[notCommon[0]] = this;
                //newnode->nodos[word[++idx]] = new RadixNode();
                return newnode; // retornano el padre
            }
            idx++;
        }

        if(idx == word.size()-1){
            auto newnode= new RadixNode(common);
            this->word = temp->word.substr(common.size(), (temp->word.size() - common.size());
            newnode->nodos[this->word[0]] = this;
            return newnode;
        }

        if(idx < word.size()){
            idx++;
            this->nodos[word[idx]] = insert(word,idx);
        }
        return this;
    }

    void search(string word){

    }

    
    void indexer(){
        cout << "** Indexer **\n";
        //system("find /Users/angelinux/Data -type f -name \"*.mp4\" > list.txt");
        fstream fileList("list.txt");
        string line;
        string filename;
        unsigned long posStartLine = 0;
        while(getline(fileList, line)){
            filename = "";
            for(int i = line.size() - 5; i >= 0; i--){
                if(line[i] == '/'){
                    break;
                }
                filename += line[i];
            }
            reverse(filename.begin(), filename.end());
            cout << " Insert filename: " << filename << " Start pos: " << posStartLine << '\n';
            // Insert into Trie Structure
            this->insert(filename, posStartLine);  
            posStartLine = fileList.tellg();
        }
        
        fileList.close();
    }

};





#endif