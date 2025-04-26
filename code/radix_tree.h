#ifndef RADIX_TREE_H
#define RADIX_TREE_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<algorithm>



using namespace std;

struct rt_node {
    string compref;
    //using shared_ptr to let c++ handle memory managment
    vector<shared_ptr<rt_node>> children;
    //metadata
    bool is_word;
    long long frequency;
    //constructor
    rt_node();
    //destructor
    ~rt_node();
};

class RadixTree {
    public:
        //constructor
        RadixTree();
        //deconstructor
        ~RadixTree();
        //insert operation
        void insert(const string& word, const long long& freq);
        void findPossibleWordsByPrefix(shared_ptr<rt_node>node, const string& prefix, vector<shared_ptr<rt_node>>& storageVector);
        void giveSuggestions(vector<shared_ptr<rt_node>>& storageVector, const string& prefix);

        //additional utilities
        void radix_insert(shared_ptr<rt_node> node, const string& word, const long long& freq);
        int getLenOfCommonPrefix(const string& s1, const string& s2);
        void visit_node(shared_ptr<rt_node> node);
        void exit_node(shared_ptr<rt_node> node);
        void recursive_trav_n_record(shared_ptr<rt_node>node, vector<shared_ptr<rt_node>>&collection);
    private:
        shared_ptr<rt_node> root;
        string recorderString;
};


#endif
