#ifndef SEARCH_ENGINE_SEARCH_SERVER_H
#define SEARCH_ENGINE_SEARCH_SERVER_H

#include <set>
#include "inverted_index.h"

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
    SearchServer(const InvertedIndex& idx) : _index(idx) {};
    std::set<std::string> query_words(const std::string& query);
    std::multimap<int, std::string> words_by_rareness(const std::set<std::string>& words);
    std::set<size_t> found_ids(std::multimap<int, std::string> sorted_words);
    std::vector<RelativeIndex> relevance_map(const std::set<size_t>& docs, const std::set<std::string>& unique_words);
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    InvertedIndex _index;
};


#endif //SEARCH_ENGINE_SEARCH_SERVER_H
