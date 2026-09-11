#pragma once

/** @file target.h
 * @brief 观测目标模型。
 */

#include <cstdint>
#include <string>
#include <vector>

#include "geo_types.h"

namespace plane::model {

struct ObservedTarget {
    std::string id;
    std::string typeCode;
    double confidence = 0.0;
    GeoPoint geoPos;
    double pixel_x = 0.0;
    double pixel_y = 0.0;
    double width = 0.0;
    double height = 0.0;
    std::int64_t timestamp_ms = 0;
    std::vector<GeoPoint> trail;
};

}  // namespace plane::model
