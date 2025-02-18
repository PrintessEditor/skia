/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkImage_GaneshBase_DEFINED
#define SkImage_GaneshBase_DEFINED

#include "include/core/SkRefCnt.h"
#include "include/core/SkSamplingOptions.h"
#include "include/gpu/ganesh/SkImageGanesh.h"
#include "include/private/gpu/ganesh/GrImageContext.h"
#include "src/image/SkImage_Base.h"

#include <memory>
#include <tuple>
#include <cstddef>
#include <cstdint>

class GrBackendFormat;
class GrBackendTexture;
class GrCaps;
class GrContextThreadSafeProxy;
class GrDirectContext;
class GrFragmentProcessor;
class GrRecordingContext;
class GrSurfaceProxyView;
class GrTextureProxy;
class SkBitmap;
class SkColorSpace;
class SkImage;
class SkMatrix;
enum SkAlphaType : int;
enum SkColorType : int;
enum class GrColorType;
enum class GrImageTexGenPolicy : int;
enum class GrSemaphoresSubmitted : bool;
enum class SkTileMode;
struct GrFlushInfo;
struct SkIRect;
struct SkISize;
struct SkImageInfo;
struct SkRect;
namespace skgpu {
enum class Mipmapped : bool;
class RefCntedCallback;
}  // namespace skgpu

class SkImage_GaneshBase : public SkImage_Base {
public:
    GrImageContext* context() const final { return fContext.get(); }

    // From SkImage.h
    bool isValid(GrRecordingContext*) const final;

    // From SkImage_Base.h
    bool getROPixels(GrDirectContext*, SkBitmap*, CachingHint) const final;

    sk_sp<SkImage> onMakeSubset(const SkIRect& subset, GrDirectContext*) const final;

    bool onReadPixels(GrDirectContext* dContext,
                      const SkImageInfo& dstInfo,
                      void* dstPixels,
                      size_t dstRB,
                      int srcX,
                      int srcY,
                      CachingHint) const override;

    // From SkImage_GaneshBase.h
    virtual GrSemaphoresSubmitted flush(GrDirectContext*, const GrFlushInfo&) const = 0;

    static bool ValidateBackendTexture(const GrCaps*,
                                       const GrBackendTexture& tex,
                                       GrColorType grCT,
                                       SkColorType ct,
                                       SkAlphaType at,
                                       sk_sp<SkColorSpace> cs);
    static bool ValidateCompressedBackendTexture(const GrCaps*,
                                                 const GrBackendTexture& tex,
                                                 SkAlphaType);

    // Helper for making a lazy proxy for a promise image.
    // PromiseImageTextureFulfillProc must not be null.
    static sk_sp<GrTextureProxy> MakePromiseImageLazyProxy(
            GrContextThreadSafeProxy*,
            SkISize dimensions,
            GrBackendFormat,
            skgpu::Mipmapped,
            SkImages::PromiseImageTextureFulfillProc,
            sk_sp<skgpu::RefCntedCallback> releaseHelper);

    virtual std::tuple<GrSurfaceProxyView, GrColorType> asView(GrRecordingContext*,
                                                               skgpu::Mipmapped,
                                                               GrImageTexGenPolicy) const = 0;

    virtual std::unique_ptr<GrFragmentProcessor> asFragmentProcessor(GrRecordingContext*,
                                                                     SkSamplingOptions,
                                                                     const SkTileMode[2],
                                                                     const SkMatrix&,
                                                                     const SkRect*,
                                                                     const SkRect*) const = 0;

protected:
    SkImage_GaneshBase(sk_sp<GrImageContext>, SkImageInfo, uint32_t uniqueID);

    sk_sp<GrImageContext> fContext;

#if defined(SK_GRAPHITE)
    sk_sp<SkImage> onMakeTextureImage(skgpu::graphite::Recorder*,
                                      RequiredImageProperties) const final;
    sk_sp<SkImage> onMakeSubset(const SkIRect& subset,
                                skgpu::graphite::Recorder*,
                                RequiredImageProperties) const final;
    sk_sp<SkImage> onMakeColorTypeAndColorSpace(SkColorType,
                                                sk_sp<SkColorSpace>,
                                                skgpu::graphite::Recorder*,
                                                RequiredImageProperties) const final;
#endif
};

#endif
