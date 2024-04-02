#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

//tabele de dispersie

typedef struct Galerie Galerie;
struct Galerie {
	int cod;
	char* nume;
	float pretIntrare;
};

typedef struct Nod Nod;
struct Nod {
	Galerie info;
	Nod* next;
};

typedef struct HashTable HashTable;
struct HashTable {
	Nod** vector;
	int dim;
};

HashTable initHash(int dimensiune) {
	HashTable hash;
	hash.dim = dimensiune;
	hash.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		hash.vector[i] = NULL;
	}

	return hash;
}

Galerie initGalerie(int cod, const char* nume, float pret) {
	Galerie g;
	g.cod = cod;
	g.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(g.nume, nume);
	g.pretIntrare = pret;
	return g;
}

int calculHash(int cod, const char* nume, int dim) {
	if (dim > 0) {
		int rezultat = cod * strlen(nume);
		return rezultat % dim;
	}
	return -1;
}

void inserareLaFinal(Nod** cap, Galerie g) {
	Nod* temp = (Nod*)malloc(sizeof(Nod));
	temp->info = g;
	temp->next = NULL;
	if (*cap) {
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = temp; // cand am ajuns la final fac legatura
	}
	else {
		*cap = temp; 
	}
}

void inserareGalerieInHash(HashTable hash, Galerie g) {
	if (hash.dim > 0) {
		int pozitie = calculHash(g.cod, g.nume, hash.dim);

		//verificam daca avem coliziune
		//acest if este aici doar pt a prez situatia de coliziune
		if (hash.vector[pozitie] != NULL) {//daca avem deja elem pe pozitia aia
			inserareLaFinal(&(hash.vector[pozitie]), g);	
		}
		else {
			//pe ramura asta nu ar fi coliziune
			inserareLaFinal(&(hash.vector[pozitie]), g);
		}
	}
}

void afisareGalerie(Galerie g) {
	printf("%d. Intrarea la Galeria %s costa %.2f.\n", g.cod, g.nume, g.pretIntrare);
}

void afisareListaGalerii(Nod* cap) {
	while (cap) {
		afisareGalerie(cap->info);
		cap = cap->next;
	}
}

void afisareHash(HashTable hash) {
	for (int i = 0; i < hash.dim; i++) {
		if (hash.vector[i] != NULL) {
			printf("Cluster: %d\n", (i + 1));
			afisareListaGalerii(hash.vector[i]);
		}
	}
}

Galerie cautaGalerieDupaCheie(int cod, const char* nume, HashTable hash){
	int pozitie = calculHash(cod, nume, hash.dim);
	if (pozitie >= 0 && pozitie < hash.dim) {
		Nod* p = hash.vector[pozitie];
		while (p && p->info.cod != cod && strcmp(p->info.nume, nume) != 0) {
			p = p->next;
		}
		if (p) {
			return p->info;//shallow copy
		}
		else {
			return initGalerie(-1, "", 0);
		}
	}
	else {
		return initGalerie(-1, "", 0);
	}

}

void main() {
	
	Galerie g1 = initGalerie(1, "Orizont", 10);
	Galerie g2 = initGalerie(2, "Cercul armatei", 6);
	Galerie g3 = initGalerie(3, "Louvre", 30);
	Galerie g4 = initGalerie(4, "Antipa", 20);
	Galerie g5 = initGalerie(5, "Istorie", 15);
	Galerie g6 = initGalerie(6, "Geologie", 17);

	HashTable tabela = initHash(5);

	inserareGalerieInHash(tabela, g1);
	inserareGalerieInHash(tabela, g2);
	inserareGalerieInHash(tabela, g3);
	inserareGalerieInHash(tabela, g4);
	inserareGalerieInHash(tabela, g5);
	inserareGalerieInHash(tabela, g6);

	afisareHash(tabela);

	Galerie g = cautaGalerieDupaCheie(1, "Orizont", tabela);
	printf("\n\nCautare\n\n");
	afisareGalerie(g);
}
