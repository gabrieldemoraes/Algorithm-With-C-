//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

#include <cstddef>
#include <cstdint>
#include <cassert>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <functional>

namespace sudoku_solver
{
    namespace internal
    {
        class iter_1 final : public std::iterator<std::forward_iterator_tag, std::int8_t>
        {
            const std::vector<std::int8_t>& xs;
            std::size_t pos, step;
        public:
            iter_1(const std::vector<std::int8_t>& xs, std::size_t pos, std::size_t step)
                : xs(xs), pos(pos), step(step) {}

            iter_1& operator=(const iter_1& that)
            {
                if (this != &that)
                {
                    const_cast<std::vector<std::int8_t>&>(xs) = that.xs;
                    pos = that.pos;
                    step = that.step;
                }
                return *this;
            }

            iter_1& operator++()
            {
                pos += step;
                return *this;
            }

            bool operator!=(const iter_1& that) const
            {
                return &that.xs != &xs || that.step != step || that.pos != pos;
            }

            bool operator==(const iter_1& that) const
            {
                return !(operator!=(that));
            }

            std::int8_t& operator*() const
            {
                return const_cast<std::int8_t&>(xs[pos]);
            }

            friend bool operator<(const iter_1& lhs, const iter_1& rhs)
            {
                return *lhs < *rhs;
            }
        };

        class iter_2 final : public std::iterator<std::forward_iterator_tag, std::int8_t>
        {
            const std::vector<std::int8_t>& xs;
            std::size_t pos, count, next;
        public:
            iter_2(const std::vector<std::int8_t>& xs, std::size_t pos, std::size_t count, std::size_t next)
                : xs(xs), pos(pos), count(count), next(next) {}

            iter_2& operator++()
            {
                pos += (pos + 1) % count ? 1 : next;
                return *this;
            }

            bool operator!=(const iter_2& that) const
            {
                return &that.xs != &xs || that.count != count || that.pos != pos || that.next != next;
            }

            bool operator==(const iter_2& that) const
            {
                return !(operator!=(that));
            }

            std::int8_t& operator*() const
            {
                return const_cast<std::int8_t&>(xs[pos]);
            }

            friend bool operator<(const iter_2& lhs, const iter_2& rhs)
            {
                return *lhs < *rhs;
            }
        };
    }

    class grid;

    class row_iterator final
    {
        const grid& g;
        std::size_t row;
    public:
        row_iterator(const grid& g, std::size_t row);
        internal::iter_1 begin();
        internal::iter_1 end();
    };

    class column_iterator final
    {
        const grid& g;
        std::size_t column;
    public:
        column_iterator(const grid& g, std::size_t column);
        internal::iter_1 begin();
        internal::iter_1 end();
    };

    class region_iterator final
    {
        const grid& g;
        std::size_t region;
    public:
        region_iterator(const grid& g, std::size_t region);
        internal::iter_2 begin();
        internal::iter_2 end();
    };

    //N x N x M x M
    class grid
    {
        std::size_t N, M;
        std::vector<std::int8_t> data_;
        friend class row_iterator;
        friend class column_iterator;
        friend class region_iterator;
    public:
        grid(std::size_t N, std::size_t M, bool fill_to_test = false)
            : N(N), M(M), data_(N * N * M * M, 0)
        {
            if (fill_to_test)
            {
                //test (fill grid)
                std::int8_t k = 0;
                for (std::size_t i = 0; i < N * M; ++i)
                    for (std::size_t j = 0; j < N * M; ++j)
                        data_[i * N * M + j] = k++;
            }
        }

        grid(std::size_t N, std::size_t M, std::vector<std::int8_t> data)
            : N(N), M(M), data_(data)
        {
            assert(data.size() == N * N * M * M);
        }

        row_iterator       row(std::size_t pos) { return    row_iterator(*this, pos); }
        column_iterator column(std::size_t pos) { return column_iterator(*this, pos); }
        region_iterator region(std::size_t pos) { return region_iterator(*this, pos); }		
        region_iterator region(std::size_t row, std::size_t column) { return region_iterator(*this, get_region(row, column)); }

        std::size_t get_N() const { return N; }
        std::size_t get_M() const { return M; }

        std::int8_t get_value(std::size_t row, std::size_t column) const
        {
            std::size_t index = row * N * M + column;
            return data_[index];
        }

        void set_value(std::size_t row, std::size_t column, std::int8_t value)
        {
            std::size_t index = row * N * M + column;
            data_[index] = value;
        }

        std::size_t get_region(std::size_t row, std::size_t column) const
        {
            return M * (row / N) + (column / N);
        }

        void clear()
        {
            std::fill(data_.begin(), data_.end(), 0);
        }

        bool complete() const
        {
            return std::find(data_.begin(), data_.end(), 0) == data_.end();
        }

        std::string to_string()
        {
            std::stringstream ss;
            ss << std::string(M * (3 * N + 2) + 1, '-') << "\n";
            for (std::size_t i = 0; i < N * M; ++i)
            {
                std::size_t j = 0;
                for (int x : row(i))
                {
                    if ((j++) % N == 0)
                        ss << "| ";
                    ss << std::setw(2) << (x ? std::to_string(x) : " ") << " ";
                }
                ss << "| \n";
                if ((i + 1) % M == 0)
                    ss << std::string(M * (3 * N + 2) + 1, '-') << "\n";
            }
            return ss.str();
        }
    };

    row_iterator::row_iterator(const grid& g, std::size_t row) : g(g), row(row) {}
    internal::iter_1 row_iterator::begin()
    {
        const std::size_t M = g.M, N = g.N;
        const std::size_t init = row * N * M;
        const std::size_t step = 1;
        return internal::iter_1(g.data_, init, step);
    }
    internal::iter_1 row_iterator::end()
    {
        const std::size_t M = g.M, N = g.N;
        const std::size_t fini = row * N * M + N * M;
        const std::size_t step = 1;
        return internal::iter_1(g.data_, fini, step);
    }

    column_iterator::column_iterator(const grid& g, std::size_t column) : g(g), column(column) {}
    internal::iter_1 column_iterator::begin()
    {
        const std::size_t M = g.M, N = g.N;
        const std::size_t init = column;
        const std::size_t step = N * M;
        return internal::iter_1(g.data_, init, step);
    }
    internal::iter_1 column_iterator::end()
    {
        const std::size_t M = g.M, N = g.N;
        const std::size_t fini = N * N * M * M + column;
        const std::size_t step = N * M;
        return internal::iter_1(g.data_, fini, N * M);
    }

    region_iterator::region_iterator(const grid& g, std::size_t region) : g(g), region(region) {}
    internal::iter_2 region_iterator::begin()
    {
        const std::size_t M = g.M, N = g.N;
        const std::size_t init = (region / M) * M * N * N + (region % M) * N;
        const std::size_t next = (M - 1) * N + 1;
        return internal::iter_2(g.data_, init, N, next);
    }
    internal::iter_2 region_iterator::end()
    {
        const std::size_t M = g.M, N = g.N;
        const std::size_t fini = (region / M) * M * N * N + (region % M) * N + M * N * N;
        const std::size_t next = (M - 1) * N + 1;
        return internal::iter_2(g.data_, fini, N, next);
    }

    namespace internal
    {
        static std::vector<std::int8_t> get_options(std::size_t N)
        {
            std::vector<std::int8_t> options(N * N, 0);
            std::iota(options.begin(), options.end(), 1);
            return options;
        }
        
        static std::vector<std::int8_t> get_choices(grid& g, std::size_t row, std::size_t column)
        {
            const std::size_t M = g.get_M(), N = g.get_N();
            
            auto row_iter = g.row(row);
            auto column_iter = g.column(column);
            auto region_iter = g.region(row, column);

            std::set<std::int8_t> row_set(row_iter.begin(), row_iter.end());
            std::set<std::int8_t> column_set(column_iter.begin(), column_iter.end());
            std::set<std::int8_t> region_set(region_iter.begin(), region_iter.end());

            std::vector<std::int8_t> already_in_use;
            std::set_union(row_set.begin(), row_set.end(), column_set.begin(), column_set.end(), std::back_inserter(already_in_use));
            std::set_difference(region_set.begin(), region_set.end(), already_in_use.begin(), already_in_use.end(), std::back_inserter(already_in_use));
            std::sort(already_in_use.begin(), already_in_use.end());

            std::vector<std::int8_t> options = get_options(N);
            std::vector<std::int8_t> choices;
            std::set_difference(options.begin(), options.end(), already_in_use.begin(), already_in_use.end(), std::back_inserter(choices));

            return choices;
        }
        
        static bool solve(grid& g, std::size_t row, std::size_t column, std::function<void(grid&, std::size_t, std::size_t)> visit = nullptr)
        {
            const std::size_t M = g.get_M(), N = g.get_N();
            bool solved = false;
            if (!g.get_value(row, column))
            {
                std::vector<std::int8_t> choices = get_choices(g, row, column);
                for (std::int8_t value : choices)
                {
                    g.set_value(row, column, value);
                    if (visit)
                        visit(g, row, column);
                    if (column + 1 < M * N)
                    {
                        solved = solve(g, row, column + 1, visit);
                        if (solved)
                            break;
                    }
                    else if (row + 1 < M * N)
                    {
                        solved = solve(g, row + 1, 0, visit);
                        if (solved)
                            break;
                    }
                    else
                    {
                        solved = true;
                        break;
                    }
                    g.set_value(row, column, 0);
                }
            }
            else
            {
                if (column + 1 < M * N)
                {
                    solved = solve(g, row, column + 1, visit);
                }
                else if (row + 1 < M * N)
                {
                    solved = solve(g, row + 1, 0, visit);
                }
                else
                {
                    solved = true;
                }
            }
            return solved;
        }
    }

    static bool solve(grid& g, std::function<void(grid&, std::size_t, std::size_t)> visit = nullptr)
    {
        return internal::solve(g, 0, 0, visit);
    }
}

#endif /* SUDOKU_SOLVER_HPP */