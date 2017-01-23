#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <istream>

std::vector<std::string> parseCSV(std::string &line, const char delimiter) {
    std::stringstream ss;
    bool hasQuotes = false;
    std::vector<std::string> result;
    for(int i = 0 ; i < line.length(); ++i){
        if (!hasQuotes && line[i] == '"'){
            hasQuotes = true;
        }
        else if (hasQuotes && line[i] == '"'){
            if (line[i+1] == '"'){
                ss << line[i+1];
                ++i;
            }
            else{
                hasQuotes = false;
            }
        }
        else if (!hasQuotes && line[i] == delimiter){
            result.push_back(ss.str());
            ss.str("");
        }
        else if(!hasQuotes && (line[i] == '\r' || line[i] == '\n')) {
            if (line[i] == '\n');
            result.push_back(ss.str());
            return result;
        }
        else {
            ss << line[i];
        }
    }
    result.push_back(ss.str());
}

void test4(){
    std::string line = "\"1111\"\",\"\"2222\"";
    std::vector<std::string> result = parseCSV(line, ',');
    for(auto it : result)
        std::cout << it << "\t";
    std::cout << std::endl;
}

void test1(){
    std::string line = "1999,Chevy,\"Venture \"\"Extended Edition, Very Large\"\"\",\"\",5000.00";
    std::vector<std::string> result = parseCSV(line, ',');
    for(auto it : result)
        std::cout << it << "\t";
    std::cout << std::endl;
}
void test2(){
    std::string line = "1999,Chevy,\"Venture \"\"Extended Edition\"\"\",\"\",4900.00";
    std::vector<std::string> result = parseCSV(line, ',');
    for(auto it : result)
        std::cout << it << "\t";
    std::cout << std::endl;
}
void test3(){
    std::string line = "1997,Ford,E350,\"ac, abs, moon\",3000.00";
    std::vector<std::string> result = parseCSV(line, ',');
    for(auto it : result)
        std::cout << it << "\t";
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    test1();
    test2();
    test3();
    test4();
    return 0;
}
