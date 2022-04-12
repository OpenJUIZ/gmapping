#include <juiz/juiz.h>
#include <juiz/container.h>

#include "GridMapping.h"

using namespace juiz;


auto init_scan_matcher(const std::shared_ptr<GMapping::RangeSensor>& ranger) {
    auto matcher = std::make_shared<GMapping::ScanMatcher>();

    const auto numLaser = ranger->beams().size();
    const auto angularResolution = ranger->angularResolution();
    const auto minAngle = -0.5*angularResolution*numLaser;
    const auto maxRange = ranger->maxRange();

    double* laser_angles = new double[numLaser];
    double theta = minAngle;
    for(unsigned int i = 0; i < numLaser;i++) {
        laser_angles[i]=theta;
        theta += angularResolution;
    }
    matcher->setLaserParameters(numLaser, laser_angles, ranger->getPose());
    delete[] laser_angles;
    matcher->setlaserMaxRange(maxRange);
    matcher->setusableRange(maxRange);
    matcher->setgenerateMap(true);
    return matcher;
}

auto init_scan_matcher_map(const std::shared_ptr<GMapping::GridSlamProcessor>& gridSlamProcessor) {
    const double xmin = gridSlamProcessor->getxmin();
    const double xmax = gridSlamProcessor->getxmax();
    const double ymin = gridSlamProcessor->getymin();
    const double ymax = gridSlamProcessor->getymax();
    const GMapping::Point center{(xmin + xmax)/2.0, (ymin + ymax)/2.0};
    return std::make_shared<GMapping::ScanMatcherMap>(center, xmin, ymin, xmax, ymax, gridSlamProcessor->getdelta());
}

void registerScans(const std::shared_ptr<GMapping::GridSlamProcessor>& gridSlamProcessor, 
                    const std::shared_ptr<GMapping::ScanMatcher>& scanMatcher,
                    const std::shared_ptr<GMapping::ScanMatcherMap>& smap) {
    auto best = gridSlamProcessor->getParticles()[gridSlamProcessor->getBestParticleIndex()];
    for(auto n = best.node; n; n = n->parent) {
        if(!n->reading) { continue; // Reading is NULL
        }
        scanMatcher->invalidateActiveArea();
        scanMatcher->computeActiveArea(*smap.get(), n->pose, &((*n->reading)[0]));
        scanMatcher->registerScan(*smap.get(), n->pose, &((*n->reading)[0]));
    }
}


extern "C" {

    JUIZ_OPERATION  void* GridMapping_updateMap() {
        return containerOperationFactory<GridMapping>(
            {
              {"typeName", "updateMap"},
              {"defaultArg", {
                  {"occuapncyThreshold", 127}
              }},
            },
            [](auto& container, auto arg) -> juiz::Value {
                
                double occ_thresh = arg["occupancyThreshold"].doubleValue();
                auto scanMatcher = init_scan_matcher(container.rangeSensor);
                auto smap = init_scan_matcher_map(container.gridSlamProcessor);
                registerScans(container.gridSlamProcessor, scanMatcher, smap);

                auto min = smap->map2world(GMapping::IntPoint(0, 0));
                auto max = smap->map2world(GMapping::IntPoint(smap->getMapSizeX(), smap->getMapSizeY()));
                auto width = smap->getMapSizeX();
                auto height = smap->getMapSizeY();
                auto pcells = new std::vector<uint8_t>(width * height);

                std::vector<uint8_t>& cells = *pcells;
                for(int x=0; x < width; x++) {
                    for(int y=0; y < height; y++) {
                        double occ = smap->cell(GMapping::IntPoint{x, y});
                        if(occ < 0) {
                            cells[y * width + x] = 127;
                        } else if(occ > occ_thresh) {
                            cells[y * width + x] = 255;
                        } else {
                            cells[y * width + x] = 0;
                        }
                    }
                }



                container.map = Value{
                    {"config", {
                        {"xmin", min.x}, {"ymin", min.y},
                        {"xmax", max.x}, {"ymax", max.y},
                        {"width", width},
                        {"height", height},
                        {"scale", smap->getResolution()}, // GridSize in meter
                        {"origin", {
                            {"x", min.x},
                            {"y", min.y}
                        }}
                    }},
                    {"cells", Value(pcells)}
                };
                return container.map;
            }
        );
    }

}
