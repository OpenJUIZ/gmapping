#include <juiz/juiz.h>
#include <juiz/container.h>

#include "GridMapping.h"

using namespace juiz;


extern "C" {

    JUIZ_OPERATION  void* GridMapping_getPose() {
        return containerOperationFactory<GridMapping>(
            {
              {"typeName", "getPose"},
              {"defaultArg", {
                  {}
              }},
            },
            [](auto& container, auto arg) -> juiz::Value {
                
                return toValue(container.pose);
            }
        );
    }

}
