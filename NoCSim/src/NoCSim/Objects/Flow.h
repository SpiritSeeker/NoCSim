#pragma once

#include "NoCSim/Core/Core.h"

namespace NoCSim {

  class Flow
  {
  public:
    Flow(uint32_t flowID);
    Flow(uint32_t flowID, uint32_t sourceID, uint32_t destinationID);
    ~Flow() = default;

    void OnUpdate();

    void SetSourceID(uint32_t sourceID) { m_SourceID = sourceID; }
    void SetDestinationID(uint32_t destinationID) { m_DestinationID = destinationID; }
    void SetFlowPriority(uint32_t flowPriority) { m_FlowPriority = flowPriority; }
    void SetFlowVolume(float flowVolume) { m_FlowVolume = flowVolume; }

    const uint32_t GetFlowID() const { return m_FlowID; }
    const uint32_t GetSourceID() const { return m_SourceID; }
    const uint32_t GetDestinationID() const { return m_DestinationID; }
    const uint32_t GetFlowPriority() const { return m_FlowPriority; }
    const float GetFlowVolume() const { return m_FlowVolume; }

    static Ref<Flow> Create(uint32_t flowID);
    static Ref<Flow> Create(uint32_t flowID, uint32_t sourceID, uint32_t destinationID);
  private:
    uint32_t m_FlowID;
    uint32_t m_SourceID;
    uint32_t m_DestinationID;
    uint32_t m_FlowPriority;
    float m_FlowVolume;
  };

}
