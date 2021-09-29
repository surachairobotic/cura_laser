// Console_SP-ICE_Sanple.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>

#include "stdafx.h"
#include "conio.h"
#include "SPIC_Export.h"

using namespace std;

class Laser {
public:
	Laser();
	bool OnInitCard();
	bool OnSetMode();
	bool OnSetCorrection(char* fname);
	bool OnSetEndOfList();
	bool OnSetStartList();
	bool OnExecuteList();
	bool OnSetDelays();
	bool OnSetSpeed();
	void OnKvadrat();
	bool OnStopExecution();
	unsigned int OnGetSn();
	unsigned int OnGetVersion();
	unsigned int OnGetDLLVersion();
	void LaserOn(unsigned short ms);
private:
	bool bInitCard, bSetMode, bLoadCorr, bStartList, bEndList, bExeList, bSetDelay, bSetSpeed;
};

int main()
{
	cout << "START." << endl;

	Init_Scan_Card_Ex(1);
	unsigned short usMode = 0x0410;
	Set_Mode(usMode);
	Set_Gain(1, 1, 0, 0);
	Set_Start_List_1();
	Set_Speed(500, 150);
	Laser_On(0);
	for (int i = 0; i < 100; i++)
		Long_Delay(100);
	PolA_Abs(0, 10000);
	for (int i = 0; i < 100; i++)
		Long_Delay(100);
	PolB_Abs(0 + 10000, 0 + 10000);
	for (int i = 0; i < 100; i++)
		Long_Delay(100);
	PolB_Abs(0 + 10000, 0);
	for (int i = 0; i < 100; i++)
		Long_Delay(100);
	PolC_Abs(0, 0);
	for (int i = 0; i < 100; i++)
		Long_Delay(100);
	Laser_Off(0);
	for (int i = 0; i < 100; i++)
		Long_Delay(100);
	Enable_Laser();
	Laser_On(0);
	for (int i = 0; i < 100; i++)
		Long_Delay(100);
	Laser_Off(0);
	Disable_Laser();
	Set_End_Of_List();
	Execute_List_1();

	cout << "Press any key to STOP." << endl;
	_getch();
	if (Stop_Execution()) {
		cout << "OnStopExecution is FALSE..." << endl;
		_getch();
	}
	return 0;

}

int xxx(){
	vector<float> x, y;
	float max[2] = { 0.0,0.0 }, min[2] = { 999.99,999.99 };
	string line;
	
	//ifstream myfile("C:\\cura_laser\\resources\\UMS5_cube_10_20_30_filter_l100.gcode");
	ifstream myfile("C:/cura_laser/resources/moai_cube_l0_filter.gcode");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			int indx = line.find(',');
			float sX = std::stof(line.substr(1, indx-1));
			float sY = std::stof(line.substr(indx+2, line.size()-(indx+2)-1));
			//cout << sX  << " : " << sY << '\n';
			x.push_back(sX);
			y.push_back(sY);
			if (max[0] < sX)
				max[0] = sX;
			if (max[1] < sY)
				max[1] = sY;
			if (min[0] > sX)
				min[0] = sX;
			if (min[1] > sY)
				min[1] = sY;
		}
		myfile.close();
	}
	char *corrFile = "E:\\Laser software\\Raylase\\TSL-355-90-163-D10-B_MS-10_LR25,0.gcd";
	cout << "Press for start." << endl;
	cout << "MIN : " << min[0] << ", " << min[1] << endl;
	cout << "MAX : " << max[0] << ", " << max[1] << endl;
	float mmin = (min[0] < min[1]) ? min[0] : min[1];
	float mmax = (max[0] > max[1]) ? max[0] : max[1];
	double m = (-30000 - 30000) / (mmin - mmax);
	cout << "mmin,mmax:" << mmin << "," << mmax << endl;
	cout << "m : " << m << endl;
	for (int i = 0; i < x.size(); i++) {
		x[i] = ((x[i] - min[0])*m) - 30000;
		y[i] = ((y[i] - min[1])*m) - 30000;
		//cout << x[i] << ", " << y[i] << endl;
	}
	max[0] = 0.0;
	max[1] = 0.0;
	min[0] = 999.99;
	min[1] = 999.99;
	for (int i = 0; i < x.size(); i++) {
		if (max[0] < x[i])
			max[0] = x[i];
		if (max[1] < y[i])
			max[1] = y[i];
		if (min[0] > x[i])
			min[0] = x[i];
		if (min[1] > y[i])
			min[1] = y[i];
	}
	cout << "Press for start." << endl;
	cout << "MIN : " << min[0] << ", " << min[1] << endl;
	cout << "MAX : " << max[0] << ", " << max[1] << endl;
	/*
	10000 = 3.0 cm = 3000 mm
	30000 = 8.5 cm = 8500 mm
	m = -30000 - 30000 / 155.000 - 174.825
	out = ((in-155.000)*m)-30000
	*/

	_getch();

	Laser *raylase = new Laser();

	if (!raylase->OnInitCard()) {
		cout << "Init Card is FALSE..." << endl;
		goto LASER_EXIT;
	}
	cout << "Serial Number : " << raylase->OnGetSn() << endl;
	cout << "Version : " << raylase->OnGetVersion() << endl;
	cout << "DLL Version : " << raylase->OnGetDLLVersion() << endl;
	if (!raylase->OnSetMode()) {
		cout << "OnSetMode is FALSE..." << endl;
		goto LASER_EXIT;
	}
	if (!raylase->OnSetCorrection(corrFile)) {
		cout << "OnSetCorrection is FALSE..." << endl;
		//goto LASER_EXIT;
	}
	//raylase->OnSetSpeed();
	Set_Gain(1.0, 1.0, 0.0, 0.0);
	if (!raylase->OnSetStartList()) {
		cout << "OnSetStartList is FALSE..." << endl;
		goto LASER_EXIT;
	}

	/*
	short s = 10000;
	short ms = 50;
	Jump_Abs(0, 0);
	raylase->LaserOn(ms);
	*/
	raylase->OnKvadrat();
	/*
	Jump_Abs(s, -s);
	raylase->LaserOn(ms);
	Jump_Abs(s, s);
	raylase->LaserOn(ms);
	Jump_Abs(-s, -s);
	raylase->LaserOn(ms);
	Jump_Abs(-s, s);
	raylase->LaserOn(ms);
	s = 30000;
	Jump_Abs(s, -s);
	raylase->LaserOn(ms);
	Jump_Abs(s, s);
	raylase->LaserOn(ms);
	Jump_Abs(-s, -s);
	raylase->LaserOn(ms);
	Jump_Abs(-s, s);
	raylase->LaserOn(ms);
	Laser_Off(0);

	Enable_Laser();
	Laser_Off(0);
	Jump_Abs(x[0], y[0]);
	Laser_On(0);
	for (int i = 0; i < x.size(); i++) {
		PolA_Abs(x[i], y[i]);
		Long_Delay(500);
	}
	*/
	Laser_Off(0);

	if (!raylase->OnSetEndOfList()) {
		cout << "OnSetEndOfList is FALSE..." << endl;
		goto LASER_EXIT;
	}
	if (!raylase->OnExecuteList()) {
		cout << "OnExecuteList is FALSE..." << endl;
		goto LASER_EXIT;
	}

	/*

	//raylase->OnKvadrat();

	if (!raylase->OnStopExecution()) {
		cout << "OnStopExecution is FALSE..." << endl;
		goto LASER_EXIT;
	}
	*/

LASER_EXIT:
	cout << "Press any key to STOP." << endl;
	_getch();
	if (!raylase->OnStopExecution()) {
		cout << "OnStopExecution is FALSE..." << endl;
		_getch();
	}
	return 0;
}

Laser::Laser() {
	bInitCard = bSetMode = bLoadCorr = bStartList = bExeList = bSetDelay = bSetSpeed = true;
}

bool Laser::OnInitCard()
{
	printf("Init_Scan_Card_Ex(1) : %d\n", Init_Scan_Card_Ex(1));
	bInitCard = (Init_Scan_Card_Ex(1) == 0);
	return bInitCard;
}
bool Laser::OnSetMode()
{
	unsigned short usMode = 0x0410;
	bSetMode = false;
	if (bInitCard)
	{
		bSetMode = Set_Mode(usMode);
	}
	return bSetMode;
}
bool Laser::OnSetCorrection(char *fname)
{
	bLoadCorr = false;
	if (bSetMode) {
		bLoadCorr = Load_Cor(fname);
	}
	return bLoadCorr;
}

bool Laser::OnSetEndOfList()
{
	bEndList = false;
	if (bInitCard && bSetMode)
	{
		bEndList = Set_End_Of_List();
	}
	return bEndList;
}

bool Laser::OnSetStartList()
{
	bStartList = false;
	if (bInitCard && bSetMode)
	{
		bStartList = Set_Start_List_1();
	}
	return bStartList;
}

bool Laser::OnExecuteList()
{
	bExeList = false;
	if (bInitCard && bSetMode)
	{
		bExeList = Execute_List_1();
	}
	return bExeList;
}

bool Laser::OnSetDelays()
{
	bSetDelay = false;
	if (bInitCard && bSetMode)
	{
		bSetDelay = Set_Delays(60, 100,
			100, 100,
			100, 100,
			100, 50, 0);
	}
	return bSetDelay;
}

bool Laser::OnSetSpeed()
{
	bSetSpeed = false;
	if (bInitCard && bSetMode)
	{
		bSetSpeed = Set_Speed(100, 100);
	}
	return bSetSpeed;
}

void Laser::OnKvadrat()
{
	Set_Speed(500, 150);
	bool isOK;
	/*
	isOK = PolA_Abs(0, 32000);
	//isOK = PolA_Abs(-32000, -32000);
	isOK = PolB_Abs(32000, 32000);
	isOK = PolB_Abs(32000, 0);
	//isOK = PolC_Abs(32000, -32000);
	isOK = PolC_Abs(0, 0);
	*/
	isOK = PolA_Abs(0, 10000);
	isOK = PolB_Abs(0 + 10000, 0 + 10000);
	isOK = PolB_Abs(0 + 10000, 0);
	isOK = PolC_Abs(0, 0);
}


bool Laser::OnStopExecution()
{
	return Stop_Execution();
}


unsigned int Laser::OnGetSn()
{
	if (bInitCard)
		return Get_Ident_Ex();
	return 0;
}
unsigned int Laser::OnGetVersion()
{
	if (bInitCard)
		return Get_Version();
	return 0;
}
unsigned int Laser::OnGetDLLVersion()
{
	if (bInitCard)
		return Get_DLL_Version();
	return 0;
}
void Laser::LaserOn(unsigned short ms) {
	Laser_On(0);
	for(int i=0; i<ms; i++)
		Long_Delay(100);
	Laser_Off(0);
}
