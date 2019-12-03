/* mbed Microcontroller Library
 * Copyright (c) 2015-2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_CIRCULARBUFFER_H
#define MBED_CIRCULARBUFFER_H

#include <stdint.h>

#include "platform/CircularBufferBase.h"

namespace mbed {

/** \addtogroup platform-public-api */
/** @{*/

/**
 * \defgroup platform_CircularBuffer CircularBuffer class
 * \ingroup platform-public-api-circular-buffer
 * @{
 */

/** Templated Circular buffer class
 *
 *  @note Synchronization level: Interrupt safe
 *  @note CounterType must be unsigned and consistent with pool_size
 */
template<typename T, uint32_t pool_size, typename CounterType = uint32_t>
class CircularBuffer : public CircularBufferBase<T> {
public:
    CircularBuffer() : CircularBufferBase<T>(_pool, pool_size)
    {
    }

    ~CircularBuffer()
    {
    }

private:
    T _pool[pool_size];
};

/**@}*/

/**@}*/

}

#endif
