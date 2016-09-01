
#ifndef ANALIZARNOTICIASLINUX_AGRUPACION_H
#define ANALIZARNOTICIASLINUX_AGRUPACION_H

#include <string>
#include <memory>
#include <list>
#include <iostream>
#include "Noticia.h"

class Agrupacion
{
public:
    std::set<std::string> getEntidades() const
    {
        std::set<std::string> entidades;
        for (const auto& n : noticias)
        {
            const auto entidad = n->getEntidadMasFrecuente().getEntidadNombrada();
            entidades.insert(entidad.begin(), entidad.end());
        }
        return entidades;
    }

    std::string getTitulo() const
    {
        if (noticias.size() > 0)
            return noticias.front()->getTitulo();
        else
            return "";
    }

    void push_back(std::shared_ptr<NoticiaInterface> noticia)
    {
        noticias.push_back(noticia);
    }

    std::list<std::shared_ptr<NoticiaInterface>>::iterator begin() { return noticias.begin(); }
    std::list<std::shared_ptr<NoticiaInterface>>::iterator end() { return noticias.end(); }

    const std::list<std::shared_ptr<NoticiaInterface>>::const_iterator begin() const { return noticias.begin(); }
    const std::list<std::shared_ptr<NoticiaInterface>>::const_iterator end() const { return noticias.end(); }

    void insert(std::list<std::shared_ptr<NoticiaInterface>>::iterator it1, std::list<std::shared_ptr<NoticiaInterface>>::iterator it2, std::list<std::shared_ptr<NoticiaInterface>>::iterator it3)
    {
        noticias.insert(it1, it2, it3);
    }
    void swap(Agrupacion& a) { noticias.swap(a.noticias); }

private:
    std::list<std::shared_ptr<NoticiaInterface>> noticias;
};

inline std::ostream& operator<<(std::ostream& os, const std::list<Agrupacion>& obj)
{
    for (auto& grupo : obj)
    {
        const auto e = grupo.getEntidades();
        for (const auto& e1 : e)
        {
            os << e1 + " ";
        }
        os << std::endl;
        for (const auto& noticia : grupo)
        {
            os << "   *[" + noticia->getTitulo() + "]\n";
        }
        os << std::endl;
    }

    return os;
}

#endif //ANALIZARNOTICIASLINUX_AGRUPACION_H
