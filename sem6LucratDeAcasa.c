#include <stdio.h>
#include <malloc.h>

typedef struct Santier Santier;
struct Santier {
	char* numeProiect;
	int nrMuncitori;
	float suprafata;
};

typedef struct Nod Nod;
struct Nod {
	Nod* prev;
	Nod* next;
	Santier info; // informatia utila = santier
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};

Santier initSantier(const char* nume, int nr, float supr) {
	Santier s;

	s.numeProiect = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(s.numeProiect, nume);
	s.nrMuncitori = nr;
	s.suprafata = supr;
	
	return s;
}

void afisareSantier(Santier s) {
	printf("Santierul: %s are %d muncitori si %5.2f m2 suprafata.\n", s.numeProiect, s.nrMuncitori, s.suprafata);
}

void inserareInceput(ListaDubla* lista, Santier s) {//unde se inserez si ce inserez
	Nod* aux = malloc(sizeof(Nod));
	aux->info = s;
	aux->next = lista->prim;
	aux->prev = NULL; //inserez la inceput, nu mai am nimic in fata
	if (lista->prim != NULL) {
		lista->prim->prev = aux;
	}
	else {
		lista->ultim = aux;
	}
	lista->prim = aux;
}

void inserareSfarsit(ListaDubla* lista, Santier s) {
	Nod* aux = malloc(sizeof(Nod));
	aux->info = s;
	aux->next = NULL;
	aux->prev = lista->ultim; 
	if (lista->ultim != NULL) {
		lista->ultim->next = aux;
	}
	else {
		lista->prim = aux;
	}
	lista->ultim = aux;
}

void afisareListaInceput(ListaDubla lista) {
	for (Nod* nod = lista.prim; nod != NULL; nod = nod->next) {
		afisareSantier(nod->info);
	}
}

void afisareListaSfarsit(ListaDubla lista) {
	for (Nod* nod = lista.ultim; nod != NULL; nod = nod->prev) {
		afisareSantier(nod->info);
	}
}

int calcNrTotalMuncitori(ListaDubla lista) {
	int suma = 0;
	for (Nod* i = lista.prim; i != NULL; i = i->next) {
		suma += i->info.nrMuncitori;
	}
	return suma;
}

int calcNrMuncitoriSuprafata(ListaDubla lista, float suprafataMax) {
	int suma = 0;
	for (Nod* i = lista.prim; i != NULL; i = i->next) {
		if (i->info.suprafata < suprafataMax) {
			suma += i->info.nrMuncitori;
		}
	}
	return suma;
}

void stergereSantierDupaNume(ListaDubla* lista, const char* nume) {
	Nod* nod = lista->prim;

	while (nod != NULL) {
		if (strcmp(nod->info.numeProiect, nume) == 0) {
			if (nod->prev == NULL) {
				if (nod->next == NULL) {
					lista->prim = NULL;
					lista->ultim = NULL;
				}
				else {
					nod->next->prev = NULL;
					lista->prim = nod->next;
				}
			}
			else {
				if (nod->next == NULL) {
					nod->prev->next = NULL;
					lista->ultim = nod->prev;
				}
				else {
					nod->prev->next = nod->next;
					nod->next->prev = nod->prev;
				}
			}
			free(nod->info.numeProiect);
			free(nod);
			nod = NULL;
		}
		else {
			nod = nod->next;
		}
	}
}

void stergereListaCompleta(ListaDubla* lista) {
	if (lista != NULL) {
		Nod* aux = lista->prim;
		while (aux != NULL) {
			free(aux->info.numeProiect);
			Nod* temp = aux->next;
			free(aux);
			aux = temp;
		}
		lista->prim = NULL;
		lista->ultim = NULL;
	}
}

int main() {
	Santier s1 = initSantier("Santier 1", 12, 370);
	Santier s2 = initSantier("Santier 2", 14, 420);
	Santier s3 = initSantier("Santier 3", 22, 545);
	Santier s4 = initSantier("Santier 4", 10, 200);

	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareInceput(&lista, s1);
	inserareInceput(&lista, s2);
	inserareInceput(&lista, s3);
	inserareInceput(&lista, s4);

	printf("\nAfisare lista de la inceput, cu inserare la inceput.\n\n");
	afisareListaInceput(lista);

	printf("\nAfisare lista de la sfarsit, cu inserare la inceput.\n\n");
	afisareListaSfarsit(lista);

	/*inserareSfarsit(&lista, s1);
	inserareSfarsit(&lista, s2);
	inserareSfarsit(&lista, s3);
	inserareSfarsit(&lista, s4);

	printf("\nAfisare lista de la inceput, cu inserare la sfarsit.\n\n");
	afisareListaInceput(lista);*/

	int nrMuncitori = calcNrTotalMuncitori(lista);
	printf("\nNr total muncitori: %d. \n\n", nrMuncitori);
	puts(""); // acelasi lucru cu printf("\n");

	int nrMuncitoriSuprafata = calcNrMuncitoriSuprafata(lista, 400);
	printf("\nNr total muncitori: %d. \n\n", nrMuncitoriSuprafata);

	stergereSantierDupaNume(&lista, "Santier 1");
	printf("\nAfisare lista dupa stergere santier:\n");
	afisareListaInceput(lista);

	stergereListaCompleta(&lista);
	printf("\nAfisare lista dupa stergere:\n");
}
