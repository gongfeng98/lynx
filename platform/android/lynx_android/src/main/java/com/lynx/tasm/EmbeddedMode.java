// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.
package com.lynx.tasm;

/**
 * Embedded mode is an experimental switch
 * When embeddedMode is set, we offer optimal performance for embedded scenarios.
 * But it will restrict business flexibility.
 * Please DO NOT enable this switch on your own for now.
 * Contact the Lynx team for more information.
 * Embedded mode configuration options using bitwise operations for multiple selections
 * Usage:
 * 1. Basic usage:
 *    - Use UNSET for no options selected
 *    - Use EMBEDDED_MODE_BASE for basic optimizations
 *    - Use EMBEDDED_MODE_ALL for all optimizations
 *
 * 2. Combine options:
 *    - Use bitwise OR (|) to combine options
 *    - Example: EMBEDDED_MODE_BASE | ENGINE_POOL
 *
 * 3. Check options:
 *    - Use bitwise AND (&) to check if an option is enabled
 *    - Example: (mode & ENGINE_POOL) != 0
 */
public enum EmbeddedMode {
  /**
   * No optimization options selected
   */
  UNSET(0),
  /**
   * Basic embedded mode with minimal optimizations
   */
  EMBEDDED_MODE_BASE(1 << 0),
  /**
   * Engine pool optimization in embedded mode
   */
  ENGINE_POOL(1 << 1),

  /**
   * Combination of all optimization options
   * <p>
   * Note: When adding new optimization options, update this value
   */
  EMBEDDED_MODE_ALL(EMBEDDED_MODE_BASE.mode() | ENGINE_POOL.mode());

  private final int mMode;

  EmbeddedMode(int mode) {
    mMode = mode;
  }

  public int mode() {
    return mMode;
  }
}
