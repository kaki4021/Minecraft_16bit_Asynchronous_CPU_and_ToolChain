#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>
#include <cstdint>
#include <map>

#include "spliter.h"

class NameException : public std::exception
{
private:
    std::string message;
public:
    NameException(const std::string message) : message(message) {};

    const char* what() const noexcept override {
        return message.c_str();
    }
};

std::map<std::string, std::string> register_code = {
    {"tmp1","0000" },
    {"tmp2","0001" },
    {"bp",  "0010" },
    {"sp",  "0011" },
    {"pc",  "0100" },
    {"tmp3","0101" },
    {"in",  "0110" },
    {"mar", "0111" },
    {"r1",  "1000" },
    {"r2",  "1001" },
    {"r3",  "1010" },
    {"r4",  "1011" },
    {"r5",  "1100" },
    {"r6",  "1101" },
    {"r7",  "1110" },
    {"out",  "1111" },
};
std::string register_code_find(const std::string& key)
{
    if (register_code.count(key))
        return register_code[key];
    // std::cout << key << ": register name error";
    // exit(0);
    throw NameException(key + ": register name error");
    return nullptr;
}

std::map<std::string, std::string> cmd_code = {
    {"add", "00101"},
    {"sub", "00110"},
    {"inc", "00111"},
    {"not", "01000"},
    {"or",  "01001"},
    {"and", "01010"},
    {"xor", "01011"},
    {"shl", "01100"},
    {"shr", "01101"},

    {"jif", "01111"},

    {"rng", "10000"},

    {"iwait", "11100"},
    {"dreset", "11101"},
    {"dindex", "11110"},
    {"dwrite", "11111"},
};
std::string cmd_code_find(const std::string& key)
{
    if (cmd_code.count(key))
        return cmd_code[key];
    // std::cout << key << ": command type error";
    // exit(0);
    throw NameException(key + ": command type error");
    return nullptr;
}

std::map<std::string, bool> cmd_double = {
    {"add", true},
    {"sub", true},
    {"inc", false},
    {"not", false},
    {"or",  true},
    {"and", true},
    {"xor", true},
    {"shl", false},
    {"shr", false},
};

std::string decToBin16Signed(const std::string& decStr) {
    long long num = std::stoll(decStr);
    uint16_t bits16 = static_cast<uint16_t>(num);
    return std::bitset<16>(bits16).to_string();
}

int cmd_size(const std::vector<std::string>& spl)
{
    const std::string& cmd = spl[0];

    if (cmd == "mov")
    {
        if (spl[2][0] == '#' || spl[2][0] == ':')
            return 2;
        return 1;
    }

    if (cmd == "jif")
        return 2;
    return 1;
}

std::map<std::string, int> simbol;
std::string movparser(const std::vector<std::string>& spl);
std::string compile(const InputsType& inputs)
{
    simbol.clear();
    std::map<std::string, int> data_simbol;

    bool data_area = false;
    int p = 0;
    int d = 0;
    for (const std::string& i : inputs.inputs)
    {
        if (i.length() == 0)
            continue;

        std::string real = split(i, ';')[0];
        if (real.length() == 0)
            continue;

        if (real == ".data")
        {
            data_area = true;
            continue;
        }
        else if (real == "./data")
        {
            data_area = false;
            continue;
        }

        if (real[0] == ':')
        {
            if (data_area)
                data_simbol.insert({ real, d });
            else
                simbol.insert({ real, p });
        }
        else
        {
            if (data_area)
            {
                d += 1;
            }
            else
            {
                std::vector<std::string> spl = split(real, ' ');
                p += cmd_size(spl);
            }
        }
    }
    for (auto& i : data_simbol)
    {
        simbol.insert({ i.first, i.second + p });
    }

    for (auto& i : simbol)
    {
        std::cout << i.first << " " << i.second << "\n";
    }

    std::string result = "";
    std::string datas = "";

    int j = 0;
    data_area = false;
    for (const std::string& i : inputs.inputs)
    {
        lines = inputs.codelines[j++];
        if (i.length() == 0)
            continue;

        if (i[0] == ':')
            continue;

        std::string real = split(i, ';')[0];
        if (real.length() == 0)
            continue;

        std::vector<std::string> spl = split(real, ' ');

        const std::string& cmd = spl[0];

        if (cmd.length() == 0)
            continue;

        if (real == ".data")
        {
            data_area = true;
            continue;
        }
        else if (real == "./data")
        {
            data_area = false;
            continue;
        }
        if (data_area)
        {
            if (cmd[0] != ':')
                datas += decToBin16Signed(real) + "\n";
            continue;
        }

        std::string parse;
        if (cmd == "exit")
        {
            parse = "0000000000000000\n";
        }
        else if (cmd == "mov")
        {
            parse = movparser(spl);
        }
        else if (cmd == "jif")
        {
            parse = cmd_code_find(cmd);
            parse = "0000" + parse;
            parse = register_code_find("pc") + parse;
            parse = "000" + parse;
            parse += "\n";
            if (!simbol.count(spl[1]))
            {
                // std::cout << spl[1] << ": symbol not found";
                // exit(0);
                throw NameException(spl[1] + ": symbol not found");
            }
            parse += decToBin16Signed(std::to_string(simbol[spl[1]]));
            parse += "\n";
        }
        else if (cmd == "rng")
        {
            parse = cmd_code_find(cmd);
            parse = "0000" + parse;
            parse = register_code_find(spl[1]) + parse;
            parse = "000" + parse;
            parse += "\n";
        }
        else if (cmd == "iwait" || cmd == "dreset" || cmd == "dindex" || cmd == "dwrite")
        {
            parse = "00000000000" + cmd_code_find(cmd) + "\n";
        }
        else
        {
            parse = cmd_code_find(cmd);
            parse = register_code_find(cmd_double[cmd] ? spl[2] : spl[1]) + parse;
            parse = register_code_find(spl[1]) + parse;
            parse = "000" + parse;
            parse += "\n";
        }

        result += parse;
        //std::cout << parse << "\n";
    }

    return result + datas;
}


std::string movparser(const std::vector<std::string>& spl)
{
    std::string result = "";

    if (spl[2][0] == '[')
    {
        result = "00010";
        result = register_code_find(removegh(spl[2])) + result;
        result = register_code_find(spl[1]) + result;
        result = "000" + result;
    }
    else if (spl[1][0] == '[')
    {
        result = "00011";
        result = register_code_find(removegh(spl[1])) + result;
        result = register_code_find(spl[2]) + result;
        result = "000" + result;
    }
    else if (spl[2][0] == '#' || spl[2][0] == ':')
    {
        result = "00100";
        result = "0000" + result;
        result = register_code_find(spl[1]) + result;
        result = "000" + result;
        result += "\n";
        if (spl[2][0] == '#')
        {
            if (spl[2][1] == 'b')
                result += make16bit(removesh(removesh(spl[2])));
            else
                result += decToBin16Signed(removesh(spl[2]));
        }
        else
        {
            if (!simbol.count(spl[2]))
            {
                // std::cout << spl[2] << ": symbol not found";
                // exit(0);
                throw NameException(spl[2] + ": symbol not found");
            }
            result += decToBin16Signed(std::to_string(simbol[spl[2]]));
        }
    }
    else
    {
        result = "00001";
        result = register_code_find(spl[2]) + result;
        result = register_code_find(spl[1]) + result;
        result = "000" + result;
    }

    return result + "\n";
}
