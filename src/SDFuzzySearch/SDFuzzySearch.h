////////////////////////////////////////////////////////////////////////////////
/**
 * @file   SDFuzzySearch.h
 * @author Wang Lei <wanglei.will@snda.com>
 * @date   Thu Aug 19 10:37:14 2010
 * 
 * @brief  
 * 
 * 
 */
////////////////////////////////////////////////////////////////////////////////
#ifndef SDHumming_SEARCH_H_
#define SDHumming_SEARCH_H_

#include "SFrameMatch.h"
#include "SNoteMatch.h"
#include "SSearchCommon.h"

/*
*  Use segmented note sequence as input to measure two melody similarity,
*  which is fast but less accurate
*/
int SNoteBasedMatch(const SModel *SQBHModels, const int nModels, SNote *Query, int QueryLen,NoteBasedResStru *myEMDResStru,int nLen);
/*
*  Use pitch sequence as input to measure two melody similarity,
*  which is accurate but slow
*/
	int SFrameBasedMatch(const SModel *SQBHModels, const int nModels, float *m_pQueryPitchVector,
			  int m_nQueryPitchVectorLen, NoteBasedResStru *NoteBasedResStru, int nCandi, FrameBasedResStru *res);

#endif //SDHumming_SSEARCH_H_
