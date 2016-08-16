#include "stdafx.h"
#include "CEFWebkitBrowser.h"

// WKEWebkitBrowser.cpp : ����Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "CEFWebkitBrowser.h"
#include <strsafe.h>

CEFWebkitBrowserWnd* CEFWebkitBrowserWnd::pCEFWebkitBrowserWnd=NULL;



CEFWebkitBrowserWnd::CEFWebkitBrowserWnd()
{
   // pWKEWebkitUI=NULL;
    pURLEditUI=NULL;
    pCEFWebkitBrowserWnd=this;
}

CEFWebkitBrowserWnd::~CEFWebkitBrowserWnd()
{

}


CControlUI* CEFWebkitBrowserWnd::CreateControl( LPCTSTR pstrClassName )
{
    if (_tcsicmp(pstrClassName, _T("CEFWebkitBrowser")) == 0)
    {
        return  new CCEFWebkitUI(GetSafeHwnd());
    }

    return NULL;
}

void CEFWebkitBrowserWnd::OnFinalMessage(HWND hWnd)
{

	
	__super::OnFinalMessage(hWnd);
}

LRESULT CEFWebkitBrowserWnd::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	//::PostQuitMessage(0L);
	return 0;
}


void CEFWebkitBrowserWnd::InitWindow()
{

    //pURLEditUI = dynamic_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("ui_et_urlinput")));

    //pWKEWebkitUI = dynamic_cast<CWKEWebkitUI*>(m_PaintManager.FindControl(_T("ui_wke_wkebrowser")));
    //if (pWKEWebkitUI)
    //{

    //    wkeClientHanler_.onTitleChanged = onTitleChangedLocal;
    //    wkeClientHanler_.onURLChanged = onURLChangedLocal;

    //    pWKEWebkitUI->SetClientHandler(&wkeClientHanler_);

    //    jsBindFunction("jsInvokeCPlusPlus", jsInvokeCPlusPlus, 2);//�����js��������js��������c++����


    //    pWKEWebkitUI->LoadFile(_T("htmlexample/index.html"));
    //}



}


void CEFWebkitBrowserWnd::Notify( TNotifyUI& msg )
{
    if( msg.sType == _T("click") ) 
    {	
        if( msg.pSender->GetName() == _T("ui_btn_goback") ) 
        {
           
        }
        if( msg.pSender->GetName() == _T("ui_btn_goforward") ) 
        {
           
        }
        if( msg.pSender->GetName() == _T("ui_btn_ensure") ) 
        {
           
        }
        if( msg.pSender->GetName() == _T("ui_btn_home") ) 
        {
           
        }
    }
    //��Ҫ�ر�richedit��want return����
    else if (msg.sType==DUI_MSGTYPE_RETURN)
    {
        if (pURLEditUI==msg.pSender)
        {
            if (pURLEditUI&&pWKEWebkitUI)
            {
                //pWKEWebkitUI->LoadURL(pURLEditUI->GetText().GetData());
            }
        }
    }
    __super::Notify(msg);
}


LRESULT CEFWebkitBrowserWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

    bHandled=FALSE;

    return 0;
}