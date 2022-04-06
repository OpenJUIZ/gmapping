#include <juiz/juiz.h>
#include <juiz/container.h>

#include "gmapping.h"

using namespace juiz;


extern "C" {

    JUIZ_OPERATION  void* gmapping_startMapping() {
        return containerOperationFactory<gmapping>(
            {
              {"typeName", "startMapping"},
              {"defaultArg", {
                  {}
              }},
            },
            [](auto& container, auto arg) -> juiz::Value {
                
                return Value::error("gmapping_startMapping is not implemented yet.");
            }
        );
    }

}
