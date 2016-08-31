
#ifndef ANALIZARNOTICIASLINUX_NOTICIAMOCK_H
#define ANALIZARNOTICIASLINUX_NOTICIAMOCK_H


#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <NoticiaInterface.h>

class NoticiaMock : public NoticiaInterface
{
public:
    MOCK_METHOD1(setTitulo, void(std::string));
    MOCK_METHOD1(setCuerpo, void(std::string));
    MOCK_METHOD1(setPalabrasReservadas, void(std::string));
    MOCK_METHOD0(actualizar, void());

    MOCK_CONST_METHOD0(getTitulo, std::string());
    MOCK_CONST_METHOD0(getCuerpo, std::string());
    MOCK_CONST_METHOD0(getEntidades, std::list<std::string>());
    MOCK_CONST_METHOD0(getEntidadMasFrecuente, EntidadComposite());
    MOCK_CONST_METHOD1(getFrecuenciaEntidad, int(EntidadComposite));
    MOCK_CONST_METHOD0(getPalabrasReservadas, std::list<std::string>());
    MOCK_CONST_METHOD0(getEntidadesRelevantes, std::list<std::string>());
    MOCK_CONST_METHOD1(esAgrupable, bool(std::shared_ptr<NoticiaInterface> noticia));
    MOCK_CONST_METHOD0(toString, std::string());
};


#endif //ANALIZARNOTICIASLINUX_NOTICIAMOCK_H
