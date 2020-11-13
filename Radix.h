#ifndef RADIX_H
#define RADIX_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

const int SIZE = 256;

class RadixNode{
    vector <RadixNode*> nodos;
    bool isEnd = false;
    string word;
    //vector<char> inserted;

public:
    RadixNode(string &cname):nodos(SIZE,nullptr), word(cname) {};
    RadixNode(string &cname, bool _isEnd):nodos(SIZE,nullptr), word(cname), isEnd(_isEnd) {};

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
                newnode->isEnd = true;
                //newnode->nodos[word[++idx]] = new RadixNode();
                return newnode; // retornano el padre
            }
            idx++;
        }

        if(idx == word.size()-1){
            auto newnode= new RadixNode(common);
            this->word = temp->word.substr(common.size(), (temp->word.size() - common.size());
            newnode->nodos[this->word[0]] = this;
            newnode->isEnd = true;
            return newnode;
        }

        if(idx < word.size()){
            idx++;
            this->nodos[word[idx]] = insert(word,idx);
        }
        return this;
    }

    bool search(string &w,int pos){
        int i;
        for(i = pos; i < this->word.size() && i < w.size() ; i++){
            if(w[pos] != this->word[pos])
                return false;
        }

        if(i >= w.size()){
            if(this->isEnd) return true;
            else return false;
        }

        if(this->nodos[w[i]])
            return this->nodos[w[i]]->search(w,i);
        else return false;

    };


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

class RadixTree{
private:
    RadixNode* root;
public:
    RadixTree(): root{nullptr} {}
    void insert(string &n){
        if(!root)
            root = new RadixNode(n,true);
        root = root->insert(n, 0);
    }
    void search(string n){
        root->search(n,0);
    }
};


#endif