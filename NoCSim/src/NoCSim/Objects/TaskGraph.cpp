#include "nspch.h"
#include "TaskGraph.h"

static std::vector<float> LineToVec(const std::string& line)
{
  std::vector<float> result;

  size_t pos = line.find_first_of("\t", 0);
  size_t begin = 0;
  while (pos != std::string::npos)
  {
    std::string num = line.substr(begin, pos - begin);
		result.push_back(std::stof(num));
    begin = line.find_first_not_of("\t", pos);
    pos = line.find_first_of("\t", begin);
  }

  return result;
}

namespace NoCSim {

  // Refactor: Move file reads into Utils
  TaskGraph::TaskGraph(const std::unordered_map<std::string, std::string>& filepaths)
  {
    // Read taskGraph file
    NS_CORE_ASSERT((filepaths.find("taskGraph") != filepaths.end()), "TaskGraph file not specified!");

    NS_CORE_TRACE("Reading TaskGraph file: {0}", filepaths.at("taskGraph"));
    std::string gridData = ReadFile(filepaths.at("taskGraph"));
    auto taskGraphGrid = PreProcess(gridData);

    m_NetworkSize = taskGraphGrid.size();

    std::vector<uint32_t> taskMappingVector;
    std::vector<uint32_t> taskPriorityVector;
    std::vector<float> executionTimeVector;
    std::vector<float> timePeriodVector;
    std::vector<uint32_t> flowPriorityVector;

    // Read mapping file
    std::string mapping = ReadFile(filepaths.at("taskMapping"));
    size_t begin = 0;
    size_t pos = mapping.find_first_of(" ", 0);
    std::string num = mapping.substr(0, pos);
    NS_CORE_ASSERT(std::stoi(num) == m_NetworkSize, "Network size mismatch in mapping file!");

    begin = mapping.find_first_not_of(" ", pos);
    pos = mapping.find_first_of(" ", begin);
    num = mapping.substr(begin, pos - begin);
    m_Rows = std::stoi(num);

    begin = mapping.find_first_not_of(" ", pos);
    pos = mapping.find_first_of(" ", begin);
    num = mapping.substr(begin, pos - begin);
    m_Columns = std::stoi(num);

    begin = mapping.find_first_not_of(" ", pos);
    pos = mapping.find_first_of(" ", begin);
    while (pos != std::string::npos)
    {
      num = mapping.substr(begin, pos - begin);
      taskMappingVector.push_back(std::stoi(num));
      begin = mapping.find_first_not_of(" ", pos);
      pos = mapping.find_first_of(" ", begin);
    }

    // Read taskPriority file
    std::string taskPriority = ReadFile(filepaths.at("taskPriority"));
    begin = 0;
    pos = taskPriority.find_first_of(" ", 0);
    num = taskPriority.substr(0, pos);
    NS_CORE_ASSERT(std::stoi(num) == m_NetworkSize, "This Simulator supports one task per node!");

    begin = taskPriority.find_first_not_of(" ", pos);
    pos = taskPriority.find_first_of(" ", begin);
    while (pos != std::string::npos)
    {
      num = taskPriority.substr(begin, pos - begin);
      taskPriorityVector.push_back(std::stoi(num));
      begin = taskPriority.find_first_not_of(" ", pos);
      pos = taskPriority.find_first_of(" ", begin);
    }

    // Read executionTime file
    std::string executionTime = ReadFile(filepaths.at("executionTime"));
    begin = 0;
    pos = executionTime.find_first_of(" ", 0);
    num = executionTime.substr(0, pos);
    NS_CORE_ASSERT(std::stoi(num) == m_NetworkSize, "This Simulator supports one task per node!");

    begin = executionTime.find_first_not_of(" ", pos);
    pos = executionTime.find_first_of("\t", begin);
    while (pos != std::string::npos)
    {
      num = executionTime.substr(begin, pos - begin);
      executionTimeVector.push_back(std::stof(num));
      begin = executionTime.find_first_not_of("\t", pos);
      pos = executionTime.find_first_of("\t", begin);
    }

    // Read timePeriod file
    std::string timePeriod = ReadFile(filepaths.at("timePeriod"));
    begin = 0;
    pos = timePeriod.find_first_of(" ", 0);
    num = timePeriod.substr(0, pos);
    NS_CORE_ASSERT(std::stoi(num) == m_NetworkSize, "This Simulator supports one task per node!");

    begin = timePeriod.find_first_not_of(" ", pos);
    pos = timePeriod.find_first_of("\t", begin);
    while (pos != std::string::npos)
    {
      num = timePeriod.substr(begin, pos - begin);
      timePeriodVector.push_back(std::stof(num));
      begin = timePeriod.find_first_not_of("\t", pos);
      pos = timePeriod.find_first_of("\t", begin);
    }

    // Read flowPriority file
    std::string flowPriority = ReadFile(filepaths.at("flowPriority"));
    begin = 0;
    pos = flowPriority.find_first_of(" ", 0);
    num = flowPriority.substr(0, pos);

    begin = flowPriority.find_first_not_of(" ", pos);
    pos = flowPriority.find_first_of(" ", begin);
    while (pos != std::string::npos)
    {
      num = flowPriority.substr(begin, pos - begin);
      flowPriorityVector.push_back(std::stoi(num));
      begin = flowPriority.find_first_not_of(" ", pos);
      pos = flowPriority.find_first_of(" ", begin);
    }

    // Create nodes
    std::vector<int> coreMapping(m_NetworkSize, -1);
    for (int index = 0; index < m_NetworkSize; index++)
    {
      auto node = Node::Create(index);
      int posX = index % m_Columns;
      int posY = index / m_Rows;
      std::vector<std::string> routingTable;
      for (int i = 0; i < m_NetworkSize; i++)
      {
        int targetX = i % m_Columns;
        int targetY = i / m_Rows;
        if ((targetX - posX) + (targetY - posY) > 0)
        {
          if ((targetX - posX) - (targetY - posY) > 0)
            routingTable.push_back("Right");
          else
            routingTable.push_back("Bottom");
        }
        else
        {
          if ((targetX - posX) - (targetY - posY) > 0)
            routingTable.push_back("Top");
          else
            routingTable.push_back("Left");
        }
      }
      node->GetRouter()->SetRoutingTable(routingTable);

      uint32_t taskID = taskMappingVector[index];
      coreMapping[taskID] = index;
      auto task = Task::Create(taskID, executionTimeVector[taskID], timePeriodVector[taskID], taskPriorityVector[taskID]);
      std::vector<float> inputVolumes;
      for (int i = 0; i < m_NetworkSize; i++)
        inputVolumes.push_back(taskGraphGrid[i][taskID]);
      task->SetInputVolumes(inputVolumes);

      node->AssignTask(task);
      m_Nodes.push_back(node);
    }

    // Create flows
    uint32_t flowID = 0;
    for (int i = 0; i < m_NetworkSize; i++)
    {
      auto row = taskGraphGrid[i];
      for (int j = 0; j < m_NetworkSize; j++)
      {
        float element = row[j];
        if (element != 0.0f)
        {
          auto flow = Flow::Create(flowID, coreMapping[i], coreMapping[j]);
          flow->SetFlowVolume(element);
          flow->SetFlowPriority(flowPriorityVector[flowID]);
          flow->SetSourceTaskID(i);
          m_Nodes[coreMapping[i]]->GetRouter()->AddFlow(flow);
          flowID++;
        }
      }
    }

    // Create channels
    for (uint32_t i = 0; i < m_Columns; i++)
      for (uint32_t j = 0; j < m_Rows; j++)
      {
        uint32_t location = j * m_Columns + i;
        if (i < m_Columns - 1)
          m_Channels.push_back(Channel::Create(m_Nodes[location]->GetRouter(), "Right", m_Nodes[location + 1]->GetRouter(), "Left"));
        if (j < m_Rows - 1)
          m_Channels.push_back(Channel::Create(m_Nodes[location]->GetRouter(), "Bottom", m_Nodes[location + m_Columns]->GetRouter(), "Top"));
      }
  }

  std::string TaskGraph::ReadFile(const std::string& path)
  {
    std::string result;
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (in)
    {
      in.seekg(0, std::ios::end);
      result.resize(in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&result[0], result.size());
      in.close();
    }

    else
    {
      NS_CORE_ERROR("Could not open file '{0}'", path);
    }

    return result;
  }

  std::vector<std::vector<float>> TaskGraph::PreProcess(const std::string& gridData)
  {
    std::vector<std::vector<float>> taskGraphGrid;

    size_t begin = 0;
    size_t pos = gridData.find_first_of("\n", 0);
    while (pos != std::string::npos)
    {
      std::string line = gridData.substr(begin, pos - begin);
      taskGraphGrid.push_back(LineToVec(line));
      begin = gridData.find_first_not_of("\n", pos);
      pos = gridData.find_first_of("\n", begin);
    }

    return taskGraphGrid;
  }

  void TaskGraph::OnUpdate(float timestep)
  {
    for (Ref<Node>& node : m_Nodes)
      node->OnUpdate(timestep);
    for (Ref<Channel>& channel : m_Channels)
      channel->OnUpdate(timestep);
  }

  Ref<TaskGraph> TaskGraph::Create(const std::unordered_map<std::string, std::string>& filepaths)
  {
    return CreateRef<TaskGraph>(filepaths);
  }

}
