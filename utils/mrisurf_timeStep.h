#pragma once
/*
 *
 */
/*
 * surfaces Author: Bruce Fischl, extracted from mrisurf.c by Bevin Brett
 *
 * $ Copyright © 2021 The General Hospital Corporation (Boston, MA) "MGH"
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
// Configurable support for checking that some of the parallel loops get the same
// results regardless of thread count
//
// Two common causes of this being false are
//          floating point reductions
//          random numbers being generated by parallel code 
//

#include "mrisurf_deform.h"

#define MAX_MM          (MAX_DIM / 10.0f)
#define MAX_PLANE_MM    (100 * 10.0f)
#define MAX_MOMENTUM_MM 1
#define MIN_MM          0.001

int mrisClearMomentum(MRI_SURFACE *mris);

double mrisAdaptiveTimeStep        (MRI_SURFACE *mris, INTEGRATION_PARMS *parms);
double mrisAsynchronousTimeStep    (MRI_SURFACE *mris, float momentum, float dt, MHT *mht, float max_mag);
double mrisAsynchronousTimeStepNew (MRI_SURFACE *mris, float momentum, float dt, MHT *mht, float max_mag);

int    mrisScaleTimeStepByCurvature(MRI_SURFACE *mris);
