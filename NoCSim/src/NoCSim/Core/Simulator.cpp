#include "nspch.h"
#include "Simulator.h"

namespace NoCSim {

  Simulator* Simulator::s_Instance = nullptr;

  Simulator::Simulator()
  {
    NS_CORE_ASSERT(!s_Instance, "Simulator instance already exists!");
    s_Instance = this;
    NS_CORE_INFO("Simulator instance created!");
  }

  Simulator::~Simulator()
  {}

  void Simulator::Run()
  {
    NS_CORE_TRACE("Simulator running!");
    for (int i = 0; i < 10; i++)
    {
      NS_CORE_WARN("Iteration {0}", i+1);
      m_TaskGraph->OnUpdate();
    }
  }

}
