#pragma once

/** @file message_topics.h
 * @brief 跨模块共享的通信主题（消息类型）与 Zenoh 键表达式。
 *
 * 所有主题字符串统一收敛到 common_include，plane 与地面站等模块共用同一份定义，
 * 避免主题字面量散落在各模块中导致收发两侧不一致。
 */

#include <string>

namespace plane::model::topics {

// ---- 下行：地面站 -> 本机 ----
inline constexpr const char* kTask = "plane/task";                     ///< 任务（多节点行为树）
inline constexpr const char* kCommand = "plane/command";               ///< 指令（单动作）
inline constexpr const char* kTaskTerminate = "plane/task_terminate";  ///< 任务终止
inline constexpr const char* kCancel = "plane/cancel";                 ///< 兼容旧键，等价任务终止

// ---- 上行：本机 -> 地面站 / 其他飞机 ----
inline constexpr const char* kTaskRejected = "plane/task_rejected";  ///< 任务被拒
inline constexpr const char* kTaskStatus = "plane/task_status";      ///< 任务状态
inline constexpr const char* kCommandAck = "plane/command_ack";      ///< 指令回执
inline constexpr const char* kSafety = "plane/safety";               ///< 安全降级
inline constexpr const char* kTargets = "plane/targets";             ///< 观测目标
inline constexpr const char* kGuidance = "plane/guidance";           ///< 导引指令
inline constexpr const char* kVehicleState = "plane/state";          ///< 本机状态（广播）
inline constexpr const char* kMessageReceipt = "plane/message_receipt";  ///< 报文送达/参数错误回执
inline constexpr const char* kCommandFailed = "plane/command_failed";    ///< 飞控指令失败通知

}  // namespace plane::model::topics

namespace plane::model::keys {

/// 地面站收件键：swarm/station/<topic>
inline std::string station(const std::string& topic) {
    return "swarm/station/" + topic;
}

/// 全网广播键：swarm/planes/<topic>
inline std::string planes(const std::string& topic) {
    return "swarm/planes/" + topic;
}

/// 指定飞机键：swarm/plane/<plane_id>/<topic>
inline std::string plane(const std::string& plane_id, const std::string& topic) {
    return "swarm/plane/" + plane_id + "/" + topic;
}

/// 查询键：swarm/query/<dest>/<topic>
inline std::string query(const std::string& dest, const std::string& topic) {
    return "swarm/query/" + dest + "/" + topic;
}

}  // namespace plane::model::keys
