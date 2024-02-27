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

int main() {
	//int v1[10];
	//int *v2=

	int nrFarmacii = 4;
	struct Farmacie* farmacii = (struct Farmacie*)malloc(sizeof(Farmacie) * nrFarmacii);
	for (int i = 0; i < nrFarmacii; i++) {
		farmacii[i] = initFarmacie(i + 1, "Farmacie", 30 * i + 10);
	}
}
