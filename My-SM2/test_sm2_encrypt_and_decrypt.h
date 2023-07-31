/**************************************************
* File name: test_sm2_encrypt_and_decrypt.h
* Author: HAN Wei，Healer(胡玉)
* Author's blog: https://blog.csdn.net/henter/, https://github.com/nudtyuyu
* Date: Aug 18th, 2022
* Description: declare SM2 encrypt data and decrypt
    ciphertext test functions
**************************************************/
#define C1_LENGTH 65
#define C3_LENGTH 32

#ifndef HEADER_SM2_ENCRYPT_DATA_AND_DECRYPT_CIPHERTEXT_TEST_H
  #define HEADER_SM2_ENCRYPT_DATA_AND_DECRYPT_CIPHERTEXT_TEST_H

#ifdef  __cplusplus
  extern "C" {
#endif

/**************************************************
* Name: test_with_input_defined_in_standard
* Function: test SM2 encrypt data and decrypt ciphertext
    with standard input from GM/T 0003.5-2012
* Return value:
    0:                test executes successfully
    any other value:  an error occurs
**************************************************/
int test_with_input_defined_in_standard(unsigned char msg[]);

/**************************************************
* Name: test_sm2_encrypt_and_decrypt
* Function: test SM2 encrypt data and decrypt ciphertext
* Return value:
    0:                test executes successfully
    any other value:  an error occurs
**************************************************/
int test_sm2_encrypt(void*data,void *encrypt,int count);
int test_sm2_decrypt(void* origin,void*secret,void *decrypt,int count);
#ifdef  __cplusplus
  }
#endif

#endif  /* end of HEADER_SM2_ENCRYPT_DATA_AND_DECRYPT_CIPHERTEXT_TEST_H */
