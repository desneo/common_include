#pragma once

/** @file target.h
 * @brief 观测目标模型。
 */

#include <cstdint>
#include <string>
#include <vector>

#include "geo_types.h"

namespace plane::model {

struct DetectTarget {
    std::string id;
    std::string trackId;
    float confidence = 0.0;
    GeoPoint geoPos;
    int cx = 0;
    int cy = 0;
    int width = 0;
    int height = 0;
    std::int64_t timestamp_ms = 0;
    std::vector<GeoPoint> trail;
};

}  // namespace plane::model
