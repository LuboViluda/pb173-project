#ifndef CRYPTO_HPP
#define CRYPTO_HPP

struct prepare_table
{
    unsigned char key[32];
    unsigned long int counter;  // should be initialize to zero
    unsigned char* p_table;
    int table_length;
};


void xor_table(unsigned char* output,
                        unsigned char* xor_table,
                        unsigned char* input,
                        unsigned int length
              );

void ecb_prepare_table(prepare_table *table);

void ctr_prepare_table(
                        unsigned char key[32],
                        unsigned char nonce_counter[16],
                        unsigned char** output,
                        int table_length
                        );


#endif // CRYPTO_HPP
