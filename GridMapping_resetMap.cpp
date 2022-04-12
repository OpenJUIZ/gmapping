#include <juiz/juiz.h>
#include <juiz/container.h>

#include "GridMapping.h"

using namespace juiz;

auto init_ranger(const juiz::Value& arg) {
    const auto name = arg["laserName"].stringValue();
    const auto numLaser = arg["numLaser"].intValue();
    const auto angularResolution = arg["angularResolution"].doubleValue();
    const auto pose = juiz::toPose3D(arg["laesrOffset"]);
    const auto rangeMax = arg["maxRange"].doubleValue();
    return std::make_shared<GMapping::RangeSensor>(
        name.c_str(), 
        numLaser, 
        angularResolution, 
        GMapping::OrientedPoint{pose.position.x, pose.position.y, pose.position.z}, juiz::QuaternionToEulerXYZ(pose.orientation).z, rangeMax);
}

auto init_gridslam_processor(const juiz::Value& arg, const std::shared_ptr<GMapping::RangeSensor>& ranger) {
    auto gridSlamProcessor = std::make_shared<GMapping::GridSlamProcessor>();
    const auto pose = juiz::toPose3D(arg["initialPose"]);
    const auto srr = arg["srr"].doubleValue();
    const auto srt = arg["srt"].doubleValue();
    const auto str = arg["str"].doubleValue();
    const auto stt = arg["stt"].doubleValue();

    const auto linearUpdate = arg["linearUpdate"].doubleValue();
    const auto angularUpdate = arg["angularUpdate"].doubleValue();
    const auto resampleThreshold = arg["resampleThreshold"].doubleValue();

    const auto temporalUpdate = arg["temporalUpdate"].doubleValue();

    const auto particles = arg["particles"].intValue();
    const auto xmin = arg["xmin"].doubleValue();
    const auto ymin = arg["ymin"].doubleValue();
    const auto xmax = arg["xmax"].doubleValue();
    const auto ymax = arg["ymax"].doubleValue();
    const auto delta = arg["delta"].doubleValue();

    const auto llsamplerange = arg["llsamplerange"].doubleValue();
    const auto llsamplestep = arg["llsamplestep"].doubleValue();
    const auto minimumScore = arg["minimumScore"].doubleValue();

	const GMapping::OrientedPoint initialPose = GMapping::OrientedPoint(pose.position.x, pose.position.y, pose.position.z);
	GMapping::SensorMap smap;
	smap.insert(std::make_pair(ranger->getName(), ranger.get()));
	gridSlamProcessor->setSensorMap(smap);
	gridSlamProcessor->setMotionModelParameters(srr, srt, str, stt);
	gridSlamProcessor->setUpdateDistances(linearUpdate, angularUpdate, resampleThreshold);
	gridSlamProcessor->setUpdatePeriod(temporalUpdate);
	gridSlamProcessor->setgenerateMap(false);
	gridSlamProcessor->GridSlamProcessor::init(particles, xmin, ymin, xmax, ymax, delta, initialPose);
	gridSlamProcessor->setllsamplerange(llsamplerange);
	gridSlamProcessor->setllsamplestep(llsamplestep);
	gridSlamProcessor->setminimumScore(minimumScore);
    return gridSlamProcessor;
}



extern "C" {

    JUIZ_OPERATION  void* GridMapping_resetMap() {
        return containerOperationFactory<GridMapping>(
            {

              {"typeName", "resetMap"},
              {"defaultArg", {
                {"srr", 0.1},
                {"srt", 0.2},
                {"str", 0.1},
                {"stt", 0.05},
                {"linearUpdate", 1.0},
                {"angularUpdate", 0.5},
                {"temporalUpdate", -1.0},
                {"resampleThreshold", 0.5},
                {"particles", 30},
                {"xmin", -12},
                {"ymin", -12},
                {"xmax", 12},
                {"ymax", 12},
                {"delta", 0.05},

                {"llsamplerange", 0.01},
                {"llsamplestep", 0.01},
                {"minimumScore", 0.0},
                //{"lasamplerange", 0.005},
                //{"lasamplestep", 0.005},

                  {"laserName", "Laser0"},
                  {"maxRange", 5.0},
                  {"numLaser", 630},
                  {"angularResolution", 240/630},
                  {"laserOffset", {
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
                  }},
                  {"initialPose", {
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
                container.isMapping = false;
                container.rangeSensor = init_ranger(arg);
                container.gridSlamProcessor = init_gridslam_processor(arg, container.rangeSensor);
                return Value(0);
            }
        );
    }

}
