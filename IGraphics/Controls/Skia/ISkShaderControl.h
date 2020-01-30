/*
 ==============================================================================

 This file is part of the iPlug 2 library. Copyright (C) the iPlug 2 developers.

 See LICENSE.txt for  more info.

 ==============================================================================
*/

#pragma once

/**
 * @file
 * @copydoc ISkShaderControl
 */

#include "IControl.h"
#include "SkRuntimeEffect.h"
#include "SkGradientShader.h"
#include "IGraphicsSkia.h"

BEGIN_IPLUG_NAMESPACE
BEGIN_IGRAPHICS_NAMESPACE

/** A control that hosts an SkSL fragment shader
 * https://github.com/google/skia/blob/master/src/sksl/README
 * @ingroup IControls */
class ISkShaderControl : public IControl
{
public:
  ISkShaderControl(const IRECT& bounds)
  : IControl(bounds)
  {
    auto data = SkData::MakeFromFileName("C:\\Users\\oli\\Desktop\\SkShader.frag");
    fSkSL = SkString((const char*)data->bytes(), data->size());

    DBGMSG(fSkSL.c_str());

    //data->
//    fSkSL =
//"uniform float rad_scale;\n"
//"uniform float2 in_center;\n"
//"\n"
//"void main(float x, float y, inout half4 color) {\n"
//"float xx = x - in_center.x;\n"
//"float yy = y - in_center.y;\n"
//"float radius = sqrt(xx * xx + yy * yy);\n"
//"radius = sqrt(radius);\n"
//"float angle = atan(yy / xx);\n"
//"float t = (angle + 3.1415926 / 2) / (3.1415926);\n"
//"t += radius * rad_scale;\n"
//"t = fract(t);\n"
//"color = half4(mix(half4(1,0,0,1), half4(0,1,0,1), t));\n"
//"}\n";

        //"uniform float time;\n"
        //"void main(float x, float y, inout half4 color) {\n"
        //  "half timeh = half(time);\n"
        //  "color = half4(timeh, half(y)/300, timeh, half(mod(y,10)));"
        //"}\n";

    SetActionFunction([&](IControl* pCaller) {

      SetAnimation([&](IControl* pCaller) {

        float* pInputLoc = (float*) fInputs.get();
        pInputLoc[0] = std::sin((float) pCaller->GetAnimationProgress() * 10.f) / 5;
        pInputLoc[1] = pCaller->GetRECT().MW();
        pInputLoc[2] = pCaller->GetRECT().MH();

        if (pCaller->GetAnimationProgress() > 1.) {
          pCaller->OnEndAnimation();
        }

      }, 10000);

    });

    Load(bounds.W(), bounds.H());
  }

  void Draw(IGraphics& g) override
  {
    g.FillRect(COLOR_GREEN, mRECT);
    
    if(fEffect)
      DoDraw((SkCanvas*) g.GetDrawContext());
  }
  
  void DoDraw(SkCanvas* canvas)
  {
    canvas->clear(SK_ColorWHITE);
    canvas->drawRect(SkiaRect(mRECT.GetPadded(1)), fPaint);
  }

  void OnMouseDown(float x, float y, const IMouseMod& mod) override
  {
    SetDirty(true);
  }
  
  void Load(SkScalar winWidth, SkScalar winHeight)
  {
    //SkPoint points[] = { { 0, 0 }, { winWidth, 0 } };
    //SkColor colors[] = { SK_ColorRED, SK_ColorGREEN };

    //sk_sp<SkShader> shader;

//    shader = SkGradientShader::MakeLinear(points, colors, nullptr, 2, SkTileMode::kClamp);
//    fShaders.push_back(std::make_pair("Linear Gradient", shader));
//
//    shader = SkGradientShader::MakeRadial({ 128, 128 }, 128, colors, nullptr, 2,
//                                          SkTileMode::kClamp);
//    fShaders.push_back(std::make_pair("Radial Gradient", shader));
//
//    shader = SkGradientShader::MakeSweep(128, 128, colors, nullptr, 2);
//    fShaders.push_back(std::make_pair("Sweep Gradient", shader));

    this->Rebuild();
  }
  
  bool Rebuild()
  {
    auto [effect, errorText] = SkRuntimeEffect::Make(fSkSL);
    if (!effect) {
      DBGMSG("%s\n", errorText.c_str());
      return false;
    }

    size_t oldSize = fEffect ? fEffect->inputSize() : 0;
    fInputs.realloc(effect->inputSize());
    if (effect->inputSize() > oldSize) {
        memset(fInputs.get() + oldSize, 0, effect->inputSize() - oldSize);
    }
    fChildren.resize_back(effect->children().count());
    for (auto& c : fChildren) {
        if (!c) {
            c = fShaders[0].second;
        }
    }

    fEffect = effect;

    auto inputs = SkData::MakeWithoutCopy(fInputs.get(), fEffect->inputSize());
    auto shader = fEffect->makeShader(std::move(inputs), fChildren.data(), fChildren.count(), nullptr, false);
    fPaint.setShader(std::move(shader));

    return true;
  }
  
private:
  sk_sp<SkRuntimeEffect> fEffect;
  SkAutoTMalloc<char> fInputs;
  SkTArray<sk_sp<SkShader>> fChildren;
  SkString fSkSL;
  SkPaint fPaint;
  // Named shaders that can be selected as inputs
  SkTArray<std::pair<const char*, sk_sp<SkShader>>> fShaders;
};

END_IGRAPHICS_NAMESPACE
END_IPLUG_NAMESPACE
