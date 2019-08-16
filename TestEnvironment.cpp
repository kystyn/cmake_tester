// TestEnvironment.cpp : Defines the entry point for the application.
//

#include "TestEnvironment.h"
#include <vector>

using namespace std;

std::vector<double> solveLinear(const std::vector<double>& eq) {
    if (eq[0] == 0.0) {
        /*if (eq[1] == 0.0)
            return { 0.0 };
        else*/ 
            throw std::runtime_error("Error!\n");
    }
    else 
        return { -eq[1] / eq[0] };
}

std::vector<double> solveSqr(const std::vector<double>& eq) {
    if (eq.size() < 3)
        throw std::runtime_error("Error!\n");
    double d = eq[1] * eq[1] - 4.0 * eq[0] * eq[2];
    if (d < 0.0)
        throw std::runtime_error("Error!\n");

    if (d == 0.0)
        return {-eq[1] / (2.0 * eq[0])};
    if (eq[0] == 0.0)
        return solveLinear({ eq[1], eq[2] });
    
    return { (-eq[1] + sqrt(d)) / (2.0 * eq[0]), (-eq[1] - sqrt(d)) / (2.0 * eq[0]) };
}

int main(int argC, char * argv[])
{
    try {
        double a, b, c;
        if (argC < 4) {
            //throw std::runtime_error("Error!\n");
            std::cout << "Error!" << std::endl;
            return 0;
        }
        sscanf(argv[1], "%lf", &a);
        sscanf(argv[2], "%lf", &b);
        sscanf(argv[3], "%lf", &c);

        auto res = solveSqr({ a, b, c });
        std::cout << "The result is: ";
        std::cout << res[0];
        if (res.size() > 1)
            std::cout << ' ' << res[1];
        std::cout << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what();
    }

	return 0;
}
