#include "gtest/gtest.h"
#include "converter.h"
#include "inverted_index.h"
#include "search_server.h"
using namespace std;

void test_inverted_index_functionality (const vector<string>& docs,
                                        const vector<string>& requests,
                                        const vector<vector<Entry>>& expected) {
    vector<vector<Entry>> result;
    Inverted_Index idx;
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

TEST(test_case_search_server, test_simple) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "Americano Capuccino"
    };
    const vector<string> request = {"milk water", "sugar"};
    const vector<vector<Relative_Index>> expected = { { {2, 1}, {0, 0.7}, {1, 0.3}},
                                                     { }
                                                   };
    Inverted_Index idx;
    idx.update_document_base(docs);
    Search_Server srv(idx);
    vector<vector<Relative_Index>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}

TEST(test_case_search_server, test_top_5) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "paris is the capital of france",
            "berlin is the capital of germany",
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "lisbon is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus",
            "astana is the capital of kazakhstan",
            "beijing is the capital of china",
            "tokyo is the capital of japan",
            "bangkok is the capital of thailand",
            "welcome to moscow the capital of russia the third rome",
            "amsterdam is the capital of netherlands",
            "helsinki is the capital of finland",
            "oslo is the capital of norway",
            "stockholm is the capital of sweden",
            "riga is the capital of latvia",
            "tallinn is the capital of estonia",
            "warsaw is the capital of poland"
    };
    const vector<string> request = {"moscow is the capital of russia"};
    const vector<vector<Relative_Index>> expected = {{ {7, 1},
                                                       {14, 1},
                                                       {0, 2.f/3},
                                                       {1, 2.f/3},
                                                       {2, 2.f/3}
                                                     }
                                                    };
    Inverted_Index idx;
    idx.update_document_base(docs);
    Search_Server srv(idx);
    vector<vector<Relative_Index>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}