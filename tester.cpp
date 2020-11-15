#ifndef TESTER_H
#define TESTER_H
#include "Trie.h"
#include "Radix.h"
#include "TernarySearchTree.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
using namespace std;

class Tester{
private:
    string fileQuery;
    vector<string> keysQueries;
public:
    Tester(){
        fileQuery = "testqueries.txt";
        loadQueries();
    }

    void loadQueries(){
        fstream fileListQueries(fileQuery);
        string keyword;
        while(getline(fileListQueries, keyword)){
            cout << keyword << "\n";
            keysQueries.push_back(keyword);
        }
        cout << "Loaded " << keysQueries.size() << " filenames for queries";
    }

    void trieTester(){
        auto rootTrie = new TrieNode;
        rootTrie->indexer();        /* read dataset.txt, Create Trie and insert */
        
        // Execute 100 queries
        int timeExecution = 0;
        int numQueries = 0;
        // Search Operations: execute 100 queries reading testqueries.txt
        for(auto filename : keysQueries){
            auto t1 = std::chrono::high_resolution_clock::now();
            rootTrie->search(filename);
            numQueries++;
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            timeExecution += duration;
            cout << "elapsed time: " << duration << " microseconds\n";
        }
        
        // cout << "total time: " << timeExecution << "\n";
        double avgTime = (double)(timeExecution)/numQueries;
        cout << "\nTrie - Tiempo promedio de consulta: " << avgTime << " microseconds\n";
        cout << "\nTrie - Memory used: ";
        rootTrie->getMemSize();
    }

    void radixTester(){
        // Radix Tree
        cout << "\n Test Radix Tree **\n ";
        RadixTree radixTree("dataset.txt");
        radixTree.indexer();

        // Execute 100 queries
        int timeExecution = 0;
        int numQueries = 0;
        for(auto filename : keysQueries){
            auto t1 = std::chrono::high_resolution_clock::now();
            radixTree.search(filename);
            numQueries++;
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            timeExecution += duration;
            cout << "elapsed time: " << duration << " microseconds\n";
        }
        // cout << "total time: " << timeExecution << "\n";
        double avgTime = (double)(timeExecution)/numQueries;
        cout << "\nRadix Tree - Tiempo promedio de consulta: " << avgTime << " microseconds\n";

        radixTree.getMemSize();
    }

    void ternaryTester(){
        cout << "\n Test Ternary Tree **\n ";

        TernarySearchTree* ts = new TernarySearchTree();
	    ts->indexer("dataset.txt");
        
        // Execute 100 queries
        /*
        int timeExecution = 0;
        int numQueries = 0;
        for(auto filename : keysQueries){
            auto t1 = std::chrono::high_resolution_clock::now();
            ts->Find(filename);
            numQueries++;
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            timeExecution += duration;
            cout << "elapsed time: " << duration << " microseconds\n";
        }
        // cout << "total time: " << timeExecution << "\n";
        double avgTime = (double)(timeExecution)/numQueries;
        cout << "\nRadix Tree - Tiempo promedio de consulta: " << avgTime << " microseconds\n";
        */
    }

};

#endif