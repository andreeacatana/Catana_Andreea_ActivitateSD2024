#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

//heap struct de date liniara (vector) care are ca scop obtinerea val min (min heap) sau val max (max heap)

//arbore binar (un nod parinte are max 2 fii) - i este nivelul
//fiu stanga i*2+1
//fiu dreapta i*2+2

typedef struct Mail Mail;
struct Mail {
	char* text;
	int prioritate;
};

typedef struct Heap Heap;
struct Heap {
	Mail* vector;
	int dim;
};

Heap initHeap(int dim) {
	Heap h;
	h.vector = (Mail*)malloc(sizeof(Mail) * dim);
	h.dim = dim;
	return h;
}

Mail initMail(const char* text, int prioritate) {
	Mail m;
	m.prioritate = prioritate;
	m.text = (char*)malloc(strlen(text) + 1);
	strcpy(m.text, text);
	return m;
}

void afisareMail(Mail m) {
	printf("Mailul cu textul: %s are prioritatea %d.\n", m.text, m.prioritate);
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.dim; i++) {
		afisareMail(h.vector[i]);
	}
}

void filtrareHeap(Heap heap, int pozRadacina) {
	int fs = pozRadacina * 2 + 1; //fiu stanga
	int fd = pozRadacina * 2 + 2; // fiu dreapta
	int pozMax = pozRadacina;

	if (fs < heap.dim && heap.vector[pozMax].prioritate < heap.vector[fs].prioritate) {//daca exista fs si
		pozMax = fs;
	}
	if (fd < heap.dim && heap.vector[pozMax].prioritate < heap.vector[fd].prioritate) {//daca exista fs si
		pozMax = fd;
	}

	if(pozMax!=pozRadacina){

		if (heap.vector[pozRadacina].prioritate < heap.vector[pozMax].prioritate) {
			Mail aux = heap.vector[pozRadacina];
			heap.vector[pozRadacina] = heap.vector[pozMax];
			heap.vector[pozMax] = aux;
			//calcul nod frunza (nu mai are fii) i*2+1>dim-1 => i
			if (pozMax < (heap.dim - 2) / 2) {
				filtrareHeap(heap, pozMax);
			}
		}
	}
}

Mail extragereMax(Heap* heap) { //aici modificam heap  pt ca realocam vectorul, de aceea heap*
	if (heap->dim > 0) {
		Mail extras = (*heap).vector[0];

		Mail* aux = (Mail*)malloc(sizeof(Mail) * ((*heap).dim - 1));

		for (int i = 1; i < heap->dim; i++) { //i=1 pt ca sarim pt primul elem care este maximul
			aux[i - 1] = heap->vector[i];
		}

		free(heap->vector);
		heap->vector = aux;
		heap->dim--;

		///dupa fiecare extragere trebuie sa refiltram
		for (int i = (heap->dim - 2) / 2; i >= 0; i--) {
			filtrareHeap((*heap), i);
		}

		return extras;
	}
}

void inserareMailInHeap(Heap* heap, Mail mail) {
	Mail* aux = (Mail*)(malloc(sizeof(Mail) * (heap->dim + 1)));
	aux[0] = mail; //il adaug la inceput
	for (int i = 1; i < heap->dim+1; i++) {
		aux[i] = heap->vector[i-1];
	}
	free(heap->vector);
	heap->vector = aux;
	heap->dim++;

	//nu mai trebuie for ul cu filtrarea parintii pt ca avem deja pe prima pozitie
	filtrareHeap((*heap), 0);
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->dim; i++) {
		free(heap->vector[i].text);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->dim = 0;
}


void main() {
	Heap heap = initHeap(6);
	heap.vector[0] = initMail("Salut0", 7);
	heap.vector[1] = initMail("Salut1", 9);
	heap.vector[2] = initMail("Salut2", 3);
	heap.vector[3] = initMail("Salut3", 8);
	heap.vector[4] = initMail("Salut4", 6);
	heap.vector[5] = initMail("Salut5", 10);

	afisareHeap(heap);

	//apelare filtrare de jos  in sus pt toti parintii

	for (int i = (heap.dim - 2) / 2; i >= 0; i--) {
		filtrareHeap(heap, i);
	}

	printf("\nAfisare dupa filtrare:\n\n");
	afisareHeap(heap);

	//de pref extragere in cadrul unor ob pe care sa le putem sterge
	printf("\nElem extrase:\n\n");
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));

	printf("\nInserare:\n\n");
	inserareMailInHeap(&heap, initMail("Buna", 6));
	inserareMailInHeap(&heap, initMail("Buna2", 10));
	inserareMailInHeap(&heap, initMail("Buna3", 4));
	afisareHeap(heap);

	dezalocareHeap(&heap);
	
}
