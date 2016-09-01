#include "stdafx.h"
#include "CEFV8HandlerEx.h"
#include <strsafe.h>

CCEFV8HandlerEx::CCEFV8HandlerEx()
{

}

CCEFV8HandlerEx::~CCEFV8HandlerEx()
{

}


bool CCEFV8HandlerEx::Execute(const CefString& name  /*JavaScript���õ�C++��������*/, CefRefPtr<CefV8Value> object /*JavaScript�����߶���*/, const CefV8ValueList& arguments /*JavaScript���ݵĲ���*/, CefRefPtr<CefV8Value>& retval /*���ظ�JS��ֵ���ø��������*/, CefString& exception)                        //֪ͨ�쳣��Ϣ��JavaScript
{
	if (name == _T("jsInvokeCPlusPlus"))
	{
		if (arguments.size() == 2)
		{
			CefString strParam1 = arguments.at(0)->GetStringValue();
			CefString strParam2 = arguments.at(1)->GetStringValue();

			TCHAR szBuffer[512];
			StringCbPrintf(szBuffer, sizeof(szBuffer), _T("jsInvokeCPlusPlus(%s,%s)"), strParam1, strParam2);
			::MessageBox(GetForegroundWindow(), szBuffer, _T("example"), MB_OK);

			retval = CefV8Value::CreateInt(0);
		}
		else
		{
			retval = CefV8Value::CreateInt(2);
		}

		return true;

	}

	// Function does not exist.
	return false;


}