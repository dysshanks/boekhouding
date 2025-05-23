#ifndef BOEKHOUDING_PDFGEN_H
#define BOEKHOUDING_PDFGEN_H

#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <sstream>

class PDFGen
{
public:
    explicit PDFGen(std::string filename) : filename(std::move(filename)) {}

    void createPDF(const std::string& company_name, const std::string& content, const std::string& invoice)
    {
        std::ofstream pdf(filename, std::ios::binary);

        pdf << "%PDF-1.4\n";

        std::string set_title = setPDFText(company_name);
        std::string set_adress = setPDFText(content);
        std::vector<std::string> invoice_lines = splitLines(invoice);

        std::string page_content;

        page_content += "BT /F1 36 Tf 50 800 Td (" + set_title + ") Tj ET\n";

        page_content += "BT /F1 14 Tf 50 770 Td (" + set_adress + ") Tj ET\n";

        int y_pos = 730;
        for (const auto& line : invoice_lines)
        {
            std::string formatted = setPDFText(line);
            page_content += "BT /F1 14 Tf 100 " + std::to_string(y_pos) + " Td (" + formatted + ") Tj ET\n";
            y_pos -= 20;
        }

        pdf << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        pdf << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        pdf << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 595 842] /Contents 4 0 R "
               "/Resources << /Font << /F1 5 0 R >> >> >>\nendobj\n";
        pdf << "4 0 obj\n<< /Length " << page_content.size() << " >>\nstream\n";
        pdf << page_content << "endstream\nendobj\n";
        pdf << "5 0 obj\n<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\nendobj\n";

        std::streampos xref_pos = pdf.tellp();
        pdf << "xref\n0 6\n";
        writeOffset(pdf, 0);
        writeOffset(pdf, 9);
        writeOffset(pdf, 38);
        writeOffset(pdf, 75);
        writeOffset(pdf, 184);
        writeOffset(pdf, 272);

        pdf << "trailer\n<< /Size 6 /Root 1 0 R >>\nstartxref\n" << xref_pos << "\n%%EOF";
        pdf.close();

        std::cout << "PDF file '" << filename << "' created successfully!" << std::endl;
    }

private:
    std::string filename;

    static void writeOffset(std::ofstream& file, long pos)
    {
        file << std::setw(10) << std::setfill('0') << pos << " 00000 n \n";
    }

    static std::string setPDFText(const std::string& text)
    {
        std::string set;
        for (char c : text)
        {
            if (c == '(' || c == ')' || c == '\\')
            {
                set += '\\';
            }
            set += c;
        }
        return set;
    }

    static std::vector<std::string> splitLines(const std::string& text, char delimiter = '\n')
    {
        std::vector<std::string> lines;
        std::stringstream ss(text);
        std::string line;
        while (std::getline(ss, line, delimiter))
        {
            lines.push_back(line);
        }
        return lines;
    }
};

#endif // BOEKHOUDING_PDFGEN_H
