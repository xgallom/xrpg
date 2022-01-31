//
// Created by gallo on 24-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ENGINE_TASK_H
#define XRPG_XRPG_SHARED_INCLUDE_ENGINE_TASK_H

#include "engine-run-state.h"

namespace engine {
    namespace TaskId {
        enum Enum : uint32_t {
            Start,
            Quit,
        };
    }

    struct EmptyTask {
    };

    template<TaskId::Enum Id>
    struct TaskData : EmptyTask {
    };

    template<TaskId::Enum Id>
    struct Task : TaskData<Id> {
        static constexpr auto id = Id;
        using TaskData = ::engine::TaskData<Id>;
        static constexpr auto hasData = std::is_base_of_v<EmptyTask, TaskData>;
        using TaskHandler = std::conditional_t<
                hasData,
                RunHandler<>,
                RunHandler<const TaskData &>
        >;
    };

    template<typename I,
            typename Task = typename I::value_type,
            typename TaskHandler = typename Task::TaskHandler>
    void runTask(I begin, I end, TaskHandler taskHandler, EngineRunState &engine)
    {
        if constexpr (Task::hasData) {
            for (; begin != end; ++begin)
                (engine.*taskHandler)(*begin);
        } else {
            for (; begin != end; ++begin)
                (engine.*taskHandler)();
        }
    }

    template<TaskId::Enum Id>
    struct TaskContainer {
        using Task = ::engine::Task<Id>;
        using TaskHandler = typename Task::TaskHandler;

        std::vector<Task> tasks;

        [[nodiscard]] inline bool empty() const { return tasks.empty(); }
        [[nodiscard]] inline bool exists() const { return !tasks.empty(); }

        inline void run(TaskHandler taskHandler, EngineRunState &engine)
        {
            runTask(tasks.cbegin(), tasks.cend(), taskHandler, engine);
            tasks.clear();
        }
    };

    struct TaskScheduler : EngineRunState {
        TaskContainer<TaskId::Start> start;
        TaskContainer<TaskId::Quit> quit;
    };
}

#endif //XRPG_XRPG_SHARED_INCLUDE_ENGINE_TASK_H
