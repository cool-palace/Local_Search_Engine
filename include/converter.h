#ifndef SEARCH_ENGINE_CONVERTER_H
#define SEARCH_ENGINE_CONVERTER_H
#include <iostream>
#include <string>
#include "nlohmann/json.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include "search_server.h"

class Converter_JSON {
public:
    Converter_JSON() = default;
    std::vector<std::string> get_text_documents();
    int get_responses_limit();
    std::vector<std::string> get_requests();
    void put_answers(const std::vector<std::vector<Relative_Index>>& answers);

private:
    nlohmann::json get_config();
};

class bad_config: public std::exception {
    const char* what() const noexcept override { return "The config file is empty."; }
};

#endif //SEARCH_ENGINE_CONVERTER_H