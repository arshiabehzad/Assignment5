# Assignment5

Arshia Behzad
2320643
behzad@chapman.edu
CPSC 350
Assignment 5

SOURCE FILES: 
TreeNode.h, BST.h, Database.h, Faculty.h, Student.h, Action.h
Database.cpp, Faculty.cpp, Student.cpp, main.cpp, Action.cpp

TEXT FILE FORMATTING:
studentTable.txt must format entries like this:
StudentID:Name:Level:Major:GPA:AdvisorID

facultytable.txt must format entries like this:
facultyID:Name:Level:Department:AdviseeID1,AdviseeID2,AdviseeID3, 
NOTE: MUST USE COMMA AFTER LAST ENTRY

I included a sample facultyTable.txt and studentTable.txt so you can see an example

ERRORS:
If you see "WARNING: " program will continue but tell user about a conflict
If you see "ERROR: " program will ask for new input, and redo loop

PROGRAM NOTES:
The program will allow you to add advisees and advisorIDs that do not exist, but
will give you warnings throughout. This is to allow entries of a student and then 
a faculty without error. However the program will always try to mantain referential 
integrity when possible. For example, if student with advisorID is added, and a faculty
member with that ID exists, the faculty member will have the student added to the advisee
list. *

*I decided against randomly assigning students without an advisor a random advisor, to 
allow more control on the user end. If a student has an advisor that was deleted. It will
show that the student does not have an advisor, however it will not reasign the student
to a new advisor, the user must do that 

SERILIZATION FILE:
At the end of the program the student tree is searlized to searlizedStudentFile.txt
At the end of the program the faculty tree is searlized to facultyStudentFile.txt

REFRENCES:
Some refrences are listed in the comments
Joely helped me with some parts of the template BST class
Stepehen helped me a bit with understanding serilization
I got the seralization code from https://www.geeksforgeeks.org/serialize-deserialize-binary-tree/
ostringstream code I found on c++refrence and stackoverflow
StackOverflow was used for debugging but unless refrenced in code
none of it was coppied 

FINAL NOTE:
this took me wayyyyyyyyyyyyyyyyyyyyyy too long 