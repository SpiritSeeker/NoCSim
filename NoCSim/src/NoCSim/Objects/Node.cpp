#include "nspch.h"
#include "Node.h"

namespace NoCSim {

  Node::Node(uint32_t nodeID, float routerBufferSize)
    : m_NodeID(nodeID)
  {
    m_Router = CreateRef<Router>(m_NodeID, routerBufferSize);
  }

  Ref<Node> Node::Create(uint32_t nodeID, float routerBufferSize)
  {
    return CreateRef<Node>(nodeID, routerBufferSize);
  }

  void Node::OnUpdate()
  {
    m_Task->OnUpdate();
  }

}
