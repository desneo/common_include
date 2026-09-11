#pragma once

/** @file detection_api.h
 * @brief 检测插件接口：内部只保留 init（初始化模型与过滤参数）与
 * detect（单帧检测）。
 */

#include <string>
#include <vector>

#include <Pluma/Pluma.hpp>
#include <opencv2/core.hpp>

#include "basemodel/target.h"

using plane::model::DetectTarget;

namespace plane {

/// 检测插件初始化参数：模型地址、置信度过滤等。
struct DetectConfig {
    std::string model_path;             ///< 模型文件或目录地址
    float confidence_threshold = 0.4F;  ///< 置信度过滤阈值
    float nms_threshold = 0.45F;        ///< 非极大值抑制阈值
    int max_detections = 100;           ///< 单帧最大输出目标数
    int input_width = 640;              ///< 网络输入宽
    int input_height = 640;             ///< 网络输入高
    bool use_gpu = false;               ///< 是否使用加速设备
};

/// 检测插件：只提供 init 与 detect 两个接口。
class DetectionPlugin {
   public:
    virtual ~DetectionPlugin() = default;

    /// 初始化模型与过滤参数；成功返回 true，失败返回 false。
    virtual bool init(const DetectConfig& config) = 0;

    /// 单帧检测：out 输出目标列表（像素框 + 置信度），失败时由 error 说明原因。
    virtual bool detect(const cv::Mat& frame, std::vector<DetectTarget>& out,
                        std::string& error) = 0;
};

PLUMA_PROVIDER_HEADER(DetectionPlugin);

}  // namespace plane
