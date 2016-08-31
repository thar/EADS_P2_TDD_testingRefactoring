
#ifndef ANALIZARNOTICIASLINUX_FILELINEITERATOR_H
#define ANALIZARNOTICIASLINUX_FILELINEITERATOR_H

#include <iostream>
#include <iterator>
#include <fstream>
#include <string>



class FileLineIterator
{
public:
    class Line : public std::string {};

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
    std::getline(is, l);
    return is;
}

#endif //ANALIZARNOTICIASLINUX_FILELINEITERATOR_H
