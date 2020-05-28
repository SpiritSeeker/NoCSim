#include "nspch.h"
#include "Task.h"

namespace NoCSim {

  Task::Task(uint32_t taskID)
    : m_TaskID(taskID)
  {
    m_TaskState = Wait;
  }

  Task::Task(uint32_t taskID, float executionTime, float timePeriod, uint32_t taskPriority)
    : m_TaskID(taskID), m_ExecutionTime(executionTime), m_TimePeriod(timePeriod), m_TaskPriority(taskPriority)
  {
    m_TaskState = Wait;
    m_RemainingExecutionTime = m_ExecutionTime;
  }

  Ref<Task> Task::Create(uint32_t taskID)
  {
    return CreateRef<Task>(taskID);
  }

  Ref<Task> Task::Create(uint32_t taskID, float executionTime, float timePeriod, uint32_t taskPriority)
  {
    return CreateRef<Task>(taskID, executionTime, timePeriod, taskPriority);
  }

  void Task::OnUpdate()
  {
    if (m_TaskState == Idle)
      return;

    if (m_TaskState == Wait)
    {
      float totalRemainingInput = 0.0f;
      for (auto element : m_RemainingInput)
        totalRemainingInput += element;
      if (totalRemainingInput == 0)
      {
        NS_CORE_TRACE("Executing Task {0}", m_TaskID);
        m_TaskState = Execute;
      }
      return;
    }

    if (m_TaskState == Execute)
    {
      if (m_RemainingExecutionTime <= 0.0f)
      {
        NS_CORE_INFO("Task {0} complete!", m_TaskID);
        m_TaskState = Complete;
      }
      else
        m_RemainingExecutionTime -= 0.5f; // Change to timestep
      return;
    }

    if (m_TaskState == Complete)
    {
      m_RemainingInput = m_InputVolumes;
      m_TaskState = Idle;
    }
  }

  void Task::Reset()
  {
    m_TaskState = Wait;
    m_RemainingExecutionTime = m_ExecutionTime;
  }

}
