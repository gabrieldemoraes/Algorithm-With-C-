//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 classification_with_kdtree.cpp -o classification_with_kdtree.exe
//cl /Fo.\obj\ /EHsc /O2 classification_with_kdtree.cpp /link /out:classification_with_kdtree.exe

//Test file
/*
2.37354618925767 5.39810588036707 0
3.18364332422208 4.38797360674923 0
2.16437138758995 5.34111969142442 0
4.59528080213779 3.87063690391921 0
3.32950777181536 6.43302370170104 0
2.17953161588198 6.98039989850586 0
3.48742905242849 4.63277852353349 0
3.73832470512922 3.95586537368347 0
3.57578135165349 5.56971962744241 0
2.69461161284364 4.86494539611918 0
4.51178116845085 7.40161776050478 0
3.38984323641143 4.96075999726683 0
2.3787594194582 5.68973936245078 0
0.7853001128225 5.02800215878067 0
4.12493091814311 4.25672679111759 0
2.95506639098477 5.18879229951434 0
2.98380973690105 3.19504137110896 0
3.9438362106853 6.46555486156289 0
3.82122119509809 5.1532533382119 0
3.59390132121751 7.17261167036215 0
3.91897737160822 5.47550952889966 0
3.78213630073107 4.29005356907819 0
3.07456498336519 5.61072635348905 0
1.01064830413663 4.06590236835575 0
3.61982574789471 3.7463665997609 0
2.943871260471 5.29144623551746 0
2.84420449329467 4.55670812678157 0
1.52924761610073 5.00110535163162 0
2.52184994489138 5.07434132415166 0
3.4179415601997 4.41047905381193 0
4.35867955152904 4.4313312671815 0
2.897212272657 4.86482138487617 0
3.38767161155937 6.1780869965732 0
2.94619495941709 3.47643319957024 0
1.62294044317139 5.59394618762842 0
2.58500543670032 5.33295037121352 0
2.60571004628965 6.06309983727636 0
2.94068660328881 4.6958160763657 0
4.10002537198388 5.37001880991629 0
3.76317574845754 5.26709879077223 0
2.83547640374641 4.45747996900835 0
2.74663831986349 6.20786780598317 0
3.69696337540474 6.16040261569495 0
3.55666319867366 5.700213649515 0
2.31124430545048 6.58683345454085 0
2.29250484303788 5.5584864255653 0
3.36458196213683 3.72340779154196 0
3.76853292451542 4.42673458576311 0
2.88765378784977 3.77538738510164 0
3.88110772645421 4.52659936356069 0
4.37963332277588 7.45018710127266 1
5.04211587314424 6.98144016728536 1
4.08907835144755 6.68193162545616 1
5.15802877240407 6.0706378525463 1
4.34541535608118 5.51253968985852 1
6.76728726937265 5.92480770338432 1
5.71670747601721 8.00002880371391 1
5.91017422949523 6.37873330520318 1
5.38418535782634 5.61557315261551 1
6.68217608051942 8.86929062242358 1
4.36426354605102 7.42510037737245 1
4.53835526963943 6.76135289908697 1
6.43228223854166 8.05848304870902 1
4.34930364668963 7.88642265137494 1
4.79261925639803 6.38075695176885 1
4.60719207055802 9.20610246454047 1
4.68000713145149 6.74497296985898 1
4.72088669702344 5.57550534978719 1
5.49418833126783 6.85560039804578 1
4.82266951773039 7.20753833923234 1
4.49404253788574 9.30797839905936 1
6.34303882517041 7.10580236789371 1
4.78542059145313 7.45699880542341 1
4.82044346995661 6.92284706464347 1
4.89980925878644 6.66599915763346 1
5.71266630705141 6.96527397168872 1
4.92643559587367 7.78763960563016 1
4.96236582853295 9.07524500865228 1
4.31833952124434 8.02739243876377 1
4.67572972775368 8.2079083983867 1
5.06016044043452 5.76867657844196 1
4.41110551374034 7.98389557005338 1
5.53149619263257 7.21992480366065 1
3.48160591821321 5.53274997090776 1
5.30655786078977 7.52102274264814 1
3.46355017646241 6.84124539528398 1
4.69902387316339 8.4645873119698 1
4.47172009555499 6.23391800039534 1
4.347905219319 6.56978824607145 1
4.94310322215261 6.07389050262256 1
3.08564057431999 6.82289603856346 1
6.17658331201856 7.40201177948634 1
3.335027563788 6.26825182688039 1
4.53646959852761 7.83037316798167 1
3.88407989495715 5.79191721369553 1
4.24918099880655 5.95201558719226 1
7.08716654562835 8.44115770684428 1
5.01739561969325 5.98415253469535 1
3.71369946956567 7.41197471231752 1
3.35939446558142 6.61892394889108 1
*/

#include <cmath>
#include <stdexcept>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <numeric>
#include <iostream>

class point2d final
{
    double X, Y;

public:
    point2d(double x, double y) 
    {
        if (std::isinf(x) || std::isinf(y))
            throw std::runtime_error("Coordinates must be finite");
        if (std::isnan(x) || std::isnan(y))
            throw std::runtime_error("Coordinates cannot be NaN");
        X = (x == -0.0) ? 0.0 : x;
        Y = (y == -0.0) ? 0.0 : y;
    }

    double distance_squared_to(point2d that) const
    {
        double dx = X - that.X;
        double dy = Y - that.Y;
        return dx * dx + dy * dy;
    }

    int compare_to(point2d that) const
    {
        if (Y < that.Y) return -1;
        if (Y > that.Y) return +1;
        if (X < that.X) return -1;
        if (X > that.X) return +1;
        return 0;
    }

    std::string to_string() const
    {
        return "[" + std::to_string(X) + ", " + std::to_string(Y) + "]";
    }

    double x() const { return X; }
    double y() const { return Y; }
};

class recthv final
{
    double Xmin, Ymin, Xmax, Ymax;

public:
    recthv(double xmin, double ymin, double xmax, double ymax)
    {
        if (xmax < xmin || ymax < ymin)
            throw std::runtime_error("Invalid rectangle");
        Xmin = xmin;
        Ymin = ymin;
        Xmax = xmax;
        Ymax = ymax;
    }

    bool intersects(recthv that) const
    {
        return Xmax >= that.Xmin && Ymax >= that.Ymin && that.Xmax >= Xmin && that.Ymax >= Ymin;
    }

    double distance_squared_to(point2d p) const
    {
        double dx = 0.0, dy = 0.0;
        if (p.x() < Xmin) dx = p.x() - Xmin;
        else if (p.x() > Xmax) dx = p.x() - Xmax;
        if (p.y() < Ymin) dy = p.y() - Ymin;
        else if (p.y() > Ymax) dy = p.y() - Ymax;
        return dx * dx + dy * dy;
    }

    double distance_to(point2d p) const
    {
        return std::sqrt(distance_squared_to(p));
    }

    bool contains(point2d p) const
    {
        return (Xmin <= p.x()) && (p.x() <= Xmax) && (Ymin <= p.y()) && (p.y() <= Ymax);
    }

    double width() const 
    { 
        return Xmax - Xmin; 
    }
    
    double height() const 
    { 
        return Ymax - Ymin; 
    }

    std::string to_string() const
    {
        return "[" + std::to_string(Xmin) + ", " + std::to_string(Xmax) + "] x [" + std::to_string(Ymin) + ", " + std::to_string(Ymax);
    }

    double x_min() const { return Xmin; }
    double y_min() const { return Ymin; }
    double x_max() const { return Xmax; }
    double y_max() const { return Ymax; }
};

class kdtree final
{
    struct kdnode
    {
        kdnode(point2d p, recthv rect) 
            : p(p), rect(rect) {}		
        point2d p;
        recthv rect;
        std::unique_ptr<kdnode> lb = nullptr;
        std::unique_ptr<kdnode> rt = nullptr;
    };

    std::unique_ptr<kdnode> root;
    size_t N;

    std::unique_ptr<kdnode> insert_recursive(std::unique_ptr<kdnode> x, point2d p, bool is_vertical, double xmin, double ymin, double xmax, double ymax)
    {
        if (x == nullptr)
        {
            std::unique_ptr<kdnode> new_node(new kdnode(p, recthv(xmin, ymin, xmax, ymax)));
            ++N;
            return new_node;
        }

        if (0 == x->p.compare_to(p))
            return x;

        if (is_vertical)
        {
            if (p.x() < x->p.x())
                x->lb = insert_recursive(std::move(x->lb), p, !is_vertical, x->rect.x_min(), x->rect.y_min(), x->p.x(), x->rect.y_max());
            else
                x->rt = insert_recursive(std::move(x->rt), p, !is_vertical, x->p.x(), x->rect.y_min(), x->rect.x_max(), x->rect.y_max());
        }
        else
        {
            if (p.y() < x->p.y())
                x->lb = insert_recursive(std::move(x->lb), p, !is_vertical, x->rect.x_min(), x->rect.y_min(), x->rect.x_max(), x->p.y());
            else
                x->rt = insert_recursive(std::move(x->rt), p, !is_vertical, x->rect.x_min(), x->p.y(), x->rect.x_max(), x->rect.y_max());
        }
        return x;
    }

    void find_range_recursive(const std::unique_ptr<kdnode>& x, recthv rect, std::vector<point2d>& acc, bool is_vertical) const
    {
        if (rect.contains(x->p))
            acc.push_back(x->p);

        recthv bound = is_vertical ?
            recthv(x->p.x(), x->rect.y_min(), x->p.x(), x->rect.y_max()) :
            recthv(x->rect.x_min(), x->p.y(), x->rect.x_max(), x->p.y());
        if (rect.intersects(bound))
        {
            //both subtrees
            if (x->lb != nullptr)
                find_range_recursive(x->lb, rect, acc, !is_vertical);
            if (x->rt != nullptr)
                find_range_recursive(x->rt, rect, acc, !is_vertical);
        }
        else
        {
            //just one subtree
            if (x->lb != nullptr && rect.intersects(x->lb->rect))
                find_range_recursive(x->lb, rect, acc, !is_vertical);
            else if (x->rt != nullptr)
                find_range_recursive(x->rt, rect, acc, !is_vertical);
        }
    }

    kdnode* find_recursive(kdnode* x, point2d p, bool is_vertical) const
    {
        if (x == nullptr)
            return nullptr;
        int cmp = x->p.compare_to(p);
        if (0 == cmp)
            return x;
        if (is_vertical)
            return find_recursive(p.x() < x->p.x() ? x->lb.get() : x->rt.get(), p, !is_vertical);
        return find_recursive(p.y() < x->p.y() ? x->lb.get() : x->rt.get(), p, !is_vertical);
    }

    kdnode* find_insertion_point_recursive(kdnode* parent, kdnode* x, point2d p, bool is_vertical) const
    {
        if (nullptr == x)
            return parent;

        if (is_vertical)
        {
            if (p.x() < x->p.x())
                return find_insertion_point_recursive(x, x->lb.get(), p, !is_vertical);
            return find_insertion_point_recursive(x, x->rt.get(), p, !is_vertical);
        }
        
        if (p.y() < x->p.y())
            return find_insertion_point_recursive(x, x->lb.get(), p, !is_vertical);
        return find_insertion_point_recursive(x, x->rt.get(), p, !is_vertical);
    }

    double perpendicular_squared(kdnode* x, point2d p, bool is_vertical) const
    {
        point2d q = is_vertical ? point2d(x->p.x(), p.y()) : point2d(p.x(), x->p.y());
        return p.distance_squared_to(q);
    }

    point2d find_nearest_recursive(kdnode* x, point2d p, point2d closest, bool is_vertical) const
    {
        double a = p.distance_squared_to(x->p);
        double b = p.distance_squared_to(closest);
        point2d c = a < b ? x->p : closest;

        double dp_squared = perpendicular_squared(x, p, is_vertical);
        double min_squared = p.distance_squared_to(c);
        if (dp_squared < min_squared)
        {
            if (x->rt != nullptr)
            {
                point2d q = find_nearest_recursive(x->rt.get(), p, c, !is_vertical);
                double q_squared = p.distance_squared_to(q);
                if (q_squared < min_squared)
                {
                    c = q;
                    min_squared = q_squared;
                }
            }

            if (x->lb != nullptr)
            {
                point2d q = find_nearest_recursive(x->lb.get(), p, c, !is_vertical);
                double q_squared = p.distance_squared_to(q);
                if (q_squared < min_squared)
                {
                    c = q;
                    //min_squared = q_squared;
                }
            }
        }
        else
        {
            bool is_lb = is_vertical ? p.x() < x->p.x() : p.y() < x->p.y();
            if (is_lb)
            {
                if (x->lb != nullptr)
                    return find_nearest_recursive(x->lb.get(), p, c, !is_vertical);
            }
            else
            {
                if (x->rt != nullptr)
                    return find_nearest_recursive(x->rt.get(), p, c, !is_vertical);
            }
        }
        return c;
    }

public:
    size_t size() const { return N; }

    bool is_empty() const { return size() == 0; }

    void insert(point2d p)
    {
        root = insert_recursive(std::move(root), p, true, 0.0, 0.0, 1.0, 1.0);
    }

    std::vector<point2d> range(recthv rect) const
    {
        std::vector<point2d> acc;
        if (!is_empty())
            find_range_recursive(root, rect, acc, true);
        return acc;
    }

    bool contains(point2d p) const
    {
        return find_recursive(root.get(), p, true) != nullptr;
    }

    point2d nearest(point2d p) const
    {
        if (is_empty())
            throw std::runtime_error("Tree is empty");
        kdnode* closest = find_insertion_point_recursive(nullptr, root.get(), p, true);
        return find_nearest_recursive(root.get(), p, closest->p, true);
    }
};

struct data final
{
    double x, y; 
    bool label;
};

std::tuple<std::vector<data>, double, double> get_all_data()
{
    std::vector<data> xs;
    data d;
    double xmax = 0.0, ymax = 0.0;
    while (std::cin >> d.x >> d.y >> d.label)
    {
        xs.push_back(d);
        if (d.x > xmax) xmax = d.x;
        if (d.y > ymax) ymax = d.y;
    }
    return std::make_tuple(std::move(xs), xmax, ymax);
}

struct point2d_hash final
{
    size_t operator()(point2d p) const 
    {
        const size_t PRIME = 31;
        const size_t MULT = 1000;
        return PRIME * (static_cast<size_t>(p.x() * MULT)) + (static_cast<size_t>(p.y() * MULT));
    }
};

inline bool operator==(point2d lhs, point2d rhs)
{
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

void test_case_1(const std::vector<data>& xs, double xmax, double ymax)
{
    if (xs.size() > 0)
    {
        kdtree kd;
        std::unordered_set<point2d, point2d_hash> zeroes, ones;
        for (data x : xs)
        {
            point2d p(x.x / xmax, x.y / ymax);
            if (x.label == 0) zeroes.insert(p); else ones.insert(p);
            kd.insert(p);
        }

        point2d target(5.3 / xmax, 4.3 / ymax);
        //point2d target(4.8 / xmax, 8.1 / ymax);
        //point2d target(3.5 / xmax, 4.5 / ymax);
        point2d nearest = kd.nearest(target);
        bool zero = zeroes.find(nearest) != zeroes.end();
        bool one = ones.find(nearest) != ones.end();
        std::cout << "Target point is " << target.to_string() << "\n";
        std::cout << "The nearest point " << nearest.to_string() << " is classified as '" << (zero ? 0 : 1) << "'\n";

        double delta = 0.10;
        //double delta = 0.15;
        std::vector<point2d> points = kd.range(recthv(target.x() - delta, target.y() - delta, target.x() + delta, target.y() + delta));
        auto counters = std::accumulate(points.begin(), points.end(), std::make_tuple(0, 0),
            [&](std::tuple<int, int> acc, point2d p) { 
                int zc, oc; std::tie(zc, oc) = acc;
                return zeroes.find(p) != zeroes.end() ? std::make_tuple(zc + 1, oc) : std::make_tuple(zc, oc + 1); 
            });
        if (std::get<0>(counters) < std::get<1>(counters))
        {
            std::cout << "It's classified as '1' (" << 100.0 * std::get<1>(counters) / points.size() 
                << "% occurrences in the neighborhood)\n";
        }
        else if (std::get<0>(counters) > std::get<1>(counters))
        {
            std::cout << "It's classified as '0' (" << 100.0 * std::get<0>(counters) / points.size()
                << "% occurrences in the neighborhood)\n";
        }
        else
        {
            std::cout << "With inconclusive classification\n";
        }
    }
    else
    {
        std::cout << "No data\n";
    }
}

int main()
{
    std::vector<data> xs;
    double xmax, ymax;
    std::tie(xs, xmax, ymax) = get_all_data();
    test_case_1(xs, xmax, ymax);
    
    //sample kdtree API
    /*
    kdtree kd;
    kd.insert(point2d(0.1, 0.2));
    kd.insert(point2d(0.3, 0.1));
    kd.insert(point2d(0.3, 0.3));
    point2d nearest = kd.nearest(point2d(0.3, 0.35));
    std::vector<point2d> points = kd.range(recthv(0.3, 0.0, 1.0, 1.0));
    */
    
    return 0;
}