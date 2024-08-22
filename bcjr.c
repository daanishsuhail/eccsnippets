#include <stdio.h>

#define true 1
#define false 0

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
    // 110101100100 -> 101100
    int receivedcodeword[12] = {1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0};

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

    // Now need to move forward within the algorithm.

    return 0;
}