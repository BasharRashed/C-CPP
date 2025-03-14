#include "tests.h"
#include <string.h>
#define K_1 3
#define K_2 2
#define K_3 -1
#define K_4 -3
#define K_5 29


// See full documentation in header file
int test_cipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  cipher (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "xy.,";
  char out[] = "za.,";
  cipher(in,K_2);
  return strcmp(in,out) != 0;

}

// See full documentation in header file
int test_cipher_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[]= "bc .";
  char out[] = "ab .";
  cipher(in , (K_3));
  return strcmp(in,out) !=0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_negative_k ()
{
    char in[]= "bc .";
    char out[] = "yz .";
    cipher(in , (K_4));
    return strcmp(in,out) !=0;
}

// See full documentation in header file
int test_cipher_cyclic_upper_case_positive_k ()
{
    char in[]= "ABC";
    char out[] = "DEF";
    cipher(in , K_5);
    return strcmp(in,out) !=0;
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decipher (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_special_char_positive_k ()
{
    char in[] = ".za.,";
    char out[] = ".xy.,";
    decipher(in,K_2);
    return strcmp(in,out) != 0;
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_special_char_negative_k ()
{
    char in[] = "ab .";
    char out[]= "bc .";
    decipher(in , (K_3));
    return strcmp(in,out) !=0;
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_negative_k ()
{
    char in[] = "yz .";
    char out[]= "bc .";
    decipher(in , (K_4));
    return strcmp(in,out) !=0;
}

// See full documentation in header file
int test_decipher_cyclic_upper_case_positive_k ()
{
    char in[] = "DEF";
    char out[]= "ABC";
    decipher(in , K_5);
    return strcmp(in,out) !=0;
}
