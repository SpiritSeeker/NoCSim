#include "nspch.h"
#include "Flow.h"

namespace NoCSim {

  Flow::Flow(uint32_t flowID)
    : m_FlowID(flowID)
  {
    m_FlowState = NonActive;
    m_Iteration = 0;
  }

  Flow::Flow(uint32_t flowID, uint32_t sourceCoreID, uint32_t destinationCoreID)
    : m_FlowID(flowID), m_SourceCoreID(sourceCoreID), m_DestinationCoreID(destinationCoreID)
  {
    m_FlowState = NonActive;
    m_Iteration = 0;
  }

  void Flow::NextIteration(uint32_t iteration)
  {
    m_Iteration = iteration;
    m_FlowState = Active;
    m_RemainingVolume = m_FlowVolume;
    NS_CORE_TRACE("Begining Flow {0}: From Node {1} to Node {2}", m_FlowID, m_SourceCoreID, m_DestinationCoreID);
  }

  Ref<Flit> Flow::GetFlit()
  {
    Ref<Flit> flit = CreateRef<Flit>(m_TaskID, m_SourceCoreID, m_DestinationCoreID, m_FlowID, m_FlowPriority, m_Iteration);
    m_RemainingVolume -= flit->GetFlitSize();
    if (m_RemainingVolume < 0)
      m_FlowState = NonActive;

    return flit;
  }

  Ref<Flow> Flow::Create(uint32_t flowID)
  {
    return CreateRef<Flow>(flowID);
  }

  Ref<Flow> Flow::Create(uint32_t flowID, uint32_t sourceCoreID, uint32_t destinationCoreID)
  {
    return CreateRef<Flow>(flowID, sourceCoreID, destinationCoreID);
  }

}
