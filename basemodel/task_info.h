#pragma once

/** @file task_info.h
 * @brief 任务入口模型（taskId/taskCode）。
 */

#include <string>

namespace plane::model {

struct TaskInfo {
    std::string taskId;
    std::string taskCode;
};

}  // namespace plane::model

namespace plane {
using TaskInfo = model::TaskInfo;
}  // namespace plane
