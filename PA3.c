#include "PA3.h"

void display_menu()
{
	printf("Please choose from the option below: \n");
	printf("1. load \n");
	printf("2. store \n");
	printf("3. display \n");
	printf("4. insert \n");
	printf("5. delete \n");
	printf("6. edit \n");
	printf("7. sort \n");
	printf("8. rate \n");
	printf("9. play \n");
	printf("10. shuffle \n");
	printf("11. Exit. \n");

}

int get_option()
{
	int option = 0;

	scanf("%d", &option);

	
	if ((option < 1) || (option > 11))
	{
		printf("Invalid option!\n");
	}

	return option;
}

int determine_option()
{
	int option = 0;

	do
	{
		display_menu();
		option = get_option();
		system("cls");

		if ((option < 1) || (option > 11))
		{
			printf("Invalid option!\n");
		}
	} while ((option < 1) || (option > 11));

	return option;
}

Node * makeNode(Record newData)
{
	Node *pMem = NULL;

	pMem = (Node *)malloc(sizeof(Node));

	if (pMem != NULL)
	{
		pMem->pPrev = NULL;
		pMem->pNext = NULL;

		pMem->data.album_title = malloc(strlen(newData.album_title) * sizeof(char *) + 1);
		strcpy(pMem->data.album_title, newData.album_title);

		pMem->data.artist = malloc(strlen(newData.artist) * sizeof(char *) + 1);
		strcpy(pMem->data.artist, newData.artist);

		pMem->data.genre = malloc(strlen(newData.genre) * sizeof(char *) + 1);
		strcpy(pMem->data.genre, newData.genre);

		pMem->data.song_title = malloc(strlen(newData.song_title) * sizeof(char *) + 1);
		strcpy(pMem->data.song_title, newData.song_title);

		pMem->data.song_length = newData.song_length;
		pMem->data.times_played = newData.times_played;
		pMem->data.rating = newData.rating;

	}

	return pMem;

}

int insertAtFront(Node **pList, Record newData)
{
	Node *pMem = NULL;
	int success = 0;

	pMem = makeNode(newData);

	if (pMem != NULL)
	{
		pMem->pNext = *pList;
		(*pList)->pPrev = pMem;

		*pList = pMem;

		success = 1;
	}

	return success;

}

//reads all records from the csv file to linked list
void load(Node **pList)
{
	FILE *infile = fopen("musicPlayList.csv", "r");

	Record record1 = { "", "", "", "",{ -1, -1 }, -1, -1 };
	char line[256] = "";
	char *duration;
	char *temp;


	if (infile != NULL)
	{
		while (fgets(line, 256, infile) != NULL)
		{
			//read and assign all the data into struct
			if (line[0] == '\"')
			{
				temp = strtok(line, "\"");

			}
			else
			{
				temp = strtok(line, ",");
				
			}
//			record1.artist = (Node *)malloc(sizeof(char) * (strlen(temp)+ 1));
			
			record1.artist = temp;

			record1.album_title = strtok(NULL, ",");
//			record1.album_title = (Node *)malloc(sizeof(char) * (strlen(temp_album) + 1));
	//		strcpy(record1.album_title, temp_album);
			
			record1.song_title = strtok(NULL, ",");

			record1.genre = strtok(NULL, ",");
			record1.song_length.minutes = atoi(strtok(NULL, ":"));
			record1.song_length.seconds = atoi(strtok(NULL, ","));
			record1.times_played = atoi(strtok(NULL, ","));
			record1.rating = atoi(strtok(NULL, ","));
			
		
			insertAtFront(pList, record1); //add &* if error
		}
	}

	fclose(infile);
}

//The “store” command writes the current records, in the dynamic doubly linked list, 
//to the musicPlayList.csv file. The store will completely overwrite the previous 
//contents in the file.
void store(Node *pList)
{
	FILE *outfile = fopen("musicPlayList.csv", "w+");

	while (pList != NULL)
	{
		fprintf(outfile, "%s, %s, %s, %s, %d:%d, %d, %d\n", pList->data.artist, pList->data.album_title,
			pList->data.song_title, pList->data.genre, pList->data.song_length.minutes, pList->data.song_length.seconds,
			pList->data.times_played, pList->data.rating);

		//update the pointer
		pList = pList->pNext;
	}

	fclose(outfile);

}

//The “rate” command must allow the user to assign a value of 1 – 5 to a song; 
//1 is the lowest rating and 5 is the highest rating. The rating will replace the previous rating.
void rate(Node **pList)
{
	Node *pMem = *pList;
	int new_rating = -1;
	char song[20];

	printf("Enter a song you would like to change rating for:\n");
	scanf("%[^\n]s", &song); //gets() easier
	printf("Enter a new rating for a song:\n");
	scanf("%d", &new_rating);

	while (pMem != NULL)
	{
		if (strcmp(pMem->data.song_title, song) == 0) //if songs match
		{
			pMem->data.rating = new_rating;
		}
		pMem = pMem->pNext;
	}

}

//The “display” command prints records to the screen. This command must support two 
//methods, one of which is selected by the user :
//1. Print all records.
//2. Print all records that match an artist.
void display(Node *pList)
{
	int option = 0;
	char artist[20];

	printf("Choose from option below:\n");
	printf("1. Print all records:\n");
	printf("2. Print all records that match an artist:\n");
	scanf("%d", &option);

	if (option == 1)
	{
		if (pList != NULL)
		{
			printf("Info: %s, %s, %s, %s, %d:%d, %d, %d\n", pList->data.artist, pList->data.album_title,
				pList->data.song_title, pList->data.genre, pList->data.song_length.minutes, pList->data.song_length.seconds,
				pList->data.times_played, pList->data.rating);
			display(pList->pNext);
		}
	}
	else if (option == 2)
	{
		printf("Enter an artist:\n");
		scanf("%[^\n]s", &artist);

		while (pList != NULL)
		{
			if (strcmp(pList->data.artist, artist) == 0)
			{
				printf("Songs by %s:\n%s\n", artist, pList->data.song_title);
			}
			pList = pList->pNext;
		}
	}
	else
	{
		printf("Invalid option!\n");
	}
}

//The “edit” command must allow the user to find a record in the list by artist.
//If there are multiple records with the same artist, then your program must 
//prompt the user which one to edit. The user may modify all of the attributes 
//in the record. 
void edit_playlist(Node *pList)
{
	char artist[25] = "", name[25] = "", title[100] = "", album[50] = "",
		genre[20] = "";
	int option;
	int modify = 0, songs_length_in_minutes = 0, songs_length_in_seconds = 0,
		times_played = 0, rating = 0;

	printf("Would you like to edit any artist: type 1 for yes, 0 for no:\n");
	scanf("%d", &option);

	fflush(stdin);

	printf("\n");

	if (option == 1)
	{
		fflush(stdin);

		printf("Enter an artist you would like to modify:\n");
		scanf("%s", &artist);

//		system("PAUSE");

		printf("What attribute of %s do you want to modify?:\n", artist);
		printf("1. artist name\n2. album title\n3. song title\n4. genre\n5. song length\n6. times played\n7. rating\n");
		scanf("%d", &modify);
		/*
		1. artist;
		2. album_title;
		3. song_title;
		4. genre;
		5. song_length;
		6. times_played;
		7. rating;
		*/
		while (pList != NULL)
		{
			if (strcmp(pList->data.artist, artist) == 0)
			{
				switch (modify)
				{
				case 1: //change artist name
					printf("Enter a new name:\n");
					scanf("%[^\n]s", &name);

					pList->data.artist = name;

					break;
				case 2: //change album title
					printf("Enter a new album title:\n");
					scanf("%[^\n]s", &album);

					pList->data.album_title = album;

					break;
				case 3: //change song title
					printf("Enter a new song title:\n");
					gets(title);

					pList->data.song_title = title;

					break;
				case 4: //change genre
					printf("Enter a new genre:\n");
					gets(genre);

					pList->data.genre = genre;

					break;

				case 5: //change song length
					printf("Enter a new length in minutes:\n");
					scanf("%d", &songs_length_in_minutes);
					printf("in seconds:\n");
					scanf("%d", &songs_length_in_seconds);

					//pList->data.song_length = itoa()

					break;
				case 6: //change times played
					printf("Enter a new times played:\n");
					scanf("%d", &times_played);

					pList->data.times_played = times_played;

					break;
				case 7: //change rating

					rate(pList);

					break;
				}
			}
			pList = pList->pNext;
		}
	}
}

//The “insert” command must prompt the user for the details of a new record. 
//The prompt must request the artist name, album title, song title, genre,
//song length, number of times played, and rating. The new record must be 
//inserted at the front of the list.
void insert(Node **pList)
{
	Node *pMem = NULL;
	pMem = (Node *)malloc(sizeof(Node));
	pMem->pNext = *pList;
	pMem = *pList;
	
	//pMem = *pList;
	//*pList = (*pList)->pNext;
/*
	char artist_name[25] = "", album_title[50] = "", song_title[50] = "",
		genre[20] = "";
	int length_in_minutes = 0, length_in_seconds = 0, times_played = 0, rating = 0;
*/
	int length_in_minutes = 0, length_in_seconds = 0;

	printf("Enter a new artist:\n");
	gets(pMem->data.artist);
//	scanf("%[^\n]s", &artist_name); //can replace &artist_name with &pMem->data.artist
//	pMem->data.artist = artist_name;

	printf("Enter an album title:\n");
	gets(pMem->data.album_title);
//	gets(album_title);

	printf("Enter a song title:\n");
	gets(pMem->data.song_title);
//	gets(song_title);

	printf("Enter a genre:\n");
	gets(pMem->data.genre);
//	gets(song_title);

	printf("Enter length in minutes:\n");
	scanf("%d", &length_in_minutes);

	printf("Enter length in seconds:\n");
	scanf("%d", &length_in_seconds);

	//assign it to duration struct
	Duration length;
	length.minutes = length_in_minutes;
	length.seconds = length_in_seconds;


	printf("Enter how many times this song is played:\n");
	scanf("%d", &pMem->data.times_played);

	printf("Enter a rating for this song:\n");
	scanf("%d", &pMem->data.rating);

}

//The “delete” command must prompt the user for a song title, 
//and remove the matching record from the list. If the song title 
//does not exist, then the list remains unchanged.
void delete(Node **pList)
{
	Node *pMem = pList;
	char song[50] = "";

	printf("Enter a song you would like to delete:");
	scanf("%[^\n]s", &song);

	while (pMem != NULL)
	{
		if (strcmp(pMem->data.song_title, song) == 0)
		{
			pMem->pPrev->pNext = pMem->pNext; //deleting a node for doubly linked list
			pMem->pNext->pPrev = pMem->pPrev;

			free(pMem); //delete pMem
		}

	}
}

/*
The “sort” command must prompt the user for 4 different methods to sort the records in the list. These include:
1. Sort based on artist (A-Z)
2. Sort based on album title (A-Z)
3. Sort based on rating (1-5)
4. Sort based on times played (largest-smallest)
Once a sort method is selected by the user, the sort must be performed on the records in the list.
Consider using bubble sort, insertion sort, or selection sort.
*/
void sort(Node **pList)
{
	int option = 0, size = 9;
	int index = 0, passes = 1;

	Node *pMem = *pList;
	Node *temp = NULL;

	printf("Choose an option for sorting:\n");
	printf("1. Sort based on artist (A-Z)\n");
	printf("2. Sort based on album title (A-Z)\n");
	printf("3. Sort based on rating (1-5)\n");
	printf("4. Sort based on times played (largest-smallest)\n");
	scanf("%d", &option);

	
	if (option == 1) //based on artist (A-Z)
	{
		
		for (; passes < size - 1; ++passes)
		{
			for (index = 0; index < size - passes; ++index)
			{
				if (strcmp(pMem->data.artist, pMem->pNext->data.artist) > 0)
				{
					//swap
					temp = pMem->data.artist;
					pMem->data.artist = pMem->pNext->data.artist;
					pMem->pNext->data.artist = temp;
				}
			}
		}
		
	}
	else if (option == 2) //based on album title
	{
		for (; passes < size - 1; ++passes)
		{
			for (index = 0; index < size - passes; ++index)
			{
				if (strcmp(pMem->data.album_title, pMem->pNext->data.album_title) > 0)
				{
					//swap
					temp = pMem->data.album_title;
					pMem->data.album_title = pMem->pNext->data.album_title;
					pMem->pNext->data.album_title = temp;
				}
			}
		}
	}
	else if (option == 3) //based on rating
	{
		for (; passes < size - 1; ++passes)
		{
			for (index = 0; index < size - passes; ++index)
			{
				if (pMem->data.rating > pMem->pNext->data.rating)
				{
					//swap
					temp = pMem->data.rating;
					pMem->data.rating = pMem->pNext->data.rating;
					pMem->pNext->data.rating = temp;
				}
			}
		}
	}
	else if (option == 4) // based on times played (largest to smallest
	{
		
		for (; passes < size - 1; ++passes)
		{
			for (index = 0; index < size - passes; ++index)
			{
				if (pMem->data.times_played < pMem->pNext->data.times_played)
				{
					temp = pMem->data.times_played;
					pMem->data.times_played = pMem->pNext->data.times_played;
					pMem->pNext->data.times_played = temp;
				}
			}
		}
	}
	else
	{
		printf("Wrong input!");
	}
	
}

void shuffle(Node *pList)
{
	Node *pMem = pList;
	Node *pHead = pList;

	int size = 0;
	
	srand((unsigned int) time(NULL));

	while (pHead != NULL) //counts the size
	{
		pHead = pHead->pNext;
		size++;
	}

	int random_num = rand() % size;

	for (int i = 0; i < size; i++) //assigns each songs to i from 1 to size
	{
		pMem->data.song_title = i;
		if (random_num = i)
		{
			printf("Song: %s is playing!\n", pMem->data.song_title);
		}
	}

}
