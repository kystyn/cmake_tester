#include <iostream>
#include <fstream>
#include <filesystem>

#include "png_toolkit.h"
#include "red_filter.h"
#include "threshold.h"
#include "convolution.h"

std::istream & operator>>( std::istream &is, filter::base::area &ar )
{
    is >> ar.top >> ar.left >> ar.bottom >> ar.right;
    return is;
}

int main( int argc, char *argv[] )
{
    // toolkit filter_name ref_pic_name student_pic_name limitPix limitMSE
    // top left bottom right
    // OR
    // toolkit config base_pic_name ref_pic_name stud_tool stud_pic_name #it means - generate reference my and student image
    // config format: <filter name> top left bottom right
    // toolkit near test images!
    try
    {
        if (argc != 10 && argc != 6)
            throw "Not enough arguments";

        png_toolkit testTool;
        testTool.load(argv[2]);

        // fill all filters
        filter::red r("Red");
        filter::threshold t("Threshold");

        filter::convolution<3> blur("Blur",
            std::array<std::array<double, 3>, 3>{
                std::array<double, 3>{1.0, 1.0, 1.0},
                {1.0, 1.0, 1.0},
                {1.0, 1.0, 1.0}
            });
        filter::convolution<3> border("Border",
            std::array<std::array<double, 3>, 3>{
                std::array<double, 3>{-1.0, -1.0, -1.0},
                {-1.0, 9.0, -1.0},
                {-1.0, -1.0, -1.0}
            });

        if (argc == 6)
        {
            std::ifstream ifs(argv[1]);
            if (!ifs)
                throw "Bad file name";

            testTool.load(argv[2]);
            while (ifs)
            {
                std::string filterName;
                filter::base::area ar;
                ifs >> filterName >> ar;

                if (filterName.empty())
                    break;

                auto f = filter::base::filters.find(filterName);
                if (f != filter::base::filters.end())
                    testTool.applyFilter(*(f->second), ar);
                else
                    throw "Bad filter";
            }
            testTool.save(argv[3]);
            std::string
                    config = std::filesystem::absolute(argv[1]),
                    base = std::filesystem::absolute(argv[2]),
                    ref = std::filesystem::absolute(argv[5]);
            system(("./" + std::string(argv[4]) + ' ' + config + ' ' + base + ' ' + ref).c_str());
            return 0;
        }

        testTool.load(argv[2]);
        png_toolkit studTool;
        studTool.load(argv[3]);

        filter::base::area ar;
        ar.top = std::stoi(argv[6]);
        ar.left = std::stoi(argv[7]);
        ar.bottom = std::stoi(argv[8]);
        ar.right = std::stoi(argv[9]);

        png_toolkit::Error err;
        int diffPix;
        auto mse = testTool.mseDeviation(studTool, err, diffPix, ar);
        if (err == png_toolkit::Error::Ok)
        {
            if (diffPix < std::stoi(argv[4]))
                std::cout << "OK ";
            else
                std::cout << "BAD: Too many bad pixels: " << diffPix << " ";

            if (mse < std::stof(argv[5]))
                std::cout << "OK";
            else
                std::cout << "BAD: Too big MSE: " << mse;
        }
        else
            throw "Bad picture size/format";
    }
    catch (const char *str)
    {
        std::cout << "BAD: Error: " << str << std::endl;
        return 1;
    }

    return 0;
}
