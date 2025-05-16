#include <fstream>
#include <string>
#include <iostream>

#include "classes/PDFGen.h"

int main()
{
    PDFGen pdf("boekhouding.pdf");

    std::cout << "input company name: ";
    std::string company_name;
    std::cin >> company_name;

    std::cout << "input street name: ";
    std::string street_name;
    std::cin >> street_name;

    std::cout << "input house address: ";
    std::string house_number;
    std::cin >> house_number;

    std::cout << "input postal code: ";
    std::string postal_code;
    std::cin >> postal_code;

    std::string address = street_name.append(", " + house_number + " " + postal_code);

    pdf.createPDF(company_name, address);

    std::cout << "PDF created successfully!" << std::endl;

    return 0;
}
