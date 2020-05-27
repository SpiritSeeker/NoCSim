#pragma once

#include "NoCSim/Core/Core.h"

#include "NoCSim/Objects/Node.h"
#include "NoCSim/Objects/Task.h"
#include "NoCSim/Objects/Flow.h"

namespace NoCSim {

  class TaskGraph
  {
  public:
    TaskGraph(const std::unordered_map<std::string, std::string>& filepaths);
    ~TaskGraph() = default;

    void OnUpdate();

    static Ref<TaskGraph> Create(const std::unordered_map<std::string, std::string>& filepaths);
  private:
    std::string ReadFile(const std::string& path);
    std::vector<std::vector<float>> PreProcess(const std::string& gridData);
  private:
    uint32_t m_NetworkSize;
    uint32_t m_Rows, m_Columns;

    std::vector<Ref<Node>> m_Nodes;
    std::vector<Ref<Flow>> m_Flows;
  };

}
