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
    void update_document_base(std::vector<std::string>&& input_docs);
    std::vector<Entry> get_word_count(const std::string& word);

private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
};

void InvertedIndex::update_document_base(std::vector<std::string>&& input_docs) {
    freq_dictionary.clear();
    docs = input_docs;
    for (size_t i = 0; i < docs.size(); ++i) {
        std::istringstream ss(docs[i]);
        std::string word;
        while (ss >> word) {
            if (freq_dictionary.count(word)) {
                bool same_doc = false;
                for (auto& entry : freq_dictionary[word]) {
                    if (entry.doc_id == i) {
                        ++entry.count;
                        same_doc = true;
                        break;
                    }
                }
                if (!same_doc) {
                    freq_dictionary[word].push_back({i, 1});
                }
            } else freq_dictionary[word].push_back({i, 1});
        }
    }
}

std::vector<Entry> InvertedIndex::get_word_count(const std::string &word) {
    if (freq_dictionary.count(word)) {
        return freq_dictionary[word];
    } else return std::vector<Entry>();
}


#endif //SEARCH_ENGINE_INVERTED_INDEX_H
