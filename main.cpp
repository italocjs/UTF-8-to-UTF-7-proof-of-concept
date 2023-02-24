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

//> processo: pega string ascii8, transforma em vetor binario7, transforma em HEX e transmite
//> processo: recebe HEX, junta conjuntos de 7bits e adiciona 1bit (0),  transforma conjuntos de 8 em char

//> função1: recebe string, verifica que os caracteres são validos (<127)
//              e retorna uma vetor<bool>.  exclui o ultimo bit (inutil)
//> função2: recebe vetor<bool> e agrupa conjuntos de 8bits, retorna vetor de char
//> função3: recebe vetor de char e simula transmissão
//> função4: recebe transmissão (tudo zoado aparentemente), desagrupa conjuntos de 7bits e adiciona o ultimo bit
//           agrupa os conjuntos em uma string
//>
//> falta conferir se o ascii é menor que 127..
//>

void print_binary_array(vector<bool> input, int bits_size = 7)
{
    int spaces = 0;
    for (size_t i = 0; i < input.size(); i++)
    {
        spaces++;
        if (spaces == bits_size)
        {
            cout << input[i] << " ";
            spaces = 0;
        }
        else
        {
            cout << input[i];
        }
    }
    cout << endl;
}
vector<bool> ascii_to_utf7_bin(string input, bool debug = false)  // funcao1
{
    vector<bool> binary_array;
    vector<bool> sub_vector;

    for (uint8_t letra : input)
    {
        //0 checa se é valido (<127)
        //1 limpa o sub_buffer e coloca a letra no subbuffer
        //2 inverte o sub_buffer
        //3 push sub_buffer pro main_buffer?

        //1
        if (letra > 127) { letra = 0x20; printf("\033[91m Unsupported char received! \033[0m\r\n");} // hex for utf8 "!"
        //2
        sub_vector.clear();
        for (int j = 0; j < 7; j++)
        {  // iterating over bits in char, except for last (8)
            bool bit = letra & 1;
            sub_vector.push_back(bit);
            letra = letra >> 1;
        }
        //3
        reverse(sub_vector.begin(), sub_vector.end());
        //4
        if (debug) print_binary_array(sub_vector);
        for (int i = 0; i < 7; i++)
        {
            binary_array.push_back(sub_vector[i]);
        }
    }
    if (debug) cout << "ascii_to_utf7_bin: ";
    if (debug) print_binary_array(binary_array);
    return binary_array;
}

/**
 * @brief helper function to convert a vector (size 7 or 8) into a int
 *
 * @param b
 * @return int
 */
int bits_to_int(vector<bool> b)
{
    // vector<bool> b(10,0);
    // b[2] = 1;
    // b[4] = 1;
    // auto p = b.begin()._M_p;
    // cout << *p << endl;
    int i;
    //i = accumulate(b.rbegin(), b.rend(), 0, [](int x, int y) { return (x << 1) + y; });
    i = accumulate(b.begin(), b.end(), 0, [](int x, int y) { return (x << 1) + y; });
    //cout << i << endl;
    //cout << i << " ";
    printf("%c - %d: ", i, i);
    return i;
}

/**
 * @brief helper function to convert a vector (size 7 or 8) into a char
 *
 * @param b
 * @return char
 */
char bits_to_char(vector<bool> b, bool debug = false)
{
    int i;
    i = accumulate(b.begin(), b.end(), 0, [](int x, int y) { return (x << 1) + y; });
    if (debug)
    {
        printf("char: %c\t dec: %d\t bin: ", i, i);
        print_binary_array(b, 8);
    }
    return i;
}

/**
 * @brief This will convert an binary stream into a montruosity composed of 7bits of char1 + 1bit of char2
 * this encoding will save 1 bit per byte, which is a 15% economy at cost of extra processing
 *
 * @param v
 * @return string
 */
string binary_to_utf7(vector<bool> v, bool debug = false)
{
    vector<bool> sub_vector;
    string vetor_out;
    int bitcount = 0;
    int n = 8; // split vector into sub-vectors each of size `n`
    int block_count = (v.size() - 1) / n + 1; // determine the total number of sub-vectors of size `n`
    int remainder = v.size() / block_count; //how many bits are missing from the last block? we need to add leading zeroes!
    bool incomplete_byte = false;
    (remainder < 8) ? incomplete_byte = true : incomplete_byte = false;

    if (debug) printf("full_size = %d | block_count = %d | ultimo_bloco = %d | incomplete = %d\r\n",
        v.size(), block_count, remainder, incomplete_byte);

    for (int current_block = 0; current_block < block_count; current_block++)
    {  // aqui eu to abrindo blocos de 7
        sub_vector.clear();  // importante!
        bool is_last_block = (current_block + 1 == block_count);
        //printf("current_block %d block_count = %d islast = %d >> ", current_block, block_count, is_last_block);
        if (is_last_block && incomplete_byte) //different way to handle last bit
        {
            int missing_leads = 8 - remainder;
            for (int i = 0; i < missing_leads; i++)
            {
                if (debug)cout << "ADDED_LEADING_ZERO: ";
                sub_vector.push_back(0);
            }
            for (int current_bit = 0; current_bit < (n - missing_leads); current_bit++)
            {
                sub_vector.push_back(v[bitcount]);
                bitcount++;
            }
        }
        else
        {

            for (int current_bit = 0; current_bit < n; current_bit++)
            {
                sub_vector.push_back(v[bitcount]);
                bitcount++;
            }
        }
        vetor_out += bits_to_char(sub_vector, debug);
        //print_binary_array(sub_vector, 8);
        sub_vector.clear();  // importante!
    }
    if (debug) cout << "vector_out = = " << vetor_out << endl;
    return vetor_out;
}

vector<uint8_t> data_to_hex(string input)
{
    vector<uint8_t> output;
    output.clear();
    for (char letra : input)
    {
        output.push_back(uint8_t(letra));
    }
    return output;
}
void print_as_hex(vector<uint8_t> input)
{
    printf("HEX_data:\t");
    for (uint8_t byte : input)
    {
        printf("%02X", byte);
    }
    printf("\r\n");
}
void print_as_hex(string input)
{
    printf("hex_data:\t");
    for (uint8_t byte : input)
    {
        printf("%02X", byte);
    }
    printf("\r\n");
}


//testes:  012345678 tem resto! 63bits compactado | 72 original
//testes:  01234567  nao tem resto!  56bits | 64 original

int main()
{
    string data = "0123465789abcdefghijklmnopqrstuvxywz!@#$%&*()-=_+";

    vector<bool> binary_data = ascii_to_utf7_bin(data,true); //Convert data into binary
    string compacted_data = binary_to_utf7(binary_data,true); //Convert binary into string

    float percent = ((float(data.size()) / float(compacted_data.size())) - 1.00f) * 100.0f;

    cout << endl << endl;
    cout << "original_data:\t" << data << endl;
    cout << "compacted_data:\t" << compacted_data << endl;
    print_as_hex(compacted_data);

    printf("data_size: %d \tcompacted_size: %d \treduction: %0.2f \r\n", int(data.size()), int(compacted_data.size()), percent);
}
//                              f_v1        f_v2 ok
// a =  dec:097	bin:01100001	1000011     1100001
// b =	dec:098	bin:01100010	0100011     1100010
// c =	dec:099	bin:01100011	1100011     1100011
// d =	dec:100	bin:01100100	0010011     1100100
// e =	dec:101	bin:01100101	1010011     1100101
// f =	dec:102	bin:01100110	0110011     1100110
// g =	dec:103	bin:01100111    1110011     1100111


// 0 =  dec:048	bin:00110000
// 1 =	dec:049	bin:00110001
// 2 =	dec:050	bin:00110010
// 3 =	dec:051	bin:00110011
// 4 =	dec:052	bin:00110100
// 5 =	dec:053	bin:00110101
// 6 =	dec:054	bin:00110110
// 7 =	dec:055	bin:00110111
// 8 =	dec:056	bin:00111000


// recebido 1000011 0100011 1100011 0010011 1010011 0110011 1110011  size:49
