#include "ExecutorImpl.hpp"

#include <new>

namespace adas
{
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : pose(pose) {}

    Pose ExecutorImpl::Query(void) const noexcept
    {
        return pose;
    }

    /*
        std::nothrow 是 C++ 标准库中的一个常量，用于指示在分配内存时不抛出任何异常。
        它是 std::nothrow_t 的实例，通常用在 new 运算符和 std::nothrow 命名空间中，
        以请求内存分配在分配失败时返回一个空指针，而不是抛出 std::bad_alloc 异常。
    */
    Executor *Executor::NewExecutor(const Pose &pose) noexcept
    {
        return new (std::nothrow) ExecutorImpl(pose); // 只在C++17下有效
    }

    // 🌟 已有：Move 函数的具体实现
    void ExecutorImpl::Move(void) noexcept
    {
        if (pose.heading == 'E')
        {
            ++pose.x;
        }
        else if (pose.heading == 'W')
        {
            --pose.x;
        }
        else if (pose.heading == 'N')
        {
            ++pose.y;
        }
        else if (pose.heading == 'S')
        {
            --pose.y;
        }
    }

    // 🆕 新增：TurnLeft 函数的具体实现
   /* void ExecutorImpl::TurnLeft(void) noexcept
    {
        // L 指令：左转
        if (pose.heading == 'E') // 东 (E) 左转到 北 (N)
        {
            pose.heading = 'N';
        }
        else if (pose.heading == 'N') // 北 (N) 左转到 西 (W)
        {
            pose.heading = 'W';
        }
        else if (pose.heading == 'W') // 西 (W) 左转到 南 (S)
        {
            pose.heading = 'S';
        }
        else if (pose.heading == 'S') // 南 (S) 左转到 东 (E)
        {
            pose.heading = 'E';
        }
    }*/

    // 🆕 新增：TurnRight 函数的具体实现
    void ExecutorImpl::TurnRight(void) noexcept
    {
        // R 指令：右转
        if (pose.heading == 'E') // 东 (E) 右转到 南 (S)
        {
            pose.heading = 'S';
        }
        else if (pose.heading == 'S') // 南 (S) 右转到 西 (W)
        {
            pose.heading = 'W';
        }
        else if (pose.heading == 'W') // 西 (W) 右转到 北 (N)
        {
            pose.heading = 'N';
        }
        else if (pose.heading == 'N') // 北 (N) 右转到 东 (E)
        {
            pose.heading = 'E';
        }
    }

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        // 遍历commands里面的每个指令cmd
        for (const auto cmd : commands)
        {
            // 如果是'M'指令
            if (cmd == 'M')
            {
                Move(); // 封装后的调用
            }
            else if (cmd == 'L')
            {
                TurnLeft(); // 封装后的调用
            }
            else if (cmd == 'R')
            {
                TurnRight(); // 封装后的调用
            }
        }
    }
}