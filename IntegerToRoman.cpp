//
// Created by mark on 16-12-7.
//
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using std::vector;
using std::map;
using std::string;
using std::cout;
using std::endl;

map<int, char> dic = {
        {1, 'I'},
        {5, 'V'},
        {10, 'X'},
        {50, 'L'},
        {100, 'C'},
        {500, 'D'},
        {1000, 'M'}
};

int setNum(int num){
    if(num < 5)
        return 5;
    else if(num < 10)
        return 10;
    else if(num < 50)
        return 50;
    else if(num < 100)
        return 100;
    else if(num < 500)
        return 500;
    else
        return 1000;
}

void setBitWeights(vector<int> &bitweights, string numstr){
    int len = numstr.length();
    for(int i = 0; i < numstr.length(); ++i){
        bitweights.push_back(std::pow(10, len - i - 1));
    }
}

string intToRoman(int num){
    string numstr = std::to_string(num);
    std::string result("");

    vector<int> bitweights;
    setBitWeights(bitweights, numstr);

    for(int i = 0; i < numstr.length(); ++i){
        int num = static_cast<int>(numstr[i] - '0');
        if(num < 4){
            result = result + std::string(num, dic[bitweights[i]]);
        }
        else if(num == 4 || num == 9){
            int key = setNum(num*bitweights[i]);
            string temp("");
            temp += dic[key];
            temp= dic[key - num * bitweights[i]] + temp;
            result += temp;
        }
        else if(num > 5 && num < 9){  // FixMe May be not safe
            result += dic[5*bitweights[i]];
            result += std::string(num - 5, dic[bitweights[i]]);
        }
        else {
            result += dic[num * bitweights[i]];
        }
    }
    return result;
}
int main(int argc, char **argv){
    auto res = intToRoman(6);
    printf("Roman number is: %s\n", res.c_str());
    return 0;
}
