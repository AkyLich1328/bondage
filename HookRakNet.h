#pragma once
#include "main.h"

bool __stdcall outcomingData(stRakNetHookParams *params);

bool __stdcall incomingData(stRakNetHookParams *params);

bool __stdcall incomingRPC(stRakNetHookParams *params);

bool __stdcall outcomingRPC(stRakNetHookParams *params);