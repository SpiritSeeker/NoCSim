#include "nspch.h"
#include "Channel.h"

namespace NoCSim {

  Channel::Channel(const Ref<Router>& firstRouter, const std::string& firstPosition, const Ref<Router>& secondRouter, const std::string& secondPosition)
    : m_FirstRouter(firstRouter), m_SecondRouter(secondRouter), m_FirstPosition(firstPosition), m_SecondPosition(secondPosition)
  {
    m_ChannelState = Free;
    m_CyclesDelay = 4;
  }

  void Channel::OnUpdate(float timestep)
  {
    if (m_ChannelState == Free)
    {
      bool firstRouterIsEmpty = m_FirstRouter->GetChannelMap().at(m_FirstPosition).empty();
      bool secondRouterIsEmpty = m_SecondRouter->GetChannelMap().at(m_SecondPosition).empty();

      if (firstRouterIsEmpty && secondRouterIsEmpty)
        return;

      if (!firstRouterIsEmpty && secondRouterIsEmpty)
      {
        m_FirstToSecond = true;
        m_CyclesLeft = m_CyclesDelay;
        m_ChannelState = Busy;
        return;
      }

      if (firstRouterIsEmpty && !secondRouterIsEmpty)
      {
        m_FirstToSecond = false;
        m_CyclesLeft = m_CyclesDelay;
        m_ChannelState = Busy;
        return;
      }

      auto firstFlit = m_FirstRouter->GetChannelMap().at(m_FirstPosition)[0];
      auto secondFlit = m_SecondRouter->GetChannelMap().at(m_SecondPosition)[0];
      if (firstFlit->GetPriority() < secondFlit->GetPriority())
      {
        m_FirstToSecond = true;
        m_CyclesLeft = m_CyclesDelay;
        m_ChannelState = Busy;
        return;
      }
      m_FirstToSecond = false;
      m_CyclesLeft = m_CyclesDelay;
      m_ChannelState = Busy;
      return;
    }

    if (m_CyclesLeft > 1)
    {
      m_CyclesLeft--;
      return;
    }

    if (m_FirstToSecond)
    {
      auto flit = m_FirstRouter->GetChannelMap().at(m_FirstPosition)[0];
      m_FirstRouter->GetChannelMap().at(m_FirstPosition).erase(m_FirstRouter->GetChannelMap().at(m_FirstPosition).begin());
      m_SecondRouter->ReceiveFlit(flit);
      m_ChannelState = Free;
      return;
    }

    auto flit = m_SecondRouter->GetChannelMap().at(m_SecondPosition)[0];
    m_SecondRouter->GetChannelMap().at(m_SecondPosition).erase(m_SecondRouter->GetChannelMap().at(m_SecondPosition).begin());
    m_FirstRouter->ReceiveFlit(flit);
    m_ChannelState = Free;
  }

  Ref<Channel> Channel::Create(const Ref<Router>& firstRouter, const std::string& firstPosition, const Ref<Router>& secondRouter, const std::string& secondPosition)
  {
    return CreateRef<Channel>(firstRouter, firstPosition, secondRouter, secondPosition);
  }

}
