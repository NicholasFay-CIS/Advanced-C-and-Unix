// Nicholas Fay
#include "cipher.h"
#define UPPER_CASE(r) ((r) - ('a' - 'A'))

struct Cipher::CipherCheshire {
    string cipherText;
};

Cipher::Cipher()
{
    smile = new CipherCheshire;
    smile->cipherText = "abcdefghijklmnopqrstuvwxyz ";
}
Cipher::Cipher(string in)
{
    smile = new CipherCheshire;
    smile->cipherText = in;
}
string Cipher::encrypt(string raw)
{
    string retStr;
    cout << "Encrypting..." << endl;
    for(unsigned int i = 0; i < raw.size(); i++) {
        unsigned int pos;
        bool upper = false;
        if(raw[i] == ' ') {
            pos = 26;
        } else if(raw[i] >= 'a') {
            pos = raw[i] - 'a';
        } else {
            pos = raw[i] - 'A';
            upper = 1;
        }
        if(upper) {
            retStr += UPPER_CASE(smile->cipherText[pos]);
        } else {
            retStr += smile->cipherText[pos];
        }
    }
    cout << "Done" << endl;

    return retStr;
}

string Cipher::decrypt(string enc)
{
    string retString;
    cout << "Decrpyting..." << endl;
    // Fill in code here
    string retStr;
    for(unsigned int i = 0; i < enc.size(); i++) {
        unsigned int pos;
        bool upper = false;
        if(enc[i] == ' ') {
            pos = 26;
        } else if(enc[i] >= 'a') {
            pos = enc[i] - 'a';
        } else {
            pos = enc[i] - 'A';
            upper = 1;
        }
        if(upper) {
            retString += UPPER_CASE(smile->cipherText[pos+1]);
        } else {
            retString += smile->cipherText[pos+1];
        }
    }
    cout << "Done" << endl;
    return retString;
}


struct CaesarCipher::CaesarCipherCheshire : CipherCheshire {
     int rot;
};

CaesarCipher::CaesarCipher()
{
    // Fill in code here
    CaesarSmile = new CaesarCipherCheshire;
    CaesarSmile->rot = 0;
}

CaesarCipher::CaesarCipher(string in, int rot)
{
    // Fill in code here
    CaesarSmile = new CaesarCipherCheshire;
    CaesarSmile->cipherText = in;
    CaesarSmile->rot = rot;
}

string CaesarCipher::encrypt(string raw)
{
    string retStr;
    cout << "Encrypting..." << endl;
    // create a temp var for the offset
    int temp_rot = CaesarSmile->rot;
    // Takes the remainder if the number is greater than 26
    // then sets it to be the offset
    temp_rot %= 27;
    for(unsigned int i = 0; i < raw.size(); i++) {
        unsigned int pos;
        bool upper = false;
        // add 27 to the rot if the given offset is negative
        // this will allow the for looking at the end of the cipher text
        // for the wanted char to cipher. 
        if(temp_rot < 0) {
            temp_rot += 27;
        }
        if(raw[i] == ' ') {
            pos = 26 + temp_rot;
        } else if(raw[i] >= 'a') {
            pos = (raw[i] - 'a') + temp_rot;
        } else {
            pos = (raw[i] - 'A') + temp_rot;
            upper = 1;
        }
        // if the position is 27 or greater, % 27 to get the remainder
        // and set that to be the new position
        if(pos > 26) {
            pos %= 27;
        }
        if(upper) {
            retStr += UPPER_CASE(CaesarSmile->cipherText[pos]);
        } else {
            retStr += CaesarSmile->cipherText[pos];
        }
    }
    cout << "Done" << endl;
    return retStr;
}

string CaesarCipher::decrypt(string enc)
{
    cout << "Decrpyting..." << endl;
    // Fill in code here
    string De;
    // temp variable for the offset
    // couldnt figure this out so this isnt fully correct
    // going to Jees office hours on monday
    int temp_rot = CaesarSmile->rot;
    for(unsigned int i = 0; i < enc.size(); i++) {
        unsigned int pos;
        bool upper = false;
        if(enc[i] == ' ') {
            pos = 26 + 1 - temp_rot;
        } else if(enc[i] >= 'a') {
            pos = (enc[i] - 'a' + 1) - temp_rot;
        } else {
            pos = (enc[i] - 'A' + 1) - temp_rot;
            upper = 1;
        }
        // if the position is 27 or greater, % 27 to get the remainder
        // and set that to be the new position
        if(pos > 26) {
            pos %= 27;
        }
        if(upper) {
            De += UPPER_CASE(CaesarSmile->cipherText[pos]);
        } else {
            De += CaesarSmile->cipherText[pos];
        }
    }
    cout << "Done" << endl;
    return De;
}


