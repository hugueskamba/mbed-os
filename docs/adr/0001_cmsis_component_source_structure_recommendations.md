# CMSIS component source structure recommendations
Date: 2020-08-19

## Status
Proposed

## Context

[`ARM-software/CMSIS_5`](https://github.com/ARM-software/CMSIS_5) has been ported to Mbed OS. However, it is split across multiple directories and it is not immediately obvious that it comes from that directory. It also makes it difficult to create an independent CMake target can be built as a library that can be optionally be added by end users.

The current proposal is to create a new directory `rtos/CMSIS_5/` that will mirror closely the structure used by `ARM-software/CMSIS_5/`. It will result in the removal of `rtos/source/TARGET_CORTEX/` and `cmsis/`.

Additionally it will provide the following advantages:
* Better maintenance of component
* Easy creation of an independent CMake target
* Easy source navigation that mirrors closely the upstream repository


## Decision
The following directory restructure is recommended:

```
+-- rtos/CMSIS_5/
|   +-- README.md
|   +-- docs/
|   +-- CMSIS/
|       +-- include/
|               +-- mbed_cmsis_conf.h   # Currently in cmsis/
|       +-- RTE/
|           +-- include/
|               +-- RTE_Components.h    # Currently in cmsis/
|       +-- RTOS2/
|           +-- Include/
|               +-- A                   # Content of rtos/source/TARGET_CORTEX/rtx5/Include/
|               +-- B                   # Header files currently in rtos/source/TARGET_CORTEX/
|           +-- RTX/
|               +-- Config/
|                   +-- C               # Content of rtos/source/TARGET_CORTEX/rtx5/RTX/Config/
|               +-- Include/
|                   +-- D               # Content of rtos/source/TARGET_CORTEX/rtx5/RTX/Include/
|               +-- Include1/
|                   +-- cmsis_os.h      # Currently in rtos/source/TARGET_CORTEX/rtx4/
|               +-- Library/
|                   +-- cmsis_os1.c     # Currently in rtos/source/TARGET_CORTEX/rtx4/
|               +-- Source/
|                   +-- E               # Content of rtos/source/TARGET_CORTEX/rtx5/RTX/Source/
|           +-- Source/
|               +-- F                   # Content of rtos/source/TARGET_CORTEX/rtx5/Source
|               +-- G                   # Source files currently in rtos/source/TARGET_CORTEX/
|           +-- TOOLCHAIN_ARM_MICRO/    # Currently in rtos/source/TARGET_CORTEX/
|           +-- TOOLCHAIN_ARM_STD/      # Currently in rtos/source/TARGET_CORTEX/
|           +-- TOOLCHAIN_GCC_ARM/      # Currently in rtos/source/TARGET_CORTEX/
|           +-- TOOLCHAIN_IAR/          # Currently in rtos/source/TARGET_CORTEX/
|           +-- mbed_lib.json           # Currently in rtos/source/TARGET_CORTEX/
|       +-- Core_A/
|           +-- Include/
|               +-- H                   # Header files currently in cmsis/TARGET_CORTEX_A/
|           +-- Source/
|               +-- I                   # Source files currently in cmsis/TARGET_CORTEX_A/
|       +-- Core/
|           +-- Include/
|               +-- J                   # Header files currently in cmsis/TARGET_CORTEX_M/
```

However, to cope with Mbed-CLI requirement to find directories to process with the target labels mechanism, some directories will be prefixed with `TARGET_` and capitalized. It will therefore look as follows:

```
+-- rtos/CMSIS_5/
|   +-- README.md
|   +-- docs/
|   +-- CMSIS/
|       +-- include/
|               +-- mbed_cmsis_conf.h   # Currently in cmsis/
|       +-- RTE/
|           +-- include/
|               +-- RTE_Components.h    # Currently in cmsis/
|       +-- RTOS2/
|           +-- Include/
|               +-- A                   # Content of rtos/source/TARGET_CORTEX/rtx5/Include/
|               +-- B                   # Header files currently in rtos/source/TARGET_CORTEX/
|           +-- RTX/
|               +-- Config/
|                   +-- C               # Content of rtos/source/TARGET_CORTEX/rtx5/RTX/Config/
|               +-- Include/
|                   +-- D               # Content of rtos/source/TARGET_CORTEX/rtx5/RTX/Include/
|               +-- Include1/
|                   +-- cmsis_os.h      # Currently in rtos/source/TARGET_CORTEX/rtx4/
|               +-- Library/
|                   +-- cmsis_os1.c     # Currently in rtos/source/TARGET_CORTEX/rtx4/
|               +-- Source/
|                   +-- E               # Content of rtos/source/TARGET_CORTEX/rtx5/RTX/Source/
|           +-- Source/
|               +-- F                   # Content of rtos/source/TARGET_CORTEX/rtx5/Source
|               +-- G                   # Source files currently in rtos/source/TARGET_CORTEX/
|           +-- TOOLCHAIN_ARM_MICRO/    # Currently in rtos/source/TARGET_CORTEX/
|           +-- TOOLCHAIN_ARM_STD/      # Currently in rtos/source/TARGET_CORTEX/
|           +-- TOOLCHAIN_GCC_ARM/      # Currently in rtos/source/TARGET_CORTEX/
|           +-- TOOLCHAIN_IAR/          # Currently in rtos/source/TARGET_CORTEX/
|           +-- mbed_lib.json           # Currently in rtos/source/TARGET_CORTEX/
|       +-- TARGET_CORTEX_A/
|           +-- Include/
|               +-- H                   # Header files currently in cmsis/TARGET_CORTEX_A/
|           +-- Source/
|               +-- I                   # Source files currently in cmsis/TARGET_CORTEX_A/
|       +-- TARGET_CORTEX_M/
|           +-- Include/
|               +-- J                   # Header files currently in cmsis/TARGET_CORTEX_M/
```

## Documentation
The README.md may contain a brief introduction to the component. Detailed documentation may be added under `docs` directory.
