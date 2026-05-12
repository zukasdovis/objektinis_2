#include <gtest/gtest.h>
#include <sstream>
#include "studentai.h"

// =============================================
// DEFAULT KONSTRUKTORIUS
// =============================================
TEST(StudentasTest, DefaultKonstruktorius)
{
    Studentas s;
    EXPECT_EQ(s.vardas(), "");
    EXPECT_EQ(s.pavarde(), "");
    EXPECT_DOUBLE_EQ(s.galutinis_med(), 0.0);
    EXPECT_DOUBLE_EQ(s.galutinis_vid(), 0.0);
}

// =============================================
// STREAM KONSTRUKTORIUS
// =============================================
TEST(StudentasTest, StreamKonstruktorius)
{
    std::stringstream ss("Jonas Jonaitis 8 7 9 6 10");
    Studentas s(ss);
    EXPECT_EQ(s.vardas(), "Jonas");
    EXPECT_EQ(s.pavarde(), "Jonaitis");
    EXPECT_GT(s.galutinis_med(), 0.0);
    EXPECT_GT(s.galutinis_vid(), 0.0);
}

// =============================================
// RULE OF FIVE
// =============================================
TEST(StudentasTest, CopyKonstruktorius)
{
    std::stringstream ss("Petras Petraitis 9 8 7 6 5");
    Studentas s1(ss);
    Studentas s2(s1);
    EXPECT_EQ(s2.vardas(), s1.vardas());
    EXPECT_DOUBLE_EQ(s2.galutinis_med(), s1.galutinis_med());
    // pakeitus s2, s1 turi likti nepakitęs
    std::stringstream ss2("Jonas Jonaitis 8 7 9 6 10");
    s2 = Studentas(ss2);
    EXPECT_EQ(s1.vardas(), "Petras");
}

TEST(StudentasTest, MoveKonstruktorius)
{
    std::stringstream ss("Antanas Antanaitis 5 6 7 8 9");
    Studentas s1(ss);
    double med = s1.galutinis_med();
    Studentas s2(std::move(s1));
    EXPECT_EQ(s2.vardas(), "Antanas");
    EXPECT_DOUBLE_EQ(s2.galutinis_med(), med);
    EXPECT_EQ(s1.vardas(), ""); // s1 tuščias po move
}

TEST(StudentasTest, CopyAssignment)
{
    std::stringstream ss1("Kazys Kazlauskas 7 8 9 10 6");
    std::stringstream ss2("Stasys Stasiulis 5 6 7 8 9");
    Studentas s1(ss1), s2(ss2);
    s2 = s1;
    EXPECT_EQ(s2.vardas(), s1.vardas());
    EXPECT_DOUBLE_EQ(s2.galutinis_med(), s1.galutinis_med());
    s2 = s2; // self-assignment
    EXPECT_EQ(s2.vardas(), "Kazys");
}

TEST(StudentasTest, MoveAssignment)
{
    std::stringstream ss1("Mantas Mantys 6 7 8 9 10");
    std::stringstream ss2("Rytis Rytas 4 5 6 7 8");
    Studentas s1(ss1), s2(ss2);
    double med = s1.galutinis_med();
    s2 = std::move(s1);
    EXPECT_EQ(s2.vardas(), "Mantas");
    EXPECT_DOUBLE_EQ(s2.galutinis_med(), med);
    EXPECT_EQ(s1.vardas(), ""); // s1 tuščias po move
}

TEST(StudentasTest, Destruktorius)
{
    EXPECT_NO_THROW({
        std::stringstream ss("Jonas Jonaitis 8 7 9 6 10");
        Studentas s(ss);
    });
}

// =============================================
// I/O OPERATORIAI
// =============================================
TEST(StudentasTest, IvestiesOperatorius)
{
    std::stringstream ss("Romas Romaitis 7 8 9 6 5");
    Studentas s;
    ss >> s;
    EXPECT_EQ(s.vardas(), "Romas");
    EXPECT_EQ(s.pavarde(), "Romaitis");
    EXPECT_GT(s.galutinis_med(), 0.0);
}

TEST(StudentasTest, IsvestiesOperatorius)
{
    std::stringstream ss("Linas Linaitis 8 7 6 9 10");
    Studentas s(ss);
    std::ostringstream os;
    os << s;
    EXPECT_FALSE(os.str().empty());
    EXPECT_NE(os.str().find("Linas"), std::string::npos);
    EXPECT_NE(os.str().find("Linaitis"), std::string::npos);
}

// =============================================
// ABSTRAKTI KLASE
// =============================================
TEST(ZmogusTest, Polimorfizmas)
{
    std::stringstream ss("Jonas Jonaitis 8 7 9 6 10");
    Studentas s(ss);
    Zmogus *z = &s;
    EXPECT_EQ(z->vardas(), "Jonas");
    std::ostringstream os;
    EXPECT_NO_THROW(z->print(os));
    EXPECT_FALSE(os.str().empty());
}