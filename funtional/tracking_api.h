#pragma once

/** @file tracking_api.h
 * @brief 单目标跟踪插件接口：内部只保留 init（初始化）与
 * track（输出最新目标位置）。
 */

#include <string>

#include <Pluma/Pluma.hpp>
#include <opencv2/core.hpp>

#include "basemodel/target.h"

using plane::model::DetectTarget;

namespace plane {

/// 单目标跟踪插件初始化参数。
struct TrackConfig {
    std::string model_path;             ///< 跟踪模型/特征文件地址
    float confidence_threshold = 0.4F;  ///< 置信度过滤阈值
    int lost_frame_limit = 30;          ///< 连续丢失帧数上限（超过判定目标丢失）
    int search_radius = 64;             ///< 局部搜索半径（像素）
};

/// 单目标跟踪插件：只提供 init 与 track 两个接口。
class TrackingPlugin {
   public:
    virtual ~TrackingPlugin() = default;

    /// 初始化跟踪模型与参数；成功返回 true，失败返回 false。
    virtual bool init(const TrackConfig& config) = 0;

    /// 单帧跟踪：target 输出最新目标位置信息（像素框 +
    /// 置信度，地理坐标由宿主按需补全）； 目标暂时丢失时返回 false 并由 error
    /// 说明原因，此时 target 保留最后已知位置。
    virtual bool track(const cv::Mat& frame, DetectTarget& target, std::string& error) = 0;
};

PLUMA_PROVIDER_HEADER(TrackingPlugin);

}  // namespace plane
