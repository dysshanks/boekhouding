#ifndef BOEKHOUDING_PDFGEN_H
#define BOEKHOUDING_PDFGEN_H

#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

class PDFGen
{
public:
    PDFGen(const std::string& filename) : filename(filename) {}

    void createPDF(const std::string& company_name, const std::string& content)
    {
        std::ofstream pdf(filename, std::ios::binary);

        pdf << "%PDF-1.4\n";

        std::string set_title = setPDFText(company_name);
        std::string set_adress = setPDFText(content);
        std::string page_content = "BT /F1 24 Tf 100 750 Td (" + set_title + ") Tj ET\n";
        page_content += "BT /F1 14 Tf 100 700 Td (" + set_adress + ") Tj ET";

        pdf << "1 0 obj\n";
        pdf << "<< /Type /Catalog /Pages 2 0 R >>\n";
        pdf << "endobj\n";

        pdf << "2 0 obj\n";
        pdf << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n";
        pdf << "endobj\n";

        pdf << "3 0 obj\n";
        pdf << "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 595 842] /Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >>\n";
        pdf << "endobj\n";

        pdf << "4 0 obj\n";
        pdf << "<< /Length " << page_content.size() << " >>\n";
        pdf << "stream\n" << page_content << "\nendstream\n";
        pdf << "endobj\n";

        pdf << "5 0 obj\n";
        pdf << "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n";
        pdf << "endobj\n";

        std::streampos xref_pos = pdf.tellp();
        pdf << "xref\n";
        pdf << "0 6\n";
        writeOffset(pdf, 0);
        writeOffset(pdf, 9);
        writeOffset(pdf, 38);
        writeOffset(pdf, 75);
        writeOffset(pdf, 184);
        writeOffset(pdf, 272);

        pdf << "trailer\n";
        pdf << "<< /Size 6 /Root 1 0 R >>\n";
        pdf << "startxref\n";
        pdf << xref_pos << "\n";
        pdf << "%%EOF";

        pdf.close();
        std::cout << "PDF file '" << filename << "' created successfully!" << std::endl;
    }

private:
    std::string filename;

    void writeOffset(std::ofstream& file, long pos)
    {
        file << std::setw(10) << std::setfill('0') << pos << " 00000 n \n";
    }

    std::string setPDFText(const std::string& text)
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
};

#endif //BOEKHOUDING_PDFGEN_H