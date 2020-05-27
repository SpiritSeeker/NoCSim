#include "nspch.h"
#include "Flow.h"

namespace NoCSim {

  Flow::Flow(uint32_t flowID)
    : m_FlowID(flowID)
  {}

  Flow::Flow(uint32_t flowID, uint32_t sourceID, uint32_t destinationID)
    : m_FlowID(flowID), m_SourceID(sourceID), m_DestinationID(destinationID)
  {}

  Ref<Flow> Flow::Create(uint32_t flowID)
  {
    return CreateRef<Flow>(flowID);
  }

  Ref<Flow> Flow::Create(uint32_t flowID, uint32_t sourceID, uint32_t destinationID)
  {
    return CreateRef<Flow>(flowID, sourceID, destinationID);
  }

  void Flow::OnUpdate()
  {
  }

}
