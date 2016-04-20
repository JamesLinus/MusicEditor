#include "CCQApplication.h"
#include "CCQGLView.h"
#include <QTimer>

NS_CC_BEGIN

static void PVRFrameEnableControlWindow(bool bEnable);

/* sharedApplication pointer */
CCQApplication * CCQApplication::sm_pSharedApplication = nullptr;

CCQApplication::CCQApplication(int argc, char *argv[])
    : QApplication(argc, argv)
    , _timer(nullptr)
{
    _qAnimationInterval = 1.0f / 60.0f * 1000.0f;
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCQApplication::~CCQApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = nullptr;
}

int CCQApplication::run()
{
	/* Initialize instance and cocos2d */
    if (! applicationDidFinishLaunching())
    {
        return 1;
    }

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    _timer->start(_qAnimationInterval);

    return cocos2d::CCQApplication::getInstance()->exec();
}

void CCQApplication::setAnimationInterval(double interval)
{
    _qAnimationInterval = interval * 1000.0f;
    if (_timer)
    {
        _timer->start(_qAnimationInterval);
    }
}

/* static member function */
CCQApplication* CCQApplication::getInstance()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

void CCQApplication::timerUpdate()
{
	Director::getInstance()->mainLoop();
	//CCQGLView::getInstance()->updateWindowSize();
}

static void PVRFrameEnableControlWindow(bool bEnable)
{
	HKEY hKey = 0;

	// Open PVRFrame control key, if not exist create it.
	if (ERROR_SUCCESS != RegCreateKeyExW(HKEY_CURRENT_USER,
		L"Software\\Imagination Technologies\\PVRVFRame\\STARTUP\\",
		0,
		0,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		0,
		&hKey,
		nullptr))
	{
		return;
	}

	const WCHAR* wszValue = L"hide_gui";
	const WCHAR* wszNewData = (bEnable) ? L"NO" : L"YES";
	WCHAR wszOldData[256] = { 0 };
	DWORD   dwSize = sizeof(wszOldData);
	LSTATUS status = RegQueryValueExW(hKey, wszValue, 0, nullptr, (LPBYTE)wszOldData, &dwSize);
	if (ERROR_FILE_NOT_FOUND == status              // the key not exist
		|| (ERROR_SUCCESS == status                 // or the hide_gui value is exist
		&& 0 != wcscmp(wszNewData, wszOldData)))    // but new data and old data not equal
	{
		dwSize = sizeof(WCHAR) * (wcslen(wszNewData) + 1);
		RegSetValueEx(hKey, wszValue, 0, REG_SZ, (const BYTE *)wszNewData, dwSize);
	}

	RegCloseKey(hKey);
}

NS_CC_END

