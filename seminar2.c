#include<stdio.h>
#include<malloc.h>

struct Farmacie {
	int id;
	char* nume;
	float suprafata;
};

struct Farmacie initFarmacie(int id, const char* nume, float suprafata) {
	struct Farmacie f;
	f.id = id;
	f.nume = (char*)malloc(sizeof(char*) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.suprafata = suprafata;
}

void afisareFarmacie(struct Farmacie f) {
	printf("%d. %s are o suprafata de %5.2f \n", f.id, f.nume, f.suprafata);
}

void afisareVector(struct Farmacie* farmacii, int nrFarmacii) {
	for (int i = 0; i < nrFarmacii; i++) {
		afisareFarmacie(farmacii[i]);
	}
}

struct Farmacie* copiazaNElemente(struct Farmacie* vector, int nrFarmacii, int nrObiecteCopiate) {
	if (nrObiecteCopiate <= nrFarmacii && nrObiecteCopiate>0) {
		struct Farmacie* copiat = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrObiecteCopiate);
		for (int i = 0; i < nrObiecteCopiate; i++) {
			copiat[i] = initFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
		return copiat;
	}
}

int main() {
	//int v1[10];
	//int *v2=

	int nrFarmacii = 4;
	struct Farmacie* farmacii = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrFarmacii);
	for (int i = 0; i < nrFarmacii; i++) {
		farmacii[i] = initFarmacie(i + 1, "Farmacie", 30 * i + 10);
	}

	afisareVector(farmacii, nrFarmacii);

	int nrFramaciiCopiate = 2;

	struct Farmacie* farmaciiCopiate = copiazaNElemente(farmacii, nrFarmacii, nrFramaciiCopiate);
	printf("\n\n");
	afisareVector(farmaciiCopiate, nrFramaciiCopiate);
}
