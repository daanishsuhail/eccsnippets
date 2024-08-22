#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Created in Spring 2023

void base10tobase2(int num, int *zinputs, int mParam);
int genpoly(int *messptr, int bitnum, int mParam);
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
    int decodeAttempt[messLength];

    // Splices message into an array
    for (int i = 0; i < strlen(rawMessage); i++)
    {
        message[i] = rawMessage[i] - '0';
    }

    printf("\n");

    for (int i = 0; i < 16; i++)
    {
        printf("%d", genpoly(message, i, mParam));
        codeWord[i] = genpoly(message, i, mParam);
    }
    // Converts the original code into an array.
    // This is the point where the error is decoded.
    printf("\n");

    printf("error present: ");

    erroraddition(codeWord); // adds a single bit error at some defined error_position.

    for (int i = 0; i < 16; i++)
    {
        printf("%d", codeWord[i]); // prints the codeword with an error
    }

    // 1101 1110 0001 0010
    printf("\n");

    for (int i = 0; i < 11; i++)
    {
        decodeAttempt[i] = 0;
    }

    // THIS IS WHERE THE DECODING OCCURS

    // Implementing PHASE ONE: SECOND DEGREE
    // decodeAttempt[10] = majorityLogic((),(),(),());

    decodeAttempt[10] = majorityLogic((codeWord[0] + codeWord[1] + codeWord[2] + codeWord[3]) % 2, (codeWord[4] + codeWord[5] + codeWord[6] + codeWord[7]) % 2, (codeWord[8] + codeWord[9] + codeWord[10] + codeWord[11]) % 2, (codeWord[12] + codeWord[13] + codeWord[14] + codeWord[15]) % 2);
    decodeAttempt[9] = majorityLogic((codeWord[0] + codeWord[1] + codeWord[4] + codeWord[5]) % 2, (codeWord[2] + codeWord[3] + codeWord[6] + codeWord[7]) % 2, (codeWord[8] + codeWord[9] + codeWord[12] + codeWord[13]) % 2, (codeWord[15] + codeWord[14] + codeWord[10] + codeWord[11]) % 2);
    decodeAttempt[8] = majorityLogic((codeWord[0] + codeWord[2] + codeWord[4] + codeWord[6]) % 2, (codeWord[1] + codeWord[3] + codeWord[5] + codeWord[7]) % 2, (codeWord[8] + codeWord[10] + codeWord[12] + codeWord[14]) % 2, (codeWord[9] + codeWord[11] + codeWord[13] + codeWord[15]) % 2);
    decodeAttempt[7] = majorityLogic((codeWord[0] + codeWord[1] + codeWord[8] + codeWord[9]) % 2, (codeWord[2] + codeWord[3] + codeWord[10] + codeWord[11]) % 2, (codeWord[4] + codeWord[5] + codeWord[12] + codeWord[13]) % 2, (codeWord[6] + codeWord[7] + codeWord[14] + codeWord[15]) % 2);
    decodeAttempt[6] = majorityLogic((codeWord[0] + codeWord[2] + codeWord[8] + codeWord[10]) % 2, (codeWord[1] + codeWord[3] + codeWord[9] + codeWord[11]) % 2, (codeWord[4] + codeWord[6] + codeWord[12] + codeWord[14]) % 2, (codeWord[5] + codeWord[7] + codeWord[13] + codeWord[15]) % 2);
    decodeAttempt[5] = majorityLogic((codeWord[0] + codeWord[4] + codeWord[8] + codeWord[12]) % 2, (codeWord[1] + codeWord[5] + codeWord[9] + codeWord[13]) % 2, (codeWord[2] + codeWord[6] + codeWord[10] + codeWord[14]) % 2, (codeWord[3] + codeWord[7] + codeWord[11] + codeWord[15]) % 2);

    printf("\n");
    for (int i = 0; i < 11; i++)
    {
        printf("%d", decodeAttempt[i]);
    }
    printf("\n");

    // SHOULD ADD THE RESPECTIVE MATRIX ROWS TO THE ORIGINAL BIT
}

int rowPhaseAdd(int bitVal, int chooseRow, int *codeWord)
{
}

int majorityLogic(int firstVal, int secondVal, int thirdVal, int fourthVal)
{
    if ((firstVal + secondVal + thirdVal + fourthVal) >= 3)
    {
        return 1;
    }

    if ((firstVal + secondVal + thirdVal + fourthVal) <= 1)
    {
        return 0;
    }
}

int genpoly(int *messptr, int bitnum, int mParam)
{
    int zvals[mParam]; // zvals[0] = 2^0 zvals[1] = 2^1.....

    base10tobase2(bitnum, zvals, mParam);

    // ####################Base case ###############################First Degree
    int polygenBit = ((*messptr) * 1) + (zvals[0] * (*(messptr + 1)) + zvals[1] * (*(messptr + 2)) + zvals[2] * (*(messptr + 3)) + zvals[3] * (*(messptr + 4)));

    polygenBit += (zvals[0] * zvals[1] * (*(messptr + 5)) + zvals[0] * zvals[2] * (*(messptr + 6)) + zvals[0] * zvals[3] * (*(messptr + 7)) + zvals[1] * zvals[2] * (*(messptr + 8)) + zvals[1] * zvals[3] * (*(messptr + 9)) + zvals[2] * zvals[3] * (*(messptr + 10)));
    polygenBit = polygenBit % 2;
    return polygenBit;
}

void erroraddition(int *codeword)
{
    int error_position = 4; // Indicates where the error position is starting from 0,1,2,...

    if (((*(codeword + error_position)) % 2) == 0)
    {
        *(codeword + error_position) = 1;
    }
    else
    {
        *(codeword + error_position) = 0;
    }
} // adds an error to the codeword.

void base10tobase2(int num, int *zinputs, int mParam)
{
    int inputsVals[mParam];

    if (8 <= num)
    {
        *(zinputs) = 1;
        num = num - 8;
    }
    else
    {
        *(zinputs) = 0;
    }
    // printf("%d", *(zinputs + 3));

    if (4 <= num)
    {
        *(zinputs + 1) = 1;
        num = num - 4;
    }
    else
    {
        *(zinputs + 1) = 0;
    }
    // printf("%d", *(zinputs + 2));

    if (2 <= num)
    {
        *(zinputs + 2) = 1;
        num = num - 2;
    }
    else
    {
        *(zinputs + 2) = 0;
    }
    // printf("%d", *(zinputs + 1));

    if (1 <= num)
    {
        *(zinputs + 3) = 1;
        num = num - 1;
    }
    else
    {
        *(zinputs + 3) = 0;
    }
    // printf("%d\n", *(zinputs));
}
// NOTE n[0] is the LSB