// Copyright 2024 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

import { LynxResourceRequest } from './LynxResourceRequest';
import { AsyncCallback } from '@ohos.base';
import { LynxResourceProvider } from './LynxResourceProvider';

export interface TemplateProviderResult {
  binary?: ArrayBuffer;
  // TODO(nihao.royal): support returning TemplateBundle
}

/**
 * `LynxTemplateResourceFetcher` is defined inside LynxEngine and
 * injected from outside to implement the resource loading interface of
 * [Bundle](/guide/spec.html#lynx-bundle-or-bundle) and [Lazy Bundle](/guide/spec.html#lazy-bundle)
 * etc.
 * @apidoc
 */
export abstract class LynxTemplateResourceFetcher implements LynxResourceProvider {
  /**
   * `LynxEngine` internally calls this method to obtain the contents of Bundle
   * and Lazy Bundle. The returned result type can contain `byte[]` or `TemplateBundle`.
   *
   * @apidoc
   * @param request Request to obtain the contents of Bundle and Lazy Bundle
   * @param callback Response with the requiring content file in ArrayBuffer type.
   */
  abstract fetchTemplate(request: LynxResourceRequest,
    callback: AsyncCallback<TemplateProviderResult>);

  /**
   * fetch SSRData of lynx.
   *
   * @param request
   * @param callback response with the requiring SSR data.
   */
  abstract fetchSSRData(request: LynxResourceRequest, callback: AsyncCallback<ArrayBuffer>);
}