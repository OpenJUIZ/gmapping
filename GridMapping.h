#pragma once
/**
 * @file GridMapping.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date $DATE
 * 
 * @copyright Copyright (c) 2022
 */


#include "gmapping/gridfastslam/gridslamprocessor.h"// gridfastslam/gridslamprocessor.h>
#include "gmapping/sensor/sensor_base/sensor.h"

/**
 * @brief 
 * 
 */
struct GridMapping {


	std::shared_ptr<GMapping::GridSlamProcessor> gridSlamProcessor;

	std::shared_ptr<GMapping::RangeSensor> rangeSensor;

	std::shared_ptr<GMapping::OdometrySensor> odometrySensor;

    juiz::Value map;

    juiz::Pose3D pose;

    bool isMapping;

    /**
     * @brief Construct a new gmapping object
     * 
     */
    GridMapping(): isMapping(false), map(juiz::Value::object()) {}
};
