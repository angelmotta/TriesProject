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

    auto root = new TrieNode();
    for(int i=0; i < keys.size(); i++){
        root->insert(keys[i]);
    }
    cout << root->search("hola") << endl;
    cout << root->search("hol") << endl;
    cout << root->search("agf") << endl;

}

void testIndex(){
    auto rootTrie = new TrieNode;
    rootTrie->indexer();
    cout << rootTrie->search("animations-10-assignment-problem") << '\n';
    cout << rootTrie->search("animations-10-assignment-problex") << '\n';
}

int main(){
    //test1();
    testIndex();
}