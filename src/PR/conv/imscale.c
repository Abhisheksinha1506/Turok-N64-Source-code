/************************************************************************\
 *                                                                        *
 *               Copyright (C) 1995, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 \************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <PRimage.h>

char *InputFileName, *OutputFileName;

#define PI 3.14159265359

#define XAXIS 0
#define YAXIS 1

float XScale = -1.0;
float YScale = -1.0;

struct ImageStruct
{
  unsigned short **Red,  **Green,  **Blue;
  unsigned short ImageWidth, ImageHeight;   
} *CurrentImage, *NewImage;

void usage(void)
{
  fprintf(stderr, "usage: imscale -i input.rgb -o output.rgb -x xscale -y yscale \n");
  exit(1);
}

extern float ImageValue(int x, int y, int channel)
{
  if ((x < 0) || (y < 0) ||
      (x > CurrentImage->ImageWidth  - 1) ||
      (y > CurrentImage->ImageHeight - 1))
    return(0.0);
  else
    {
      switch (channel)
	{
	case 0:
	  return(CurrentImage->Red[y][x]   / 255.0);
	  break;
	case 1:
	  return(CurrentImage->Green[y][x] / 255.0);
	  break;
	case 2:
	  return(CurrentImage->Blue[y][x]  / 255.0);
	  break;
	default:
	  fprintf(stderr, "!!!ERROR: incorrect plane in ImageValue \n");
	  exit(1);      
	}
    }
}

void MallocImage(struct ImageStruct **Image, unsigned short Width, unsigned short Height)
{
    int i;

    *Image = (struct ImageStruct *) malloc(sizeof(struct ImageStruct));
    (*Image)->ImageWidth  = Width;
    (*Image)->ImageHeight = Height;
    
    (*Image)->Red    = (unsigned short **) malloc(Height * sizeof(unsigned short *));
    (*Image)->Green  = (unsigned short **) malloc(Height * sizeof(unsigned short *));
    (*Image)->Blue   = (unsigned short **) malloc(Height * sizeof(unsigned short *));

    for (i=0; i < Height; i++)
      {	  
	(*Image)->Red[i]    = (unsigned short *)malloc(Width * sizeof(unsigned short));
	(*Image)->Green[i]  = (unsigned short *)malloc(Width * sizeof(unsigned short));
	(*Image)->Blue[i]   = (unsigned short *)malloc(Width * sizeof(unsigned short));
      }
}

void ParseArguments(int argc, char **argv)
{
    int c;
    extern char *optarg;
    extern int optind;
    char *ofile = NULL;

    while ((c = getopt(argc, argv, "i:o:x:y:")) != EOF)
	switch (c)
	    {
	    case 'i':
	      InputFileName = strdup(optarg);
	      break;
	    case 'o':
	      OutputFileName = strdup(optarg);
	      break;
	    case 'x':
	      XScale = (float) atof(optarg);
	      break;
	    case 'y':
	      YScale = (float) atof(optarg);
	      break;
	    case '?':
	      usage();
	      break;		
	    }    
    
    if ((InputFileName == NULL) ||
	(OutputFileName == NULL) ||
	(XScale < 0.0) || (YScale < 0.0))
	usage();
}

void ReadInputFile(void)
{
  IMAGE *image;
  unsigned short Height, Width;
  int i;


  if ((image = iopen(InputFileName, "r")) == NULL)
    {
      fprintf(stderr, "Error, could not open input file %s \n", InputFileName);
      exit(1);
    }

  Height = image->ysize;
  Width  = image->xsize;  
  
  MallocImage(&CurrentImage, Width, Height);
  
  for (i=0; i< Height; i++)
    {
      getrow(image, CurrentImage->Red[i],   i, 0);
      getrow(image, CurrentImage->Green[i], i, 1);
      getrow(image, CurrentImage->Blue[i],  i, 2);   
    }

  iclose(image);
}

float Lanczos(float x)
{
  float PIx, PIx2;

  PIx = PI * x;
  PIx2 = PIx / 2.0;

  if ((x >= 2.0) || (x <= -2.0))
    return (0.0);
  else if (x == 0.0)
    return (1.0);
  else
    return(sin(PIx) / PIx * sin(PIx2) / PIx2);
}

ImMag(float Value, int Axis)
{
  int hsize, vsize, i, j, k, l, lMax, iEnd, jEnd;
  int LanczosWidthFactor;
  float *l0, *l1, OldLocation;
  int T, TempJump1, TempJump2;
  float F, PictureValue;

  if (Axis == XAXIS)
    {
      hsize = (int) ((float) CurrentImage->ImageWidth * Value);
      vsize = CurrentImage->ImageHeight;

      jEnd = hsize;
      iEnd = vsize;

      TempJump1 = (hsize - 1) * 3;
      TempJump2 = hsize * (vsize - 1) * 3 + TempJump1;
    }
  else
    {
      hsize = CurrentImage->ImageWidth;
      vsize = (int) ((float) CurrentImage->ImageHeight * Value);

      jEnd = vsize;
      iEnd = hsize;

      TempJump1 = 0;
      TempJump2 = 0;
    }

  MallocImage(&NewImage, hsize, vsize);

  if (Value >=1)
    LanczosWidthFactor = 1;
  else
    LanczosWidthFactor = (int) (1.0/Value);

  lMax = LanczosWidthFactor << 1;

  l0 = (float *) malloc(lMax * sizeof(float));
  l1 = (float *) malloc(lMax * sizeof(float));

  for (j=0; j<jEnd; j++)
    {
      OldLocation = ((float) j) / Value;
      T = (int) (OldLocation);
      F = OldLocation - (float) T;	

      for (l = 0; l < lMax; l++)
	{
	  l0[lMax-l-1] =
	    Lanczos(((float) (lMax-l-1) + F) / (float) LanczosWidthFactor);
	  l1[l] =
	    Lanczos(((float) (l + 1) - F) / (float) LanczosWidthFactor);
	}      
      
      for (i=0; i<iEnd; i++)
	{
	  for (k=0; k<3; k++)
	    {
	      PictureValue = 0.0;
	      
	      for (l=0; l < lMax; l++)
		{
		  PictureValue += l1[l] *
		    ((Axis == XAXIS) ?
		     ImageValue(T+l+1, i, k) :
		     ImageValue(i, T+l+1, k));
		  PictureValue += l0[lMax-l-1] *
		    ((Axis == XAXIS) ?
		     ImageValue(T-lMax+l+1, i, k) :
		     ImageValue(i, T-lMax+l+1, k));
		}
	      
	      PictureValue /= (float) LanczosWidthFactor;	      
	      if (PictureValue > 1.0) PictureValue = 1.0;
	      else if (PictureValue < 0.0) PictureValue = 0.0;
	      
	      if (Axis == XAXIS)
		switch (k)
		  {
		  case 0:
		    NewImage->Red[i][j]   = (unsigned short) (255.0 * PictureValue + 0.5);
		    break;
		  case 1:
		    NewImage->Green[i][j] = (unsigned short) (255.0 * PictureValue + 0.5);
		    break;
		  case 2:
		    NewImage->Blue[i][j]  = (unsigned short) (255.0 * PictureValue + 0.5);
		    break;		  
		  }
	      else
		switch (k)
		  {
		  case 0:
		    NewImage->Red[j][i]   = (unsigned short) (255.0 * PictureValue + 0.5);
		    break;
		  case 1:
		    NewImage->Green[j][i] = (unsigned short) (255.0 * PictureValue + 0.5);
		    break;
		  case 2:
		    NewImage->Blue[j][i]  = (unsigned short) (255.0 * PictureValue + 0.5);
		    break;		  
		  };
	    }	  
	}
    }
  
  free(l0);
  free(l1);

  CurrentImage = NewImage;
}


void ApplyScalings(void)
{
  if (XScale != 1.0) ImMag(XScale, XAXIS);
  if (YScale != 1.0) ImMag(YScale, YAXIS);
}

void WriteOutputFile(void)
{
    IMAGE *image;
    int i;

    if (OutputFileName == NULL) return;

    if ((image = iopen(OutputFileName, "w", RLE(1), 3,
		       CurrentImage->ImageWidth, CurrentImage->ImageHeight, 3)) == NULL)
	{
	    fprintf(stderr, "Error, could not open output file %s \n", OutputFileName);
	    exit(1);
	}

    for (i = 0; i < CurrentImage->ImageHeight ; i++)
	{
	    putrow(image, CurrentImage->Red[i],   i, 0);
	    putrow(image, CurrentImage->Green[i], i, 1);
	    putrow(image, CurrentImage->Blue[i],  i, 2);
	}

    iclose(image);
}

void Cleanup(void)
{
}

main(int argc, char **argv)
{
  ParseArguments(argc, argv);
  ReadInputFile();
  ApplyScalings();
  WriteOutputFile();
  Cleanup();
  
  exit(0);
}
