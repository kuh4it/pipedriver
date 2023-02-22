#include "Communication.hh"

NTSTATUS SendDataToUsermode(PVOID pData, ULONG uDataSize)
{
    NTSTATUS ntStatus = STATUS_SUCCESS;
    PEPROCESS pUserProcess = NULL;
    PVOID pMappedAddress = NULL;

    // Get a handle to the user process
    ntStatus = PsLookupProcessByProcessId((HANDLE)g_dwUserPID, &pUserProcess);
    if (!NT_SUCCESS(ntStatus))
    {
        DbgPrint("SendDataToUsermode: PsLookupProcessByProcessId failed: %08X\n", ntStatus);
        return ntStatus;
    }

    __try
    {
        // Map the user-mode buffer to kernel space
        ntStatus = ObReferenceObjectByHandle(g_hUserBuffer, 0, NULL, KernelMode, &pMappedAddress, NULL);
        if (!NT_SUCCESS(ntStatus))
        {
            DbgPrint("SendDataToUsermode: ObReferenceObjectByHandle failed: %08X\n", ntStatus);
            __leave;
        }

        // Copy the data to the user-mode buffer
        RtlCopyMemory(pMappedAddress, pData, uDataSize);
    }
    __finally
    {
        // Unmap the user-mode buffer from kernel space
        if (pMappedAddress)
        {
            ObDereferenceObject(pMappedAddress);
        }

        // Release the handle to the user process
        if (pUserProcess)
        {
            ObDereferenceObject(pUserProcess);
        }
    }

    return ntStatus;
}

NTSTATUS ReceiveDataFromUsermode(PVOID pData, ULONG uDataSize)
{
    NTSTATUS ntStatus = STATUS_SUCCESS;
    PEPROCESS pUserProcess = NULL;
    PVOID pMappedAddress = NULL;

    // Get a handle to the user process
    ntStatus = PsLookupProcessByProcessId((HANDLE)g_dwUserPID, &pUserProcess);
    if (!NT_SUCCESS(ntStatus))
    {
        DbgPrint("ReceiveDataFromUsermode: PsLookupProcessByProcessId failed: %08X\n", ntStatus);
        return ntStatus;
    }

    __try
    {
        // Map the user-mode buffer to kernel space
        ntStatus = ObReferenceObjectByHandle(g_hUserBuffer, 0, NULL, KernelMode, &pMappedAddress, NULL);
        if (!NT_SUCCESS(ntStatus))
        {
            DbgPrint("ReceiveDataFromUsermode: ObReferenceObjectByHandle failed: %08X\n", ntStatus);
            __leave;
        }

        // Copy the data from the user-mode buffer
        RtlCopyMemory(pData, pMappedAddress, uDataSize);
    }
    __finally
    {
        // Unmap the user-mode buffer from kernel space
        if (pMappedAddress)
        {
            ObDereferenceObject(pMappedAddress);
        }

        // Release the handle to the user process
        if (pUserProcess)
        {
            ObDereferenceObject(pUserProcess);
        }
    }

    return ntStatus;
}
