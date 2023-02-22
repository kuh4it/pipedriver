#include <ntddk.h>
#include "Communication.hh"

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(DriverObject);
    UNREFERENCED_PARAMETER(RegistryPath);

    // Initialize the communication channel with user mode
    if (!InitializeCommunication())
    {
        DbgPrint("Failed to initialize the communication channel.\n");
        return STATUS_UNSUCCESSFUL;
    }

    DbgPrint("The driver has been loaded successfully.\n");

    return STATUS_SUCCESS;
}
