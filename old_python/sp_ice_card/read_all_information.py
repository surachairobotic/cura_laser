

import time
import ctypes
sp_ice = ctypes.CDLL("C:\\Program Files\\RAYLASE\\SP-ICE\\bin\\SP-ICE.dll")

def main():
    global sp_ice
    
    sp_ice.Init_Scan_Card_Ex.restype = ctypes.c_int32
    sp_ice.Init_Scan_Card_Ex.argtype = ctypes.c_short
    
    err = sp_ice.Init_Scan_Card_Ex(ctypes.c_short(1).value)
    print(str(err) + " : " + str(type(err)))
    if err != 0:
        sp_ice.Get_Error_Message.restype = ctypes.c_char_p
        sp_ice.Get_Error_Message.argtype = [ctypes.c_int32]
        msgs = sp_ice.Get_Error_Message(err)
        print("Err != 0 : " + str(type(msgs)))
    print("Init_Scan_Card_Ex : " + str(msgs))
    #print("Init_Scan_Card_Ex : " + ctypes.cast(msgs, ctypes.c_char_p).value)
    read()
    control()
    print("Remove_Scan_Card_Ex : " + str(sp_ice.Remove_Scan_Card_Ex(1)))

def control():
    global sp_ice
    
    print("Set_Mode : " + str(sp_ice.Set_Mode(0x0410)))
    print("Set_Start_List_1 : " + str(sp_ice.Set_Start_List_1()))

    print("Enable_Laser : " + str(sp_ice.Enable_Laser()))
    print("Laser_On : " + str(sp_ice.Laser_On()))

    print("PolA_Abs : " + str(sp_ice.PolA_Abs(0, 0 + 10000)))
    print("PolB_Abs : " + str(sp_ice.PolB_Abs(0+10000, 0 +10000)))
    print("PolB_Abs : " + str(sp_ice.PolB_Abs(0+10000, 0)))
    print("PolC_Abs : " + str(sp_ice.PolC_Abs(0, 0)))

    print("Laser_Off : " + str(sp_ice.Laser_Off()))
    print("Disable_Laser : " + str(sp_ice.Disable_Laser()))

    print("Set_End_Of_List : " + str(sp_ice.Set_End_Of_List()))
    print("Execute_List_1 : " + str(sp_ice.Execute_List_1()))
    
    
    #print("Laser_Off : " + str(sp_ice.Laser_Off()))
    #print("Laser_On : " + str(sp_ice.Laser_On()))
    #time.sleep(1)
    #print("Laser_Off : " + str(sp_ice.Laser_Off()))
    
    #print("Set_Delays : " + str(sp_ice.Set_Delays()))
    
    #print("Enable_Laser : " + str(sp_ice.Enable_Laser()))
    #print("Laser_Off : " + str(sp_ice.Laser_Off()))
    #print("Laser_On : " + str(sp_ice.Laser_On()))
    time.sleep(3)
    #print("Laser_Off : " + str(sp_ice.Laser_Off()))
    #print("Disable_Laser : " + str(sp_ice.Disable_Laser()))

def read():
    global sp_ice
    print("Hello world !!!")
    print("Get_Active_Card : " + str(sp_ice.Get_Active_Card()))
    print("Set_Active_Card : " + str(sp_ice.Set_Active_Card(1)))
    print("Get_Active_Card : " + str(sp_ice.Get_Active_Card()))
    print("Get_Counts : " + str(sp_ice.Get_Counts()))
    print("Get_CPU_Type : " + str(sp_ice.Get_CPU_Type()))
    print("Get_DLL_Version : " + str(sp_ice.Get_DLL_Version()))
    
    print("Get_Ident_Ex : " + str(sp_ice.Get_Ident_Ex()))
    print("Get_Jump_Speed : " + str(sp_ice.Get_Jump_Speed()))
    print("Get_Mark_Speed : " + str(sp_ice.Get_Mark_Speed()))
    #print("Get_Mode_Mask : " + str(sp_ice.Get_Mode_Mask()))
    print("Get_SPC1_Version : " + str(sp_ice.Get_SPC1_Version()))
    print("Get_System_Status : " + str(sp_ice.Get_System_Status()))
    print("Get_Version : " + str(sp_ice.Get_Version()))
    #print("Get_XY_Pos : " + str(sp_ice.Get_Version()))

    # RLC Only
    #print("Get_Device_Description_String : " + str(sp_ice.Get_Device_Description_String()))
    #print("Get_Driver_Version : " + str(sp_ice.Get_Driver_Version()))
    #print("Get_Firmware_Version : " + str(sp_ice.Get_Firmware_Version()))
    #print("Get_Hardware_Version : " + str(sp_ice.Get_Hardware_Version()))
    #print("Get_Library_Version : " + str(sp_ice.Get_Library_Version()))
    

if __name__ == "__main__":
    main()
    print("END !!!")
