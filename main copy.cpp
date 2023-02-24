#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h>

#include <cstdlib>
#include <fstream>  //leitura de arquivo
#include <iostream>
#include <map>
#include <vector>
using namespace std;

string palavra = "abcdefghijklmopqrstuvxywz0123456789";



/**
 * @brief iterate over every char, breaking them into individual bits and adding to the buffer.
 *
 * @param input
 * @param byte_size
 * @param debug
 * @return vector<bool>
 */
vector<bool> string_to_binary(string input, int byte_size = 7, bool debug = false) {
    vector<bool> binary_array;
    int chars_in_string = input.length();

    for (int i = 0; i < chars_in_string; i++) {  // iterating over string object (chars)
        char letra = input[i];
        for (int j = 0; j < byte_size; j++) {  // iterating over bits in char
            binary_array.push_back(letra & 1);
            letra = letra >> 1;
        }
    }
    return binary_array;
}

bool example_holder[7];
/**
 * @brief explode um byte em 7 bits, ignorando o bit [7] (que seria o 8 elemento)
 *
 * @param byte
 * @param byte_holder
 * @param debug
 * @return true
 * @return false
 */
bool byte_to_7bit(char byte, bool* byte_holder, bool debug = false) {
    for (int i = 0; i < 8; ++i) {
        byte_holder[i] = byte & 1;
        byte = byte >> 1;
    }
    if (debug)
        printf("BIN7=\t%d %d %d %d %d %d %d\r\n", byte_holder[0], byte_holder[1], byte_holder[2], byte_holder[3],
               byte_holder[4], byte_holder[5], byte_holder[6]);

    if (debug)
        printf("BIN8=\t%d %d %d %d %d %d %d %d\r\n", byte_holder[0], byte_holder[1], byte_holder[2], byte_holder[3],
               byte_holder[4], byte_holder[5], byte_holder[6], byte_holder[7]);
    return true;
}

int amai2n() {
    vector<bool> b(10,0);
    b[2] = b[4] = 1;
    int i;
    i = accumulate(b.rbegin(), b.rend(), 0, [](int x, int y) { return (x << 1) + y; });
    cout << i << endl;
}

int mai2n() {
    vector<bool> b(10,0);
    b[2] = b[4] = 1;
    int i;
    i = accumulate(b.rbegin(), b.rend(), 0, [](int x, int y) { return (x << 1) + y; });
    cout << i << endl;
}

//> processo: pega string ascii8, transforma em vetor binario7, transforma em HEX e transmite
//> processo: recebe HEX, junta conjuntos de 7bits e adiciona 1bit (0),  transforma conjuntos de 8 em char

//> função1: recebe string e retorna uma vetor<bool>.  exclui o ultimo bit (inutil)
//> função2: recebe vetor<bool> e agrupa conjuntos de 8bits, retorna vetor de char
//> função3: recebe vetor de char e simula transmissão
//> função4: recebe transmissão (tudo zoado aparentemente), desagrupa conjuntos de 7bits e adiciona o ultimo bit
//           agrupa os conjuntos em uma string
//> 
//> falta conferir se o ascii é menor que 127..
//> 


string binary7_to_ascii(vector<bool> input, int byte_size, bool debug = false) {
    string output;
    int _input_size = input.size();
    int _groups = _input_size / byte_size;
    printf("size = %d, groups = %d\r\n", _input_size, _groups);

    for (int i = 0; i < _groups; i++)  // iterate over groups of n bits (which make a char)
    {

        char _current_byte; //hold a single byte val (0-255), maybe use char instead?
        for (int j = 0; j < byte_size; j++)  // iterate over 7-8 bits and make a char
        {
            // https://stackoverflow.com/questions/47981/how-do-i-set-clear-and-toggle-a-single-bit
            bool _bit = input[i * byte_size + j];
            _current_byte ^= (-_bit ^ _current_byte) & (1UL << i);
        }
        output.push_back(_current_byte);
        cout << "current_byte(char): " << _current_byte << " (dec): " << int(_current_byte) << endl; 
        cout << "output single: " << output << endl; 
    }
        cout << "output full: " << output << endl; 
    
}

string backup_binary_to_7bit_ascii(vector<bool> input, int byte_size, bool debug = false) {
    string output;
    int _input_size = input.size();
    int _groups = _input_size / byte_size;
    printf("size = %d, groups = %d\r\n", _input_size, _groups);

    for (int i = 0; i < _groups; i++)  // iterate over groups of n bits (which make a char)
    {
        char _current_byte; //hold a single byte val (0-255), maybe use char instead?
        for (int j = 0; j < byte_size; j++)  // iterate over 7-8 bits and make a char
        {
            // https://stackoverflow.com/questions/47981/how-do-i-set-clear-and-toggle-a-single-bit
            bool _bit = input[i * byte_size + j];
            _current_byte ^= (-_bit ^ _current_byte) & (1UL << i);
        }
        output.push_back(_current_byte);
        cout << "current_byte(char): " << _current_byte << endl; 
        cout << "output single: " << output << endl; 
    }
        cout << "output full: " << output << endl; 
    
}

int main() {
    system("CLS");
    mai2n();
    return 0;


    byte_to_7bit('a', example_holder, true);
    int ascii_value = 'a';
    cout << "ascii_value dec = " << ascii_value << endl;

    vector<bool> binary_pool;
    binary_pool.clear();
    binary_pool = string_to_binary("a", 7);

    // transforma vetor e printa os bits
    int a = 0;
    cout << "BINx=\t";
    for (bool bit : binary_pool) {
        a++;
        cout << bit << " ";
    }
    cout << "\t bits=" << a << endl;


    binary7_to_ascii(binary_pool,7,true);

    return 1;
}

// byte1 = 7bit[1] + 1bit[2] 8
// byte2 = 6bit[2] + 2bit[3] 8
// byte4 = 5bit[3] + 3bit[4] 8
// byte5 = 4bit[4] + 4bit[5] 8
// byte6 = 3bit[5] + 5bit[6] 8
// byte7 = 2bit[6] + 6bit[7] 8
// byte8 = 1bit[7] + 7bit[8] 8
// byte9 = 7bit[8] + 1bit[9] 8

// int letter_pos = secret_word.find(letter);
// if (letter_pos != -1)
// {
//       char letra
//       secret_word.c_str();
//       incomplete_word[i] =
//       cout << "TEM ESSA LETRA AI: " << secret_word[letter_pos] << endl;
// }
