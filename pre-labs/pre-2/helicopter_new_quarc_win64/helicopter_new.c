/*
 * helicopter_new.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_new".
 *
 * Model version              : 11.8
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Fri Feb 27 10:15:31 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_new.h"
#include "helicopter_new_private.h"
#include "helicopter_new_dt.h"

/* Block signals (default storage) */
B_helicopter_new_T helicopter_new_B;

/* Continuous states */
X_helicopter_new_T helicopter_new_X;

/* Block states (default storage) */
DW_helicopter_new_T helicopter_new_DW;

/* Real-time model */
static RT_MODEL_helicopter_new_T helicopter_new_M_;
RT_MODEL_helicopter_new_T *const helicopter_new_M = &helicopter_new_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopter_new_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_new_output(void)
{
  /* local block i/o variables */
  real_T rtb_Sum5[4];
  real_T rtb_Clock;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_Clock_tmp;
  real_T rtb_Derivative;
  real_T rtb_Gain1_idx_2;
  real_T rtb_Gain1_idx_3;
  real_T *lastU;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopter_new_M)) {
    /* set solver stop time */
    if (!(helicopter_new_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_new_M->solverInfo,
                            ((helicopter_new_M->Timing.clockTickH0 + 1) *
        helicopter_new_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_new_M->solverInfo,
                            ((helicopter_new_M->Timing.clockTick0 + 1) *
        helicopter_new_M->Timing.stepSize0 +
        helicopter_new_M->Timing.clockTickH0 *
        helicopter_new_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_new_M)) {
    helicopter_new_M->Timing.t[0] = rtsiGetT(&helicopter_new_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopter_new_DW.IfActionSubsystem_SubsysRanBC);
  if (rtmIsMajorTimeStep(helicopter_new_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_new/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_new_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_new_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_new_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_new_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_new_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter_new_B.TravelCounttorad = helicopter_new_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter_new_P.TravelCounttorad_Gain;

    /* Gain: '<S12>/Gain' */
    helicopter_new_B.Gain = helicopter_new_P.Gain_Gain *
      helicopter_new_B.TravelCounttorad;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]1'
     */
    helicopter_new_B.Elevation = helicopter_new_P.elavation_offsetdeg1_Value +
      helicopter_new_B.Gain;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter_new_B.PitchCounttorad = helicopter_new_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    helicopter_new_B.Gain_i = helicopter_new_P.Gain_Gain_a *
      helicopter_new_B.PitchCounttorad;
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopter_new_P.TravelTransferFcn_C *
    helicopter_new_X.TravelTransferFcn_CSTATE;
  rtb_Clock += helicopter_new_P.TravelTransferFcn_D *
    helicopter_new_B.TravelCounttorad;

  /* Gain: '<S13>/Gain' */
  helicopter_new_B.Gain_d = helicopter_new_P.Gain_Gain_l * rtb_Clock;

  /* Clock: '<S3>/Clock' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopter_new_P.PitchTransferFcn_C *
    helicopter_new_X.PitchTransferFcn_CSTATE;
  rtb_Clock += helicopter_new_P.PitchTransferFcn_D *
    helicopter_new_B.PitchCounttorad;

  /* Gain: '<S10>/Gain' */
  helicopter_new_B.Gain_b = helicopter_new_P.Gain_Gain_ae * rtb_Clock;
  if (rtmIsMajorTimeStep(helicopter_new_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopter_new_B.ElevationCounttorad = helicopter_new_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopter_new_P.ElevationCounttorad_Gain;

    /* Gain: '<S7>/Gain' */
    helicopter_new_B.Gain_e = helicopter_new_P.Gain_Gain_lv *
      helicopter_new_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_new_B.Elevation_g = helicopter_new_B.Gain_e +
      helicopter_new_P.elavation_offsetdeg_Value;
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopter_new_P.ElevationTransferFcn_C *
    helicopter_new_X.ElevationTransferFcn_CSTATE;
  rtb_Clock += helicopter_new_P.ElevationTransferFcn_D *
    helicopter_new_B.ElevationCounttorad;

  /* Gain: '<S8>/Gain' */
  helicopter_new_B.Gain_dg = helicopter_new_P.Gain_Gain_n * rtb_Clock;
  if (rtmIsMajorTimeStep(helicopter_new_M)) {
    /* SignalConversion generated from: '<Root>/To File' */
    helicopter_new_B.TmpSignalConversionAtToFileInpo[0] =
      helicopter_new_B.Elevation;
    helicopter_new_B.TmpSignalConversionAtToFileInpo[1] =
      helicopter_new_B.Gain_d;
    helicopter_new_B.TmpSignalConversionAtToFileInpo[2] =
      helicopter_new_B.Gain_i;
    helicopter_new_B.TmpSignalConversionAtToFileInpo[3] =
      helicopter_new_B.Gain_b;
    helicopter_new_B.TmpSignalConversionAtToFileInpo[4] =
      helicopter_new_B.Elevation_g;
    helicopter_new_B.TmpSignalConversionAtToFileInpo[5] =
      helicopter_new_B.Gain_dg;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter_new_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_new_DW.ToFile_IWORK.Count * (6 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_new_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[6 + 1];
          helicopter_new_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_new_M->Timing.t[1];
          u[1] = helicopter_new_B.TmpSignalConversionAtToFileInpo[0];
          u[2] = helicopter_new_B.TmpSignalConversionAtToFileInpo[1];
          u[3] = helicopter_new_B.TmpSignalConversionAtToFileInpo[2];
          u[4] = helicopter_new_B.TmpSignalConversionAtToFileInpo[3];
          u[5] = helicopter_new_B.TmpSignalConversionAtToFileInpo[4];
          u[6] = helicopter_new_B.TmpSignalConversionAtToFileInpo[5];
          if (fwrite(u, sizeof(real_T), 6 + 1, fp) != 6 + 1) {
            rtmSetErrorStatus(helicopter_new_M,
                              "Error writing to MAT-file simout.mat");
            return;
          }

          if (((++helicopter_new_DW.ToFile_IWORK.Count) * (6 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file simout.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_new_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_new_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_new_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter_new_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_new_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Clock = pDataValues[currTimeIndex];
        } else {
          rtb_Clock = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Clock = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 141;
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace2' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_new_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_new_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_new_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = helicopter_new_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_new_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Sum5[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 141;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Sum5[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 141;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 4; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Sum5[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 141;
          }
        }
      }
    }
  }

  /* Gain: '<S2>/Gain1' */
  rtb_Gain1_idx_2 = helicopter_new_P.Gain1_Gain * helicopter_new_B.Gain_i;
  rtb_Gain1_idx_3 = helicopter_new_P.Gain1_Gain * helicopter_new_B.Gain_b;

  /* Sum: '<Root>/Sum5' incorporates:
   *  Gain: '<S2>/Gain1'
   */
  rtb_Sum5[0] = helicopter_new_P.Gain1_Gain * helicopter_new_B.Elevation -
    rtb_Sum5[0];
  rtb_Sum5[1] = helicopter_new_P.Gain1_Gain * helicopter_new_B.Gain_d -
    rtb_Sum5[1];
  rtb_Sum5[2] = rtb_Gain1_idx_2 - rtb_Sum5[2];
  rtb_Sum5[3] = rtb_Gain1_idx_3 - rtb_Sum5[3];

  /* Clock: '<S3>/Clock' incorporates:
   *  Gain: '<Root>/Gain'
   *  Sum: '<Root>/Sum4'
   *  Sum: '<S5>/Sum2'
   */
  rtb_Clock -= ((helicopter_new_P.K[0] * rtb_Sum5[0] + helicopter_new_P.K[1] *
                 rtb_Sum5[1]) + helicopter_new_P.K[2] * rtb_Sum5[2]) +
    helicopter_new_P.K[3] * rtb_Sum5[3];
  rtb_Clock -= rtb_Gain1_idx_2;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum3'
   */
  rtb_Gain1_idx_2 = (helicopter_new_P.K_pp * rtb_Clock - helicopter_new_P.K_pd *
                     rtb_Gain1_idx_3) + helicopter_new_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_new_X.Integrator_CSTATE >= helicopter_new_P.Integrator_UpperSat)
  {
    helicopter_new_X.Integrator_CSTATE = helicopter_new_P.Integrator_UpperSat;
  } else {
    if (helicopter_new_X.Integrator_CSTATE <=
        helicopter_new_P.Integrator_LowerSat) {
      helicopter_new_X.Integrator_CSTATE = helicopter_new_P.Integrator_LowerSat;
    }
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  Integrator: '<S3>/Integrator'
   */
  rtb_Clock = helicopter_new_X.Integrator_CSTATE;

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/elevation_ref'
   *  Gain: '<S2>/Gain1'
   */
  rtb_Derivative = helicopter_new_P.elevation_ref_Value -
    helicopter_new_P.Gain1_Gain * helicopter_new_B.Elevation_g;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Gain1_idx_3 = ((helicopter_new_P.K_ep * rtb_Derivative + rtb_Clock) -
                     helicopter_new_P.Gain1_Gain * helicopter_new_B.Gain_dg *
                     helicopter_new_P.K_ed) + helicopter_new_P.Vs_ff;

  /* Clock: '<S3>/Clock' incorporates:
   *  Derivative: '<S4>/Derivative'
   */
  rtb_Clock_tmp = helicopter_new_M->Timing.t[0];

  /* Clock: '<S3>/Clock' */
  rtb_Clock = rtb_Clock_tmp;

  /* If: '<S3>/If' incorporates:
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S6>/In1'
   */
  if (rtmIsMajorTimeStep(helicopter_new_M)) {
    rtAction = (int8_T)!(rtb_Clock >= 2.0);
    helicopter_new_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopter_new_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    helicopter_new_B.In1 = helicopter_new_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopter_new_M)) {
      srUpdateBC(helicopter_new_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopter_new_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter_new_DW.TimeStampA >= rtb_Clock_tmp) &&
      (helicopter_new_DW.TimeStampB >= rtb_Clock_tmp)) {
    rtb_Derivative = 0.0;
  } else {
    rtb_Derivative = helicopter_new_DW.TimeStampA;
    lastU = &helicopter_new_DW.LastUAtTimeA;
    if (helicopter_new_DW.TimeStampA < helicopter_new_DW.TimeStampB) {
      if (helicopter_new_DW.TimeStampB < rtb_Clock_tmp) {
        rtb_Derivative = helicopter_new_DW.TimeStampB;
        lastU = &helicopter_new_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_new_DW.TimeStampA >= rtb_Clock_tmp) {
        rtb_Derivative = helicopter_new_DW.TimeStampB;
        lastU = &helicopter_new_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopter_new_B.PitchCounttorad - *lastU) /
      (rtb_Clock_tmp - rtb_Derivative);
  }

  /* Gain: '<S11>/Gain' */
  helicopter_new_B.Gain_l = helicopter_new_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter_new_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Derivative = (rtb_Gain1_idx_3 - rtb_Gain1_idx_2) *
    helicopter_new_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Derivative > helicopter_new_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_new_B.BackmotorSaturation =
      helicopter_new_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter_new_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_new_B.BackmotorSaturation =
      helicopter_new_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_new_B.BackmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_new_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (rtb_Gain1_idx_2 + rtb_Gain1_idx_3) *
    helicopter_new_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Derivative > helicopter_new_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_new_B.FrontmotorSaturation =
      helicopter_new_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter_new_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_new_B.FrontmotorSaturation =
      helicopter_new_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_new_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_new_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_new/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_new_DW.HILWriteAnalog_Buffer[0] =
        helicopter_new_B.FrontmotorSaturation;
      helicopter_new_DW.HILWriteAnalog_Buffer[1] =
        helicopter_new_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_new_DW.HILInitialize_Card,
        helicopter_new_P.HILWriteAnalog_channels, 2,
        &helicopter_new_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_new_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_new_DW.TimeStampA == (rtInf)) {
    helicopter_new_DW.TimeStampA = helicopter_new_M->Timing.t[0];
    lastU = &helicopter_new_DW.LastUAtTimeA;
  } else if (helicopter_new_DW.TimeStampB == (rtInf)) {
    helicopter_new_DW.TimeStampB = helicopter_new_M->Timing.t[0];
    lastU = &helicopter_new_DW.LastUAtTimeB;
  } else if (helicopter_new_DW.TimeStampA < helicopter_new_DW.TimeStampB) {
    helicopter_new_DW.TimeStampA = helicopter_new_M->Timing.t[0];
    lastU = &helicopter_new_DW.LastUAtTimeA;
  } else {
    helicopter_new_DW.TimeStampB = helicopter_new_M->Timing.t[0];
    lastU = &helicopter_new_DW.LastUAtTimeB;
  }

  *lastU = helicopter_new_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_new_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_new_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++helicopter_new_M->Timing.clockTick0)) {
    ++helicopter_new_M->Timing.clockTickH0;
  }

  helicopter_new_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_new_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helicopter_new_M->Timing.clockTick1)) {
      ++helicopter_new_M->Timing.clockTickH1;
    }

    helicopter_new_M->Timing.t[1] = helicopter_new_M->Timing.clockTick1 *
      helicopter_new_M->Timing.stepSize1 + helicopter_new_M->Timing.clockTickH1 *
      helicopter_new_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_new_derivatives(void)
{
  XDot_helicopter_new_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopter_new_T *) helicopter_new_M->derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_new_P.TravelTransferFcn_A *
    helicopter_new_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_new_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_new_P.PitchTransferFcn_A *
    helicopter_new_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_new_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_new_P.ElevationTransferFcn_A *
    helicopter_new_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter_new_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_new_X.Integrator_CSTATE <=
          helicopter_new_P.Integrator_LowerSat);
  usat = (helicopter_new_X.Integrator_CSTATE >=
          helicopter_new_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_new_B.In1 > 0.0)) || (usat &&
       (helicopter_new_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_new_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_new_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_new/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_new_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter_new_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_new_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
      return;
    }

    if ((helicopter_new_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopter_new_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter_new_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopter_new_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter_new_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_new_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(helicopter_new_DW.HILInitialize_Card,
        helicopter_new_P.HILInitialize_AIChannels, 8U,
        &helicopter_new_DW.HILInitialize_AIMinimums[0],
        &helicopter_new_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_new_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopter_new_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter_new_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopter_new_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter_new_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_new_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(helicopter_new_DW.HILInitialize_Card,
        helicopter_new_P.HILInitialize_AOChannels, 8U,
        &helicopter_new_DW.HILInitialize_AOMinimums[0],
        &helicopter_new_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_new_P.HILInitialize_AOStart && !is_switching) ||
        (helicopter_new_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_new_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_new_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopter_new_DW.HILInitialize_Card,
        helicopter_new_P.HILInitialize_AOChannels, 8U,
        &helicopter_new_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_new_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_new_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_new_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_new_DW.HILInitialize_Card,
         helicopter_new_P.HILInitialize_AOChannels, 8U,
         &helicopter_new_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_new_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopter_new_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_new_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter_new_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_new_DW.HILInitialize_Card,
         helicopter_new_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_new_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_new_P.HILInitialize_EIStart && !is_switching) ||
        (helicopter_new_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_new_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopter_new_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopter_new_DW.HILInitialize_Card,
        helicopter_new_P.HILInitialize_EIChannels, 8U,
        &helicopter_new_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_new_P.HILInitialize_POPStart && !is_switching) ||
        (helicopter_new_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_new_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_new_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopter_new_DW.HILInitialize_Card,
        helicopter_new_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopter_new_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopter_new_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &helicopter_new_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopter_new_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            helicopter_new_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helicopter_new_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_new_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            helicopter_new_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] = helicopter_new_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter_new_DW.HILInitialize_Card,
          &helicopter_new_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &helicopter_new_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter_new_DW.HILInitialize_Card,
          &helicopter_new_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter_new_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_new_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_new_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_new_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter_new_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_new_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter_new_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter_new_DW.HILInitialize_Card,
        helicopter_new_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopter_new_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter_new_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter_new_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_new_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter_new_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_new_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_new_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopter_new_DW.HILInitialize_Card,
        helicopter_new_P.HILInitialize_POChannels, 8U,
        &helicopter_new_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_new_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_new_P.HILInitialize_POStart && !is_switching) ||
        (helicopter_new_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_new_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_new_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopter_new_DW.HILInitialize_Card,
        helicopter_new_P.HILInitialize_POChannels, 8U,
        &helicopter_new_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_new_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_new_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_new_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_new_DW.HILInitialize_Card,
         helicopter_new_P.HILInitialize_POChannels, 8U,
         &helicopter_new_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_new/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(helicopter_new_DW.HILInitialize_Card,
      helicopter_new_P.HILReadEncoderTimebase_SamplesI,
      helicopter_new_P.HILReadEncoderTimebase_Channels, 3,
      &helicopter_new_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopter_new_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (helicopter_new_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "simout.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_new_M, "Error creating .mat file simout.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 6 + 1, 0, "simout_data")) {
      rtmSetErrorStatus(helicopter_new_M,
                        "Error writing mat file header to file simout.mat");
      return;
    }

    helicopter_new_DW.ToFile_IWORK.Count = 0;
    helicopter_new_DW.ToFile_IWORK.Decimation = -1;
    helicopter_new_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5235987755983017,
      0.52359877559830037, 0.52359877559829948, 0.523598775598299,
      0.52359877559829859, 0.52359877559829815, 0.52359877559829793,
      0.52359877559829726, 0.523598775598293, 0.523598775598291,
      0.52359877559828416, 0.523598775598208, 0.32964146228217717,
      -0.0821958885269854, -0.3901609857880266, -0.52359877557970558,
      -0.5235987755981889, -0.5235987755982684, -0.52359877559827972,
      -0.52359877559828016, -0.52359877559827772, -0.52359877559824941,
      -0.5235987755977376, -0.52359877559777779, -0.4903364262458787,
      -0.40501787486895807, -0.32447042303848794, -0.25079671744545035,
      -0.18530808032092588, -0.12865835682770121, -0.0809754873314803,
      -0.041984628283726011, -0.011118848096727807, 0.01238476863801552,
      0.029404394129464939, 0.040867891428362779, 0.047701505281312562,
      0.050791466533636642, 0.050956920537016615, 0.048932489369284737,
      0.045358784059094659, 0.040779265133354281, 0.035641982526266824,
      0.030304889236377197, 0.025043601492973133, 0.020060659692465843,
      0.015495520202516322, 0.011434672126564127, 0.0079214212438352138,
      0.0049650133004188746, 0.0025488797115740258, 0.000637880683052261,
      -0.00081550531816443339, -0.0018660394693365001, -0.0025715790522360393,
      -0.0029898539410271319, -0.0031760657239572332, -0.003181202085524526,
      -0.0030509561513124561, -0.0028251429631067637, -0.0025375116369894535,
      -0.0022158607990738766, -0.0018823755377715967, -0.0015541155031902898,
      -0.00124359525386053, -0.00095940899539370683, -0.00070686211726900261,
      -0.00048858117878314289, -0.00030508209152368959, -0.00015528314358903561,
      -3.6955223439272267E-5, 5.2893811463117224E-5, 0.00011770012204570524,
      0.0001610870988512092, 0.00018666583024040673, 0.0001978866992922157,
      0.00019793537121060023, 0.00018966626060334946, 0.00017556672958229935,
      0.00015774567209048129, 0.00013794070910810863, 0.00011753888845267291,
      9.7606499431135418E-5, 7.8924336026520159E-5, 6.2025442730262448E-5,
      4.7233034201066282E-5, 3.46968816988813E-5, 2.4427001165672202E-5,
      1.6323961854247671E-5, 1.0205568179544322E-5, 5.8300631288199511E-6,
      2.9163733322734586E-6, 1.1622739952699135E-6, 2.6168780586921514E-7,
      -7.7416241306416111E-8, -1.1308347669380936E-7, -4.6748791837636361E-8,
      4.4408920985006262E-16, 4.4408920985006262E-16, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0 } ;

    helicopter_new_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_new_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_new_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace2' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1378421413625568, 3.1262155534580569,
      3.1033093000300211, 3.0666274151911757, 3.0144539223915587,
      2.9456562771124717, 2.8595077632860524, 2.7555515879538341,
      2.6335051104749785, 2.4931956060117986, 2.3345185760397018,
      2.1574113214423587, 1.9632257906736166, 1.7564180641641713,
      1.5436868047965151, 1.3320083857247353, 1.1270304718925586,
      0.93285514186196661, 0.7522862634074, 0.58716721231514812,
      0.43867753194554465, 0.3075570988175762, 0.19426296524399195,
      0.099074076111971665, 0.021920755910083304, -0.037969151835006876,
      -0.082000899823435877, -0.11201440982637061, -0.13007759871699173,
      -0.138314377906513, -0.13877705513882396, -0.13335997532665278,
      -0.12374718484738659, -0.11138645062753368, -0.097482802997716167,
      -0.083005938288591943, -0.068706949630962091, -0.055140839568996264,
      -0.042692090366771365, -0.0316012433450885, -0.021990989797143007,
      -0.013890723526992912, -0.0072588655014678774, -0.0020025578214644267,
      0.00200545188913927, 0.0049127442958470918, 0.0068758641565568705,
      0.0080514552083167119, 0.0085896360149869833, 0.0086293288714740721,
      0.0082952440819961514, 0.007696227379224682, 0.006924694733938544,
      0.00605690280453917, 0.0051538318291837991, 0.0042624885131750268,
      0.0034174675361066009, 0.0026426403087032712, 0.0019528675469701971,
      0.0013556574480214382, 0.00085271337308208352, 0.00044133382077010842,
      0.00011564313428600762, -0.00013235601508730397, -0.00031190754404741074,
      -0.00043279618115876978, -0.00050479782391749984, -0.000537269614758782,
      -0.00053886159629076987, -0.00051733128227976943, -0.0004794428770421975,
      -0.000430933941634916, -0.00037653382579492151, -0.00032001998081396878,
      -0.00026430019400088613, -0.00021151072691467205, -0.00016312221024009847,
      -0.0001200468873802947, -8.2742366048971423E-5, -5.1308409745679095E-5,
      -2.5574470012833415E-5, -5.17662785280777E-6, 1.0376611444827829E-5,
      2.164962597927276E-5, 2.9235600451084962E-5, 3.3722270948507717E-5,
      3.5666504638564335E-5, 3.5576627887380936E-5, 3.3901389050972691E-5,
      3.1024468347380992E-5, 2.7263509165435688E-5, 2.2872726583859109E-5,
      1.8048234591017958E-5, 1.2935309367319586E-5, 7.6368592152844646E-6,
      2.2223927058814883E-6, -3.26323564660606E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.015002048905105226,
      -0.046506351619204481, -0.091625013714683415, -0.14672753935682167,
      -0.20869397119799873, -0.27519058111828248, -0.34459405530308379,
      -0.41582470133089205, -0.48818590991482613, -0.56123801785056981,
      -0.63470811988851694, -0.70842901839044881, -0.77674212307541157,
      -0.82723090603542637, -0.85092503746810977, -0.84671367628823269,
      -0.81991165533225641, -0.7767013201309223, -0.722275513828495,
      -0.66047620436167231, -0.59395872148309059, -0.52448173251157015,
      -0.45317653430066679, -0.38075555652661136, -0.30861328080360595,
      -0.23955963097702057, -0.1761269919584231, -0.12005404000982774,
      -0.072252755551473008, -0.032947116756367495, -0.0018507089263696734,
      0.021668319248902213, 0.038451161914603744, 0.049442936879983683,
      0.055614590523104836, 0.057907458836807583, 0.057195954631484372,
      0.05426444024788081, 0.049794996808980016, 0.044363388086291047,
      0.038441014192039706, 0.032401065080370904, 0.026527432102038222,
      0.021025230720418231, 0.01603203884166959, 0.011629169627209689,
      0.0078524794425714559, 0.0047023642072428224, 0.0021527232272929636,
      0.00015877142571971657, -0.0013363391574810928, -0.0023960668113146371,
      -0.003086130581224767, -0.0034711677176255387, -0.0036122839013710216,
      -0.0035653732640586184, -0.003380083908193277, -0.0030993089096260319,
      -0.0027590910469185133, -0.0023888403957744997, -0.0020117762997751416,
      -0.0016455182092285521, -0.0013027627459667064, -0.00099199659749682782,
      -0.00071820611585385091, -0.000483554548483874, -0.00028800657104298909,
      -0.000129887163378371, -6.3679261380562542E-6, 8.6121256045129175E-5,
      0.00015155362095657898, 0.00019403574163561209, 0.00021760046336387061,
      0.0002260553799291664, 0.00022287914725041837, 0.00021115786834563697,
      0.00019355406669875757, 0.00017230129143947759, 0.00014921808532597408,
      0.00012573582521243327, 0.00010293575893106127, 8.1591368637989111E-5,
      6.2212957191356348E-5, 4.5092058138441924E-5, 3.03438978840661E-5,
      1.7946681987774146E-5, 7.7769347609733289E-6, -3.5950700520433051E-7,
      -6.7009553459014963E-6, -1.1507682814893179E-5, -1.5043836728052757E-5,
      -1.7563130326048714E-5, -1.9297967971109403E-5, -2.045170089477916E-5,
      -2.119380060815688E-5, -2.1657866037601851E-5, -2.194251340997607E-5,
      -2.2115245727048424E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.10602875205955331, 0.22266037931991534, 0.31888147181690107,
      0.38944360631368724, 0.43795507377901255, 0.46997264230582536,
      0.49051724877714309, 0.50343100141602182, 0.511421385861219,
      0.51630439857764288, 0.519258621270981, 0.52103115488686635,
      0.48281093355328164, 0.35683543512888805, 0.16746107161976731,
      -0.02976429239716416, -0.18942644786108598, -0.30539414625789563,
      -0.38466081246430089, -0.43677391652708875, -0.47012016446800831,
      -0.49103682322397507, -0.50395790785330419, -0.51184381167157411,
      -0.50987405202764557, -0.48804482386097126, -0.44831766617327146,
      -0.39630220885496759, -0.3378412219883794, -0.2777972432633764,
      -0.21977753412297896, -0.1662235086774308, -0.11861472221159619,
      -0.077685667409108539, -0.043618890870558147, -0.016205117551968073,
      0.0050286400008457965, 0.020718824033029937, 0.031588319244965857,
      0.038388535996625506, 0.0418570767969384, 0.04268805352693783,
      0.041512594609785292, 0.038887457950009918, 0.035289973177562772,
      0.03111779805351389, 0.026692203812957227, 0.022263811389359733,
      0.018019888676385931, 0.014092489792639773, 0.010566870588620048,
      0.0074897503235580309, 0.0048771071758565432, 0.0027212954279851598,
      0.00099735529199396211, -0.00033154646885180661, -0.0013095544006666016,
      -0.0019844104562304343, -0.00240452991628326, -0.0026167901949060157,
      -0.0026649450212304915, -0.0025885723012089024, -0.0024224647088118,
      -0.0021963764480045223, -0.0019350465573051423, -0.0016584276590650981,
      -0.0013820584201197361, -0.0011175275839789833, -0.00087298679383729372,
      -0.00065367821565331941, -0.00046245096482067094, -0.00030024740424849927,
      -0.00016654645310787419, -5.9756121114973304E-5, 2.2448399462304813E-5,
      8.2841522652254973E-5, 0.00012441694675069392, 0.00015020649859542878,
      0.00016314328480249163, 0.00016596364605570013, 0.00016114216060481024,
      0.00015085399864200877, 0.00013695921105694175, 0.00012100397561864984,
      0.00010423436399009667, 8.7618787189880365E-5, 7.18758893466509E-5,
      5.7505262894275155E-5, 4.4818934930357379E-5, 3.39721139533955E-5,
      2.4992185316041748E-5, 1.7805404976534156E-5, 1.2261169900051883E-5,
      8.1541436655063748E-6, 5.244877348431487E-6, 3.2798372204823067E-6,
      2.0117789143458964E-6, 1.2208060465868087E-6, 7.34323529760772E-7, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823389237,
      0.46652650905849707, 0.38488436997508263, 0.28224853798250288,
      0.19404586986240946, 0.12807027410765212, 0.082178425884731468,
      0.051655010555636163, 0.03196153778073408, 0.019532050865697644,
      0.011816890773625962, 0.00709013446357448, -0.15288088533439909,
      -0.50390199369776412, -0.757497454034849, -0.78890145607776474,
      -0.63864862185606686, -0.46387079358246924, -0.31706666482668588,
      -0.20845241624953495, -0.13338499176291396, -0.083666635023795649,
      -0.051684338517554974, -0.031543615273683309, 0.0078790385744086852,
      0.087316912666759, 0.15890863074972236, 0.20806182927356662,
      0.23384394746924334, 0.24017591489042639, 0.23207883656135142,
      0.214216101789716, 0.1904351458603484, 0.16371621921156662,
      0.13626710615806845, 0.10965509327322948, 0.084935030210045628,
      0.0627607361300867, 0.043477980847401766, 0.027200867007133367,
      0.013874163200275909, 0.00332390692071733, -0.0047018356668710737,
      -0.01050054664175488, -0.014389939088509949, -0.016688700497095116,
      -0.017702376959598313, -0.017713569696672885, -0.016975690850709709,
      -0.01570959553665938, -0.014102476815065509, -0.012308481060160916,
      -0.010450572590649656, -0.0086232469913391924, -0.0068957605438581633,
      -0.0053156070432642914, -0.0039120317272243656, -0.0026994242222257558,
      -0.0016804778402421949, -0.00084904111459239691, -0.00019261930524231758,
      0.00030549088011635019, 0.0006644303695859734, 0.00090435304334175043,
      0.0010453195628499232, 0.0011064755928880757, 0.0011054769557128003,
      0.0010581233445982427, 0.00097816316062283989, 0.00087723431277543561,
      0.00076490900330385039, 0.00064881424230061929, 0.00053480380459006074,
      0.00042716132797031292, 0.00032881808230816759, 0.00024157249276206345,
      0.00016630169639215547, 0.00010315820737979621, 5.1747144832111356E-5,
      1.1281445014771606E-5, -1.9285941810665693E-5, -4.1152647839758816E-5,
      -5.55791503338611E-5, -6.3820941752593439E-5, -6.7078446520444328E-5,
      -6.64623072002301E-5, -6.2971591375684714E-5, -5.7482505817747851E-5,
      -5.0745311850277328E-5, -4.3387283902906714E-5, -3.5919714549701356E-5,
      -2.874712135827994E-5, -2.2176940305600916E-5, -1.6428104938767029E-5,
      -1.1637065268411251E-5, -7.860160512035935E-6, -5.0722332248565304E-6,
      -3.1638914707382918E-6, -1.9459300673304714E-6, -1.1834459044683623E-6,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_new_DW.FromWorkspace2_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_new_DW.FromWorkspace2_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_new_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* Start for If: '<S3>/If' */
  helicopter_new_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_new_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_new_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_new_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_new_X.Integrator_CSTATE = helicopter_new_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_new_DW.TimeStampA = (rtInf);
  helicopter_new_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_new_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_new/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_new_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_new_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_new_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopter_new_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_new_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_new_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopter_new_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopter_new_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_new_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_new_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter_new_DW.HILInitialize_Card
                         , helicopter_new_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopter_new_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_new_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_new_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter_new_DW.HILInitialize_Card,
            helicopter_new_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &helicopter_new_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter_new_DW.HILInitialize_Card,
            helicopter_new_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopter_new_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_new_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_new_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_new_DW.HILInitialize_Card);
    hil_close(helicopter_new_DW.HILInitialize_Card);
    helicopter_new_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter_new_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "simout.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_new_M, "Error closing MAT-file simout.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_new_M,
                          "Error reopening MAT-file simout.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6 + 1, helicopter_new_DW.ToFile_IWORK.Count,
           "simout_data")) {
        rtmSetErrorStatus(helicopter_new_M,
                          "Error writing header for simout_data to MAT-file simout.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_new_M, "Error closing MAT-file simout.mat");
        return;
      }

      helicopter_new_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helicopter_new_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_new_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helicopter_new_initialize();
}

void MdlTerminate(void)
{
  helicopter_new_terminate();
}

/* Registration function */
RT_MODEL_helicopter_new_T *helicopter_new(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_new_P.Integrator_UpperSat = rtInf;
  helicopter_new_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_new_M, 0,
                sizeof(RT_MODEL_helicopter_new_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_new_M->solverInfo,
                          &helicopter_new_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_new_M->solverInfo, &rtmGetTPtr(helicopter_new_M));
    rtsiSetStepSizePtr(&helicopter_new_M->solverInfo,
                       &helicopter_new_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_new_M->solverInfo, &helicopter_new_M->derivs);
    rtsiSetContStatesPtr(&helicopter_new_M->solverInfo, (real_T **)
                         &helicopter_new_M->contStates);
    rtsiSetNumContStatesPtr(&helicopter_new_M->solverInfo,
      &helicopter_new_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_new_M->solverInfo,
      &helicopter_new_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_new_M->solverInfo,
      &helicopter_new_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_new_M->solverInfo,
      &helicopter_new_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_new_M->solverInfo, (&rtmGetErrorStatus
      (helicopter_new_M)));
    rtsiSetRTModelPtr(&helicopter_new_M->solverInfo, helicopter_new_M);
  }

  rtsiSetSimTimeStep(&helicopter_new_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_new_M->intgData.f[0] = helicopter_new_M->odeF[0];
  helicopter_new_M->contStates = ((real_T *) &helicopter_new_X);
  rtsiSetSolverData(&helicopter_new_M->solverInfo, (void *)
                    &helicopter_new_M->intgData);
  rtsiSetSolverName(&helicopter_new_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_new_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_new_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_new_M->Timing.sampleTimes =
      (&helicopter_new_M->Timing.sampleTimesArray[0]);
    helicopter_new_M->Timing.offsetTimes =
      (&helicopter_new_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_new_M->Timing.sampleTimes[0] = (0.0);
    helicopter_new_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_new_M->Timing.offsetTimes[0] = (0.0);
    helicopter_new_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_new_M, &helicopter_new_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_new_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_new_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_new_M, -1);
  helicopter_new_M->Timing.stepSize0 = 0.002;
  helicopter_new_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_new_M->Sizes.checksums[0] = (1328503199U);
  helicopter_new_M->Sizes.checksums[1] = (196191965U);
  helicopter_new_M->Sizes.checksums[2] = (3089820543U);
  helicopter_new_M->Sizes.checksums[3] = (1979883486U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopter_new_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &helicopter_new_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopter_new_M->extModeInfo,
      &helicopter_new_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_new_M->extModeInfo,
                        helicopter_new_M->Sizes.checksums);
    rteiSetTPtr(helicopter_new_M->extModeInfo, rtmGetTPtr(helicopter_new_M));
  }

  helicopter_new_M->solverInfoPtr = (&helicopter_new_M->solverInfo);
  helicopter_new_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_new_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_new_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_new_M->blockIO = ((void *) &helicopter_new_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopter_new_B.TmpSignalConversionAtToFileInpo[i] = 0.0;
    }

    helicopter_new_B.TravelCounttorad = 0.0;
    helicopter_new_B.Gain = 0.0;
    helicopter_new_B.Elevation = 0.0;
    helicopter_new_B.Gain_d = 0.0;
    helicopter_new_B.PitchCounttorad = 0.0;
    helicopter_new_B.Gain_i = 0.0;
    helicopter_new_B.Gain_b = 0.0;
    helicopter_new_B.ElevationCounttorad = 0.0;
    helicopter_new_B.Gain_e = 0.0;
    helicopter_new_B.Elevation_g = 0.0;
    helicopter_new_B.Gain_dg = 0.0;
    helicopter_new_B.Gain_l = 0.0;
    helicopter_new_B.BackmotorSaturation = 0.0;
    helicopter_new_B.FrontmotorSaturation = 0.0;
    helicopter_new_B.In1 = 0.0;
  }

  /* parameters */
  helicopter_new_M->defaultParam = ((real_T *)&helicopter_new_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_new_X;
    helicopter_new_M->contStates = (x);
    (void) memset((void *)&helicopter_new_X, 0,
                  sizeof(X_helicopter_new_T));
  }

  /* states (dwork) */
  helicopter_new_M->dwork = ((void *) &helicopter_new_DW);
  (void) memset((void *)&helicopter_new_DW, 0,
                sizeof(DW_helicopter_new_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_new_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_new_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_new_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_new_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_new_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_new_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_new_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_new_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_new_DW.TimeStampA = 0.0;
  helicopter_new_DW.LastUAtTimeA = 0.0;
  helicopter_new_DW.TimeStampB = 0.0;
  helicopter_new_DW.LastUAtTimeB = 0.0;
  helicopter_new_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_new_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_new_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_new_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_new_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopter_new_M->Sizes.numY = (0);  /* Number of model outputs */
  helicopter_new_M->Sizes.numU = (0);  /* Number of model inputs */
  helicopter_new_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_new_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_new_M->Sizes.numBlocks = (66);/* Number of blocks */
  helicopter_new_M->Sizes.numBlockIO = (16);/* Number of block outputs */
  helicopter_new_M->Sizes.numBlockPrms = (149);/* Sum of parameter "widths" */
  return helicopter_new_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
