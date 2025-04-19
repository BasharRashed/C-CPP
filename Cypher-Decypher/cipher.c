#include "cipher.h"

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.
enum alphabet_letters {ALPHABET_LETTERS_NUM=26};


// See full documentation in header file
void cipher (char s[], int k)
{
    // modulo 26 to ensure cyclic letters when needed
    k %= ALPHABET_LETTERS_NUM;
    // check and cipher capital letters
    for (int i = 0;s[i] != '\0' ;i++)
        if('A' <= s[i] &&  s[i] <= 'Z')
        {
            s[i] += k;
            if (s[i]>'Z'){
                s[i] -= ALPHABET_LETTERS_NUM;
            }
            else if (s[i]<'A'){
                s[i]+=ALPHABET_LETTERS_NUM;
            }
        }
        // check and cipher small letters
        else if('a'<= s[i] && s[i]<='z')
        {
            s[i] += k;
            if (s[i]>'z'){
                s[i] -= ALPHABET_LETTERS_NUM;
            }
            else if (s[i]<'a'){
                s[i]+=ALPHABET_LETTERS_NUM;
            }
        }
    }


// See full documentation in header file
void decipher (char s[], int k)
{
    // ensure that k stays correct even when negative
    k = ((k % ALPHABET_LETTERS_NUM) + ALPHABET_LETTERS_NUM) % ALPHABET_LETTERS_NUM;
    cipher(s,-k);
}
