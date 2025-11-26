// Command.hpp (最终修正版 - 对应 PPT image_682f72.png)

#pragma once
#include "PoseHandler.hpp" // 🆕 依赖 PoseHandler，而不是 ExecutorImpl

namespace adas
{
    // 定义一个虚基类ICommand，完成DoOperate动作
    class ICommand
    {
    public:
        // 🆕 核心修改：签名改为接受 PoseHandler 引用
        virtual void DoOperate(PoseHandler &poseHandler) const noexcept = 0;
        virtual ~ICommand() noexcept = default;
    };

    // 定义一个嵌套类MoveCommand，完成Move动作
    class MoveCommand final : public ICommand
    {
    public:
        void DoOperate(PoseHandler &poseHandler) const noexcept override
        {
            // 修正：直接调用 PoseHandler 的方法
            poseHandler.Move();
        }
    };

    // 定义一个嵌套类TurnLeftCommand，完成TurnLeft动作
    class TurnLeftCommand final : public ICommand
    {
    public:
        void DoOperate(PoseHandler &poseHandler) const noexcept override
        {
            if (poseHandler.IsFast())        // 修正：调用 PoseHandler::IsFast()
                poseHandler.MoveByOneStep(); // 修正：调用 PoseHandler::MoveByOneStep()

            poseHandler.TurnLeft(); // 修正：调用 PoseHandler::TurnLeft()
        }
    };

    // 定义一个嵌套类TurnRightCommand，完成TurnRight动作
    class TurnRightCommand final : public ICommand
    {
    public:
        void DoOperate(PoseHandler &poseHandler) const noexcept override
        {
            if (poseHandler.IsFast())        // 修正：调用 PoseHandler::IsFast()
                poseHandler.MoveByOneStep(); // 修正：调用 PoseHandler::MoveByOneStep()

            poseHandler.TurnRight(); // 修正：调用 PoseHandler::TurnRight()
        }
    };

    // 定义一个嵌套类FastCommand，完成Fast动作
    class FastCommand final : public ICommand
    {
    public:
        void DoOperate(PoseHandler &poseHandler) const noexcept override
        {
            // 修正：直接调用 PoseHandler 的方法
            poseHandler.Fast();
        }
    };
}