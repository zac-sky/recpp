#include "ExecutorImpl.hpp"

#include <new>
#include <memory>
#include <iostream> // 建议添加，用于调试输出 Fast 状态变化等信息

namespace adas
{
    // =========================================================================
    // 公有方法实现
    // =========================================================================

    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : pose(pose)
    {
        // 可以在此处添加构造日志
    }

    Pose ExecutorImpl::Query(void) const noexcept
    {
        return pose;
    }

    /*
     * 静态工厂方法：使用 new (std::nothrow) 确保内存分配失败时返回空指针而非抛出异常。
     */
    Executor *Executor::NewExecutor(const Pose &pose) noexcept
    {
        // 确保 NewExecutor 方法在 Executor 抽象基类中被声明为静态方法
        return new (std::nothrow) ExecutorImpl(pose);
    }

    // =========================================================================
    // 私有动作方法实现
    // =========================================================================

    // 🌟 已有：Move 函数的具体实现
    void ExecutorImpl::Move(void) noexcept
    {
        if (pose.heading == 'E')
        {
            // 在 Fast 状态下，额外移动一次
            pose.x += (isFast() ? 2 : 1);
        }
        else if (pose.heading == 'W')
        {
            pose.x -= (isFast() ? 2 : 1);
        }
        else if (pose.heading == 'N')
        {
            pose.y += (isFast() ? 2 : 1);
        }
        else if (pose.heading == 'S')
        {
            pose.y -= (isFast() ? 2 : 1);
        }
    }

    // 🆕 已有：TurnLeft 函数的具体实现
    void ExecutorImpl::TurnLeft(void) noexcept
    {
        // L 指令：左转
        if (pose.heading == 'E')
        {
            pose.heading = 'N';
        }
        else if (pose.heading == 'N')
        {
            pose.heading = 'W';
        }
        else if (pose.heading == 'W')
        {
            pose.heading = 'S';
        }
        else if (pose.heading == 'S')
        {
            pose.heading = 'E';
        }
    }

    // 🆕 已有：TurnRight 函数的具体实现
    void ExecutorImpl::TurnRight(void) noexcept
    {
        // R 指令：右转
        if (pose.heading == 'E')
        {
            pose.heading = 'S';
        }
        else if (pose.heading == 'S')
        {
            pose.heading = 'W';
        }
        else if (pose.heading == 'W')
        {
            pose.heading = 'N';
        }
        else if (pose.heading == 'N')
        {
            pose.heading = 'E';
        }
    }

    // 🆕 新增：Fast 函数的具体实现
    void ExecutorImpl::Fast(void) noexcept
    {
        // 切换 Fast 状态
        isfast = !isfast;
        // std::cout << "Fast state toggled to: " << (isfast ? "true" : "false") << std::endl;
    }

    // 🆕 新增：isFast 函数的具体实现
    bool ExecutorImpl::isFast(void) const noexcept
    {
        return isfast;
    }

    // =========================================================================
    // Execute 方法实现 (已修正变量名)
    // =========================================================================

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        // 修正：将 'command' 修正为函数参数 'commands'
        for (const auto cmd : commands)
        {
            // ICommand 等嵌套类可以在成员函数内部直接访问，无需 ExecutorImpl:: 限定
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
                cmder->DoOperate(*this);
        }
    }
}