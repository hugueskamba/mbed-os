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

#include "drivers/DigitalInOut.h"

#include "platform/mbed_critical.h"

namespace mbed {

DigitalInOut::DigitalInOut(PinName pin) : gpio()
{
    // No lock needed in the constructor
    gpio_init_in(&gpio, pin);
}

DigitalInOut::DigitalInOut(
    PinName pin, PinDirection direction, PinMode mode, int value
) : gpio()
{
    // No lock needed in the constructor
    gpio_init_inout(&gpio, pin, direction, mode, value);
}

void DigitalInOut::write(int value)
{
    // Thread safe / atomic HAL call
    gpio_write(&gpio, value);
}

int DigitalInOut::read()
{
    // Thread safe / atomic HAL call
    return gpio_read(&gpio);
}

void DigitalInOut::output()
{
    core_util_critical_section_enter();
    gpio_dir(&gpio, PIN_OUTPUT);
    core_util_critical_section_exit();
}

void DigitalInOut::input()
{
    core_util_critical_section_enter();
    gpio_dir(&gpio, PIN_INPUT);
    core_util_critical_section_exit();
}

void DigitalInOut::mode(PinMode pull)
{
    core_util_critical_section_enter();
    gpio_mode(&gpio, pull);
    core_util_critical_section_exit();
}

int DigitalInOut::is_connected()
{
    // Thread safe / atomic HAL call
    return gpio_is_connected(&gpio);
}

DigitalInOut &DigitalInOut::operator= (int value)
{
    // Underlying write is thread safe
    write(value);
    return *this;
}

DigitalInOut &DigitalInOut::operator= (DigitalInOut &rhs)
{
    core_util_critical_section_enter();
    write(rhs.read());
    core_util_critical_section_exit();
    return *this;
}

DigitalInOut::operator int()
{
    // Underlying call is thread safe
    return read();
}

};
