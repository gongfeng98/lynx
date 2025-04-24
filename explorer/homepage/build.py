#!/usr/bin/env python3
# Copyright 2025 The Lynx Authors. All rights reserved.
# Licensed under the Apache License Version 2.0 that can be found in the
# LICENSE file in the root directory of this source tree.

import os
import subprocess

root_dir = subprocess.check_output(['git', 'rev-parse', '--show-toplevel']).decode().strip()
os.environ['PATH'] = f"{root_dir}/buildtools/node/bin:{os.environ['PATH']}"
# Install dependencies and build
os.system('pnpm install')
os.system('pnpm build')
