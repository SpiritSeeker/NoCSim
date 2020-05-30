#pragma once

#include "NoCSim/Core/Core.h"

#include "NoCSim/Objects/TaskGraph.h"

namespace  NoCSim {

	class Simulator
	{
	public:
		Simulator();
		virtual ~Simulator();

		void Run();

    void SetTaskGraph(const Ref<TaskGraph>& taskGraph) { m_TaskGraph = taskGraph; }
		void SetClockPeriod_us(float us) { m_Timestep = us; }
		void SetSimulationLimit_s(float sec) { m_SimulationLimit = sec * 1000000; }

		inline Ref<TaskGraph>& GetTaskGraph() { return m_TaskGraph; }
		inline static Simulator& Get() { return *s_Instance; }
	private:
		Ref<TaskGraph> m_TaskGraph;
		bool m_Running = true;
	private:
		static Simulator* s_Instance;
		float m_Timestep;
		double m_SimulationLimit;
		uint64_t m_CycleCounter;
	};

	Simulator* CreateSimulator() { return new Simulator(); }

}
