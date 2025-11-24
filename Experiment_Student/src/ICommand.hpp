// ICommand.hpp

#pragma once

// 前置声明：由于命令需要访问 ExecutorImpl 的内部状态，我们先声明它。
namespace adas
{
    class ExecutorImpl;
}

namespace adas
{
    /*
     * ICommand 接口/抽象基类
     * 定义了所有具体命令类必须实现的操作。
     */
    class ICommand
    {
    public:
        // 虚析构函数是必须的，以确保通过基类指针删除派生类对象时，能够正确调用派生类的析构函数。
        virtual ~ICommand() = default;

        /* * 纯虚函数 Execute：
         * 负责执行具体的指令逻辑。它接受一个 ExecutorImpl 对象的引用，
         * 让命令对象能够操作执行者的内部状态 (Pose)。
         */
        virtual void Execute(ExecutorImpl &executor) = 0;
    };
} // namespace adas