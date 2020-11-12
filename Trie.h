#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

const int SIZE = 256; 
const string extensionFile = ".mp4";
const string dataFile = "dataset.txt";

class TrieNode{
private:
    vector <TrieNode*> nodos;
    bool isEnd = false; 
    vector<unsigned long> posDisk;
    vector<string> resultStartWith;

    TrieNode* searchUtil(string key){
        TrieNode* temp = this;
        for(int i = 0; i < key.size(); i++){
            int pos = (int)key[i];
            if(!temp->nodos[pos]){
                return nullptr;
            }
            temp = temp->nodos[pos]; 
        }
        return temp;
    }

    void startWithUtil(TrieNode* tnode, int i, string result){
        result += (char) i;
        if(tnode->isEnd){
            resultStartWith.push_back(result);
        }
        for(int i = 0; i < tnode->nodos.size(); i++){
            if(tnode->nodos[i]){
                startWithUtil(tnode->nodos[i], i, result);
            }
        }
    }

public:
    TrieNode(): nodos(SIZE,nullptr){};

    void insert(string word, int position=-1){
        TrieNode* temp = this;
        int pos;
        for(int i = 0; i < word.size(); i++){
            pos = (int)word[i] ;
            if(!temp->nodos[pos]){
                temp->nodos[pos] = new TrieNode;
            }
            temp = temp->nodos[pos];
        }
        temp->isEnd = true;
        temp->posDisk.push_back(position);
    }
    
    void search(string key){
        cout << "** Search: '" << key << "' **\n";
        auto temp = searchUtil(key);
        if (temp != nullptr && temp->isEnd){
            int nroVeces = temp->posDisk.size();
            string printVeces = (nroVeces > 1) ? "veces.\n" : " vez.\n";
            cout << "a) Archivo repetido: " <<  nroVeces <<  printVeces;
            string buf;
            fstream fileList(dataFile);
            cout << "b) Ruta de archivos encontrados: \n";
            for(int i = 0; i < temp->posDisk.size(); i++){
                fileList.seekg(temp->posDisk[i]);
                getline(fileList, buf);
                cout << buf << endl;
            }
            fileList.close();
        }
        else{
            cout << "Not Found!\n";
        } 
    }
    
    void startWith(string partialKey){
        cout << "** Search keywords start with: " << partialKey << " **\n";
        auto temp = searchUtil(partialKey);
        if(temp == nullptr){
            cout << "c) Ningun archivo inicia con: " << partialKey << "\n";
            return;
        }
        string result = partialKey;
        resultStartWith.clear();
        for(int i = 0; i < temp->nodos.size(); i++){
            if(temp->nodos[i]){
                startWithUtil(temp->nodos[i], i, result);
            }
        }

        cout << "c) Archivos que inician con: " << partialKey << "\n";
        for(int i = 0; i < resultStartWith.size(); i++){
            cout << resultStartWith[i] << extensionFile << "\n";
        }
    }

    void indexer(){
        cout << "** Indexer **\n";
        //system("find /Users/angelinux/Data -type f -name \"*.mp4\" > list.txt");
        fstream fileList(dataFile);
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
            cout << " Insert filename: " << filename << ", Start position in disk file: " << posStartLine << '\n';
            // Insert into Trie Structure
            this->insert(filename, posStartLine);  
            posStartLine = fileList.tellg();
        }
        
        fileList.close();
    }

};

#endif