#include <stdlib.h>

void ppquad(int t, float *romega, float **rx){

	if (t==1){
		for(int k=0;k<3;k++){romega[k] = 1/36;}
		for(int k=4;k<7;k++){romega[k] = 1/9;}
		romega[8]= 4/9;

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
                for(int k=0;k<3;k++){romega[k] = 1/6;}

                rx[0][0] = 0.5, rx[0][1] = 0.5;
                rx[1][0] = 0, rx[1][1] = 0.5;
                rx[2][0] = 0.5, rx[2][1] = 0;
        }

	else if(t==3){
		romega[0] = 1/6, romega[1] = 1/6, romega[2] = 2/3;


                rx[0][0] = 1;
                rx[1][0] = 0;
                rx[2][0] = 0.5;
        }



}

int valq(int t){

	int q = 0;
	if(t==1){q=9;}
	else if(t==2 || t==3){q=3;}

	return q;

}

void calFbase(int t, float* x, float* Fbase){

	if (t==1){
		Fbase[0] = x[0] - x[0]*x[1];
		Fbase[1] = x[0]*x[1];
		Fbase[2] = x[1] - x[0]*x[1];
		Fbase[0] = 1 -x[1] - x[0] + x[0]*x[1];
	}

	if (t==2){
		Fbase[0] = x[0];
		Fbase[1] = x[1];
		Fbase[2] = 1 - x[0]*x[1];
	}

	if (t==3){
		Fbase[0] = x[0];
		Fbase[1] = 1 - x[0];
	}
	
}


float* calDerFbase(int t, float* x, float** d_Fbase){

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

	if (t==2){
		d_Fbase[0][0] = 1;
		d_Fbase[0][1] = 0;

		d_Fbase[1][0] = 0;
		d_Fbase[1][1] = 1;
		
		d_Fbase[2][0] = -x[1];
		d_Fbase[2][1] = -x[0];
	}

	if (t==3){
		d_Fbase[0][0] = 1;

		d_Fbase[1][0] = -1;
	}
}

void (int d, int p,float**, coordFK float** d_Fbase, float** JacFK){

	if (d == 1){

		JacFK[0][0] = 0;
		JacFK[1][0] = 0;
		
		for (int i=0; i<p; i++){
			JacFK[0][0] = JacFK[0][0] + d_Fbase[i][0]*coordFK[i][0];
			JacFK[1][0] = JacFK[1][0] + d_Fbase[i][0]*coordFK[i][1];
		}
	}

	else if (d == 2){

		JacFK[0][0] = 0;
		JacFK[0][1] = 0;

		JacFK[1][0] = 0;
		JacFK[1][1] = 0;
		
		for (int i=0; i<p; i++){
			JacFK[0][0] = JacFK[0][0] + d_Fbase[i][0]*coordFK[i][0];
			JacFK[0][1] = JacFK[0][1] + d_Fbase[i][1]*coordFK[i][0];
			
			JacFK[1][0] = JacFK[1][0] + d_Fbase[i][0]*coordFK[i][1];
			JacFK[1][1] = JacFK[1][1] + d_Fbase[i][1]*coordFK[i][1];
		}
	}
}

void invertM2x2(float** A, float** InvA, float det){

	det = A[0][0]*A[1][1] - A[1][0]*A[0][1]

	if(fabs(det)<0.0000000001){
		printf("Le déterminant vaut en valeur absolue : \f <1e-10",&det);
		printf("C'est trop proche de 0 pour que la matrice soit considérée comme inversible");
		exit(EXIT_FAILURE);
	}

	else{
		invDet = 1/det;
		InvA[0][0] = invDet*A[1][1];
		InvA[0][1] = -invDet*A[0][1];
		InvA[1][0] = -invDet*A[1][0];
		InvA[1][1] = invDet*A[0][0];
	}
}

void numNaret(int t, int Naret, int* numPnts_Naret){

	if (t==1){

		if(Naret==1){
			numPnts_Naret[0] = 1;
			numPnts_Naret[1] = 2;
		}
		
		if(Naret==2){
			numPnts_Naret[0] = 2;
			numPnts_Naret[1] = 3;
		}

		if(Naret==3){
			numPnts_Naret[0] = 3;
			numPnts_Naret[1] = 4;
		}

		if(Naret==4){
			numPnts_Naret[0] = 4;
			numPnts_Naret[1] = 1;
		}
	}

	else if (t==2){

		if(Naret==1){
			numPnts_Naret[0] = 1;
			numPnts_Naret[1] = 2;
		}
		
		if(Naret==2){
			numPnts_Naret[0] = 2;
			numPnts_Naret[1] = 3;
		}

		if(Naret==3){
			numPnts_Naret[0] = 3;
			numPnts_Naret[1] = 1;
		}
	}
}