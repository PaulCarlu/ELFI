// Carlu Paul - Martin Malo
//
#include <stdio.h>
#include <stdlib.h>
#include "allocmat.h"

void etiqAr(int typel, int n1, int n2, int nrefdom, const int *nrefcot, int nbtel, int nbaret, int **nRefAr) {
    for(int i=0; i<nbtel; i++) {
        for(int j=0; j<nbaret; j++) {
            nRefAr[i][j] = nrefdom;
        }
    }
    if (typel==1) {
        for (int i=0; i<(n1-1); i++) {
            nRefAr[i][3] = nrefcot[0];
            nRefAr[nbtel-1-i][1] = nrefcot[2];
        }
        for (int j=0; j<(n2-1); j++) {
            nRefAr[j*(n1-1)][2] = nrefcot[3];
            nRefAr[nbtel-1-j*(n1-1)][0] = nrefcot[1];
        }
    } else if (typel==2) {
        for (int i=0; i<(n1-1); i++) {
            nRefAr[2*i][2] = nrefcot[0];
            nRefAr[nbtel-1-2*i][2] = nrefcot[2];
        }
        for (int j=0; j<(n2-1); j++) {
            nRefAr[2*j*(n1-1)][1] = nrefcot[3];
            nRefAr[nbtel-1-2*j*(n1-1)][1] = nrefcot[1];
        }
    }
}

void maillage(char* nomFichierDonnees, char* nomFichierMaillage) {
    /* Ouverture du fichier de données */
    FILE* fichierDonnees = fopen(nomFichierDonnees, "r");
    if (!fichierDonnees) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    /* Lecture des données */
    float a,b,c,d;
    fscanf(fichierDonnees,"%f %f %f %f",&a,&b,&c,&d);
    int n1,n2,t;
    fscanf(fichierDonnees,"%d %d",&n1,&n2);
    fscanf(fichierDonnees,"%d",&t);
    int nrefdom; int nrefcot[4];
    fscanf(fichierDonnees,"%d %d %d %d %d\n",&nrefdom,&nrefcot[0],&nrefcot[1],&nrefcot[2],&nrefcot[3]);

    /* Fermeture du fichier de donnée */
    fclose(fichierDonnees);

    /* Création/Ouverture du fichier contenant le maillage */
    FILE* fichierMaillage = fopen(nomFichierMaillage, "w");
    if (!fichierMaillage) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    /* Ecriture du maillage dans le fichier dédié */
    fprintf(fichierMaillage,"%d\n",n1*n2);
    float h1 = (b-a)/(n1-1);   // pas sur entre chaque noeud pour n1
    float h2 = (d-c)/(n2-1);   // pas sur entre chaque noeud pour n2
    // Coordonnées des noeuds
    for(int j=0; j<n2; j++) {
        float y = c + j*h2;
        for(int i=0; i<n1; i++) {
            fprintf(fichierMaillage,"%f %f\n",a+i*h1,y);
        }
    }
    // Liste des numéros globaux des noeuds de chaque éléments
    if (t==1) {
        int p = 4;
        int q = 4;
        int m = (n1-1)*(n2-1);
        fprintf(fichierMaillage,"%d %d %d %d\n",m,t,p,q);
        // Allocation nRefAr
        int *alloc_nRefAr = (int*) malloc(m*q*sizeof(int));
        int **nRefAr = (int**) malloc(m*sizeof(int*));
        for(int k=0; k<m; k++) {
            nRefAr[k] = &alloc_nRefAr[k*q];
        }
        // Ecriture des donnees du maillage
        etiqAr(t,n1,n2,nrefdom,nrefcot,m,q,nRefAr);
        for(int j=1; j<n2; j++) {
            for(int i=1; i<n1; i++) {
                fprintf(fichierMaillage,"%d %d %d %d %d %d %d %d\n",(j-1)*n1+(i+1),j*n1+(i+1),j*n1+i,(j-1)*n1+i,
                        nRefAr[(j-1)*(n1-1)+(i-1)][0],nRefAr[(j-1)*(n1-1)+(i-1)][1],nRefAr[(j-1)*(n1-1)+(i-1)][2],nRefAr[(j-1)*(n1-1)+(i-1)][3]);
            }
        }
        free(*nRefAr);
    } else if (t==2) {
        int p = 3;
        int q = 3;
        int m = (n1-1)*(n2-1)*2;
        fprintf(fichierMaillage,"%d %d %d %d\n",m,t,p,q);
        // Allocation nRefAr
        int *alloc_nRefAr = (int*) malloc(m*q*sizeof(int));
        int **nRefAr = (int**) malloc(m*sizeof(int*));
        for(int k=0; k<m; k++) {
            nRefAr[k] = &alloc_nRefAr[k*q];
        }
        // Ecriture des donnees du maillage
        etiqAr(t,n1,n2,nrefdom,nrefcot,m,q,nRefAr);
        for(int j=1; j<n2; j++) {
            for(int i=1; i<n1; i++) {
                fprintf(fichierMaillage,"%d %d %d %d %d %d\n",(j-1)*n1+(i+1),j*n1+i,(j-1)*n1+i,
                        nRefAr[2*(j-1)*(n1-1)+2*(i-1)][0],nRefAr[2*(j-1)*(n1-1)+2*(i-1)][1],nRefAr[2*(j-1)*(n1-1)+2*(i-1)][2]);
                fprintf(fichierMaillage,"%d %d %d %d %d %d\n",j*n1+i,(j-1)*n1+(i+1),j*n1+(i+1),
                        nRefAr[2*(j-1)*(n1-1)+(i+(i-1))][0],nRefAr[2*(j-1)*(n1-1)+(i+(i-1))][1],nRefAr[2*(j-1)*(n1-1)+(i+(i-1))][2]);
            }
        }
        free(nRefAr[0]);
        free(nRefAr);
    }

    /* Fermeture du fichier de maillage*/
    fclose(fichierMaillage);
}

void lecfima(char *ficmai, int *p_typel, int *p_nbtng, float ***ppp_coord, int *p_nbtel, 
            int ***ppp_ngnel, int *p_nbneel, int *p_nbaret, int ***ppp_nRefAr) {
    /* Notations :
    - typel : type de l'élément géométrique
    - nbtng : nombre total de noeuds
    - nbtel : nombre total d'éléments
    - nbneel : nombre de noeuds sur un élément
    - nbaret : nombre d'arêtes sur un élément
    */
    FILE* fichierMaillage = fopen(ficmai, "r");
    if (!fichierMaillage) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fscanf(fichierMaillage,"%d",p_nbtng);

    /* Coordonnées */
    float **mat_coord = allocmatFLOAT(*p_nbtng,2);
    for (int i=0; i<*p_nbtng; i++) {
        fscanf(fichierMaillage,"%f %f",&mat_coord[i][0],&mat_coord[i][1]);
    }
    *ppp_coord = mat_coord;

    fscanf(fichierMaillage,"%d %d %d %d",p_nbtel,p_typel,p_nbneel,p_nbaret);

    /* Numéros globaux noeuds éléments + numéros globaux référence arêtes */
    int **mat_ngnel = allocmatINT(*p_nbtel,*p_nbneel);
    int **mat_nRefAr = allocmatINT(*p_nbtel,*p_nbaret);
    if (*p_typel == 1) {   // QUADRANGLE
        for(int i=0; i<*p_nbtel; i++) {
            fscanf(fichierMaillage,"%d %d %d %d %d %d %d %d",&mat_ngnel[i][0],&mat_ngnel[i][1],&mat_ngnel[i][2],&mat_ngnel[i][3],
                                                            &mat_nRefAr[i][0],&mat_nRefAr[i][1],&mat_nRefAr[i][2],&mat_nRefAr[i][3]);
        }
    } else if (*p_typel == 2) {   // TRIANGLE
        for(int i=0; i<*p_nbtel; i++) {
            fscanf(fichierMaillage,"%d %d %d %d %d %d",&mat_ngnel[i][0],&mat_ngnel[i][1],&mat_ngnel[i][2],
                                                       &mat_nRefAr[i][0],&mat_nRefAr[i][1],&mat_nRefAr[i][2]);
        }
    }
    *ppp_ngnel = mat_ngnel;
    *ppp_nRefAr = mat_nRefAr;

    fclose(fichierMaillage);
    }

void visualisation(int n, int t, int m, float **coord, int **ngnel, int **nRefAr) {
    printf("%d\n",n);
    for (int i=0; i<n; i++) {
        printf("%f %f\n",coord[i][0],coord[i][1]);
    }
    if (t == 1) {   // QUADRANGLE
        printf("%d %d %d %d\n",m,t,4,4);
        for(int i=0; i<m; i++) {
            printf("%d %d %d %d %d %d %d %d\n",ngnel[i][0],ngnel[i][1],ngnel[i][2],ngnel[i][3],
                                            nRefAr[i][0],nRefAr[i][1],nRefAr[i][2],nRefAr[i][3]);
        }
    } else if (t == 2) {   // TRIANGLE
        printf("%d %d %d %d\n",m,t,3,3);
        for(int i=0; i<m; i++) {
            printf("%d %d %d %d %d %d\n",ngnel[i][0],ngnel[i][1],ngnel[i][2],
                                        nRefAr[i][0],nRefAr[i][1],nRefAr[i][2]);
        }
    }
}
