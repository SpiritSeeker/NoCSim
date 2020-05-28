#pragma once

#include "NoCSim/Core/Core.h"

namespace NoCSim {

  enum FlowState
  {
    FlowWait, FlowTransmit, FlowComplete
  };

  class Flow
  {
  public:
    Flow(uint32_t flowID);
    Flow(uint32_t flowID, uint32_t sourceCoreID, uint32_t destinationCoreID);
    ~Flow() = default;

    void OnUpdate();

    void SetSourceCoreID(uint32_t sourceCoreID) { m_SourceCoreID = sourceCoreID; }
    void SetDestinationCoreID(uint32_t destinationCoreID) { m_DestinationCoreID = destinationCoreID; }
    void SetFlowPriority(uint32_t flowPriority) { m_FlowPriority = flowPriority; }
    void SetFlowVolume(float flowVolume) { m_FlowVolume = flowVolume; }
    void SetFlowState(FlowState flowState) { m_FlowState = flowState; }

    const uint32_t GetFlowID() const { return m_FlowID; }
    const uint32_t GetSourceCoreID() const { return m_SourceCoreID; }
    const uint32_t GetDestinationCoreID() const { return m_DestinationCoreID; }
    const uint32_t GetFlowPriority() const { return m_FlowPriority; }
    const float GetFlowVolume() const { return m_FlowVolume; }
    const FlowState GetFlowState() const { return m_FlowState; }

    static Ref<Flow> Create(uint32_t flowID);
    static Ref<Flow> Create(uint32_t flowID, uint32_t sourceCoreID, uint32_t destinationCoreID);
  private:
    uint32_t m_FlowID;
    uint32_t m_SourceCoreID;
    uint32_t m_DestinationCoreID;
    uint32_t m_FlowPriority;
    float m_FlowVolume;
    FlowState m_FlowState;
  };

}
