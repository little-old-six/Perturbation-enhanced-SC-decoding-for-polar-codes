/*****************************************************************//**
 * \file   decode.h
 * \brief  Random Perturbation-based SC (RPSC or namely PSC)
 * 
 * \author YZJ
 * \date   June 2024
 *********************************************************************/

#pragma once
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "crc.h"
#include "variables.h"
using namespace std;


/*****************************************head******************************************/


class SCL
{
public:
    SCL(int* list, int* pos, int crc_l, int LL);
    ~SCL();

    void P_FSCL(double* y, double sgm_noise, int* msg_de);

private:
    int i, j;
    int L_MAX=1;                          // list size
    int crc_len;                          // crc length 

    int A_list[N] = { 0 };
    int position[N] = { 0 };    
    int g[crc_type + 1] = { 0 };          // polynomial of crc

    void AWGN(double* a, double sgm);

};


/****************************************program****************************************/


SCL::SCL(int* list, int* pos, int crc_l, int LL)
{
    L_MAX = LL;
    crc_len = crc_l;

    for (int i = 0;i < N; i++)
    {
        A_list[i] = list[i];
        position[i] = pos[i];
    }

    /* get CRC polynomial */
    CRC_polynomial(crc_len, g);

}

SCL::~SCL()
{
}


 
/**
 * .Random Perturbation-based SC (RPSC or namely PSC)
 * 
 * \param y£ºReceived Symbols
 * \param sgm_noise£ºstandard deviation of perturbation
 * \param msg_de : msg_de[0, K - 1] are decoded msg; msg_de[K] is number of decoding attempt; msg_de[K + 1]is crc result
 */
void SCL::P_FSCL(double* y, double sgm_noise, int* msg_de)
{
    /*******************************Basic Parameter Settings******************************/

    double y_orig[N] = { 0 };   // Original Received Symbols
    double y_temp[N] = { 0 };   // Perturbed Received Symbols
    int msg[K + 2] = { 0 };     // decoded msg bit: 0-K-1£ºdecoded msg; K: decoding attempts£»K+1: crc check result
    int flg_crc = 0;            // CRC detection£º0:faile; 1:pass

    /****************************************Begin****************************************/


    /**********************************Original SC decoding********************************/

    //copy
    memcpy(y_orig, y, sizeof(double) * (N));
    memcpy(y_temp, y_orig, sizeof(double) * (N));

    //SC decoding algorithm
    //use the SC decoder by yourself
    SC(y_orig, msg); // y_orig: original received LLR; msg: decoded msg, where 0-K-1£ºdecoded msg; K+1: crc check result

    /* CRC_Check */
    flg_crc = msg[K + 1];    // 0:wrong; 1:pass

    /* Decode correct */
    if (flg_crc == 1)
    {
        memcpy(msg_de, msg, sizeof(int) * (K));

        msg_de[K] = 1;
        msg_de[K + 1] = 1;

        return;
    }


    /*************************************************************************************************/


    /**********************************Random Perturbation-based SC************************************/

    // RPSC decoding
    for (size_t t = 1; t <= T_flip; t++)
    {

        memcpy(y_temp, y_orig, sizeof(double) * (N));

        //add perturbation
        AWGN(y_temp, sgm_noise);

        //SC decoding algorithm
        //use the SC decoder by yourself
        SC(y_temp, msg); // y_temp:received llr; msg: decoded msg, where 0-K-1£ºdecoded msg; K+1: crc check result

        /* CRC_Check */
        flg_crc = msg[K + 1];    // 0:wrong; 1:pass

        /* Decode correct */
        if (flg_crc == 1)
        {
            memcpy(msg_de, msg, sizeof(int) * (K));

            msg_de[K] = 1 + t;
            msg_de[K + 1] = 1;

            return;
        }

    }


    // decoding failure
    memcpy(msg_de, msg, sizeof(int) * (K));
    msg_de[K] = 1 + T_flip;
    msg_de[K + 1] = 0;

    /**********************************End*************************************/

}

/**
 * .adding perturbation
 * 
 * \param y£ºreceived symbols
 * \param sgm
 */
void SCL::AWGN(double* a, double sgm)
{
    double u, r, g;
    for (int i = 0; i < N; i++)
    {
        u = (float)rand() / (float)RAND_MAX;
        if (u == 1.0)
            u = 0.999999;
        r = sgm * sqrt(2.0 * log(1.0 / (1.0 - u)));

        u = (float)rand() / (float)RAND_MAX;
        if (u == 1.0)
            u = 0.999999;
        g = (float)r * cos(2 * pi * u);

        a[i] += g;
    }
}



