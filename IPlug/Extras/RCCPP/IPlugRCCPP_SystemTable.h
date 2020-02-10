#pragma once

#ifndef INTERFACEIDS_INCLUDED
#define INTERFACEIDS_INCLUDED

#include "RuntimeObjectSystem/IObject.h"

namespace iplug
{
  class IPlugAPP;
}

struct SystemTable
{
  iplug::IPlugAPP* pPlug;
  void* pParentWindow;
  void* pAppHost; // for InstanceInfo
};

#endif //INTERFACEIDS_INCLUDED

