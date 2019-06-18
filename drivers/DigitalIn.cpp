/* mbed Microcontroller Library
 * Copyright (c) 2006-2019 ARM Limited
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

#include "drivers/DigitalIn.h"

#include "platform/mbed_critical.h"

namespace mbed {

DigitalIn::DigitalIn(PinName pin) : gpio()
{
    // No lock needed in the constructor
    gpio_init_in(&gpio, pin);
}

DigitalIn::DigitalIn(PinName pin, PinMode mode) : gpio()
{
    // No lock needed in the constructor
    gpio_init_in_ex(&gpio, pin, mode);
}

int DigitalIn::read()
{
    // Thread safe / atomic HAL call
    return gpio_read(&gpio);
}

void DigitalIn::mode(PinMode pull)
{
    core_util_critical_section_enter();
    gpio_mode(&gpio, pull);
    core_util_critical_section_exit();
}

int DigitalIn::is_connected()
{
    // Thread safe / atomic HAL call
    return gpio_is_connected(&gpio);
}

DigitalIn::operator int()
{
    // Underlying read is thread safe
    return read();
}

};
