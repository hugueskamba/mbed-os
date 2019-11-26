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

#include "drivers/UnbufferedSerial.h"

#if DEVICE_SERIAL

#include "platform/mbed_critical.h"

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

    if (size == 0) {
        return 0;
    }

    bool lock_api = !core_util_in_critical_section();

    if (lock_api) {
        api_lock();
    }

    for (size_t i = 0; i < size; i++) {
        _base_putc(buf[i]);
    }

    if (lock_api) {
        api_unlock();
    }

    return size;
}

ssize_t UnbufferedSerial::read(void *buffer, size_t size)
{
    unsigned char *buf = static_cast<unsigned char *>(buffer);
    if (size == 0) {
        return 0;
    }
    buf[0] = _base_getc();
    return 1;
}

short UnbufferedSerial::poll(short events)
{
    short revents = 0;
    if ((events & POLLIN) && SerialBase::readable()) {
        revents |= POLLIN;
    }
    if ((events & POLLOUT) && SerialBase::writeable()) {
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

void UnbufferedSerial::api_lock(void)
{
    _mutex.lock();
}

void UnbufferedSerial::api_unlock(void)
{
    _mutex.unlock();
}

} // namespace mbed

#endif // #if DEVICE_SERIAL
