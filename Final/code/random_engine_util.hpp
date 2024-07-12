//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef RANDOM_ENGINE_UTIL_HPP
#define RANDOM_ENGINE_UTIL_HPP

#include <random>

namespace internals
{
    using random_engine = std::default_random_engine; //default engine
    
    static thread_local random_engine current_engine;

    inline random_engine::result_type rd()
    {
        return std::random_device{}();
    }

    inline random_engine& rand_engine()
    {
        static thread_local random_engine engine{ rd() };
        return engine;
    }

    inline void seed_rand()
    {
        rand_engine().seed(rd());
    }

    inline void seed_rand(random_engine::result_type seed)
    {
        rand_engine().seed(seed);
    }
}

inline void seed_rand() 
{
    internals::seed_rand();
}

inline void seed_rand(internals::random_engine::result_type seed)
{
    internals::seed_rand(seed);
}

#endif /* RANDOM_ENGINE_UTIL_HPP */
