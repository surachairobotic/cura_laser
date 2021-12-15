#include "stdio.h"
#include "SPIC_Export.h"

int read(void) {
    printf("Hello world !!!");
    printf("Get_Active_Card : %d", Get_Active_Card());
    printf("Set_Active_Card : %d", Set_Active_Card(1));
    printf("Get_Active_Card : %d", Get_Active_Card());
    printf("Get_Counts : %d", Get_Counts());
    printf("Get_CPU_Type : %d", Get_CPU_Type());
    printf("Get_DLL_Version : %d", Get_DLL_Version());
    
    printf("Get_Ident_Ex : %d", Get_Ident_Ex());
    printf("Get_Jump_Speed : %lf", Get_Jump_Speed());
    printf("Get_Mark_Speed : %lf", Get_Mark_Speed());
    //printf("Get_Mode_Mask : %d", Get_Mode_Mask());
    printf("Get_SPC1_Version : %d", Get_SPC1_Version());
    printf("Get_System_Status : %d", Get_System_Status());
    printf("Get_Version : %d", Get_Version());
	
	return 0;
}

int main (int argc, char *argv[]) {
	read();
	
	return 0;
}