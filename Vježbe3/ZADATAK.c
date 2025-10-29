/*Prethodnom zadatku dodati funkcije:
A. dinamièki dodaje novi element iza odreðenog elementa,
B. dinamièki dodaje novi element ispred odreðenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. èita listu iz datoteke.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN 32

struct _person;
typedef struct _person* PersonP;
typedef struct _person {
	char name[MAX_NAME_LEN];
	char surname[MAX_NAME_LEN];
	int birth_year;
	PersonP next;
}Person;

int addBegining(Person* p, char* firstname, char* lastname, int year);
int printList(Person* p);
int addEnd(Person* p, char* firstname, char* lastname, int year);
Person* findPerson(Person* p, char* lastname);
int deletePerson(Person* p, char* firstname, char* lastname, int year);
//-------------FUNKCIJE ZA OVAJ ZADATAK-------------------
int addAfter(Person* p, char* lastname, char* firstname1, char* lastname1, int year1);
int addBefore(Person* p, char* lastname, char* firstname1, char* lastname1, int year1);
int sortList(Person* p);
int writeFile(Person* p);
int readFile(Person* p);

int main() {

	Person Head;
	Head.next = NULL;

	addBegining(&Head, "Mare", "Maric", 2003);	printList(&Head);
	addBegining(&Head, "Lovre", "Lovric", 2002); printList(&Head);
	addBegining(&Head, "Mate", "Matic", 1999);
	addBegining(&Head, "Ana", "Anic", 2001); printList(&Head);
	addEnd(&Head, "Jure", "Juric", 2001);
	addEnd(&Head, "Pere", "Peric", 2004); printList(&Head);
	deletePerson(&Head, "Mare", "Maric", 2003); printList(&Head);
	addAfter(&Head, "Lovric", "Ivan", "Ivic", 2002); printList(&Head);
	addBefore(&Head, "Anic", "Hrvoje", "Horvat", 2001); printList(&Head);
	sortList(&Head); printList(&Head);
	writeFile(&Head);
	readFile(&Head);


	return 0;
}

int addBegining(Person* p, char* firstname, char* lastname, int year) {

	//alokacija memorije za novi clan liste
	Person* new_person = malloc(sizeof(Person));
	if (new_person == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	//sadrzaj clana liste
	strcpy(new_person->name, firstname);
	strcpy(new_person->surname, lastname);
	new_person->birth_year = year;

	//postavljanje pokazivaca
	new_person->next = p->next; //novo dodani cvor pokazuje na cvor na kojeg pokazuje Head
	p->next = new_person;		//Head pokazuje na novo dodani cvor 

	return EXIT_SUCCESS;
}

int printList(Person* p) {
	Person* curr = p->next; //pomocni pokazivac na prvi clan liste iza Heada
	while (curr != NULL) {
		printf("%s %s %d\n", curr->name, curr->surname, curr->birth_year);
		curr = curr->next; //pomicanje na iduceg clana
	}
	printf("--------------------------\n");

	return EXIT_SUCCESS;
}

int addEnd(Person* p, char* firstname, char* lastname, int year) {

	//alokacija memorije za novi clan liste
	Person* new_person = malloc(sizeof(Person));
	if (new_person == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	//sadrzaj clana liste
	strcpy(new_person->name, firstname);
	strcpy(new_person->surname, lastname);
	new_person->birth_year = year;

	//postavljanje pokazivaca
	Person* curr = p;
	while (curr->next != NULL) {  //petlja kojon "trazin" zadnji clan liste (onaj koji pokazuje na NULL)
		curr = curr->next;
	}
	curr->next = new_person; //taj koji je bija zadnji sad pokazuje na novi clan
	new_person->next = NULL; //novi clan pokazuje na NULL, tj. zadnji je u listi

	return EXIT_SUCCESS;
}

Person* findPerson(Person* p, char* lastname) { //prepravljena funkcija tako da vraca pokazivac umjesto da ispisuje pronadeni clan
	Person* curr = p->next; //preskacen Head jer nema "sadrzaja" u njemu za usporedbu s unesenim prezimenom
	while (curr != NULL) {
		if (strcmp(curr->surname, lastname) == 0) { //usporedba prezimena "trenutnog" clana i unesenog prezimena
			
			return curr;
		}
		curr = curr->next; //pomicanje na iduceg

	}

	//ako nije pronaden
	return NULL;

}

int deletePerson(Person* p, char* firstname, char* lastname, int year) {
	Person* prev = p;
	Person* curr = p->next;

	while (curr != NULL) {
		if (strcmp(curr->name, firstname) == 0 && strcmp(curr->surname, lastname) == 0 && curr->birth_year == year) {

			prev->next = curr->next; //pomicanje pokazivaca
			free(curr);

			return EXIT_SUCCESS;
		}
		prev = curr;
		curr = curr->next;
	}
	printf("Ne postoji ta osoba pa se ne moze obrisati!\n");
	return EXIT_FAILURE;
}
//-------------FUNKCIJE ZA OVAJ ZADATAK-------------------

int addAfter(Person* p, char* lastname, char* firstname1, char* lastname1, int year1) {
	//pronalazak clana iza kojeg dodajem
	Person* found = findPerson(p, lastname);
	if (found == NULL) {
		printf("Student nije pronaden!\n");
		return EXIT_FAILURE;
	}
	
	//alokacija memorije za novi clan
	Person* new_person = malloc(sizeof(Person));
	if (new_person == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	//sadrzaj novog elementa u listi
	strcpy(new_person->name, firstname1);
	strcpy(new_person->surname, lastname1);
	new_person->birth_year = year1;

	//umetanje u listu
	new_person->next = found->next; 
	found->next = new_person;

	return EXIT_SUCCESS;
}

int addBefore(Person* p, char* lastname, char* firstname1, char* lastname1, int year1) {
	//pronalazak clana ispred kojeg dodajem
	Person* prev = p;
	Person* curr = p->next;
	while (curr != NULL && strcmp(curr->surname, lastname) != 0) { //petlja koja pomice pokazivace na sljedeceg clana ako ne nade trazenoga
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL) { //ako curr dode do kraja znaci da nije pronaden odgovarajuci clan
		printf("Student nije pronaden!\n");
		return EXIT_FAILURE;
	}

	//alokacija memorije za novi clan
	Person* new_person = malloc(sizeof(Person));
	if (new_person == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	//sadrzaj novog elementa u listi
	strcpy(new_person->name, firstname1);
	strcpy(new_person->surname, lastname1);
	new_person->birth_year = year1;

	//umetanje u listu
	prev->next = new_person;
	new_person->next = curr;

	return EXIT_SUCCESS;
}

int sortList(Person* p)
{
	Person* prev = NULL;
	Person* curr = NULL;
	Person* temp = NULL;
	Person* sorted = NULL;

	// vanjska petlja - ide dok ne doðemo do poèetka sortiranog dijela
	while (p->next != sorted)
	{
		prev = p;
		curr = p->next;

		// prolaz po listi do sortirane granice
		while (curr->next != sorted)
		{
			if (strcmp(curr->surname, curr->next->surname) > 0)
			{
				// zamjena susjednih èvorova
				temp = curr->next;
				curr->next = temp->next;
				temp->next = curr;
				prev->next = temp;

				// nakon zamjene prev pokazuje na èvor temp (koji je sada ispred curr)
				prev = temp;
			}
			else
			{
				// nema zamjene — samo pomakni pokazivaèe
				prev = curr;
				curr = curr->next;
			}
		}

		// zadnji element u ovom prolazu je sortiran
		sorted = curr;
	}

	return EXIT_SUCCESS;
}

int writeFile(Person* p) {

	FILE* fp = fopen("datoteka.txt", "w");
	if (fp == NULL) {
		printf("Datoteka nije otvorena!\n");
		return EXIT_FAILURE;
	}
	Person* curr = p->next;
	while (curr != NULL) {
		fprintf(fp, "%s %s %d\n", curr->name, curr->surname, curr->birth_year);
		curr = curr->next;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int readFile(Person* p) {

	FILE* fp = fopen("datoteka.txt", "r");
	if (fp == NULL) {
		printf("Datoteka nije otovrena!\n");
		return EXIT_FAILURE;
	}
	char buffer[100];
	printf("Procitano iz datoteke: \n");
	while (fgets(buffer, 255, fp) != NULL) {
		printf("%s", buffer);
	}

	return EXIT_SUCCESS;
}
