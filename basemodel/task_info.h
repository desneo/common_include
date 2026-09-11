#pragma once

/** @file task_info.h
 * @brief 任务入口模型（taskId/taskCode/targetTrackId）与任务状态。
 */

#include <string>

namespace plane::model {

// 从地面站下发的任务信息
struct TaskInfo {
    std::string taskId;         ///< 任务唯一标识
    std::string taskCode;       ///< 任务代号（行为树白名单键）
    std::string targetTrackId;  ///< 关联的跟踪目标（可空）
};

// 上报给地面站的任务状态信息
struct TaskStatus {
    std::string taskId;
    std::string targetTrackId;
    std::string status;
};

}  // namespace plane::model

namespace plane {
using TaskInfo = model::TaskInfo;
}  // namespace plane
