#pragma once

#include <string>
#include <vector>

void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}
void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}
void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}
std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        trim(item);
        result.push_back(item);
    }
    return result;
}
std::vector<std::string> split_token(const std::string& s)
{
    const std::set<char> spliter = { ' ', '+', '-', '[', ']' };

    std::vector<std::string> result;
    std::string temp;
    for (char i : s)
    {
        if (spliter.count(i))
        {
            if (temp.size() > 0)
                result.push_back(temp);
            temp.clear();
            result.push_back(std::string(1, i));
        }
        else
        {
            temp.push_back(i);
        }
    }
    if (temp.size() > 0)
        result.push_back(temp);

    return result;
}

std::string removesh(const std::string& input)
{
    std::string result;

    int input_len = input.length();
    for (int i = 1; i < input_len; ++i)
    {
        result += input[i];
    }

    return result;
}
std::string removegh(const std::string& input)
{
    std::string result;

    int input_len = input.length();
    for (int i = 1; i < input_len - 1; ++i)
    {
        result += input[i];
    }

    return result;
}

std::string make16bit(const std::string& input)
{
    std::string result;
    int input_size = input.size();
    int loop_size = 16 - input_size;
    for (int i = 0; i < loop_size; ++i)
        result += "0";
    result += input;
    return result;
}