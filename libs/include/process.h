#ifndef PROCESS_H
#define PROCESS_H

#include <windows.h>
#include <string>

namespace myLib {
class Process
{
	PROCESS_INFORMATION pi{};
public:
	Process(const std::wstring& commandLine,
			bool bInheritHandles = false,
			DWORD dwCreationFlags = 0,
			const std::wstring& currentDirectory = L""
		);              

	Process(const Process&) = delete;
	Process& operator=(const Process&) = delete;

	Process(Process&& other) noexcept;
	Process& operator=(Process&& other) noexcept;
	~Process() noexcept { close(); }
	
	void wait(DWORD timeout=INFINITE);

	bool valid() const {return pi.hProcess != nullptr;}

	bool terminate(UINT exitCode = 1);

	DWORD GetThreadID() const noexcept { return pi.dwThreadId; }
	DWORD GetProcessID() const noexcept { return pi.dwProcessId; }
	HANDLE GetThreadHandle() const noexcept { return pi.hThread; }
	HANDLE GetProcessHandle() const noexcept { return pi.hProcess; }

private:
	void close() noexcept;
};

}
#endif // PROCESS_H