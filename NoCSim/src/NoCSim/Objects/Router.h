#pragma once

#include "NoCSim/Core/Core.h"

namespace NoCSim {

  class Router
  {
  public:
    Router(uint32_t routerID, float bufferSize);
    ~Router() = default;

    const uint32_t GetRouterID() const { return m_RouterID; }
    const float GetBufferSize() const { return m_BufferSize; }
  private:
    uint32_t m_RouterID;
    float m_BufferSize;
  };

}
