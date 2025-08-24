/***************************************************
               rate profiling based on GA
Input：
Channel_GA：SNR；sigma
Get_information_pos：num_A-number of subchannel

Output：A_list; information set

***************************************************/

///////////////////////////////////////head////////////////////////////////////////

#pragma once
#include "variables.h"
static void switch_position(int* position, int KK);
static double phi(double x);
static double phi_derivative(double x);
static double phi_inverse(double x);

class Channel_GA
{
public:
    Channel_GA(float SNR, float rate1);
    ~Channel_GA();

    void Get_information_pos(int* list, int* position, int num_A);

private:
    int i, j;
    int num_A;
    float rate;
    double N0;

    int* index;

    void GA();
    void sort(double* M, int* length);
};






/////////////////////////////////////program///////////////////////////////////////

static void switch_position(int* position, int KK)
{
    int K1, temp;
    K1 = KK / 2;

    for (int i = 0; i < K1; i++)
    {
        temp = position[i];
        position[i] = position[KK - 1 - i];
        position[KK - 1 - i] = temp;
    }
}

static double phi(double x)
{
    double y, k = 0;
    if ((x >= 0) && (x <= 10))
    {
        k = -0.4527 * pow(x, 0.859) + 0.0218;
        y = exp(k);
    }
    else
    {
        if (x >= 10)
        {
            y = sqrt(pi / x) * exp(-x / 4.0) * (1 - (10.0 / (7.0 * x)));
        }
        else
        {
            printf("x is not a positive number, so the function: phi can not pass !");

        }
    }
    return y;
}

static double phi_derivative(double x)
{
    double k = 0, dx = 0;
    if ((x >= 0) && (x <= 10))
    {
        dx = -0.4527 * 0.86 * (pow(x, -0.14)) * phi(x);
    }
    else
    {
        k = (15.0 / 7.0) * pow(x, -2.5) - (1.0 / 7.0) * pow(x, -1.5) - (1.0 / 4.0) * pow(x, -0.5);
        dx = sqrt(pi) * exp(-x / 4.0) * k;
    }
    return dx;
}

static double phi_inverse(double x)
{
    double y, k = 0, delta, gap;
    if (x >= 0.0388 && x <= 1.0221)
    {
        k = (0.0218 - log(x)) / 0.4527;
        y = pow(k, (1.0 / 0.86));
    }
    else
    {
        double x0 = 0.0388, x1 = 0;
        x1 = x0 - ((phi(x0) - x) / phi_derivative(x0));
        delta = abs(x1 - x0);
        gap = 0.001;

        while (delta >= gap)
        {
            x0 = x1;
            x1 = x1 - ((phi(x1) - x) / phi_derivative(x1));
            if (x1 > 100)
            {
                gap = 10;
            }
            delta = abs(x1 - x0);
        }
        y = x1;
    }
    return y;
}


Channel_GA::Channel_GA(float SNR, float rate1)
{
    rate = rate1;

    N0 = (1.0 / (2 * rate)) / pow(10.0, (float)(SNR) / 10.0);

    index = new int[N];

}

Channel_GA::~Channel_GA()
{
    delete[] index;
}

void Channel_GA::Get_information_pos(int* list, int* position, int num_A)
{
    GA();

    /* get the position of message bits, 将信道按照可靠度从高到低排序*/
    for (i = 0; i < num_A; i++)
    {
        position[i] = index[N - 1 - i];
        list[position[i]] = 1;
    }

}

void Channel_GA::GA()
{
    double llr, llr_temp;
    llr = 2.0 / N0;

    double* llri = new double[N];
    double* llrcopy = new double[N];

    for (i = 0; i < N; i++)
    {
        llri[i] = 0;
        llrcopy[i] = 0;
    }

    llri[0] = llr;
    int m = 1;
    while (m <= N / 2)
    {
        for (int k = 0; k < m; k++)
        {
            llr_temp = llri[k];
            llrcopy[k * 2] = phi_inverse(1 - pow((1 - phi(llr_temp)), 2));
            llrcopy[2 * k + 1] = llr_temp * 2;
        }
        for (i = 0; i < N; i++)
        {
            llri[i] = llrcopy[i];
        }
        m = 2 * m;
    }


    for (i = 0; i < N; i++)
    {
        index[i] = i;
    }

    sort(llri, index);

    delete[]llri;
    delete[]llrcopy;
}

void Channel_GA::sort(double* M, int* length)
{
    {
        double temp1;
        int temp;
        for (int i = 0;i < N - 1;i++)
        {
            if (M[i + 1] < M[i])
            {
                for (int j = i + 1;j > 0;j--)
                {
                    if (M[j] < M[j - 1])
                    {
                        
                        temp1 = M[j - 1];
                        M[j - 1] = M[j];
                        M[j] = temp1;

                       
                        temp = length[j - 1];
                        length[j - 1] = length[j];
                        length[j] = temp;
                    }
                    else
                    {
                        break;
                    }
                }

            }
        }
    }
}