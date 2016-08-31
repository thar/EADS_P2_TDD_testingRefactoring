/*
 * EntidadNombrada.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef ENTIDADNOMBRADA_H_
#define ENTIDADNOMBRADA_H_
#include <string>
#include <set>

class EntidadComposite {


public:

    EntidadComposite() {}
	EntidadComposite( const std::string n);
    EntidadComposite( const char * n) : EntidadComposite(std::string(n)) {}

    EntidadComposite& operator+=(const EntidadComposite& rhs) {

        return *this;
    }

    std::set<std::string> getEntidadNombrada() const;

    friend bool operator< (const EntidadComposite& lhs, const EntidadComposite& rhs);
    friend bool operator> (const EntidadComposite& lhs, const EntidadComposite& rhs){ return rhs < lhs; }
    friend bool operator<=(const EntidadComposite& lhs, const EntidadComposite& rhs){ return !(lhs > rhs); }
    friend bool operator>=(const EntidadComposite& lhs, const EntidadComposite& rhs){ return !(lhs < rhs); }
    friend bool operator==(const EntidadComposite& lhs, const EntidadComposite& rhs);
    friend bool operator!=(const EntidadComposite& lhs, const EntidadComposite& rhs){ return !(lhs == rhs); }

    friend std::ostream& operator<<(std::ostream& os, const EntidadComposite& obj)
    {
        return os;
    }

};

#endif /* ENTIDADNOMBRADA_H_ */
