#pragma once

#include "NoCSim/Core/Core.h"

#include "NoCSim/Objects/Router.h"

namespace NoCSim {

  class Channel
  {
  public:
    Channel(const Ref<Router>& firstRouter, const std::string& firstPosition, const Ref<Router>& secondRouter, const std::string& secondPosition);
    ~Channel() = default;

    void OnUpdate();

    static Ref<Channel> Create(const Ref<Router>& firstRouter, const std::string& firstPosition, const Ref<Router>& secondRouter, const std::string& secondPosition);
  private:
    Ref<Router> m_FirstRouter, m_SecondRouter;
    std::string m_FirstPosition, m_SecondPosition;
  };

}
