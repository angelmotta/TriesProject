#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

const int SIZE = 256; 

class TrieNode{
    vector <TrieNode*> nodos;
    //Node* nodos[SIZE];    
    bool isEnd = false; 
    /*int childnum;*/
    //int buffsize;
    vector<unsigned long> posDisk;

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
    
    bool search(string key){
       TrieNode* temp = this;
       for(int i = 0; i < key.size(); i++){
           int pos = (int)key[i];
           if(!temp->nodos[pos])
              return false;
           temp = temp->nodos[pos]; 
       }

       bool found = temp!=nullptr && temp->isEnd;
       if (found){
           string buf;
            fstream fileList("list.txt");
           for(int i = 0; i < temp->posDisk.size(); i++){
               fileList.seekg(temp->posDisk[i]);
               getline(fileList, buf);
               cout << buf << endl;
           }
           fileList.close();
           return true;
       } 
       return false;
    }
    /*void remove(){

    } */
    
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


/*
class Node{
    Node* nodos[SIZE];
    
public:
    
}; */
/*
class Fnode:public Node{
    int buffSize;
    int reps;

    private: 

};

*/
#endif