#pragma once

/** @file message_envelope.h
 * @brief 通用消息外壳。
 *
 * 所有进出 Zenoh 的消息都必须封装为该外壳：接收方先读取 @ref type 判定业务类型
 * （取值见 message_topics.h），再把 @ref msg 反序列化为对应的业务结构体，
 * 从而把“传输/寻址”与“业务载荷”解耦，新增业务类型无需改动传输层。
 */

#include <string>

namespace plane::model {

/// 通用通信外壳。msg 以 JSON 文本承载业务载荷，发送方与接收方通过 type 约定其结构。
struct MessageEnvelope {
    std::string type;           ///< 业务消息类型（见 message_topics.h）
    std::string sourceId;       ///< 发送方 ID
    std::string destId;         ///< 目标 ID；空或 "*" 表示广播
    std::string correlationId;  ///< 关联/追踪 ID
    int schemaVersion = 1;      ///< 外壳版本
    std::string msg;            ///< 业务载荷（JSON 文本）
};

}  // namespace plane::model

namespace plane {
using MessageEnvelope = model::MessageEnvelope;
}  // namespace plane
