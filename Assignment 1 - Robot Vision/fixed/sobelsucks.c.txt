#include <stdio.h>                          /* Sobel.c */
#include <math.h>

int pic[256][256];
int outpicx[256][256];
int outpicy[256][256];
int maskx[3][3] = {{-1, 0, 1},
                   {-2, 0, 2},
                   {-1, 0, 1}};
int masky[3][3] = {{1,  2,  1},
                   {0,  0,  0},
                   {-1, -2, -1}};
double ival[256][256], maxival;

void main(argc, argv)
        int argc;
        char **argv;
{
    int i, j, p, q, mr, sum1, sum2;
    double lowThreshold = 20, highTreshHold = 120;
    FILE *fp1,  *sobelmag, *sobelout1, *sobelout2;
    char *foobar;

    argc--;
    argv++;
    foobar = *argv;
    fp1 = fopen(foobar, "rb");

    argc--;
    argv++;
    foobar = *argv;
    printf("Provide a Low Threshold: ");
    scanf("%lf", &lowThreshold);


    argc--;
    argv++;
    foobar = *argv;
    printf("Provide a High Threshold: ");
    scanf("%lf", &highTreshHold);


    // pgm header 
    // resolution 256 256
    // brightness values
    sobelmag = fopen("sobelmag.pgm", "wb");
    sobelout1 = fopen("sobelout1.pgm", "wb");
    sobelout2 = fopen("sobelout2.pgm", "wb");

    fprintf(sobelmag,"P5\n");
    fprintf(sobelmag, "%d %d\n", 256, 256);
    fprintf(sobelmag, "255\n");

    fprintf(sobelout1,"P5\n");
    fprintf(sobelout1, "%d %d\n", 256, 256);
    fprintf(sobelout1, "255\n");

    fprintf(sobelout2,"P5\n");
    fprintf(sobelout2, "%d %d\n", 256, 256);
    fprintf(sobelout2, "255\n");


///----------------------------------

// skip input headers
    for (i = 0; i < 15; i++)
        getc(fp1);

        

    // pgm header 
    // resolution 256 256
    // brightness values
    // fprintf(fo1, "P5\n256 256\n255\n");

    // read in input picture 
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            pic[i][j] = getc(fp1);
            pic[i][j] &= 0377;
        }
    }

    mr = 1;
    for (i = mr; i < 256 - mr; i++) {
        for (j = mr; j < 256 - mr; j++) {
            sum1 = 0;
            sum2 = 0;
            for (p = -mr; p <= mr; p++) {
                for (q = -mr; q <= mr; q++) {
                    sum1 += pic[i + p][j + q] * maskx[p + mr][q + mr];
                    sum2 += pic[i + p][j + q] * masky[p + mr][q + mr];
                }
            }
            outpicx[i][j] = sum1;
            outpicy[i][j] = sum2;
        }
    }

    maxival = 0;
    for (i = mr; i < 256 - mr; i++) {
        for (j = mr; j < 256 - mr; j++) {
            ival[i][j] = sqrt((double) ((outpicx[i][j] * outpicx[i][j]) +
                                        (outpicy[i][j] * outpicy[i][j])));
            if (ival[i][j] > maxival)
                maxival = ival[i][j];

        }
    }

    // output final result to 3 different files
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            ival[i][j] = (ival[i][j] / maxival) * 255;
            // fprintf(fo1, "%c", (char) ((int) (ival[i][j])));
            int edgeVal = (int)(ival[i][j]);
            int lowVal = 0;
            int highVal = 0;
            
            if (edgeVal > lowThreshold)
                lowVal = 255;

            if (edgeVal > highTreshHold)
                highVal = 255;

            fprintf(sobelmag, "%c", (char)edgeVal);
            fprintf(sobelout1, "%c", (char)lowVal);
            fprintf(sobelout2, "%c", (char)highVal);

        }
    }

}