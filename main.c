#include "header_general.h"

int main() {
    setbuf(stdout, 0);
    char* jeu_donnees = "01";
    DATAS datas = SCANDATAS(jeu_donnees);
    printf("TESTF");
    printf("EXCLUSIONS :\n");
    for(int i = 0; i < datas.EXCLUSIONS_TOT; i++){
        printf("%d :\t%d\t%d\n", i, datas.EXCLUSIONS[i][0], datas.EXCLUSIONS[i][1]);
    }
    printf("\nPRECEDENCES :\n");
    for(int i = 0; i < datas.PRECEDENCES_TOT; i++){
        printf("%d :\t%d\t%d\n", i, datas.PRECEDENCES[i][0], datas.PRECEDENCES[i][1]);
    }
    printf("\nOPERATIONS :\n");
    for(int i = 0; i < datas.OPERATIONS_TOT; i++){
        printf("%d :\t%d\t%d\n", i, datas.OPERATIONS[i][0], datas.OPERATIONS[i][1]);
    }
    printf("\nTCYCLE : \n");
    printf("%d\n", datas.TCYCLE);
    return 0;
}
