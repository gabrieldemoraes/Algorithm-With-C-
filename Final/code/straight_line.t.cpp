//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include <cmath>
#include <iostream>

namespace straight_line
{
    static void to_mathematica_plot(int A, int B, int C, int x_min = -5, int x_max = 5)
    {
        //Plot straight line in Mathematica where A=2, B=3, C=6 where input is Ax + By = C:
        //Plot[{(-2x+6)/3},{x,-5,5}]
        if (B == 0)
        {
            std::cout << "Plot[{x=" << (static_cast<float>(C) / A);
        }
        else if (A == 0)
        {
            std::cout << "Plot[{" << C;
        }
        else
        {
            std::cout << "Plot[{(" << (-A) << "x";
            if (C > 0) std::cout << "+" << C;
            else if (C < 0) std::cout << C;
            std::cout << ")/" << B;
        }
        std::cout << "},{x," << x_min << "," << x_max << "}]\n";
    }

    static int run_solution()
    {
        //PROBLEM: Find the intersections in a straight line
        //Straight line general equation:
        //Defined by a linear equation whose general form is: Ax + By + C = 0

        //INPUT: A, B, C
        //Our input represents the linear equation: Ax + By = C

        int A, B, C;
        std::cout << "A: "; std::cin >> A;
        std::cout << "B: "; std::cin >> B;
        std::cout << "C: "; std::cin >> C;

        //REQUIREMENTS:
        if (0 == A && 0 == B)
        {
            std::cout << "A and B can't be both 0\n";
            return -1;
        }

        //SOLUTION:
        float px = 0.f, py = 0.f;
        if (C != 0.f)
        {
            //Intersection at x-axis: isolate x and y = 0
            px = static_cast<float>(C) / A;
            //Intersection at y-axis: isolate y and x = 0
            py = static_cast<float>(C) / B;
        }

        //OUTPUT:
        float slope = 0.f;
        std::cout << "direction: ";
        if (A == 0) std::cout << "horizontal\n";
        else if (B == 0) std::cout << "vertical\n";
        else if ((slope = static_cast<float>(-A) / B) > 0.f) std::cout << "increasing\n";
        else std::cout << "decreasing\n";
        std::cout << "intersection point(s): ";
        bool has_px = !std::isinf(px);
        bool has_py = !std::isinf(py) && py != 0.f;
        if (has_px) std::cout << "(" << px << ", 0) ";
        if (has_py) std::cout << "(0, " << py << ")";
        if (has_px || has_py) std::cout << "\n";
        const float PI = 3.14159265f;
        if (slope && (-PI / 2.f <= slope && slope <= PI / 2.f))
        {
            std::cout << "angle in degrees:\n";
            std::cout << std::atan(slope) * 180.f / PI << "\n";
        }
        std::cout << "graph:\n";
        to_mathematica_plot(A, B, C);
        return 0;
    }
}

//Test cases:
//horizontal line: A=0, B=1, C=2
//vertical line: A=1, B=0, C=2
//positive slope (two intersections): A=-2, B=3, C=6
//negative slope (two intersections): A=2,  B=3, C=6
//positive slope (one intersection):  A=-2, B=3, C=0
//negative slope (one intersection):  A=2,  B=3, C=0
//positive slope (one intersection):  A=-1, B=1, C=0 (angle: 45 degrees)
//negative slope (one intersection):  A=1,  B=1, C=0 (angle:-45 degrees)
int straight_line_main(int argc, char *argv[], bool run)
{
    using straight_line::run_solution;
    
    if (run)
    {
        return run_solution();
    }

    return 0;
}