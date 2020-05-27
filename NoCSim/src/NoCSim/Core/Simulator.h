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

		inline Ref<TaskGraph>& GetTaskGraph() { return m_TaskGraph; }
		inline static Simulator& Get() { return *s_Instance; }
	private:
		Ref<TaskGraph> m_TaskGraph;
		bool m_Running = true;
	private:
		static Simulator* s_Instance;
	};

	Simulator* CreateSimulator() { return new Simulator(); }

}
