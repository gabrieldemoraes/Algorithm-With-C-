//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O0 cpp_memory_layout.cpp -o cpp_memory_layout.exe
//cl /Fo.\obj\ /EHsc /Od cpp_memory_layout.cpp /link /out:cpp_memory_layout.exe

#include <vector>
#include <cstdio>
using std::printf;

int int_global = 42;
int int_global_unitialized;

void print(std::vector<int>* v_ptr, const char* local)
{
    printf("[%2lldb] %16lld (0x%012llx): %4lld on %s\n", (long long)sizeof(*v_ptr), (long long)v_ptr, (long long)v_ptr, (long long)v_ptr->size(), local);
}

void print(int* i_ptr, const char* local)
{
    printf("[%2lldb] %16lld (0x%012llx): %4d on %s\n", (long long)sizeof(*i_ptr), (long long)i_ptr, (long long)i_ptr, *i_ptr, local);
}

template<typename Ptr>
void print(Ptr** ptr, const char* local)
{
    printf("[%2lldb] %16lld (0x%012llx)       on %s\n", (long long)sizeof(*ptr), (long long)ptr, (long long)ptr, local);
}

template<typename F>
void print(F f_ptr, const char* f_name, const char* local)
{
    printf("      %16lld (0x%012llx): %8s on %s\n", (long long)f_ptr, (long long)f_ptr, f_name, local);
}

int main(int argc, char *argv[])
{
    static int int_static = 42;
    static int int_static_unitialized;

    int  int_onstack{ 42 };
    int* int_onheap{ new int(42) };
    int* i1{ new int(84) };
    int* i2{ new int(126) };
    int* i3{ new int(168) };
    int  i4{ 84 };
    int  i5{ 126 };
    int  i6{ 168 };
    std::vector<int> int_vec{ 42, 84, 126, 168 };

    print(&argv, "stack");
    print(&argc, "stack");
    
    print(&int_onstack, "stack");
    print(&int_onheap, "stack");
    print(&i1, "stack");
    print(&i2, "stack");
    print(&i3, "stack");
    print(&i4, "stack");
    print(&i5, "stack");
    print(&i6, "stack");
    print(&int_vec, "stack");

    print(int_onheap, "heap");
    print(i1, "heap");
    print(i2, "heap");
    print(i3, "heap");
    print(&int_vec[0], "heap");
    print(&int_vec[1], "heap");
    print(&int_vec[2], "heap");
    print(&int_vec[3], "heap");
    
    print(&int_global_unitialized, "data (uninitialized)");
    print(&int_static_unitialized, "data (uninitialized)");
    
    print(&int_global, "data (initialized)");
    print(&int_static, "data (initialized)");

    print(printf, "printf", "text");
    print(main, "main", "text");
    print(static_cast<void(*)(int*, const char*)>(print), "print", "text");
    
    delete i3;
    delete i2;
    delete i1;
    delete int_onheap;

    /*
    printf("\n[Enter to finish]\n");
    while ((char)std::getchar() != '\n');
    */
    
    return 0;
}