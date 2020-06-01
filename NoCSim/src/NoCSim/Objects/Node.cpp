#include "nspch.h"
#include "Node.h"

namespace NoCSim {

  Node::Node(uint32_t nodeID)
    : m_NodeID(nodeID)
  {
    m_Router = CreateRef<Router>(m_NodeID);
    m_TotalTasks = 0;
    m_CompletedTasks = 0;
  }

  void Node::OnUpdate(float timestep)
  {
    m_Task->OnUpdate(timestep);

    if (m_Task->GetTaskState() == Complete)
    {
      m_Router->BeginFlows(m_Task->GetIteration());
    }

    m_Router->OnUpdate(timestep);

    if (!m_Router->GetNodeBuffer().empty())
    {
      for (auto flit : m_Router->GetNodeBuffer())
        m_Task->InputFlit(flit);
      m_Router->ClearNodeBuffer();
    }

    if (!m_Task->GetDeadlinesVector().empty())
    {
      m_TotalTasks++;
      if (m_Task->GetDeadlinesVector()[0])
        m_CompletedTasks++;
      m_Task->GetDeadlinesVector().clear();
    }
  }

  Ref<Node> Node::Create(uint32_t nodeID)
  {
    return CreateRef<Node>(nodeID);
  }

}
