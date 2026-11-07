#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>
#include <cstdint>
#include <map>

#include "preprocess.h"
#include "compile.h"
#include "mcfunction.h"
#include "clipboard.h"
#include "nameException.h"


#define MAX_ADDRESS 16 * 16 * 2

#define PRINT_LOG


int main()
{
    std::ifstream in("input.txt");
    std::string line;

    if (!in.is_open())
    {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return 0;
    }

    InputsType inputs;
    std::vector<std::string> original;

    int linenumber = 1;

    // inputs.push_back("mov sp #" + std::to_string(MAX_ADDRESS));
    // inputs.codelines[inputs.codelines.size() - 1] = linenumber++;

    bool first = true;
    int init_sp = 0;
    int auto_stack_size = 50;
    for (; std::getline(in, line); ++linenumber) {
        if (first)
        {
            first = false;
            if (line[0] == '@')
            {
                if (line[1] == '+')
                {
                    auto_stack_size = std::stoi(line.c_str() + 2);
                }
                else
                {
                    init_sp = std::stoi(line.c_str() + 1);
                }
                continue;
            }
        }
        trim(line);
        inputs.push_back(line);
        inputs.codelines[inputs.codelines.size() - 1] = linenumber;
        original.push_back(line);
    }
    inputs.push_back("exit");
    inputs.codelines[inputs.codelines.size() - 1] = linenumber++;
    in.close();
    std::cout << "--original--\n";
#ifdef PRINT_LOG
    inputs.print();
    std::cout << "--\n";
#endif

    try
    {
        inputs = pre_string(inputs);
        std::cout << "--pre_string--\n";
#ifdef PRINT_LOG
        inputs.print();
        std::cout << "--\n";
#endif

        inputs = pre_define(inputs);
        std::cout << "--pre_define--\n";
#ifdef PRINT_LOG
        inputs.print();
        std::cout << "--\n";
#endif

        inputs = pre_whileif(inputs);
        std::cout << "--pre_whileif--\n";
#ifdef PRINT_LOG
        inputs.print();
        std::cout << "--\n";
#endif

        inputs = pre_callreturn(inputs);
        std::cout << "--pre_callreturn--\n";
#ifdef PRINT_LOG
        inputs.print();
        std::cout << "--\n";
#endif

        inputs = pre_pushpop(inputs);
        std::cout << "--pre_pushpop--\n";
#ifdef PRINT_LOG
        inputs.print();
        std::cout << "--\n";
#endif

        inputs = pre_jmp(inputs);
        std::cout << "--pre_jmp--\n";
#ifdef PRINT_LOG
        inputs.print();
        std::cout << "--\n";
#endif

        inputs = pre_offset(inputs);
        std::cout << "--pre_offset--\n";
#ifdef PRINT_LOG
        inputs.print();
        std::cout << "--\n";
#endif

        inputs = pre_mov(inputs);
        std::cout << "--pre_mov--\n";
#ifdef PRINT_LOG
        inputs.print();
        std::cout << "--\n";
#endif

        inputs = pre_alu(inputs);
        std::cout << "--pre_alu--\n";
#ifdef PRINT_LOG
        inputs.print();
        std::cout << "--\n";
#endif

        std::string init_sp_msg = "";
        std::string cmp = compile(inputs);
        int binary_lines = std::count(cmp.begin(), cmp.end(), '\n') + 2; // original + init sp
        if (init_sp == 0)
        {
            init_sp = binary_lines + auto_stack_size;
            init_sp_msg += "auto set ";
        }
        if (init_sp > MAX_ADDRESS)
            init_sp = MAX_ADDRESS;
        init_sp_msg += "init sp = " + std::to_string(init_sp) + "\n";
        if (init_sp <= binary_lines + 10)
        {
            if (init_sp > binary_lines)
                init_sp_msg += "*WARNING*: low stack space detected(" + std::to_string(init_sp - binary_lines) + " words left)\n";
            else
                init_sp_msg += "*WARNING*: stack overflow detected(heap end: " + std::to_string(binary_lines) + ", stack start: " + std::to_string(init_sp) + ")\n";
        }
        cmp = "0000011000000100\n" + decToBin16Signed(std::to_string(init_sp)) + "\n" + cmp; // mov sp #init_sp
        std::cout << "--end--\n";
#ifdef PRINT_LOG
        std::cout << cmp;
        std::cout << "--\n";
#endif

        std::string func = mcfunctions(cmp);
        func += "\n";
        func += "tellraw @a {\"text\":\"program loaded\"}";
        std::cout << init_sp_msg;
        if (CopyToClipboard(func))
            std::cout << "Copied!";
        else
            std::cout << "Failed to Copy.";

        return 0;
    }
    catch (const NameException& e)
    {
        std::cout << "\n\n" << e.what() << "\n";
    }
    catch (...)
    {
        std::cout << "\n\n" << "SOMETHING ERROR..." << "\n";
    }

    int s = lines - 2;
    if (s < 1) s = 1;
    int e = lines + 2;
    if (e > original.size()) e = original.size();
    for (int i = s; i <= e; ++i)
    {
        std::cout << i << " ";
        std::cout << original[i - 1];
        if (i == lines)
            std::cout << "    <- HERE";
        std::cout << "\n";
    }
    return 0;
}