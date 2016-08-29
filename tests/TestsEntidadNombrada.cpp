#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "EntidadNombrada.h"

TEST(EntidadNombrada, givenEntidadNombrada_whenUsarInterfazPublica_then_ComportamientoCorrectoEsObtenido)
{
    EntidadNombrada e("Entidad", 2);
    EXPECT_EQ(e.getFrecuencia(), 2);
    EXPECT_EQ(e.getEntidadNombrada(), "Entidad");
    EntidadNombrada e2("Entidad", 1);
    EXPECT_EQ(e.esIgual(e2), true);
    e2.setEntidadNombrada("Prueba");
    EXPECT_EQ(e.esIgual(e2), false);
    e.setFrecuencia(3);
    EXPECT_EQ(e.getFrecuencia(), 3);
    EXPECT_EQ(e.toString(), "Entidad [3]");
    EXPECT_EQ(e2.toString(), "Prueba [1]");
}