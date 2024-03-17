#include<stdio.h>
#include<malloc.h>

struct Cofetarie {
	char* nume;
	int nrAngajati;
	float* salarii;
};

void afiseazaCofetarie(struct Cofetarie c) {
	if (c.nume != NULL) {
		printf("Nume cofetarie: %s\n", c.nume);
	}
	printf("Nr. angajati: %d\n", c.nrAngajati);
	if (c.salarii != NULL) {
		printf("Salarii: ");
		for (int i = 0; i < c.nrAngajati;  i++) {
			printf("%5.2f, ", c.salarii[i]);
		}
	}
	printf("\n");
}

struct Cofetarie initCofetarie(const char* nume, int nrAng, const float* salarii) {
	struct Cofetarie c;
	c.nume = (char*)malloc(sizeof(char*) * (strlen(nume) + 1));
	strcpy(c.nume, nume);
	c.nrAngajati = nrAng;
	c.salarii = malloc(sizeof(float) * nrAng);
	for (int i = 0; i < nrAng; i++) {
		c.salarii[i] = salarii[i];
	}

	return c;
}

void stergeCofetarie(struct Cofetarie* c) {
	if (c->nume != NULL) {
		free(c->nume);
	}
	free(c->salarii);
	c->nume = NULL;
	c->salarii = NULL;
}

int main() {
	struct Cofetarie cofetaria1;

	cofetaria1.nume = (char*)malloc(strlen("Dulce") + 1);
	strcpy(cofetaria1.nume,"Dulce");
	cofetaria1.nrAngajati = 3;
	cofetaria1.salarii = malloc(sizeof(float) * cofetaria1.nrAngajati);
	for (int i = 0; i < cofetaria1.nrAngajati; i++) {
		cofetaria1.salarii[i] = (i + 1) * 1000;
	}

	afiseazaCofetarie(cofetaria1);

	float* vector = malloc(sizeof(float) * 2);
	vector[0] = 2358;
	vector[1] = 3546;

	struct Cofetarie cofetaria2 = initCofetarie("Mara", 2, vector);
	printf("\n");
	afiseazaCofetarie(cofetaria2);

	free(vector);
	stergeCofetarie(&cofetaria2);
	//nu mai afiseaza iar cofetaria2 pt ca am sters-0
	printf("\n Afisare cofetarii dupa stergere:");
	afiseazaCofetarie(cofetaria2);

	free(cofetaria1.nume);
	free(cofetaria1.salarii);


	return 0;
}
