#include"../code/radix_tree.h"
#include "../code/httplib.h"
#include"json/json.h"

#include<fstream>
#include<sstream>
#include <cctype>

using namespace std;

int main(){
    ifstream file("Files/frequency_list.txt");

    string line;

    RadixTree new_radix_tree;

    if (!file) {
        cerr << "Could not open one of the files" << endl;
        return 1;
    }
    //build the radix tree
    while (getline(file, line)) {
        istringstream iss(line);
        string word;
        long long frequency;
        if (iss >> word >> frequency) {
            new_radix_tree.insert(word, frequency);
        }
    }
    

    //instantiate the server
    httplib::Server svr;

    // Match any path with regex
    svr.Get(R"(/(.*))", [&new_radix_tree](const httplib::Request& req, httplib::Response& res) {
        vector<shared_ptr<rt_node>> storageVector;

        string path = req.matches[1]; // 👈 capture what was typed after /

        transform(path.begin(), path.end(), path.begin(),
            [](unsigned char c) { return tolower(c); });

        new_radix_tree.giveSuggestions(storageVector, path);

        Json::Value json_response;

        if (storageVector.size() > 0) {
            cout << "entered block" << endl;
            //store the top three suggestions in a json response
            for (int i = 0; i < 3; i++) {
                json_response["suggestions"][i] = storageVector.back()->compref;
                storageVector.pop_back();
                if (storageVector.size() == 0) {
                    break;
                }
            }
        }


        //convert json response to json string
        Json::StreamWriterBuilder writer;
        string response_body = Json::writeString(writer, json_response);


        res.set_content(response_body, "application/json");

        res.set_header("Access-Control-Allow-Origin", "*");

        });

    svr.listen("0.0.0.0", 8080);

    //vector<shared_ptr<rt_node>> storageVector;

    //string prefix = "alrea";

    //new_radix_tree.giveSuggestions(storageVector, "alrea");

    return 0;

}