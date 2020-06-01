#include "nspch.h"
#include "Task.h"

namespace NoCSim {

  Task::Task(uint32_t taskID)
    : m_TaskID(taskID)
  {
    m_TaskState = Wait;
    m_Iteration = 1;
    m_FlitSize = 1024.0f;
  }

  Task::Task(uint32_t taskID, float executionTime, float timePeriod, uint32_t taskPriority)
    : m_TaskID(taskID), m_ExecutionTime(executionTime), m_TimePeriod(timePeriod), m_TaskPriority(taskPriority)
  {
    m_TaskState = Wait;
    m_RemainingExecutionTime = m_ExecutionTime;
    m_RemainingTime = m_TimePeriod;
    m_Iteration = 1;
    m_FlitSize = 1024.0f;
  }

  void Task::OnUpdate(float timestep)
  {
    if (m_RemainingTime <= 0)
    {
      m_DeadlineMet.push_back(m_TaskState > Execute);
      Reset();
      m_Iteration++;
    }

    if (m_TaskState == Wait)
    {
      float totalRemainingInput = 0.0f;
      for (auto element : m_RemainingInput)
        totalRemainingInput += element;
      if (totalRemainingInput <= 0)
      {
        NS_CORE_TRACE("Executing Task {0}", m_TaskID);
        for (int i = 0; i < m_InputVolumes.size(); i++)
        {
          if (m_AdditionalInputBuffer[i] < m_InputVolumes[i])
            m_RemainingInput[i] = m_InputVolumes[i] - m_AdditionalInputBuffer[i];
          else
          {
            m_RemainingInput[i] = 0;
            float flitVolume = 0.0f;
            while (flitVolume < m_InputVolumes[i])
              flitVolume += m_FlitSize;
            m_AdditionalInputBuffer[i] -= flitVolume;
          }
        }

        m_TaskState = Execute;
      }
    }

    else if (m_TaskState == Execute)
    {
      if (m_RemainingExecutionTime <= 0.0f)
      {
        NS_CORE_INFO("Task {0} complete!", m_TaskID);
        m_TaskState = Complete;
      }
      else
        m_RemainingExecutionTime -= timestep * 0.001f;
    }

    else if (m_TaskState == Complete)
      m_TaskState = Idle;

    m_RemainingTime -= timestep * 0.001f;
  }

  void Task::Reset()
  {
    if (m_TaskState == Wait)
      m_RemainingInput = m_InputVolumes;
    m_TaskState = Wait;
    m_RemainingExecutionTime = m_ExecutionTime;
    m_RemainingTime = m_TimePeriod;
  }

  void Task::InputFlit(const Ref<Flit>& flit)
  {
    if (m_FlitSize != flit->GetFlitSize())
      m_FlitSize = flit->GetFlitSize();
    if (m_Iteration <= flit->GetFlowIteration())
    {
      if (m_RemainingInput[flit->GetTaskID()] > 0)
      {
        m_RemainingInput[flit->GetTaskID()] -= flit->GetFlitSize();
        if (m_RemainingInput[flit->GetTaskID()] < 0)
          NS_CORE_INFO("Flow {0} Complete!", flit->GetFlowID());
      }
      else
        m_AdditionalInputBuffer[flit->GetTaskID()] += flit->GetFlitSize();
    }
  }

  void Task::SetInputVolumes(const std::vector<float>& inputVolumes)
  {
    m_InputVolumes = inputVolumes;
    m_RemainingInput = inputVolumes;
    for (int i = 0; i < m_InputVolumes.size(); i++)
      m_AdditionalInputBuffer.push_back(0);
  }

  Ref<Task> Task::Create(uint32_t taskID)
  {
    return CreateRef<Task>(taskID);
  }

  Ref<Task> Task::Create(uint32_t taskID, float executionTime, float timePeriod, uint32_t taskPriority)
  {
    return CreateRef<Task>(taskID, executionTime, timePeriod, taskPriority);
  }

}
