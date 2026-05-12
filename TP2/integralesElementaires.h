/* 
Paul Carlu - Malo Martin 
Université de Rennes 
Master 1 CSM
Module - Elements finis
*/

void W(int nbneel, float *Fbase, float eltdif, float cofvar, float *vecelm);
void WW(int nbneel, float *Fbase, float eltdif, float cofvar, float **matelm);
void ADWDW(int nbneel, float **DerParFbase, float eltdif, float **cofvar, float **matelm);