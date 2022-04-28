#include <iostream>
#include <fstream>
#include "converter.h"
#include "inverted_index.h"

int main() {
//    auto a = ConverterJSON().get_text_documents();
//    for (const auto& word : a) std::cout << word << '\n';
//    cout << ConverterJSON().get_responses_limit();
//    vector<vector<pair<int, float>>> ans;
//    vector<pair<int, float>> v {{1, 0.2}, {2, 0.3}};
//    ans.push_back(vector<pair<int, float>>());
//    ans.push_back(vector<pair<int, float>>({{3, 0.9}}));
//    ans.push_back(v);
//    ConverterJSON().put_answers(ans);

    InvertedIndex index;
    index.update_document_base({"milk sugar salt", "milk a milk b, milk c, milk d"});
    auto count = index.get_word_count("a");
    for (const auto& entry : count) {
        cout << entry.doc_id << ' ' << entry.count << '\n';
    }

//    auto b = ConverterJSON().get_requests();
//    for (const auto& word : b) std::cout << word << '\n';
//    int a = 15360;
//    cout << (char)((a << 8) >> 16);
//    cout << ((const char*) &a ) [1];
//    char c = ((a >> 16) << 8);
//    cout << (int)c;
    return 0;

}
