/*****************************************************************//**
 * \file   Pol_encode.h
 * \brief  Polar encode
 *
 * In£º
 * Polar_encode£ºA_list , crc length£»standard deviation of AWGN-sigma
 * Encode£ºinformation set
 *
 * Out£º
 * Encode£ºmessage, received_symbol
 *
 * \author YZJ
 * \date   May 2023
 *********************************************************************/


#pragma once
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include "variables.h"
#include "crc.h"
using namespace std;


/*****************************************head******************************************/

class Polar_encode
{
public:
	Polar_encode(int* list, int* pos, int crc_l, double sigma1);
	~Polar_encode();

	void Encode(int* message, double* received_symbol, int* g);

private:
	int i, j;
	int crc_len;
	double sigma;

	int A_list[N] = { 0 };
	int position[K] = { 0 };
	int code_symbol[N] = { 0 };

	void encode(int* u);      //x = u*G
	void BPSK_AWGN(double* a);   //BPSK_AWGN
};



/****************************************program****************************************/

Polar_encode::Polar_encode(int* list, int* pos, int crc_l, double sigma1)
{
	crc_len = crc_l;
	sigma = sigma1;

	for (int i = 0; i < K; i++)
	{
		position[i] = pos[i];
		A_list[i] = list[i];
	}

	for (int i = K; i < N; i++)
		A_list[i] = list[i];

	sort(position, position + K);
}

Polar_encode::~Polar_encode()
{}

//polar encode and awgn_bpsk
void Polar_encode::Encode(int* message, double* received_symbol, int* g)
{
	//set 0
	memset(code_symbol, 0, sizeof(code_symbol));

	/*Get message bits*/
	for (int i = 0; i < K_msg; i++)
	{
		message[i] = rand() % 2;
	}

	/*Add crc*/
	CRC_Gen(message, K, g, crc_len);

	// add the frozen bit
	for (int i = 0; i < K; i++)
		code_symbol[position[i]] = message[i];

	//x = u*G
	encode(code_symbol);

	//BPSK_AWGN
	BPSK_AWGN(received_symbol);
}

//x = u*G
void Polar_encode::encode(int* u)
{
	int i_s, i_g, del, base, i_sg;

	for (i_s = 0; i_s < n; i_s++)
	{
		for (i_g = 0; i_g < (1 << (n - i_s - 1)); i_g++)
		{
			del = (1 << i_s);
			base = (1 << (i_s + 1)) * (i_g);
			for (i_sg = 0; i_sg < del; i_sg++)
			{
				u[base + i_sg] = u[base + i_sg] ^ u[base + i_sg + del];
			}
		}
	}
}

//BPSK_AWGN
void Polar_encode::BPSK_AWGN(double* a)
{
	double u, r, g;
	for (int i = 0; i < N; i++)
	{
		u = (float)rand() / (float)RAND_MAX;
		if (u == 1.0)
			u = 0.999999;
		r = sigma * sqrt(2.0 * log(1.0 / (1.0 - u)));

		u = (float)rand() / (float)RAND_MAX;
		if (u == 1.0)
			u = 0.999999;
		g = (float)r * cos(2 * pi * u);

		a[i] = (1 - 2 * code_symbol[i]) + g;
	}
}
