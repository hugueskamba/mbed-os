/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
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

#include "drivers/MinimalSerial.h"

#if DEVICE_SERIAL

namespace mbed {

MinimalSerial::MinimalSerial(
    PinName tx,
    PinName rx,
    int baud = MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE
) : _serial(), _baud(baud)
{

    init(tx, rx);
}

MinimalSerial::MinimalSerial(
    serial_t &serial_ref,
    bool serial_inited,
    PinName tx,
    PinName rx,
    int baud = MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE
) : _serial(serial_ref), _baud(baud)
{
    if (serial_inited) {
        return;
    }

    init(tx, rx);
}

MinimalSerial::~MinimalSerial()
{
}

void MinimalSerial::init(PinName tx, PinName rx)
{
    serial_init(&_serial, tx, rx);
    serial_baud(&_serial, _baud);
}

void MinimalSerial::baud(int baudrate)
{
    serial_baud(&_serial, baudrate);
    _baud = baudrate;
}

#if DEVICE_SERIAL_FC
void MinimalSerial::set_flow_control(
    Flow type,
    PinName flow1,
    PinName flow2
)
{
    FlowControl flow_type = (FlowControl)type;
    switch (type) {
        case RTS:
            serial_set_flow_control(&_serial, flow_type, flow1, NC);
            break;

        case CTS:
            serial_set_flow_control(&_serial, flow_type, NC, flow1);
            break;

        case RTSCTS:
        case Disabled:
            serial_set_flow_control(&_serial, flow_type, flow1, flow2);
            break;

        default:
            break;
    }
}
#endif // DEVICE_SERIAL_FC

int MinimalSerial::_base_getc()
{
    // Mutex is already held
    return serial_getc(&_serial);
}

int MinimalSerial::_base_putc(int c)
{
    // Mutex is already held
    serial_putc(&_serial, c);
    return c;
}

} // namespace mbed

#endif // DEVICE_SERIAL
