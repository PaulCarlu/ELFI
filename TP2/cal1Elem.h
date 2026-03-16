// Carlu Paul - Martin Malo
//

void cal1Elem(int nbneel, int nRefDom, int nbRefD0, int* numRefD0, int nbRefD1, int* numRefD1, int nbRefF1, int* numRefF1, int typEL,
              float** coorEl, int nbaret, int* nRefArEl, float** MatElem, float* SMbrElem, int* NuDElem, float* uDElem);
void impCalEl(int K, int typEl, int nbneel, float **MatElem, float *SMbrElem,
              int *NuDElem, float *uDElem);