#include <NoCSim.h>

int main(int argc, char** argv)
{
	NoCSim::Log::Init();
	NS_CORE_WARN("Initialized NoCSim!");

	NoCSim::Simulator* sim = NoCSim::CreateSimulator();

	std::unordered_map<std::string, std::string> filepaths;
	filepaths["taskGraph"] = "Sandbox/assets/task_graph.txt";
	filepaths["taskMapping"] = "Sandbox/assets/mapping.txt";
	filepaths["taskPriority"] = "Sandbox/assets/task_pri.txt";
	filepaths["executionTime"] = "Sandbox/assets/exe_time.txt";
	filepaths["timePeriod"] = "Sandbox/assets/time_period.txt";
	filepaths["flowPriority"] = "Sandbox/assets/flow_pri.txt";

	NoCSim::Ref<NoCSim::TaskGraph> taskGraph = NoCSim::TaskGraph::Create(filepaths);
	sim->SetTaskGraph(taskGraph);
	sim->SetClockPeriod_us(0.1f);
	sim->SetSimulationLimit_s(1.0f);

	sim->Run();
	delete sim;
	return 0;
}
