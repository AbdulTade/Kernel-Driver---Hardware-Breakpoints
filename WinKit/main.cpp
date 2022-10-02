#include <ntddk.h>
#include <wsk.h>

#define FILE_DEVICE_ROOTKIT 0x1234

const WCHAR DeviceNameBuffer[] = L"\\Device\\vicesys2";
PDEVICE_OBJECT g_RootKitDevice; // Global pointer to our device object
const WCHAR DeviceLinkBuffer[] = L"\\Devices\\vicesys2";


NTSTATUS OnStubDispatch(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);

	Irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

void Unload(IN PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);
	DbgPrint("OnUnload called\n");
}

NTSTATUS Close(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);
	return STATUS_SUCCESS;
}

NTSTATUS Read(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);
	return STATUS_SUCCESS;
}

NTSTATUS Write(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);
	return STATUS_SUCCESS;
}

NTSTATUS Open(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);
	return STATUS_SUCCESS;
}

NTSTATUS IoControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);
	PIO_STACK_LOCATION IrpSp;
	ULONG			   FunctionCode;

	IrpSp = IoGetCurrentIrpStackLocation(Irp);
	FunctionCode = IrpSp->Parameters.DeviceIoControl.IoControlCode;

	switch (FunctionCode)
	{
	case -1:
		break;

	default:
		break;
	}

	return STATUS_SUCCESS;
}


extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS ntStatus;

	UNICODE_STRING DeviceNameUnicodeString;
	UNICODE_STRING DeviceLinkUnicodeString;

	RtlInitUnicodeString(&DeviceLinkUnicodeString, DeviceLinkBuffer);
	RtlInitUnicodeString(&DeviceNameUnicodeString, DeviceNameBuffer);

	ntStatus = IoCreateDevice(DriverObject, 0, &DeviceNameUnicodeString, FILE_DEVICE_ROOTKIT, 0, TRUE, &g_RootKitDevice);

	if (NT_SUCCESS(ntStatus))
	{
		ntStatus = IoCreateSymbolicLink(&DeviceLinkUnicodeString, &DeviceNameUnicodeString);
	}


	return STATUS_SUCCESS;
}

