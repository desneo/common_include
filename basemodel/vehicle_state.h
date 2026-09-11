#pragma once

/** @file vehicle_state.h
 * @brief 本机运动状态（供导引/跟踪等插件计算控制量使用）。
 */

#include "geo_types.h"

namespace plane::model {

/// 本机状态快照：地理位置 + 姿态 + 速度。
struct VehicleState {
    GeoPoint geoPos;                  ///< 本机经纬高（height 为相对高度，米）
    double roll_deg = 0.0;            ///< 横滚角（度）
    double pitch_deg = 0.0;           ///< 俯仰角（度）
    double yaw_deg = 0.0;             ///< 偏航角（度）
    double ground_speed_m_s = 0.0;    ///< 水平速度（米/秒）
    double vertical_speed_m_s = 0.0;  ///< 垂直速度（米/秒，向上为正）
};

}  // namespace plane::model

namespace plane {

using VehicleState = model::VehicleState;

}  // namespace plane
