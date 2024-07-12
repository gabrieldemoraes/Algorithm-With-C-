//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef RAII_HPP
#define RAII_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <memory>
#include <algorithm>

#include <cerrno>
#include <cstdio>
using std::fopen;
using std::fputs;
using std::fclose;
using std::fflush;
using std::FILE;

namespace raii
{
    static std::FILE* deprecated_fopen(const char* filename, const char* mode)
    {
    #ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable: 4996) //_CRT_SECURE_NO_WARNINGS
    #endif
        return fopen(filename, mode);
    #ifdef _MSC_VER
    #pragma warning(pop)
    #endif
    }

    class open_file_error final : public std::runtime_error
    {
    public:
        using base_t = std::runtime_error;
        open_file_error() : base_t("Error opening the file"){}
        explicit open_file_error(const std::string& what_arg) : base_t(what_arg.c_str()){}
        explicit open_file_error(const char* what_arg) : base_t(what_arg) {}
    };

    class write_file_error final : public std::runtime_error
    {
    public:
        using base_t = std::runtime_error;
        write_file_error() : base_t("Error writing to the file") {}
        explicit write_file_error(const std::string& what_arg) : base_t(what_arg.c_str()) {}
        explicit write_file_error(const char* what_arg) : base_t(what_arg) {}
    };

    class close_file_error final : public std::runtime_error
    {
    public:
        using base_t = std::runtime_error;
        close_file_error() : base_t("Error closing the file") {}
        explicit close_file_error(const std::string& what_arg) : base_t(what_arg.c_str()) {}
        explicit close_file_error(const char* what_arg) : base_t(what_arg) {}
    };

    //Leaked and wrong
    static int leaked_and_wrong_write_strings_to_file(const char* filename, std::vector<std::string> ss, std::size_t& written)
    {
        FILE* file_ptr = deprecated_fopen(filename, "a+");
        if (!file_ptr)
            return errno; //Houston, we've had a problem
        for (auto& s : ss)
        {
            s += '\n';
            fputs(s.c_str(), file_ptr);
            ++written;
        }
        fflush(file_ptr);
        return 0;
    }

    //Not using RAII idiom
    static void write_strings_to_file(const char* filename, std::vector<std::string> ss, std::size_t& written)
    {
        FILE* file_ptr = nullptr;
        try
        {
            file_ptr = deprecated_fopen(filename, "w+");
            if (file_ptr)
            {
                for (auto& s : ss)
                {
                    s += '\n';
                    if (fputs(s.c_str(), file_ptr) == EOF)
                        throw write_file_error();
                    ++written;
                }
            }
            else
            {
                throw open_file_error();
            }
        }
        catch (...)
        {
            if (file_ptr)
                fclose(file_ptr);
            throw;
        }

        if (file_ptr && fclose(file_ptr) == EOF)
            throw close_file_error();
    }

    class file
    {	
    public:
        file(const char* filename, const char* fopen_mode) :
            file_ptr(deprecated_fopen(filename, fopen_mode))
        {
            if (file_ptr == nullptr)
                throw open_file_error();
        }

        ~file()
        {
            if (file_ptr) //due to close
                fclose(file_ptr);
        }

        void write(const std::string& s)
        {
            if (fputs(s.c_str(), file_ptr) == EOF)
                throw write_file_error();
        }

        void write_all_lines(std::vector<std::string> ss, std::size_t& written)
        {
            for (auto& s : ss)
            {
                s += '\n';
                write(s);
                ++written;
            }
        }

        void close()
        {
            FILE* temp = nullptr;
            std::swap(temp, file_ptr);
            if (fclose(temp) == EOF)
                throw close_file_error();
        }

        file(const file&) = delete;
        file& operator=(const file&) = delete;

    private:
        FILE* file_ptr;
    };

    //Using RAII idiom
    static void write_strings_to_file_raii_stack(const char* filename, std::vector<std::string> ss, size_t& written)
    {
        //stack
        file f(filename, "w+");
        f.write_all_lines(ss, written);
    }

    //Using RAII idiom
    static void write_strings_to_file_raii_heap(const char* filename, std::vector<std::string> ss, size_t& written)
    {
        //heap
        auto fclose_deleter = [](FILE* file_ptr) { std::fclose(file_ptr); };
        std::unique_ptr<FILE, decltype(fclose_deleter)> file_ptr(deprecated_fopen(filename, "w+"), fclose_deleter);
        if (file_ptr)
        {
            for (auto& s : ss)
            {
                s += '\n';
                if (fputs(s.c_str(), file_ptr.get()) == EOF)
                    throw write_file_error();
                ++written;
            }
        }
        else
        {
            throw open_file_error();
        }
    }
}

#endif /* RAII_HPP */