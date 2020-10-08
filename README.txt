DEVELOPER: Gabriel Johnson

#About
Within this folder is a Visual Studio Project that has completed the required specifications for the technical assingment.

The solution was written in c++ within Visual Studios. Along with this, unit test were written in Visual Studios to test various aspects of the solution.

#Usage
To run the solution either:
	-open .sln file in VS 2019 and debug the program.
	-under "PLEXSYS\x64\Debug" run the PLEXSYS Homework.exe file and it will open a command prompt to run the application.
	
Once running the solution, the user can now enter a mathematical equation.

The equation can use any of the following operations: ^, *, /, %, +, -.

The solution can handle decimal values, and braces.

The solution will solve the entered equation using standard order of operation.

Example entrys:
	-2+2
	-[55-1]
	-{2+3}
	-(2+4) * 89.4^.5
	-(23 % 3) -   45

#Output
The solution will then output a parenthesized result of the input (again it adds parenthesis based on standard order of operation), and it will output the resulting value of the entered mathematical equation.

#Error Checking
The solution has robust error checking to verify that the users entry is valid and proper in mathematical form.

If an error is caught, it will output a helpful error message aswell as where the solution detected the error.

#Exiting
After the solution outputs either a result or an error message, it will continue to ask the user for more mathematical equations to be inputted.

In order to close out of the program cleanly, type 'exit' or 'quit' in the input field.