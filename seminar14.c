#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Autobuz Autobuz;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Autobuz {
	int linie;
	char* capatLinie;
};

struct NodPrincipal {
	Autobuz info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

//functie de inserare la sf in lista pricipala
//functie de cautare dupa linie

void inserarePrincipala(NodPrincipal** graf, Autobuz a) {
	NodPrincipal* nod = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nod->info = a;
	nod->next = NULL;
	nod->vecini = NULL;

	if ((*graf) != NULL) {
		NodPrincipal* temp = *graf;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nod;
	}
	else
	{
		*graf = nod;
	}
}

NodPrincipal* cautaLinie(NodPrincipal* graf, int linie) {
	while (graf && graf->info.linie != linie) {
		graf = graf->next;
	}
	return graf;
}

//functie de inserare in lista secundara
//functie de inserare muchie

NodSecundar* inserareSecundara(NodSecundar* cap, NodPrincipal* info) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = info;
	if (cap) {
		NodSecundar* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}

Autobuz initializareAutobuz(int linie, const char* capat) {
	Autobuz a;
	a.linie = linie;
	a.capatLinie = (char*)malloc(sizeof(char) * (strlen(capat) + 1));
	strcpy_s(a.capatLinie, strlen(capat) + 1, capat);
	return a;
}

void inserareMuchie(NodPrincipal* graf, int linieStart, int linieStop) {
	NodPrincipal* nodStart = cautaLinie(graf, linieStart);
	NodPrincipal* nodStop = cautaLinie(graf, linieStop);
	nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop);
	nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart);
}

//SEMINAR 14

#pragma region Coada

typedef struct nodCoada NodCoada;
struct nodCoada {
	int id;
	NodCoada* next;
};

void inserareCoada(NodCoada** cap, int id) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->id = id;
	nou->next = NULL;
	if (*cap) {
		NodCoada* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

int extragereDinCoada(NodCoada** cap) {
	if (*cap) {
		int rez = (*cap)->id;
		NodCoada* temp = (*cap)->next;
		free(*cap);
		*cap = temp;
		return rez;
	}
	else {
		return -1;
	}
}

//void inserareStiva(NodCoada** cap, int id) {
//	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
//	nou->id = id;
//	nou->next=
//}
//
//int extragereDinStiva(NodCoada** cap) {
//	extragereDinCoada(&cap);
//}

#pragma endregion


int getNumarNoduri(NodPrincipal* graf) {
	int s = 0;
	while (graf) {
		s++;
		graf = graf->next;
	}
	return s;
}

void afisareAutobuz(Autobuz a) {
	printf("%d are capatul la %s\n", a.linie, a.capatLinie);
}

void afisareCuParcurgereInLatime(NodPrincipal* graf, int nodPlecare) {
	//initializari
	NodCoada* coada = NULL;
	int nrNoduri = getNumarNoduri(graf);
	char* vizitate = (char*)malloc(sizeof(char) * nrNoduri); 
	for (int i=0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}

	inserareCoada(&coada, nodPlecare);
	vizitate[nodPlecare] = 1;

	while (coada) {
		//extragem nodul din coada
		int idNodCurent = extragereDinCoada(&coada);
		NodPrincipal* nodCurent = cautaLinie(graf, idNodCurent);
		afisareAutobuz(nodCurent->info);

		NodSecundar* temp = nodCurent->vecini;

		//inserare in coada si marcare ca vizitat fiecare vecin
		while (temp) {
			if (vizitate[temp->nod->info.linie] == 0) {
				vizitate[temp->nod->info.linie] = 1;
				inserareCoada(&coada, temp->nod->info.linie);
			}
			temp = temp->next;
		}
	}
	if (vizitate) {
		free(vizitate);
	}
}

//void afisareCuParcurgereInAdancime(NodPrincipal* graf, int nodPlecare) {
//	//initializari
//	NodCoada* stiva = NULL;
//	int nrNoduri = getNumarNoduri(graf);
//	char* vizitate = (char*)malloc(sizeof(char) * nrNoduri);
//	for (int i = 0; i < nrNoduri; i++) {
//		vizitate[i] = 0;
//	}
//
//	inserareStiva(&stiva, nodPlecare);
//	vizitate[nodPlecare] = 1;
//
//	while (coada) {
//		//extragem nodul din coada
//		int idNodCurent = extragereS(&coada);
//		NodPrincipal* nodCurent = cautaLinie(graf, idNodCurent);
//		afisareAutobuz(nodCurent->info);
//
//		NodSecundar* temp = nodCurent->vecini;
//
//		//inserare in stiva si marcare ca vizitat fiecare vecin
//		while (temp) {
//			if (vizitate[temp->nod->info.linie] == 0) {
//				vizitate[temp->nod->info.linie] = 1;
//				inserareCoada(&stiva, temp->nod->info.linie);
//			}
//			temp = temp->next;
//		}
//	}
// if (vizitate) {
//   free(vizitate);
//	}
//}

void stergereListaVecini(NodSecundar** cap) {
	NodSecundar* p = (*cap);
	while (p) {
		NodSecundar* aux = p;
		p = p->next;
		free(aux);
	}
	*cap = NULL;
}

void stergereGraf(NodPrincipal** graf) {
	while (*graf) {
		free((*graf)->info.capatLinie);
		stergereListaVecini(&(*graf)->vecini);

		NodPrincipal* temp = *graf;
		*graf = temp->next;
		free(temp);
	}
}

void main() {
	NodPrincipal* graf = NULL;

	inserarePrincipala(&graf, initializareAutobuz(0, "Romana"));
	inserarePrincipala(&graf, initializareAutobuz(1, "Universitate"));
	inserarePrincipala(&graf, initializareAutobuz(2, "Unirii"));
	inserarePrincipala(&graf, initializareAutobuz(3, "Victoriei"));
	inserarePrincipala(&graf, initializareAutobuz(4, "Militari"));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);

	afisareCuParcurgereInLatime(graf, 0);

	stergereGraf(&graf);
}
