//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include <vector>
#include <string>
#include <cstddef>
#include <cmath>
#include <limits>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <iomanip>

namespace estimated_running_time
{
    struct sampling
    {
        double N; //dimension
        double T; //time
    };

    struct sampling_log
    {
        double log_N; //log dimension
        double log_T; //log time
    };

    struct sampling_ratio
    {
        double ratio;
        double log_ratio;
    };

    //a*N^b (power law)
    struct arguments
    {
        double a;
        double b;
    };

    static inline double compute_order_of_growth(const std::vector<sampling>& samples)
    {
        return samples[1].N / samples[0].N;
    }
    
    static inline std::vector<sampling_log> compute_log(const std::vector<sampling>& samples, double order_of_growth)
    {
        std::vector<sampling_log> samples_log;
        for (sampling s : samples)
        {
            double log_N = std::log(s.N) / std::log(order_of_growth);
            double log_T = std::log(s.T) / std::log(order_of_growth);
            samples_log.push_back(sampling_log{ log_N, log_T });
        }
        return samples_log;
    }

    static inline std::vector<sampling_ratio> compute_ratio(const std::vector<sampling>& samples, double order_of_growth)
    {
        std::vector<sampling_ratio> samples_ratio;
        for (size_t i = samples.size() - 1; i > 0; --i)
        {
            double ratio = samples[i].T / samples[i - 1].T;
            double log_ratio = std::log(ratio) / std::log(order_of_growth);
            samples_ratio.push_back(sampling_ratio{ ratio, log_ratio });
        }
        samples_ratio.push_back(sampling_ratio{ -std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity() });
        std::reverse(samples_ratio.begin(), samples_ratio.end());
        return samples_ratio;
    }

    static inline arguments compute_estimated_running_time(const std::vector<sampling>& samples, double N, double b)
    {
        double t = samples[samples.size() - 1].T;
        double a = t / std::pow(N, b);
        return arguments{ a, b };
    }
}

int estimated_running_time_main(int argc, char *argv[])
{
    using namespace estimated_running_time;

    std::string name;
    int dim;
    double time;
    int ns_per_ops;
    double ops_per_second;
    char ignore;

    std::cout << "Enter benchmark data (EOF to compute):\n";
    //Sample data
    /*
            bench_count * |    2048 |     0.069 |      33 |      - | 29786058.1
            bench_count * |    4096 |     0.136 |      33 |      - | 30116097.0
            bench_count * |    8192 |     0.286 |      34 |      - | 28685180.8
            bench_count * |   16384 |     0.569 |      34 |      - | 28776321.4
            bench_count * |   32768 |     1.402 |      42 |      - | 23377644.4
            bench_count * |   65536 |     2.619 |      39 |      - | 25028050.4
            bench_count * |  131072 |     5.093 |      38 |      - | 25736443.4
            bench_count * |  262144 |     9.449 |      36 |      - | 27742201.9
            bench_count * |  524288 |    20.105 |      38 |      - | 26076922.5
            bench_count * | 1048576 |    39.487 |      37 |      - | 26554886.8
    */
    std::vector<sampling> samples;
    while (std::cin >> name >> ignore >> ignore >> dim >> ignore >> time 
                    >> ignore >> ns_per_ops >> ignore >> ignore >> ignore >> ops_per_second)
    {
        samples.push_back(sampling{ static_cast<double>(dim), time });
    }

    if (samples.size() < 6)
    {
        std::cout << "Less than 6 samples to estimate the running time\n";
        return -1;
    }

    double order_of_growth = compute_order_of_growth(samples);
    std::vector<sampling_log> samples_log = compute_log(samples, order_of_growth);
    std::vector<sampling_ratio> samples_ratio = compute_ratio(samples, order_of_growth);

    std::cout << std::string(76, '=') << "\n";
    std::cout << std::setw(10) << "N" << " |" << std::setw(16) << "T" << " |" << std::setw(10) << "log N" << " |"
        << std::setw(10) << "log T" << " |" << std::setw(10) << "ratio" << " |" << std::setw(10) << "log ratio" << "\n";
    std::cout << std::string(76, '=') << "\n";
    for (size_t i = 0; i < samples.size(); ++i)
    {
        std::cout << std::fixed << std::setprecision(4) << std::setw(10) << static_cast<std::size_t>(samples[i].N) << " |" << std::setw(16)
            << samples[i].T << " |" << std::setw(10) << static_cast<std::size_t>(samples_log[i].log_N) << " |" << std::setw(10)
            << samples_log[i].log_T << " |" << std::setw(10) << samples_ratio[i].ratio << " |" << std::setw(10) << samples_ratio[i].log_ratio << "\n";
    }
    std::cout << std::string(76, '=') << "\n";

    double b = samples_ratio[samples_log.size() - 1].log_ratio;
    double N = samples[samples.size() - 1].N;
    arguments ert = compute_estimated_running_time(samples, N, b);

    std::cout << "Estimated runnning time is " << std::scientific << ert.a << " x N^" <<
        std::fixed << std::setprecision(4) << ert.b << " ms\n";
    std::cout << std::string(76, '=') << "\n";

    std::cout << "\nInfer the past estimated running time and the next two:\n";
    double N_0 = N / order_of_growth;
    double N_1 = N * order_of_growth;
    double N_2 = N_1 * order_of_growth;
    std::cout << std::fixed << std::setprecision(4) << std::setw(10) << static_cast<std::size_t>(N_0) << std::setw(16) << (ert.a * std::pow(N_0, ert.b)) << "\n";
    std::cout << std::fixed << std::setprecision(4) << std::setw(10) << static_cast<std::size_t>(N_1) << std::setw(16) << (ert.a * std::pow(N_1, ert.b)) << "\n";
    std::cout << std::fixed << std::setprecision(4) << std::setw(10) << static_cast<std::size_t>(N_2) << std::setw(16) << (ert.a * std::pow(N_2, ert.b)) << "\n";

    return 0;
}