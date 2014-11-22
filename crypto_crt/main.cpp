#include <iostream>
#include <time.h>

#include <polarSSL/aes.h>
#include <polarSSL/aesni.h>
#include <polarSSL/check_config.h>
#include <polarSSL/config.h>
#include <polarSSL/padlock.h>
#include <polarSSL/platform.h>
#include "polarssl/ctr_drbg.h"
#include <polarSSL/entrophy.h>

using namespace std;

/**
 * \brief   function to compute table to xor, key and nonce must be same in both side!
 *
 * \param key                       key - symetric key used by both part
 * \param nonce_counter[out]        counter, be carefull, couter is changed by computation
 * \param output[out]               table to xor
 * \param table_length              required length of generated tabl
 *
 */
void ctr_prepare_table(
                        unsigned char key[32],
                        unsigned char nonce_counter[16],
                        unsigned char** output,
                        int table_length
                        )
{
    unsigned char* input = NULL;
    aes_context aes;
    unsigned char stream_block[16];
    size_t nc_off = 0;

    input = (unsigned char*) malloc(table_length * sizeof(unsigned char));
    if (NULL == input)
    {   // ERROR
        printf("ERROR allocations ctr_prepare_table()");
    }
    // set all values in table to '0'
    memset(input, 48, table_length);

    (*output) = (unsigned char*) malloc(64 * sizeof(unsigned char));
    if (NULL == (*output)){
        // ERROR
        printf("ERROR allocations ctr_prepare_table()");
    }

    aes_setkey_enc(&aes, key, 128);
    aes_crypt_ctr(&aes, table_length, &nc_off, nonce_counter, stream_block, input, (*output));
}

/**
 * \brief   function to xor two *char of length
 *
 * \param output[out]               here is storred text after xoring
 * \param xor_table                 generated table to xor
 * \param input                     input to xor
 * \paramlength              length of char*'s to xor
 *
 */
void xor_table(
                        unsigned char* output,
                        unsigned char* xor_table,
                        unsigned char* input,
                        int length
              )
{
    for (int i = 0; i < length; i++){
        *(output+i) = *(input+i) ^ *(xor_table+i);
    }
}



int main()
{
    const int length_size = 64;

    // private key
    unsigned char key[32] = "private key";

    // nonce couters
    unsigned char nonce_counter[16];
    unsigned char nonce_counter2[16];

    // no secure generation of randoms
    srand(time(NULL));
    for (int i = 0; i < 16; i++) {
        nonce_counter[i] = (unsigned char) rand() % 256;
    }
    memcpy(nonce_counter2, nonce_counter, 16);

    unsigned char input[length_size] = "Hello  12345678901234567890";
    unsigned char output[length_size];
    unsigned char plaintext[length_size];

    //
    //  Test case 1 single enc./dec.
    //

    // compute fist table
    unsigned char* p_table = NULL;
    ctr_prepare_table(key, nonce_counter, &p_table, length_size);

    // XOR plain text with "cipher" table, result = cipher text
    xor_table(output, input, p_table, length_size);

    // compute second table
    unsigned char* p_table2 = NULL;
    ctr_prepare_table(key, nonce_counter2, &p_table2, length_size);

    xor_table(plaintext, output, p_table2, length_size);

    if (0 == strcmp((const char *) plaintext, (const char *) input))
    {
        printf("TEST CASE 1 - basic enc. and dec. ---- pass\n");
    } else
    {
        printf("TEST CASE 1 - basic enc. and dec. ---- failed\n");
    }
    return 0;
}

