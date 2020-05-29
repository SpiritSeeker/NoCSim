#include "nspch.h"
#include "Router.h"

namespace NoCSim {

  Router::Router(uint32_t routerID)
    : m_RouterID(routerID)
  {
    m_ToChannel["Left"] = std::vector<Ref<Flit>>();
    m_ToChannel["Right"] = std::vector<Ref<Flit>>();
    m_ToChannel["Top"] = std::vector<Ref<Flit>>();
    m_ToChannel["Bottom"] = std::vector<Ref<Flit>>();
  }

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
        {
          auto flit = flow->GetFlit();
          m_OutputBuffer.push_back(flit);
        }
      }
    }

    if (!std::is_sorted(m_OutputBuffer.begin(), m_OutputBuffer.end(),
      [](const auto& a, const auto& b)
      {
        return (a->GetPriority() < b->GetPriority());
      }))
      std::sort(m_OutputBuffer.begin(), m_OutputBuffer.end(),
        [](const auto& a, const auto& b)
        {
          return (a->GetPriority() < b->GetPriority());
        });

    std::vector<Ref<Flit>> retainList;
    for (uint32_t i = 0; i < m_OutputBuffer.size(); i++)
    {
      std::string direction = m_RoutingTable[m_OutputBuffer[i]->GetDestinationCoreID()];
      if (m_ToChannel.at(direction).empty())
        m_ToChannel.at(direction).push_back(m_OutputBuffer[i]);
      else
        retainList.push_back(m_OutputBuffer[i]);
    }
    m_OutputBuffer = retainList;
  }

}
