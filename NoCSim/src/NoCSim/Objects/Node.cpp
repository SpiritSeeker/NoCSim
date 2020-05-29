#include "nspch.h"
#include "Node.h"

namespace NoCSim {

  Node::Node(uint32_t nodeID)
    : m_NodeID(nodeID)
  {
    m_Router = CreateRef<Router>(m_NodeID);
  }

  void Node::OnUpdate()
  {
    m_Task->OnUpdate();

    if (m_Task->GetTaskState() == Complete)
    {
      m_Router->BeginFlows();
    }

    m_Router->OnUpdate();
  }

  Ref<Node> Node::Create(uint32_t nodeID)
  {
    return CreateRef<Node>(nodeID);
  }

}
