#ifndef RADIX_H
#define RADIX_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


int MEMORIA = 0;

const int SIZEN = 256;

class RadixNode{
    vector <RadixNode*> nodos;
    bool isEnd = false;
    string word;
    vector<long long int> posDisks;
    //vector<char> inserted;

public:
    RadixNode(string &cname):nodos(SIZEN,nullptr), word(cname) {
        MEMORIA += sizeof(this);
    };
    RadixNode(string &cname, bool _isEnd):nodos(SIZEN,nullptr), word(cname), isEnd(_isEnd) {
        MEMORIA += sizeof(this);
    };
    RadixNode(string &cname, bool _isEnd, long long int _posDisk):nodos(SIZEN,nullptr), word(cname), isEnd(_isEnd) {
        posDisks.push_back(_posDisk);
        MEMORIA += sizeof(this);
    };

    int getRepetidos(){
        return posDisks.size();
    }

    void read(string filename){
        ifstream file(filename,ios::binary);
        string data;
        cout << "Archivos encontrados: " << endl;
        for(int i  = 0; i < posDisks.size() ; i++){
            file.seekg(posDisks[i]);
            getline(file,data);
            cout << data << endl;
        }
        file.close();
    }

    RadixNode* insert(string word,int pos, long long int _posDisK){
        RadixNode * temp = this;
        int idx = pos;
        string common; /*comun*/
        string tempString = temp->word;
        int i= 0;
        while(i < temp->word.size() && idx < word.size()){
            if(tempString[i++] == word[idx]){
                common.push_back(word[idx]);
            }
            else{
                auto newnode = new RadixNode(common); //padre
                string notCommon = temp->word.substr(common.size(), (temp->word.size() - common.size()));
                temp->word = notCommon;
                string notCommon2 = word.substr(pos + common.size(), (word.size() - common.size()));
                newnode->nodos[notCommon2[0]] = new RadixNode(notCommon2,true,_posDisK);
                newnode->nodos[notCommon[0]] = this;
                newnode->isEnd = false;
                return newnode; // retornano el padre
            }
            idx++;
        }

        if(idx == word.size()){
            if(idx == this->word.size()){
                this->posDisks.push_back(_posDisK);
                this->isEnd = true;
                return this;
            }
            else{
                auto newnode= new RadixNode(common);
                this->word = temp->word.substr(common.size(), (temp->word.size() - common.size()));
                newnode->nodos[this->word[0]] = this;
                newnode->isEnd = true;
                newnode->posDisks.push_back(_posDisK);
                return newnode;
            }
        }

        if(idx < word.size()){
            if(!this->nodos[word[idx]]){
                string notcommon = word.substr(common.size(),(word.size()-common.size()));
                this->nodos[word[idx]] = new RadixNode(notcommon,true,_posDisK);
            }
            else
                this->nodos[word[idx]] = this->nodos[word[idx]]->insert(word,idx,_posDisK);
        }
        return this;
    }


    RadixNode* search(string &w,int pos){
        int i;
        int j = 0;
        for(i = pos; j < this->word.size() && i < w.size() ; i++){
            if(w[i] != this->word[j++])
                return nullptr;
        }
        if(j < this->word.size()){
            return nullptr;
        }
        if(i >= w.size()){
            if(this->isEnd) return this;
            else return nullptr;
        }

        if(this->nodos[w[i]])
            return this->nodos[w[i]]->search(w,i);
        else return nullptr;

    };
};

class RadixTree{
private:
    RadixNode* root;
    string filename;    
public:
    RadixTree(string _filename): filename(_filename), root{nullptr} {}

    void insert(string &n, long long int posDisk){
        if(!root)
            root = new RadixNode(n,true,posDisk);
        else
            root = root->insert(n, 0,posDisk);
    }
    RadixNode* search(string n){
        cout << "SEARCH: " << n << endl;
        auto result = root->search(n,0);
        if(!result)
            cout << "Not found" << endl;
        else {
            result->read(filename);
        }
        return result;
    }

    void indexer(){
        cout << "** Indexer **\n";
        //system("find /Users/angelinux/Data -type f -name \"*.mp4\" > list.txt");
        fstream fileList("dataset.txt");
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
    long int getMemSize(){
        cout << "Memoria: " << MEMORIA + sizeof(this) << " B"<< endl;
        return MEMORIA + sizeof(this);
    }
};


#endif