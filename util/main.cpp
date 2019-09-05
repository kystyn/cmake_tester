#include <iostream>
#include "png_toolkit.h"

int main( void )
{
    // 0toolkit
    // 1filter_name
    // 2base_pic_name
    // 3sudent_tool
    // 4student_pic_name
    // 5limitPix
    // 6limitMSE
    // toolkit near test images!
    try
    {
        png_toolkit testTool;
        testTool.load("ex1.png");
        testTool.applyFilter(png_toolkit::Filter::FILL_HALF_RED);
        png_toolkit studTool;
        studTool.load("res.png");

        png_toolkit::Error err;
        int diffPix;
        auto mse = testTool.mseDeviation(studTool, err, diffPix);
        if (err == png_toolkit::Error::Ok) // TODO num of diff pixels limits
        {
            if (diffPix < std::stoi("10"))
                std::cout << "OK ";
            else
                std::cout << "Too many bad pixels: " << diffPix << " ";

            if (mse < std::stoi("30"))
                std::cout << "OK";
            else
                std::cout << "Too big MSE: " << mse;
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
