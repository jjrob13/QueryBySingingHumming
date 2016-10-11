////////////////////////////////////////////////////////////////////////////////
/**
 * @file   STypes.h
 * @author Wang Lei <wanglei.will@snda.com>
 * @date   Thu Aug 19 10:37:14 2010
 * 
 * @brief  
 * 
 * 
 */
////////////////////////////////////////////////////////////////////////////////

#ifndef SDHumming_STYPES_H_
#define SDHumming_STYPES_H_

#include <limits.h>

#define ERROR_CODE_FILE_CANNOT_OPEN -1001
#define ERROR_CODE_MODELINFO_WRONG_FORMAT -1002
#define ERROR_CODE_CANNOT_ALLOC_MEM -1003
#define ERROR_CODE_LOAD_MODEL_ERROR -1004
#define ERROR_CODE_TOO_SHORT_INPUT -1005

#define FLOAT_EQUAL(a,b) (fabs((a)-(b))<EPSILON3)
#define MAX_NUMBER INT_MAX
#define EPSILON 1e-6f
#define EPSILON3 1e-3f
#define LINEREAD 1024 
#define PI 3.141592653589793  

#define FUSION_RATIO 0.66f  

#define MAX_SIG_SIZE   200
#define MAX_ITERATIONS 500
#define EMD_INFINITY       1e20f
#define MAX_NUMBER INT_MAX
#define FORGET_FACTOR 0.93f
#define MAX_FLOW_NUM 200

#define EMD_SCALING_TIMES 4
#define EMD_SCALING_STEP 0.15f
#define EMD_SCALING_OFFSET ((EMD_SCALING_TIMES-1)*EMD_SCALING_STEP/2)

#define MAX_SONGS_NUMBER 1000000

/* the upper bound of pitch*/
#define MAX_PITCH_VALUE 1000 
/* the lower bound of pitch*/   
#define MIN_PITCH_VALUE 60    
/* the frame length, in milliseconds*/ 
#define FRAME_LEN_MS 20       
/* the frame shift, in milliseconds*/ 
#define FRAME_SHT_MS 10       
/* the value for note sequence normalization*/ 
#define NOTE_NORMALIZE_VALUE 47.6237f 
/* the value for pitch sequence normalization*/ 
#define PITCH_NORMALIZE_VALUE 7.0f
/* the half window size of median filter*/ 
#define MEDIAN_FILTER_HALF_WINDOWS_SIZE 2
/* the window size of median filter*/ 
#define MEDIAN_FILTER_WINDOWS_SIZE 5

#define MAX_EMD_FEASIZE 200

typedef struct {
	float fNoteValue; /* note value */
	float fNoteDuration; /* note length, in frames */
}SNote; 

typedef struct {
	int nSongID;     /* song id */
	int nNoteNum;    /* total note number contained in the song */
	SNote* sNotes;   /* note sequence */
	int nPhraseNum;  /* total phrase number contained in the song */
	int* PhrasePos;  /* phrase offsets */
}SModel;

/* struct store the mid-term result generated by note-based matching method */
typedef struct {
	int nModelID;    /* song id */
	int nPhraseID;   /* phrase id */
	float fScore;    /* similarity score for the query againest on the current model */
	float fScale;    /* scaling value */
}NoteBasedResStru;

/* struct store the result generated by frame-based matching method */
typedef struct  {
	int nModelID;    /* song id */
	int nOffset;     /* the phrase position in the song, measured by the offset to the start of the song */
	float fScore;    /* similarity score for the query againest on the current model */
}FrameBasedResStru;

typedef struct SStru {
	SNote fNote;
	struct SStru *Next;
}SNoteSequenceStru;
  
typedef struct SWaveDataStru{
	int fs;           /* sampling rate */
	int nDataLen;     /* total length of the wave data, the header is skipped */
	float *fDataBuf;  /* wave data buffer */ 
}SWaveDataStru;

/* wave header struct */ 
typedef  struct WAVE_HEADERTag{
	char RIFF[4];
	long Whgilelen;
	char WAVEfmt[8];
	long version;
	short  FormatTag;
	short  Channels;
	long SamplePerSec;
	long AvgBytesPerSec;
	short  blockalign;
	short  BitPerSample;
	char data[4];
	long Pcmfilelen;
}WAVE_HEADER;

typedef struct SPolar{
	double M;  /* magnitude */
	double P;  /* phase */
} SPolar, *aSPolar;

typedef struct ComplexStru{
	double R;  /* real */
	double I;  /* image */
} Complex, *sComplexStru;

#endif //SDHumming_STYPES_H_