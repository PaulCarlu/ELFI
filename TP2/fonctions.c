#include <stdlib.h>

void ppquad(int t, float *romega, float **rx){
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
	else if (t==2){
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
	int q = 0;
	if(t==1){ q=9; }
	else if(t==2 || t==3){ q=3; }
	return q;
}

void transFK(int q, float **a, float *Fbase, float *FK) {
	FK[0] = 0; FK[1] = 0;
	for (int i=0; i<q; i++) {
		FK[0] += Fbase[i]*a[i][0];
		FK[1] += Fbase[i]*a[i][1];
	}
}

void selectPts(int nb, int num[], float *coorEns[], float *coorSel[]) {
	for (int i=0; i<nb; i++) {
		coorSel[i] = coorEns[num[i]-1];
	}
}