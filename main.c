#include "header_general.h"

int main() {
    setbuf(stdout, 0);
    char* jeu_donnees = "03";
    DATAS datas = SCANDATAS(jeu_donnees);

    DISPDATAS(datas);
    // Pour la version alternative : ALGO2

    DATASET dataset = DATASORT(datas);
    DISPDATASET(dataset);

    ALGO(dataset);

    FREEDATASET(dataset);
    return 0;
}