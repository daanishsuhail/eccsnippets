#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0

//Created Spring 2023

void base10tobase2(int num, int *zinputs, int mParam);
int genpoly(int *messptr, int bitnum, int mParam, int messlength, int rParam);
void erroraddition(int *codeword);
int majorityLogic(int, int, int, int);
int rowPhaseAdd(int, int, int *codeword);

int main()
{
    // conventions: left most bit is the least significant bit
    int rParam = 2;
    int mParam = 4;
    int messLength = 11;
    // Original parameters

    int blockLength = (1 << mParam);
    char rawMessage[] = "11010010101"; //  message

    int message[strlen(rawMessage)];
    int codeWord[blockLength];

    // Splices message into an array
    for (int i = 0; i < strlen(rawMessage); i++)
    {
        message[i] = rawMessage[i] - '0';
    }

    printf("\n");

    // here, I mark every single bit with a 2-D array using the "1-2 skip a few"
    int markingVector[mParam][messLength];
    // Zeroes out the vector
    for (int j = 0; j < messLength; j++)
    {
        for (int i = 0; i < mParam; i++)
        {
            markingVector[i][j] = 0;
        }
    }

    genpoly(message, 7, mParam, messLength, rParam);

    /*for (int i = 0; i < 16; i++)
    {
        printf("%d", genpoly(message, i, mParam));
        codeWord[i] = genpoly(message, i, mParam);
    }
    */
}

int genpoly(int *messptr, int bitnum, int mParam, int messLength, int rParam)
{
    int binarybitpos[mParam]; // zvals[0] = 2^0 zvals[1] = 2^1.....

    base10tobase2(bitnum, binarybitpos, mParam);

    // ####################Base case ###############################First Degree
    int polygenBit = *(messptr); // = ((*messptr) * 1) + (zvals[0] * (*(messptr + 1)) + zvals[1] * (*(messptr + 2)) + zvals[2] * (*(messptr + 3)) + zvals[3] * (*(messptr + 4)));

    int numberWeight = 0;

    for (int i = 0; i < mParam; i++) // Gets weight of the number
    {
        if (binarybitpos[i] == 1)
        {
            numberWeight++;
        }
    }

    int vectorsUsed[numberWeight]; // Informs which vectors we care about

    for (int i = 0; i < mParam; i++) // Gets weight of the number
    {
        if (binarybitpos[i] == 1)
        {
            vectorsUsed[i] = (i + 1);
        }
    }

    int subsetCount = 1;
    subsetCount = (subsetCount << numberWeight);
    subsetCount = subsetCount - 1;

    int counterZinput[numberWeight];

    int subsetSymbols[numberWeight][subsetCount];

    for (int i = 1; i < subsetCount + 1; i++)
    {
        base10tobase2(i, counterZinput, numberWeight);
        for (int j = 0; j < numberWeight; j++)
        {
            subsetSymbols[j][i - 1] = vectorsUsed[j] * counterZinput[j];
            printf("%d", subsetSymbols[j][i - 1]);
        }

        printf("\n");
    } // Builds the array of all possible subsets

    // int markingVector[mParam][messLength];

    // Zeroes out the vector
    // for (int j = 0; j < messLength; j++)
    //{
    //    for (int i = 0; i < mParam; i++)
    //    {
    //        markingVector[i][j] = 0;
    //    }
    //}
    // Note that the first row is going to be all 0's anyways.

    // markingVector[0][1] = 1;
    //  The first row by default has a 1

    // int xCol = 0;
    // int yRow = 2;

    // for (int order = 0; order < rParam; order++)
    //{
    //     int currentOrd = order + 1;
    //     int boolnextOrd = FALSE;
    //     while (boolnextOrd == FALSE)
    //     {
    //     }
    // }

    // Strip all subsets above the rParam size.

    return polygenBit;
}

void base10tobase2(int num, int *zinputs, int mParam) // Intended to convert any number to the proper base 2
{
    int inputsVals[mParam];
    int numbertracker = num;

    for (int i = 0; i < mParam; i++)
    {
        *(zinputs + i) = (numbertracker % 2);
        numbertracker = numbertracker / 2;
    }
}
// NOTE n[0] is the LSB