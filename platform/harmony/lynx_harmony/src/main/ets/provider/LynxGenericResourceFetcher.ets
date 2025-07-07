// Copyright 2024 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

import { LynxResourceRequest } from './LynxResourceRequest';
import { LynxResourceProvider } from './LynxResourceProvider';
import { LynxStreamDelegate } from './LynxStreamDelegate';
import { AsyncCallback } from '@ohos.base';

/**
 * `LynxGenericResourceFetcher` is defined inside `LynxEngine`
 * and injected from outside to implement a general resource loading interface.
 * It is used inside LynxEngine for resource loading capabilities of components such as `Text`
 * @apidoc
 */
export abstract class LynxGenericResourceFetcher implements LynxResourceProvider {
  /**
   * `LynxEngine` internally calls this method to obtain the general
   * resource content, and the return result is required to be the resource content `byte[]` type.
   *
   * @apidoc
   * @param request Request to obtain the general resource content.
   * @param callback Containing contents of the requiring resource.
   */
  abstract fetchResource(request: LynxResourceRequest, callback: AsyncCallback<ArrayBuffer>);

  /**
   * `LynxEngine` internally calls this method to obtain the path of the common resource
   * on the local disk, and the return result is required to be of `String` type.
   *
   * @apidoc
   * @param request Request to obtain the path of the common resource on the local disk.
   * @param callback with path on the disk of the requiring resource.
   */
  abstract fetchResourcePath(request: LynxResourceRequest, callback: AsyncCallback<string>);

  /**
   * `LynxEngine` internally calls this method to obtain resource content in a streaming
   * manner.
   *
   * @apidoc
   * @optional user may impl this method if stream loading is necessary.
   * @param request Request to obtain resource content in a streaming manner.
   * @param delegate streaming of the requiring resource.
   */
  fetchStream(request: LynxResourceRequest, delegate: LynxStreamDelegate) {
  }

  /**
   * Cancel the request of the requiring resource.
   *
   * @apidoc
   * @param request Request to be canceled.
   */
  abstract cancel(request: LynxResourceRequest);
}