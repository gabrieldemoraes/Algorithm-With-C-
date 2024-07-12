Resolver os problemas:
 1) https://leetcode.com/problems/find-all-duplicates-in-an-array/
	Solução: ..\code\find_duplicates_in_unsorted_array.cpp
 2) https://leetcode.com/problems/copy-list-with-random-pointer/
	Solução: ..\code\copy_list_with_random_pointer.cpp
 3) https://leetcode.com/problems/merge-two-sorted-lists/
	Solução: ..\code\merge_two_sorted_lists.cpp
	Se achar o 3 muito fácil, recomendo:
	3.1) https://leetcode.com/problems/letter-combinations-of-a-phone-number/
	Solução: ..\code\letter_combinations_of_a_phone_number.cpp
 4) https://leetcode.com/problems/kth-largest-element-in-an-array/
	Solução: ..\code\kth-largest-element-in-an-array.cpp
 5) https://leetcode.com/problems/coin-change/
	Solução: ..\code\coin-change.cpp
 6) https://leetcode.com/problems/two-sum/
	Solução: ..\code\two-sum.cpp
	Se achar o 6 muito fácil, recomendo:
	3.1) https://leetcode.com/problems/lru-cache/
	Solução: ..\code\lru-cache.cpp

Tarefas propostas:

  1) Implementar um teste de benchmarking comparando busca força bruta e busca kmp. Qual sua conclusão sobre o resultado?
     Sugestões: 
     1.1) função brute_force_substring:
          std::size_t brute_force_substring(const std::string& text, const std::string& pattern) 
     1.2) função kmp_substring:
          std::size_t kmp_substring(const std::string& text, const std::string& pattern)
     1.3) implementar em apenas 1 arquivo .cpp (benchmark_find_substring.cpp)

  2) Implementar o doubly_linked_list (ou doubly_linked_list_alt) numa API orientada a objetos.
     Sugestões:
     2.1) classe doubly_linked_list encapsula doubly_linked_node e as suas operações (ex.: append, prepend, insert_before, insert_after, remove_before, remove_after, traverse_forward, traverse_backward, ...)
     2.2) adaptar o test-driver (doubly_linked_list.t.cpp) para a nova classe doubly_linked_list 