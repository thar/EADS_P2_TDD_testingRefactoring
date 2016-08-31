#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "EntidadComposite.h"

TEST(EntidadComposite, givenEntidadCompositeFormadaPorPalabra_Uno_y_MultiplesPalabras_whenPreguntarPorIgualdad_then_SoloEsTrueCuandoSeEjecutaConString_Uno_EnCualquierSentido)
{
    EntidadComposite e("Uno");
    EXPECT_EQ(e == "Uno", true);
    EXPECT_EQ("Uno" == e, true);
    EXPECT_EQ(e == "Dos", false);
    EXPECT_EQ("Dos" == e, false);
}

TEST(EntidadComposite, givenEntidadCompositeFormadaPorPalabras_Uno_y_Dos_y_MultiplesPalabras_whenPreguntarPorIgualdad_then_EsTrueCuandoSeEjecutaConStrings_Uno_o_Dos_EnCualquierSentido)
{
    EntidadComposite e("Uno");
    e += "Dos";
    EXPECT_EQ(e == "Uno", true);
    EXPECT_EQ("Uno" == e, true);
    EXPECT_EQ(e == "Dos", true);
    EXPECT_EQ("Dos" == e, true);
    EXPECT_EQ("Tres" == e, false);
}

TEST(EntidadComposite, givenDosEntidadCompositeLaSegundaComoLaPrimeraMasLaPalabraDos_whenPreguntarPorIgualdad_then_TrueEnCualquierSentido)
{
    EntidadComposite e("Uno");
    EntidadComposite e2 = e;
    EXPECT_EQ(e == e2, true);
    e2 += "Dos";
    EXPECT_EQ(e == e2, true);
}

TEST(EntidadComposite, givenEntidadCompositeFormadaPorPalabra_Uno_whenSumarUnaPalabra_then_EntidadCompositeSeExtiendeConLaNuevaPalabra)
{
    EntidadComposite e("Uno");
    EntidadComposite e2 = e;
    EXPECT_EQ(e.getEntidadNombrada().size(), 1);
    e2 += "Dos";
    e += e2;
    EXPECT_EQ(e.getEntidadNombrada().size(), 2);
    EXPECT_EQ("Dos" == e, true);
}