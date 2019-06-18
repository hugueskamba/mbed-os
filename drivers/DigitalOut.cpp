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

#include "drivers/DigitalOut.h"

#include "platform/mbed_critical.h"

namespace mbed {

DigitalOut::DigitalOut(PinName pin) : gpio()
{
    // No lock needed in the constructor
    gpio_init_out(&gpio, pin);
}

DigitalOut::DigitalOut(PinName pin, int value) : gpio()
{
    // No lock needed in the constructor
    gpio_init_out_ex(&gpio, pin, value);
}

void DigitalOut::write(int value)
{
    // Thread safe / atomic HAL call
    gpio_write(&gpio, value);
}

int DigitalOut::read()
{
    // Thread safe / atomic HAL call
    return gpio_read(&gpio);
}

int DigitalOut::is_connected()
{
    // Thread safe / atomic HAL call
    return gpio_is_connected(&gpio);
}

DigitalOut &DigitalOut::operator= (int value)
{
    // Underlying write is thread safe
    write(value);
    return *this;
}

DigitalOut &DigitalOut::operator= (DigitalOut &rhs)
{
    core_util_critical_section_enter();
    write(rhs.read());
    core_util_critical_section_exit();
    return *this;
}

DigitalOut::operator int()
{
    // Underlying call is thread safe
    return read();
}

};
