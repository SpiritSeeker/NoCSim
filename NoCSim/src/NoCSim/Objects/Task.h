#pragma once

#include "NoCSim/Core/Core.h"

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

    void OnUpdate();
    void Reset();

    void SetExecutionTime(float executionTime) { m_ExecutionTime = executionTime; m_RemainingExecutionTime = executionTime; }
    void SetTimePeriod(float timePeriod) { m_TimePeriod = timePeriod; }
    void SetTaskPriority(uint32_t taskPriority) { m_TaskPriority = taskPriority; }
    void SetInputVolumes(const std::vector<float>& inputVolumes) { m_InputVolumes = inputVolumes; m_RemainingInput = inputVolumes; }

    const uint32_t GetTaskID() const { return m_TaskID; }
    const float GetExecutionTime() const { return m_ExecutionTime; }
    const float GetTimePeriod() const { return m_TimePeriod; }
    const uint32_t GetTaskPriority() const { return m_TaskPriority; }
    const std::vector<float>& GetInputVolumes() const { return m_InputVolumes; }
    const TaskState GetTaskState() const { return m_TaskState; }

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
  };

}
