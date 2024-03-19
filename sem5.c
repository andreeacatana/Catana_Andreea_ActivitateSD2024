#include<stdio.h>
#include<malloc.h>

//liste simple
//fiecare nod contine inf utila si adresa urmatorului nod

typedef struct Santier Santier;
struct Santier {
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

typedef struct Nod Nod;
struct Nod {
    Santier info;
    Nod* next;
};

Santier initSantier(const char* nume, int nrMuncitori, float suprafata) {
    Santier s;
    s.numeProiect = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(s.numeProiect, nume);
    s.nrMuncitori = nrMuncitori;
    s.suprafata = suprafata;

    return s;
}

Nod* inserareInceput(Santier s, Nod* lista) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->info = s;
    nod->next = lista;

    return nod;
}

void afisareSantier(Santier s) {
    printf("%s are %d muncitori si o suprafata de %5.2f m2\n", s.numeProiect, s.nrMuncitori, s.suprafata);
}

void afisareLista(Nod* lista) {
    while (lista != NULL) {

        //procesare
        afisareSantier(lista->info);
        //parcurgerea clasica a unei liste simple
        lista = lista->next;
    }
}

int sumaNrMuncitori(Nod* lista) {
    int suma = 0;
    while (lista != NULL) {
        suma += lista->info.nrMuncitori;
        lista = lista->next;
    }
    return suma;
}

void stergereLista(Nod** lista) { //modificam lista la final de aceea dublu pointer
    while ((*lista) != NULL) {
        free((*lista)->info.numeProiect);
        Nod* aux = (*lista)->next;
        free(*lista);
        (*lista) = aux;
    }
    (*lista) = NULL;
}

//functie care sa afis numele santierului cu densitatea cea mai mare de mun/m2
float densitateMuncitori(Santier s) {
    if (s.suprafata > 0) {
        return s.nrMuncitori / s.suprafata;
    }
    else return 0;
}

char* numeSantierDensMunc(Nod* lista) {
    float max = 0;
    char* aux = NULL;
    while (lista != NULL) {
        if (densitateMuncitori(lista->info) > max) {
            max = densitateMuncitori(lista->info);
            aux = lista->info.numeProiect;
        }
        lista = lista->next;
    }
    if (aux != NULL) {
        char* nume = (char*)malloc(strlen(aux) + 1);
        strcpy(nume, aux);
        return nume;
    }

    else return NULL;
}

int main() {
    Nod* lista = NULL; //merge si = 0, dar scriem NULL pt a marca faptul ca este pointer

    Santier s1 = initSantier("Santier1", 15, 4875);
    Santier s2 = initSantier("Santier2", 18, 5746);
    Santier s3 = initSantier("Santier3", 12, 3450);
    Santier s4 = initSantier("Santier4", 25, 9747);
    lista = inserareInceput(s1, lista);
    lista = inserareInceput(s2, lista);
    lista = inserareInceput(s3, lista);
    lista = inserareInceput(s4, lista);

    lista = inserareInceput(initSantier("Santier5", 17, 8754), lista);

    //afisareSantier(s1);

    afisareLista(lista);

    int nrTotalMuncitori = sumaNrMuncitori(lista);
    printf("\nNr total muncitori: %d \n", nrTotalMuncitori);


    printf("\nProiectul cu dens cea mai mare este %s.\n", numeSantierDensMunc(lista));

    //dezalocare
    stergereLista(&lista);
    afisareLista(lista);
}
