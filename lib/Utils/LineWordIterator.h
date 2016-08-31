
#ifndef ANALIZARNOTICIASLINUX_LINEWORDITERATOR_H
#define ANALIZARNOTICIASLINUX_LINEWORDITERATOR_H

#include <iostream>
#include <iterator>
#include <string>
#include <sstream>


class LineWordIterator
{
public:
    typedef std::string Word;

    LineWordIterator(std::string line) : inputLine(line), beginIterator(inputLine) { }
    std::istream_iterator<Word> begin() { return beginIterator; }
    std::istream_iterator<Word> end() { return std::istream_iterator<Word>(); }
    float getPosition()
    {
        return 0;
    }
protected:
private:
    std::istringstream inputLine;
    std::istream_iterator<Word> beginIterator;
};

inline std::istream &operator>>(std::istream &is, LineWordIterator::Word &w)
{
    return is;
}

#endif //ANALIZARNOTICIASLINUX_LINEWORDITERATOR_H
