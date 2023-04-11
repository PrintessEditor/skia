/*
 * Copyright 2023 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

// This should be a temporary file that can be removed when SkImageEncoder is removed

#include "include/encode/SkPngEncoder.h"

class SkPixmap;
class SkWStream;

namespace SkPngEncoder {

bool Encode(SkWStream*, const SkPixmap&, const Options&) {
    return false;
}

}  // namespace SkPngEncoder
