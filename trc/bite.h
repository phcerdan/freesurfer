/**
 * @file  bite.h
 * @brief Tractography data and methods for an individual voxel
 *
 * Tractography data and methods for an individual voxel
 */
/*
 * Original Author: Anastasia Yendiki
 * CVS Revision Info:
 *
 * Copyright © 2011 The General Hospital Corporation (Boston, MA) "MGH"
 *
 * Terms and conditions for use, reproduction, distribution and contribution
 * are found in the 'FreeSurfer Software License Agreement' contained
 * in the file 'LICENSE' found in the FreeSurfer distribution, and here:
 *
 * https://surfer.nmr.mgh.harvard.edu/fswiki/FreeSurferSoftwareLicense
 *
 * Reporting: freesurfer@nmr.mgh.harvard.edu
 *
 */

#ifndef BITE_H
#define BITE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <math.h>
#include "mri.h"

class Bite {
  public:
    Bite(MRI *Dwi, MRI **Phi, MRI **Theta, MRI **F,
         MRI **V0, MRI **F0, MRI *D0,
         int CoordX, int CoordY, int CoordZ);
    ~Bite();

  private:
    static int mNumDir, mNumB0, mNumTract, mNumBedpost,
               mAsegPriorType, mNumTrain;
    static float mFminPath;
    static std::vector<float> mGradients,	// [3 x mNumDir]
                              mBvalues;		// [mNumDir]
    static std::vector< std::vector<unsigned int> > mAsegIds;

    bool mIsPriorSet;
    int mCoordX, mCoordY, mCoordZ, mPathTract;
    float mS0, mD, mPathPrior0, mPathPrior1,
          mLikelihood0, mLikelihood1, mPrior0, mPrior1;
    std::vector<float> mDwi;		// [mNumDir]
    std::vector<float> mPhiSamples;	// [mNumTract x mNumBedpost]
    std::vector<float> mThetaSamples;	// [mNumTract x mNumBedpost]
    std::vector<float> mFSamples;	// [mNumTract x mNumBedpost]
    std::vector<float> mPhi;		// [mNumTract]
    std::vector<float> mTheta;		// [mNumTract]
    std::vector<float> mF;		// [mNumTract]
    std::vector<unsigned int> mAsegTrain, mPathTrain, mAseg,
                              mAsegDistTrain, mAsegDist;
    std::vector< std::vector<float> > mAsegPrior0, mAsegPrior1;

  public:
    static void SetStatic(const char *GradientFile, const char *BvalueFile,
                          int NumTract, int NumBedpost, float FminPath);
    static void SetStaticPrior(int AsegPriorType,
                               const std::vector<
                                     std::vector<unsigned int> > &AsegIds,
                               int NumTrain);
    static int GetNumTract();
    static int GetNumDir();
    static int GetNumB0();
    static int GetNumBedpost();

    bool IsPriorSet();
    void SetPrior(MRI *Prior0, MRI *Prior1,
                  std::vector<MRI *> &AsegPrior0,
                  std::vector<MRI *> &AsegPrior1,
                  MRI *AsegTrain, MRI *PathTrain, MRI *Aseg,
                  int CoordX, int CoordY, int CoordZ);
    void ResetPrior();
    void SampleParameters();
    void ComputeLikelihoodOffPath();
    void ComputeLikelihoodOnPath(float PathPhi, float PathTheta);
    void ChoosePathTractAngle(float PathPhi, float PathTheta);
    void ChoosePathTractLike(float PathPhi, float PathTheta);
    void ComputePriorOffPath();
    void ComputePriorOnPath();
    bool IsFZero();
    bool IsThetaZero();
    float GetLikelihoodOffPath();
    float GetLikelihoodOnPath();
    float GetPathPriorOffPath();
    float GetPathPriorOnPath();
    float GetPriorOffPath();
    float GetPriorOnPath();
    float GetPosteriorOffPath();
    float GetPosteriorOnPath();
};

#endif

