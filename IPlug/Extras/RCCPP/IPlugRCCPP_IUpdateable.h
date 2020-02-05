#pragma once

#ifndef IUPDATEABLE_INCLUDED
#define IUPDATEABLE_INCLUDED

#include "RuntimeObjectSystem/IObject.h"

struct IUpdateable : public IObject
{
  virtual void OnCompile(void* pPlug) = 0;
  virtual void Update(float deltaTime) = 0;
};

#endif // IUPDATEABLE_INCLUDED
