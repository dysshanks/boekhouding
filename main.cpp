// all included libraries
#include <fstream>
#include <string>
#include <iostream>

class PDFGen
        {
public: PDFGen(const std::string& filename) : filename(filename) {}

    void createPDF(const std::string& title, const std::string& content)
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Failed to open file");
        }

        file << "%PDF-1.4\n";
        int objCount = 1;

        long titleObjPos = file.tellp();
        file << objCount++ << " 0 obj\n<< /Type /Metadata /Subtype /XML /Length " << title.size() + 28 << " >>\nstream\n";
        file << "<?xpacket begin='\xef\xbb\xbf' id='W5M0MpCehiHzreSzNTczkc9d'?>\n";
        file << "<title>" << title << "</title>\n";
        file << "<?xpacket end='w'?>\nendstream\nendobj\n";

        long pageObjPos = file.tellp();
        file << objCount++ << " 0 obj\n<< /Type /Page /Parent 3 0 R /Contents 4 0 R >>\nendobj\n";

        long pagesObjPos = file.tellp();
        file << objCount++ << " 0 obj\n<< /Type /Pages /Kids [2 0 R] /Count 1 >>\nendobj\n";

        long catalogObjPos = file.tellp();
        file << objCount++ << " 0 obj\n<< /Type /Catalog /Pages 3 0 R >>\nendobj\n";

        long contentObjPos = file.tellp();
        file << objCount++ << " 0 obj\n<< /Length " << content.size() + 18 << " >>\nstream\nBT /F1 12 Tf 72 720 Td (" << content << ") Tj ET\nendstream\nendobj\n";

        long xrefPos = file.tellp();
        file << "xref\n0 " << objCount << "\n0000000000 65535 f \n";
        file << std::string(titleObjPos, '0') << " 00000 n \n";
        file << std::string(pageObjPos, '0') << " 00000 n \n";
        file << std::string(pagesObjPos, '0') << " 00000 n \n";
        file << std::string(catalogObjPos, '0') << " 00000 n \n";
        file << std::string(contentObjPos, '0') << " 00000 n \n";

        file << "trailer\n<< /Size " << objCount << " /Root 4 0 R >>\nstartxref\n" << xrefPos << "\n%%EOF";
        file.close();
    }

private: std::string filename;
};

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