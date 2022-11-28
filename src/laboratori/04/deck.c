#include <stdio.h>
#include <stdlib.h>

#define num_carte 52

typedef struct{
    char valore;
    char seme;
} carta;

//Lettura funziona correttamente
void lettura_binario(){
    char lett;
    carta deck [num_carte*2+1], estratt[21]; //mazzo come array tipo di tipo carta
    FILE *f;
    f = fopen("mazzoPolimi.bin", "rb");

    if(f == NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    else
    {
        int i = 0;
        while(fread(&deck[i], sizeof(carta), 1, f) == 1){
            i++;
        }
        fclose(f);

        printf("Mazzo in apertura:\n");
        for(int i = 0; i < num_carte; i++){
            printf("%c%c ", deck[i].valore, deck[i].seme);
        }
        printf("\n");
    }
}

void scrittura_binario(){                                   //@mssuperlol aiutaci tu
    FILE * f_w;
    f_w = fwrite("mazzoPolimi.bin", "wb");

    if(f_w == NULL){
        printf ("Il file non si apre.");
        exit(-1);
    }
    else
    {
        int i = 0;
        while(fwrite(&deck[i], sizeof(carta), 1, f_w) == 1){
            i++;
        }
        fclose(f);

        printf("\nMazzo così ottenuto:\n");
        for(int i = 0; i < num_carte; i++){
            printf("%c%c ", deck[i].valore, deck[i].seme);
        }
        printf("\n");
    }
}

int main(){
    lettura_binario();


    scrittura_binario();
    
    return 0;
}