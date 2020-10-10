#ifndef _BARE_
#define _BARE_

#include "common.h"

void W_mult_H(queue *q, buffer<real, 2> *b_WH, buffer<real, 2> *b_W, buffer<real, 2> *b_Htras, int N, int M, int K);
void accum(queue *q, buffer<real, 1> *b_acc, buffer<real, 2> *b_X, int N, int M);
void Wt_mult_WH(queue *q, buffer<real, 2> *b_Haux, buffer<real, 2> *b_W, buffer<real, 2> *b_WH, int N, int M, int K);
void WH_mult_Ht(queue *q, buffer<real, 2> *b_Waux, buffer<real, 2> *b_WH, buffer<real, 2> *b_Htras, int N, int M, int K);

#endif