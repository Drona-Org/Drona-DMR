#include "pch.h"
#include "Simulation.h"
#include <ppl.h>
using namespace FlightController;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace concurrency;

static Simulation^ s_Simulator;

extern "C"
{
#define __PrtDistIDL_h_h__  // winrt doesn't like the RPC interface
#include "StateMachine.h"


}


void __cdecl LogForwarder(const char* msg) {
    Simulation^ sim = s_Simulator;
    if (sim != nullptr)
    {
        std::string str(msg);
        std::wstring widestr(str.begin(), str.end());
        sim->HandleLogEvent(ref new Platform::String(widestr.c_str()));
    }
}

Simulation::Simulation()
{
    StorageFolder^ folder = Windows::Storage::ApplicationData::Current->LocalFolder;
    Platform::String^ path = folder->Path;
    std::wstring wide(path->Data());
    std::string ascii(wide.begin(), wide.end());
    Init((PRT_CHAR*)ascii.c_str());
}

Simulation::~Simulation() {
}

void Simulation::HandleLogEvent(Platform::String^ message)
{
    LogEvent(this, message);
}

void Simulation::Start()
{
    s_Simulator = this;
    create_async([=] {
        RunSimulation(LogForwarder);
    });
}


void Simulation::Stop()
{
    StopSimulation();
    s_Simulator = nullptr;
}

void Simulation::RaiseEvent(SimulationMachine machineId, SimulationEvent eventId, Platform::Object^ payload)
{
    PRT_VALUE* value = nullptr;

    if (payload == nullptr)
    {
        value = MakeNullValue();
    }
    else
    {
        IPropertyValue^ ipv = dynamic_cast<IPropertyValue^>(payload);

        switch (ipv->Type)
        {
        case PropertyType::Boolean:
        {
            bool b = ipv->GetBoolean();
            value = MakeBooleanValue((BOOL)b);
        }
        break;
        case PropertyType::UInt8:
        {
            int32_t i = ipv->GetUInt8();
            value = MakeIntegerValue(i);
        }
        break;
        case PropertyType::Int16:
        {
            int32_t i = ipv->GetInt16();
            value = MakeIntegerValue(i);
        }
        break;
        case PropertyType::Int32:
        {
            int32_t i = ipv->GetInt32();
            value = MakeIntegerValue(i);
        }
        break;
        case PropertyType::Int64:
        {
            int32_t i = (int32_t)ipv->GetInt64();
            value = MakeIntegerValue(i);
        }
        break;
        case PropertyType::UInt16:
        {
            int32_t i = ipv->GetUInt16();
            value = MakeIntegerValue(i);
        }
        break;
        case PropertyType::UInt32:
        {
            int32_t i = ipv->GetUInt32();
            value = MakeIntegerValue(i);
        }
        break;
        case PropertyType::UInt64:
        {
            int32_t i = (int32_t)ipv->GetUInt64();
            value = MakeIntegerValue(i);
        }
        break;
        default:
            throw ref new Platform::InvalidArgumentException(L"Value type is not supported");
            break;

        }
    }

    ::RaiseEvent((int)machineId, (int)eventId, value);
    if (value != nullptr)
    {
        PrtFreeValue(value);
    }
}
