#include<stdio.h>
#include<stdlib.h>
#include <iostream>
int main()
{
	//Data String
	char intro[] = "Hi there. This assembly program will count how many values are positive, negative and equal to zero.\n Please enter how many values you would like to enter:  ";
	char getvalues[] = "Please enter the value: ";
	char positives[] = "There are %d positive values.\n";
	char negatives[] = "There are %d negative values.\n";
	char zero[] = "There are %d values equal to zero.\n";

	//Formatting
	char format[] = "%d";
	int num;																																
	int pos = 0; 													
	int neg = 0; 													
	int zer = 0;
	int input;

	_asm {
		/*Print an introduction message.*/
		lea eax, intro
		push eax
		call printf
		add esp, 4
		/*Grab first user input needed, how many values are going to be inserted.*/
		lea eax, input
		push eax
		lea eax, format
		push eax
		call scanf
		add esp, 8
		/*Move the input into a reg and start the loop*/
		mov ecx, input
			jmp loop1											
			loop1:
			push ecx;
			lea eax, getvalues
				push eax
				call printf
				add esp, 4
				lea eax, num
				/*Grab number and increment the specific counter*/
				push eax
				lea eax, format
				push eax
				call scanf
				add esp, 8
				mov eax, num
				cmp eax, 0
				jl negative
				je zerr
				jg positive
				/*we have to clear the ecx before looping again*/
		rotate : 
			pop ecx
			loop loop1
			jmp display
	
		negative :
			add neg, 1			//increment negative counter
			jmp rotate
			
				zerr :
			add zer, 1		//increment zero counter
				jmp rotate

			positive :		//increment positive counter
				add pos, 1
				jmp rotate 

			je display
	/* Display the messages with values*/
		display : 												
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
