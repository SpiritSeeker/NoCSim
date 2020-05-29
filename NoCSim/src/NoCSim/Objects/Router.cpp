#include "nspch.h"
#include "Router.h"

namespace NoCSim {

  Router::Router(uint32_t routerID)
    : m_RouterID(routerID)
  {}

  void Router::BeginFlows()
  {
    for (auto flow : m_Flows)
      flow->NextIteration();

    std::remove_if(m_OutputBuffer.begin(), m_OutputBuffer.end(),
    [this](const Ref<Flit>& flit)
    {
      return (flit->GetSourceCoreID() == this->m_RouterID);
    });
  }

  void Router::OnUpdate()
  {
    for (auto flit : m_InputBuffer)
    {
      if (flit->GetDestinationCoreID() == m_RouterID)
        m_ToNodeBuffer.push_back(flit);
      else
        m_OutputBuffer.push_back(flit);
    }
    m_InputBuffer.clear();

    for (auto flow : m_Flows)
    {
      if (flow->GetFlowState() == Active)
      {
        bool flitInBuffer = false;
        for (auto flit : m_OutputBuffer)
        {
          if (flit->GetFlowID() == flow->GetFlowID())
          {
            flitInBuffer = true;
            break;
          }
        }

        if (!flitInBuffer)
          m_OutputBuffer.push_back(flow->GetFlit());
      }
    }


  }

}
