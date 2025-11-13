/*Napisati program za zbrajanje i mnozenje polinoma. Koeficijenti i eksponenti se
citaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nuzno sortirani.*/#define _CRT_SECURE_NO_WARNINGS#include <stdio.h>#include <stdlib.h>typedef struct poly {
	int coeff;
	int pow;
	struct poly* next;
} poly;

typedef poly* Position;int sortPoly(Position head, int coeff, int pow);int openFile(Position head, const char* dat);int sumPoly(Position head,Position head1, Position head2);int productPoly(Position head, Position head1, Position head2);int printPoly(Position head);int freePoly(Position head);int main() {	poly head = { .coeff = 0, .pow = 0, .next = NULL };	poly head1 = { .coeff = 0, .pow = 0, .next = NULL };	poly head2 = { .coeff = 0, .pow = 0, .next = NULL };	const char* dat1 = "polinom1.txt";	const char* dat2 = "polinom2.txt";	openFile(&head1, dat1);	openFile(&head2, dat2);	sumPoly(&head, &head1, &head2);	printPoly(&head);	freePoly(&head);	productPoly(&head, &head1, &head2);	printPoly(&head);	freePoly(&head);	freePoly(&head1);	freePoly(&head2);	return 0;}int sortPoly(Position head, int coeff, int pow) {	//postavljanje pokazivaca za head i cvor koji slijedi iza heada	Position prev = head;	Position curr = head->next;	//alokacija memorije i provjera 	poly* new_poly = malloc(sizeof(poly));	if (new_poly == NULL) {		printf("Neuspjesna alokacija memorije!\n");		return EXIT_FAILURE;	}	//sadrzaj cvora koji se ubacuje	new_poly->coeff = coeff;	new_poly->pow = pow;	//ako je lista prazna ili je potencija trenutnog cvora manja od onog koji se ubacuje	if (curr == NULL || curr->pow < new_poly->pow) {		new_poly->next = prev->next; //cvor koji se ubacuje pokazuje na sljedeci od heada		prev->next = new_poly; //head pokazuje na ubaceni cvor			}	//ako lista nije prazna i novi cvor ne ide na pocetak 	else {		while (curr != NULL && curr->pow > new_poly->pow) { //u ovoj petlji pomicemo pokazivace dok ne dodemo do kraja liste ili 			//dok potencija trenutnog ne bude manja od novog 			prev = curr;			curr = curr->next;		}		//ubacivanje u sredinu/kraj		new_poly->next = curr; //novi cvor pokazuje na trenutnog (jer novi ima vecu potenciju od trenutnog)		prev->next = new_poly; //prethodni sad pokazuje na novi	}			return EXIT_SUCCESS;}int openFile(Position head, const char* dat) {	//otvaranje datoteke u modu za citanje	FILE* fp = fopen(dat, "r");	if (fp == NULL) {		printf("Datoteka nije otvorena!\n");		return EXIT_FAILURE;	}		int coeff, pow;	while (fscanf(fp, "%d %d", &coeff, &pow) == 2) { 		sortPoly(head, coeff, pow);	}	fclose(fp);	return EXIT_SUCCESS;}int sumPoly(Position head,Position head1, Position head2) {	Position curr1 = head1->next;	Position curr2 = head2->next;	Position curr = head;	while (curr1 != NULL && curr2 != NULL) { //u ovoj petlji se usporeduju potencije dok poly1 i poly2 ne dodu do kraja				poly* new_poly = malloc(sizeof(poly));		if (new_poly == NULL) {			printf("Neuspjesna alokacija memorije!\n");			return EXIT_FAILURE;		}		//ako je potencija poly1 veca, onda prepisi taj element u new_poly		if (curr1->pow > curr2->pow) { 			new_poly->pow = curr1->pow;			new_poly->coeff = curr1->coeff;			curr1 = curr1->next;		}		//ako je potencija poly1 manja, onda prepisi element poly2 u new_poly		else if (curr1->pow < curr2->pow) {			new_poly->coeff = curr2->coeff;			new_poly->pow = curr2->pow;			curr2 = curr2->next;		}		//ako su potencije iste		else {			new_poly->coeff = curr1->coeff + curr2->coeff; //zbroji koeficijente			new_poly->pow = curr1->pow; //isti su koeficijenti svejedno oce li bit curr1 ili curr2			//ako je zbroj jednak 0, ne zelim taj element u listi pa ga brisem			if (new_poly->coeff == 0) {				free(new_poly);				curr1 = curr1->next;				curr2 = curr2->next;				continue;			}			//nakon usporedbe idemo na iduce clanove			curr1 = curr1->next;			curr2 = curr2->next;		}		//dodavanje na kraj (poly1 i poly2 su sortirani pa ce bit i ovaj zbroj)		new_poly->next = NULL;		curr->next = new_poly;		curr = new_poly;	}	//ako je u poly1 ostalo elemenata	while (curr1 != NULL) {

		poly* new_poly = malloc(sizeof(poly));
		if (new_poly == NULL) {
			printf("Neuspjesna alokacija memorije!\n");
			return EXIT_FAILURE;
		}
		new_poly->coeff = curr1->coeff;
		new_poly->pow = curr1->pow;

		new_poly->next = NULL;
		curr->next = new_poly;
		curr = new_poly;

		curr1 = curr1->next;
	}	//ako je u poly2 ostalo elemenata	while (curr2 != NULL) {

		poly* new_poly = malloc(sizeof(poly));
		if (new_poly == NULL) {
			printf("Neuspjesna alokacija memorije!\n");
			return EXIT_FAILURE;
		}
		new_poly->coeff = curr2->coeff;
		new_poly->pow = curr2->pow;

		new_poly->next = NULL;
		curr->next = new_poly;
		curr = new_poly;

		curr2 = curr2->next;
	}		return EXIT_SUCCESS;}int productPoly(Position head, Position head1, Position head2) {

	Position curr1 = head1->next;

	while (curr1 != NULL) {
		Position curr2 = head2->next;
		while (curr2 != NULL) {

			int newCoeff = curr1->coeff * curr2->coeff;
			int newPow = curr1->pow + curr2->pow;

			// provjera postoji li veæ èlan s istom potencijom
			Position temp = head->next;
			int found = 0;
			while (temp != NULL) {
				if (temp->pow == newPow) {
					temp->coeff += newCoeff; // zbroji koeficijente
					found = 1;
					break;
				}
				temp = temp->next;
			}

			// ako ne postoji, ubaci novi èvor pomoæu sortPoly
			if (found!=1) {
				sortPoly(head, newCoeff, newPow);
			}

			curr2 = curr2->next;
		}
		curr1 = curr1->next;
	}

	return EXIT_SUCCESS;
}

int printPoly(Position head) {
	Position curr = head->next; 
	while (curr != NULL) {
		printf("%d*x^%d ", curr->coeff, curr->pow);
		curr = curr->next;
	}
	printf("\n");

	return EXIT_SUCCESS;
}

int freePoly(Position head) {
	Position curr = head->next; 
	Position temp = NULL;

	while (curr != NULL) {
		temp = curr;
		curr = temp->next;
		temp->next = NULL;
		free(temp);
	}

	head->next = NULL; 

	return EXIT_SUCCESS;
}