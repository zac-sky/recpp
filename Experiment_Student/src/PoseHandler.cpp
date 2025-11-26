// src/PoseHandler.cpp

#include "PoseHandler.hpp"
#include <iostream>

namespace adas
{

    // 构造函数
    PoseHandler::PoseHandler(const Pose &initialPose) noexcept : pose(initialPose)
    {
        // 构造日志等
    }

    // 查询当前位置
    Pose PoseHandler::Query(void) const noexcept
    {
        return pose;
    }

    // 检查是否处于快速状态
    bool PoseHandler::IsFast(void) const noexcept
    {
        return isfast;
    }

    // 切换 Fast 状态
    void PoseHandler::Fast(void) noexcept
    {
        // 切换 Fast 状态
        isfast = !isfast;
        // 可选：调试输出
        // std::cout << "Fast state toggled to: " << (isfast ? "true" : "false") << std::endl;
    }

    // 强制移动 1 步 (用于 TurnLeft/TurnRight)
    void PoseHandler::MoveByOneStep(void) noexcept
    {
        if (pose.heading == 'E')
        {
            pose.x += 1;
        }
        else if (pose.heading == 'W')
        {
            pose.x -= 1;
        }
        else if (pose.heading == 'N')
        {
            pose.y += 1;
        }
        else if (pose.heading == 'S')
        {
            pose.y -= 1;
        }
    }

    // 移动方法
    void PoseHandler::Move(void) noexcept
    {
        // 根据 IsFast() 状态决定移动步数 (1 或 2)
        const int steps = IsFast() ? 2 : 1;

        if (pose.heading == 'E')
        {
            pose.x += steps;
        }
        else if (pose.heading == 'W')
        {
            pose.x -= steps;
        }
        else if (pose.heading == 'N')
        {
            pose.y += steps;
        }
        else if (pose.heading == 'S')
        {
            pose.y -= steps;
        }
    }

    // 左转方法
    void PoseHandler::TurnLeft(void) noexcept
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

    // 右转方法
    void PoseHandler::TurnRight(void) noexcept
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

}