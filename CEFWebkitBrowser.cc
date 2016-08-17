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
	pURLEditCtrl_=NULL;
	pWebStateCtrl_ = NULL;
	pWKEWebkitCtrl_ = NULL;

    pCEFWebkitBrowserWnd=this;
	
}

CEFWebkitBrowserWnd::~CEFWebkitBrowserWnd()
{
	
}


CControlUI* CEFWebkitBrowserWnd::CreateControl( LPCTSTR pstrClassName )
{
    if (_tcsicmp(pstrClassName, _T("CEFWebkitBrowser")) == 0)
    {
        return  (pWKEWebkitCtrl_=new CCEFWebkitUI(GetSafeHwnd()));
    }

    return NULL;
}

void CEFWebkitBrowserWnd::OnFinalMessage(HWND hWnd)
{

	
	__super::OnFinalMessage(hWnd);
}

//LRESULT CEFWebkitBrowserWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
//{
//	//::PostQuitMessage(0L);
//
//	return __super::OnDestroy(uMsg,wParam,lParam,bHandled);
//}

//��ȡWM_CLOSE��Ϣ
LRESULT CEFWebkitBrowserWnd::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{

	if (!pWKEWebkitCtrl_->IsClosed())
	{
		pWKEWebkitCtrl_->CloseAllPage();
		bHandled = TRUE;
		// // Cancel the close.
		return 0;
	}

	bHandled = FALSE;

	return -1;
}


void CEFWebkitBrowserWnd::InitWindow()
{
	pWebStateCtrl_ =dynamic_cast<CLabelUI*>(	FindControl(_T("ui_lbl_status")));
    pURLEditCtrl_ = dynamic_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("ui_et_urlinput")));
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
        if (pURLEditCtrl_==msg.pSender)
        {
            if (pURLEditCtrl_&&pWKEWebkitCtrl_)
            {
                //pWKEWebkitUI->LoadURL(pURLEditUI->GetText().GetData());
            }
        }
    }
	else if (msg.sType == _T("windowinit"))
	{
		OnInitComplate();
	}
    __super::Notify(msg);
}


LRESULT CEFWebkitBrowserWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	TCHAR szBuf[256];

	switch (uMsg)
	{
	case UM_CEF_COMPLETEELEASE:
		bHandled = TRUE;
		//Sleep(2000);
		//CefQuitMessageLoop();
		//PostQuitMessage(0L);
		break;
	case UM_CEF_WEBLOADPOPUP:
		
		break;
	case UM_CEF_WEBLOADEND:
	{
	
	/*	int index = m_pTabLayoutUI->GetCurSel();
		CHorizontalLayoutUI* pHor = (CHorizontalLayoutUI*)m_pTabLayoutUI->GetItemAt(index);
		if (pHor)
		{
			int iCount = m_pTabSwitchHor->GetCount();
			for (int i = 0; i < iCount; i++)
			{
				COptionUI* pOpt = (COptionUI*)m_pTabSwitchHor->GetItemAt(i);
				CHorizontalLayoutUI* pHaveHor = (CHorizontalLayoutUI*)pOpt->GetTag();
				if (pHaveHor == pHor)
				{
					if (m_cWebClient.at(index)->GetBrowser()->CanGoBack())
					{
						m_BackBtn->SetEnabled(true);
					}
					else
					{
						m_BackBtn->SetEnabled(false);
					}
					if (m_cWebClient.at(index)->GetBrowser()->CanGoForward())
					{
						m_ForwardBtn->SetEnabled(true);
					}
					else
					{
						m_ForwardBtn->SetEnabled(false);
					}
					m_UEdit.at(index) = m_cWebClient.at(index)->m_url.c_str();
					break;
				}
			}
		}*/

		
		if (pURLEditCtrl_)
		{
			pURLEditCtrl_->SetText(pWKEWebkitCtrl_->GetFinalURL(pWKEWebkitCtrl_->GetHitIndex()).c_str());
		}

		memset(szBuf, '\0', sizeof(szBuf));
		CefString* pStrComplateURL = (CefString*)lParam;
		if (pStrComplateURL!=NULL)
		{
			StringCbPrintf(szBuf,sizeof(szBuf), _T("%s:�������"), pStrComplateURL->c_str());
			delete pStrComplateURL;
		}

		pWebStateCtrl_->SetText(szBuf);
	}
	break;

	case UM_CEF_WEBLOADSTART:
	{
		memset(szBuf, '\0', sizeof(szBuf));
		CefString* pStrComplateURL = (CefString*)lParam;
		if (pStrComplateURL != NULL)
		{
			StringCbPrintf(szBuf, sizeof(szBuf), _T("���ڼ���:%s"), pStrComplateURL->c_str());
			delete pStrComplateURL;
		}

		pWebStateCtrl_->SetText(szBuf);

		//int index = m_pTabLayoutUI->GetCurSel();
		/*	CHorizontalLayoutUI* pHor = (CHorizontalLayoutUI*)m_pTabLayoutUI->GetItemAt(index);
		if (pHor)
		{
			int iCount = m_pTabSwitchHor->GetCount();
			for (int i = 0; i < iCount; i++)
			{
				COptionUI* pOpt = (COptionUI*)m_pTabSwitchHor->GetItemAt(i);
				CHorizontalLayoutUI* pHaveHor = (CHorizontalLayoutUI*)pOpt->GetTag();
				if (pHaveHor == pHor)
				{
					m_UEdit.at(index) = m_cWebClient.at(index)->m_url.c_str();
					break;
				}
			}
		}*/
	}
	break;
	case UM_CEF_WEBTITLECHANGE:
	{
		CefString* pStrComplateURL = (CefString*)lParam;
		if (pStrComplateURL != NULL)
		{
			OnTitleChanged(*pStrComplateURL);
			delete pStrComplateURL;
		}
	}
		break;
	default:
		break;
	}

    bHandled=FALSE;

    return 0;
}

void CEFWebkitBrowserWnd::OnInitComplate()
{
	if (pWKEWebkitCtrl_)
	{
		pWKEWebkitCtrl_->NewPage(_T("www.baidu.com"));
	}
}


//����ı�
void CEFWebkitBrowserWnd::OnTitleChanged(const CefString str)
{

	//int index = m_pTabLayoutUI->GetCurSel();
	//CHorizontalLayoutUI* pHor = (CHorizontalLayoutUI*)m_pTabLayoutUI->GetItemAt(index);
	//if (pHor)
	//{
	//	int iCount = m_pTabSwitchHor->GetCount();
	//	for (int i = 0; i < iCount; i++)
	//	{
	//		COptionUI* pOpt = (COptionUI*)m_pTabSwitchHor->GetItemAt(i);
	//		CHorizontalLayoutUI* pHaveHor = (CHorizontalLayoutUI*)pOpt->GetTag();
	//		if (pHaveHor == pHor)
	//		{
	//			if (str.length() > 8)
	//			{
	//				wchar_t strtilte[100] = { NULL };
	//				wcsncpy(strtilte, str.c_str(), 6);
	//				wcsncat(strtilte, _T("..."), 3);
	//				pOpt->SetText(strtilte);
	//			}
	//			else
	//			{
	//				pOpt->SetText(str.c_str());
	//			}
	//			pOpt->SetToolTip(str.c_str());
	//			break;
	//		}
	//	}
	//}

	return;
}
