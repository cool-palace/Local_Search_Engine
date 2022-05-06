#include "include/converter.h"

int main() {
    Converter_JSON converter;
    auto docs = converter.get_text_documents();
    auto request = converter.get_requests();
    Inverted_Index idx;
    idx.update_document_base(docs);
    Search_Server srv(idx);
    auto result = srv.search(request);
    converter.put_answers(result);
    return 0;
}
