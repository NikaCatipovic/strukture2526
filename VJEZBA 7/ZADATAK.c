/*Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Toènije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _directory;
typedef struct _directory* directoryP;
typedef struct _directory {
	char name[64];
	directoryP parent;
	directoryP child;
	directoryP next;
}directory;

directoryP createDirectory(const char* name, directoryP parent); 
int addChild(directoryP parent, directoryP child);
directoryP cdDir(directoryP current, const char* name);

int main() {

	int izbor;
	char ime_direktorija[64];
	
	directoryP root = createDirectory("C:", NULL); //root
	directoryP current = root;

	do {
		printf("1 - md (napravi direktorij)\n");
		printf("2 - cd dir (udi u poddirektorij)\n");
		printf("3 - cd.. (vrati se u parent)\n");
		printf("4 - dir (ispis sadrzaja)\n");
		printf("5 - exit \n");
		printf("Unesite izbor: ");
		scanf("%d", &izbor);

		switch (izbor) {
		case 1:
			printf("Uneiste ime novog direktorija: ");
			scanf("%s", ime_direktorija);
			current = cdDir(current, ime_direktorija);
			if( novi)

		}
	}

	return 0;
}

directoryP createDirectory(const char* name, directoryP parent) {
	//alokacija memorije i provjera
	directoryP new = malloc(sizeof(directory));
	if (new == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return NULL; //mora bit NULL jer funkcija vraca directoryP
	}
	strcpy(new->name, name);
	new->parent = parent;
	new->child = NULL;
	new->next = NULL;


	return new;
}

int addChild(directoryP parent, directoryP child) {

	//provjera postoje li argumenti funkcije
	if (parent == NULL || child == NULL) {
		printf("Direktorij ili poddirektorij ne postoji!\n");
		return EXIT_FAILURE;
	}

	//Ako parent nema djece, child postaje prvo dijete
	if (parent->child == NULL) {
		parent->child = child;

		return EXIT_SUCCESS;
	}

	//Ako parent vec ima djecu, prodi listu do zadnjeg i dodaj na kraj 
	directoryP curr = parent->child; //pomocni pokazivac za prolazak kroz listu
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = child;


	return EXIT_SUCCESS;
}

directoryP cdDir(directoryP current, const char* name) {

	//provjera
	if (current == NULL || name == NULL) {
		printf("Direktorij ili ime nije vazece!\n");
		return current;
	}

	directoryP curr = current->child; //pokazivac na prvo dijete trenutnog direktorija

	//petlja kroz sve cvorove djece trenutnog direktorija 
    // (vrti se sve dok ima djece)
	while (curr != NULL) {

		if (strcmp(curr->name, name) == 0) { 

			return curr; //vracamo pokazivac direktorija sa trazenim imenom
		}
		curr = curr->next;
	}

	printf("Direktorij '%s' ne postoji!\n", name);


	return current;
}
