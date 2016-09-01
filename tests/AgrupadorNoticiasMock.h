
#ifndef ANALIZARNOTICIASLINUX_AGRUPADORNOTICIASMOCK_H
#define ANALIZARNOTICIASLINUX_AGRUPADORNOTICIASMOCK_H


#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <AgrupadorNoticiasInterface.h>

class AgrupadorNoticiasMock : public AgrupadorNoticiasInterface
{
public:
    MOCK_CONST_METHOD2(isAgregableEntidadMasFrecuente, bool(std::shared_ptr<NoticiaInterface>, std::shared_ptr<NoticiaInterface>));
    MOCK_METHOD2(isAgregable, bool(std::shared_ptr<NoticiaInterface>, std::shared_ptr<NoticiaInterface>));
};


#endif //ANALIZARNOTICIASLINUX_AGRUPADORNOTICIASMOCK_H
