// src/PoseHandler.hpp

#pragma once

// 假设 Pose 结构体定义在 Executor.hpp 中
#include "Executor.hpp"

namespace adas
{

    class PoseHandler final
    {
    public:
        // 构造函数：初始化姿态
        explicit PoseHandler(const Pose &pose) noexcept;

        // 禁止拷贝构造
        PoseHandler(const PoseHandler &) = delete;
        // 禁止赋值操作
        PoseHandler &operator=(const PoseHandler &) = delete;

        // 默认析构函数
        ~PoseHandler() noexcept = default;

    public:
        // 向前移动 (根据 Fast 状态决定移动 1 步或 2 步)
        void Move(void) noexcept;
        // 向左转
        void TurnLeft(void) noexcept;
        // 向右转
        void TurnRight(void) noexcept;
        // 切换快速模式
        void Fast(void) noexcept;
        // 查询是否处于快速状态
        bool IsFast(void) const noexcept;
        // 查询当前位置和朝向
        Pose Query(void) const noexcept;

        // 强制移动 1 步 (供 TurnLeft/TurnRight 在 Fast 状态下调用)
        void MoveByOneStep(void) noexcept;

    private:
        Pose pose;          // 当前位置和朝向
        bool isfast{false}; // 是否处于快速状态
    };

}