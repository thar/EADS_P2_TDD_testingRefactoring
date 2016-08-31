
#ifndef ANALIZARNOTICIASLINUX_LINEWORDITERATOR_H
#define ANALIZARNOTICIASLINUX_LINEWORDITERATOR_H

#include <iostream>
#include <iterator>
#include <string>
#include <sstream>


class LineWordIterator
{
public:

    LineWordIterator(std::string line) : inputLine(line), beginIterator(inputLine), lineSize(line.size()) { }
    std::istream_iterator<std::string> begin() { return beginIterator; }
    std::istream_iterator<std::string> end() { return std::istream_iterator<std::string>(); }
    float getPosition()
    {
        if (inputLine.eof())
            return 1;
        else
            return static_cast<float>(inputLine.tellg())/lineSize;
    }
protected:
private:
    std::istringstream inputLine;
    std::istream_iterator<std::string> beginIterator;
    unsigned long lineSize;
};

#endif //ANALIZARNOTICIASLINUX_LINEWORDITERATOR_H
