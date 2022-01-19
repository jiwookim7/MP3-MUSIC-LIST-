/*****************************************************************************************************
Programmer's name: Jiwoo Kim
Class: CptS 122 Spring 2021
Programming Assignment: PA3 Digital Music Manager & Singly Linked Lists � Part I Date: 2/7/21
Description: can be found at this link: http://eecs.wsu.edu/~aofallon/cpts122/progassignments/PA3.htm

Comments:
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