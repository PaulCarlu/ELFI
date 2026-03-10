#include <stdio.h>
#include <stdlib.h>
#include "cal1Elem.h"
#include "fonctionsUtilitaires.h"
#include "../TP1/lecfima.h"
#include "../TP1/allocmat.h"

int main() {
    char *ficmai = "maillage.txt";
    int typEl, nbtng, nbtel, nbneel, nbaret;
    float **coord; 
    int **ngnel, **nRefAr;
    /* Notations :
    - typEl : type de l'élément géométrique
    - nbtng : nombre total de noeuds
    - nbtel : nombre total d'éléments
    - nbneel : nombre de noeuds sur un élément
    - nbaret : nombre d'arêtes sur un élément
    */
    lecfima(ficmai,&typEl,&nbtng,&coord,&nbtel,&ngnel,&nbneel,&nbaret,&nRefAr);

    // Appel de cal1Elem
    cal1Elem(nbneel,nRefDom,nbRefD0,numRefD0,nbRefD1,numRefD1,nbRefF1,numRefF1,typEL,coorEl,nbaret,nRefArEl,MatElem,SMbrElem,NuDElem,uDElem);
    
    // Appel de impCalEl pour vérifier les calculs
    impCalEl(K,typEl,nbneel,MatElem,SMbrElem,NuDElem,uDElem);

    return 0;
}