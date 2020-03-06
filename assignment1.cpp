#include<stdio.h>
#include<stdlib.h>
#include <iostream>
int main()
{
	//Data String
	char intro[] = "Hi there. Please enter how many values you would like to enter:  ";
	char getvalues[] = "Please enter the %d value: ";
	char positives[] = "There are %d positive values.\n";
	char negatives[] = "There are %d negative values.\n";
	char zero[] = "There are %d values equal to zero.\n";

	//Formatting
	char noofitems[] = "%d";
	char currno[] = "%d";										// format string for the scanf function*/
	char Colon[] = ": "; 											// format string for the scanf function*/

	int modno = 0; 												
	int number = 1; 												//Tracks the number of loops and also prints out the number of the module entered

	int count = 1; 													//Array counter
	int pos = 0; 													//Number of passes
	int neg = 0; 													
	int zer = 0;	
	int values[9999]; 													

	_asm {
		jmp start 											//This jumps to the start section

		start : 	
		mov ecx, 1 												//set ecx to 1 
			lea eax, values 											//sets eax as the value array
			mov ebx, eax 											//moves address of array into eax
			lea eax, intro 											//move intro into eax
			push ecx												//stacks ecx
			push eax												//stack eax
			call printf												//prints intro (welcome message)
			add esp, 4												//remove 4 bytes from the stack pointer
			pop ecx													
			push ecx												
			push eax												
			lea eax, noofitems											
			push eax												
			call scanf												
			add esp, 8												
			pop ecx
			jmp forloop												

			forloop :												
				//Prints and stacks
		push ecx												//stacks ecx
			lea eax, getvalues									//puts the getModuleMark string into eax
			push number												//pushes the number int into eax
			push eax												//stack eax
			call printf												//prints the number module number string and the number integer
			add esp, 8												//remove 8 bytes from the stack pointer
			pop ecx													//clears ecx to default

			lea eax, modno 										//loads modMark in eax
			push ecx												//stacks ecx
			push eax												//stacks eax
			lea eax, currno											//loads current number into eax
			push eax												//stacks eax
			call scanf												
			add esp, 8												
			pop ecx													

		mov eax, modno;										
		mov[ebx], eax;											
		add ebx, 4;												
		inc ecx													
			inc number												
			cmp ecx, noofitems												
			jle forloop												

			//After for Loop
			lea ebx, values
			mov count, 1


	valueChecker:
			cmp[ebx], 0								 //checks if the value is equal to zero
			jl negative								 //jumps if our value is less than zero
			je zerr									 // jumps if the value is zero
			jg positive								 //jump if it is positive
			jmp valueChecked						 //continue checking if value is invalid

			negative :							
				add neg, 1			//increment negative counter
				jmp valueChecked
			
				zerr :
			add zer, 1		//increment zero counter
				jmp valueChecked

			positive :		//increment positive counter
				add pos, 1
				jmp valueChecked 

			valueChecked :
			add ebx, 4 //next index of array
			add count, 1
			cmp count, 7
			je display
			jmp valueChecker //loop back

			display : 												//display the messages with values
		lea eax, positives											//loads passed into eax
			push pos												//pushes pass int into eax
			push eax												//stack eax
			call printf												//prints the passed string and the pass integer
			add esp, 8												//remove 8 bytes from the stack pointer

			lea eax, negatives											//loads failed into eax									
			push neg												//pushes fail int into eax
			push eax												//stack eax
			call printf												//prints the failed string and the fail integer
			add esp, 8												//remove 8 bytes from the stack pointer

			lea eax, zero											//loads passed into eax
			push zer												//pushes pass int into eax
			push eax												//stack eax
			call printf												//prints the passed string and the pass integer
			add esp, 8												//remove 8 bytes from the stack pointer

	}
	system("pause");
	return 0;
}
