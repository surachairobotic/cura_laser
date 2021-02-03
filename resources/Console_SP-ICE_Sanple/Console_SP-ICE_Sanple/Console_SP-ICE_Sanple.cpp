// Console_SP-ICE_Sanple.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>

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
private:
	bool bInitCard, bSetMode, bLoadCorr, bStartList, bEndList, bExeList, bSetDelay, bSetSpeed;
};

int main()
{
	string line;
	ifstream myfile("C:\\cura_laser\\resources\\UMS5_cube_10_20_30_filter_l100.gcode");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			int indx = line.find(',');
			string sX = line.substr(1, indx-1);
			string sY = line.substr(indx+2, line.size()-(indx+2)-1);
			cout << sX  << " : " << sY << '\n';
		}
		myfile.close();
	}
	char x;
	//cin >> x;
	//return 1;
	char *corrFile = "E:\\Laser software\\Raylase\\TSL-355-90-163-D10-B_MS-10_LR25,0.gcd";
	cout << "Press for start." << endl;
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
	raylase->OnSetSpeed();
	Set_Gain(100.0, 100.0, 0.0, 0.0);
	if (!raylase->OnSetStartList()) {
		cout << "OnSetStartList is FALSE..." << endl;
		goto LASER_EXIT;
	}
	raylase->OnKvadrat();
	if (!raylase->OnSetEndOfList()) {
		cout << "OnSetEndOfList is FALSE..." << endl;
		goto LASER_EXIT;
	}
	if (!raylase->OnExecuteList()) {
		cout << "OnExecuteList is FALSE..." << endl;
		goto LASER_EXIT;
	}
	if (!raylase->OnStopExecution()) {
		cout << "OnStopExecution is FALSE..." << endl;
		goto LASER_EXIT;
	}


LASER_EXIT:
	_getch();
	return 0;
}

Laser::Laser() {
	bInitCard = bSetMode = bLoadCorr = bStartList = bExeList = bSetDelay = bSetSpeed = true;
}

bool Laser::OnInitCard()
{
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
