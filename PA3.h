#ifndef PA3_H
#define PA3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct duration
{
	int minutes;
	int seconds;
} Duration;

typedef struct record
{
	char *artist;
	char *album_title;
	char *song_title;
	char *genre;
	Duration song_length;
	int times_played;
	int rating;
} Record;

typedef struct node
{
	Record data;
	struct node *pNext;
	struct node *pPrev;
} Node;

//displays the menu
void display_menu();
int get_option();
int determine_option();

//makes node for new data
Node * makeNode(Record newData);

//inserts new data at front
int insertAtFront(Node **pList, Record newData);

//reads all records from the csv file to linked list
void load(Node **pList);

//The “store” command writes the current records, in the dynamic doubly linked list, 
//to the musicPlayList.csv file. The store will completely overwrite the previous 
//contents in the file. 
void store(Node *pList);

//The “rate” command must allow the user to assign a value of 1 – 5 to a song; 
//1 is the lowest rating and 5 is the highest rating. The rating will replace the previous rating.
void rate(Node **pList);


//The “display” command prints records to the screen.This command must support two methods, one of which is selected by the user :
//1. Print all records.
//2. Print all records that match an artist.
void display(Node *pList);

//The “edit” command must allow the user to find a record in the list by artist.
//If there are multiple records with the same artist, then your program must 
//prompt the user which one to edit. The user may modify all of the attributes 
//in the record. 
void edit_playlist(Node *pList);

//The “insert” command must prompt the user for the details of a new record. 
//The prompt must request the artist name, album title, song title, genre, 
//song length, number of times played, and rating. The new record must be 
//inserted at the front of the list.
void insert(Node **pList);

//The “delete” command must prompt the user for a song title, 
//and remove the matching record from the list. If the song title 
//does not exist, then the list remains unchanged.
void delete(Node **pList);

/*
The “sort” command must prompt the user for 4 different methods to sort the records in the list. These include:
1. Sort based on artist (A-Z)
2. Sort based on album title (A-Z)
3. Sort based on rating (1-5)
4. Sort based on times played (largest-smallest)
Once a sort method is selected by the user, the sort must be performed on the records in the list. 
Consider using bubble sort, insertion sort, or selection sort.
*/
void sort(Node **pList);

/*
The “shuffle” command must provide a random order in which the songs are played. This command must not 
modify the links in the list.It must just specify the order in which songs are played, based on the 
position of the song in the list.For example, let’s say we have a list with 5 songs at positions 1 – 5 
in the list, shuffle must generate an order 1 – 5 in which the songs are played.An order 2, 5, 3, 1, 4 
would require that the second song in the list is played first, the fifth song in the list is played second, 
the third song in the list is played third, the first song in the list is played fourth, and the fourth song 
in the list is played fifth.The songs are accessed by traversing the list both forwards and backwards to satisfy 
the order.Hence, the need for a doubly linked list!
*/
void shuffle(Node *pList);

#endif