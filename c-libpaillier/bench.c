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


typedef struct KEYS {
    int modulusbits;
    paillier_pubkey_t* pub;
	paillier_prvkey_t* prv;
} paillier_keys_t;

typedef struct PARAM { 
    paillier_keys_t *keys;
    paillier_ciphertext_t *ciphertext;
    paillier_plaintext_t *plaintext;
} paillier_t;

typedef struct PARAM_MUL { 
    paillier_keys_t *keys;
    paillier_ciphertext_t *ciphertext1;
    paillier_ciphertext_t *ciphertext2;
    paillier_ciphertext_t *ciphertext_result;
} paillier_mul_t;



void test_paillier_keygen(void *keys) {
    paillier_keys_t *my_keys = (paillier_keys_t *)keys;
    paillier_keygen(my_keys->modulusbits, &(my_keys->pub), &(my_keys->prv), paillier_get_rand_devurandom);
}

void test_paillier_encryption_small(void *keys) {
    paillier_keys_t *my_keys = (paillier_keys_t *)keys;
    paillier_plaintext_t* magic_number;
    paillier_ciphertext_t* ciphertext;
    magic_number = paillier_plaintext_from_ui(45);
    paillier_enc(0, my_keys->pub, magic_number, paillier_get_rand_devurandom);
}

void test_paillier_encryption_random(void *keys) {
    paillier_keys_t *my_keys = (paillier_keys_t *)keys;
    paillier_plaintext_t* magic_number;
    char *magic_number_str = "9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729";
    magic_number = paillier_plaintext_from_str(magic_number_str);
    paillier_enc(0, my_keys->pub, magic_number, paillier_get_rand_devurandom);
}

void test_paillier_decryption(void *params) {
    paillier_t *my_params = (paillier_t *)params;
    paillier_plaintext_t* sum;
    paillier_dec(my_params->plaintext, my_params->keys->pub, my_params->keys->prv, my_params->ciphertext);
}

void test_paillier_multiplication(void *params) {
    paillier_mul_t *my_params = (paillier_mul_t *)params;
    paillier_mul(my_params->keys->pub, my_params->ciphertext_result, my_params->ciphertext1, my_params->ciphertext2);
}




/* Function to time other functions */ 
/* eg:  
void *identity(void *) { } 
*/
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




double test_keygen(int bitlength) {
    paillier_keys_t *keys = (paillier_keys_t *)malloc(sizeof(paillier_keys_t));
    keys->modulusbits = bitlength;
    double keygen_times[ROUNDS];
    for(int i = 0; i<ROUNDS; i++)
        keygen_times[i] = time_it(test_paillier_keygen, (void*)keys);
    free(keys);
    return avg_time(keygen_times);
}


double test_encryption_small(int bitlength){
    paillier_keys_t *keys = (paillier_keys_t *)malloc(sizeof(paillier_keys_t));
    keys->modulusbits = bitlength;
    paillier_keygen(keys->modulusbits, &(keys->pub), &(keys->prv), paillier_get_rand_devurandom);
    double small_encryption_times[ROUNDS];

    for(int i = 0; i<ROUNDS; i++){
        small_encryption_times[i] = time_it(test_paillier_encryption_small, (void*)keys);   
    }
    free(keys);
    return avg_time(small_encryption_times);
}

double test_encryption_random(int bitlength){
    paillier_keys_t *keys = (paillier_keys_t *)malloc(sizeof(paillier_keys_t));
    keys->modulusbits = bitlength;
    paillier_keygen(keys->modulusbits, &(keys->pub), &(keys->prv), paillier_get_rand_devurandom);
    double random_encryption_times[ROUNDS];

    for(int i = 0; i<ROUNDS; i++){
        random_encryption_times[i] = time_it(test_paillier_encryption_random, (void*)keys);   
    }
    free(keys);
    return avg_time(random_encryption_times);
}

double test_decryption_small(int bitlength){
    paillier_keys_t *keys = (paillier_keys_t *)malloc(sizeof(paillier_keys_t));
    keys->modulusbits = bitlength;
    paillier_keygen(keys->modulusbits, &(keys->pub), &(keys->prv), paillier_get_rand_devurandom);
    paillier_plaintext_t* magic_number;
    paillier_ciphertext_t* ciphertext;
    magic_number = paillier_plaintext_from_ui(42);
    ciphertext = paillier_enc(0, keys->pub, magic_number, paillier_get_rand_devurandom);

    paillier_t *params = (paillier_t *)malloc(sizeof(paillier_t));
    params->keys = keys;
    params->ciphertext = ciphertext;
    params->plaintext = magic_number;

    double small_decryption_times[ROUNDS];

    for(int i = 0; i<ROUNDS; i++){
        small_decryption_times[i] = time_it(test_paillier_decryption, (void*)params);
    }
    free(keys);
    free(params);
    return avg_time(small_decryption_times);
}

double test_decryption_random(int bitlength){
    paillier_keys_t *keys = (paillier_keys_t *)malloc(sizeof(paillier_keys_t));
    keys->modulusbits = bitlength;
    paillier_keygen(keys->modulusbits, &(keys->pub), &(keys->prv), paillier_get_rand_devurandom);
    paillier_plaintext_t* magic_number;
    paillier_ciphertext_t* ciphertext;
    char *magic_number_str = "9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729";
    magic_number = paillier_plaintext_from_str(magic_number_str);
    ciphertext = paillier_enc(0, keys->pub, magic_number, paillier_get_rand_devurandom);

    paillier_t *params = (paillier_t *)malloc(sizeof(paillier_t));
    params->keys = keys;
    params->ciphertext = ciphertext;
    params->plaintext = magic_number;

    double small_decryption_times[ROUNDS];

    for(int i = 0; i<ROUNDS; i++){
        small_decryption_times[i] = time_it(test_paillier_decryption, (void*)params);
    }
    free(keys);
    free(params);
    return avg_time(small_decryption_times);
}


double test_multiplication(int bitlength){
    paillier_keys_t *keys = (paillier_keys_t *)malloc(sizeof(paillier_keys_t));
    keys->modulusbits = bitlength;
    paillier_keygen(keys->modulusbits, &(keys->pub), &(keys->prv), paillier_get_rand_devurandom);
    paillier_plaintext_t* magic_number;
    paillier_plaintext_t* magic_number_random;
    paillier_ciphertext_t* ciphertext1;
    paillier_ciphertext_t* ciphertext2;
    magic_number = paillier_plaintext_from_ui(42);
    ciphertext1 = paillier_enc(0, keys->pub, magic_number, paillier_get_rand_devurandom);

    char *magic_number_str = "9601375721773960030826048348718350956180868954786249183055522621772391594913965263068361191091587324151101807311169301869981191762119859865346892157945421998951222949069729370836921713919282283633399891943869137940899827469813950721928452427835958620445001112962904065293585229146038515621140909326729";
    magic_number_random = paillier_plaintext_from_str(magic_number_str);
    ciphertext2 = paillier_enc(0, keys->pub, magic_number_random, paillier_get_rand_devurandom);

    paillier_mul_t *params = (paillier_mul_t *)malloc(sizeof(paillier_mul_t));
    paillier_ciphertext_t *result = (paillier_ciphertext_t *) malloc (sizeof(paillier_ciphertext_t));
    params->keys = keys;
    params->ciphertext1 = ciphertext1;
    params->ciphertext2 = ciphertext2;
    params->ciphertext_result = ciphertext2;  // change this! allocate space

    double multiplication_times[ROUNDS];

    for(int i = 0; i<ROUNDS; i++){
        multiplication_times[i] = time_it(test_paillier_multiplication, (void*)params);
    }
    free(keys);
    free(params);
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

void run_encryption_random_tests(){
    printf("ENCRYPTION RANDOM (%d bits) AVG TIME: %lf ms\n", 1024, test_encryption_random(1024)*1000);
    printf("ENCRYPTION RANDOM (%d bits) AVG TIME: %lf ms\n", 2048, test_encryption_random(2048)*1000);
    printf("ENCRYPTION RANDOM (%d bits) AVG TIME: %lf ms\n", 3072, test_encryption_random(3072)*1000);
    printf("ENCRYPTION RANDOM (%d bits) AVG TIME: %lf ms\n", 4096, test_encryption_random(4096)*1000);
}

void run_decryption_small_tests(){
    printf("DECRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 1024, test_decryption_small(1024)*1000);
    printf("DECRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 2048, test_decryption_small(2048)*1000);
    printf("DECRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 3072, test_decryption_small(3072)*1000);
    printf("DECRYPTION SMALL (%d bits) AVG TIME: %lf ms\n", 4096, test_decryption_small(4096)*1000);
}

void run_decryption_random_tests(){
    printf("DECRYPTION RANDOM (%d bits) AVG TIME: %lf ms\n", 1024, test_decryption_random(1024)*1000);
    printf("DECRYPTION RANDOM (%d bits) AVG TIME: %lf ms\n", 2048, test_decryption_random(2048)*1000);
    printf("DECRYPTION RANDOM (%d bits) AVG TIME: %lf ms\n", 3072, test_decryption_random(3072)*1000);
    printf("DECRYPTION RANDOM (%d bits) AVG TIME: %lf ms\n", 4096, test_decryption_random(4096)*1000);
}

void run_multiplication_tests(){
    printf("MULTIPLICATION (%d bits) AVG TIME: %lf ms\n", 1024, test_multiplication(1024)*1000);
    printf("MULTIPLICATION (%d bits) AVG TIME: %lf ms\n", 2048, test_multiplication(2048)*1000);
    printf("MULTIPLICATION (%d bits) AVG TIME: %lf ms\n", 3072, test_multiplication(3072)*1000);
    printf("MULTIPLICATION (%d bits) AVG TIME: %lf ms\n", 4096, test_multiplication(4096)*1000);
}


int main(int argc, char **argv)
{
    /* KEYGEN TESTS */
    //run_keygen_tests();


    //run_encryption_small_tests();
    //run_encryption_random_tests();
    //run_decryption_small_tests();
    //run_decryption_random_tests();
    run_multiplication_tests();
    
//    gmp_printf("The public key is: %Zd\n", &keys->pub->n);
    
	return 0;
}