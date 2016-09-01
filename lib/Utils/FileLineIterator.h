
#ifndef ANALIZARNOTICIASLINUX_FILELINEITERATOR_H
#define ANALIZARNOTICIASLINUX_FILELINEITERATOR_H

#include <iostream>
#include <iterator>
#include <fstream>
#include <string>



class FileLineIterator
{
public:
    class Line
    {
    public:
        Line() : line() {}
        Line(const std::string line) : line(line) {}
        Line(const char * line) : Line(std::string(line)) {}
        std::string getLine() const { return line; }
        Line& operator =(const std::string& b)
        {
            line = b;
        }
    private:
        std::string line;
    };

    FileLineIterator(std::string filePath) : inputFile(filePath), beginIterator(inputFile) { }
    bool is_open() { return inputFile.is_open(); }
    std::istream_iterator<Line> begin() { return beginIterator; }
    std::istream_iterator<Line> end() { return std::istream_iterator<Line>(); }
protected:
private:
    std::ifstream inputFile;
    std::istream_iterator<Line> beginIterator;
};

inline std::istream &operator>>(std::istream &is, FileLineIterator::Line &l)
{
    std::string tempLine;
    std::getline(is, tempLine);
    l = tempLine;
    return is;
}

#endif //ANALIZARNOTICIASLINUX_FILELINEITERATOR_H
