#include <algorithm>
#include "../include/inverted_index.h"

std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return s;
}

void Inverted_Index::update_document_base(const std::vector<std::string>& input_docs) {
    freq_dictionary.clear();
    docs = input_docs;
    for (size_t i = 0; i < docs.size(); ++i) {
        std::istringstream ss(docs[i]);
        std::string word;
        while (ss >> word) {
            word = to_lower(word);
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

std::vector<Entry> Inverted_Index::get_word_count(const std::string &word) {
    if (freq_dictionary.count(word)) {
        return freq_dictionary[word];
    } else return std::vector<Entry>();
}