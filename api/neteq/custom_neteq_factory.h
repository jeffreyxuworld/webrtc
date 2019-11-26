/*
 *  Copyright (c) 2019 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef API_NETEQ_CUSTOM_NETEQ_FACTORY_H_
#define API_NETEQ_CUSTOM_NETEQ_FACTORY_H_

#include <memory>

#include "api/audio_codecs/audio_decoder_factory.h"
#include "api/neteq/neteq_controller_factory.h"
#include "api/neteq/neteq_factory.h"
#include "api/scoped_refptr.h"
#include "system_wrappers/include/clock.h"

namespace webrtc {

// This factory can be used to generate NetEq instances that make use of a
// custom AudioDecoderFactory and/or NetEqControllerFactory. Using a custom
// AudioDecoderFactory is deprecated and the functionality will be removed soon.
class CustomNetEqFactory : public NetEqFactory {
 public:
  explicit CustomNetEqFactory(
      std::unique_ptr<NetEqControllerFactory> controller_factory);
  // This constructor is deprecated and will be removed soon.
  CustomNetEqFactory(
      rtc::scoped_refptr<AudioDecoderFactory> decoder_factory,
      std::unique_ptr<NetEqControllerFactory> controller_factory);
  ~CustomNetEqFactory() override;
  CustomNetEqFactory(const CustomNetEqFactory&) = delete;
  CustomNetEqFactory& operator=(const CustomNetEqFactory&) = delete;

  std::unique_ptr<NetEq> CreateNetEq(const NetEq::Config& config,
                                     Clock* clock) const override;

  std::unique_ptr<NetEq> CreateNetEq(
      const NetEq::Config& config,
      const rtc::scoped_refptr<AudioDecoderFactory>& decoder_factory,
      Clock* clock) const override;

 private:
  rtc::scoped_refptr<AudioDecoderFactory> decoder_factory_;
  std::unique_ptr<NetEqControllerFactory> controller_factory_;
};

}  // namespace webrtc
#endif  // API_NETEQ_CUSTOM_NETEQ_FACTORY_H_
