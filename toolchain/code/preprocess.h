#pragma once

#include <vector>
#include <string>
#include <stack>
#include <map>
#include <set>

#include "spliter.h"

int lines = 0;

class InputsType
{
public:
    std::vector<std::string> inputs;
    std::vector<int> codelines;

    InputsType()
    {
        inputs.resize(0);
        codelines.resize(0);
    }
    InputsType(int n)
    {
        inputs.resize(n);
        codelines.resize(n);
    }

    void push_back(const std::string& s)
    {
        inputs.push_back(s);
        codelines.push_back(lines);
    }

    void print()
    {
        int i = 0;
        for (auto& j : inputs)
            std::cout << codelines[i++] << " " << j << "\n";
    }
};

#define PREHEAD lines = -1;                                                  \
    InputsType result(0);                                                    \
    bool data_area = false;                                                  \
    int j = 0;                                                               \
    for (const std::string& i : inputs.inputs)                               \
    {                                                                        \
        lines = inputs.codelines[j++];                                       \
        if (i.length() == 0)                                                 \
        {                                                                    \
            result.push_back(i);                                             \
            continue;                                                        \
        }                                                                    \
                                                                             \
        std::string real = split(i, ';')[0];                                 \
        if (real.length() == 0)                                              \
        {                                                                    \
            result.push_back(i);                                             \
            continue;                                                        \
        }                                                                    \
                                                                             \
        std::vector<std::string> spl = split(real, ' ');                     \
                                                                             \
        const std::string& cmd = spl.at(0);                                  \
                                                                             \
        if (cmd.length() == 0)                                               \
            continue;                                                        \
        if (cmd == ".data")                                                  \
            { result.push_back(cmd); data_area = true; continue; }           \
        else if (cmd == "./data")                                            \
            { result.push_back(cmd); data_area = false; continue; }          \
        if (data_area)                                                       \
            { result.push_back(real); continue; }                            \

InputsType pre_string(const InputsType& inputs)
{
    InputsType result(0);
    int j = 0;
    for (const std::string& i : inputs.inputs)
    {
        lines = inputs.codelines[j++];
        if (i.length() == 0)
        {
            result.push_back(i);
            continue;
        }
        std::string real = split(i, ';')[0];
        if (real.length() == 0)
        {
            result.push_back(i);
            continue;
        }

        if (real[0] == '"')
        {
            for (int j = 1;; ++j)
            {
                if (real[j] == '"')
                    break;
                std::string pb = "'";
                if (real[j] == ' ')
                    pb += "\\s";
                else
                {
                    pb += real[j];
                    if (real[j] == '\\')
                        pb += real[++j];
                }
                pb += "'";
                result.push_back(pb);
            }
            result.push_back("'\\0'");
        }
        else
        {
            result.push_back(i);
        }
    }
    return result;
}

InputsType pre_define(const InputsType& inputs)
{
    std::map<std::string, std::string> defines = {
        {"'A'", "10"},
        {"'B'", "11"},
        {"'C'", "12"},
        {"'D'", "13"},
        {"'E'", "14"},
        {"'F'", "15"},
        {"'G'", "16"},
        {"'H'", "17"},
        {"'I'", "18"},
        {"'J'", "19"},
        {"'K'", "20"},
        {"'L'", "21"},
        {"'M'", "22"},
        {"'N'", "23"},
        {"'O'", "24"},
        {"'P'", "25"},
        {"'Q'", "26"},
        {"'R'", "27"},
        {"'S'", "28"},
        {"'T'", "29"},
        {"'U'", "30"},
        {"'V'", "31"},
        {"'W'", "32"},
        {"'X'", "33"},
        {"'Y'", "34"},
        {"'Z'", "35"},

        {"'a'", "10"},
        {"'b'", "11"},
        {"'c'", "12"},
        {"'d'", "13"},
        {"'e'", "14"},
        {"'f'", "15"},
        {"'g'", "16"},
        {"'h'", "17"},
        {"'i'", "18"},
        {"'j'", "19"},
        {"'k'", "20"},
        {"'l'", "21"},
        {"'m'", "22"},
        {"'n'", "23"},
        {"'o'", "24"},
        {"'p'", "25"},
        {"'q'", "26"},
        {"'r'", "27"},
        {"'s'", "28"},
        {"'t'", "29"},
        {"'u'", "30"},
        {"'v'", "31"},
        {"'w'", "32"},
        {"'x'", "33"},
        {"'y'", "34"},
        {"'z'", "35"},

        {"' '", "36"},
        {"'\\s'", "36"},
        {"'_'", "37"},
        {"'+'", "38"},
        {"'-'", "39"},
        {"'*'", "40"},
        {"'/'", "41"},
        {"'='", "42"},
        {"'('", "43"},
        {"')'", "44"},
        {"'^'", "45"},


        {"'\\ll'", "56"},
        {"'\\rr'", "57"},
        {"'\\uu'", "58"},
        {"'\\dd'", "59"},

        {"'\\b'", "61"},
        {"'\\n'", "62"},
        {"'\\0'", "63"},
    };

    std::stack<std::pair<std::string, std::string>> ss;
    for (auto& i : defines)
    {
        ss.push({ i.first, i.second });
    }
    while (!ss.empty())
    {
        defines.insert({ "#" + ss.top().first, "#" + ss.top().second});
        ss.pop();
    }

    InputsType result(0);
    int j = 0;
    for (const std::string& i : inputs.inputs)                                     
    {                                      
        lines = inputs.codelines[j++];
        if (i.length() == 0)                                                
        {                                                                   
            result.push_back(i);                                            
            continue;                                                       
        }    
        std::string real = split(i, ';')[0];                                
        if (real.length() == 0)                                             
        {                                                                   
            result.push_back(i);                                            
            continue;                                                       
        }      
        std::vector<std::string> spl = split(real, ' ');        
        const std::string& cmd = spl.at(0);                 
        if (cmd.length() == 0)                                          
            continue;              
        if (cmd == "define")
        {
            defines[spl.at(1)] = spl.at(2);
            defines["[" + spl.at(1) + "]"] = "[" + spl.at(2) + "]";
        }
        else
        {
            std::string s;
            int spl_size = spl.size();
            for (int j = 0; j < spl_size; ++j)
            {
                if (defines.count(spl[j]))
                    spl[j] = defines[spl[j]];
                s += spl[j] + " ";
            }

            result.push_back(s);
        }
    }
    
    return result;
}

InputsType pre_whileif(const InputsType& inputs)
{
    std::stack<std::string> stck;
    std::stack<std::string> wsstck;
    std::stack<std::string> westck;
    std::stack<std::pair<std::string, int>> istck;

    int w_ = 0;
    int f_ = 0;
    int i_ = 0;
    int e_ = 0;

    PREHEAD
        auto if_jmp = [&]()
        {
            if (spl.at(2) == "==")
            {
                result.push_back("xor tmp1 tmp1");
                result.push_back("mov tmp2 " + spl.at(1));
                result.push_back("sub tmp2 " + spl.at(3));
                result.push_back("sub tmp1 tmp2");
            }
            else if (spl.at(2) == "!=")
            {
                result.push_back("mov tmp1 #-1");
                result.push_back("mov tmp2 " + spl.at(1));
                result.push_back("sub tmp2 " + spl.at(3));
                result.push_back("add tmp1 tmp2");
            }
            else if (spl.at(2) == "<")
            {
                result.push_back("mov tmp1 " + spl.at(3));
                result.push_back("mov tmp2 " + spl.at(1));
                result.push_back("inc tmp2");
                result.push_back("sub tmp1 tmp2");
            }
            else if (spl.at(2) == ">")
            {
                result.push_back("mov tmp1 " + spl.at(1));
                result.push_back("mov tmp2 " + spl.at(3));
                result.push_back("inc tmp2");
                result.push_back("sub tmp1 tmp2");
            }
            else if (spl.at(2) == "<=")
            {
                result.push_back("mov tmp1 " + spl.at(3));
                result.push_back("sub tmp1 " + spl.at(1));
            }
            else if (spl.at(2) == ">=")
            {
                result.push_back("mov tmp1 " + spl.at(1));
                result.push_back("sub tmp1 " + spl.at(3));
            }
        };
        auto if_not_jmp = [&]()
        {
            if (spl.at(2) == "==") // a != b skip
            {
                result.push_back("mov tmp1 #-1");
                result.push_back("mov tmp2 " + spl.at(1));
                result.push_back("sub tmp2 " + spl.at(3));
                result.push_back("add tmp1 tmp2");
            }
            else if (spl.at(2) == "!=") // a == b skip
            {
                result.push_back("xor tmp1 tmp1");
                result.push_back("mov tmp2 " + spl.at(1));
                result.push_back("sub tmp2 " + spl.at(3));
                result.push_back("sub tmp1 tmp2");
            }
            else if (spl.at(2) == "<") // a >= b skip
            {
                result.push_back("mov tmp1 " + spl.at(1));
                result.push_back("sub tmp1 " + spl.at(3));
            }
            else if (spl.at(2) == ">") // a <= b, b >= a skip
            {
                result.push_back("mov tmp1 " + spl.at(3));
                result.push_back("sub tmp1 " + spl.at(1));
            }
            else if (spl.at(2) == "<=") // a > b, a >= b + 1 skip
            {
                result.push_back("mov tmp1 " + spl.at(1));
                result.push_back("mov tmp2 " + spl.at(3));
                result.push_back("inc tmp2");
                result.push_back("sub tmp1 tmp2");
            }
            else if (spl.at(2) == ">=") // a < b, b > a skip
            {
                result.push_back("mov tmp1 " + spl.at(3));
                result.push_back("mov tmp2 " + spl.at(1));
                result.push_back("inc tmp2");
                result.push_back("sub tmp1 tmp2");
            }
        };
        

        if (cmd == "break")
        {
            result.push_back("mov pc " + westck.top() + "_e");
        }
        else if (cmd == "continue")
        {
            result.push_back("mov pc " + wsstck.top());
        }
        else if (cmd == "while")
        {
            std::string code = "::while" + std::to_string(w_++);
            wsstck.push(code + "_s");
            westck.push(code);
            stck.push(code);
            result.push_back(code + "_s");
        }
        else if (cmd == "for")
        {
            std::string code = "::for" + std::to_string(f_++);
            wsstck.push(code + "_m");
            westck.push(code);
            stck.push(code);
            result.push_back(code + "_s");
        }
        else if (cmd == "step")
        {
            result.push_back(westck.top() + "_m");
        }
        else if (cmd == "if")
        {
            std::string code = "::if" + std::to_string(i_++);
            stck.push(code);

            istck.push({ code, 0 });

            if_not_jmp();
            result.push_back("jif " + code + "_" + std::to_string(istck.top().second));
        }
        else if (cmd == "elif")
        {
            std::string t = stck.top();
            std::string code = istck.top().first;
            result.push_back("mov pc " + code);
            result.push_back(code + "_" + std::to_string(istck.top().second));

            istck.top().second += 1;


            if_not_jmp();
            result.push_back("jif " + code + "_" + std::to_string(istck.top().second));
        }
        else if (cmd == "else")
        {
            std::string t = stck.top();
            std::string code = istck.top().first;
            result.push_back("mov pc " + code);
            result.push_back(code + "_" + std::to_string(istck.top().second));

            istck.top().second += 1;
        }
        else if (cmd == "ifbreak")
        {
            if_jmp();
            result.push_back("jif " + westck.top() + "_e");
        }
        else if (cmd == "ifcontinue")
        {
            if_jmp();
            result.push_back("jif " + wsstck.top());
        }
        else if (cmd == "ifjmp")
        {
            if_jmp();
            result.push_back("jif " + spl.at(4));
        }
        else if (cmd == "}")
        {
            std::string t = stck.top();
            if (t[2] == 'w' || t[2] == 'f')
            {
                wsstck.pop();
                westck.pop();
                result.push_back("mov pc " + t + "_s");
                result.push_back(t + "_e");
                stck.pop();
            }
            else
            {
                stck.pop();
                result.push_back(istck.top().first + "_" + std::to_string(istck.top().second));

                result.push_back(istck.top().first);

                istck.pop();
            }
        }
        else
        {
            result.push_back(i);
        }
    }

    return result;
}

InputsType pre_callreturn(const InputsType& inputs)
{
    int cnt = 0;

    PREHEAD
        if (cmd == "call")
        {
            result.push_back("mov tmp1 ::call" + std::to_string(cnt));
            result.push_back("push tmp1");
            result.push_back("mov pc " + spl.at(1));
            result.push_back("::call" + std::to_string(cnt));
            cnt += 1;
        }
        else if (cmd == "ret")
        {
            result.push_back("pop pc");
        }
        else
        {
            result.push_back(i);
        }
    }

    return result;
}

InputsType pre_pushpop(const InputsType& inputs)
{
    PREHEAD
        if (cmd == "push")
        {
            result.push_back("add sp #-1");
            if (spl.at(1).at(0) == '#')
            {
                result.push_back("mov tmp1 " + spl.at(1));
                result.push_back("mov [sp] tmp1");
            }
            else
                result.push_back("mov [sp] " + spl.at(1));
        }
        else if (cmd == "pop")
        {
            result.push_back("mov " + spl.at(1) + " [sp]");
            result.push_back("inc sp");
        }
        else
        {
            result.push_back(i);
        }
    }

    return result;
}

InputsType pre_offset(const InputsType& inputs)
{
    PREHEAD
        if (cmd == "mov")
        {
            std::string gh;
            if (spl.at(1).at(0) == '[')
            {
                gh = removegh(spl.at(1));
            }
            else if (spl.at(2).at(0) == '[')
            {
                gh = removegh(spl.at(2));
            }
            else
            {
                result.push_back(i);
                continue;
            }

            std::string oper = "add";
            std::vector<std::string> spl2 = split(gh, '+');
            if (spl2.size() <= 1)
            {
                oper = "sub";
                spl2 = split(gh, '-');
                if (spl2.size() <= 1)
                {
                    result.push_back(i);
                    continue;
                }
            }

            result.push_back("mov tmp1 " + spl2[0]);
            result.push_back(oper + " tmp1 " + spl2[1]);
            if (spl.at(1).at(0) == '[')
            {
                result.push_back("mov [tmp1] " + spl.at(2));
            }
            else if (spl.at(2).at(0) == '[')
            {
                result.push_back("mov " + spl.at(1) + " [tmp1]");
            }
            continue;
        }
        result.push_back(i);
    }

    return result;
}

InputsType pre_alu(const InputsType& inputs)
{
	std::set<std::string> double_alu_list = {
		"add",
		"sub",
		"or",
		"and",
		"xor",
	};

    PREHEAD
        if (double_alu_list.count(cmd))
        {
            if (spl.at(2).at(0) == '#' || spl.at(2).at(0) == ':')
            {
                result.push_back("mov tmp3 " + spl.at(2));
                result.push_back(cmd + " " + spl.at(1) + " tmp3");
            }
            else
            {
                result.push_back(i);
            }
        }
        else
        {
            result.push_back(i);
        }
    }

	return result;
}

#undef PREHEAD