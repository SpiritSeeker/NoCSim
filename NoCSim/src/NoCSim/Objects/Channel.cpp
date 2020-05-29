#include "nspch.h"
#include "Channel.h"

namespace NoCSim {

  Channel::Channel(const Ref<Router>& firstRouter, const std::string& firstPosition, const Ref<Router>& secondRouter, const std::string& secondPosition)
    : m_FirstRouter(firstRouter), m_SecondRouter(secondRouter), m_FirstPosition(firstPosition), m_SecondPosition(secondPosition)
  {}

  void Channel::OnUpdate()
  {
    bool firstRouterIsEmpty = m_FirstRouter->GetChannelMap().at(m_FirstPosition).empty();
    bool secondRouterIsEmpty = m_SecondRouter->GetChannelMap().at(m_SecondPosition).empty();

    if (firstRouterIsEmpty && secondRouterIsEmpty)
      return;

    if (!firstRouterIsEmpty && secondRouterIsEmpty)
    {
      auto flit = m_FirstRouter->GetChannelMap().at(m_FirstPosition)[0];
      m_FirstRouter->GetChannelMap().at(m_FirstPosition).erase(m_FirstRouter->GetChannelMap().at(m_FirstPosition).begin());
      m_SecondRouter->ReceiveFlit(flit);
      return;
    }

    if (firstRouterIsEmpty && !secondRouterIsEmpty)
    {
      auto flit = m_SecondRouter->GetChannelMap().at(m_SecondPosition)[0];
      m_SecondRouter->GetChannelMap().at(m_SecondPosition).erase(m_SecondRouter->GetChannelMap().at(m_SecondPosition).begin());
      m_FirstRouter->ReceiveFlit(flit);
      return;
    }

    auto firstFlit = m_FirstRouter->GetChannelMap().at(m_FirstPosition)[0];
    auto secondFlit = m_SecondRouter->GetChannelMap().at(m_SecondPosition)[0];
    if (firstFlit->GetPriority() < secondFlit->GetPriority())
    {
      m_FirstRouter->GetChannelMap().at(m_FirstPosition).erase(m_FirstRouter->GetChannelMap().at(m_FirstPosition).begin());
      m_SecondRouter->ReceiveFlit(firstFlit);
      return;
    }
    m_SecondRouter->GetChannelMap().at(m_SecondPosition).erase(m_SecondRouter->GetChannelMap().at(m_SecondPosition).begin());
    m_FirstRouter->ReceiveFlit(secondFlit);
  }

  Ref<Channel> Channel::Create(const Ref<Router>& firstRouter, const std::string& firstPosition, const Ref<Router>& secondRouter, const std::string& secondPosition)
  {
    return CreateRef<Channel>(firstRouter, firstPosition, secondRouter, secondPosition);
  }

}
