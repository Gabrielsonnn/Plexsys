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
			std::string mathInput1 = "1/2*3+{4+5}+6 + [7-8]+(9.+10)";

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
			std::string mathInput1 = "({[8+5]})";

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

	};
}
