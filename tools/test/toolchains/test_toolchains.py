#!/usr/bin/env python3
# Copyright (c) 2019 Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: Apache-2.0

"""Test the arm toolchain."""

import os
import sys

import mock


ROOT = os.path.abspath(
    os.path.join(os.path.dirname(__file__), "..", "..", "..")
)
sys.path.insert(0, ROOT)

from tools.toolchains.arm import ARM_STD, ARM_MICRO, ARMC6
from tools.toolchains.gcc import GCC_ARM
from tools.toolchains.iar import IAR


class TestArmToolchain:
    """Test Arm classes."""

    def test_arm_minimal_printf(self):
        """Test that linker flags are correctly added to an instance of ARM."""
        mock_target = mock.MagicMock()
        mock_target.core = "Cortex-M4"
        mock_target.printf_lib = "minimal-printf"
        mock_target.supported_toolchains = ["ARM", "uARM", "ARMC5"]

        arm_std_obj = ARM_STD(mock_target)
        arm_micro_obj = ARM_MICRO(mock_target)
        arm_c6_obj = ARMC6(mock_target)

        assert "-DMBED_MINIMAL_PRINTF" in arm_std_obj.flags["common"]
        assert "-DMBED_MINIMAL_PRINTF" in arm_micro_obj.flags["common"]
        assert "-DMBED_MINIMAL_PRINTF" in arm_c6_obj.flags["common"]


class TestGccToolchain:
    """Test the GCC class."""

    def test_gcc_minimal_printf(self):
        """Test that linker flags are correctly added to an instance of GCC_ARM."""
        mock_target = mock.MagicMock()
        mock_target.core = "Cortex-M4"
        mock_target.printf_lib = "minimal-printf"
        mock_target.supported_toolchains = ["GCC_ARM"]
        mock_target.is_TrustZone_secure_target = False

        gcc_obj = GCC_ARM(mock_target)

        assert "-DMBED_MINIMAL_PRINTF" in gcc_obj.flags["common"]

        minimal_printf_wraps = [
            "-Wl,--wrap,printf",
            "-Wl,--wrap,sprintf",
            "-Wl,--wrap,snprintf",
            "-Wl,--wrap,vprintf",
            "-Wl,--wrap,vsprintf",
            "-Wl,--wrap,vsnprintf",
            "-Wl,--wrap,fprintf",
            "-Wl,--wrap,vfprintf",
        ]

        assert all(
            elem in gcc_obj.flags["ld"] for elem in minimal_printf_wraps
        )


class TestIarToolchain:
    """Test the IAR class."""

    def test_iar_minimal_printf(self):
        """Test that linker flags are correctly added to an instance of GCC_ARM."""
        mock_target = mock.MagicMock()
        mock_target.core = "Cortex-M4"
        mock_target.printf_lib = "minimal-printf"
        mock_target.supported_toolchains = ["IAR"]
        mock_target.is_TrustZone_secure_target = False

        iar_obj = IAR(mock_target)

        assert "-DMBED_MINIMAL_PRINTF" in iar_obj.flags["common"]
