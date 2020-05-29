#pragma once

#include "NoCSim/Core/Core.h"

namespace NoCSim {

  class Flit
  {
  public:
    Flit(uint32_t sourceCoreID, uint32_t destinationCoreID, uint32_t flowID, uint32_t priority, uint32_t flowIteration);
    ~Flit() = default;

    const uint32_t GetSourceCoreID() const { return m_SourceCoreID; }
    const uint32_t GetDestinationCoreID() const { return m_DestinationCoreID; }
    const uint32_t GetFlowID() const { return m_FlowID; }
    const uint32_t GetPriority() const { m_Priority; }
    const uint32_t GetFlowIteration() const { m_FlowIteration; }
    const float GetFlitSize() const { m_FlitSize; }

    void SetFlitSize(float flitSize) { m_FlitSize = flitSize; }
  private:
    uint32_t m_SourceCoreID, m_DestinationCoreID, m_FlowID;
    uint32_t m_Priority;
    uint32_t m_FlowIteration;
    float m_FlitSize;
  };

}
