#pragma once

#include "NoCSim/Core/Core.h"
#include "NoCSim/Objects/Flit.h"

namespace NoCSim {

  enum TaskState
  {
    Wait, Execute, Complete, Idle
  };

  class Task
  {
  public:
    Task(uint32_t taskID);
    Task(uint32_t taskID, float executionTime, float timePeriod, uint32_t taskPriority);
    ~Task() = default;

    void OnUpdate(float timestep);
    void Reset();
    void InputFlit(const Ref<Flit>& flit);

    void SetExecutionTime(float executionTime) { m_ExecutionTime = executionTime; m_RemainingExecutionTime = executionTime; }
    void SetTimePeriod(float timePeriod) { m_TimePeriod = timePeriod; }
    void SetTaskPriority(uint32_t taskPriority) { m_TaskPriority = taskPriority; }
    void SetInputVolumes(const std::vector<float>& inputVolumes);

    const uint32_t GetTaskID() const { return m_TaskID; }
    const float GetExecutionTime() const { return m_ExecutionTime; }
    const float GetTimePeriod() const { return m_TimePeriod; }
    const uint32_t GetTaskPriority() const { return m_TaskPriority; }
    const std::vector<float>& GetInputVolumes() const { return m_InputVolumes; }
    const TaskState GetTaskState() const { return m_TaskState; }
    const uint32_t GetIteration() const { return m_Iteration; }
    std::vector<bool>& GetDeadlinesVector() { return m_DeadlineMet; }

    static Ref<Task> Create(uint32_t taskID);
    static Ref<Task> Create(uint32_t taskID, float executionTime, float timePeriod, uint32_t taskPriority);
  private:
    // Task parameters
    uint32_t m_TaskID;
    float m_ExecutionTime;
    float m_TimePeriod;
    uint32_t m_TaskPriority;
    std::vector<float> m_InputVolumes;

    TaskState m_TaskState;
    float m_RemainingExecutionTime;
    std::vector<float> m_RemainingInput;

    float m_RemainingTime;
    uint32_t m_Iteration;
    std::vector<bool> m_DeadlineMet;
    float m_FlitSize;
    std::vector<float> m_AdditionalInputBuffer;
  };

}
