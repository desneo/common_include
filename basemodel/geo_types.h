#pragma once

/** @file geo_types.h
 * @brief 地理与航线基础类型（GeoPoint/Route/TaskArea）。
 */

#include <string>
#include <vector>

namespace plane::model {

struct GeoPoint {
    double latitude = 0.0;
    double longitude = 0.0;
    double height = 0.0;
    double velocity = 0.0;
};

struct Route {
    std::string routeId;
    std::string nodeId;
    std::string type;
    std::vector<GeoPoint> pointList;
};

struct TaskArea {
    std::string id;
    std::string name;
    std::vector<GeoPoint> bounds;
};

}  // namespace plane::model

namespace plane {

using GeoPoint = model::GeoPoint;
using Route = model::Route;
using TaskArea = model::TaskArea;

}  // namespace plane
