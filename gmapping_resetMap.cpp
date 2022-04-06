#include <juiz/juiz.h>
#include <juiz/container.h>

#include "gmapping.h"

using namespace juiz;


extern "C" {

    JUIZ_OPERATION  void* gmapping_resetMap() {
        return containerOperationFactory<gmapping>(
            {
              {"typeName", "resetMap"},
              {"defaultArg", {
                  {}
              }},
            },
            [](auto& container, auto arg) -> juiz::Value {
                
                return Value::error("gmapping_resetMap is not implemented yet.");
            }
        );
    }

}
