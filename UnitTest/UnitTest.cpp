#include "pch.h"
#include "CppUnitTest.h"
#include "../PLEXSYS Homework/MathFormat.h"
#include "../PLEXSYS Homework/MathFormat.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(ValidCharacterTest)
	{
	public:
		
		TEST_METHOD(CorrectTest1)
		{
			std::string mathInput1 = "1/2*3+{4+5}+6 + [7-8]+(9.+10)";
			MathFormat MF;

			Assert::AreEqual(true, MF.errorCheck(mathInput1));

		}

		TEST_METHOD(CorrectTest2)
		{
			std::string mathInput1 = "(2+4) * 4";
			MathFormat MF;

			Assert::AreEqual(true, MF.errorCheck(mathInput1));

		}

		TEST_METHOD(CorrectTest3)
		{
			std::string mathInput1 = "2             +            2";
			MathFormat MF;

			Assert::AreEqual(true, MF.errorCheck(mathInput1));

		}

		TEST_METHOD(IncorrectTest1)
		{
			std::string mathInput2 = "1/2*3+{4+5}+6j + [7-8]+(9.+10)";
			MathFormat MF;

			Assert::AreEqual(false, MF.errorCheck(mathInput2));

		}

		TEST_METHOD(IncorrectTest2)
		{
			std::string mathInput2 = ")4+3(";
			MathFormat MF;

			Assert::AreEqual(false, MF.errorCheck(mathInput2));

		}
	};
}
