#pragma once
#include "ExecutorImpl.hpp"

namespace adas{
    // 定义一个虚基类ICommand，完成DoOperate动作
    class ICommand
    {
    public:
        virtual void DoOperate(ExecutorImpl &executor) const noexcept = 0;
        virtual ~ICommand() noexcept = default;
    };
    // 定义一个嵌套类MoveCommand，完成Move动作
    class MoveCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl &executor) const noexcept override
        {
            // 正确：只需要调用一次 Move()
            // Move() 方法会根据 isFast() 的状态来移动 1 步或 2 步。
            executor.Move();
        }
    };
    // 定义一个嵌套类TurnLeftCommand，完成TurnLeft动作
    // 定义一个嵌套类TurnLeftCommand，完成TurnLeft动作
    class TurnLeftCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl &executor) const noexcept override
        {
            if (executor.isFast())        // 检查是否处于 Fast 状态
                executor.MoveByOneStep(); // 🆕 预期在这里调用移动1步的私有方法

            executor.TurnLeft();
        }
    };
    // 定义一个嵌套类TurnRightCommand，完成TurnRight动作
    // 定义一个嵌套类TurnRightCommand，完成TurnRight动作
    class TurnRightCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl &executor) const noexcept override
        {
            if (executor.isFast())        // 检查是否处于 Fast 状态
                executor.MoveByOneStep(); // 🆕 预期在这里调用移动1步的私有方法

            executor.TurnRight();
        }
    };

    // 定义一个嵌套类FastCommand，完成Fast动作
    class FastCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl &executor) const noexcept override
        {
            executor.Fast();
        }
    };
}