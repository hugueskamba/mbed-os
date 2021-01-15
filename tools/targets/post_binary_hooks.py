#!/usr/bin/env python
# Copyright (c) 2021 Arm Limited
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import inspect
import sys
from enum import Enum


class ReturnCode(Enum):
    """Return codes."""

    SUCCESS = 0
    ERROR = 1
    INVALID_OPTIONS = 2


class ArgumentParserWithDefaultHelp(argparse.ArgumentParser):
    """Subclass that always shows the help message on invalid arguments."""

    def error(self, message):
        """Error handler."""
        sys.stderr.write("error: {}\n".format(message))
        self.print_help()
        raise SystemExit(ReturnCode.INVALID_OPTIONS.value)


class PostBinaryHookIdError(Exception):
    """Indicates an error with the function ID provided."""


class PostBinaryHook:
    """..."""

    def __int__(self, hook_id):
        """..."""
        hook_id_details = hook_id.split(".")

        if len(hook_id_details) != 2:
            raise PostBinaryHookIdError(
                "Invalid hook function id '{}' (must be 'class_name.function_name')".format(
                    hook_id
                )
            )

        module_classes = tuple(
            x[1]
            for x in inspect.getmembers(sys.modules[__name__], inspect.isclass)
        )

        class_name, func_name = hook_id_details

        if class_name not in module_classes:
            raise PostBinaryHookIdError(
                "Class '{}' not found in {}".format(class_name,  __file__)
            )

        


def post_build_action(args):
    """..."""
    p_b_hook = PostBinaryHook(args.hook_id)


def parse_args():
    """Parse the command line args."""
    parser = ArgumentParserWithDefaultHelp(
        description="Applying a post binary hook.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )

    parser.add_argument(
        "hook-id",
        type=str,
        help=(
            "the id of the post build operation to perform."
            " Must be '<CLASS_NAME>.<FUNCTION_NAME>'"
        ),
    )

    parser.add_argument(
        "-e",
        "--elf-file",
        type=str,
        default="",
        help="an Executable and Linkable Format (ELF) file to work with",
    )

    parser.add_argument(
        "-b",
        "--bin-file",
        type=str,
        default="",
        help="a binary file to work with",
    )

    parser.set_defaults(func=post_build_action)

    args_namespace = parser.parse_args()

    # We want to fail gracefully, with a consistent
    # help message, in the no argument case.
    # So here's an obligatory hasattr hack.
    if not hasattr(args_namespace, "func"):
        parser.error("No arguments given!")
    else:
        return args_namespace


def run_post_binary_hooks():
    """Application main algorithm."""
    args = parse_args()
    args.func(args)


def _main():
    """Run post_binary_hook."""
    try:
        run_post_binary_hooks()
    except Exception as error:
        print(error)
        return ReturnCode.ERROR.value
    else:
        return ReturnCode.SUCCESS.value


if __name__ == "__main__":
    sys.exit(_main())
