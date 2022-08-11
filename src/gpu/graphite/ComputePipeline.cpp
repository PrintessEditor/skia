/*
 * Copyright 2022 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "src/gpu/graphite/ComputePipeline.h"

namespace skgpu::graphite {

ComputePipeline::ComputePipeline(const Gpu* gpu)
        : Resource(gpu, Ownership::kOwned, SkBudgeted::kYes) {}

}  // namespace skgpu::graphite