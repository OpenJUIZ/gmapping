#include <juiz/juiz.h>
#include <juiz/utils/os.h>
#include <juiz/container.h>

#include "GridMapping.h"

using namespace juiz;

std::optional<std::vector<double>> to_double_vector(const Value& ranges) {
    if (!ranges.isListValue()) {
        logger::error("GMapping_setSensorReading error. Argument ranger/ranges is not list value.");
        return std::nullopt;
    }
    return ranges.const_list_map<double>([](const Value& v) -> double {
        return v.doubleValue();
    });
}

GMapping::OrientedPoint value_to_pose(const Value& poseValue) {
    auto pose = juiz::toPose3D(poseValue);
    return  GMapping::OrientedPoint(pose.position.x, pose.position.y, juiz::QuaternionToEulerXYZ(pose.orientation).z);
}

extern "C" {

    JUIZ_OPERATION  void* GridMapping_setSensorReading() {
        return containerOperationFactory<GridMapping>(
            {
              {"typeName", "setSensorReading"},
              {"defaultArg", {
                  {"ranger", {
                        {"timeStamp", -1},
                        {"minAngle", -2.0944},
                        {"maxAngle", 2.0944},
                        {"maxRange", 5.0},
                        {"minRange", 0.3},
                        {"ranges", Value::list()},
                        {"__TYPE__", "Robotics::LaserScan2D"}
                  }},
                  {"odometry", {
                      {"timeStamp", -1},
                      {"position", {
                          {"x", 0.0},
                          {"y", 0.0},
                          {"z", 0.0}
                      }},
                      {"orientation", {
                          {"x", 0.0},
                          {"y", 0.0},
                          {"z", 0.0},
                          {"w", 1.0}
                      }}
                  }}
              }},
            },
            [](auto& container, auto arg) -> juiz::Value {                
                auto ranges = to_double_vector(arg["ranger"]);
                if (!ranges) {
                    return Value::error(logger::error("GMapping_setSensorReading failed."));
                }
                auto timeStamp = arg["timeStamp"].intValue();
                if (timeStamp < 0) {
                    timeStamp = juiz::getTimeStampNanos();
                }
                if(!container.gridSlamProcessor->processScan(GMapping::RangeReading(ranges->size(), &(ranges.value()[0]), container.rangeSensor.get(), value_to_pose(arg["odometry"]), ((double)timeStamp)/1000000000))) {
                    return Value::error(logger::error("GMapping_setSensorReading, GridSlamProcessor::processScan failed."));
                }
                return Value{0};
            }
        );
    }

}
