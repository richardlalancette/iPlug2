#include "IPlugWin32.h"
#include "IPlug_include_in_plug_src.h"
#include "commctrl.h"
#include "wdlutf8.h"

IPlugWin32::IPlugWin32(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPrograms))
{
  GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");
}

void* IPlugWin32::OpenWindow(void* pParent)
{
  HWND parentHWND = reinterpret_cast<HWND>(pParent);
  mControlHWND = CreateDialog(gHINSTANCE, MAKEINTRESOURCE(IDD_DIALOG1), parentHWND, (DLGPROC)Proc);
  SetWindowLongPtr(mControlHWND, GWLP_USERDATA, (LONG_PTR)this);
  ShowWindow(mControlHWND, SW_SHOW);

  return mControlHWND;
}

void IPlugWin32::CloseWindow()
{
  DestroyWindow(mControlHWND);
}

BOOL CALLBACK IPlugWin32::Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  IPlugWin32* _this = reinterpret_cast<IPlugWin32*>(GetWindowLongPtr(hDlg, GWLP_USERDATA));

  switch (message)
  {
    case WM_INITDIALOG:
    {
      SendMessage(GetDlgItem(hDlg, IDC_GAIN_SLIDER), TBM_SETRANGE, 0, MAKELONG(0, 1024));
      return TRUE;
    }
    case WM_HSCROLL:
    {
  #ifndef OS_WIN
      int sliderID = GetWindowLong((HWND)lParam, GWL_ID);
      float normalisedValue = SWELL_TB_GetPos(hDlg, sliderID) / 1024.f;
  #else
      float normalisedValue = static_cast<float>(HIWORD(wParam))/ 1024.f;
      int sliderID = GetDlgCtrlID((HWND)lParam);
  #endif
    
      switch (sliderID)
      {
        case IDC_GAIN_SLIDER:
        {
          _this->SetParameterValue(kGain, normalisedValue);
          _this->SetStaticText(IDC_GAIN_TEXT, kGain);
          return TRUE;
        }
        default:
          break;
      }
    }
    default:
      break;
  }
  return FALSE;
}

void IPlugWin32::OnParamChangeUI(int paramIdx, EParamSource source)
{
  if (source != EParamSource::kUI)
  {
    switch (paramIdx)
    {
      case kGain:
      {
        SendDlgItemMessage(mControlHWND, IDC_GAIN_SLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)GetParam(kGain)->Int());
        SetStaticText(IDC_GAIN_TEXT, kGain);
      }
    default:
      break;
    }
  }
}

void IPlugWin32::OnUIOpen()
{
}

void IPlugWin32::SetStaticText(int id, int paramIdx)
{
  WDL_String str;
  GetParam(paramIdx)->GetDisplayForHostWithLabel(str, true);

#if UNICODE
  WDL_WCHAR itemText[32];
  WDL_MBtoWideStr(itemText, str.Get(), 32/*check?*/);
  SetDlgItemText(mControlHWND, id, (LPCWSTR) itemText);
#else
  SetDlgItemText(mControlHWND, id, (LPCSTR) str.Get());
#endif
}

void IPlugWin32::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const double gain = GetParam(kGain)->Value() / 100.;
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
    for (int c = 0; c < nChans; c++) {
      outputs[c][s] = inputs[c][s] * gain;
    }
  }
}
