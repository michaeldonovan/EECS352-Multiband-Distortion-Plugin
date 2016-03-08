
#ifndef IPopupMenuControl_h
#define IPopupMenuControl_h

class IPopUpMenuControl : public IControl
{
public:
    IPopUpMenuControl(IPlugBase *pPlug, IRECT pR, IColor cBG, IColor cFG, int paramIdx)
    : IControl(pPlug, pR, paramIdx)
    {
        mDisablePrompt = false;
        mDblAsSingleClick = true;
        mText = IText(14,&COLOR_WHITE,"Futura");
        mColor = cBG;
        mColorFG = cFG;
        textRect= IRECT(pR.L+8, pR.T+1, pR.R, pR.B);
    }
    
    bool Draw(IGraphics* pGraphics)
    {
        pGraphics->FillIRect(&mColor, &mRECT);
        IChannelBlend blend = IChannelBlend();
        pGraphics->FillTriangle(&COLOR_WHITE, mRECT.L+4, mRECT.T+4, mRECT.L+4, mRECT.B-4, mRECT.L+8, (mRECT.T + mRECT.H()/2 ), &blend);
        char disp[32];
        mPlug->GetParam(mParamIdx)->GetDisplayForHost(disp);
        
        if (CSTR_NOT_EMPTY(disp))
        {
            return pGraphics->DrawIText(&mText, disp, &textRect);
        }
        
        return true;
    }
    
    void OnMouseDown(int x, int y, IMouseMod* pMod)
    {
        if (pMod->L)
        {
            PromptUserInput(&mRECT);
        }
        
        mPlug->GetGUI()->SetAllControlsDirty();
    }
    
    //void OnMouseWheel(int x, int y, IMouseMod* pMod, int d){} //TODO: popup menus seem to hog the mousewheel
private:
    IColor mColor;
    IColor mColorFG;
    IRECT textRect;
};

#endif /* IPopupMenuControl_h */