/*Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna
rezultat. Stog je potrebno realizirati preko vezane liste.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _postfix* Position;
typedef struct _postfix {
	double number;
	Position next;
}postfix;

int readFile(Position head);
int push(Position head, double value); //dodavanje na stog 
int evaluatePostfix(Position head, char operator); //izvršava operaciju pomocu dva elementa sa vrha stoga
int freeList(Position head);


int main() {

	postfix Head = { .number = 0, .next = NULL };

	readFile(&Head);
	printf("Rezultat postfix izraza: %.2lf\n", Head.next->number);

	freeList(&Head);

	return 0;
}

int readFile(Position head) {

	FILE* fp = fopen("postfix.txt", "r"); 
	if (fp == NULL) {
		printf("Datoteka nije otvorena!\n");
		return EXIT_FAILURE;
	}

	char buffer[50];

	while (fscanf(fp, " %s", buffer) == 1) { //cita se element po element iz datoteke i sprema u buffer
		//ako je buffer broj (pozitivan ili negativan)
		if ((buffer[0] >= '0' && buffer[0] <= '9') || (buffer[0] == '-' && buffer[1] >= '0' && buffer[1] <= '9')) {
			double value;
			sscanf(buffer, "%lf", &value); //iz stringa buffer procita jedan double broj i spremi ga u value 
			push (head, value);
		}
		//ako je buffer operacija
		else if (strlen(buffer) == 1 && (buffer[0] == '+' || buffer[0] == '-' || buffer[0] == '*' || buffer[0] == '/')) {

			evaluatePostfix(head, buffer[0]);
		}

		//inace
		else {
			printf("Nepoznat element: %s\n", buffer);
		}
	}


	fclose(fp);
	return EXIT_SUCCESS;
}

int push(Position head, double value) {

	//alokacija i provjera memorije
	Position newElement = (Position)malloc(sizeof(postfix));
	if (newElement == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	//dodjeljivanje vrijednosti u cvor
	newElement->number = value;

	//POSTAVLJANJE CVORA NA POCETAK
	newElement->next = head->next; //nakon novo ubacenog slijedi ono sta je bilo iza heada
	head->next = newElement; //nakon heada slijedi novi 

	return EXIT_SUCCESS;
}

int evaluatePostfix(Position head, char operator) {

	Position q = head;           
	Position first = q->next;    
	Position second = first->next;
	Position temp = NULL;
	double result = 0.0;
    
	switch (operator) {
	case '+':
		result = second->number + first->number;
		break;
	case '-':
		result = second->number - first->number;
		break;
	case '*':
		result = second->number * first->number;
		break;
	case '/':
		result = second->number / first->number;
		break;
	}

	//alokacija i provjera memorije
	temp = (Position)malloc(sizeof(postfix));
	if (temp == NULL) {
		printf("Neuspjela alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	temp->number = result; //cvoru s vrha (temp) dodijeli rezultat 

	temp->next = second->next; //povezi cvor s vrha s iducin od second

	
	q->next = temp; //povezi head sa vrhon (umjesto sa first)

	//oslobodi first i second jer se napravila operacija nad njima 
	first->next = NULL;
	second->next = NULL;
	free(first);
	free(second);

	return EXIT_SUCCESS;
}

int freeList(Position head) {
	Position temp = NULL;

	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}

