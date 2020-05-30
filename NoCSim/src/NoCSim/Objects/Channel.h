#pragma once

#include "NoCSim/Core/Core.h"

#include "NoCSim/Objects/Router.h"

namespace NoCSim {

  enum ChannelState
  {
    Busy, Free
  };

  class Channel
  {
  public:
    Channel(const Ref<Router>& firstRouter, const std::string& firstPosition, const Ref<Router>& secondRouter, const std::string& secondPosition);
    ~Channel() = default;

    void OnUpdate(float timestep);
    void SetCyclesPerFlit(uint32_t cycles) { m_CyclesDelay = cycles; }

    static Ref<Channel> Create(const Ref<Router>& firstRouter, const std::string& firstPosition, const Ref<Router>& secondRouter, const std::string& secondPosition);
  private:
    Ref<Router> m_FirstRouter, m_SecondRouter;
    std::string m_FirstPosition, m_SecondPosition;
    ChannelState m_ChannelState;
    bool m_FirstToSecond;
    uint32_t m_CyclesDelay, m_CyclesLeft;
  };

}
