#include "pch.h"

#include "MemoryControl.h"


MemoryController  Controller;

uint64_t g_TargetEProcess = 0;

USERMEMORYOPERATION64_API LONG Initialization()
{
    VMProtectBeginUltra("Initialization");
#ifndef VMP_VERSION
    MessageBox(NULL, "��ǰ�汾����VMP���� ����Ƿ����汾 ����PCH.H�ж���VMP_VERSION\n ����ǲ��԰汾 ���Ӵ���ʾ.\n", "No Vmp", MB_OK);
#endif // !VMP_VERSION

    SYSTEMTIME systm;
    GetLocalTime(&systm);

    if (systm.wMonth == 10 && systm.wDay <= 30)
    {
        Controller = Mc_InitContext();
    }
    else
    {
        Controller.CreationStatus = 1;
    }
    Sleep(200);
    VMProtectEnd();
    return Controller.CreationStatus;
}

USERMEMORYOPERATION64_API uint64_t GetTargetBase(uint64_t pid)
{
    //VMProtectBeginUltra("GetTargetBase");
    uint64_t EProcess = Controller.FindEProcess(pid);

    if (EProcess == 0)
        return 0;

    g_TargetEProcess = EProcess;

    Controller.AttachTo(EProcess);

    uint64_t GameBase = Controller.ReadProcessBase(EProcess);

    //Controller.Detach();
    //VMProtectEnd();
    return GameBase;
}

USERMEMORYOPERATION64_API void WriteByte(LPVOID Dst, PVOID  Src, SIZE_T Size) 
{
    //VMProtectBeginUltra("WriteByte");
    //Controller.AttachTo(g_TargetEProcess);
    Controller.WriteVirtual(Src, Dst, Size);
    //Controller.Detach();
    //VMProtectEnd();
}

USERMEMORYOPERATION64_API void ReadByte(LPVOID Dst, PVOID  Src, SIZE_T Size) 
{
    //VMProtectBeginUltra("ReadByte");
    //Controller.AttachTo(g_TargetEProcess);
    Controller.ReadVirtual(Dst, Src, Size);
    //Controller.Detach();
    //VMProtectEnd();
}





