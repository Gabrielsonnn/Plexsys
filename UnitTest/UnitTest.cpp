#include "pch.h"
#include "CppUnitTest.h"
#include "../PLEXSYS Homework/MathFormat.h"
#include "../PLEXSYS Homework/MathFormat.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(ValidMathInputTest)
	{
	public:
		MathFormat MF;
		TEST_METHOD(CorrectTest1)
		{
			std::string mathInput1 = "1/2*3+{4+5}-([{6}]) + [7^8]+(9.05+10)";

			Assert::AreEqual(1, MF.errorCheck(mathInput1));

		}

		TEST_METHOD(CorrectTest2)
		{
			std::string mathInput1 = "(2+4) * 4";

			Assert::AreEqual(1, MF.errorCheck(mathInput1));

		}

		TEST_METHOD(CorrectTest3)
		{
			std::string mathInput1 = "2             +            2";

			Assert::AreEqual(1, MF.errorCheck(mathInput1));

		}

		TEST_METHOD(CorrectTest4)
		{
			std::string mathInput1 = "({[8^7]})";

			Assert::AreEqual(1, MF.errorCheck(mathInput1));

		}

		TEST_METHOD(CorrectTest5)
		{
			//assume mulplication, so this is correct
			std::string mathInput2 = "4+4(4+4)";

			Assert::AreEqual(1, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(CorrectTest6)
		{
			std::string mathInput2 = "4 + (2-3)";

			Assert::AreEqual(1, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(CorrectTest7)
		{
			std::string mathInput2 = "(7*3) / 2";

			Assert::AreEqual(1, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectCharTest1)
		{
			std::string mathInput2 = "1/2*3+{4+5}+6j + [7-8]+(9.+10)";

			Assert::AreEqual(-1, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectCharTest2)
		{
			std::string mathInput2 = "a";

			Assert::AreEqual(-1, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectParTest1)
		{
			std::string mathInput2 = ")4+3(";

			Assert::AreEqual(-2, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectParTest2)
		{
			std::string mathInput2 = "(5+5-(4-4)";

			Assert::AreEqual(-2, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectParTest3)
		{
			std::string mathInput2 = "(5+5-](4-4)";

			Assert::AreEqual(-2, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectParTest4)
		{
			std::string mathInput2 = "[5+5/()](4^4)";

			Assert::AreEqual(-2, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectParTest5)
		{
			std::string mathInput2 = "{[()]}";

			Assert::AreEqual(-2, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectTest1)
		{
			std::string mathInput2 = "(4+4)+4 +";

			Assert::AreEqual(-3, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectTest2)
		{
			std::string mathInput2 = "4++4";

			Assert::AreEqual(-3, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectTest3)
		{
			std::string mathInput2 = "4+4 4+4";

			Assert::AreEqual(false, MF.removeSpaces(&mathInput2));

		}
		TEST_METHOD(IncorrectTest4)
		{
			std::string mathInput2 = "(4+)";

			Assert::AreEqual(-3, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectTest5)
		{
			std::string mathInput2 = "(+4+8)";

			Assert::AreEqual(-3, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectTest6)
		{
			std::string mathInput2 = "    +   ";

			Assert::AreEqual(-3, MF.errorCheck(mathInput2));

		}

		

		
	};

	TEST_CLASS(RemoveSpaceTest)
	{
	public:
		MathFormat MF;

		TEST_METHOD(RemoveSpace1)
		{
			std::string mathInput1 = "4 + 4";

			MF.removeSpaces(&mathInput1);

			Assert::AreEqual((string)"4+4", mathInput1);
		}

		TEST_METHOD(RemoveSpace2)
		{
			std::string mathInput1 = "           4                +                  4            ";

			MF.removeSpaces(&mathInput1);

			Assert::AreEqual((string)"4+4", mathInput1);
		}

		TEST_METHOD(RemoveSpace3)
		{
			std::string mathInput1 = "1 / 2 * 3 + { 4 +    5 } + 6  +  [ 7 -    8 ] + (9.25   + 10)";

			MF.removeSpaces(&mathInput1);

			Assert::AreEqual((string)"1/2*3+{4+5}+6+[7-8]+(9.25+10)", mathInput1);
		}

		TEST_METHOD(RemoveSpaceError1)
		{
			std::string mathInput1 = "4 4";

			Assert::AreEqual(false, MF.removeSpaces(&mathInput1));
		}

		TEST_METHOD(RemoveSpaceError2)
		{
			std::string mathInput1 = "4324 4450";

			Assert::AreEqual(false, MF.removeSpaces(&mathInput1));
		}

		TEST_METHOD(RemoveSpaceError3)
		{
			std::string mathInput1 = "    4 - 4     10    + 7";

			Assert::AreEqual(false, MF.removeSpaces(&mathInput1));
		}

		TEST_METHOD(RemoveSpaceError4)
		{
			std::string mathInput1 = "9. 51 + 5";

			Assert::AreEqual(false, MF.removeSpaces(&mathInput1));
		}

	};

	TEST_CLASS(AddParenthesis)
	{
	public:
		MathFormat MF;

		TEST_METHOD(AddPar1)
		{
			std::string mathInput1 = "4+4";

			Assert::AreEqual((string)"(4+4)", MF.parenthesize(mathInput1));
		}

		TEST_METHOD(AddPar2)
		{
			std::string mathInput1 = "4837624+412312";

			Assert::AreEqual((string)"(4837624+412312)", MF.parenthesize(mathInput1));
		}

		TEST_METHOD(AddPar3)
		{
			std::string mathInput1 = "(44.23+867)*[23]^9.567";

			Assert::AreEqual((string)"(((44.23+867))*([23]^9.567))", MF.parenthesize(mathInput1));
		}

		TEST_METHOD(AddPar4)
		{
			std::string mathInput1 = "{[(4)]}+2";

			Assert::AreEqual((string)"({[(4)]}+2)", MF.parenthesize(mathInput1));
		}

		TEST_METHOD(AddPar5)
		{
			std::string mathInput1 = "4+(2)";

			Assert::AreEqual((string)"(4+(2))", MF.parenthesize(mathInput1));
		}

		TEST_METHOD(AddPar6)
		{
			std::string mathInput1 = "4+5*3-2";

			Assert::AreEqual((string)"((4+(5*3))-2)", MF.parenthesize(mathInput1));
		}
	};
}
