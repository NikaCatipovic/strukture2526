/*1. Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 32
#define MAX_SCORE 30

struct _student;
typedef struct _student* StudentP;
typedef struct _student {
	char name[MAX_LEN];
	char surname[MAX_LEN];
	int score;
	float rel_score;
	StudentP next;
}Student;

int noStudents(const char* dat);
void loadStudents(const char* dat, Student* p);
void appendStudent(Student* p, char* firstname, char* lastname, int test_score);
void printList(Student* p);
void freeList(Student* p);

int main() {

	const char* dat = "studenti.txt";
	struct _student Head;
	Head.next = NULL;
	
	printf("Number of students in list: %d \n", noStudents(dat));
	printf("-----------------------------------------------------\n");
	loadStudents(dat, &Head);
	printList(&Head);
	freeList(&Head);

	return 0;
}

int noStudents(const char* dat) {

	FILE* fp = fopen(dat, "r");
	if (fp == NULL) {
		printf("Error! File is not open!\n");
		exit(1);
	}

	char buffer[256];
	int counter = 0;
	while (fgets(buffer, 256, fp)!=NULL) {

		counter++;
	}
	
	fclose(fp);

	return counter;

}

void loadStudents(const char* dat, Student* p) {

	FILE* fp = fopen(dat, "r");
	if (fp == NULL) {
		printf("Error! File not open!\n");
		exit(2);
	}
	
	char buffer[256];
	char firstname[MAX_LEN];
	char lastname[MAX_LEN];
	int test_score;
	float relative;
	while (fgets(buffer, 256, fp) != NULL) {
		sscanf(buffer,"%s %s %d", firstname, lastname, &test_score);
		appendStudent(p, firstname, lastname, test_score);
	}
	

	fclose(fp);
	
}

void appendStudent(Student* p, char* firstname, char* lastname, int test_score) {
	Student* curr = p;

	Student* q = malloc(sizeof(Student));
	if (q == NULL) {
		printf("Error! Memory allocation failed!\n");
		exit(3);
	}
	strcpy(q->name, firstname);
	strcpy(q->surname, lastname);
	q->score = test_score;
	q->rel_score = ((float)test_score / MAX_SCORE)*100;
	q->next = NULL;

	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = q;
}

void printList(Student* p) {

	Student* curr = p->next;
	while (curr != NULL) {
		printf("%-15s %-15s %-10d %-9.1f%%\n", curr->name, curr->surname, curr->score, curr->rel_score);
		curr = curr->next;
	}

}

void freeList(Student* p) {

	Student* curr = p->next;
	Student* temp;

	while (curr != NULL) {
		temp = curr;
		curr = curr->next;
		free(temp);
	}

	p->next = NULL;
}