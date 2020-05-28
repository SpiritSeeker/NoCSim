#pragma once

#include "NoCSim/Core/Core.h"

#include "NoCSim/Objects/Router.h"
#include "NoCSim/Objects/Task.h"
#include "NoCSim/Objects/Flow.h"

namespace NoCSim {

  class Node
  {
  public:
    Node(uint32_t nodeID, float routerBufferSize = 1024.0f);
    ~Node() = default;

    void AssignTask(const Ref<Task>& task) { m_Task = task; }
    void AddFlow(const Ref<Flow>& flow) { m_Flows.push_back(flow); }

    void OnUpdate();

    const uint32_t GetNodeID() const { return m_NodeID; }
    const Ref<Router>& GetRouter() const { return m_Router; }
    const Ref<Task>& GetTask() const { return m_Task; }
    const std::vector<Ref<Flow>>& GetFlows() const { return m_Flows; }

    static Ref<Node> Create(uint32_t nodeID, float routerBufferSize = 1024.0f);
  private:
    uint32_t m_NodeID;
    Ref<Router> m_Router;
    Ref<Task> m_Task;
    std::vector<Ref<Flow>> m_Flows;
  };

}
