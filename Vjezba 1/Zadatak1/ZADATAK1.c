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

struct _student;
typedef struct _student* StudentP;
typedef struct _student {
	char name[MAX_LEN];
	char surname[MAX_LEN];
	int bodovi;
	StudentP next;
}Student;

int brojStudenata(const char* dat);


int main() {

	const char* dat = "studenti.txt";
	struct _student Head;
	Head.next = NULL;
	//Testiranje
	int br = brojStudenata(dat);
	printf("Broj redaka je %d \n", br);
	

	return 0;
}

int brojStudenata(const char* dat) {

	FILE* fp = fopen(dat, "r");
	if (fp == NULL) {
		printf("Geska! Datoteka nije otvorena!\n");
		exit(1);
	}

	char buffer[256];
	int brojac = 0;
	while (fgets(buffer, 256, fp)!=NULL) {

		brojac++;
	}
	
	fclose(fp);

	return brojac;

}