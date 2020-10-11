#include "./common.h"

void adjust_WH(queue &q, buffer<real, 1> &b_W, buffer<real, 1> &b_Ht, int N, int M, int K) {
    q.submit([&](handler& cgh) {
        auto W = b_W.get_access<sycl_read_write>();

        cgh.parallel_for<class check_W>(range<2>(N, K), [=](id <2> ij){
            int i = ij[0];
            int j = ij[1];

            if(W[i*N + j] < eps)
                W[i*N + j] = eps;
        });
    });
	
    q.submit([&](handler& cgh) {
        auto Ht = b_Ht.get_access<sycl_read_write>();

        cgh.parallel_for<class check_Ht>(range<2>(M, K), [=](id <2> ij){
            int i = ij[0];
            int j = ij[1];

            if(Ht[i*M + j] < eps)
                Ht[i*M + j] = eps;
        });
    });	 
}


void V_div_WH(queue &q, buffer<real, 1> &b_V, buffer<real, 1> &b_WH, int N, int M) {
    q.submit([&](handler& cgh) {
        auto V = b_V.get_access<sycl_read>();
        auto WH = b_WH.get_access<sycl_read_write>();

        cgh.parallel_for<class div_matrix>(range<2>(N, M), [=](id <2> ij){
            int i = ij[0];
            int j = ij[1];

            WH[i*N + j] = V[i*N + j] / WH[i*N + j];
        });
    });
}


void mult_M_div_vect(queue &q, buffer<real, 1> &b_M, buffer<real, 1> &b_Maux, buffer<real, 1> &b_acc, int M, int K) {
    q.submit([&](handler& cgh) {
        auto Mat = b_M.get_access<sycl_read_write>();
        auto Maux = b_Maux.get_access<sycl_read>();
        auto acc = b_acc.get_access<sycl_read>();

        cgh.parallel_for<class mul_div_matrix>(range<2>(M, K), [=](id <2> ij){
            int i = ij[0];
            int j = ij[1];

            Mat[i*M + j] = Mat[i*M + j] * Maux[i*M + j] / acc[j];
        });
    });
}
