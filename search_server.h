#ifndef SEARCH_ENGINE_SEARCH_SERVER_H
#define SEARCH_ENGINE_SEARCH_SERVER_H
#include <set>
#include "inverted_index.h"

struct Relative_Index {
    size_t doc_id;
    float rank;

    bool operator==(const Relative_Index& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class Search_Server {
public:
    Search_Server(const Inverted_Index& idx) : _index(idx) {};
    std::vector<std::vector<Relative_Index>> search(const std::vector<std::string>& queries_input);

private:
    Inverted_Index _index;
    std::set<std::string> query_words(const std::string& query);
    std::multimap<int, std::string> words_by_rareness(const std::set<std::string>& words);
    std::set<size_t> exclusive_ids(std::multimap<int, std::string> sorted_words);
    std::set<size_t> found_ids(std::multimap<int, std::string> sorted_words);
    std::vector<Relative_Index> relevance_map(const std::set<size_t>& docs, const std::set<std::string>& unique_words);
};

#endif //SEARCH_ENGINE_SEARCH_SERVER_H
