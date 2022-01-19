/*****************************************************************************************************
Programmer's name: Diwash Biswa
Class: CptS 122 Spring 2018
Programming Assignment: PA3 Digital Music Manager & Doubly Linked Lists – Part II
Date: 2/7/18
Description: can be found at this link: http://eecs.wsu.edu/~aofallon/cpts122/progassignments/PA3.htm

Comments: Hey Ryan, I have made some changes to my code according to your comment in Osble. Some part
of the program still crashes when I run. However, can you grade for the things I've included here? Thanks
so much.
Some changes include:
	* changes in insert function
	* changes in delete function
	* sort function done
	* shuffle function done
*****************************************************************************************************/

#include "PA3.h"

int main(int argc, char *argv[])
{
	Node *pList = (Node *)malloc(sizeof(Node));

	int option = 0; 
	
	do
	{
		option = determine_option();
		
		switch (option)
		{
		case 1: //load

			load(&pList);

			printf("Records loaded to the list!\n\n");

			break;

		case 2: //store

			store(pList);

			break;
		case 3: //display

			display(pList);

			break;
		case 4: //insert

			insert(&pList);

			break;

		case 5: //delete

			delete(&pList);

			break;

		case 6: //edit
			edit_playlist(&pList);

			break;

		case 7: //sort

			sort(&pList);

			break;

		case 8: //rate
			rate(&pList);

			break;

		case 9: //play

			break;

		case 10: //shuffle
			shuffle(pList);

			break;

		case 11: //exit
			printf("Application ended...\n\n");

			break;

		} 
	} while (option != 11);

	return 0;
}