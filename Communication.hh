// Communication.h

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <ntddk.h>

#define COMMUNICATION_PIPE_NAME L"\\Device\\MyPipe"
#define COMMUNICATION_BUFFER_SIZE 1024

BOOLEAN InitializeCommunication();
VOID TerminateCommunication();
BOOLEAN ReadFromCommunication(PVOID Buffer, ULONG BufferSize, PULONG BytesRead);
BOOLEAN WriteToCommunication(PVOID Buffer, ULONG BufferSize, PULONG BytesWritten);

#endif
