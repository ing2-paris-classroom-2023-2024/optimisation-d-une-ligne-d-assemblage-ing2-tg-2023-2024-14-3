#include "header_general.h"

int main() {
    setbuf(stdout, 0);
    char* jeu_donnees = "01";
    DATAS datas;
    SCANDATA(&datas,jeu_donnees);
    test_SCANDATA(&datas);
    return 0;
}
