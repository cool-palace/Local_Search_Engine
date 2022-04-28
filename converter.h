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
    return get_config()["config"]["max_responses"];
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

void ConverterJSON::put_answers(const vector<vector<pair<int, float>>>& answers) {
    if (answers.empty()) return;
    nlohmann::json j;
    for (int i = 0, requests_count = answers.size(); i < requests_count; ++i) {
        auto number = std::to_string(i + 1);
        while (number.size() < 3) {
            number = "0" + number;
        }

        j["answers"]["request" + number] = {{"result", !answers[i].empty()}};

        if (answers[i].empty()) continue;
        if (answers[i].size() == 1) {
            j["answers"]["request" + number]["docid"] = answers[i].back().first;
            j["answers"]["request" + number]["rank"] = answers[i].back().second;
        } else for (const auto& pair : answers[i]) {
            j["answers"]["request" + number]["relevance"] += {{"docid", pair.first}, {"rank", pair.second}};
        }
    }
    std::ofstream answer_file("answers.json", std::ofstream::trunc);
    answer_file << j;
    answer_file.close();
}

#endif //SEARCH_ENGINE_CONVERTER_H
