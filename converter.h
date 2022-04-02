#ifndef SEARCH_ENGINE_CONVERTER_H
#define SEARCH_ENGINE_CONVERTER_H
#include <iostream>
#include <string>
#include "nlohmann/json.hpp"
#include <vector>
#include <fstream>
#include <sstream>

using std::vector;
using std::string;
using std::pair;
using std::ifstream;
using std::cout;
using std::ostringstream;

class ConverterJSON {
public:
    ConverterJSON() = default;
    nlohmann::json get_config();
    vector<string> get_text_documents();
    int get_responses_limit();
    vector<string> get_requests();
    void put_answers(const vector<vector<pair<int, float>>>& answers);
};

class bad_config: public std::exception {
    const char* what() const noexcept override { return "The config file is empty."; }
};

nlohmann::json ConverterJSON::get_config() {
    ifstream config_file("config.json", ifstream::in);
    nlohmann::json config;
    if (!config_file.is_open()) {
        throw bad_config();
    }
    config_file >> config;
    config_file.close();
    return config;
}

vector<string> ConverterJSON::get_text_documents() {
    vector<string> words;
    auto config = get_config();
    auto files = config["files"];

    for (const auto& path : files) {
        ifstream file(path, ifstream::in);
        if (!file.is_open()) {
            continue;
        }
        string s;
        getline(file, s);
        words.push_back(s);
//        while (!file.eof()) {
//            string s;
//            file >> s;
//            if (!s.empty()) words.push_back(s);
//        }
        file.close();
    }
    return words;
}

int ConverterJSON::get_responses_limit() {
    auto config = get_config();
    return config["config"]["max_responses"];
}

vector<string> ConverterJSON::get_requests() {
    ifstream request_file("requests.json", ifstream::in);
    nlohmann::json request;
    if (!request_file.is_open()) {
        return vector<string>();
    }
    request_file >> request;
    request_file.close();
    return request["requests"];
}


#endif //SEARCH_ENGINE_CONVERTER_H
