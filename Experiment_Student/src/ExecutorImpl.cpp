// src/ExecutorImpl.cpp

#include "ExecutorImpl.hpp"
#include "Command.hpp"
#include <new>
#include <memory>
#include <iostream>
#include <unordered_map> // 🆕 1. 添加 unordered_map 头文件

namespace adas
{

    // 构造函数：使用传入的 pose 初始化 poseHandler
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : poseHandler(pose)
    {
    }

    // Query：委托给 poseHandler 的 Query 方法
    Pose ExecutorImpl::Query(void) const noexcept
    {
        return poseHandler.Query();
    }

    Executor *Executor::NewExecutor(const Pose &pose) noexcept
    {
        return new (std::nothrow) ExecutorImpl(pose);
    }

    // 🆕 修改后的 Execute 方法：使用表驱动替代 if-else
    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        // 2. 建立指令和对应操作类的映射 (表驱动)
        // Key 是指令字符 (char), Value 是指令对象的智能指针 (unique_ptr)
        std::unordered_map<char, std::unique_ptr<ICommand>> cmderMap;

        // 建立操作 M, L, R, F 的映射关系
        cmderMap.emplace('M', std::make_unique<MoveCommand>());
        cmderMap.emplace('L', std::make_unique<TurnLeftCommand>());
        cmderMap.emplace('R', std::make_unique<TurnRightCommand>());
        cmderMap.emplace('F', std::make_unique<FastCommand>());

        // 3. 遍历指令并执行
        for (const auto cmd : commands)
        {
            // 根据操作查找表驱动
            const auto it = cmderMap.find(cmd);

            // 如果找到表驱动 (it != end)，执行操作对应的指令
            if (it != cmderMap.end())
            {
                // it->second 是 unique_ptr<ICommand>
                // 调用 DoOperate 并传入 poseHandler
                it->second->DoOperate(poseHandler);
            }
        }
    }
}