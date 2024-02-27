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
	return f;
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
	else {
		return NULL;
	}
}

struct Farmacie* copiazaFarmMici(struct Farmacie* farmacii, int nrFarm, float pragSupraf, int* nrFarmMici) {
	*nrFarmMici = 0;
	for (int i = 0; i < nrFarm; i++) {
		if (farmacii[i].suprafata < pragSupraf) {
			(*nrFarmMici)++;
		}
	}
	struct Farmacie* vector = (struct Farmacie*)malloc(sizeof(struct Farmacie) * (*nrFarmMici));

	int k = 0;
	for (int i = 0; i < nrFarm; i++) {
		if (farmacii[i].suprafata < pragSupraf) {
			vector[k++] = initFarmacie(farmacii[i].id, farmacii[i].nume, farmacii[i].suprafata);
		}
	}
	return vector;
}

void dezalocareVectFarm(struct Farmacie** vector, int* nrFarm) {
	for (int i = 0; i < (*nrFarm); i++){
		free((*vector)[i].nume);
	}

	free(*vector);
	*nrFarm = 0;
	*vector = NULL;
}

struct Farmacie getFarmacieByID(struct Farmacie* vector, int nrFarm, int idCautat) {
	for (int i = 0; i < nrFarm; i++) {
		if (vector[i].id == idCautat) {
			//returnam cu deep copy
			return initFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
	}

	return initFarmacie(0, "n/a", 0);
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

	int nrFarmMici = 0;

	farmacii[3].suprafata = 20;
	struct Farmacie* farmaciiMici = copiazaFarmMici(farmacii, nrFarmacii, 50,&nrFarmMici);
	printf("\n\n");
	afisareVector(farmaciiMici, nrFarmMici);


	struct Farmacie farmCautata = getFarmacieByID(farmacii, nrFarmacii, 10);
	printf("\nFarmacie cautata:\n");
	afisareFarmacie(farmCautata);
	free(farmCautata.nume);

	dezalocareVectFarm(&farmacii, &nrFarmacii);
	dezalocareVectFarm(&farmaciiCopiate, &nrFramaciiCopiate);
	dezalocareVectFarm(&farmaciiMici, &nrFarmMici);


}
