#include "stdafx.h"
#include "TestPOrb.h"
#include "Commands.h"
#include "UdpSocketPort.h"
#include "SerialPort.h"
#include "PTrace.h"

PRT_PROCESS* MAIN_APPLICATION_PROCESS = NULL;
bool trace = false;

void ErrorHandler(PRT_STATUS status, PRT_MACHINEINST *ptr)
{
	if (status == PRT_STATUS_ASSERT)
	{
		EventTrace(PRuntime, status, "exiting with PRT_STATUS_ASSERT (assertion failure)\n");
		exit(1);
	}
	else if (status == PRT_STATUS_EVENT_OVERFLOW)
	{
		EventTrace(PRuntime, status, "exiting with PRT_STATUS_EVENT_OVERFLOW\n");
		exit(1);
	}
	else if (status == PRT_STATUS_EVENT_UNHANDLED)
	{
		EventTrace(PRuntime, status, "exiting with PRT_STATUS_EVENT_UNHANDLED\n");
		exit(1);
	} 
	else if (status == PRT_STATUS_QUEUE_OVERFLOW)
	{
		EventTrace(PRuntime, status, "exiting with PRT_STATUS_QUEUE_OVERFLOW \n");
		exit(1);
	}
	else if (status == PRT_STATUS_ILLEGAL_SEND)
	{
		EventTrace(PRuntime, status, "exiting with PRT_STATUS_ILLEGAL_SEND \n");
		exit(1);
	}
	else
	{
		EventTrace(PRuntime, status, "unexpected PRT_STATUS in ErrorHandler: %d\n", status);
		exit(2);
	}
}

void Log(PRT_STEP step, PRT_MACHINEINST *context, PRT_MACHINEINST *sender, PRT_VALUE* event, PRT_VALUE* payload)
{
	if (trace ) PrtPrintStep(step, context, sender, event, payload);
}

bool isUdp = false;
const char* portName = NULL;

bool ParseCommandLine(int argc, char* argv[])
{
	// parse command line
	for (int i = 1; i < argc; i++)
	{
		const char* arg = argv[i];
		if (arg[0] == '-' || arg[0] == '/')
		{
			std::string lower(arg + 1);
			_strlwr_s((char*)lower.c_str(), lower.length() + 1);
			if (lower == "udp")
			{
				if (i + 1 < argc)
				{
					isUdp = true;
					portName = argv[++i];
				}
				else
				{
					printf("### Error: missing ip address after -udp argument\n");
					return false;
				}
			}
			else if (lower == "com")
			{
				isUdp = false;
				if (i + 1 < argc)
				{
					portName = argv[++i];
				}
			}
			else if (lower == "h" || lower == "?" || lower == "help" || lower == "-help")
			{
				return false;
			}
			else if (lower == "v")
			{
				trace = true;
			}
			else
			{
				printf("### Error: unexpected argument: %s\n", arg);
				return false;
			}
		}
		else
		{
			printf("### Error: unexpected argument: %s\n", arg);
			return false;
		}
	}
	return true;
}

void PrintUsage() {
	printf("Usage: PX4 [-udp ipaddr] [-com port]\n");
	printf("Connects to PX4 either over udp or serial COM port\n");
	printf("If no arguments it will find a COM port matching PX4\n");
}

void P_CTOR_Main_IMPL(PRT_MACHINEINST *context, PRT_VALUE *value)
{
}
void P_DTOR_Main_IMPL(PRT_MACHINEINST *context)
{
}
void MyPrint(PRT_CSTRING msg)
{
	// output in both places.
	printf_s(msg);
	EventTrace(PProgram, 0, msg);
}

#define DEFAULT_MAVLINK_PORT 14550

Port* OpenPort(bool isUdp, const char* portAddress)
{
	if (isUdp)
	{
		if (UdpSocketPort::Initialize() != 0)
		{
			EventTrace(Communication, E_FAIL, "Could not initialize sockets\n");
			return NULL;
		}
		UdpSocketPort::Initialize();
		UdpSocketPort* socket = new UdpSocketPort();

		HRESULT hr = socket->Connect(portAddress, DEFAULT_MAVLINK_PORT);
		if (hr != 0)
		{
			EventTrace(Communication, hr, "Could not open the socket to %s, error=%d\n", portAddress, hr);
			if (hr == ERROR_ACCESS_DENIED)
			{
				EventTrace(Communication, hr, "Error ERROR_ACCESS_DENIED, is another app using the port?\n");
			}
			return NULL;
		}
		return socket;
	}
	else
	{
		int baudRate = 115200;
		int dataBits = 8;
		bool dtr_enable = false;
		bool rts_enable = false;
		int readTimeout = -1;
		int write_timeout = 500;
		int readBufferSize = 16384;
		int writeBufferSize = 2048;
		const char* initString = "sh /etc/init.d/rc.usb\n";
		int hr = 0;

		SerialPort * serial = new SerialPort();
		std::string name(portAddress == NULL ? "" : portAddress);
		if (portAddress == NULL)
		{
			hr = serial->Find("PX4", name);
			if (hr != 0 || name.length() == 0)
			{
				EventTrace(Communication, hr, "### Error: could not find the PX4 Serial Port");
				return NULL;
			}
			else
			{
				EventTrace(Communication, hr, "Opening PX4 SerialPort on %s\n", name.c_str());
			}
		}
		hr = serial->Open(name.c_str(), baudRate, dataBits, Parity_None, StopBits_10, dtr_enable, rts_enable, Handshake_None, readTimeout, write_timeout, readBufferSize, writeBufferSize);
		if (hr != 0)
		{
			EventTrace(Communication, hr, "Could not open the COM port %s, error=%d\n", name.c_str(), hr);
			if (hr == ERROR_ACCESS_DENIED)
			{
				EventTrace(Communication, hr, "Error ERROR_ACCESS_DENIED, is another app using the COM port?\n");
			}
			return NULL;
		}

		// send this right away.
		hr = serial->Write((BYTE*)initString, (int)strlen(initString));

		return serial;
	}

}

int main(int argc, char *argv[])
{
	EventLog log("trace.txt");

	if (!ParseCommandLine(argc, argv))
	{
		PrintUsage();
		return 1;
	}
	Port* port = OpenPort(isUdp, portName);
	if (port == NULL) {
		return 1;
	}
	POrbMavlink::Initialize(port);

	//remove all
	//-----------------------------
	PrtUpdatePrintFn(&MyPrint);

	PRT_GUID processGuid;
	PRT_VALUE *payload;
	processGuid.data1 = 1;
	processGuid.data2 = 0;
	processGuid.data3 = 0;
	processGuid.data4 = 0;
	MAIN_APPLICATION_PROCESS = PrtStartProcess(processGuid, &P_GEND_PROGRAM, ErrorHandler, Log);
	payload = PrtMkNullValue();

	//create the main machine
	PrtMkMachine(MAIN_APPLICATION_PROCESS, P_MACHINE_POrbMachine, payload);
	PrtFreeValue(payload);

	// todo: when to exit?
	while (true)
	{
		SleepEx(1000, TRUE);
	}

	PrtStopProcess(MAIN_APPLICATION_PROCESS);
}
