#include <iostream>
#include <fstream>
#include "converter.h"

int main() {
    auto a = ConverterJSON().get_text_documents();
    for (const auto& word : a) std::cout << word << '\n';
//    cout << ConverterJSON().get_responses_limit();
//    auto b = ConverterJSON().get_requests();
//    for (const auto& word : b) std::cout << word << '\n';
    return 0;

}
