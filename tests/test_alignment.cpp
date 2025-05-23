#include <gtest/gtest.h>
#include "AlignmentUtils.hpp"  // Tu archivo con las funciones declaradas

TEST(ScoreTest, calcularScoreCaracter) {
    EXPECT_EQ(calcularScoreCaracter('A', 'A'), 1);
    EXPECT_EQ(calcularScoreCaracter('C', 'G'), -1);
    EXPECT_EQ(calcularScoreCaracter('-', 'A'), -1);
    EXPECT_EQ(calcularScoreCaracter('-', '-'), 1);
}

TEST(SubstringTest, verificarSubstring) {
    EXPECT_EQ(verificarSubstring("AGTC", "GT"), "\"GT\" es substring de \"AGTC\".");
    EXPECT_EQ(verificarSubstring("GT", "AGTC"), "\"GT\" es substring de \"AGTC\".");
    EXPECT_EQ(verificarSubstring("ACGT", "TGCA"), "Ninguna cadena es substring de la otra.");

}

TEST(AlignmentTest, calcularScoreAlineado) {
    EXPECT_EQ(calcularScoreAlineado("-TACCG-A--T", "ATACCATACGT"), -3); // OK tras limpieza
    EXPECT_EQ(calcularScoreAlineado("AGTC", "AGTC"), 4);      // Igual sin guiones
    EXPECT_EQ(calcularScoreAlineado("A-GTC", "ATG-C"), -1);    // OK tras limpieza

    // Esta línea es la que estaba fallando por lanzar excepción
    EXPECT_THROW(calcularScoreAlineado("A-C-G-T", "A T G T"), std::invalid_argument);
}


TEST(AlignmentTest, alineamientoGlobal) {
    // Solo valida que no lance excepciones
    EXPECT_EQ(alineamientoGlobal("TACCGAT", "ATACCATACGT"), -3); 
    EXPECT_NO_THROW(alineamientoGlobal("GATTACA", "GCATGCU"));
}
