// timew.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <io.h>
#include <Windows.h>

void usage() {
	_tprintf(_T("time command for windows:\n"));
	_tprintf(_T("  timew.exe <yourprogram>\n"));
}

int _tmain(int argc, _TCHAR* argv[]) {

	if (argc != 2) {
		usage();
		return 0;
	} else {
		if (-1 == _taccess(argv[1], 0)) {
			_tprintf(_T("%s cannot found!\n"), argv[1]);
		}

		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;

		ZeroMemory(&pi, sizeof(pi));

		BOOL bRet = FALSE;
		bRet = CreateProcess(argv[1], NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

		if (bRet) {
			WaitForSingleObject(pi.hProcess, INFINITE);

			FILETIME createTime, exitTime, kernelTime, userTime;
			bRet = GetProcessTimes(pi.hProcess, &createTime, &exitTime, &kernelTime, &userTime);

			if (bRet) {
				_tprintf(_T("\n%s finished\n"), argv[1]);
				_tprintf(_T("cost time: %dms\n"), (exitTime.dwLowDateTime - createTime.dwLowDateTime) / 10000);
			}

			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
		}
	}

	return 0;
}

