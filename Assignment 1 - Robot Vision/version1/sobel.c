#include <stdio.h>                          /* Sobel.c */
#include <math.h>

        int pic[256][256];
        int outpicx[256][256];
        int outpicy[256][256];
        int maskx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
        int masky[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
        double ival[256][256],maxival;

int main(argc,argv)
int argc;
char **argv;
{
  int i = 0;
  int j,p,q,mr,sum1,sum2;
  double threshold1, threshold2;
  FILE *fo1, *fo2, *fo3, *fp1, *fopen();
  char *foobar;

  //picture file
  argc--; argv++;
  foobar = *argv;
  fp1=fopen(foobar,"rb");

  //magnitude file
    argc--; argv++;
    foobar = *argv;
    fo1=fopen(foobar,"wb");

  //hi file
    argc--; argv++;
    foobar = *argv;
    fo2=fopen(foobar,"wb");

  //lo file
    argc--; argv++;
    foobar = *argv;
    fo3=fopen(foobar,"wb");

  // hi threshold to find the difference
  argc--; argv++;
    foobar = *argv;
    threshold1 = atoi(foobar);

  // lo threshold to find the difference
  argc--; argv++;
    foobar = *argv;
    threshold2 = atoi(foobar);

  //skip the header of the input pgm file
  char buffer[20];
  while (i<4) {
    fscanf(fp1,"%s", buffer);
    i++;
  }
  //header info for pgm viewer
  
  fprintf(fo1,"P5\n");
  fprintf(fo1,"%d %d\n", 256, 256);
  fprintf(fo1,"255\n");

  //header info for pgm viewer
  fprintf(fo2,"P5\n");
  fprintf(fo2,"%d %d\n", 256, 256);
  fprintf(fo2,"255\n");

  //header info for pgm viewer
  fprintf(fo3,"P5\n");
  fprintf(fo3,"%d %d\n", 256, 256);
  fprintf(fo3,"255\n");

  //magnitude image
  for (i=0;i<256;i++)
  { for (j=0;j<256;j++)
    {
      //scaling is done here
      ival[i][j] = (ival[i][j] / maxival) * 255;
      fprintf(fo1,"%c",(char)((int)(ival[i][j])));
    }
  }

  //threshold images
  //to mark as an edge: replace pixel value with 255, if no edge value is 0 slide 32
  for (i=0;i<256;i++)
  { for (j=0;j<256;j++)
    {
      //pixel brightness 255 or 0
      (ival[i][j] > threshold1) ? fprintf(fo2,"%c",(char)255) : fprintf(fo2,"%c",(char)0);

      (ival[i][j] > threshold2) ? fprintf(fo3,"%c",(char)255) : fprintf(fo3,"%c",(char)0);

    }
  }
}
