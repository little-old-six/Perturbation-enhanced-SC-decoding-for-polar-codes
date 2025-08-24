#pragma once
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "variables.h"
using namespace std;


/*****************************************head******************************************/

static int Obtain_input_parameters();


/****************************************program****************************************/


static int Obtain_input_parameters()
{
    int L = 1; // list size

    cout << "\n/***************************************************\n\n";
    printf("Random Perturbation-based SC (RPSC or namely PSC) \n\nPolar code: (%d,%d)\n\n", N, K_msg);
    if (flg_channel == 0)
    {
        printf("rate profiling£ºGA %.1f\n\n", GA_SNR);
    }
    else if (flg_channel == 1)
    {
        printf("rate profiling£º5G\n\n");
    }
    cout << "/***************************************************\n\n";
    cout << "V.1.0 \n\n" << "Code rate = " << code_rate << "\n\nMax error num = " << max_error_num;
    printf("; Max run num = %.0E\n\n", max_run_time);
    cout << "Step = " << SNR_inc << endl << endl;
    cout << "CRC type: " << crc_type << endl << endl;
    cout << "maximum number of additional deccoding attempt = " << T_flip << "\n\n";
    cout << "perturbation strength = " << SNR_noise << "\n\n";
    cout << "Enter start SNR: ";
    cin >> SNR_start;
    cout << "\nEnter finish SNR: ";
    cin >> SNR_finish;
    printf("\n");

    return L;
}