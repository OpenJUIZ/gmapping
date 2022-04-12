/**
 * @file GridMapping.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date $DATE
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <juiz/juiz.h>
#include <juiz/container.h>

#include "GridMapping.h"

using namespace juiz;

extern "C" {
    /**
     * @brief Create a GridMapping object
     * 
     * @return JUIZ_OPERATION*
     */
    JUIZ_OPERATION  void* createGridMapping() {
        return containerFactory<GridMapping>();
    }

}

