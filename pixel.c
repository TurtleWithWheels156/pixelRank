

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "pixel.h"

static int rankSize;

/* Iterates through data buffer to feed. Calls pushRank to handle replacement of values if top ranking values come in. */
void processRow(struct pixelData * topVals, uint16_t * buffer_data, uint32_t width, uint32_t row, int * pixelcount)
{
    uint32_t i;
    for (i=0;i<width;i++)
    {
        pushRank(topVals, buffer_data[i], i, row);
        (*pixelcount)++;
    }
}

/* Processes incoming pixels and determines whether it meets value minimum to be included. */
void pushRank(struct pixelData * topVals, int val, uint32_t width, uint32_t row)
{
    int curr;
    
    (topVals+rankSize)->value = val;
    (topVals+rankSize)->x = width;
    (topVals+rankSize)->y = row;
    curr = rankSize;

    /* Logic to percolate higher values up the ranking by comparing with successive neighbor.
    Starts from end of array to beginning, where beginning holds the highest pixel value. */
    while(curr>0 && (topVals+((curr-1)))->value < (topVals+curr)->value)
    {
        int index = (curr-1);

        int temp_val = (topVals+index)->value;
        uint32_t temp_x = (topVals+index)->x;
        uint32_t temp_y = (topVals+index)->y;

        (topVals+index)->value = (topVals+curr)->value;
        (topVals+index)->x = (topVals+curr)->x;
        (topVals+index)->y = (topVals+curr)->y;
        
        (topVals+curr)->value = temp_val;
        (topVals+curr)->x = temp_x;
        (topVals+curr)->y = temp_y;
        curr = (curr-1);
    }
    /* Once rankings have been filled with value, store incoming pixel data 
    at the end by default for comparison with min value in the ranking */
    if(rankSize<SIZE)
    {
        rankSize += 1;
    }
}

/* Prints out ranking of pixel data. */
void showRank(struct pixelData * topVals)
{
    int i;
    printf("Top Pixel Values:\n");
    for(i=0;i<rankSize-1;++i) {
        printf("Value: %u ; Location(x: %u,y: %u) %d\n", (topVals+i)->value, (topVals+i)->x, (topVals+i)->y, i);
    }
}
