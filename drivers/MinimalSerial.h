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
#ifndef MBED_MINIMAL_SERIAL_H
#define MBED_MINIMAL_SERIAL_H

#include "platform/platform.h"

#if DEVICE_SERIAL || defined(DOXYGEN_ONLY)
#include "hal/serial_api.h"
#include "platform/NonCopyable.h"
#include "PinNames.h"

namespace mbed {

/**
 * \defgroup drivers_MinimalSerial MinimalSerial class
 * \ingroup drivers-public-api-uart
 * @{
 */

/** A abstract class for serial port implementations
 */
class MinimalSerial : private NonCopyable<MinimalSerial> {

public:

    enum Flow {
        Disabled = 0,
        RTS,
        CTS,
        RTSCTS
    };

#if DEVICE_SERIAL_FC
    /** Set the flow control type on the serial port
     *
     *  @param type the flow control type (Disabled, RTS, CTS, RTSCTS)
     *  @param flow1 the first flow control pin (RTS for RTS or RTSCTS, CTS for CTS)
     *  @param flow2 the second flow control pin (CTS for RTSCTS)
     */
    void set_flow_control(Flow type, PinName flow1 = NC, PinName flow2 = NC);
#endif // DEVICE_SERIAL_FC

    /** Set the baud rate of the serial port
     *
     *  @param baudrate The baudrate of the serial port.
     */
    void baud(int baudrate);

    /** Write a char to the serial port
     *
     * @param c The char to write
     *
     * @returns The written char
     */
    int putc(int c);

    /** Read a char to the serial port
     *
     * @returns The char read from the serial port
     */
    int getc();

protected:
    MinimalSerial(
        PinName tx,
        PinName rx,
        int baud
    );

    MinimalSerial(
        serial_t &serial_ref,
        bool serial_inited,
        PinName tx,
        PinName rx,
        int baud
    );

    virtual ~MinimalSerial();

    int _base_getc();

    int _base_putc(int c);    

    int _baud;

    serial_t _serial;

#if !defined(DOXYGEN_ONLY)
    /** Acquire exclusive access to this serial port
     */
    virtual void lock(void){};

    /** Release exclusive access to this serial port
     */
    virtual void unlock(void){};
#endif // !defined(DOXYGEN_ONLY)

private:
    void init(PinName tx, PinName rx);
};

/** @}*/

} // namespace mbed

#endif // DEVICE_SERIAL || defined(DOXYGEN_ONLY)

#endif // MBED_MINIMAL_SERIAL_H
