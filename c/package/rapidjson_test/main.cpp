#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

int main() {
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    rapidjson::Document d;
    d.Parse(json);

    rapidjson::Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    d.Accept(writer);
    std::cout << buffer.GetString() << std::endl;
    return 0;
}
