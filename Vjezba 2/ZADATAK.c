/*Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
A. dinamièki dodaje novi element na poèetak liste,
B. ispisuje listu,
C. dinamièki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

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
int findPerson(Person* p, char* lastname);
int deletePerson(Person* p, char* firstname, char* lastname, int year);


int main() {

	Person Head;
	Head.next = NULL;

	addBegining(&Head, "Mare", "Maric", 2003);	printList(&Head);
	addBegining(&Head, "Lovre", "Lovric", 2002); printList(&Head);
	addBegining(&Head, "Mate", "Matic", 1999);
	addBegining(&Head, "Ana", "Anic", 2001); printList(&Head);
	addEnd(&Head, "Jure", "Juric", 2001); 
	addEnd(&Head, "Pere", "Peric", 2004); printList(&Head);
	findPerson(&Head, "Matic");
	findPerson(&Head, "Horvat");
	deletePerson(&Head, "Mare", "Maric", 2003); printList(&Head);
	

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

int findPerson(Person* p, char* lastname) {
	Person* curr = p->next; //preskacen Head jer nema "sadrzaja" u njemu za usporedbu s unesenim prezimenom
	while(curr!=NULL){
		if (strcmp(curr->surname, lastname) == 0) { //usporedba prezimena "trenutnog" clana i unesenog prezimena
			printf("Pronadena osoba je:  %s %s %d \n", curr->name, curr->surname, curr->birth_year);
			printf("---------------------------------\n");
			 return EXIT_SUCCESS;
		}
			curr = curr->next; //pomicanje na iduceg
		
	}

	//ako ne pronade 
	printf("Nema osobe sa trazenim prezimenom!\n");
	printf("---------------------------------\n");
	return EXIT_FAILURE;
	
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
