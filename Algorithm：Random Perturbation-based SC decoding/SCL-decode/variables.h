#pragma once
#ifndef VARIABLES_H
#define VARIABLES_H 1

/*========Adjustable parameters========*/
//polar code
#define n 10
//type of crc
#define crc_type 16



/*========Control Parameters========*/
#define flg_channel         0                                      // rate profiling£»0£ºGA£»1£º5G NR



/*========Fixed Parameters========*/
#define SNR_inc             0.5                                    // step of SNR
#define frozen_bit          0                                      // frozen_bit value
#define code_rate           0.5                                    // code rate
double GA_SNR = 2.5;                                               // design SNR of GA
#define T_flip              10                                     // maximum number of additional deccoding attempt
#define SNR_noise           0.5                                    // perturbation strength
#define pi                  3.1415926
#define inf                 9999999



/*========General Parameters========*/
int max_error_num = 300;                                           // max_error_num: maximum number of errors
double max_run_time = 1E10;                                        // max_run_time: maximum number of program runs allowed
double min_run_time = 1E4;                                         // min_run_time: minimum number of program runs required
long int run;                                                      // run: current run count
double FZD = 0.0;                                                  // FZD: average complexity
double FER = 0.0, BER = 0.0;                                       // FER-Frame Error Rate£»BER-Bit Error Rate
float SNR_start, SNR_finish;                                       // SNR range
clock_t start, finish;                                             // Timing Program
int cost;                                                          // time cost of simulation



/*========Polar code========*/
#define len_redundancy           crc_type
#define N                        (1<<n)                            // number of codeword
#define K_msg                    int(N * code_rate)                // number of msg bits
#define K                        (K_msg + len_redundancy)          // number of information bits



#endif