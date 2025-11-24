// Commands.hpp

#pragma once

#include "ICommand.hpp"
#include "ExecutorImpl.hpp" // 需要包含 ExecutorImpl.hpp 来让命令对象能够操作 ExecutorImpl

namespace adas
{
    // --- 1. Move 命令 ---
    // final 关键字表示这个类不能被进一步继承
    class MoveCommand final : public ICommand
    {
    public:
        // override 确保我们正确地实现了基类 ICommand 的纯虚函数
        void Execute(ExecutorImpl &executor) override
        {
            // 移动命令的执行，只需要调用 ExecutorImpl 里封装好的 Move() 方法
            executor.Move();
        }
    };

    // --- 2. TurnLeft 命令 ---
    class TurnLeftCommand final : public ICommand
    {
    public:
        void Execute(ExecutorImpl &executor) override
        {
            // 左转命令的执行，只需要调用 ExecutorImpl 里封装好的 TurnLeft() 方法
            executor.TurnLeft();
        }
    };


} // namespace adas