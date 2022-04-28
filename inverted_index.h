#ifndef SEARCH_ENGINE_INVERTED_INDEX_H
#define SEARCH_ENGINE_INVERTED_INDEX_H
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

struct Entry {
    size_t doc_id, count;

    bool operator==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {
public:
    InvertedIndex() = default;
    void update_document_base(const std::vector<std::string>& input_docs);
    std::vector<Entry> get_word_count(const std::string& word);

private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
};

#endif //SEARCH_ENGINE_INVERTED_INDEX_H
