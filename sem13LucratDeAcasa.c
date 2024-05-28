//grafuri

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Autobuz Autobuz;
struct Autobuz {
	int linie;
	char* capatLinie;
};

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct NodPrincipal {
	Autobuz info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

Autobuz initAutobuz(int linie, const char* capat) {
	Autobuz a;
	a.linie = linie;
	a.capatLinie = (char*)malloc(sizeof(char) * (strlen(capat) + 1));
	strcpy(a.capatLinie, capat);
	return a;
}

//inserare la sfarsit lista simpla (lista principala)
void inserareListaPrincipala(NodPrincipal** graf, Autobuz a) {
	NodPrincipal* nod = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nod->info = a;
	nod->next = NULL;
	nod->vecini = NULL;

	if (*graf == NULL) {
		*graf = nod;
	}
	else {
		NodPrincipal* temp = *graf;
		//parcurg list cu ajutorul lui temp pana la final
		while (temp->next != NULL) {
			temp = temp->next;
		}
		//fac legatura dintre ultimul nod al listei cu nodul pe care il inserez
		temp->next = nod;
	}
}

//inserare lista secundara (tot inserare lista simpla la sfarsit)
NodSecundar* inserareListaSecundara(NodSecundar* cap, NodPrincipal* info) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->nod = info;
	nou->next = NULL;
	if (cap == NULL) {
		return nou;
	}
	else {
		NodSecundar* temp = cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
		return cap;
	}
}

//functie de cautare dupa linie
NodPrincipal* cautaLinie(NodPrincipal* graf, int linieCautata) {
	while (graf != NULL && graf->info.linie != linieCautata) {
		graf = graf->next;
	}
	return graf;
}

//inserareMuchie
void inserareMuchie(NodPrincipal* graf, int linieStart, int linieStop) {
	NodPrincipal* nodStart = cautaLinie(graf, linieStart);
	NodPrincipal* nodStop = cautaLinie(graf, linieStop);
	nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop);
	nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);
}

void main() {
	NodPrincipal* graf = NULL;

	inserareListaPrincipala(&graf, initAutobuz(0, "Romana"));
	inserareListaPrincipala(&graf, initAutobuz(1, "Universitate"));
	inserareListaPrincipala(&graf, initAutobuz(2, "Unirii"));
	inserareListaPrincipala(&graf, initAutobuz(3, "Victoriei"));
	inserareListaPrincipala(&graf, initAutobuz(4, "Militari"));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);
}
