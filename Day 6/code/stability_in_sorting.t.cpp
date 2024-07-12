//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>

namespace stability_in_sorting
{
    struct album
    {
        std::string name;
        std::string band;
        
        album(const std::string& name, const std::string& band) 
            : name(name), band(band){}
        
        album() = delete;
        
        ~album() = default;
        
        album(const album& that) :
            name(that.name), band(that.band){}
        
        album& operator=(const album& that)
        {
            if (&that != this)
            {
                name = that.name; 
                band = that.band;
            }
            return *this;
        }
        
        friend bool operator==(const album& lhs, const album& rhs)
        { 
            return lhs.name == rhs.name && lhs.band == rhs.band;
        }
        
        friend bool operator!=(const album& lhs, const album& rhs)
        { 
            return !(lhs == rhs); 
        }
        
        friend bool operator<(const album& lhs, const album& rhs)
        {
            if (lhs.name < rhs.name) 
                return true;
            return false;
        }

        friend bool operator>(const album& lhs, const album& rhs)
        {
            return rhs < lhs;
        }

        friend bool operator<=(const album& lhs, const album& rhs)
        {
            return !(rhs < lhs);
        }

        friend bool operator>=(const album& lhs, const album& rhs)
        {
            return !(lhs < rhs);
        }
    };

    static inline bool by_band(const album& lhs, const album& rhs)
    {
        if (lhs.band < rhs.band) 
            return true;
        return false;
    }

    static void test_interactive()
    {
        std::vector<album> albums;
        std::string album_name, band_name;
        while (std::cin >> album_name >> band_name)
            albums.push_back(album{album_name, band_name});
        std::random_device rd;
        std::shuffle(albums.begin(), albums.end(), std::mt19937{rd()});
        std::cout << "Albums after shuffling:\n";
        for (album a : albums)
        std::cout << std::setw(35) << a.name << " " 
                    << std::setw(15) << a.band << "\n";
        std::cout << "\nAlbums sorted by name:\n";
        std::sort(albums.begin(), albums.end());
        for (album a : albums)
            std::cout << std::setw(35) << a.name << " " 
                      << std::setw(15) << a.band << "\n";
        std::cout << "\nThen sorted by band:\n";
        std::stable_sort(albums.begin(), albums.end(), by_band);
        for (album a : albums)
            std::cout << std::setw(35) << a.name << " " 
                      << std::setw(15) << a.band << "\n";
    }
}

//Test cases:
//stability_in_sorting.exe < albums.txt
int stability_in_sorting_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using stability_in_sorting::test_interactive;
    
    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}