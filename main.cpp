#include "Trie.h"
using namespace std;

void test1(){
    vector<string> keys ;
    //{"hola", "hello","hipo","amigo", "amistad"}
    keys.push_back("hola");
    keys.push_back("hello");
    keys.push_back("hipo");
    keys.push_back("amigo");
    keys.push_back("amistad");
    keys.push_back("angel");
    keys.push_back("angelica");
    keys.push_back("antonio");
    auto root = new TrieNode();
    for(int i=0; i < keys.size(); i++){
        root->insert(keys[i]);
    }
    root->search("hola");
    root->search("hipo");
    root->search("hol");
    root->search("agf");

    // Start with
    root->startWith("ami");
    root->startWith("ang");
    root->startWith("an");
}

void testIndex(){
    auto rootTrie = new TrieNode;
    rootTrie->indexer();
    rootTrie->search("animations-10-assignment-problem");
    rootTrie->search("animations-10-assignment-prob");
}

int main(){
    test1();
    // testIndex();
}