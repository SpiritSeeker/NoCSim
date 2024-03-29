#pragma once

#include "NoCSim/Core/Core.h"

#include "NoCSim/Objects/Router.h"
#include "NoCSim/Objects/Task.h"
#include "NoCSim/Objects/Flow.h"

namespace NoCSim {

  class Node
  {
  public:
    Node(uint32_t nodeID);
    ~Node() = default;

    void AssignTask(const Ref<Task>& task) { m_Task = task; }

    void OnUpdate(float timestep);

    const uint32_t GetNodeID() const { return m_NodeID; }
    const Ref<Router>& GetRouter() const { return m_Router; }
    const Ref<Task>& GetTask() const { return m_Task; }
    const uint32_t GetCompletedTasks() const { return m_CompletedTasks; }
    const uint32_t GetTotalTasks() const { return m_TotalTasks; }

    static Ref<Node> Create(uint32_t nodeID);
  private:
    uint32_t m_NodeID;
    Ref<Router> m_Router;
    Ref<Task> m_Task;

    uint32_t m_CompletedTasks;
    uint32_t m_TotalTasks;
  };

}
