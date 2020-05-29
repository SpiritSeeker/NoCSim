#pragma once

#include "NoCSim/Core/Core.h"
#include "NoCSim/Objects/Flow.h"
#include "NoCSim/Objects/Flit.h"

namespace NoCSim {

  class Router
  {
  public:
    Router(uint32_t routerID);
    ~Router() = default;

    void AddFlow(const Ref<Flow>& flow) { m_Flows.push_back(flow); }
    void BeginFlows();

    void OnUpdate();

    const uint32_t GetRouterID() const { return m_RouterID; }
  private:
    uint32_t m_RouterID;
    std::vector<Ref<Flow>> m_Flows;

    std::vector<Ref<Flit>> m_OutputBuffer;
    std::vector<Ref<Flit>> m_InputBuffer;
    std::vector<Ref<Flit>> m_ToNodeBuffer;
  };

}
