#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>

struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++) {
		aux[i] = masini[i];
	}
	aux[*nrMasini] = m; //se adauga noua masina la sfarsitul vectorului aux
	(*nrMasini)++;
	if (masini != NULL)
		free(masini);

	return aux; //afisare vector dupa adugarea noii masini
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) {
	FILE* file = fopen(numeFisier, "r"); //deschidere fisier doar pt citire
	char buffer[100];
	char delimitare[] = ",\n"; //delimitarea proprietatilor unei masini in fisier
	struct Masina* masini = NULL;
	(*nrMasini) = 0;

	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);

		struct Masina m;
		m.id = atoi(element);
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);
		
		masini = adaugareInVector(masini, m, nrMasini);
	}

	fclose(file);
	return masini;
}

struct Masina* masiniMulteUsi(struct Masina* masini, int* nrMasini) {
	int nrMasiniNoi = 0;
	for (int i = 0; i < *nrMasini; i++) {
		if (masini[i].nrUsi > 2) {
			nrMasiniNoi++;
		}
	}
	
	struct Masina* masiniUsi = malloc(sizeof(struct Masina) * nrMasiniNoi);
	int j = 0;
	
	for (int i = 0; i < *nrMasini; i++) {
		if (masini[i].nrUsi > 2) {
			masiniUsi[j] = masini[i];
			j++;
		}
	}
	return masiniUsi;
}

//sem 4

void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			printf("%d, %s, %d, %.2f \t", matrice[i][j].id, matrice[i][j].producator, matrice[i][j].nrUsi, matrice[i][j].pret);
		}
		printf("\n");
	}
}

void citireMatrice(const char* numeFis, struct Masina** matrice, int nrLinii, int* nrCol) {
	FILE* file = fopen(numeFis, "r");
	char buffer[100];
	char delimitare[] = ",\n"; 

	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);

		struct Masina m;
		m.id = atoi(element);
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);

		matrice[m.nrUsi - 2] = adaugareInVector(matrice[m.nrUsi - 2], m, &(nrCol[m.nrUsi - 2]));
	}

	fclose(file);

}

//functie care calc pretul mediu al masinilor cu nr de usi dat ca parametru

float pretMediu(struct Masina** matrice, int nrLinii, int* nrCol, int nrUsi) {
	if (nrUsi < 2 || nrUsi>4) {
		return 0;
	}
	float pretTotal = 0;
	int index = nrUsi - 2;
	if (nrCol[index] == 0) {
		return 0;
	}

	for (int i = 0; i < nrCol[index]; i++) {
		pretTotal += matrice[index][i].pret;
	}
	return pretTotal / nrCol[index];
}

struct Masina cautareMasinaId(struct Masina** matrice, int nrLinii, int* nrCol, int id) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrCol[i]; j++) {
			if (matrice[i][j].id == id) 
				return matrice[i][j];
		}
	}

	struct Masina m;
	m.id = -1;
	m.producator = NULL;
	m.nrUsi = -1;
	m.pret = -1;
	return m;
}

void dezalocareMatrice(struct Masina*** matrice, int nrLinii, int** nrCol) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < (*nrCol)[i]; j++) {
			free((*matrice)[i][j].producator);
			//optional de facut
			//(*matrice)[i][j].producator = NULL; 
		}
		free((*matrice)[i]);
	}
	free((*nrCol));
	(*nrCol) = NULL;
	free((*matrice));
	(*matrice) = NULL;
}


int main() {
	//struct Masina* masini = NULL;
	//int nrMasini = 0;

	//
	///*masini = citireFisier("masini.txt", &nrMasini); // am preluat masinile
	//// le afisam
	//for (int i = 0; i < nrMasini; i++) {
	//	printf("Masina nr. %d \n", i);
	//	printf("Id: %d \n", masini[i].id);
	//	printf("Producator: %s \n", masini[i].producator);
	//	printf("Nr usi: %d \n", masini[i].nrUsi);
	//	printf("Pret: %5.2f \n", masini[i].pret);
	//	printf("\n");
	//}*/

	//masini = citireFisier("masini.txt", &nrMasini);
	//int k = 0;
	//for (int i = 0; i < nrMasini; i++) {
	//	if (masini[i].nrUsi > 2) {
	//		k++;
	//	}
	//}

	//printf("nr masini cu peste 2 usi: %d\n", k);

	//struct Masina* masiniMaiMulteUsi = masiniMulteUsi(masini, &nrMasini);

	////afisare masini cu peste 2 usi
	//for (int i = 0; i < k; i++) {
	//	printf("Masina nr. %d \n", i);
	//	printf("Id: %d \n", masiniMaiMulteUsi[i].id);
	//	printf("Producator: %s \n", masiniMaiMulteUsi[i].producator);
	//	printf("Nr usi: %d \n", masiniMaiMulteUsi[i].nrUsi);
	//	printf("Pret: %5.2f \n", masiniMaiMulteUsi[i].pret);
	//	printf("\n");
	//}

	//free(masiniMaiMulteUsi);

	//sem 4

	struct Masina** matrice;
	int nrLinii = 3;
	int* nrCol;
	nrCol = (int*)malloc(sizeof(int) * nrLinii); //vector de lungimi
	matrice = (struct Masina**)malloc(sizeof(struct Masina*) * nrLinii);

	for (int i = 0; i < nrLinii; i++) {
		nrCol[i] = 0;
		matrice[i] = NULL;
	}

	citireMatrice("masini.txt", matrice, nrLinii, nrCol);
	afisareMatrice(matrice, nrLinii, nrCol);

	printf("\nPretul mediu este: %5.2f", pretMediu(matrice, nrLinii, nrCol, 4));

	struct Masina masinaCautata;
	masinaCautata = cautareMasinaId(matrice, nrLinii, nrCol, 6);
	printf("\n\n%i %s %i %.2f", masinaCautata.id, masinaCautata.producator, masinaCautata.nrUsi, masinaCautata.pret);

	dezalocareMatrice(&matrice, nrLinii, &nrCol);
}
