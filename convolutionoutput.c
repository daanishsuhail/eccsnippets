#include <stdio.h>
#include <math.h>

// Convolution output for the code
// (1,(d+1)/(d+1))

// 10111110111001010111100101101100
// 12 digits: 111010100100 <- 101100

int main()
{
    // all registers start with 0 as their starting state.
    char bitstringch[] = "101100"; // inserts two zeroes into our original message
    int bitstring[6];

    for (int i = 0; i < 6; i++)
    {
        bitstring[i] = bitstringch[i] - '0';
        printf("%d", bitstring[i]);
    }
    printf("\n");
    int ta = bitstring[0];
    int tb = 0;
    int d1 = 0;
    int d2 = 0;
    int dx[10] = {0}; // registers
    int recreg[10] = {0};
    int inputVec[10] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0}; // constant vector that we take the dot product s+9 regs. Numerator
    int recVec[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};   // denominator has 10 registers
    printf("\n");
    for (int j = 0; j < 6; j++)
    {
        printf("%d ", j);
        tb = 0;
        ta = bitstring[j]; // source output
        printf("%d", ta);
        dx[0] = bitstring[j]; // convolving window dx[0] is the source

        for (int i = 0; i < 10; i++)
        {
            tb += dx[i] * inputVec[i]; // polynomial
            tb += recreg[i] * recVec[i];
        }

        tb = tb % 2;
        // printf("%d", bitstring[j]); // printing out the codewords
        //    printf("%d%d",ta,tb);
        //    This is where you iterate t
        for (int i = 12; i >= 0; i--)
        {
            dx[i + 1] = dx[i];
            // printf("%d", dx[i + 1]);
        }

        for (int i = 12; i >= 0; i--)
        {
            recreg[i + 1] = recreg[i];
            // printf("%d", dx[i + 1]);
        }
        recreg[0] = tb;
        // printf("\n");
        ta = 0;
        tb = 0;
    }

    return 0;
}