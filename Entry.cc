#include "stdafx.h"
#include "CEFWebkitBrowser.h"
#include "clientapp.h"
#include <Shlobj.h>
#include <strsafe.h>

//�ǵÿ���resource�е���Դ������Ŀ¼



int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//ʵ���������Ⱦ�����
	CPaintManagerUI::SetInstance(hInstance);

	//Initializes the COM library on the current thread and identifies,��ʼ��COM��, Ϊ����COM���ṩ֧��
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr))
	{
		return 0;
	}

	cef_enable_highdpi_support();

	void* sandbox_info = NULL;

#if defined(CEF_USE_SANDBOX)
	// Manage the life span of the sandbox information object. This is necessary
	// for sandbox support on Windows. See cef_sandbox_win.h for complete details.
	CefScopedSandboxInfo scoped_sandbox;
	sandbox_info = scoped_sandbox.sandbox_info();
#endif


	// Provide CEF with command-line arguments.
	CefMainArgs main_args(hInstance);

	// SimpleApp implements application-level callbacks for the browser process.
	// It will create the first browser instance in OnContextInitialized() after
	// CEF has initialized.
	CefRefPtr<CCefClientApp> app(new CCefClientApp); //CefAppʵ�֣����ڴ��������صĻص���


	// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
	// that share the same executable. This function checks the command-line and,
	// if this is a sub-process, executes the appropriate logic.
	int exit_code = CefExecuteProcess(main_args, app, sandbox_info);
	if (exit_code >= 0) {
		// The sub-process has completed so return here.
		return exit_code;
	}

	// Specify CEF global settings here.
	CefSettings settings;
	CefSettingsTraits::init(&settings);
//	settings.single_process = true;                //ʹ�ö����ģʽ
	settings.ignore_certificate_errors = true;      //���Ե�ssl֤����֤����
//	settings.command_line_args_disabled = true;
//	CefString(&settings.locale).FromASCII("zh-CN");
	TCHAR szSpecialPath[MAX_PATH];
	memset(szSpecialPath, '\0', sizeof(szSpecialPath));
	//	GetEnvironmentVariable("",szSpecialPath,sizeof())
	
	if (FALSE!= SHGetSpecialFolderPath(NULL, szSpecialPath, CSIDL_PROFILE, FALSE))
	{
		StringCbCat(szSpecialPath,sizeof(szSpecialPath),_T("\\AppData\\Local\\Temp\\CEF"));
		CefString(&settings.cache_path).FromString(szSpecialPath,sizeof(szSpecialPath)/2,true);
	}
	
	

#if !defined(CEF_USE_SANDBOX)
	settings.no_sandbox = true;
#endif

	//multi_threaded_message_loop=true �������õ�Ŀ����ʹcef��browser ui�̺߳ͳ�����̷߳��룬ʹ��duilib����Ϣѭ������
	settings.multi_threaded_message_loop = true;




	// Initialize CEF.
	CefInitialize(main_args, settings, app, sandbox_info);

	
	CEFWebkitBrowserWnd pFrame;
	pFrame.Create(NULL, _T("�����"), UI_WNDSTYLE_FRAME | WS_CLIPCHILDREN, WS_EX_ACCEPTFILES);
	pFrame.CenterWindow();

	//	������Ӱ

	CShadowWindow shadowwnd;
	CShadowWindow::Initialize(hInstance);
	shadowwnd.Create(pFrame.GetHWND());
	shadowwnd.SetSize(4);
	shadowwnd.SetPosition(4, 4);
	shadowwnd.SetColor(RGB(22, 22, 22));

	//   pFrame.ShowWindow(true);

	if (!settings.multi_threaded_message_loop)
	{
		//Run the CEF message loop. This function will block until the application
		//recieves a WM_QUIT message.
		CefRunMessageLoop();
		//CefDoMessageLoopWork();

	}
	else
	{
		CPaintManagerUI::MessageLoop();
	}


	CefShutdown();

	//�˳������ͷ�COM��
	::CoUninitialize();

	return 0;
}