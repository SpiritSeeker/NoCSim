#include "nspch.h"
#include "Flow.h"

namespace NoCSim {

  Flow::Flow(uint32_t flowID)
    : m_FlowID(flowID)
  {
    m_FlowState = FlowWait;
  }

  Flow::Flow(uint32_t flowID, uint32_t sourceCoreID, uint32_t destinationCoreID)
    : m_FlowID(flowID), m_SourceCoreID(sourceCoreID), m_DestinationCoreID(destinationCoreID)
  {
    m_FlowState = FlowWait;
  }

  Ref<Flow> Flow::Create(uint32_t flowID)
  {
    return CreateRef<Flow>(flowID);
  }

  Ref<Flow> Flow::Create(uint32_t flowID, uint32_t sourceCoreID, uint32_t destinationCoreID)
  {
    return CreateRef<Flow>(flowID, sourceCoreID, destinationCoreID);
  }

  void Flow::OnUpdate()
  {
  }

}
