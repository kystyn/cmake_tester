#include <iostream>
#include "png_toolkit.h"
#include "red_filter.h"
#include "threshold.h"

int main( int argc, char *argv[] )
{
    // toolkit filter_name base_pic_name sudent_tool student_pic_name limitPix limitMSE
    // top left bottom riht
    // toolkit near test images!
    try
    {
        if (argc != 11)
            throw "Not enough arguments";

        png_toolkit testTool;
        testTool.load(argv[2]);

        // fill all filters
        filter::red r("Red");
        filter::threshold t("Threshold");

        auto f = filter::base::filters.find(argv[1]);
        filter::base::area ar;
        ar.top = std::stoi(argv[7]);
        ar.left = std::stoi(argv[8]);
        ar.bottom = std::stoi(argv[9]);
        ar.right = std::stoi(argv[10]);

        if (f != filter::base::filters.end())
            testTool.applyFilter(*(f->second), ar);
        else
            throw "Bad filter";

        png_toolkit studTool;
        system(("./" + std::string(argv[3]) + ' ' +  argv[1] + ' ' + argv[2] + ' ' + argv[4]).c_str());
        studTool.load(argv[4]);

        png_toolkit::Error err;
        int diffPix;
        auto mse = testTool.mseDeviation(studTool, err, diffPix, ar);
        if (err == png_toolkit::Error::Ok)
        {
            if (diffPix < std::stof(argv[5]))
                std::cout << "OK ";
            else
                std::cout << "BAD: Too many bad pixels: " << diffPix << " ";

            if (mse < std::stof(argv[6]))
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
