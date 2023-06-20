#include "stdafx.h"
#include "SndComp.h"
#include "SndCompDlg.h"
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <math.h>
#include <fcntl.h>
#include <ctype.h>
#include <float.h>


/*****************************************************************************
*   Defines
*****************************************************************************/
#define		HEADER_ERROR	-32768

#define EOL         0x0d
#define CR          0x0a
#define BELL_SOUND  0x07

#define	FALSE		0
#define	TRUE		1
#define	PERMS		0666

#define TYPE_AIFF   0
#define TYPE_WAV    1

/*****************************************************************************
*   Data Structures
*****************************************************************************/
typedef signed char		INT8 ;
typedef signed short	INT16 ;
typedef signed long		INT32 ;
typedef unsigned char	UINT8 ;
typedef unsigned short	UINT16 ;
typedef unsigned long   UINT32 ;

#include "sfhdr.h"


/*****************************************************************************
*	Global variables
*****************************************************************************/
INT32           SR;
INT32           gate = 0;

/*****************************************************************************
*	External variables
*****************************************************************************/

/*****************************************************************************
*	Local variables
*****************************************************************************/

/*****************************************************************************
*	Function prototypes
*****************************************************************************/
void		AddDefaultExtension (char *SourceName, char *DestFile, char *ext) ;
void		PrintUsage();
UINT16	SWAP16 (UINT16 Value);
UINT32	SWAP32(UINT32 Value);
INT32		str2num(char *string);
void		getstr(char *pStr, FILE* fptr);
INT32		getSoundTime(CFile &SoundFile);
void		getNextFile(FILE *fileptr, char *filename);
void		WriteSoundBlock(FILE *fileptr, char *filename, INT16 filenum);
void		WriteKeymapBlock(FILE *fileptr, INT16 filenum);
void		WriteEnvelopeBlock(FILE *fileptr, INT16 filenum, INT32 time, int  Looped);
void		WriteInstBlock(FILE *fileptr, INT16 numfiles);
void		putstring(char *pStr, FILE *pFile);
int		LoadAIFFhdr(t_COMM_CHUNK  *comm, CFile &SoundFile);
int		LoopCheck(char *SourceFile);



int MakeInst (FILE *inhandle, CString *FileTable)
{
	INT8    			HeaderType, *ptr;
	INT16   			*Buffer, HdrBytes;
	char           string[5], ch;
	INT32				outbytes, numbytes, numsamples;
	FILE           *outhandle, *pCurrentFile;
	CFile				CurrentFile;
	INT16          result = 0, numfiles;
	char           NumStr[15];
	char           SourceFile[15];
	INT32          i, index, j, SoundTime;
	float   			NormFactor;
	t_AIFF_HDR		aiff_hdr;
	char    			newfile[12];
	char				*OutputFile;
	char				path[1024];
	int				Looped;

#if 0

	CFileStatus		rStatus1;
	CFile				testFile;
	INT8				testbuffer[256] ;

	memset(testbuffer, 256, 0x00);
	result = testFile.Open("e:\\src\\PR\\tengine\\sounds\\monkey2p.aif", CFile::modeRead, NULL); 
	if(result != 0)
		testFile.Read( testbuffer, 256 );


#endif

	//	outhandle = fopen ("c:\\Turok\\sfx.inst", "wb") ;  // open output file
	outhandle = fopen ("e:\\src\\PR\\tengine\\sounds\\sfx.inst", "wb") ;  // open output file

	if(outhandle == NULL)
		return -32767;

	// get sample rate from file
	getstr(NumStr, inhandle);
	SR = str2num(NumStr);

	// get number of files from file
	getstr(NumStr, inhandle);
	numfiles = str2num(NumStr);
	
	for ( j = 0; j < numfiles; j++)
	{
		getNextFile(inhandle, SourceFile);
		Looped = LoopCheck(SourceFile);
 		strcpy(path, "e:\\src\\PR\\tengine\\sounds\\");		
		strcat(path, SourceFile);		

		//pCurrentFile = fopen (path, "r") ;
		result = CurrentFile.Open(path, CFile::modeRead, NULL); 

		if(result == 0)
		{
			return -(j+1);
		}

#if 0
		if ( pCurrentFile == NULL)
		{
			return -(j+1);
		}
#endif

		FileTable[j] = SourceFile; 
		SoundTime = getSoundTime(CurrentFile);
		if(SoundTime < 0)
		{
			//fclose(pCurrentFile);
			CurrentFile.Close();
			return HEADER_ERROR;
		}

		CurrentFile.Close();
		//fclose(pCurrentFile);
		WriteEnvelopeBlock(outhandle, j, SoundTime, Looped);
		WriteKeymapBlock(outhandle,j);
		WriteSoundBlock(outhandle, SourceFile, j);
		fputc(EOL, outhandle);
		fputc(CR, outhandle);
	}

    WriteInstBlock(outhandle, numfiles);
    fclose(outhandle);
	return numfiles;

}



/*****************************************************************************
*       Function Title: int LoopCheck(char *SourceFile)
******************************************************************************
*		Description:
*		Input:
*		Output:
*
*****************************************************************************/
int LoopCheck(char *SourceFile)
{
	int		i, Space = 0;;
	char		*pCh = SourceFile;

	
	//while((*pCh != EOL) && (*pCh != CR) && (*pCh != 0x00))
	while(*pCh)
	{	
		if(*pCh == ' ')
			Space = 1;

		if(Space && (*pCh == 'l'))
		{
			pCh--;
			*pCh = 0;
			return 1;
		}

		pCh++;
	}
	
	return 0;
}

/*****************************************************************************
*       Function Title: void WriteSoundBlock(FILE *fileptr, INT16 filenum);
******************************************************************************
*		Description:
*		Input:
*		Output:
*
*****************************************************************************/
void WriteSoundBlock(FILE *fileptr, char *filename, INT16 filenum)
{
   char    str[128];
	char 	DestFile[20];



    sprintf(str, "sound sound%d", filenum+1);
    putstring(str, fileptr);
    putstring("{", fileptr);

	AddDefaultExtension (filename, DestFile, "n64");
    sprintf(str, "\tuse (\"%s\");",  DestFile);
    putstring(str, fileptr);
    putstring("\tkeymap = key1;", fileptr);
    putstring("\tpan    = 64;", fileptr);
    putstring("\tvolume = 127;", fileptr);
    sprintf(str, "\tenvelope = env%d;", filenum+1);
    putstring(str, fileptr);
    putstring("}", fileptr);

}

/*****************************************************************************
*       Function Title: void WriteKeymapBlock(FILE *fileptr, INT16 filenum);
******************************************************************************
*		Description:
*       Input:
*		Output:
*
*****************************************************************************/
void WriteKeymapBlock(FILE *fileptr, INT16 filenum)
{

    int  i;
    char *strings[9];
    char str1[20];

    sprintf(str1,  "keymap key%d", filenum+1);


    i = 0;
    strings[i++] = str1;
    strings[i++] =         "{";
    strings[i++] =     "\tvelocityMin = 0;";
    strings[i++] =     "\tvelocityMax = 127;";
    strings[i++] =     "\tkeyMin      = 41;";
    strings[i++] =     "\tkeyMax      = 41;";
    strings[i++] =     "\tkeyBase     = 41;";
    strings[i++] =     "\tdetune      = 0;";
    strings[i++] =     "}";

    for ( i = 0; i < 9; i++ )
    {
        putstring(strings[i], fileptr);
    }

}

/*****************************************************************************
*       Function Title: void WriteEnvelopeBlock(FILE *fileptr, INT16 filenum, INT32 time, int  Looped)
******************************************************************************
*		Description:
*		Input:
*		Output:
*
*****************************************************************************/
void WriteEnvelopeBlock(FILE *fileptr, INT16 filenum, INT32 time, int  Looped)
{

    int  i;
    char *strings[9];
    char str1[30];
    char str2[30];

	if(Looped)
	    sprintf(str1,  "\tdecayTime       = %d;", -1);
	else	
	    sprintf(str1,  "\tdecayTime       = %d;", time);

    sprintf(str2,  "envelope env%d", filenum+1);


    i = 0;
    strings[i++] = str2;
    strings[i++] =         "{";
    strings[i++] =     "\tattackTime      = 0;";
    strings[i++] =     "\tattackVolume    = 127;";
    strings[i++] = str1;
    strings[i++] =     "\tdecayVolume     = 127;" ;
    strings[i++] =     "\treleaseTime     = 0;";
    strings[i++] =     "\treleaseVolume   = 0;";
    strings[i++] =     "}";


    for ( i = 0; i < 9; i++ )
    {
        putstring(strings[i], fileptr);
    }


}


/*****************************************************************************
*       Function Title: void WriteInstBlock(FILE *fileptr, INT16 filenum);
******************************************************************************
*		Description:
*		Input:
*		Output:
*
*****************************************************************************/
void    WriteInstBlock(FILE *fileptr, INT16 numfiles)
{

    char    *strings[4];
    char    soundstr[25];
    int     i = 0;

    strings[i++] = "instrument inst1";
    strings[i++] = "{";
    strings[i++] = "\tvolume = 127;";
    strings[i++] = "\tpan    = 64;";


    for ( i = 0; i < 4; i++ )
    {
        putstring(strings[i], fileptr);

    }

    for ( i = 0; i < numfiles; i++ )
    {
        sprintf(soundstr, "\tsound  = sound%d;", i+1);
        putstring(soundstr, fileptr);
    }

    putstring("}", fileptr);

    i = 0;
    strings[i++] = "bank Wave1";
    strings[i++] = "{";
    strings[i++] = "\tinstrument [0] = inst1;";
    strings[i++] = "}";

    for ( i = 0; i < 4; i++ )
    {
       putstring(strings[i], fileptr);
    }

}

/*****************************************************************************
*       Function Title: void getNextFile(FILE *fileptr, char *filename)
******************************************************************************
*       Description:    getNextFile
*		Input:
*		Output:
*
*****************************************************************************/
void getNextFile(FILE *fileptr, char *filename)
{
    char       ch, pStr[128];
    int         i, j = 0;

    getstr(pStr, fileptr);
    strcpy(filename, pStr);
}


/*****************************************************************************
*       Function Title: INT32 getSoundTime(FILE *SoundFile)
******************************************************************************
*       Description:    getSoundTime
*		Input:
*		Output:
*
*****************************************************************************/
INT32 getSoundTime(CFile &SoundFile)
{
    t_COMM_CHUNK    comm;
    INT32           num_samples;
    float           time;
    INT16           numread;
	 int					result;
	


   result = LoadAIFFhdr(&comm, SoundFile);
	if(result < 0)
		return -1;

#if 0
    printf("FORM ID:%c%c%c%c\n", aiff_hdr.FORM_ID[0],aiff_hdr.FORM_ID[1],
                            aiff_hdr.FORM_ID[2],aiff_hdr.FORM_ID[3]) ;

    printf("COMM ID:%c%c%c%c\n", aiff_hdr.COMM_ID[0],aiff_hdr.COMM_ID[1],
                            aiff_hdr.COMM_ID[2],aiff_hdr.COMM_ID[3]) ;
    printf("COMM Length:%d\n", SWAP32(aiff_hdr.COMM_Length));
    printf("COMM numChannels:%d\n", SWAP16(aiff_hdr.numChannels));
    printf("COMM NumSampleFrames:%d\n", SWAP16(aiff_hdr.NumSampleFrames));
    printf("COMM sampleSize:%d\n", SWAP16(aiff_hdr.sampleSize));


    printf("SSND ID:%c%c%c%c\n", aiff_hdr.SSND_ID[0],aiff_hdr.SSND_ID[1],
                            aiff_hdr.SSND_ID[2],aiff_hdr.SSND_ID[3]) ;
    printf("SSND Length:%d\n", SWAP32(aiff_hdr.SSND_Length)) ;
    printf("SSND offset:%d\n", SWAP32(aiff_hdr.offset)) ;
    printf("SSND blockSize:%d\n", SWAP32(aiff_hdr.blockSize)) ;
#endif


    num_samples = SWAP32(comm.NumSampleFrames);
    time =  1.0/SR;
    time *=  num_samples;

    return (INT32)(time*1000000);
}

/*****************************************************************************
*       Function Title: void PrintUsage()
******************************************************************************
*       Description:    PrintUsage
*		Input:
*		Output:
*
*****************************************************************************/
void PrintUsage()
{
    printf("Usage: makeinst <filename> \n");
}


/*****************************************************************************
*       Function Title: void getstr(char *NumStr, FILE* fptr)
******************************************************************************
*       Description:    This will get a line from the file
*		Input:
*		Output:
*
*****************************************************************************/
void getstr(char *pStr, FILE* fptr)
{
    int         i;
    char        ch;

    i = 0;
    ch = getc(fptr);

    while(ch != CR)
    {
        pStr[i++] = ch;
        ch = getc(fptr);
    }

    pStr[i] = 0;

}

/*****************************************************************************
*       Function Title: INT32 str2num(char *string)
******************************************************************************
*       Description:    This will convert a string into a number
*		Input:
*		Output:
*
*****************************************************************************/
INT32 str2num(char *string)
{
    INT16       i, j, k;
    char        ch, zero = '0';
    INT32       num = 0;
    INT32       MagnitudePos;


    i = 0;
    ch = string[i++];
    while (ch)
        ch = string[i++];

    i -= 2;
    for (j = 0;i >= 0; i--, j++)
    {

        MagnitudePos = 1;
        for (k = 0; k < j; k++)
        {
            MagnitudePos *= 10;
        }

        num = ((string[i]-zero) * MagnitudePos) + num;
    }


    return num;

}


/*****************************************************************************
*       Function Title: void AddDefaultExtension (char *SourceName, char *DestFile, char *ext) ;
******************************************************************************
*       Description:    AddDefaultExtension
*		Input:
*		Output:
*
*****************************************************************************/
void AddDefaultExtension (char *SourceName, char *DestFile, char *ext)
{
	int		i;
	char 	*ch;
	char 	*SourcePtr;
	char 	*DestPtr;


	ch  = SourceName;
	SourcePtr = SourceName;
	DestPtr = DestFile;
	while(*ch != '.')
	{
		if(isupper(*ch))
			*ch = tolower(*ch);

		*DestPtr++ = *SourcePtr++;
		ch++;
	}

	*DestPtr++ = *SourcePtr++;


	ch  = ext;
	while(*ch != 0)
	{
		*DestPtr++ = *ch++;
	}

	*DestPtr = 0;	// terminate string

}

/*****************************************************************************
*       Function Title: UINT16 SWAP16 (UINT16 Value)
******************************************************************************
*       Description:    This will swap bytes
*		Input:
*		Output:
*
*****************************************************************************/
UINT16 SWAP16 (UINT16 Value)
{
	return  ((Value >> 8)) |
			((Value << 8)) ;
}

/*****************************************************************************
*       Function Title: UINT32 SWAP32 (UINT16 Value)
******************************************************************************
*       Description: This will swap bytes
*		Input:
*		Output:
*
*****************************************************************************/
UINT32 SWAP32(UINT32 Value)
{
    return (unsigned long)((Value >> 24)) |
			((Value >>  8) & 0x0000FF00) |
			((Value <<  8) & 0x00FF0000) |
			((Value << 24)) ;
}


/*****************************************************************************
*       Function Title: void LoadAIFFhdr(FILE *SoundFile)
******************************************************************************
*     Description: This will load in an AIFF header. Although it looks kind of messy.
*                   I had to do it this way because the damn compiler kept on padding
*                   out the header.
*		Input:
*		Output:
*
*****************************************************************************/
int LoadAIFFhdr(t_COMM_CHUNK  *comm, CFile &SoundFile)
{
    #define     BUFFER_SIZE     256

    int             result = -1, bytecount = 0;
    static char     buffer[BUFFER_SIZE];
    char            *pStr;
	 CFile			  File;


#if 0
 memset(buffer, 0x00, BUFFER_SIZE);
	result = File.Open("e:\\src\\PR\\tengine\\sounds\\monkey2p.aif", CFile::modeRead, NULL); 
	if(result != 0)
		File.Read( buffer, 256 );
#endif


	 memset(buffer, 0x00, BUFFER_SIZE);
    //result = fread(buffer, BUFFER_SIZE, 1, SoundFile);
	result = SoundFile.Read( buffer, BUFFER_SIZE );

    pStr = buffer;

	 if(result != BUFFER_SIZE)
       return -1; 

    if(memcmp(pStr, "FORM", 4) != 0)
       return -1; 

    while ( pStr != (buffer+BUFFER_SIZE) )
    {
        if(memcmp(pStr, "COMM", 4) == 0)
        {
            memcpy(comm, pStr, 10);
            memcpy(&comm->NumSampleFrames, pStr+10, 6);
            break;
        }
        else
            pStr++;
    }

    if( pStr == (buffer+BUFFER_SIZE) )
		return -1;		




#if 0
    // read indata up to "aiff_hdr.numChannels"
    if(fread(hdr, 22, 1, SoundFile) <  1)
       return -1; 
		 //printf("error in reading file\n");

    // read indata rest
    if(fread(&hdr->NumSampleFrames, 30, 1, SoundFile) <  1)
       return -1; 
       //printf("error in reading file\n");
#endif

	return 0;
}

/*****************************************************************************
*       Function Title: UINT32 SWAP32 (UINT16 Value)
******************************************************************************
*       Description: This will swap bytes
*		Input:
*		Output:
*
*****************************************************************************/
void putstring(char *pStr, FILE *pFile)
{
   fputs(pStr, pFile);
   fputc(EOL, pFile);
   fputc(CR, pFile);

}

