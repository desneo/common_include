#pragma once

/** @file guidance_api.h
 * @brief 图像导引插件接口：内部只保留 init（初始化）与 guide（目标 + 本机状态 ->
 * 北东地速度）。
 */

#include <memory>
#include <string>

#include <Pluma/Pluma.hpp>

#include "basemodel/target.h"
#include "basemodel/vehicle_state.h"
#include "shared_resource_api.h"

using plane::model::DetectTarget;
using plane::model::VehicleState;

namespace plane {

/// 图像导引插件初始化参数。
struct GuidanceConfig {
    double desired_distance_m = 10.0;  ///< 期望保持的跟踪距离（米）
    double max_speed_m_s = 5.0;        ///< 速度限幅（米/秒）
    double max_yaw_rate_deg_s = 30.0;  ///< 偏航角速度限幅（度/秒）
    double kp = 0.8;                   ///< 比例增益
    double kd = 0.1;                   ///< 微分增益
    bool enable_yaw = true;            ///< 是否输出偏航控制量
    std::shared_ptr<SharedResource> shared_resource;  ///< 宿主注入的共享资源（可空）
};

/// 发送给飞控的北东地速度指令。
struct NedVelocity {
    double north_m_s = 0.0;
    double east_m_s = 0.0;
    double down_m_s = 0.0;
    double yaw_deg = 0.0;
    double yaw_rate_deg_s = 0.0;
};

/// 图像导引插件：只提供 init 与 guide 两个接口。
class GuidancePlugin {
   public:
    virtual ~GuidancePlugin() = default;

    /// 初始化导引参数；成功返回 true，失败返回 false。
    virtual bool init(const GuidanceConfig& config) = 0;

    /// 输入目标与本机状态，out 输出要发送给飞控的北东地速度；失败时由 error 说明原因。
    virtual bool guide(const DetectTarget& target, const VehicleState& ego, NedVelocity& out,
                       std::string& error) = 0;
};

PLUMA_PROVIDER_HEADER(GuidancePlugin);

}  // namespace plane
