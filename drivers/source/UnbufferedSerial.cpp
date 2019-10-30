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

#include "hal/serial_api.h"

#include "drivers/UnbufferedSerial.h"


#if DEVICE_SERIAL

namespace mbed {

UnbufferedSerial::UnbufferedSerial(
    PinName tx,
    PinName rx,
    int baud
) : SerialBase(tx, rx, baud)
{
    // No lock needed in the constructor
}

ssize_t UnbufferedSerial::write(const void *buffer, size_t size)
{
    const unsigned char *buf = static_cast<const unsigned char *>(buffer);
    for (size_t i = 0; i < size; i++) {
        serial_putc(&_serial, buf[i]);
    }
    return size;
}

ssize_t UnbufferedSerial::read(void *buffer, size_t size)
{
    unsigned char *buf = static_cast<unsigned char *>(buffer);
    if (size == 0) {
        return 0;
    }
    buf[0] = serial_getc(&_serial);
    return 1;
}

short UnbufferedSerial::poll(short events) const
{
    short revents = 0;
    if ((events & POLLIN) && serial_readable((serial_t*)&_serial)) {
        revents |= POLLIN;
    }
    if ((events & POLLOUT) && serial_writable((serial_t*)&_serial)) {
        revents |= POLLOUT;
    }
    return revents;
}

/** Acquire exclusive access to this serial port
 */
void UnbufferedSerial::lock()
{
    // No lock used - external synchronization required
}

/** Release exclusive access to this serial port
 */
void UnbufferedSerial::unlock()
{
    // No lock used - external synchronization required
}

} // namespace mbed

#endif // #if DEVICE_SERIAL
