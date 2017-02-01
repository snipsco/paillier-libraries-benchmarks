#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include "paillier.h"

#ifdef CLOCK_PROCESS_CPUTIME_ID
/* cpu time in the current process */
#define CLOCKTYPE  CLOCK_PROCESS_CPUTIME_ID
#else
/* this one should be appropriate to avoid errors on multiprocessors systems */
#define CLOCKTYPE  CLOCK_MONOTONIC
#endif

#define ROUNDS 10


typedef struct PARAMS_BENCH {
    int modulusbits;
    paillier_pubkey_t* pub;
    paillier_prvkey_t* prv;
    paillier_plaintext_t *plaintext;
    paillier_ciphertext_t *ciphertext1;
    paillier_ciphertext_t *ciphertext2;
    paillier_ciphertext_t *ciphertext_result;
} paillier_params_t;

/* Function to time other functions */
/* eg: void *identity(void *) { } */

double time_it(void (*action)(void *arg), void* arg)
{
    struct timespec tsi, tsf;
    clock_gettime(CLOCKTYPE, &tsi);
    action(arg);
    clock_gettime(CLOCKTYPE, &tsf);
    
    double elaps_s = difftime(tsf.tv_sec, tsi.tv_sec);
    long elaps_ns = tsf.tv_nsec - tsi.tv_nsec;
    return elaps_s + ((double)elaps_ns) / 1.0e9;
}


double avg_time(double in_arr[]) {
    double sum = 0;
    for(int i = 0; i<ROUNDS; i++)
        sum += in_arr[i];
    return sum/ROUNDS;
}


/* Benchmarks */

void bench_paillier_keygen(void *params) {
    paillier_params_t *my_params = (paillier_params_t *)params;
    paillier_keygen(my_params->modulusbits, &(my_params->pub), &(my_params->prv), paillier_get_rand_devurandom);
}

void bench_paillier_encryption(void *params) {
    paillier_params_t *my_params = (paillier_params_t *)params;
    paillier_enc(&(my_params->ciphertext1), my_params->pub, my_params->plaintext, paillier_get_rand_devurandom);
}

void bench_paillier_decryption(void *params) {
    paillier_params_t *my_params = (paillier_params_t *)params;
    paillier_dec(&(my_params->plaintext), my_params->pub, my_params->prv, my_params->ciphertext1);
}

void bench_paillier_multiplication(void *params) {
    paillier_params_t *my_params = (paillier_params_t *)params;
    paillier_mul(&(my_params->ciphertext_result), my_params->pub, my_params->ciphertext1, my_params->ciphertext2);
}





double test_keygen(int bitlength) {
    paillier_params_t *params = (paillier_params_t *)malloc(sizeof(paillier_params_t));
    params->modulusbits = bitlength;
    
    double keygen_times[ROUNDS];
    for(int i = 0; i<ROUNDS; i++) {
        keygen_times[i] = time_it(bench_paillier_keygen, (void*)params);
        paillier_freepubkey(params->pub);
        paillier_freeprvkey(params->prv);
    }
    free(params);
    return avg_time(keygen_times);
}


double test_encryption_small(int bitlength){
    double small_encryption_times[ROUNDS];
    
    paillier_params_t *my_params = (paillier_params_t *)malloc(sizeof(paillier_params_t));
    my_params->modulusbits = bitlength;
    paillier_keygen(my_params->modulusbits, &(my_params->pub), &(my_params->prv), paillier_get_rand_devurandom);
    my_params->plaintext = paillier_plaintext_from_ui(42);
    
    for(int i = 0; i<ROUNDS; i++){
        small_encryption_times[i] = time_it(bench_paillier_encryption, (void*)my_params);
        paillier_freeciphertext(my_params->ciphertext1);
    }
    paillier_freeplaintext(my_params->plaintext);
    paillier_freepubkey(my_params->pub);
    paillier_freeprvkey(my_params->prv);
    free(my_params);
    return avg_time(small_encryption_times);
}

double test_encryption_large(int bitlength){
    double encryption_times[ROUNDS];
    char *magic_number_str = "9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729";
    
    paillier_params_t *my_params = (paillier_params_t *)malloc(sizeof(paillier_params_t));
    my_params->modulusbits = bitlength;
    paillier_keygen(my_params->modulusbits, &(my_params->pub), &(my_params->prv), paillier_get_rand_devurandom);
    my_params->plaintext = paillier_plaintext_from_str(magic_number_str, 10);
    
    for(int i = 0; i<ROUNDS; i++){
        encryption_times[i] = time_it(bench_paillier_encryption, (void*)my_params);
        paillier_freeciphertext(my_params->ciphertext1);
    }
    paillier_freeplaintext(my_params->plaintext);
    paillier_freepubkey(my_params->pub);
    paillier_freeprvkey(my_params->prv);
    free(my_params);
    return avg_time(encryption_times);
}

double test_decryption_small(int bitlength){
    double small_decryption_times[ROUNDS];
    
    paillier_params_t *my_params = (paillier_params_t *)malloc(sizeof(paillier_params_t));
    my_params->modulusbits = bitlength;
    paillier_keygen(my_params->modulusbits, &(my_params->pub), &(my_params->prv), paillier_get_rand_devurandom);
    my_params->plaintext = paillier_plaintext_from_ui(42);
    paillier_enc(&(my_params->ciphertext1), my_params->pub, my_params->plaintext, paillier_get_rand_devurandom);
    
    for(int i = 0; i<ROUNDS; i++){
        small_decryption_times[i] = time_it(bench_paillier_decryption, (void*)my_params);
        paillier_freeplaintext(my_params->plaintext);
    }
    paillier_freeciphertext(my_params->ciphertext1);
    paillier_freepubkey(my_params->pub);
    paillier_freeprvkey(my_params->prv);
    free(my_params);
    return avg_time(small_decryption_times);
}

double test_decryption_large(int bitlength){
    double large_decryption_times[ROUNDS];
    char *magic_number_str = "9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729";
    
    paillier_params_t *my_params = (paillier_params_t *)malloc(sizeof(paillier_params_t));
    my_params->modulusbits = bitlength;
    paillier_keygen(my_params->modulusbits, &(my_params->pub), &(my_params->prv), paillier_get_rand_devurandom);
    my_params->plaintext = paillier_plaintext_from_str(magic_number_str, 10);
    paillier_enc(&(my_params->ciphertext1), my_params->pub, my_params->plaintext, paillier_get_rand_devurandom);
    
    
    for(int i = 0; i<ROUNDS; i++){
        large_decryption_times[i] = time_it(bench_paillier_decryption, (void*)my_params);
        paillier_freeplaintext(my_params->plaintext);
    }
    paillier_freeciphertext(my_params->ciphertext1);
    paillier_freepubkey(my_params->pub);
    paillier_freeprvkey(my_params->prv);
    free(my_params);
    return avg_time(large_decryption_times);
}


double test_multiplication(int bitlength){
    double multiplication_times[ROUNDS];
    char *magic_number_str = "9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729";
    
    paillier_params_t *my_params = (paillier_params_t *)malloc(sizeof(paillier_params_t));
    my_params->modulusbits = bitlength;
    paillier_keygen(my_params->modulusbits, &(my_params->pub), &(my_params->prv), paillier_get_rand_devurandom);
    
    my_params->plaintext = paillier_plaintext_from_ui(42);
    paillier_enc(&(my_params->ciphertext1), my_params->pub, my_params->plaintext, paillier_get_rand_devurandom);
    
    my_params->plaintext = paillier_plaintext_from_str(magic_number_str, 10);
    paillier_enc(&(my_params->ciphertext2), my_params->pub, my_params->plaintext, paillier_get_rand_devurandom);
    
    for(int i = 0; i<ROUNDS; i++){
        multiplication_times[i] = time_it(bench_paillier_multiplication, (void*)my_params);
        paillier_freeciphertext(my_params->ciphertext_result);
    }
    paillier_freeciphertext(my_params->ciphertext1);
    paillier_freeciphertext(my_params->ciphertext2);
    paillier_freepubkey(my_params->pub);
    paillier_freeprvkey(my_params->prv);
    free(my_params);
    return avg_time(multiplication_times);
}

void run_keygen_tests() {
    printf("KEYGEN(%d bits) AVG TIME: %lf ms\n", 1024, test_keygen(1024)*1000);
    printf("KEYGEN(%d bits) AVG TIME: %lf ms\n", 2048, test_keygen(2048)*1000);
    printf("KEYGEN(%d bits) AVG TIME: %lf ms\n", 3072, test_keygen(3072)*1000);
    printf("KEYGEN(%d bits) AVG TIME: %lf ms\n", 4096, test_keygen(4096)*1000);
}

void run_encryption_small_tests(){
    printf("ENCRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 1024, test_encryption_small(1024)*1000);
    printf("ENCRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 2048, test_encryption_small(2048)*1000);
    printf("ENCRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 3072, test_encryption_small(3072)*1000);
    printf("ENCRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 4096, test_encryption_small(4096)*1000);
}

void run_encryption_large_tests(){
    printf("ENCRYPTION LARGE (%d bits) AVG TIME: %lf ms\n", 1024, test_encryption_large(1024)*1000);
    printf("ENCRYPTION LARGE (%d bits) AVG TIME: %lf ms\n", 2048, test_encryption_large(2048)*1000);
    printf("ENCRYPTION LARGE (%d bits) AVG TIME: %lf ms\n", 3072, test_encryption_large(3072)*1000);
    printf("ENCRYPTION RANDOM (%d bits) AVG TIME: %lf ms\n", 4096, test_encryption_large(4096)*1000);
}

void run_decryption_small_tests(){
    printf("DECRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 1024, test_decryption_small(1024)*1000);
    printf("DECRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 2048, test_decryption_small(2048)*1000);
    printf("DECRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 3072, test_decryption_small(3072)*1000);
    printf("DECRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 4096, test_decryption_small(4096)*1000);
}

void run_decryption_large_tests(){
    printf("DECRYPTION LARGE (%d bits) AVG TIME: %lf ms\n", 1024, test_decryption_large(1024)*1000);
    printf("DECRYPTION LARGE (%d bits) AVG TIME: %lf ms\n", 2048, test_decryption_large(2048)*1000);
    printf("DECRYPTION LARGE (%d bits) AVG TIME: %lf ms\n", 3072, test_decryption_large(3072)*1000);
    printf("DECRYPTION LARGE (%d bits) AVG TIME: %lf ms\n", 4096, test_decryption_large(4096)*1000);
}

void run_multiplication_tests(){
    printf("MULTIPLICATION (%d bits) AVG TIME: %lf ms\n", 1024, test_multiplication(1024)*1000);
    printf("MULTIPLICATION (%d bits) AVG TIME: %lf ms\n", 2048, test_multiplication(2048)*1000);
    printf("MULTIPLICATION (%d bits) AVG TIME: %lf ms\n", 3072, test_multiplication(3072)*1000);
    printf("MULTIPLICATION (%d bits) AVG TIME: %lf ms\n", 4096, test_multiplication(4096)*1000);
}


int main(int argc, char **argv){
    run_keygen_tests();
    run_encryption_small_tests();
    run_encryption_large_tests();
    run_decryption_small_tests();
    run_decryption_large_tests();
    run_multiplication_tests();
    return 0;
}
