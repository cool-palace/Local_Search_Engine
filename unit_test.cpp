#include "gtest/gtest.h"
#include "inverted_index.h"
using namespace std;

void test_inverted_index_functionality (const vector<string>& docs,
                                        const vector<string>& requests,
                                        const vector<vector<Entry>>& expected) {
    vector<vector<Entry>> result;
    InvertedIndex idx;
    idx.update_document_base(docs);

    for (auto& request : requests) {
        vector<Entry> word_count = idx.get_word_count(request);
        result.push_back(word_count);
    }
    ASSERT_EQ(result, expected);
}

TEST(test_case_inverted_index, test_basic) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "big ben is the nickname for the great bell of the striking clock"
    };
    const vector<string> requests = {"london", "the"};
    const vector<vector<Entry>> expected = { { {0,1} },
                                             { {0, 1}, {1,3} }
                                           };
    test_inverted_index_functionality(docs, requests, expected);
}

TEST(test_case_inverted_index, test_basic2) {
    const vector<string> docs = {
            "milk milk milk milk water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "Americano Capuccino"
    };
    const vector<string> requests = {"milk", "water", "capuccino"};
    const vector<vector<Entry>> expected = { { {0,4}, {1,1}, {2, 5} },
                                             { {0, 2}, {1,2}, {2, 5} },
                                             { {3, 1} }
                                            };
    test_inverted_index_functionality(docs, requests, expected);
}

TEST(test_case_inverted_index, test_inverted_index_missing_word) {
    const vector<string> docs = {
            "a b c d e f g h i j k l",
            "statement"
    };
    const vector<string> requests = {"m", "statement"};
    const vector<vector<Entry>> expected = { { },
                                             { {1, 1} }
                                            };
    test_inverted_index_functionality(docs, requests, expected);
}