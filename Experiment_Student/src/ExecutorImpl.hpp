// ExecutorImpl.hpp (最终修正版)

#pragma once

#include "Executor.hpp"
#include <string>
#include "PoseHandler.hpp" // 🆕 添加对 PoseHandler 的依赖

namespace adas
{
    /*
        Executor的具体实现
    */
    class ExecutorImpl : public Executor
    {
    public:
        // 构造函数
        explicit ExecutorImpl(const Pose &pose) noexcept;
        // 默认析构函数
        ~ExecutorImpl() noexcept = default;
        // 不能拷贝
        ExecutorImpl(const ExecutorImpl &) = delete;
        // 不能赋值
        ExecutorImpl &operator=(const ExecutorImpl &) = delete;

    public:
        // 查询当前汽车姿态,是父类抽象方法Query的具体实现
        Pose Query(void) const noexcept override;
        // 通过命令执行驾驶动作,是父类抽象方法Execute的具体实现
        void Execute(const std::string &command) noexcept override;

    private:
        // 🆕 包含 PoseHandler 对象，管理状态
        PoseHandler poseHandler;

        // ⚠️ 删除了 pose, isfast, MoveByOneStep, Move, TurnLeft, TurnRight, Fast, isFast 方法和成员
    };
}