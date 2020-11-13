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
            //    cout << "notCommon: " << notCommon << endl;
             //   cout << "notCommon2: " << notCommon2 << endl;
                newnode->nodos[notCommon2[0]] = new RadixNode(notCommon2,true);
                newnode->nodos[notCommon[0]] = this;
                newnode->isEnd = false;
                //newnode->nodos[word[++idx]] = new RadixNode();
                return newnode; // retornano el padre
            }
            idx++;
        }

        if(idx == word.size()){
            if(idx == this->word.size()){
                this->isEnd = true;
                return this;
            }
            else{
                auto newnode= new RadixNode(common);
                this->word = temp->word.substr(common.size(), (temp->word.size() - common.size()));
                newnode->nodos[this->word[0]] = this;
                newnode->isEnd = true;
                return newnode;
            }
        }

        if(idx < word.size()){
            if(!this->nodos[word[idx]]){
                string notcommon = word.substr(common.size(),(word.size()-common.size()));
                this->nodos[word[idx]] = new RadixNode(notcommon,true);
            }
            else
                this->nodos[word[idx]] = this->nodos[word[idx]]->insert(word,idx);
        }
        return this;
    }

    bool search(string &w,int pos){
       // cout << "search this->name: " << this->word << endl;
        int i;
        int j = 0;
        for(i = pos; j < this->word.size() && i < w.size() ; i++){
            if(w[i] != this->word[j++])
                return false;
        }
        if(j < this->word.size()){
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
        else
            root = root->insert(n, 0);
    }
    bool search(string n){
        return  root->search(n,0);
    }
};


#endif