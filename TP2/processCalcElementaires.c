// Paul Carlu - Malo Martin

#include <stdio.h>
#include <stdlib.h>

float intElem(int t,float** coorEl){

    int nbneel;
    if (t==1){nbneel=4;}
    if (t==2){nbneel=3;}
    if (t==3){nbneel=2;}
    
    int q = valq(t);
    float* omegaquad[q];
    int dim = t==3?1:2;
    float** xquad[q][dim];
    ppquad(t,omegaquad,xquad);
    
    for (int i=0;i<q;i++){
        float* Fbase_x[nbneel];
        calFbase(t,xquad[i],Fbase_x);
        float** calDerFbase_x[nbneel][2];
        calDerFbase(t,xquad[i],calDerFbase_x);
        
        float* FK_x[2];
        transFK(nbneel, coorEl, Fbase_x, FK_x);
        float** JacFK_x[2][2];
        matJacob(dim, nbneel, coorEl, calDerFbase_x, JacFK_x);
        float** InvJacFK_x[2][2];
        float det;
        invertM2x2(JacFK_x,InvJacFK_x,&det);

        float** DerParFbase[nbneel][2];
        for(int i=0;i<nbneel;i++){
            DerParFbase[i][0] = calDerFbase[i][0]*InvJacFK_x[0][0] + calDerFbase[i][1]*InvJacFK_x[1][0];
            DerParFbase[i][1] = calDerFbase[i][0]*InvJacFK_x[0][1] + calDerFbase[i][1]*InvJacFK_x[1][1];
        }
    }

}