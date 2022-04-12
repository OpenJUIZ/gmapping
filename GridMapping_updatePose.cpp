#include <juiz/juiz.h>
#include <juiz/container.h>

#include "GridMapping.h"

using namespace juiz;


extern "C" {

    JUIZ_OPERATION  void* GridMapping_updatePose() {
        return containerOperationFactory<GridMapping>(
            {
              {"typeName", "updatePose"},
              {"defaultArg", {
                  {}
              }},
            },
            [](auto& container, auto arg) -> juiz::Value {
                auto pose = container.gridSlamProcessor->getParticles()[container.gridSlamProcessor->getBestParticleIndex()].pose;
                container.pose.position.x = pose.x;
                container.pose.position.y = pose.y;
                container.pose.position.z = 0.0;
                container.pose.orientation = juiz::EulerXYZToQuaternion({0, 0, pose.theta});
                return toValue(container.pose);
            }			
        );
    }

}
