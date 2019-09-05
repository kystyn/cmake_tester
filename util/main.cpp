#include <iostream>
#include "png_toolkit.h"

int main( void )
{
    // toolkit filter_name base_pic_name sudent_tool student_pic_name limitPix limitMSE
    // toolkit near test images!
    try
    {
        png_toolkit testTool;
        testTool.load("ex1.png");
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
