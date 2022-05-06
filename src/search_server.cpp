#include "../include/search_server.h"

std::set<std::string> Search_Server::query_words(const std::string& query) {
    std::set<std::string> unique_words;
    std::istringstream ss(query);
    std::string word;
    while (ss >> word) {
        unique_words.insert(word);
    }
    return unique_words;
}

std::multimap<int, std::string> Search_Server::words_by_rareness(const std::set<std::string>& words) {
    std::multimap<int, std::string> sorted_words;
    for (const auto& word : words) {
        int count = 0;
        for (const auto& entry : _index.get_word_count(word)) {
            count += entry.count;
        }
        sorted_words.insert(std::make_pair(count, word));
    }
    return sorted_words;
}

std::set<size_t> Search_Server::exclusive_ids(std::multimap<int, std::string> sorted_words) {
    std::set<size_t> doc_ids;
    for (auto it = sorted_words.begin(); it != sorted_words.end(); ++it) {
        auto word = (*it).second;
        std::cout << word << '\n';
        std::set<size_t> narrowed_ids;
        for (const auto& entry : _index.get_word_count(word)) {
            if (it == sorted_words.begin()) {
                doc_ids.insert(entry.doc_id);
            } else if (doc_ids.count(entry.doc_id)) {
                narrowed_ids.insert(entry.doc_id);
            }
        }
        if (it != sorted_words.begin()) {
            std::swap(doc_ids, narrowed_ids);
        }
        if (doc_ids.empty()) break;
    }
    return doc_ids;
}

std::set<size_t> Search_Server::found_ids(std::multimap<int, std::string> sorted_words) {
    std::set<size_t> doc_ids;
    for (auto it = sorted_words.begin(); it != sorted_words.end(); ++it) {
        auto word = (*it).second;
        for (const auto& entry : _index.get_word_count(word)) {
            doc_ids.insert(entry.doc_id);
        }
    }
    return doc_ids;
}

std::vector<Relative_Index> Search_Server::relevance_map(const std::set<size_t>& docs,
                                                         const std::set<std::string>& unique_words) {
    if (docs.empty()) return std::vector<Relative_Index>();

    std::multimap<int, size_t, std::greater<>> abs_relevance;
    for (auto doc_id : docs) {
        int frequency = 0;
        for (const auto& word : unique_words) {
            for (const auto& entry : _index.get_word_count(word)) {
                if (doc_id == entry.doc_id) {
                    frequency += entry.count;
                }
            }
        }
        abs_relevance.insert({frequency, doc_id});
    }

    int max = abs_relevance.begin()->first;
    std::vector<Relative_Index> relevance;
    for (auto it = abs_relevance.begin(); it != abs_relevance.end(); ++it) {
        float rank = static_cast<float>(it->first) / max;
        relevance.push_back({it->second, rank});
    }
    return relevance;
}

std::vector<std::vector<Relative_Index>> Search_Server::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<Relative_Index>> search_result;
    for (size_t i = 0; i < queries_input.size(); ++i) {
        auto unique_words = query_words(queries_input[i]);
        auto sorted_words = words_by_rareness(unique_words);
        auto docs = found_ids(sorted_words);
        auto query_search_result = relevance_map(docs, unique_words);
        search_result.push_back(std::move(query_search_result));
    }
    return search_result;
}