#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "LineWordIterator.h"

TEST(LineWordIterator, givenCadenaConVariasPalabrasSeparadasPorDiferentesEspacios_whenUsandoIteradorDePalabrasEnLinea_then_TodasLasPalabrasSonRecorridas)
{
    std::string line("Prueba pruebo\ttest\ntest");
    LineWordIterator lit(line);
    std::vector<std::string> wordSplitResult(4);
    std::vector<float> progressSplitResult(4);
    wordSplitResult[0] = "Prueba";
    wordSplitResult[1] = "pruebo";
    wordSplitResult[2] = "test";
    wordSplitResult[3] = "test";
    progressSplitResult[0] = static_cast<float>(wordSplitResult[0].size()) / line.size();
    progressSplitResult[1] = progressSplitResult[0] + static_cast<float>(wordSplitResult[1].size() + 1) / line.size();
    progressSplitResult[2] = progressSplitResult[1] + static_cast<float>(wordSplitResult[2].size() + 1) / line.size();
    progressSplitResult[3] = 1;
    int index = 0;
    for (auto l : lit)
    {
        ASSERT_LE(index, 3);
        EXPECT_EQ(l, wordSplitResult[index]);
        EXPECT_EQ(lit.getPosition(), progressSplitResult[index]);
        ++index;
    }
}