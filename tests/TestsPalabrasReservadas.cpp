#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "PalabrasReservadas.h"

TEST(PalabrasReservadas, givenFicheroConPalabrasReservadas_whenPalabrasReservadasEsCreado_y_SuTamanioEsPreguntado_then_ElNumeroDePalabrasDelFicheroEsRetornado)
{
    PalabrasReservadas p("data/ES_stopList.txt");
    //El fichero tiene 351 palabras
    ASSERT_EQ(p.size(), 351);
}

TEST(PalabrasReservadas, givenSetDePalabrasConUnaPalabra_whenPalabrasReservadasCreadoDesdeSet_y_PreguntadoSiContieneLaPalabraDelSetOriginal_then_true)
{
    std::set<std::string> palabras;
    palabras.insert("hola");
    PalabrasReservadas p(palabras);
    ASSERT_EQ(p.size(), 1);
    ASSERT_EQ(p.has("hola"), true);
}

TEST(PalabrasReservadas, givenSetDePalabrasConUnaPalabra_whenPalabrasReservadasCreadoDesdeSet_y_PreguntadoSiContieneUnaPalabraNoPertenecienteAlSet_then_false)
{
    std::set<std::string> palabras;
    palabras.insert("hola");
    PalabrasReservadas p(palabras);
    ASSERT_EQ(p.size(), 1);
    ASSERT_EQ(p.has("otraPalabra"), false);
}
