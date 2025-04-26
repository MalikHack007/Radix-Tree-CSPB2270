#include"../code/radix_tree.h"

#include<fstream>
#include<sstream>

using namespace std;

int main(){
    ifstream file("../Files/frequency_list.txt");

    string line;

    RadixTree new_radix_tree;

    if(!file){
        cerr << "Could not open one of the files" << endl;
        return 1;
    }
    while(getline(file, line)){
        istringstream iss(line);
        string word;
        long long frequency;
        if(iss >> word >> frequency){
            new_radix_tree.insert(word, frequency);
        }
    }
    string prefix = "whe";
    vector<shared_ptr<rt_node>> storageVector;
    new_radix_tree.giveSuggestions(storageVector, prefix);

    return 0; 
}