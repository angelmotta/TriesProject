#include <iostream>
#include <list>
#include <fstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


class Info{
public:
	vector<long long> paths;
};

class Node{
public:
	char letter;
	Node* children[3];
	Info* data;
	vector<string> paths;
	Node(char l){
		letter = l;
		children[0] = nullptr;
		children[1] = nullptr;
		children[2] = nullptr;
	}

	bool has_children(){
		for(int i=0; i<3; ++i){
			if(children[i] != nullptr){
				return true;
			}
		}
		return false;
	}

	void Insert(int i, int n, string key, long long inf){
		//cout << "letra "<<key[i] << endl;
		if(i<n-1){
			if(key[i] > letter){
				if(children[2] == nullptr){
					children[2] = new Node(key[i]);
				}
				children[2]->Insert(i, n, key, inf);
			}
			else if(key[i] < letter){
				if(children[0] == nullptr){
					children[0] = new Node(key[i]);
				}
				children[0]->Insert(i, n, key, inf);
			}
			else{
				if(children[1] == nullptr){
					children[1] = new Node(key[i+1]);
				}
				children[1]->Insert(i+1, n, key, inf);
			}
		}
		else if(i == n-1){
			//cout << "ultima letra: "<<letter << endl;
			if(data == nullptr){
				data = new Info();
			}
			data->paths.push_back(inf);
		}
	}
};

class TernarySearchTree{
	Node* root;
public:
	void Insert(string key, long long inf){
		if(root == nullptr){
			root = new Node(key[0]);
		}
		root->Insert(0, key.size(), key, inf);
	}
	
	Node* Find(string key){
		Node* aux = root;
		int i=0;
		int n = key.size();
		while(aux && i<n-1){
			if(aux->letter < key[i]){
				aux = aux->children[2];
			}
			else if(aux->letter > key[i]){
				aux = aux->children[0];
			}
			else{
				cout << "letter: "<<aux->letter << endl;
				aux = aux->children[1];
				++i;
			}
		}
		if(aux != nullptr || i != n-1){
			cout << "not found"<<endl;
			return nullptr;
		}
		return aux;
	}


	void indexer(string name_f){
        //system("find /Users/angelinux/Data -type f -name \"*.mp4\" > list.txt");
        fstream fileList(name_f);
        string line;
        string filename;
        unsigned long posStartLine = 0;
        while(getline(fileList, line)){
        	cout << line << endl;
            filename = "";
            for(int i = line.size() - 5; i >= 0; i--){
                if(line[i] == '/'){
                    break;
                }
                filename += line[i];
            }
            reverse(filename.begin(), filename.end());
           // cout << " Insert filename: " << filename << ", Start position in disk file: " << posStartLine << '\n';
            // Insert into Trie Structure
            Insert(filename, posStartLine);  
            posStartLine = fileList.tellg();
        }
        
        fileList.close();
    }

};

/*

int main(){

	TernarySearchTree* ts = new TernarySearchTree();
	ts->indexer("dataset2.txt");
	auto x = ts->Find("Slides");
	if(x){
		for(auto &v:x->data->paths){
			cout << v << endl;
		}
	}
	//auto x2 = ts->Find("^BAD63CD350431BD3D5DD7F6CF8CD9A9C9485C1CA285BCC8B2C^pdefault_distr");

	return 0;
}
*/