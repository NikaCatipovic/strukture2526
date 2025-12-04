/*Napisati program koji èita datoteku racuni.txt u kojoj su zapisani nazivi svih datoteka koji
predstavljaju pojedini raèun.Na poèetku svake datoteke je zapisan datum u kojem vremenu je
raèun izdat u formatu YYYY - MM - DD.Svaki sljedeæi red u datoteci predstavlja artikl u formatu
naziv, kolièina, cijena.Potrebno je formirati vezanu listu raèuna sortiranu po datumu.Svaki èvor
vezane liste sadržava vezanu listu artikala sortiranu po nazivu artikla.Nakon toga potrebno je
omoguæiti upit kojim æe korisnik saznati koliko je novaca sveukupno potrošeno na specifièni
artikl u odreðenom vremenskom razdoblju i u kojoj je kolièini isti kupljen*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN 100

struct _date;
typedef struct _date* DateP;
typedef struct _date {
	int year;
	int month;
	int day;
}Date;

struct _article;
typedef struct _article* ArticleP;
typedef struct _article {
	char name[MAX_NAME_LEN];
	int quantity;
	double price;
	ArticleP next;
}Article;

struct _receipt;
typedef struct _receipt* ReceiptP;
typedef struct _receipt {
	char title[MAX_NAME_LEN];
	DateP date;
	ArticleP head;
	ReceiptP next;
}Receipt;

int openMainFile(Receipt* p);
int openFile(Receipt* p, const char* receipt_name);
int sortDate(Receipt* p, const char* name, int y, int m, int d);
int loadArticles(Receipt* p);
int openReceipt(Receipt* r);
int sortArticles(Article* p, char* article_name, int quan, double pr);
int printReceipts(Receipt* head);
int findArticle(Receipt* head);
int freeList(Receipt* head);


int main() {

	Receipt Head = { .title = "", .date = NULL, .head = NULL, .next = NULL };

	openMainFile(&Head); //lista racuna
	loadArticles(&Head); //lista artikala

	printReceipts(&Head);
	findArticle(&Head);

	freeList(&Head);
	

	return 0;
}

int openMainFile(Receipt* p) {

	FILE* fp = fopen("racuni.txt", "r");
	if (fp == NULL) {
		printf("Greska! Datoteka NIJE otvorena!\n");
		return EXIT_FAILURE;
	}

	char buffer[256];
	char receipt_title[MAX_NAME_LEN];

	while (fgets(buffer, 256, fp) != NULL) {
		sscanf(buffer, "%s", receipt_title);
		openFile(p, receipt_title);
		
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int openFile(Receipt* p, const char* receipt_name) {

	FILE* fp = fopen(receipt_name, "r");
	if (fp == NULL) {
		printf("Greska! Datoteka NIJE otvorena!\n");
		return EXIT_FAILURE;
	}

	char buffer[256];
	int y, m, d;

	fgets(buffer, 256, fp);
	sscanf(buffer, "%d - %d - %d", &y, &m, &d);
	sortDate(p, receipt_name, y, m, d);

	fclose(fp);

	return EXIT_SUCCESS;
}

int sortDate(Receipt* p, const char* name, int y, int m, int d) {

	Receipt* new = malloc(sizeof(Receipt));
	if (new == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	new->date = malloc(sizeof(Date));
	if (new->date == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		free(new);
		return EXIT_FAILURE;
	}

	new->head = malloc(sizeof(Article));
	if (new->head == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		free(new->date);
		free(new);
		return EXIT_FAILURE;
	}
	new->head->next = NULL;

	strcpy(new->title, name);
	new->date->year = y;
	new->date->month = m;
	new->date->day = d;
	new->next = NULL;

	Receipt* prev = p;
	Receipt* curr = p->next;

	while (curr != NULL &&
		  (curr->date->year < y ||
		  (curr->date->year == y && curr->date->month < m) ||
		  (curr->date->year == y && curr->date->month == m && curr->date->day < d))) {

		prev = curr;
		curr = curr->next;
	}

	prev->next = new;
	new->next = curr;

	return EXIT_SUCCESS;
}

int loadArticles(Receipt* p) {

	Receipt* curr = p->next;

	while (curr != NULL) {

		openReceipt(curr);
		curr = curr->next;
	}

	return EXIT_SUCCESS;
}

int openReceipt(Receipt* r) {

	FILE* fp = fopen(r->title, "r");
	if (fp == NULL) {
		printf("Greska! Datoteka NIJE otvorena!\n");
		return EXIT_FAILURE;
	}

	char buffer_date[256];
	char buffer[256];
	char article_name[MAX_NAME_LEN];
	int q;
	double pri;

	fgets(buffer_date, 256, fp); //ode je procitan datum 
	while (fgets(buffer, 256, fp) != NULL) {
		sscanf(buffer, "%s %d %lf", article_name, &q, &pri);
		sortArticles(r->head, article_name, q, pri);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int sortArticles(Article* p, char* article_name, int quan, double pr) {

	Article* new = malloc(sizeof(Article));
	if (new == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	strcpy(new->name, article_name);
	new->quantity = quan;
	new->price = pr; 
	new->next = NULL;

	Article* prev = p;
	Article* curr = p->next;

	while (curr != NULL && strcmp(curr->name,article_name)<0) {

		prev = curr;
		curr = curr->next;
	}

	prev->next = new;
	new->next = curr;

	return EXIT_SUCCESS;

}

//------------provjera------------------

int printReceipts(Receipt* head) {
	Receipt* currR = head->next;  
	while (currR != NULL) {
		printf("Racun: %-15s Datum: %04d-%02d-%02d\n",
			currR->title,
			currR->date->year,
			currR->date->month,
			currR->date->day);

		Article* currA = currR->head->next;
		while (currA != NULL) {
			printf("%-15s %-10d %-10.2lf\n",
				currA->name,
				currA->quantity,
				currA->price);
			currA = currA->next;
		}

		printf("\n");
		currR = currR->next;
	}

	return EXIT_SUCCESS;
}

int findArticle(Receipt* head) {

	printf("Unesi artikl za koji zelis saznati koliko je novaca sveukupno potroseno: ");
	char article_name[MAX_NAME_LEN];
	scanf("%s", article_name);

	int total_quantity = 0;
	double total_money = 0.0;

	Receipt* currR = head->next;
	while (currR != NULL) {
		Article* currA = currR->head->next;
		while (currA != NULL) {
			if (strcmp(currA->name, article_name) == 0) {
				total_quantity += currA->quantity;
				total_money += currA->quantity * currA->price;
			}
			currA = currA->next;
		}
		currR = currR->next;
	}

	if (total_quantity > 0) {
		printf("Artikl '%s' kupljen je ukupno %d puta, potroseno %.2lf eura.\n",
			article_name, total_quantity, total_money);
	}
	else {
		printf("Artikl '%s' nije pronaden u racunima.\n", article_name);
	}

	return EXIT_SUCCESS;
}

int freeList(Receipt* head) {

	Receipt* currR = head->next;
	while (currR != NULL) {
		Receipt* tempR = currR;

		// oslobodi sve artikle u ovom raèunu
		Article* currA = currR->head;
		while (currA != NULL) {
			Article* tempA = currA;
			currA = currA->next;
			tempA->next = NULL;
			free(tempA);
		}

		// oslobodi datum
		if (currR->date != NULL)
			free(currR->date);

		currR = currR->next;
		tempR->next = NULL;
		free(tempR);
	}

	head->next = NULL;

	return EXIT_SUCCESS;
}

