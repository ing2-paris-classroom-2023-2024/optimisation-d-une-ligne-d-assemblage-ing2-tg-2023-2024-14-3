#include "header_general.h"

int main() {
    /*
     * Fonction main qui exécute les différents sous programme
     * La variable jeu_donnees permet de facilement passer d'un jeu de donnée à un autre
     * */
    setbuf(stdout, 0);
    char* jeu_donnees = "04";
    DATAS datas = SCANDATAS(jeu_donnees);

    DISPDATAS(datas);

    DATASET dataset = DATASORT(datas);
    DISPDATASET(dataset);

    // Pour la version alternative :
    //ALGO2(dataset);
    ALGO(dataset);

    FREEDATASET(dataset);
    return 0;

}