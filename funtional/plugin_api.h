#pragma once

/** @file plugin_api.h
 * @brief 视觉插件 ABI：能力声明与异常隔离。
 */

#include <string>
#include <vector>

#include <Pluma/Pluma.hpp>
#include <opencv2/core.hpp>

#include "basemodel/target.h"

namespace plane::targethandler {

struct Detection {
    std::string id;
    std::string typeCode;
    double confidence = 0.0;
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
};

class VisionPlugin {
   public:
    virtual ~VisionPlugin() = default;
    virtual unsigned int abiVersion() const = 0;
    virtual std::string name() const = 0;
    virtual std::string capability() const = 0;
    virtual bool infer(const cv::Mat& frame, std::vector<Detection>& out, std::string& error) = 0;
};

PLUMA_PROVIDER_HEADER(VisionPlugin);

// Expected ABI version of the vision plugin interface. Plugins reporting a
// different abiVersion() are rejected and isolated at load time.
constexpr unsigned int kVisionPluginAbiVersion = 1;

}  // namespace plane::targethandler
