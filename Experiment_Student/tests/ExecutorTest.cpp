#include <gtest/gtest.h>
#include <memory>
#include <tuple>
#include "Executor.hpp"

// 一个测试套件，用第一名字相见

namespace adas
{
    // 重载Pose的==，用于比较两个姿态对象是不是相等
    bool operator==(const Pose &lhs, const Pose &rhs)
    {
        return std::tie(lhs.x, lhs.y, lhs.heading) == std::tie(rhs.x, rhs.y, rhs.heading);
    }

    // 下面两个测试用例，测试静态方法Executor::NewExecutor

    // 测试用例1
    TEST(ExecutorTest, should_return_init_pose_when_without_command)
    {
        // given
        // 给定测试条件

        // 测试条件就是调用Executor的静态方法NewExecutor 返回一个指向Executor对象的智能指针executor, 这样我们就需要不需要去delete了
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'})); // 给了初始姿势

        // when

        // then
        const Pose target{0, 0, 'E'}; // 构造一个姿势对象target, 其内容为{0, 0, 'E'}

        // 既然给executor对象的初始姿势是{0, 0, 'E'}, 那么executor->Query()返回的Executor对象的姿势必须等于target
        // 所以这里断言: executor->Query()返回的Executor对象的姿势必须等于target, 否则测试失败, 说明Executor的实现有问题
        ASSERT_EQ(target, executor->Query()); // ASSERT_EQ内部调用了重载的Pose的==
    }

    // 测试用例2
    TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command)
    {
        // given
        std::unique_ptr<Executor> executor(Executor::NewExecutor()); // 没有给初始姿势

        // when

        // then
        const Pose target{0, 0, 'N'};
        ASSERT_EQ(target, executor->Query());
    }

    // 【修复点】：这个测试用例被移入了 adas 命名空间内部
    TEST(ExecutorTest, should_return_x_plus_1_given_command_is_M_and_facing_is_E)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'})); // 给了初始姿势：当前朝向是E，起点(0, 0)

        // when 调用executor的Execute方法去执行指令
        executor->Execute("M");

        // then
        const Pose target{1, 0, 'E'};         // 如果执行指令正确，新的姿势应该是target：{1, 0, 'E'}
        ASSERT_EQ(target, executor->Query()); // 当指令执行完，executor->Query()返回的汽车姿势应该等于target：{1, 0, 'E'}
    }

// 测试用例4, 测试Execute方法,朝向W,起点(0,0),执行M命令,期望结果为(-1,0,W)
TEST(ExecutorTest, should_return_x_minus_1_given_command_is_M_and_facing_is_W)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

    // when
    executor->Execute("M");

    // then
    const Pose target = {-1, 0, 'W'};
    ASSERT_EQ(executor->Query(), target);
}

// 测试用例5, 测试Execute方法,朝向N,起点(0,0),执行M命令,期望结果为(0,1,N)
TEST(ExecutorTest, should_return_x_plus_1_given_command_is_M_and_facing_is_N)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when
    executor->Execute("M");

    // then
    const Pose target = {0, 1, 'N'};
    ASSERT_EQ(executor->Query(), target);
}

// 测试用例6, 测试Execute方法,朝向S,起点(0,0),执行M命令,期望结果为(0,-1,S)
TEST(ExecutorTest, should_return_x_minus_1_given_command_is_M_and_facing_is_S)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

    // when
    executor->Execute("M");

    // then
    const Pose target = {0, -1, 'S'};
    ASSERT_EQ(executor->Query(), target);
}
} // namespace adas
