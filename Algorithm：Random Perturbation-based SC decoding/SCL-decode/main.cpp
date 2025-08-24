/*****************************************************************//**
 * \file   main.cpp
 * \brief  Random Perturbation-based SC
 *
 * crc_len：crc length
 *
 * \author YZJ
 * \date   June 2024
 *********************************************************************/


#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "Pol_encode.h"
#include "decode.h"
#include "ga.h"
#include "variables.h"
#include "crc.h"
#include "other.h"
#include "5G_NR.h"
using namespace std;


#define crc_len crc_type   //type of crc
float rate = code_rate;    // code rate


void main()
{
	double SNR;                                                      // SNR
	double N0, sigma;                                                // N0-Noise variance；sigma-Noise standard deviation
	unsigned long long error[2] = { 0 }, error_num;                  // error[0]-total number of bit errors；error[1]-total number of frame errors；error_num-number of bit errors in current frame
	long int total_complex_num;                                      // decoding complexity
	int L;                                                           // list size

	int A_list[N] = { 0 };                                           // information set
	int message[K] = { 0 };                                          // message bit
	int message_decode[K + 2] = { 0 };                               // 0-K-1：decoded msg; K: decoding attempts；K+1: crc check result
	double received_symbol[N] = { 0 };                               // received symbol
	double llr[N] = { 0 };                                           // received LLR
	int data_position[K] = { 0 };                                    // position of message bit and crc bit 
	int frozen_position[N - K] = { 0 };                              // position of forzen bits
	int g[crc_len + 1] = { 0 };                                      // polynomial of crc


	/* obtain input parameters */
	L = Obtain_input_parameters();

	//random seed
	srand((int)1);

	/* get CRC polynomial */
	CRC_polynomial(crc_len, g);

	// rate profiling；0：GA；1：5G NR
	switch (flg_channel)
	{
	case 0:
	{
		//select the transmission channel for message bit
		Channel_GA c(GA_SNR, code_rate);
		c.Get_information_pos(A_list, data_position, K);
	}
	break;
	case 1:
	{
		//5G NR
		NR_5G(A_list, frozen_position, data_position);
	}
	break;
	default:
		abort();
		break;
	}

	sort(data_position, data_position + K);


	printf(" Polar  code     SNR     BER           FER            FZD             Block errors       Run times       Time cost \n\n");
	for (SNR = SNR_start; SNR <= SNR_finish; SNR += SNR_inc)
	{
		//time start
		start = clock();

		// AWGN
		N0 = (1.0 / (2.0 * rate)) / pow(10.0, (float)(SNR) / 10.0);   // AWGN power
		sigma = sqrt(N0);                                             // standard deviation of AWGN

		// perturbation
		double N0_added = (1.0 / (2.0 * code_rate)) / pow(10.0, (float)(SNR - SNR_noise) / 10.0);
		double N0_noise = abs(N0_added - N0); // perturbation power
		double sgm_noise = sqrt(N0_noise);    // standard deviation of perturbation


		error[0] = error[1] = 0;
		total_complex_num = error_num = run = 0;

		Polar_encode a(A_list, data_position, crc_len, sigma);
		SCL b(A_list, data_position, crc_len, L);

		while (error[1] < max_error_num && run < max_run_time)
		{
			run++;

			//set 0
			memset(message, 0, sizeof(message));
			memset(received_symbol, 0, sizeof(received_symbol));
			memset(message_decode, 0, sizeof(message_decode));

			//encode
			a.Encode(message, received_symbol, g);

			//decode
			b.P_FSCL(received_symbol, sgm_noise, message_decode);

			/* number of decoding attempts */
			total_complex_num += message_decode[K];


			error_num = 0;
			for (int i = 0; i < K- crc_len; i++)
			{
				if (message[i] != message_decode[i])
					error_num++;
			}   

			error[0] = error[0] + error_num;
			if (error_num != 0)
				error[1] = error[1] + 1;

			//calcuate BER and FER
			BER = (double)error[0] / K / (double)(run);
			FER = (double)error[1] / (double)run;
			FZD = (double)total_complex_num / (double)run;
			printf("(%5d,%5d)    %.2f    %.3E     %.3E      %.4E      %-5d              %-7d\r", 
				N, K_msg, SNR, BER, FER, FZD, error[1], run);
		}

		//time end
		finish = clock();
		//calcuate the time cost
		cost = (double)(finish - start) / CLOCKS_PER_SEC;

		printf("(%5d,%5d)    %.2f    %.3E     %.3E      %.4E      %-5d              %-7d         %-d s\n\n", 
			N, K_msg, SNR, BER, FER, FZD, error[1], run, cost);

	}

	system("pause");
	getchar();
}
