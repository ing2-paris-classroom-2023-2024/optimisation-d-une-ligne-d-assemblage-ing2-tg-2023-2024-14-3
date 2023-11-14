#include "header_general.h"

void SCANDATA(DATAS* datas,char* jeu_donnees){
    //      -- FONCTION DE CHARGEMENT DES DONNEES
    //      JEU_DONNEES : Numéro du jeu de données
    //      || RETURN :   Structure de valeurs

    char* exclusions = (char*) malloc( 40*sizeof(char));
    nom_fichiers(exclusions,jeu_donnees,1);
    char* operations = (char*) malloc(40* sizeof(char));
    nom_fichiers(operations,jeu_donnees,2);
    char* precedences = (char*) malloc(40* sizeof(char));
    nom_fichiers(precedences,jeu_donnees,3);
    char* temps_cycle = (char*) malloc(40* sizeof(char));
    nom_fichiers(temps_cycle,jeu_donnees,0);
    int count;

    FILE* fichier1 = fopen(exclusions, "rw+");
    FILE* fichier2 = fopen(operations, "rw+");
    FILE* fichier3 = fopen(precedences, "rw+");
    FILE* fichier4 = fopen(temps_cycle, "rw+");
    if(fichier1==NULL){
        printf("Ouverture impossible\n");
    }
    count = 0;
    while(!feof(fichier1)){
        datas->EXCLUSION = (DATA*) malloc( (count+1)*sizeof(DATA) );
        fscanf(fichier1, "%d %d\n", &(datas->EXCLUSION[count].nb), &(datas->EXCLUSION[count].i));
        count++;
    }
    datas->EXCLUSION_TOT = count;
    fclose(fichier1);
}

void test_SCANDATA(DATAS* inst){
    for (int i = 0; i < inst->EXCLUSION_TOT; i++) {
        printf("%d  %d \n",inst->EXCLUSION[i].nb,inst->EXCLUSION[i].i);
    }
}

void nom_fichier(char* chemin,char* jeu_donnees,int num){
    /*
     * Rempli les infos pour les variables utilisés pour les FILE| fopen| fclose
     * chemin : valeur remplie pour le chemin du fichier
     * jeu_donnee : combinaison de 2 chiffres pour identifier les données
     * num : numéro pour savoir quel fichier :
     * 0 : temps | 1 : exclusions | 2 operations | 3 : précédences
     */
    strcpy(chemin, "../fichiers_ressources/");
    strcat(chemin, jeu_donnees);
    strcat(chemin, "/");
    switch (num) {
        case 0:
            strcat(chemin,"temps_cycle");
            break;
        case 1:
            strcat(chemin,"exclusions");
            break;
        case 2:
            strcat(chemin,"operations");
            break;
        case 3:
            strcat(chemin,"precedences");
            break;
        default:
            break;
    }
    strcat(chemin, ".txt");
}