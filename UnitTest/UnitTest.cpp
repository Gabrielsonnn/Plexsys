//Developer: Gabriel Johnson

#include "pch.h"
#include "CppUnitTest.h"
#include "../PLEXSYS Homework/MathFormat.h"
#include "../PLEXSYS Homework/MathFormat.cpp"
#include "../PLEXSYS Homework/MathTree.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <crtdbg.h>
struct CrtCheckMemory
{
	_CrtMemState state1;
	_CrtMemState state2;
	_CrtMemState state3;
	CrtCheckMemory()
	{
		_CrtMemCheckpoint(&state1);
	}
	~CrtCheckMemory()
	{
		_CrtMemCheckpoint(&state2);
		// else just do this to dump the leaked blocks to stdout.
		if (_CrtMemDifference(&state3, &state1, &state2))
			_CrtMemDumpStatistics(&state3);
	}
};

namespace UnitTest
{
	TEST_CLASS(MathTest) {
	public:
		
		CrtCheckMemory check;
		MathFormat MF;
		MathTree<double> MT;

		TEST_METHOD(MathIntegerTest1)
		{
			string temp = MF.parenthesize("4+4");

			Assert::AreEqual(8, (int)MT.calculate(temp));
		}

		TEST_METHOD(MathIntegerTest2)
		{
			string temp = MF.parenthesize("2-2");

			Assert::AreEqual(0, (int)MT.calculate(temp));
		}

		TEST_METHOD(MathIntegerTest3)
		{
			string temp = MF.parenthesize("5*10");

			Assert::AreEqual(50, (int)MT.calculate(temp));
		}

		TEST_METHOD(MathIntegerTest4)
		{
			string temp = MF.parenthesize("40/2");

			Assert::AreEqual(20, (int)MT.calculate(temp));
		}

		TEST_METHOD(MathIntegerTest5)
		{
			string temp = MF.parenthesize("2^4");

			Assert::AreEqual(16, (int)MT.calculate(temp));
		}

		TEST_METHOD(MathIntegerTest6)
		{
			string temp = MF.parenthesize("11 % 3");

			Assert::AreEqual(2, (int)MT.calculate(temp));
		}

		TEST_METHOD(MultiplicationTest1)
		{
			string temp = MF.parenthesize("(4)(5)");

			Assert::AreEqual(20, (int)MT.calculate(temp));
		}

		TEST_METHOD(MultiplicationTest2)
		{
			string temp = MF.parenthesize("(4)5");

			Assert::AreEqual(20, (int)MT.calculate(temp));
		}

		TEST_METHOD(MultiplicationTest3)
		{
			string temp = MF.parenthesize("4(5)");

			Assert::AreEqual(20, (int)MT.calculate(temp));
		}

		TEST_METHOD(MultiplicationTest4)
		{
			string temp = MF.parenthesize("4+(10(20))");

			Assert::AreEqual(204, (int)MT.calculate(temp));
		}

		TEST_METHOD(MathComplexIntegerTest1)
		{
			string temp = MF.parenthesize("2+5-4*10");

			Assert::AreEqual(-33, (int)MT.calculate(temp));
		}

		TEST_METHOD(MathComplexIntegerTest2)
		{
			string temp = MF.parenthesize("40*78-32+(90)*[{50}]");

			Assert::AreEqual(-1412, (int)MT.calculate(temp));
		}

		TEST_METHOD(MathDoubleTest1)
		{
			string temp = MF.parenthesize("5.05515+2.69");

			Assert::AreEqual(7.74515, round(MT.calculate(temp) * 100000) / 100000);
		}

		TEST_METHOD(MathDoubleTest2)
		{
			string temp = MF.parenthesize("2.5+.5");

			Assert::AreEqual(3.0, round(MT.calculate(temp) * 10) / 10);
		}

		TEST_METHOD(MathStressTest) 
		{

			MathTree<double> MT2;
			string temp = MF.parenthesize("(2+2)+2+2+2+(2+2)+2+2");

			for (int i = 0; i < 1000; i++) {
				if (18 != MT2.calculate(temp))
					break;
				MT2.clear();
			}

			Assert::AreEqual(1,1);
		}

	};

	TEST_CLASS(ValidMathInputTest)
	{
	public:
		MathFormat MF;
		int charLocation = 0;

		TEST_METHOD(CorrectTest1)
		{
			std::string mathInput1 = "1/2*3+{4+5}-([{6}]) + [7^8]+(9.05+10)";

			Assert::AreEqual(1, MF.errorCheck(mathInput1, &charLocation));

		}

		TEST_METHOD(CorrectTest2)
		{
			std::string mathInput1 = "(2+4) * 4";

			Assert::AreEqual(1, MF.errorCheck(mathInput1, &charLocation));

		}

		TEST_METHOD(CorrectTest3)
		{
			std::string mathInput1 = "2             +            2";

			Assert::AreEqual(1, MF.errorCheck(mathInput1, &charLocation));

		}

		TEST_METHOD(CorrectTest4)
		{
			std::string mathInput1 = "({[8^7]})";

			Assert::AreEqual(1, MF.errorCheck(mathInput1, &charLocation));

		}

		TEST_METHOD(CorrectTest5)
		{
			//assume mulplication, so this is correct
			std::string mathInput2 = "4+4(4+4)";

			Assert::AreEqual(1, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(CorrectTest6)
		{
			std::string mathInput2 = "4 + (2-3)";

			Assert::AreEqual(1, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(CorrectTest7)
		{
			std::string mathInput2 = "(7*3) / 2";

			Assert::AreEqual(1, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectCharTest1)
		{
			std::string mathInput2 = "1/2*3+{4+5}+6j + [7-8]+(9.+10)";

			Assert::AreEqual(-1, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectCharTest2)
		{
			std::string mathInput2 = "a";

			Assert::AreEqual(-1, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectParTest1)
		{
			std::string mathInput2 = ")4+3(";

			Assert::AreEqual(-2, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectParTest2)
		{
			std::string mathInput2 = "(5+5-(4-4)";

			Assert::AreEqual(-2, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectParTest3)
		{
			std::string mathInput2 = "(5+5-](4-4)";

			Assert::AreEqual(-2, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectParTest4)
		{
			std::string mathInput2 = "[5+5/()](4^4)";

			Assert::AreEqual(-2, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectParTest5)
		{
			std::string mathInput2 = "{[()]}";

			Assert::AreEqual(-2, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectTest1)
		{
			std::string mathInput2 = "(4+4)+4 +";

			Assert::AreEqual(-3, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectTest2)
		{
			std::string mathInput2 = "4++4";

			Assert::AreEqual(-3, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectTest3)
		{
			std::string mathInput2 = "4+4 4+4";

			Assert::AreEqual(-4, MF.removeSpaces(&mathInput2, &charLocation));

		}
		TEST_METHOD(IncorrectTest4)
		{
			std::string mathInput2 = "(4+)";

			Assert::AreEqual(-3, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectTest5)
		{
			std::string mathInput2 = "(+4+8)";

			Assert::AreEqual(-3, MF.errorCheck(mathInput2, &charLocation));

		}

		TEST_METHOD(IncorrectTest6)
		{
			std::string mathInput2 = "    +   ";

			Assert::AreEqual(-3, MF.errorCheck(mathInput2, &charLocation));

		}
	};

	TEST_CLASS(RemoveSpaceTest)
	{
	public:
		MathFormat MF;
		int charLocation = 0;

		TEST_METHOD(RemoveSpace1)
		{
			std::string mathInput1 = "4 + 4";

			MF.removeSpaces(&mathInput1, &charLocation);

			Assert::AreEqual((string)"4+4", mathInput1);
		}

		TEST_METHOD(RemoveSpace2)
		{
			std::string mathInput1 = "           4                +                  4            ";

			MF.removeSpaces(&mathInput1, &charLocation);

			Assert::AreEqual((string)"4+4", mathInput1);
		}

		TEST_METHOD(RemoveSpace3)
		{
			std::string mathInput1 = "1 / 2 * 3 + { 4 +    5 } + 6  +  [ 7 -    8 ] + (9.25   + 10)";

			MF.removeSpaces(&mathInput1, &charLocation);

			Assert::AreEqual((string)"1/2*3+{4+5}+6+[7-8]+(9.25+10)", mathInput1);
		}

		TEST_METHOD(RemoveSpaceError1)
		{
			std::string mathInput1 = "4 4";

			Assert::AreEqual(-4, MF.removeSpaces(&mathInput1, &charLocation));
		}

		TEST_METHOD(RemoveSpaceError2)
		{
			std::string mathInput1 = "4324 4450";

			Assert::AreEqual(-4, MF.removeSpaces(&mathInput1, &charLocation));
		}

		TEST_METHOD(RemoveSpaceError3)
		{
			std::string mathInput1 = "    4 - 4     10    + 7";

			Assert::AreEqual(-4, MF.removeSpaces(&mathInput1, &charLocation));
		}

		TEST_METHOD(RemoveSpaceError4)
		{
			std::string mathInput1 = "9. 51 + 5";

			Assert::AreEqual(-4, MF.removeSpaces(&mathInput1, &charLocation));
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
