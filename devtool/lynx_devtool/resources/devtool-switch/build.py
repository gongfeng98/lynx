#!/usr/bin/env python3
# Copyright 2025 The Lynx Authors. All rights reserved.
# Licensed under the Apache License Version 2.0 that can be found in the
# LICENSE file in the root directory of this source tree.
import os
import shutil
import sys


# Set the script exit mode, equivalent to set -e in bash
sys.tracebacklimit = 0

# Get the directory where the current script is located
current_dir = os.path.dirname(os.path.realpath(__file__))
# Get the root directory
root_dir = os.path.abspath(os.path.join(current_dir, '../../../../'))
template_dir = "dist/devtoolSwitch.lynx.bundle"
android_target_dir = os.path.join(root_dir, "platform/android/lynx_devtool/src/main/assets/devtool_switch")
ios_target_dir = os.path.join(root_dir, "platform/darwin/ios/lynx_devtool/assets")
switch_page_dir = "switchPage/"

# Get command-line arguments
output = sys.argv[1] if len(sys.argv) > 1 else None

print("========== build devtool switch page ==========")
# Change to the current directory
os.chdir(current_dir)
# Execute the pnpm build command
os.environ['PATH'] = f"{root_dir}/../buildtools/node/bin:{os.environ['PATH']}"
os.system("pnpm build")

print("========== copy devtool switch resource ==========")
if output:
    output_path = os.path.join(output, switch_page_dir)
    print(output_path)
    # Create the output directory
    os.makedirs(output_path, exist_ok=True)
    # Copy the file
    shutil.copy(os.path.join(current_dir, template_dir), output_path)

# Delete the old target directory
if os.path.exists(android_target_dir):
    shutil.rmtree(android_target_dir)
ios_switch_page_path = os.path.join(ios_target_dir, switch_page_dir)
if os.path.exists(ios_switch_page_path):
    shutil.rmtree(ios_switch_page_path)

# Create the new target directory
os.makedirs(os.path.join(android_target_dir, switch_page_dir), exist_ok=True)
os.makedirs(ios_switch_page_path, exist_ok=True)

# Copy the file to the target directory
shutil.copy(os.path.join(current_dir, template_dir), os.path.join(android_target_dir, switch_page_dir))
shutil.copy(os.path.join(current_dir, template_dir), ios_switch_page_path)