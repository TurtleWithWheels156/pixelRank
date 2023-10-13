#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "pixel.h"
#include "tiffio.h"

int main()
{
    struct pixelData *topValues;
    char filepath[100];
    TIFF* tif;

    /* Grab file path */
    printf("Enter filepath: ");
    scanf("%99s", filepath);
    printf("Opening 16-bit depth grayscale TIFF image. Example Created with ImageJ\n");

    /* Open .tif file */
    tif = TIFFOpen(filepath, "r");
    topValues = (struct pixelData*) malloc(SIZE * sizeof(struct pixelData));

    /* If successful open, process .tif file. Else, exit program with error */
    if (tif) {
        uint32_t imagelength, width, row;
        tdata_t buf;
        uint16_t s, nsamples;
        uint16_t* data;
        int pixelcount = 0;

        /* Allocate memory for data buffer and grab relevant fields for processing */
        buf = _TIFFmalloc(TIFFScanlineSize(tif));
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imagelength);
        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
        TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &nsamples);

        /* Grayscale check. Invalid grayscale files will have > 1 samples per pixel, indicating RGB */
        if (nsamples > 1) {
            printf("Tiff file contains TIFFTAG_SAMPLESPERPIXEL value > 1. Check if file is grayscale image.\n");
            return 0;
        }

        printf("Processing image with Width: %d and Height: %d\n", width, imagelength);

        /* Main logic. Load incoming pixel data into buffer and load topValues with ranked pixel weights */
        for (row = 0; row < imagelength; row++)
        {
            TIFFReadScanline(tif, buf, row, s);
            data=(uint16_t*)buf;
            processRow(topValues, data, width, row, &pixelcount);
        }

        printf("Processed %d pixels\n", pixelcount);

        /* Display rankings of pixel data */
        showRank(topValues);

        /* Free resources such as .tif data, and pixel data ranking */
        TIFFClose(tif);
        free(topValues);
    } else {
        printf("Error: Failed to open TIFF file.\n");
    }
    exit(0);
}
