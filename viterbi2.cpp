#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <string>

// Convolution output for the code
// (1,(d+1)/(d+1))

// 10111110111001010111100101101100
// Lifts the same code from convolutionoutput.c
// Enters from the left side
// 00 = 0
// 10 = 1
// 01 = 2
// 11 = 3

int main()
{
    float perror = 0.4; // probability that an error has occurred
    float minusp = 1 - perror;

    int state[2] = {0};
    int statelist[4] = {0, 1, 2, 3};
    int stateOnOff[4] = {0};

    float carryoverprobability;

    // all registers start with 0 as their starting state.
    char bitstringch[] = "1011";
    int bitstring[4];
    int output[8];

    for (int i = 0; i < 4; i++)
    {
        bitstring[i] = bitstringch[i] - '0';
    }

    int ta = bitstring[0];
    int tb = 0;
    int d1 = 0;
    int d2 = 0;
    int dx[10] = {0};
    int inputVec[10] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0}; // vector that we take the dot product s+9 regs
    printf("Encoded codeword: ");
    for (int j = 0; j < 4; j++)
    {
        tb = 0;
        ta = bitstring[j];

        dx[0] = bitstring[j];

        for (int i = 0; i < 10; i++)
        {
            tb += dx[i] * inputVec[i]; // polynomial
        }

        tb = tb % 2;
        printf("%d%d", ta, tb);
        output[j + j] = ta;
        output[j + j + 1] = tb;

        //  printf("%d%d",ta,tb);
        //  This is where you iterate t
        for (int i = 8; i >= 0; i--)
        {
            dx[i + 1] = dx[i];
            // printf("%d", dx[i + 1]);
        }
        // printf("\n");
    }

    // ERROR Insertion
    int errorposition = 4; // placement of error
    if (output[errorposition] == 0)
    {
        output[errorposition] = 1;
    }
    else
    {
        output[errorposition] = 0;
    }

    int nextstate[2] = {0}; // Where the "next state" is calculated.
    stateOnOff[0] = 1;      // Turns on the initial state

    int outputSize = 8; // After 4 the code should only process the next states that end in a 0.
    int outputStop = 2; //

    int finalcodeword[10] = {0};
    for (int i = 0; i < outputSize; i++)
    {
        finalcodeword[i] = output[i];
    }
    for (int i = outputSize; i < outputSize + outputStop; i++)
    {
        finalcodeword[i] = 0; // Adds the zeroes at the end of the codeword
    }

    std::string finalcodewordstring = "";

    for (int i = 0; i < 10; i++)
    {
        finalcodewordstring = finalcodewordstring + finalcodeword[i];
    }

    std::cout << finalcodewordstring + "HUzzah" << std::endl;

    return 0;
}