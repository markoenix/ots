// Copyright (c) 2011-2017 The OTS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "vmtx.h"

#include "maxp.h"
#include "vhea.h"

// vmtx - Vertical Metrics Table
// http://www.microsoft.com/typography/otspec/vmtx.htm

namespace ots {

bool ots_vmtx_parse(Font *font, const uint8_t *data, size_t length) {
  font->vmtx = new OpenTypeVMTX(font);
  return font->vmtx->Parse(data, length);
}

bool OpenTypeVMTX::Parse(const uint8_t *data, size_t length) {
  if (!GetFont()->vhea || !GetFont()->maxp) {
    return Error("vhea or maxp table missing as needed by vmtx");
  }

  return OpenTypeMetricsTable::Parse(data, length);
}

bool OpenTypeVMTX::Serialize(OTSStream *out) {
  return OpenTypeMetricsTable::Serialize(out);
}

bool OpenTypeVMTX::ShouldSerialize() {
  return OpenTypeMetricsTable::ShouldSerialize() &&
         GetFont()->vhea != NULL; // vmtx should serialise when vhea is preserved.
}

bool ots_vmtx_should_serialise(Font *font) {
  return font->vmtx != NULL && font->vmtx->ShouldSerialize();
}

bool ots_vmtx_serialise(OTSStream *out, Font *font) {
  return font->vmtx->Serialize(out);
}

void ots_vmtx_reuse(Font *font, Font *other) {
  font->vmtx = other->vmtx;
  font->vmtx_reused = true;
}

void ots_vmtx_free(Font *font) {
  delete font->vmtx;
}

}  // namespace ots
