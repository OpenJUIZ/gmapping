#include <juiz/juiz.h>
#include <juiz/container.h>

#include "gmapping.h"

using namespace juiz;


extern "C" {

    JUIZ_OPERATION  void* gmapping_stopMapping() {
        return containerOperationFactory<gmapping>(
            {
              {"typeName", "stopMapping"},
              {"defaultArg", {
                  {}
              }},
            },
            [](auto& container, auto arg) -> juiz::Value {
                
                return Value::error("gmapping_stopMapping is not implemented yet.");
            }
        );
    }

}
