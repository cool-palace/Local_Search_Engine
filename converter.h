#ifndef SEARCH_ENGINE_CONVERTER_H
#define SEARCH_ENGINE_CONVERTER_H
#include <iostream>
#include <string>
#include "nlohmann/json.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include "search_server.h"

using std::vector;
using std::string;
using std::pair;
using std::ifstream;
using std::cout;
using std::ostringstream;

class Converter_JSON {
public:
    Converter_JSON() = default;
    nlohmann::json get_config();
    vector<string> get_text_documents();
    int get_responses_limit();
    vector<string> get_requests();
    void put_answers(const vector<vector<Relative_Index>>& answers);
};

class bad_config: public std::exception {
    const char* what() const noexcept override { return "The config file is empty."; }
};

#endif //SEARCH_ENGINE_CONVERTER_H