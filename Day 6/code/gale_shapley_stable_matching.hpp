//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef GALE_SHAPLEY_STABLE_MATCHING_HPP
#define GALE_SHAPLEY_STABLE_MATCHING_HPP

#include <cassert>
#include <cstddef>
#include <vector>
#include <queue>
#include <algorithm>

#ifdef DBG
#include <iostream> //DBG
#endif

namespace gale_shapley_stable_matching
{
    const std::size_t NOT_SELECTED = -1;

    struct element
    {
        element() = delete;
        element(std::vector<std::size_t> preference_list) 
            : preference_list(std::move(preference_list)) {}
        std::vector<std::size_t> preference_list;
        std::size_t selected = NOT_SELECTED;
        bool is_free() const { return selected == NOT_SELECTED; }
    };

    namespace internal
    {
        static inline bool is_valid(const std::vector<element>& xs)
        {
            const std::size_t N = xs.size();
            return std::all_of(xs.cbegin(), xs.end(),
                [N](const element& x) { return x.preference_list.size() == N; });
        }
    }

    static inline void find_stable_matching(std::vector<element>& ms, std::vector<element>& ws)
    {
        assert(ms.size() == ws.size());
        assert(internal::is_valid(ms));
        assert(internal::is_valid(ws));

        const std::size_t N = ms.size();
        std::vector<std::size_t> next_preferred(N, 0);
        std::queue<std::size_t> chooser;
        for (std::size_t i = 0; i < N; ++i) chooser.push(i);
        while (!chooser.empty())
        {
            std::size_t i = chooser.front();
            chooser.pop();			
            while (true)
            {
                std::size_t j = ms[i].preference_list[next_preferred[i]++];
                #ifdef DBG
                std::cout << i << " " << j << "\n"; //DBG
                #endif
                if (ws[j].is_free())
                {
                    ws[j].selected = i;
                    ms[i].selected = j;
                    break; //has match
                }
                else //if (!ws[j].is_free())
                {
                    auto& w = ws[j];
                    std::size_t m  = i; //new candidate match
                    std::size_t new_ = w.preference_list[m];
                    std::size_t m_ = w.selected; //current match
                    std::size_t cur_ = w.preference_list[m_];
                    if (new_ > cur_)
                    {
                        w.selected = m;
                        ms[m].selected = j;
                        ms[m_].selected = NOT_SELECTED;
                        chooser.push(m_);
                        break; //has match
                    }
                }
            }
        }
    }
}

#endif /* GALE_SHAPLEY_STABLE_MATCHING_HPP */