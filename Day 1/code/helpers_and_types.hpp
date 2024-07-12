//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef HELPERS_AND_TYPES_HPP
#define HELPERS_AND_TYPES_HPP

#include <string>
#include <cstring>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>
#include <array>
#include <set>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "random_int_util.hpp"
#include "random_real_util.hpp"

enum class Gender { male, female };

struct person
{
    person(Gender gender, const std::string& first_name, const std::string& last_name, unsigned char age) :
        gender(gender), first_name(first_name), last_name(last_name), age(age), id(get_unique_id()) {}
    person() = delete;
    person(const person& that) : 
        gender(that.gender), 
        first_name(that.first_name), 
        last_name(that.last_name), 
        age(that.age), 
        id(that.id){}
    person& operator=(const person& that)
    {
        if (&that != this)
        {
            first_name = that.first_name; 
            last_name = that.last_name; 
            gender = that.gender;
            age = that.age;
            id = that.id;
        }
        return *this;
    }
    virtual ~person() = default;

    friend bool operator==(const person& lhs, const person& rhs)
    { 
        return lhs.id == rhs.id && lhs.gender == rhs.gender && lhs.first_name == rhs.first_name && lhs.last_name == rhs.last_name && lhs.age == rhs.age;
    }
    
    friend bool operator!=(const person& lhs, const person& rhs)
    { 
        return !(lhs == rhs); 
    }

    friend bool operator<(const person& lhs, const person& rhs)
    {
        if (lhs.first_name < rhs.first_name) 
            return true;
        if (lhs.first_name > rhs.first_name)
            return false;
        if (lhs.last_name < rhs.last_name) 
            return true;
        if (lhs.last_name > rhs.last_name)
            return false;
        if (lhs.age < rhs.age)
            return true;
        if (lhs.age > rhs.age)
            return false;
        if (lhs.gender < rhs.gender)
            return true;
        if (lhs.gender > rhs.gender)
            return false;		
        return lhs.id < rhs.id;
    }

    friend bool operator>(const person& lhs, const person& rhs)
    {
        return rhs < lhs;
    }

    friend bool operator<=(const person& lhs, const person& rhs)
    {
        return !(rhs < lhs);
    }

    friend bool operator>=(const person& lhs, const person& rhs)
    {
        return !(lhs < rhs);
    }

    Gender gender;
    std::string first_name;
    std::string last_name;
    unsigned char age;

private:
    static std::size_t get_unique_id() { static std::size_t id = 0; return ++id; }
    std::size_t id;
};

inline static std::string to_string(const person& p)
{
    std::string result = p.first_name;
    result += " ";
    result += p.last_name;
    result += ", ";
    result += std::to_string(static_cast<unsigned int>(p.age));
    result += p.gender == Gender::female ? " (she/her)" : " (he/him)";
    return result;
}

using coord_2d_real32 = std::tuple<float, float>;
using coord_2d_real64 = std::tuple<double, double>;
using coord_2d_int32 = std::tuple<std::int32_t, std::int32_t>;

template <typename T>
inline static std::string to_string(const std::tuple<T, T>& x)
{
    std::string result = "(";
    result += std::to_string(std::get<0>(x));
    result += ", ";
    result += std::to_string(std::get<1>(x));
    result += ")";
    return result;
}

template<typename T>
struct buffer_union final
{
    buffer_union() = default;
    buffer_union(const buffer_union<T>&) = default;
    buffer_union<T>& operator=(const buffer_union<T>&) = default;
    ~buffer_union() = default;

    buffer_union(const char* s)
    {
        clear();
        copy(s);
    }

    buffer_union<T>& operator=(const char* s)
    {
        clear();
        copy(s);
        return *this;
    }

    buffer_union(T value) : value(value) {}

    constexpr std::size_t size() const { return sizeof(T); }

    unsigned char* ptr() { return &bytes[0]; }

    const unsigned char* ptr() const { return &bytes[0]; }

    void clear() { std::memset(ptr(), 0, size()); }

    unsigned char* begin() { return ptr();	}

    unsigned char* end() { return ptr() + size(); }

    const unsigned char* cbegin() const { return ptr(); }

    const unsigned char* cend() const { return ptr() + size(); }
    
    union
    {
        unsigned char bytes[sizeof(T)];
        T value;
    };

private:
    void copy(const char* s)
    {
        std::size_t len = size(), slen = std::strlen(s);
        if (slen < len) len = slen;
        for (std::size_t i = 0; i < len; ++i)
            bytes[i] = static_cast<unsigned char>(s[i]);
    }
};

template<typename T>
static inline bool operator==(const buffer_union<T>& lhs, const buffer_union<T>& rhs)
{
    for (std::size_t i = 0, l = lhs.size(); i < l; ++i)
        if (lhs.bytes[i] != rhs.bytes[i])
            return false;
    return true;
}

template<typename T>
static inline bool operator!=(const buffer_union<T>& lhs, const buffer_union<T>& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
static inline bool operator<(const buffer_union<T>& lhs, const buffer_union<T>& rhs)
{
    for (std::size_t i = 0; i < lhs.size(); ++i)
    {
        if (lhs.bytes[i] < rhs.bytes[i]) return true;
        if (rhs.bytes[i] < lhs.bytes[i]) return false;
    }
    return false;
}

template<typename T>
static inline bool operator>(const buffer_union<T>& lhs, const buffer_union<T>& rhs)
{
    return rhs < lhs;
}

template<typename T>
static inline bool operator<=(const buffer_union<T>& lhs, const buffer_union<T>& rhs)
{
    return !(rhs < lhs);
}

template<typename T>
static inline bool operator>=(const buffer_union<T>& lhs, const buffer_union<T>& rhs)
{
    return !(lhs < rhs);
}

using buffer_8 = buffer_union<unsigned char[8]>;
using buffer_16 = buffer_union<unsigned char[16]>;
using buffer_32 = buffer_union<unsigned char[32]>;
using buffer_64 = buffer_union<unsigned char[64]>;
using buffer_128 = buffer_union<unsigned char[128]>;
using buffer_256 = buffer_union<unsigned char[256]>;
using buffer_512 = buffer_union<unsigned char[512]>;

template <typename T>
inline static std::string to_string(const buffer_union<T>& buffer)
{
    std::stringstream ss;
    for (unsigned char ch : const_cast<buffer_union<T>&>(buffer))
    {
        ss << std::setw(2) << std::hex << std::uppercase 
            << std::setfill('0') << (0xff & ch);
    }
    return ss.str();
}

static inline std::vector<std::string> load_file(const char* filename)
{
    std::vector<std::string> lines;
    std::string line;
    std::ifstream ifs(filename);
    if (!ifs.is_open())
        throw std::runtime_error("open file failed");
    while (std::getline(ifs, line))
        lines.emplace_back(line);
    ifs.close();
    return lines;
}

static inline std::vector<std::string> load_male_first_names_file()
{
    std::vector<std::string> boys = load_file("boys.txt");
    return boys;
}

static inline std::vector<std::string> load_female_first_names_file()
{
    std::vector<std::string> girls = load_file("girls.txt");
    return girls;
}

static inline std::vector<std::string> load_surnames_file()
{
    std::vector<std::string> surnames = load_file("surnames.txt");
    return surnames;
}

static inline std::vector<std::array<short, 6>> load_megasena_file()
{
    std::vector<std::string> games = load_file("megasena.txt");
    std::vector<std::array<short, 6>> megasena(games.size());
    for (std::size_t i = 0; i < games.size(); ++i)
    {
        std::istringstream temp(games[i]);
        for (std::size_t j = 0; j < 6; ++j)
            temp >> megasena[i][j];
    }
    return megasena;
}

struct dna
{
    std::string dna_sequence;
    int dna_class;
};

static inline std::vector<dna> load_human_dna_file()
{
    std::vector<std::string> dataset = load_file("dna_sequence_dataset_kaggle_human.txt");
    const std::size_t N = dataset.size() - 1;
    std::vector<dna> dna_data(N);
    for (std::size_t i = 0; i < N; ++i)
    {
        std::istringstream temp(dataset[i + 1]);
        temp >> dna_data[i].dna_sequence >> dna_data[i].dna_class;
    }
    return dna_data;
}

static inline unsigned int now_since_epoch()
{
    return static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
}

static inline std::vector<person> generate_random_people
(	
    std::size_t n,
    std::vector<std::string>& male_first_names,
    std::vector<std::string>& female_first_names,
    std::vector<std::string>& surnames
)
{
    std::vector<person> people;
    int M = static_cast<int>(male_first_names.size()) - 1;
    int F = static_cast<int>(female_first_names.size()) - 1;
    int S = static_cast<int>(surnames.size()) - 1;
    while (n--)
    {
        Gender gender = rand_int(0, 1) ? Gender::female : Gender::male;
        std::string first_name = gender == Gender::female ?
            female_first_names[rand_int(0, F)] : male_first_names[rand_int(0, M)];
        std::string last_name = surnames[rand_int(0, S)];
        unsigned char age = static_cast<unsigned char>(rand_int(18, 90));
        person p(gender, first_name, last_name, age);
        people.emplace_back(p);
    }
    return people;
}

static inline std::vector<person> generate_ordered_random_people
(
    std::size_t n,
    std::vector<std::string>& male_first_names,
    std::vector<std::string>& female_first_names,
    std::vector<std::string>& surnames
)
{
    std::vector<person> people = generate_random_people(n, male_first_names, female_first_names, surnames);
    std::sort(people.begin(), people.end());
    return people;
}

static inline std::string generate_random_string(std::size_t n)
{
    std::string s(n, '\0');
    int A = static_cast<int>('A'), Z = static_cast<int>('Z');	
    for (std::size_t i = 0; i < n; ++i)
        s[i] = rand_int(A, Z);
    return s;
}

static inline std::vector<std::string> generate_random_strings(std::size_t n, std::size_t min_length, std::size_t max_length)
{
    if (max_length < min_length) std::swap(min_length, max_length);

    std::vector<std::string> strings;
    bool uniform_length = min_length == max_length;
    while (n--)
    {
        std::string temp = generate_random_string
        (
            uniform_length ? min_length : rand_int(min_length, max_length)
        );
        strings.emplace_back(temp);
    }		
    return strings;
}

static inline std::vector<std::string> generate_random_strings(std::size_t n, std::size_t length)
{
    return generate_random_strings(n, length, length);
}

static inline std::vector<std::string> generate_ordered_random_strings(std::size_t n, std::size_t min_length, std::size_t max_length)
{
    std::vector<std::string> strings = generate_random_strings(n, min_length, max_length);
    std::sort(strings.begin(), strings.end());
    return strings;
}

static inline std::vector<std::string> generate_ordered_random_strings(std::size_t n, std::size_t length)
{
    return generate_ordered_random_strings(n, length, length);
}

static inline std::vector<std::string> generate_ordered_distinct_random_strings(std::size_t n, std::size_t min_length, std::size_t max_length)
{
    std::vector<std::string> strings = generate_random_strings(n, min_length, max_length);
    std::set<std::string> temp(strings.begin(), strings.end());
    std::size_t N = temp.size();
    if (N < n) strings.resize(N);
    std::copy(temp.begin(), temp.end(), strings.begin());
    return strings;
}

static inline std::vector<std::string> generate_ordered_distinct_random_strings(std::size_t n, std::size_t length)
{
    return generate_ordered_distinct_random_strings(n, length, length);
}

template<typename T>
static inline void generate_random_buffer(buffer_union<T>& buffer)
{
    for (unsigned char& _byte : buffer)
        _byte = rand_int(0, 255);
}

template<typename Buffer>
static inline Buffer generate_random_buffer()
{
    Buffer temp;
    generate_random_buffer(temp); 
    return temp;
}

static inline buffer_8 generate_random_buffer_8() { return generate_random_buffer<buffer_8>(); }
static inline buffer_16 generate_random_buffer_16() { return generate_random_buffer<buffer_16>(); }
static inline buffer_32 generate_random_buffer_32() { return generate_random_buffer<buffer_32>(); }
static inline buffer_64 generate_random_buffer_64() { return generate_random_buffer<buffer_64>(); }
static inline buffer_128 generate_random_buffer_128() { return generate_random_buffer<buffer_128>(); }
static inline buffer_256 generate_random_buffer_256() { return generate_random_buffer<buffer_256>(); }
static inline buffer_512 generate_random_buffer_512() { return generate_random_buffer<buffer_512>(); }

template<typename T, typename F>
static inline std::vector<std::tuple<T, T>> generate_random_coords_2d(std::size_t n, F rand_func)
{
    std::vector<std::tuple<T, T>> coordinates;
    while (n--)
    {
        std::tuple<T, T> temp = std::make_tuple(rand_func(), rand_func());
        coordinates.emplace_back(temp);
    }
    return coordinates;
}

template<typename Tuple>
using _TElem0 = typename std::tuple_element<0, Tuple>::type;

static inline std::vector<coord_2d_real32> generate_random_coords_2d_real32(std::size_t n, _TElem0<coord_2d_real32> max_value = 10.0f)
{
    using _T0 = _TElem0<coord_2d_real32>;
    return generate_random_coords_2d<_T0>(n, [max_value]() { return rand_real(0.0f, max_value); });
}

static inline std::vector<coord_2d_real64> generate_random_coords_2d_real64(std::size_t n, _TElem0<coord_2d_real64> max_value = 10.0)
{
    using _T0 = _TElem0<coord_2d_real64>;
    return generate_random_coords_2d<_T0>(n, [max_value]() { return rand_real(0.0, max_value); });
}

static inline std::vector<coord_2d_int32> generate_random_coords_2d_int32(std::size_t n, _TElem0<coord_2d_int32> max_value = 10)
{
    using _T0 = _TElem0<coord_2d_int32>;
    return generate_random_coords_2d<_T0>(n, [max_value]() { return rand_int(0, max_value); });
}

static inline std::vector<int> generate_random_ints(std::size_t n, int min_value, int max_value)
{
    if (max_value < min_value) std::swap(min_value, max_value);

    std::vector<int> ints;
    while (n--)
    {
        ints.push_back(rand_int(min_value, max_value));
    }
    return ints;
}

static inline std::vector<int> generate_ordered_random_ints(std::size_t n, int min_value, int max_value)
{
    std::vector<int> ints = generate_random_ints(n, min_value, max_value);
    std::sort(ints.begin(), ints.end());
    return ints;
}

static inline std::vector<int> generate_ordered_distinct_random_ints(std::size_t n, int min_value, int max_value)
{
    std::vector<int> ints = generate_random_ints(n, min_value, max_value);
    std::set<int> temp(ints.begin(), ints.end());
    std::size_t N = temp.size();
    if (N < n) ints.resize(N);
    std::copy(temp.begin(), temp.end(), ints.begin());
    return ints;
}

static inline char rand_char(char min_value, char max_value)
{
    return rand_int(static_cast<int>(min_value), static_cast<int>(max_value));
}

static inline std::vector<char> generate_random_chars(std::size_t n, char min_value, char max_value)
{
    if (max_value < min_value) std::swap(min_value, max_value);

    std::vector<char> chars;
    while (n--)
    {
        chars.push_back(rand_char(min_value, max_value));
    }
    return chars;
}

static inline std::vector<char> generate_ordered_random_chars(std::size_t n, char min_value, char max_value)
{
    std::vector<char> chars = generate_random_chars(n, min_value, max_value);
    std::sort(chars.begin(), chars.end());
    return chars;
}

static inline std::vector<char> generate_ordered_distinct_random_ints(std::size_t n, char min_value, char max_value)
{
    std::vector<char> chars = generate_random_chars(n, min_value, max_value);
    std::set<char> temp(chars.begin(), chars.end());
    std::size_t N = temp.size();
    if (N < n) chars.resize(N);
    std::copy(temp.begin(), temp.end(), chars.begin());
    return chars;
}

template<typename T>
std::list<T> to_list(const std::vector<T>& xs) 
{
    std::list<T> temp;
    for (const T& x : xs)
        temp.push_back(x);
    return temp;
}

template<std::size_t N>
std::string to_string(const std::array<char, N>& xs)
{
    return std::string(xs.begin(), xs.end());
}

std::string to_string(const std::vector<char>& xs)
{
    return std::string(xs.begin(), xs.end());
}

template<typename Iter>
void shuffle(Iter first, Iter last)
{
    std::shuffle(first, last, internals::random_engine());
}

#endif /* HELPERS_AND_TYPES_HPP */