#include <iostream>
#include <fstream>
#include "converter.h"

int main() {
//    auto a = ConverterJSON().get_text_documents();
//    for (const auto& word : a) std::cout << word << '\n';
    cout << ConverterJSON().get_responses_limit();
    ConverterJSON().put_answers(vector<vector<pair<int, float>>>({{{1, 0.2}}}));
//    auto b = ConverterJSON().get_requests();
//    for (const auto& word : b) std::cout << word << '\n';
//    int a = 15360;
//    cout << (char)((a << 8) >> 16);
//    cout << ((const char*) &a ) [1];
//    char c = ((a >> 16) << 8);
//    cout << (int)c;
    return 0;

}
