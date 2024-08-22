#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define true 1
#define false 0
// need to fix so that it is correctly assessing the bits
typedef int bool;

typedef struct node
{
    int codeword[12]; // the actual codeword
    int timestate;
    bool onoffState;
    long double probability;
    struct node_t *nextzero; // next points in trellis for next state 0
    struct node_t *nextone;  // next point in trellis for next state 1
    struct node_t *previous;
} node_t;

int main()
{
    int successfuldecode[6] = {1, 0, 1, 1, 0, 0};
    long double successprobability[100] = {0};
    long double successfulbits = 0;
    long double accuracy = 0;
    srand(time(NULL));
    for (int completionstate = 0; completionstate < 100; completionstate++)
    {
        {
            int originalcodewordsize = 12; // 12
            int kval = 2;                  // 2 zeroes enter memory
            int messlength = 6;            // defines number of original nodes
            int outputkval = 2 * kval;
            int finalinputsize = originalcodewordsize + outputkval;
            long double perror = 0.89; // probability for a bit flip
            long double minusp = 1 - perror;
            // 11011110 <- 1011
            // 111010100100 <- 101100
            int receivedcodeword[12] = {1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0};
            int randomval;

            // FLIPPING BITS BY RANDOM
            for (int i = 0; i < 12; i++)
            {
                randomval = rand() % 100 + 0;
                if (randomval <= (perror * 100))
                {
                    if (receivedcodeword[i] == 1)
                    {
                        receivedcodeword[i] = 0;
                    }
                    else
                    {
                        receivedcodeword[i] = 1;
                    }
                }
            }
            // BITFLIP

            /*
            for (int i = 0; i < 10; i++)
            {
                receivedcodeword[i] = receivedcodeword[i] - '0'; // convert to integers
            }
            */
            printf("Received: ");
            for (int i = 0; i < 12; i++)
            {
                printf("%d", receivedcodeword[i]);
            }
            printf("\n");

            node_t trellis[4][7]; // creates the nodes for our trellis and initializes them as null

            // Sets up the original trellis values
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    for (int k = 0; k < 12; k++)
                    {
                        trellis[j][i].codeword[k] = 0;
                    }
                    trellis[j][i].probability = 0;
                    trellis[j][i].timestate = 0;
                    trellis[j][i].onoffState = false;
                }
            }

            // DEFINING THE INITIAL STATES
            node_t initialState;

            for (int i = 0; i < 12; i++)
            {
                trellis[0][0].codeword[i] = 0; // sets initial state as 0
            }
            trellis[0][0].timestate = 0;
            trellis[0][0].probability = 1;
            trellis[0][0].onoffState = true; // turns on the first node
            // WIP: Fix initial state being the zero state

            int finalmessage[6];
            int tempcodewordcopy[12] = {0};
            int ta;
            int tb;
            int inputVec[10] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0}; // s+9 registers, s+d1
            int recVec[10] = {0};
            int recreg[10] = {0}; // vector defining recursive elements.
            int differences = 0;
            long double nextProb;
            int nextVal;
            // At this point, we define the actual viterbi algorithm.

            for (int i = 0; i < messlength; i++) // Iteration for each time state. Get inputs compute probabilities 7 total nodes, each edge is two parts
            {
                for (int j = 0; j < 4; j++) // note that j is the state
                {
                    if (trellis[j][i].onoffState == true)
                    {
                        // printf("%d%d\n", j, i); //Prints all turned on nodes
                        differences = 0;
                        tb = 0;
                        // printf("Hello error\n");
                        for (int k = 0; k < 11; k++) // (final input size - 1)?
                        {
                            tempcodewordcopy[k + 1] = trellis[j][i].codeword[k]; // Reads the current memory and cuts the last bit.
                        }

                        // Consider 1:
                        ta = 1;                  // source in this case is 1
                        tempcodewordcopy[0] = 1; // tempcodewordcopy actually stores the memory not codewords

                        for (int z = 0; z < 10; z++)
                        {
                            tb += tempcodewordcopy[z] * inputVec[z]; // polynomial
                            tb += recreg[z] * recVec[z];             // recursive piece
                        }

                        tb = tb % 2; // We now have ta,tb

                        if (ta != receivedcodeword[i + i])
                        {
                            differences++;
                        }
                        if (tb != receivedcodeword[(i + i) + 1])
                        {
                            differences++;
                        }
                        // printf("%d\n", i);
                        // printf("Received %d%d Calculated: %d%d Differences: %d ", receivedcodeword[i + i], receivedcodeword[(i + i) + 1], ta, tb, differences);

                        // printf("%d ", differences);                                     // checks differences
                        nextProb = trellis[j][i].probability * powl(perror, differences) * powl(minusp, (2 - differences)); // computes the probability of the next node
                        nextVal = (tempcodewordcopy[0] * 1) + (tempcodewordcopy[1] * 2);                                    // computes the next state
                        if (trellis[nextVal][i + 1].probability <= nextProb)
                        {
                            trellis[nextVal][i + 1].probability = nextProb;
                            for (int z = 0; z < 10; z++)
                            {
                                trellis[nextVal][i + 1].codeword[z] = tempcodewordcopy[z]; // places new codeword
                            }
                            trellis[nextVal][i + 1].onoffState = true;
                            trellis[nextVal][i + 1].timestate = trellis[j][i].timestate + 1;
                        }
                        // printf("NProb: %.20Lf\n", nextProb);

                        differences = 0;
                        tb = 0;
                        nextProb = 0;
                        ////////////
                        // Consider 0: #####
                        ta = 0; // source in this case is 1
                        tempcodewordcopy[0] = 0;

                        for (int z = 0; z < 10; z++)
                        {
                            tb += tempcodewordcopy[z] * inputVec[z]; // polynomial
                            tb += recreg[z] * recVec[z];             // recursive piece
                        }

                        tb = tb % 2; // We now have ta,tb

                        if (ta != receivedcodeword[i + i])
                        {
                            differences++;
                        }
                        if (tb != receivedcodeword[(i + i) + 1])
                        {
                            differences++;
                        }
                        // checks differences
                        nextProb = trellis[j][i].probability * powl(perror, differences) * powl(minusp, (2 - differences)); // computes the probability of the next node
                        nextVal = (tempcodewordcopy[0] * 1) + (tempcodewordcopy[1] * 2);                                    // computes the next state
                        // printf("%d%d\n", tempcodewordcopy[0], tempcodewordcopy[1]);
                        if (trellis[nextVal][i + 1].probability <= nextProb)
                        {
                            trellis[nextVal][i + 1].probability = nextProb;
                            for (int z = 0; z < 10; z++)
                            {
                                trellis[nextVal][i + 1].codeword[z] = tempcodewordcopy[z]; // places new codeword
                            }
                            trellis[nextVal][i + 1].onoffState = true;
                            trellis[nextVal][i + 1].timestate = trellis[j][i].timestate + 1;
                        }
                        // ENDING CONSIDERING 0

                        //
                    }
                }
            }
            /*
            for (int i = 4; i < 6; i++) // Getting the final bits of protection
            {
                for (int j = 0; j < 4; j++)
                {
                    if (trellis[j][i].onoffState == true)
                    {
                        // printf("%d%d\n", j, i); //Prints all turned on nodes
                        differences = 0;
                        tb = 0;
                        // printf("Hello error\n");
                        for (int k = 0; k < (finalinputsize - 1); k++)
                        {
                            tempcodewordcopy[k + 1] = trellis[j][i].codeword[k]; // Reads the current memory and cuts the last bit.
                        }
                        // Consider 0: for culling
                        ta = 0; // source in this case is 1
                        tempcodewordcopy[0] = 0;

                        for (int z = 0; z < 12; z++)
                        {
                            tb += tempcodewordcopy[z] * inputVec[z]; // polynomial
                            tb += recreg[z] * recVec[z];             // recursive piece
                        }

                        tb = tb % 2; // We now have ta,tb

                        if (ta != receivedcodeword[i + i])
                        {
                            differences++;
                        }
                        if (tb != receivedcodeword[(i + i) + 1])
                        {
                            differences++;
                        }
                        printf("%d\n", i);
                        printf("Received %d%d Calculated: %d%d Differences: %d ", receivedcodeword[i + i], receivedcodeword[(i + i) + 1], ta, tb, differences);

                        nextProb = trellis[j][i].probability * powl(perror, differences) * powl(minusp, (2 - differences)); // computes the probability of the next node
                        nextVal = (tempcodewordcopy[0] * 1) + (tempcodewordcopy[1] * 2);                                    // computes the next state
                        if (trellis[nextVal][i + 1].probability <= nextProb)
                        {
                            trellis[nextVal][i + 1].probability = nextProb;
                            for (int z = 0; z < 12; z++)
                            {
                                trellis[nextVal][i + 1].codeword[z] = tempcodewordcopy[z]; // places new codeword
                            }
                            trellis[nextVal][i + 1].onoffState = true;
                            trellis[nextVal][i + 1].timestate = trellis[j][i].timestate + 1;
                        }
                        printf("NEXT: %d\n", nextVal);
                        printf("NProb: %.20Lf\n", nextProb);

                        differences = 0;
                        tb = 0;
                        nextProb = 0;
                    }
                }
            } */

            printf("Final Message: ");
            for (int i = 5; i >= 0; i--)
            {
                printf("%d", trellis[0][6].codeword[i]);
            }
            finalmessage[0] = trellis[0][6].codeword[5];
            finalmessage[1] = trellis[0][6].codeword[4];
            finalmessage[2] = trellis[0][6].codeword[3];
            finalmessage[3] = trellis[0][6].codeword[2];
            finalmessage[4] = trellis[0][6].codeword[1];
            finalmessage[5] = trellis[0][6].codeword[0];

            for (int i = 0; i < 6; i++)
            {
                if (finalmessage[i] == successfuldecode[i])
                {
                    successfulbits++;
                }
            }

            if (successfulbits == 6)
            {
                accuracy = 1;
            }

            successprobability[0] += accuracy;

            printf("\n Probability: %.20Lf\n", trellis[0][6].probability);
            printf("\n Bit Success Probability: %.20Lf\n", accuracy);

            printf("Terminated");
            successfulbits = 0;
            accuracy = 0;
        }
    }
    printf("\n FINAL Bit Success Probability: %.20Lf\n", successprobability[0]);
}