/****************************************************************************
 Copyright (c) 2021-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include "DrawBatch2D.h"
#include "core/Root.h"
#include "core/assets/Material.h"
#include "scene/Pass.h"

namespace cc {
namespace scene {

void DrawBatch2D::clear() {
}

void DrawBatch2D::fillPass(Material *mat, const gfx::DepthStencilState *depthStencilState, ccstd::hash_t dsHash, const ccstd::vector<IMacroPatch> *patches) {
    const auto &passes = mat->getPasses();
    if (passes->empty()) return;
    _shaders.clear();
    if (_passes.size() < passes->size()) {
        auto num = static_cast<uint32_t>(passes->size() - _passes.size());
        for (uint32_t i = 0; i < num; ++i) {
            _passes.emplace_back(ccnew scene::Pass(Root::getInstance()));
        }
    }

    for (uint32_t i = 0; i < passes->size(); ++i) {
        auto &pass = passes->at(i);
        auto &passInUse = _passes[i];
        pass->update();
        if (!depthStencilState) depthStencilState = pass->getDepthStencilState();
        passInUse->initPassFromTarget(pass, *depthStencilState, dsHash);
        _shaders.push_back(patches ? passInUse->getShaderVariant(*patches) : passInUse->getShaderVariant());
    }
}

} // namespace scene
} // namespace cc
