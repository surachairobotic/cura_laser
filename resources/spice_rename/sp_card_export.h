#ifndef SPIC_EXPORT_H
#define SPIC_EXPORT_H

extern "C"
{
	int   __stdcall Get_Last_Error_Code(void);
	char* __stdcall Get_Error_Message(int iErrorCode);
	char* __stdcall Get_Last_Error_Message(void);


	bool __stdcall Init_Scan_Card(void);
	int __stdcall Init_Scan_Card_Ex(unsigned short N);   

	int __stdcall Init_Scan_Card_Raw(unsigned short N, unsigned short nSerialPort, unsigned long nParBase, unsigned long nParFifo, unsigned long nTimeout);   

	bool __stdcall Remove_Scan_Card(void);
	int __stdcall Remove_Scan_Card_Ex(unsigned short N);   

	bool __stdcall Is_Allowed_To_Use(unsigned short N, const char * szAppName, bool IfNoneThanAny);   

	bool __stdcall Start_Manual_Operation(void);
	bool __stdcall Stop_Manual_Operation(void);
	bool __stdcall Start_Laser_Manually(void);
	bool __stdcall Stop_Laser_Manually(void);
	bool __stdcall  Set_Auto_Delay(unsigned short usStepPeriod);
	bool __stdcall  Set_Jump_Delay(unsigned short usJumpDelay);
	bool __stdcall  Set_Mark_Delay(unsigned short usMarkDelay);
	bool __stdcall  Set_Poly_Delay(unsigned short usPolyDelay);
	bool __stdcall  Set_Laser_Off_Delay(unsigned short usLaserOffDelay);
	bool __stdcall  Set_Laser_On_Delay(unsigned short usLaserOnDelay);
	bool __stdcall  Set_T1(unsigned short usT1);
	bool __stdcall  Set_T2(unsigned short usT2);
	bool __stdcall  Set_T3(unsigned short usT3);
	bool __stdcall  Set_Manual_Delay(unsigned short usManualDelay);

	bool __stdcall  Set_Dig_Gain(unsigned short usDigGain); 
	bool __stdcall	Set_Dig_Gain_Ex(double dDigGain);
	bool __stdcall	Set_Dig_Gain_Ex_2(double dDigGain);
	bool __stdcall  Set_Mark_Shift(unsigned short usMarkShift); 
	bool __stdcall  Set_Rot_Grad(double dGrad); 
	bool __stdcall  Set_Rot_Grad_2(double dGrad); 

	bool __stdcall  Set_Gain_X(double dGainX);
	bool __stdcall  Set_Gain_Y(double dGainY);
	bool __stdcall  Set_Offset_X(signed short ssOffsetX);
	bool __stdcall  Set_Offset_Y(signed short ssOffsetY);
	
	bool __stdcall  Set_Gain_X_N(double dGainX, int NHead);
	bool __stdcall  Set_Gain_Y_N(double dGain, int NHead);
	bool __stdcall  Set_Offset_X_N(signed short ssOffsetX, int NHead);
	bool __stdcall  Set_Offset_Y_N(signed short ssOffsetY, int NHead);

	bool __stdcall  Set_Offset_Z(int ssOffsetZ);

	bool __stdcall  Set_Offset_Z_N(int ssOffsetZ, int NHead);


	bool __stdcall  Set_Jump_Speed(double dJumpSpeed);
	bool __stdcall  Set_Mark_Speed(double dMarkSpeed);
	bool __stdcall  Set_Mark_Parameters_List(unsigned short usStepPeriod, unsigned short usStepSize);
	bool __stdcall  Set_Jump_Parameters_List(unsigned short usStepPeriod, unsigned short usJumpSize);
	bool __stdcall  Get_XY_Manual(signed short *pXManual, signed short *pYManual);
	bool __stdcall  Get_DXDY_Manual(signed short *pDXManual, signed short *pDYManual);
	bool __stdcall  Set_DXDY_Manual(signed short ssDXManual, signed short ssDYManual);
	bool __stdcall  Start_Manual_Move(void);
	bool __stdcall  Stop_Manual_Move(void);
	bool __stdcall  Get_Manual_Move(void);
	bool __stdcall  Restart_List_1(void);
	bool __stdcall  Restart_List_2(void);
	double __stdcall Get_Jump_Speed(void);
	double __stdcall Get_Mark_Speed(void);
	const char* __stdcall Corr_File_Name(int nCard);
	bool  __stdcall Read_Port(unsigned short usAddressOffset, unsigned short* pValue);
	bool  __stdcall Write_Port(unsigned short usAddressOffset, unsigned short usValue);
	bool  __stdcall Test_Read_Port(unsigned short usAddressOffset, unsigned short* pValue); 
	bool  __stdcall Test_Write_Port(unsigned short usAddressOffset, unsigned short usValue); 

	bool  __stdcall Load_Corr_File_From_Target_Disk( const char *lpszFileName );
    
    bool __stdcall Enable_Custlist( bool bEnable );
   
    bool __stdcall Set_Custlist_Parameters( double dLeadInPower, double dLeadOutPower
        , double dPowerControlSlope, unsigned short nMicroSegmentLenght );
    
    bool __stdcall Get_Custlist_Parameters( double* pdLeadInPower, double* pdLeadOutPower
        , double* pdPowerControlSlope, unsigned short* pnMicroSegmentLenght );


	bool __stdcall Set_3DMode(void);
	bool __stdcall Reset_3DMode(void);
	bool __stdcall Set_3D_Parameters( int iXYReqField, double dXYMaxGalvoAngles, double dYrad, double dXtoY,
				double dObjtoX, double dFocalLength, double dMidFocPosition, double dMaxLensTravel, int inHead);
	bool __stdcall Get_3D_Parameters( int *piXYReqField, double *pdXYMaxGalvoAngles, double *pdYrad, double *pdXtoY,
				double *pdObjtoX, double *pdFocalLength, double *pdMidFocPosition, double *pdMaxLensTravel, int inHead);
	bool __stdcall Set_InvertedZ(int inHead, bool bInvert);


	unsigned short __stdcall Get_CPU_Type();

	
	bool __stdcall Set_TAxisFlag(void);
	bool __stdcall Reset_TAxisFlag(void);
	bool __stdcall Set_FocusShifterParameters(	double dXzGainFactor, double dYzGainFactor,
												double dAFactor, double dBFactor, double dCFactor,
												float fZmax, float fZmin, int nLTJumpDelay);
	bool __stdcall Get_FocusShifterParameters(	double *pdXzGainFactor, double *pdYzGainFactor,
												double *pdAFactor, double *pdBFactor, double *pdCFactor,
												float *pfZmax, float *pfZmin, int *pnLTJumpDelay);
	bool __stdcall Set_ZPosition( float fZPosition );
	bool __stdcall Load_FocusShifterParameters(const char* lpstrFileName);


	bool __stdcall Aut_Change(void);
	bool __stdcall Disable_Laser(void);
	bool __stdcall Enable_Laser(void);
	bool __stdcall Execute_List_1(void);
	bool __stdcall Execute_List_2(void);
	int __stdcall Get_Counts(void);
	unsigned short __stdcall Get_DLL_Version(void);
	unsigned short __stdcall Get_SPC1_Mode(void);
	unsigned short __stdcall Get_SPC1_Version(void);
	unsigned short __stdcall Get_Version(void);
	bool __stdcall Get_XY_Pos(signed short *pXPos, signed short *pYPos);
	bool __stdcall Goto_XY(signed short ssXPos, signed short ssYPos);
	bool __stdcall Goto_XY_Ex(signed short ssXPos, signed short ssYPos);
	bool __stdcall Load_Cor(const char* lpstrFileName);
	bool __stdcall Load_Corr_N(const char* lpstrFileName, int N);  
	bool __stdcall Load_Corr_N_Ex(const char* lpstrFileName, int N);
	bool __stdcall Quit_Loop(void);
	unsigned short __stdcall Read_Status(void);
	bool __stdcall Set_Control_Mode(unsigned short usControl_Mode);

	bool __stdcall Set_Gain(double dGainX, double dGainY, signed short ssOffsetX, signed short ssOffsetY);
	bool __stdcall	Set_Gain_N(double dGainX, double dGainY, signed short ssOffsetX, signed short ssOffsetY, int NHead);

	bool __stdcall Set_Max_Counts(int iCounts);
	bool __stdcall Set_Mode(unsigned short usMode);
	bool __stdcall Set_Laser_Mode(unsigned short usLaserMode);
	bool __stdcall Set_Speed(double dJumpSpeed, double dMarkSpeed);
	bool __stdcall Set_Start_List_1(void);
	bool __stdcall Set_Start_List_2(void);
	bool __stdcall Set_YAG_Parameter(unsigned short usPrescaler);
	bool __stdcall Start_Loop(void);
	bool __stdcall Stop_Execution(void);
	bool __stdcall Stop_Execution_NoClear(void); 
	bool __stdcall Write_DA(unsigned short usValue);

	
	bool __stdcall Write_DA2(unsigned short usValue);

	
	bool __stdcall Write_DA_16Bit(unsigned short usValue);
	bool __stdcall Write_DA2_16Bit(unsigned short usValue);

	unsigned short __stdcall Get_Active_Card();
	bool __stdcall Set_Active_Card(unsigned short iCard);
	bool __stdcall Make_Boot_Program(const char *lpszFileName);
	bool __stdcall Output_To_File(const char *lpszFileName);
	bool __stdcall Loop_To_Start_List(signed short iTargetList);
	bool __stdcall Jump_To_Start_List(signed short iTargetList); 
	bool __stdcall Copy_File_To_Target_Disk(const char *lpszFileName);
	bool __stdcall Copy_File_From_Target_Disk(const char *lpszFileName);
	bool __stdcall Delete_File_On_Target_Disk(const char *lpszFileName);
	unsigned short __stdcall Get_System_Status();
	bool __stdcall Set_Auto_Jump_Delay_List(unsigned short usDelay, unsigned short usLen);
	unsigned int __stdcall Get_Ident_Ex( void );	
	int __stdcall Get_Mode_Mask(unsigned short* pMode); 
	bool __stdcall  Set_Head_Rot(double dRot, int NHead);

	bool  __stdcall  Set_Lag_Time( unsigned short usLagTime, int NHead );
	
	bool __stdcall Clear_Scan_Complete();


	bool __stdcall Field_Jump(signed short ssXVal, signed short ssYVal);
	bool __stdcall Home_Jump(signed short ssXVal, signed short ssYVal);
	bool __stdcall Jump_Abs(signed short ssXVal, signed short ssYVal);
	bool __stdcall Reset_Jump_List(signed short ssXVal, signed short ssYVal); 
	bool __stdcall Reset_Jump_List_Rel(signed short ssXVal, signed short ssYVal); 

	bool __stdcall Set_Head_Mask(unsigned short usHead_N); 
	unsigned short __stdcall Get_Head_Mask();			   

	bool __stdcall Set_JobControl_List(unsigned short usJobControlWORD); 
	bool __stdcall Skip_Var_List(short ssEntries, unsigned short usMASK); 
	bool __stdcall Skip_Var_List_Back(short ssEntries, unsigned short usMASK); 
	bool __stdcall Skip_Counter_List(short ssEntries, unsigned short usCounter_List); 
	bool __stdcall Set_Counter_List(unsigned short usCounter_List); 
	bool __stdcall Read_Port_To_Var_List(unsigned short usPORT); 
	bool __stdcall JobControl_To_Var_List(); 

	bool __stdcall Laser_On(unsigned short usDelay);
	bool __stdcall Laser_Off(unsigned short usDelay);
	bool __stdcall Long_Delay(unsigned short usDelay);
	bool __stdcall Jump_Rel(signed short ssXVal, signed short ssYVal); 
	bool __stdcall Mark_Rel(signed short ssXVal, signed short ssYVal); 
	bool __stdcall PolA_Rel(signed short ssXVal, signed short ssYVal); 
	bool __stdcall PolB_Rel(signed short ssXVal, signed short ssYVal); 
	bool __stdcall PolC_Rel(signed short ssXVal, signed short ssYVal); 
	bool __stdcall Mark_Abs(signed short ssXVal, signed short ssYVal);
	bool __stdcall PolA_Abs(signed short ssXVal, signed short ssYVal);
	bool __stdcall PolB_Abs(signed short ssXVal, signed short ssYVal);
	bool __stdcall PolC_Abs(signed short ssXVal, signed short ssYVal);
	bool __stdcall Set_Delays(unsigned short usStepPeriod, unsigned short usJumpDelay, unsigned short usMarkDelay, unsigned short usPolyDelay,
	unsigned short usLaserOffDelay, unsigned short usLaserOnDelay, unsigned
	short usT1, unsigned short usT2, unsigned short usT3);
	
	bool __stdcall Set_Delays_1_2(unsigned short usStepPeriod, unsigned short usJumpDelay);
	bool __stdcall Set_Delays_3_4(unsigned short usMarkDelay, unsigned short usPolyDelay);
	bool __stdcall Set_Delays_5_6(unsigned short usLaserOffDelay, unsigned short usLaserOnDelay);
	bool __stdcall Set_Delays_7_8(unsigned short usT1, unsigned short usT2);
	bool __stdcall Set_Delays_9_10(unsigned short usT3, unsigned short usT4);
	
	bool __stdcall Set_End_Of_List(void);

	bool __stdcall Write_DA_List(unsigned short usValue);

	
	bool __stdcall Write_DA2_List(unsigned short usValue);

	
	bool __stdcall Write_DA_16Bit_List(unsigned short usValue);
	bool __stdcall Write_DA2_16Bit_List(unsigned short usValue);

	bool __stdcall Write_Port_List(unsigned short usAddressOffset, unsigned short usValue);

	bool __stdcall Set_Wobble_List(unsigned short usWidth, unsigned short usPeriod);  

	bool __stdcall Wait_For_External_Start();
	bool __stdcall Wait_For_Counter_Value(unsigned short ssValue); 
	bool __stdcall Wait_For_Counter_Value_Ex(int nValue);
	bool __stdcall Mark_Immediately();


	bool __stdcall Put_Bitmapline_List( short LineBegX, short LineBegY, short LineEndX, short LineEndY, unsigned short* pArrDelays, unsigned short arraylen );
	bool __stdcall Put_Bitmapline_List_Ex( short LineBegX, short LineBegY, short LineEndX, short LineEndY, void* pValues, unsigned short numValues, unsigned short BitmapAlgorithmSelect );
	bool __stdcall Put_Bitmapline_List_Float( double LineBegX, double LineBegY, double LineEndX, double LineEndY, void* pValues, unsigned short numValues, unsigned short BitmapAlgorithmSelect );
	bool __stdcall Set_BmpWhitePixelThreshold(const short nThreshold);
	bool __stdcall Set_BmpMaxPixelValue(const short nMaxPixelValue);
	bool __stdcall Set_BmpLineShiftCorrection(const double dblBmpLineShiftCorrection);
	bool __stdcall BmpLine_LeftToRight(const bool bLeftToRight);
	bool __stdcall Set_BmpNumberOfLines(const unsigned long nNumLines);

	
	bool __stdcall Jump_Abs_3D(signed short ssXVal, signed short ssYVal, signed short ssZVal, signed short ssNVal);
	bool __stdcall Mark_Abs_3D(signed short ssXVal, signed short ssYVal, signed short ssZVal, signed short ssNVal);
	bool __stdcall PolA_Abs_3D(signed short ssXVal, signed short ssYVal, signed short ssZVal, signed short ssNVal);
	bool __stdcall PolB_Abs_3D(signed short ssXVal, signed short ssYVal, signed short ssZVal, signed short ssNVal);
	bool __stdcall PolC_Abs_3D(signed short ssXVal, signed short ssYVal, signed short ssZVal, signed short ssNVal);
	
	
	bool __stdcall Set_Gain_List(float fGainX, float fGainY);
	
	
	bool __stdcall Set_ZPosition_List( float ZPosition ); 

	
	bool __stdcall Set_Laser_Mode_List(unsigned short usLaserMode);

	
	bool __stdcall SetAutoSegmentation(bool bEnable, unsigned short usBreakAngleDegrees);

	
	bool __stdcall SetAutoCalFineAdjustRange(unsigned nFineAdjustRange);
	bool __stdcall SetAutoCalNumMeasurements(unsigned nCycles, unsigned nCyclesReference);
	bool __stdcall GetAutoCalNumMeasurements(unsigned& nCycles, unsigned& nCyclesReference);
	bool __stdcall RunAutoCalibration();
	bool __stdcall RunAutoCalibrationOnHead(unsigned short nHeadNumber);
	bool __stdcall RunReferenceAutoCalibration();
	bool __stdcall RunReferenceAutoCalibrationOnHead(unsigned short nHeadNumber);
	bool __stdcall GetAutoCalMeasurement(int anResult[4]);
	bool __stdcall GetAutoCalMeasurementOfHead(unsigned short nHeadNumber, int anResult[4]);
	bool __stdcall GetAutoCalibratedGain(double& dblGainX, double& dblGainY, bool bAveraged, int nCardIndex);
	bool __stdcall GetAutoCalibratedGainOfHead(unsigned short nHeadNumber, double& dblGainX, double& dblGainY, bool bAveraged, int nCardIndex);
	bool __stdcall GetAutoCalibratedOffset(int& nOffsetX, int& nOffsetY, bool bAveraged, int nCardIndex);
	bool __stdcall GetAutoCalibratedOffsetOfHead(unsigned short nHeadNumber, int& nOffsetX, int& nOffsetY, bool bAveraged, int nCardIndex);
	bool __stdcall SetAutoCalNumSamplesForAvg(unsigned nNumSamples, short nHeadNumber, int nCardIndex);
	bool __stdcall GetAutoCalNumSamplesForAvg(unsigned& rnNumSamples, unsigned short nHeadNumber, int nCardIndex);
	bool __stdcall SetAutoCorrection(bool bGain, bool bOffset);
	bool __stdcall GetAutoCorrection(bool& bGain, bool& bOffset);
	bool __stdcall SetAutoCalHeadRampDelay(short nHeadNumber, unsigned short nMicroSeconds);
	bool __stdcall GetAutoCalHeadRampDelay(unsigned short nHeadNumber, unsigned short& nMicroSeconds);
	bool __stdcall ForceAutoCorrection(bool bForce);
	bool __stdcall GetAutoCalibrationError(char* szErrorInfo);
	int  __stdcall GetAutoCalibrationErrorID();
	bool __stdcall GetAutoCalibrationBusy(bool& bBusy);
	bool __stdcall ResetCalibrationOfHead(unsigned short nHeadNumber);
	bool __stdcall ResetCalibration();
	bool __stdcall TerminateCalibration();
	bool __stdcall SetNullCorrection(int nHeadNumber);
	bool __stdcall RestoreLastCorrection(int nHeadNumber);
	bool __stdcall SetAutoCalJumpSpeed(unsigned short nHeadNumber, unsigned short nStepperiod, unsigned short nStepSize);
	bool __stdcall GetAutoCalValidReference(unsigned short nHeadNumber);
	bool __stdcall SetAutoCalStablePositions(unsigned short nHeadNumber, unsigned short nPositionX, unsigned short nPositionY);
	bool __stdcall GetAutoCalStablePositions(unsigned short nHeadNumber, unsigned short& nPositionX, unsigned short& nPositionY);
	
	
	bool __stdcall Arc_Abs( short centreX, short centreY, double angle, unsigned short numSegments );
	bool __stdcall Arc_Rel( short centreX, short centreY, double angle, unsigned short numSegments );

	
	bool __stdcall Set_LM_Timer_Unit( unsigned short unitID );

	
	bool __stdcall Set_Edge_Level(unsigned short usEdgeLevel);
	bool __stdcall Load_Var_Poly_Delay_Table(const char* lpstrFileName);

	
	bool __stdcall XY2100Enh_Transceive( 
		unsigned short headNumber, 
		unsigned short channelSelect, 
		unsigned short cmdPktX, unsigned short cmdPktY, unsigned short cmdPktZ,
		unsigned int * pDataBufX, unsigned int * pDataBufY, unsigned int * pDataBufZ
		);
	
	
	bool __stdcall XY2100Enh_Transmit( 
		unsigned short headNumber, 
		unsigned short channelSelect, 
		unsigned short cmdPktX, unsigned short cmdPktY, unsigned short cmdPktZ
		);
	
	
	bool __stdcall XY2100Enh_Transmit_List( 
		unsigned short headNumber, 
		unsigned short channelSelect, 
		unsigned short cmdPktX, unsigned short cmdPktY, unsigned short cmdPktZ
		);
	
	
	bool __stdcall XY2100Enh_Exit_Enhanced_Mode(
		unsigned short headNumber
		);
	
}

#endif
