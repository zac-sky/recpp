// ExecutorImpl.cpp (最终修正版)

#include "ExecutorImpl.hpp"
#include "Command.hpp"
#include <new>
#include <memory>
#include <iostream>

namespace adas
{

    // 🆕 构造函数：使用传入的 pose 初始化 poseHandler
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : poseHandler(pose)
    {
        // 可以在此处添加构造日志
    }

    // 🆕 Query：委托给 poseHandler 的 Query 方法
    Pose ExecutorImpl::Query(void) const noexcept
    {
        return poseHandler.Query();
    }

    Executor *Executor::NewExecutor(const Pose &pose) noexcept
    {
        return new (std::nothrow) ExecutorImpl(pose);
    }

    // ⚠️ 删除了 MoveByOneStep, Move, TurnLeft, TurnRight, Fast, isFast 的实现

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        for (const auto cmd : commands)
        {
            std::unique_ptr<ICommand> cmder;

            if (cmd == 'M')
                cmder = std::make_unique<MoveCommand>();
            else if (cmd == 'L')
                cmder = std::make_unique<TurnLeftCommand>();
            else if (cmd == 'R')
                cmder = std::make_unique<TurnRightCommand>();
            else if (cmd == 'F')
                cmder = std::make_unique<FastCommand>();

            if (cmder)
                // 🆕 核心修改：Execute 方法将 PoseHandler 传递给 DoOperate
                cmder->DoOperate(poseHandler); // **注意：这里需要修改 ICommand::DoOperate 的签名**
        }
    }
}