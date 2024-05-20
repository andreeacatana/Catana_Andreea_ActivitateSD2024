#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Rezervare Rezervare;
struct Rezervare {
	int id;
	char* numeClient;
	int nrPers;
};

typedef struct Nod Nod;
struct Nod {
	Nod* st;
	Nod* dr;
	Rezervare info;
};

Rezervare citireRezervare(FILE* f) {
	Rezervare r;
	char aux[30];
	fgets(aux, 30, f);
	fscanf(f, "%d", &r.id);
	fscanf(f, "%s", &aux);
	r.numeClient = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(r.numeClient, aux);
	fscanf(f, "%d", &r.nrPers);
	return r;
}

Nod* inserareInArbore(Nod* arbore, Rezervare r) {
	if (arbore != NULL) {
		if (arbore->info.id < r.id) {
			arbore->dr = inserareInArbore(arbore->dr, r);
		}
		else {
			arbore->st = inserareInArbore(arbore->st, r);
		}
	}
	else {
		Nod* temp = (Nod*)malloc(sizeof(Nod));
		temp->info = r;
		temp->dr = NULL;
		temp->st = NULL;

		arbore = temp;
	}

	return arbore;
}

void citireFisier(char* numeFis, Nod** radacina) {
	int nrRez;
	FILE* f = fopen(numeFis, "r");
	fscanf(f, "%d", &nrRez);
	for (int i = 0; i < nrRez; i++) {
		Rezervare rez;
		rez = citireRezervare(f);
		*radacina = inserareInArbore(*radacina, rez);
	}
}

void afisareRezervare(Rezervare r) {
	printf("Rezervarea cu id-ul %d a fost facuta de %s pentru %d persoane\n",
		r.id, r.numeClient, r.nrPers);
}

void afisareArborePreordine(Nod* arbore) {
	if (arbore != NULL) {
		afisareRezervare(arbore->info);
		afisareArborePreordine(arbore->st);
		afisareArborePreordine(arbore->dr);
	}
}

void afisareArboreInordine(Nod* arbore) {
	if (arbore != NULL) {
		afisareArboreInordine(arbore->st);
		afisareRezervare(arbore->info);
		afisareArboreInordine(arbore->dr);
	}
}

void afisareArborePostordine(Nod* arbore) {
	if (arbore != NULL) {
		afisareArborePostordine(arbore->st);
		afisareArborePostordine(arbore->dr);
		afisareRezervare(arbore->info);
	}
}

Rezervare cautareRezervareDupaId(Nod* radacina, int id) {
	if (radacina != NULL) {
		if (radacina->info.id < id) {
			return cautareRezervareDupaId(radacina->dr, id);
		}
		else {
			if (radacina->info.id > id) {
				return cautareRezervareDupaId(radacina->st, id);
			}
			else {
				return radacina->info;
			}
		}
	}
	else {
		Rezervare r;
		r.id = -1;
		r.numeClient = NULL;
		r.nrPers = -1;
		return r;
	}
}

int calculNrTotalPersoane(Nod* rad) {
	if (rad) {
		int nrPers = rad->info.nrPers;
		int sPers = calculNrTotalPersoane(rad->st);
		int dPers = calculNrTotalPersoane(rad->dr);
		int suma = nrPers + sPers + dPers;

		return suma;
	}
	else {
		return 0;
	}
}


void main() {
	Nod* radacina = NULL;
	citireFisier("rezervari.txt", &radacina);
	//afisareArborePreordine(radacina);
	afisareArboreInordine(radacina);
	//afisareArborePostordine(radacina);

	printf("\n\n");
	Rezervare rez = cautareRezervareDupaId(radacina, 5);
	afisareRezervare(rez);

	printf("\nNr total persoane: %d", calculNrTotalPersoane(radacina));
}
