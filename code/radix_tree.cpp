#include"radix_tree.h"

using namespace std;

//Define constructor for rt_node
//using the initializer list syntax to set the compref member to an empty string
rt_node::rt_node()
    :compref(""), is_word(false), frequency(0)
    {}

rt_node::~rt_node(){}

//the constructor of RadixTree initialize the root to an empty rt_node
RadixTree::RadixTree():root(make_shared<rt_node>()), recorderString(""){}

//destructor
RadixTree::~RadixTree(){}

void RadixTree::insert(const string& word, const long long& freq){
    radix_insert(root, word, freq);
}

void RadixTree::findPossibleWordsByPrefix(shared_ptr<rt_node>node, const string& prefix, vector<shared_ptr<rt_node>>& storageVector){

    //Look at each child of the node
    if(node->children.size() > 0){
        for (auto child : node->children){
            int commonPrefLen = getLenOfCommonPrefix(child->compref, prefix);
            //if a node with fully/partially matching prefix is found
            if(commonPrefLen > 0){
                //if child's string fully matches the prefix
                if(static_cast<size_t>(commonPrefLen) == prefix.size()){
                    //starting from the child node, 
                    //recursively traverse the tree until all
                    //possible branches are explored
                    recursive_trav_n_record(child, storageVector);
                    return;
                }
                //if only partially matching
                else{
                    //extract the remainder, and recursively call the function
                    string remainder = prefix.substr(commonPrefLen);
                    findPossibleWordsByPrefix(child, remainder, storageVector);
                    return; 
                }
            }
        } 
    }
    //do nothing if no children 
}

void RadixTree::giveSuggestions(vector<shared_ptr<rt_node>>& storageVector, const string& prefix){
    //initialize the recorder string to the first to the second to last character of the prefix
    recorderString = prefix.substr(0, prefix.length() - 1);

    findPossibleWordsByPrefix(root, prefix, storageVector);
    if(storageVector.size() > 0){
        sort(storageVector.begin(), storageVector.end(), 
            [](const shared_ptr<rt_node>& a, const shared_ptr<rt_node>& b) {
                return a->frequency < b->frequency; // ascending order
            });
    }
    recorderString = "";
}

//additional utilities

void RadixTree::radix_insert(shared_ptr<rt_node> node, const string& word, const long long& freq){
    
    //base case
    if(word.empty()){
        node->is_word = true;
        node->frequency = freq;
        return;
    }
    //Children exist
    if(node->children.size() > 0){
        //look at each of the node's children
        for(const auto&child : node->children){
            int commonPrefLen = getLenOfCommonPrefix(child->compref, word);
            //CASE 1: A child with common prefix exists
            if(commonPrefLen > 0){
                //CASE 1a: The common prefix is only a part of the child
                if(static_cast<size_t>(commonPrefLen) < child->compref.size()){
                    //create an empty rt_node
                    shared_ptr<rt_node> newChild = make_shared<rt_node>();
                    //assign to it the remaining letters that's not common from the child
                    newChild->compref = child->compref.substr(commonPrefLen);
                    //new child inherits the old child's metadata
                    newChild->is_word = child->is_word;
                    newChild->frequency = child->frequency;
                    //new child inherits the old child's children
                    newChild->children = child->children;
                    //old child will only keep the common prefix.
                    child->compref = child->compref.substr(0, commonPrefLen);
                    //clear out old child's children
                    child->children.clear();
                    //reset old child's metadata
                    child->is_word = false;
                    child->frequency = 0;
                    //old child will now adopt the new child
                    child->children.push_back(newChild);
                }
                
                //CASE 1b: The common prefix is the entirety of the child
                //OR the last step of CASE 1a
                string remainderOfWord = word.substr(commonPrefLen);
                return radix_insert(child, remainderOfWord, freq);
            }
        }
    }

    //CASE 2: No children OR no children with common prefix
    shared_ptr<rt_node> new_rtNode = make_shared<rt_node>();
    new_rtNode->compref = word;
    new_rtNode->is_word = true;
    new_rtNode->frequency = freq;
    node->children.push_back(new_rtNode);
    return;
}


int RadixTree::getLenOfCommonPrefix(const string& s1, const string& s2){
    int length = 0;
    //compare char by char starting from index 0, return length either when a different char is encountered or
    //one of the strings runs out of chars, whichever happens earlier.
    while(static_cast<size_t>(length) < s1.size() && static_cast<size_t>(length) < s2.size() && s1[length] == s2[length]){
        length++;
    }
    return length;
}

void RadixTree::visit_node(shared_ptr<rt_node> node){
    recorderString += node->compref;
}

void RadixTree::exit_node(shared_ptr<rt_node> node){
    recorderString = recorderString.substr(0, (recorderString.length() - node->compref.length()));
}

void RadixTree::recursive_trav_n_record(shared_ptr<rt_node>node, vector<shared_ptr<rt_node>>&collection){
    //read the common prefix into the recorderString
    visit_node(node);
    //if a word is encountered
    if(node->is_word){
        auto new_node = make_shared<rt_node>();
        new_node->compref = recorderString;
        new_node->frequency = node->frequency;
        collection.push_back(new_node);
    }

    //look at each child when children exist
    if(node->children.size() > 0){
        for(auto child : node->children){
            recursive_trav_n_record(child, collection);
        }
        //Once each child has been fully explored, exit the node and return
        exit_node(node);
        return;
    }

    //if childless
    else{
        //jump back to previous node
        exit_node(node);
        return;
    }
}