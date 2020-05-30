#include "nspch.h"
#include "Simulator.h"

namespace NoCSim {

  Simulator* Simulator::s_Instance = nullptr;

  Simulator::Simulator()
  {
    NS_CORE_ASSERT(!s_Instance, "Simulator instance already exists!");
    s_Instance = this;
    m_Timestep = 0.01f;
    m_SimulationLimit = 1000000.0;
    m_CycleCounter = 0;
    NS_CORE_INFO("Simulator instance created!");
  }

  Simulator::~Simulator()
  {}

  void Simulator::Run()
  {
    NS_CORE_TRACE("Simulator running!");
    while (m_CycleCounter * m_Timestep < m_SimulationLimit)
    {
      m_CycleCounter++;
      double millis = m_CycleCounter * m_Timestep * 0.001;
      if ((uint64_t)(millis) - (millis) == 0)
        NS_CORE_WARN("Time: {0} ms", millis);
      m_TaskGraph->OnUpdate(m_Timestep);
    }
  }

}
