#include <fstream>
#include <string>
#include <iostream>

#include "classes/PDFGen.h"

int main() {
    PDFGen pdf("output.pdf");

    std::string title = "test";
    std::string content = "test";

    pdf.createPDF(title, content);

    return 0;
}
