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
    void BeginFlows(uint32_t iteration);

    void OnUpdate(float timestep);

    void ReceiveFlit(const Ref<Flit>& flit) { m_InputBuffer.push_back(flit); }

    void ClearNodeBuffer() { m_ToNodeBuffer.clear(); }

    void SetRoutingTable(const std::vector<std::string>& routingTable) { m_RoutingTable = routingTable; }

    const uint32_t GetRouterID() const { return m_RouterID; }
    std::unordered_map<std::string, std::vector<Ref<Flit>>>& GetChannelMap() { return m_ToChannel; }
    const std::vector<Ref<Flit>> GetNodeBuffer() const { return m_ToNodeBuffer; }
  private:
    uint32_t m_RouterID;
    std::vector<Ref<Flow>> m_Flows;

    std::vector<Ref<Flit>> m_OutputBuffer;
    std::vector<Ref<Flit>> m_InputBuffer;
    std::vector<Ref<Flit>> m_ToNodeBuffer;
    std::vector<std::string> m_RoutingTable;

    std::unordered_map<std::string, std::vector<Ref<Flit>>> m_ToChannel;
  };

}
