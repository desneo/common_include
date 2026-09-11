#pragma once

/** @file vehicle_state.h
 * @brief 本机运动状态（供导引/跟踪等插件计算控制量使用）。
 */

#include "geo_types.h"

namespace plane::model {

/// 上报给地面站、其他飞机的状态信息
struct VehicleState {
    GeoPoint geoPos;                  ///< 本机经纬高（height 为相对高度，米）
    double roll_deg = 0.0;            ///< 横滚角（度）
    double pitch_deg = 0.0;           ///< 俯仰角（度）
    double yaw_deg = 0.0;             ///< 偏航角（度）
    float velocity_m_s = 0.0;          ///< 速度（米/秒）
};

}  // namespace plane::model

namespace plane {

using VehicleState = model::VehicleState;

}  // namespace plane
