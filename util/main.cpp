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

void brightness( image_data const &imgData )
{
    for (int i = 0;
         i < imgData.w * imgData.h * imgData.compPerPixel;
         i += imgData.compPerPixel)
    {
        auto newc = stbi_uc(double(imgData.pixels[i + 0] * 0.3 +
                imgData.pixels[i + 1] * 0.6 +
                imgData.pixels[i + 2] * 0.1));
        for (int c = 0; c < 3; c++)
            imgData.pixels[i + c] = newc;
    }
}

int main( int argc, char *argv[] )
{
    // toolkit config filter_name ref_pic_name student_pic_name limitPix limitMSE
    // OR
    // toolkit config base_pic_name ref_pic_name stud_tool stud_pic_name #it means - generate reference my and student image
    // config format: <filter name> top left bottom right
    // toolkit near test images!
    try
    {
        if (argc != 7 && argc != 6)
            throw "Not enough arguments";

        png_toolkit testTool;
        testTool.load(argv[2]);

        // fill all filters
        filter::red r("Red");
        filter::threshold t("Threshold", brightness);
        filter::convolution<3> blur("Blur",
            std::array<std::array<double, 3>, 3>{
                std::array<double, 3>{1.0, 1.0, 1.0},
                {1.0, 1.0, 1.0},
                {1.0, 1.0, 1.0}
            });
        filter::convolution<3> border("Edge",
            std::array<std::array<double, 3>, 3>{
                std::array<double, 3>{-1.0, -1.0, -1.0},
                {-1.0, 9.0, -1.0},
                {-1.0, -1.0, -1.0}
            }, brightness);

        std::ifstream ifs(argv[1]);
        if (!ifs)
            throw "Bad config name";

        if (argc == 6)
        {
            testTool.load(argv[2]);
            while (ifs)
            {
                std::string filterName;
                filter::base::area ar;
                ifs >> filterName >> ar;

                if (filterName.empty())
                    break;

                auto f = filter::base::getFilters().find(filterName);
                if (f != filter::base::getFilters().end())
                    testTool.applyFilter(*(f->second), ar);
                else
                    throw "Bad filter";
            }
            testTool.save(argv[3]);
            std::string
                    config = std::filesystem::absolute(argv[1]),
                    base = std::filesystem::absolute(argv[2]),
                    stud = std::filesystem::absolute(argv[5]);
            system(("./" + std::string(argv[4]) + ' ' + config + ' ' + base + ' ' + stud).c_str());
            std::cout << "OK\n";
            return 0;
        }

        testTool.load(argv[2]);
        png_toolkit studTool;
        studTool.load(argv[3]);

        filter::base::area ar;
        std::string filterName;

        while (ifs)
        {
            ifs >> filterName;
            if (filterName == argv[2])
            {
                ifs >> ar;
                break;
            }
        }

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
