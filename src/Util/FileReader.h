#ifndef FILEREADER_H
#define FILEREADER_H
#include <fstream>
#include <string>


class FileReader {
public:
    explicit FileReader(const std::string &path);

    std::string getFileContent() { return fileContent; }

    std::string readLine();

    std::string readAllLines();

    void close();

    char readChar();

    bool isOpen();

    std::streampos fileSize();

private:
    std::string fileContent;
    std::string filePath;
    std::ifstream fileStream;

    void openIfIsClosed();
};


#endif //FILEREADER_H
