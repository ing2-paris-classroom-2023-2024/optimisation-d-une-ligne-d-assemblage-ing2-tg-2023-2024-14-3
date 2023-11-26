#include "header_general.h"

int main() {
    setbuf(stdout, 0);
    char* jeu_donnees = "03";
    scanf("%s", jeu_donnees);
    DATAS datas = SCANDATAS(jeu_donnees);
    //DISPDATAS(datas);
    DATASET dataset = DATASORT(datas);
    DISPDATASET(dataset);

    ALGO(dataset);

    FREEDATASET(dataset);
    return 0;
}