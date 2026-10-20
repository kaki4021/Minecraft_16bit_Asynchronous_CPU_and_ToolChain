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

    int linenumber = 0;
    inputs.push_back("mov sp #" + std::to_string(MAX_ADDRESS));
    inputs.codelines[inputs.codelines.size() - 1] = linenumber++;
    while (std::getline(in, line)) {
        trim(line);
        inputs.push_back(line);
        inputs.codelines[inputs.codelines.size() - 1] = linenumber++;
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

        inputs = pre_offset(inputs);
        std::cout << "--pre_offset--\n";
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

        std::string cmp = compile(inputs);
        std::cout << "--end--\n";
#ifdef PRINT_LOG
        std::cout << cmp;
        std::cout << "--\n";
#endif

        std::string func = mcfunctions(cmp);
        func += "\n";
        func += "tellraw @a {\"text\":\"program loaded\"}";
        if (CopyToClipboard(func))
            std::cout << "클립보드 복사 완료.";
        else
            std::cout << "클립보드 복사 실패.";

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