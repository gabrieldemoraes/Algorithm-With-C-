//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef MIN_AND_MAX_HPP
#define MIN_AND_MAX_HPP

#include <vector>
#include <utility>
#include <cstddef>

namespace min_and_max
{
    static int min(const std::vector<int>& xs)
    {
        //precondition: xs.size() >= 1

        //average case: N - 1 comparisons	
        int result = xs[0];
        for (std::size_t i = 1; i < xs.size(); ++i)
        {
            if (xs[i] < result)
            {
                result = xs[i];
            }
        }
        return result;
    }

    static int max(const std::vector<int>& xs)
    {
        //precondition: xs.size() >= 1
        
        //average case: N - 1 comparisons
        int result = xs[0];
        for (std::size_t i = 1; i < xs.size(); ++i)
        {
            if (xs[i] > result)
            {
                result = xs[i];
            }
        }
        return result;
    }
    
    static std::pair<int, int> min_max_it(const std::vector<int>& xs)
    {
        //precondition: xs.size() >= 1

        //worst case: ~3N/2 comparisons

        using FwdIter = std::vector<int>::const_iterator;
        FwdIter first = xs.begin();
        FwdIter last = xs.end();
        std::pair<FwdIter, FwdIter> result{ first, first };
        if (first != last)
        {
            if (++first != last)
            {
                if (*first < *result.first)
                {
                    result.first = first;
                }
                else
                {
                    result.second = first;
                }

                while (++first != last)
                {
                    FwdIter prev = first;
                    if (++first == last)
                    {
                        if (*prev < *result.first)
                        {
                            result.first = prev;
                        }
                        else if (*prev > *result.second)
                        {
                            result.second = prev;
                        }
                        break;
                    }
                    else
                    {
                        FwdIter curr = first;
                        if (*curr < *prev)
                        {
                            if (*curr < *result.first)
                            {
                                result.first = curr;
                            }
                            if (*prev > *result.second)
                            {
                                result.second = prev;
                            }
                        }
                        else
                        {
                            if (*prev < *result.first)
                            {
                                result.first = prev;
                            }
                            if (*curr > *result.second)
                            {
                                result.second = curr;
                            }
                        }
                    }
                }
            }
        }
        return std::make_pair(*result.first, *result.second);
    }

    static std::pair<int, int> min_max_idx(const std::vector<int>& xs)
    {
        //precondition: xs.size() >= 1

        //worst case: ~3N/2 comparisons

        std::pair<int, int> result{ xs[0], xs[0] };
        if (xs.size() > 1) //1
        {
            if (xs[1] < result.first) //1
            {
                result.first = xs[1];
            }
            else
            {
                result.second = xs[1];
            }

            //1 + 2 + 3N/2 - 6 == 3N/2 - 3 == ~3N/2 (**)
            for (std::size_t i = 2; i < xs.size(); ++i) //(N - 2)/2 == N/2 - 1
            {
                int prev = xs[i];
                if (++i == xs.size()) //1 (*)
                {
                    //2 (*)
                    if (prev < result.first)
                    {
                        result.first = prev;
                    }
                    else if (prev > result.second)
                    {
                        result.second = prev;
                    }
                }
                else //(N/2 - 1) - 1 == (N/2 - 2)
                {
                    //3(N/2 - 2) == 3N/2 - 6 (*) 
                    int curr = xs[i];
                    if (curr < prev) //(N/2 - 2)
                    {
                        if (curr < result.first) //(N/2 - 2)
                        {
                            result.first = curr;
                        }
                        if (prev > result.second) //(N/2 - 2)
                        {
                            result.second = prev;
                        }
                    }
                    else
                    {
                        if (prev < result.first)
                        {
                            result.first = prev;
                        }
                        if (curr > result.second)
                        {
                            result.second = curr;
                        }
                    }
                }
            }
        }
        return result;
    }

    static std::pair<int, int> min_and_max(const std::vector<int>& xs)
    {
        //precondition: xs.size() >= 1

        //worst case: 2(N - 1) comparisons	
        std::pair<int, int> result{ xs[0], xs[0] };
        for (std::size_t i = 1; i < xs.size(); ++i)
        {
            if (xs[i] < result.first)
            {
                result.first = xs[i];
            }
            else if (xs[i] > result.second)
            {
                result.second = xs[i];
            }
        }
        return result;
    }
}

#endif /* MIN_AND_MAX_HPP */