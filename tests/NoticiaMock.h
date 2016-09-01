
#ifndef ANALIZARNOTICIASLINUX_NOTICIAMOCK_H
#define ANALIZARNOTICIASLINUX_NOTICIAMOCK_H


#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <NoticiaInterface.h>
#include "Noticia.h"
#include "Tuit.h"

class NoticiaMock : public NoticiaInterface
{
public:
    MOCK_METHOD1(setTitulo, void(std::string));
    MOCK_METHOD1(setCuerpo, void(std::string));
    MOCK_METHOD1(setPalabrasReservadas, void(std::shared_ptr<PalabrasReservadasInterface>));

    MOCK_CONST_METHOD0(getTitulo, std::string());
    MOCK_CONST_METHOD0(getCuerpo, std::string());
    MOCK_CONST_METHOD0(getEntidades, std::set<std::string>());
    MOCK_CONST_METHOD0(getEntidadMasFrecuente, EntidadComposite());
    MOCK_CONST_METHOD1(getFrecuenciaEntidad, int(EntidadComposite));
    MOCK_CONST_METHOD0(getPalabrasReservadas, std::shared_ptr<PalabrasReservadasInterface>());
    MOCK_CONST_METHOD0(getEntidadesRelevantes, std::set<std::string>());
    MOCK_CONST_METHOD0(toString, std::string());

    MOCK_METHOD1(accept, void(NoticiaVisitor& visitor));
};

class NoticiaTextoMock : public Noticia
{
public:

    MOCK_CONST_METHOD0(getTitulo, std::string());
    MOCK_CONST_METHOD0(getCuerpo, std::string());
    MOCK_CONST_METHOD0(getEntidades, std::set<std::string>());
    MOCK_CONST_METHOD0(getEntidadMasFrecuente, EntidadComposite());
    MOCK_CONST_METHOD1(getFrecuenciaEntidad, int(EntidadComposite));
    MOCK_CONST_METHOD0(getPalabrasReservadas, std::shared_ptr<PalabrasReservadasInterface>());
    MOCK_CONST_METHOD0(getEntidadesRelevantes, std::set<std::string>());
};

class TuitMock : public Tuit
{
public:

    MOCK_CONST_METHOD0(getTitulo, std::string());
    MOCK_CONST_METHOD0(getEntidades, std::set<std::string>());
    MOCK_CONST_METHOD0(getEntidadMasFrecuente, EntidadComposite());
    MOCK_CONST_METHOD1(getFrecuenciaEntidad, int(EntidadComposite));
    MOCK_CONST_METHOD0(getPalabrasReservadas, std::shared_ptr<PalabrasReservadasInterface>());
    MOCK_CONST_METHOD0(getEntidadesRelevantes, std::set<std::string>());
};


#endif //ANALIZARNOTICIASLINUX_NOTICIAMOCK_H
