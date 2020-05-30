#include "nspch.h"
#include "Node.h"

namespace NoCSim {

  Node::Node(uint32_t nodeID)
    : m_NodeID(nodeID)
  {
    m_Router = CreateRef<Router>(m_NodeID);
  }

  void Node::OnUpdate(float timestep)
  {
    m_Task->OnUpdate(timestep);

    if (m_Task->GetTaskState() == Complete)
    {
      m_Router->BeginFlows();
    }

    m_Router->OnUpdate(timestep);

    if (!m_Router->GetNodeBuffer().empty())
    {
      for (auto flit : m_Router->GetNodeBuffer())
        m_Task->InputFlit(flit);
      m_Router->ClearNodeBuffer();
    }
  }

  Ref<Node> Node::Create(uint32_t nodeID)
  {
    return CreateRef<Node>(nodeID);
  }

}
