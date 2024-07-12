//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "raii.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <cerrno>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>

namespace raii
{
    namespace internal
    {
        #define Callable typename
        #define CallableArgs typename

        template <Callable C, CallableArgs... Args>
        decltype(auto) invoke_catching_runtime_error(C&& c, Args&&... args)
        {
            try
            {
                return std::forward<C>(c)(std::forward<Args>(args)...);
            }
            catch (std::runtime_error& err)
            {
                std::cout << err.what() << "\n";
            }
            std::terminate();
        }
    }

    static void run_leaked_and_wrong()
    {
        const char* filename0 = "_strings0.temp.txt";
        for (int i = 1; i <= 100000; ++i)
        {
            std::vector<std::string> ss = generate_random_strings(1, 5, 10);
            std::size_t written = 0;
            int error_number = leaked_and_wrong_write_strings_to_file(filename0, ss, written);
            if (error_number)
            {
                switch (error_number)
                {
                case EMFILE: //errno 24
                    std::cout << "Too many open files. No more file descriptors are available, so no more files can be opened.\n";
                    return;
                default:
                    std::cout << "Failed with error number = " << error_number << '\n';
                    return;
                }
            }
            std::cout << std::setw(6) << i << ": " << written << " string(s) written\n";
        }
    }

    static void run_solution()
    {
        std::vector<std::string> ss = generate_random_strings(50, 5, 10);
        const char* filename1 = "_strings1.temp.txt";
        const char* filename2 = "_strings2.temp.txt";
        const char* filename3 = "_strings3.temp.txt";

        std::size_t written = 0;
        write_strings_to_file(filename1, ss, written);
        //invoke_catching_runtime_error(write_strings_to_file, filename1, ss, written);
        std::cout << written << " strings written\n";
        
        written = 0;
        write_strings_to_file_raii_stack(filename2, ss, written);
        //invoke_catching_runtime_error(write_strings_to_file_raii_stack, filename2, ss, written);
        std::cout << written << " strings written\n";

        written = 0;
        write_strings_to_file_raii_heap(filename3, ss, written);
        //invoke_catching_runtime_error(write_strings_to_file_raii_heap, filename3, ss, written);
        std::cout << written << " strings written\n";
    }
}

int raii_main(int argc, char *argv[], bool run_tests)
{
    using raii::run_solution;
    using raii::run_leaked_and_wrong;
    
    if (run_tests)
    {
        //run_leaked_and_wrong();
        run_solution();
    }

    return 0;
}