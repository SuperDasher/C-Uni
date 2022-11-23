#include <custom/string.h>
#include <custom/datastruct.h>

#define STR_LEN 100
#define EXAMS 5

struct esame
{
	char nome_corso[STR_LEN];
	char cognome_docente[STR_LEN];
	int numero_cfu;
	int voto;
};

void input_esame(struct esame *);
void stampa_esame(struct esame);
int sum_func(int, int);

int main()
{
	struct esame e[EXAMS];
	for (int i = 0; i < EXAMS; i++)
	{
		printf("inserisci i dati dell'esame n.%d:\n", i + 1);
		input_esame(&e[i]);
	}
	for (int i = 0; i < EXAMS; i++)
	{
		printf("i dati dell'esame n.%d sono:\n", i + 1);
		stampa_esame(e[i]);
	}

	int voti[EXAMS];
	for (int i = 0; i < EXAMS; i++)
		voti[i] = e[i].voto;
	int sum = reduce_a(sum_func, voti, EXAMS);
	printf("la media dei voti e': %.2f\n", (float)sum / EXAMS);

	return 0;
}

void input_esame(struct esame *esame)
{
	printf("Nome corso: ");
	inputstring(esame->nome_corso, STR_LEN);
	printf("Cognome docente: ");
	inputstring(esame->cognome_docente, STR_LEN);
	printf("Numero CFU: ");
	scanf("%d", &esame->numero_cfu);
	printf("Voto: ");
	scanf("%d", &esame->voto);
}

void stampa_esame(struct esame e)
{
	printf("Nome corso: %s\n", e.nome_corso);
	printf("Cognome docente: %s\n", e.cognome_docente);
	printf("Numero CFU: %d\n", e.numero_cfu);
	printf("Voto: %d\n", e.voto);
}

int sum_func(int a, int b)
{
	return a + b;
}
