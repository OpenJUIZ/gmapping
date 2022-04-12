#include <juiz/juiz.h>
#include <juiz/container.h>

#include "GridMapping.h"

using namespace juiz;


extern "C" {

    JUIZ_OPERATION  void* GridMapping_getMap() {
        return containerOperationFactory<GridMapping>(
            {
              {"typeName", "getMap"},
              {"defaultArg", {
                  {}
              }},
            },
            [](auto& container, auto arg) -> juiz::Value {
                
                return container.map;
            }
        );
    }

}
