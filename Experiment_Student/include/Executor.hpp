#pragma once
#include <string>

// 实验所有代码都位于命名空间 adas
namespace adas
{
    /* 汽车姿态 */
    struct Pose // Pose描述
    {
        int x;        // x坐标
        int y;        // y坐标
        char heading; // 'N','S','E','W'代表四个方向
    };

    /* 驾驶动作执行器接口 */
    class Executor
    {
    public:
        // Caller should delete *executor when it is no longer needed.
        // 【修改点】：将 const Pose *pose 改为 const Pose &pose，并修正默认参数语法。
        static Executor *NewExecutor(const Pose &pose = Pose{0, 0, 'N'}) noexcept;

    public:
        // 默认构造函数
        Executor(void) = default;
        // 默认虚析构函数
        virtual ~Executor(void) = default;

        // 不允许拷贝
        Executor(const Executor &) = delete;
        // 不允许赋值
        Executor &operator=(const Executor &) = delete;

    public:
        // 查询当前汽车姿态，纯虚函数，留给子类具体实现
        virtual Pose Query(void) const noexcept = 0;
        virtual void Execute(const std::string &commands) noexcept = 0;
        
    };
} // namespace adas