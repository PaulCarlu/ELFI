// Carlu Paul - Martin Malo
//
#include <stdlib.h>

void ppquad(int t, float *romega, float **rx){
	/*
	Renvoie les poids et points de quadrature selon le type de l'élément
	 
	En entrée :
	- t : type de l'élément (1 quadrangle, 2 triangle, 3 segment) 
	En sortie :
	- romega : vecteur des poids de quadrature
	- rx : matrice de coordonnées des points de quadrature
	*/
	if (t==1){
		for(int k=0;k<3;k++){romega[k] = 1.0/36;}
		for(int k=4;k<7;k++){romega[k] = 1.0/9;}
		romega[8]= 4.0/9;

		rx[0][0] = 1, rx[0][1] = 0;
		rx[1][0] = 1, rx[1][1] = 1;
		rx[2][0] = 0, rx[2][1] = 1;
		rx[3][0] = 0, rx[3][1] = 0;
		rx[4][0] = 1, rx[4][1] = 0.5;
		rx[5][0] = 0.5, rx[5][1] = 1;
		rx[6][0] = 0, rx[6][1] = 0.5;
		rx[7][0] = 0.5, rx[7][1] = 0;
		rx[8][0] = 0.5, rx[8][1] = 0.5;
	}
	else if(t==2){
        for(int k=0;k<3;k++){ romega[k] = 1.0/6; }
        rx[0][0] = 0.5, rx[0][1] = 0.5;
        rx[1][0] = 0, rx[1][1] = 0.5;
        rx[2][0] = 0.5, rx[2][1] = 0;
    }
	else if(t==3){
		romega[0] = 1.0/6, romega[1] = 1.0/6, romega[2] = 2.0/3;
        rx[0][0] = 1;
        rx[1][0] = 0;
        rx[2][0] = 0.5;
    }
}

int valq(int t){
	/*
	Renvoie le nombre de poids et points de quadrature selon le type géométrique de l'élément

	En entrée : 
	- t : type de l'élément (1 quadrangle, 2 triangle, 3 segment) 
	En sortie : 
	- q : nombre de poids et points de quadrature
	*/
	int q = 0;
	if(t==1){ q=9; }
	else if(t==2 || t==3){ q=3; }
	return q;
}

void calFbase(int t, float* x, float* Fbase){
	/*
	Calcul la valeur en un point des fonctions de base associées à l'élément de référence

	En entrée :
	- t : type de l'élément de référence (1 quadrangle, 2 triangle, 3 segment)
	- x : vecteur de coordonnées du point à évaluer
	En sortie : 
	- Fbase : vecteur contenant les valeurs des fonctions de base calculées au point x
	*/
	if (t==1){
		Fbase[0] = x[0] - x[0]*x[1];
		Fbase[1] = x[0]*x[1];
		Fbase[2] = x[1] - x[0]*x[1];
		Fbase[3] = 1 -x[1] - x[0] + x[0]*x[1];
	}
	else if (t==2){
		Fbase[0] = x[0];
		Fbase[1] = x[1];
		Fbase[2] = 1 - x[0]*x[1];
	}
	else if (t==3){
		Fbase[0] = x[0];
		Fbase[1] = 1 - x[0];
	}
}

void calDerFbase(int t, float* x, float** d_Fbase){
	/*
	Calcul la valeur en un point des dérivées des fonctions de base associées à l'élément de référence

	En entrée :
	- t : type de l'élément de référence (1 quadrangle, 2 triangle, 3 segment)
	- x : vecteur de coordonnées du point à évaluer
	En sortie : 
	- d_Fbase : matrice contenant les valeurs des dérivées des fonctions de base calculées au point x
	*/
	if (t==1){
		d_Fbase[0][0] = 1 - x[1];
		d_Fbase[0][1] = x[0];
		d_Fbase[1][0] = x[1];
		d_Fbase[1][1] = x[0];
		d_Fbase[2][0] = -x[1];
		d_Fbase[2][1] = 1 - x[0];
		d_Fbase[3][0] = -1 + x[1];
		d_Fbase[3][1] = 1 + x[0];
	}
	else if (t==2){
		d_Fbase[0][0] = 1;
		d_Fbase[0][1] = 0;
		d_Fbase[1][0] = 0;
		d_Fbase[1][1] = 1;
		d_Fbase[2][0] = -x[1];
		d_Fbase[2][1] = -x[0];
	}
	else if (t==3){
		d_Fbase[0][0] = 1;
		d_Fbase[1][0] = -1;
	}
}

void transFK(int q, float **a, float *Fbase, float *FK) {
	/*
	Calcul l'image d'un point de l'élément de référence par la transformation notée FK :
	FK = [somme sur i de 1 à q] des (i fonctions de base calculer au point souhaité) * (coordonnées des noeuds géométriques)

	En entrée : 
	- q : nombre de poids et points de quadrature
	- a : matrice contenant les coordonnées des noeuds géométriques
	- Fbase : vecteur des valeurs des fonctions de base au point souhaité
	En sortie :
	- FK : vecteur qui contient le résultat de la transformation 
	*/
	FK[0] = 0; FK[1] = 0;
	for (int i=0; i<q; i++) {
		FK[0] += Fbase[i]*a[i][0];
		FK[1] += Fbase[i]*a[i][1];
	}
}

void matJacob(int d, int p, float** coordFK, float** d_Fbase, float** JacFK){
	/*
	Calcul la matrice jacobienne de la transformation FK

	En entrée :
	- d : dimension de l'ensemble de départ de FK (1 segment, 2 triangle/quadrangle)
	- p : nombre de fonctions de bases
	- coordFK : matrice des coordonnées des noeuds géométriques
	- d_Fbase : matrices des valeurs des dérivées des fonctions de base au point souhaité
	En sortie : 
	- JacFK : matrice contenant la jacobienne de la transformation FK
	*/
	if (d == 1){
		JacFK[0][0] = 0;
		JacFK[1][0] = 0;
		for (int i=0; i<p; i++){
			JacFK[0][0] += d_Fbase[i][0]*coordFK[i][0];
			JacFK[1][0] += d_Fbase[i][0]*coordFK[i][1];
		}
	}
	else if (d == 2){
		JacFK[0][0] = 0;
		JacFK[0][1] = 0;
		JacFK[1][0] = 0;
		JacFK[1][1] = 0;
		for (int i=0; i<p; i++){
			JacFK[0][0] += d_Fbase[i][0]*coordFK[i][0];
			JacFK[0][1] += d_Fbase[i][1]*coordFK[i][0];
			JacFK[1][0] += d_Fbase[i][0]*coordFK[i][1];
			JacFK[1][1] += d_Fbase[i][1]*coordFK[i][1];
		}
	}
}

void invertM2x2(float** A, float** InvA, float det){
	/*
	Renvoie le déterminant d'une matrice de taille 2x2 ainsi que son inverse

	En entrée :
	- A : matrice de taille 2x2 à inverser
	En sortie :
	- InvA : matrice inverse de A
	- det : déterminant de la matrice A
	*/
	det = A[0][0]*A[1][1] - A[1][0]*A[0][1];
    // Critère d'inversibilité : 1e-10
	if(fabs(det)<0.0000000001){
		printf("Le déterminant vaut en valeur absolue : \f <1e-10",&det);
		printf("C'est trop proche de 0 pour que la matrice soit considérée comme inversible");
		exit(EXIT_FAILURE);
	}
	else{
		float invDet = 1/det;
		InvA[0][0] = invDet*A[1][1];
		InvA[0][1] = -invDet*A[0][1];
		InvA[1][0] = -invDet*A[1][0];
		InvA[1][1] = invDet*A[0][0];
	}
}

void numNaret(int t, int Naret, int* numPnts_Naret){
	/*
	Renvoie la liste des numéros locaux des noeuds qui sont situés sur une arête de numéro donné sur l'élément de référence

	En entrée :
	- t : type de l'élément de référence (1 quadrangle, 2 triangle)
	- Naret : numéro de l'arête sur l'élément de référence 
	En sortie :
	- numPnts_Naret : vecteur des numéros locaux des noeuds situés sur l'arête numéro 'Naret'
	*/
	if (t==1){
		if(Naret==1){
			numPnts_Naret[0] = 1;
			numPnts_Naret[1] = 2;
		}
		else if(Naret==2){
			numPnts_Naret[0] = 2;
			numPnts_Naret[1] = 3;
		}
		else if(Naret==3){
			numPnts_Naret[0] = 3;
			numPnts_Naret[1] = 4;
		}
		else if(Naret==4){
			numPnts_Naret[0] = 4;
			numPnts_Naret[1] = 1;
		}
	}
  
	else if (t==2){
		if(Naret==1){
			numPnts_Naret[0] = 1;
			numPnts_Naret[1] = 2;
		}
		else if(Naret==2){
			numPnts_Naret[0] = 2;
			numPnts_Naret[1] = 3;
		}
		else if(Naret==3){
			numPnts_Naret[0] = 3;
			numPnts_Naret[1] = 1;
		}
	}
}

void selectPts(int nb, int num[], float *coorEns[], float *coorSel[]) {
	/*
	Sélectionne un nombre 'nb' de points donnés dans 'num' parmi l'ensemble des coordonnées 'coorEns'

	En entrée :
	- nb : nombre de points à sélectionner
	- num : vecteur des numéros des noeuds qui doivent être sélectionnés
	- coorEns : vecteur de pointeurs qui renvoie vers les coordonnées des noeuds 
	En sortie :
	- coorSel : vecteur de pointeurs qui renvoie vers les coordonnées des noeuds sélectionnés dans 'num'
	*/
	for (int i=0; i<nb; i++) {
		coorSel[i] = coorEns[num[i]-1];
  }
}
