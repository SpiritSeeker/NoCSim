#include "nspch.h"
#include "Flit.h"

namespace NoCSim {

  Flit::Flit(uint32_t taskID, uint32_t sourceCoreID, uint32_t destinationCoreID, uint32_t flowID, uint32_t priority, uint32_t flowIteration)
    : m_TaskID(taskID), m_SourceCoreID(sourceCoreID), m_DestinationCoreID(destinationCoreID), m_FlowID(flowID), m_Priority(priority), m_FlowIteration(flowIteration)
  {
    m_FlitSize = 128.0f;
  }

}
