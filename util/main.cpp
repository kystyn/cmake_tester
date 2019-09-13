#include <iostream>
#include "png_toolkit.h"
#include "red_filter.h"

int main( int argc, char *argv[] )
{
    // toolkit filter_name base_pic_name sudent_tool student_pic_name limitPix limitMSE
    // toolkit near test images!
    try
    {
        if (argc != 7)
            throw "Not enough arguments";

        png_toolkit testTool;
        testTool.load(argv[2]);

        filter::red r("fillHalfRed");

        auto f = filter::filters.find(argv[1]);
        if (f != filter::filters.end())
            testTool.applyFilter(*(f->second));
        else
            throw "Bad filter";

        png_toolkit studTool;
        system(("./" + std::string(argv[3]) + ' ' +  argv[2] + ' ' + argv[4]).c_str());
        studTool.load(argv[4]);

        png_toolkit::Error err;
        int diffPix;
        auto mse = testTool.mseDeviation(studTool, err, diffPix);
        if (err == png_toolkit::Error::Ok) // TODO num of diff pixels limits
        {
            if (diffPix < std::stoi(argv[5]))
                std::cout << "OK ";
            else
                std::cout << "BAD: Too many bad pixels: " << diffPix << " ";

            if (mse < std::stoi(argv[6]))
                std::cout << "OK";
            else
                std::cout << "BAD: Too big MSE: " << mse;
        }
        else
            throw "Bad picture size/format";
    }
    catch (const char *str)
    {
        std::cout << "Error: " << str << std::endl;
        return 1;
    }

    return 0;
}
