#include "../include/converter.h"

nlohmann::json Converter_JSON::get_config() {
    std::ifstream config_file("config.json", std::ifstream::in);
    nlohmann::json config;
    if (!config_file.is_open()) {
        throw bad_config();
    }
    config_file >> config;
    config_file.close();
    return config;
}

std::vector<std::string> Converter_JSON::get_text_documents() {
    std::vector<std::string> words;
    auto config = get_config();
    auto files = config["files"];

    for (const auto& path : files) {
        std::ifstream file(path, std::ifstream::in);
        if (!file.is_open()) {
            continue;
        }
        std::string s;
        std::getline(file, s);
        words.push_back(s);
        file.close();
    }
    return words;
}

int Converter_JSON::get_responses_limit() {
    return get_config()["config"]["max_responses"];
}

std::vector<std::string> Converter_JSON::get_requests() {
    std::ifstream request_file("requests.json", std::ifstream::in);
    nlohmann::json request;
    if (!request_file.is_open()) {
        return std::vector<std::string>();
    }
    request_file >> request;
    request_file.close();
    return request["requests"];
}

void Converter_JSON::put_answers(const std::vector<std::vector<Relative_Index>>& answers) {
    if (answers.empty()) return;
    nlohmann::json json;
    int max_responses_limit = get_responses_limit();
    for (int i = 0, requests_count = answers.size(); i < requests_count; ++i) {
        auto number = std::to_string(i + 1);
        while (number.size() < 3) {
            number = "0" + number;
        }

        json["answers"]["request" + number] = {{"result", !answers[i].empty()}};

        if (answers[i].empty()) continue;
        if (answers[i].size() == 1) {
            json["answers"]["request" + number]["docid"] = answers[i].back().doc_id;
            json["answers"]["request" + number]["rank"] = answers[i].back().rank;
        } else for (int j = 0; j < answers[i].size() && j < max_responses_limit; ++j) {
                json["answers"]["request" + number]["relevance"] += {{"docid", answers[i][j].doc_id}, {"rank", answers[i][j].rank}};
        }
    }
    std::ofstream answer_file("answers.json", std::ofstream::trunc);
    answer_file << json;
    answer_file.close();
}