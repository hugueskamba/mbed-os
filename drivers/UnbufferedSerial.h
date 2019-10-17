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
#ifndef MBED_UNBUFFERED_SERIAL_H
#define MBED_UNBUFFERED_SERIAL_H

#include "platform/platform.h"

#if DEVICE_SERIAL || defined(DOXYGEN_ONLY)

#include "drivers/SerialBase.h"
#include "platform/FileHandle.h"
#include "platform/NonCopyable.h"

namespace mbed {

/**
 * \defgroup drivers_UnbufferedSerial UnbufferedSerial class
 * \ingroup drivers-public-api-uart
 * @{
 */

/**
 * Class implementation for unbuffered I/O for an interrupt driven application
 * or one that needs to have more control.
 */
class UnbufferedSerial:
    public SerialBase,
    public FileHandle,
    private NonCopyable<UnbufferedSerial>
{
public:
    /**
     * Create a serial port instance connected to the specified transmit and
     * receive pins, with the specified baud rate.
     *
     *  @param tx Transmit pin
     *  @param rx Receive pin
     *  @param baud The baud rate of the serial port (optional, defaults to MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE)
     *
     *  @note
     *    Either tx or rx may be specified as NC if unused
     */
    UnbufferedSerial(
        PinName tx,
        PinName rx,
        int baud = MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE
    );

        /** Write a char to the serial port
     *
     * @param c The char to write
     *
     * @returns The written char or -1 if an error occurred
     */
    int putc(int c);

    /** Read a char from the serial port
     *
     * @returns The char read from the serial port
     */
    int getc();

    /** Write a string to the serial port
     *
     * @param str The string to write
     *
     * @returns 0 if the write succeeds, EOF for error
     */
    int puts(const char *str);

    /** Write the contents of a buffer to a file
     *
     *  Follows POSIX semantics:
     *
     * * if blocking, block until all data is written
     * * if no data can be written, and non-blocking set, return -EAGAIN
     * * if some data can be written, and non-blocking set, write partial
     *
     *  @param buffer   The buffer to write from
     *  @param length   The number of bytes to write
     *  @return         The number of bytes written, negative error on failure
     */
    virtual ssize_t write(const void *buffer, size_t size);

    /** Read the contents of a file into a buffer
     *
     *  Follows POSIX semantics:
     *
     *  * if no data is available, and non-blocking set return -EAGAIN
     *  * if no data is available, and blocking set, wait until data is available
     *  * If any data is available, call returns immediately
     *
     *  @param buffer   The buffer to read in to
     *  @param length   The number of bytes to read
     *  @return         The number of bytes read, 0 at end of file, negative error on failure
     */
    virtual ssize_t read(void *buffer, size_t size);

    /** Move the file position to a given offset from from a given location
     *
     * Not valid for a device type FileHandle like UARTSerial.
     * In case of UARTSerial, returns ESPIPE
     *
     *  @param offset   The offset from whence to move to
     *  @param whence   The start of where to seek
     *      SEEK_SET to start from beginning of file,
     *      SEEK_CUR to start from current position in file,
     *      SEEK_END to start from end of file
     *  @return         The new offset of the file, negative error code on failure
     */
    virtual off_t seek(off_t offset, int whence = SEEK_SET)
    {
        return -ESPIPE;
    }

    /** Get the size of the file
     *
     *  @return         Size of the file in bytes
     */
    virtual off_t size()
    {
        return -EINVAL;
    }

    /** Check if the file in an interactive terminal device
     *
     *  @return         True if the file is a terminal
     *  @return         False if the file is not a terminal
     *  @return         Negative error code on failure
     */
    virtual int isatty()
    {
        return true;
    }

    /** Close a file
     *
     *  @return         0 on success, negative error code on failure
     */
    virtual int close()
    {
        return 0;
    }

    /** 
     * Equivalent to POSIX poll(). Derived from FileHandle.
     * Provides a mechanism to multiplex input/output over a set of file
     * handles.
     */
    virtual short poll(short events) const;

#if !(DOXYGEN_ONLY)
protected:
    /* Acquire exclusive access to this serial port
     */
    virtual void lock(void);

    /* Release exclusive access to this serial port
     */
    virtual void unlock(void);
#endif // !(DOXYGEN_ONLY)
};

} // namespace mbed

#endif // DEVICE_SERIAL || defined(DOXYGEN_ONLY)

#endif // MBED_UNBUFFERED_SERIAL_H
