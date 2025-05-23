#include <fstream>
#include <string>
#include <iostream>
#include <ctime>

#include "classes/PDFGen.h"

int main()
{
    PDFGen pdf("boekhouding.pdf");

    std::string company_name;
    std::cout << "input company name: ";
    std::cin >> company_name;

    std::string street_name;
    std::cout << "input street name: ";
    std::cin >> street_name;

    std::string house_number;
    std::cout << "input house address: ";
    std::cin >> house_number;

    std::string postal_code;
    std::cout << "input postal code: ";
    std::cin >> postal_code;

    std::string invoice_number;
    std::cout << "input Factuurnummer: ";
    std::cin >> invoice_number;

    std::string inputDate;
    std::cout << "Enter a date (YYYY-MM-DD): ";
    std::cin >> inputDate;

    int year, month, day;
    char dash1, dash2;
    std::istringstream iss(inputDate);
    if (!(iss >> year >> dash1 >> month >> dash2 >> day) || dash1 != '-' || dash2 != '-') {
        std::cerr << "Invalid date format." << std::endl;
        return 1;
    }

    std::tm date_tm = {};
    date_tm.tm_year = year - 1900;
    date_tm.tm_mon = month - 1;
    date_tm.tm_mday = day;

    std::time_t input_time = std::mktime(&date_tm);
    if (input_time == -1) {
        std::cerr << "Failed to convert input date to time_t." << std::endl;
        return 1;
    }

    std::cout << "input kvk: ";
    std::string kvk_number;
    std::cin >> kvk_number;

//    std::string item_name;
//    std::cout << "input item name: ";
//    std::cin >> item_name;

    std::string experation_time = "30";

    std::string address = street_name.append(", " + house_number + " " + postal_code);
    std::string invoice =
            "Factuurnummer: " + invoice_number + "\n" +
            "Factuurdatum: " + inputDate + "\n" +
            "Verlooptermijn: " + experation_time + "\n" +
            "kvk: " + kvk_number;

    pdf.createPDF(company_name, address, invoice);

    std::cout << "PDF created successfully!" << std::endl;

    return 0;
}
