// all included libraries
#include <fstream>
#include <string>
#include <iostream>

// used classes
#include "classes/PDFGen.h"

int main()
{
    try
    {
        PDFGen pdf("test.pdf");
        pdf.createPDF("Sample Title", "Hello world");
        std::cout << "PDF created successfully!" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}