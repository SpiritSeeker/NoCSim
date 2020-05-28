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

    if (m_Task->GetTaskState() == Complete)
    {
      for (auto flow : m_Flows)
      {
        NS_CORE_TRACE("Begining Flow {0}: From Node {1} to Node {2}!", flow->GetFlowID(), flow->GetSourceCoreID(), flow->GetDestinationCoreID());
        flow->SetFlowState(FlowTransmit);
        m_Router->AddFlow(flow);
      }
    }
  }

}
