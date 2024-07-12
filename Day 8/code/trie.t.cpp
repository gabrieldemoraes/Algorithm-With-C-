//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "helpers_and_types.hpp"
#include "trie.hpp"

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

namespace trie
{
    static void display_keys(const std::vector<std::string>& keys)
    {
        int count = 0;
        for (auto& key : keys)
        {
            if (count++ == 8) { std::cout << '\n'; count = 0; }
            std::cout << key << ' ';
        }
        std::cout << '\n';
    }

    static bool valid_key(const std::string& key, bool includeWildcard = false)
    {
        auto pred = [includeWildcard](char c) { return 'A' <= c && c <= 'Z' || (includeWildcard && c == '_'); };
        return std::find_if_not(key.begin(), key.end(), pred) == key.end();
    }

    static void test_interactive()
    {
        std::cout << "   string: insert a string, ?<string>: find a string, -<string>: remove a string, *<string>: strings with prefix\n";
        std::cout << "#<string>: strings with pattern _,  1: load with verbs file,  0: clear trie,              !: display info\n";        

        r_way_trie t;
        std::size_t count = 0;

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '*':
                {
                    std::string prefix = cmd.substr(1);
                    if (valid_key(prefix))
                    {
                        std::vector<std::string> keys = t.keys_with_prefix(prefix);
                        if (keys.size()) display_keys(keys);
                    }
                    else
                    {
                        std::cout << "Invalid char out of [A, Z]\n";
                    }
                }
                break;
            case '-':
                {
                    std::string key = cmd.substr(1);
                    if (valid_key(key))
                    {
                        bool removed = t.remove(key);
                        std::cout << key << (removed ? "" : " not") << " removed\n";
                    }
                    else
                    {
                        std::cout << "Invalid char out of [A, Z]\n";
                    }
                }
                break;
            case '?':
                {
                    std::string key = cmd.substr(1);
                    if (valid_key(key))
                    {
                        std::size_t value = t.find(key);
                        if (value == r_way_trie::npos)
                            std::cout << key << " not found\n";
                        else
                            std::cout << key << " has value #" << value << '\n';
                    }
                    else
                    {
                        std::cout << "Invalid char out of [A, Z]\n";
                    }
                }
                break;
            case '#':
                {
                    std::string pattern = cmd.substr(1);
                    if (valid_key(pattern, true))
                    {
                        std::vector<std::string> keys = t.keys_with_pattern(pattern);
                        if (keys.size()) display_keys(keys);
                    }
                    else
                    {
                        std::cout << "Invalid char out of [A, Z] or _\n";
                    }
                }
                break;
            case '0':
                {
                    t.clear();
                    count = 0;
                    std::cout << "trie cleared\n";
                }
                break;
            case '1':
                {
                    for (auto& verb : load_verbs_file())
                        t.insert(std::move(verb), ++count);
                }
                break;
            case '!':
                {
                    std::cout << "size: " << t.size() << '\n';
                    std::cout << "keys: " << '\n';
                    std::vector<std::string> keys = t.keys();
    	            if (keys.size()) display_keys(keys);
                }
                break;
            default:
                {
                    if (valid_key(cmd))
                    {
                        t.insert(cmd, ++count);
                        std::cout << cmd << " inserted with value #" << count << '\n';
                    }
                    else
                    {
                        std::cout << "Invalid char out of [A, Z]\n";
                    }
                }
                break;
            }
        }
    }
}

int trie_main(int argc, char *argv[], bool run_tests)
{
    using trie::test_interactive;
    
    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}