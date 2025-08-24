/*****************************************************************//**
 * \file   crc.h
 * \brief  CRC程序
 * 
 * CRC编码：CRC_Gen
 * CRC校验：CRC_Det
 * 获得CRC多项式：CRC_polynomial
 * 
 * msg--message bits;                K--length of msg bits;
 * polynomial--polynomial of crc;    m--types of crc
 * 
 * 输出：A_list; position-传信信道的index
 * 
 * \author YZJ
 * \date   May 2023
 *********************************************************************/

#pragma once
#include<iostream>
using namespace std;

//////////////////////////////////////head/////////////////////////////////////////

static void CRC_Gen(int* msg, int K_crc, int* polynomial, int m);
static int CRC_Det(int* msg_dec, int K_crc, int* polynomial, int m);
static void CRC_polynomial(int crc_len, int* g);



/////////////////////////////////////program///////////////////////////////////////

/* CRC encode */
static void CRC_Gen(int* msg, int K_crc, int* polynomial, int m)
{
    int i, j;
    int* msg_copy = new int[K_crc];
    for (i = 0; i < K_crc; i++)
        msg_copy[i] = msg[i];

    for (i = 0; i < K_crc - m; i++)
    {
        if (msg_copy[i])
        {
            for (j = 0; j < m + 1; j++)
                msg_copy[i + j] = msg_copy[i + j] ^ polynomial[j];
        }
    }

    for (i = K_crc - m; i < K_crc; i++)
        msg[i] = msg_copy[i];

    delete[]msg_copy;
}

/* CRC check */
static int CRC_Det(int* msg_dec, int K_crc, int* polynomial, int m) //0:wrong; 1:pass
{
    int i, j, tap;
    int* code_temp = new int[K_crc];

    for (i = 0;i < K_crc;i++)
        code_temp[i] = msg_dec[i];

    for (i = 0; i < K_crc - m; i++)
    {
        if (code_temp[i] != 0)
        {
            for (j = 0; j < m + 1; j++)
                code_temp[i + j] = code_temp[i + j] ^ polynomial[j];
        }
    }

    tap = 0;
    for (i = K_crc - m; i < K_crc; i++)
        tap += code_temp[i];

    delete[] code_temp;

    if (tap > 0)
    {
        //wrong
        return 0;
    }
    else
    {
        //right
        return 1;
    }
}

/* get CRC polynomial */
static void CRC_polynomial(int crc_len, int* g)
{
    int polynomial_2[3] = { 1,0,1 };
    int polynomial_4[5] = { 1,1,0,0, 1 };
    int polynomial_6[7] = { 1,1,0,0, 0,0,1 };
    int polynomial_8[9] = { 1,1,1,1, 1,1,0,0, 1 };
    int polynomial_11[12] = { 1,1,1,0, 0,0,1,0, 0,0,0,1 };
    int polynomial_12[13] = { 1,1,0,0, 0,0,0,0, 0,1,0,1, 1 };
    int polynomial_16[17] = { 1,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0, 1 };   // CRC-16, IBM: 16,15,2,0
    int polynomial_24[25] = { 1,1,0,1, 1,0,0,1, 0,1,0,1, 1,0,0,0, 1,0,0,0, 1,0,1,1, 1 };
    int polynomial_32[33] = { 1,0,0,0, 0,0,1,0, 0,1,1,0, 0,0,0,0, 1,0,0,0, 1,1,1,0, 1,1,0,1, 1,0,1,1, 1 };

    /* 赋值crc多项式 */
    switch (crc_len)
    {
    case 2:
        for (int i = 0; i <= crc_len; i++)
            g[i] = polynomial_2[i];
        break;
    case 4:
        for (int i = 0; i <= crc_len; i++)
            g[i] = polynomial_4[i];
        break;
    case 6:
        for (int i = 0; i <= crc_len; i++)
            g[i] = polynomial_6[i];
        break;
    case 8:
        for (int i = 0; i <= crc_len; i++)
            g[i] = polynomial_8[i];
        break;
    case 11:
        for (int i = 0; i <= crc_len; i++)
            g[i] = polynomial_11[i];
        break;
    case 12:
        for (int i = 0; i <= crc_len; i++)
            g[i] = polynomial_12[i];
        break;
    case 16:
        for (int i = 0; i <= crc_len; i++)
            g[i] = polynomial_16[i];
        break;
    case 24:
        for (int i = 0; i <= crc_len; i++)
            g[i] = polynomial_24[i];
        break;
    case 32:
        for (int i = 0; i <= crc_len; i++)
            g[i] = polynomial_32[i];
        break;
    }

}
