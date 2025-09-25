#include <windows.h>
#include <iostream>

#define SERVICE_NAME  L"KursOSAn" // Имя службы

// Прототипы функций
VOID WINAPI ServiceMain(DWORD argc, LPTSTR* argv);
VOID WINAPI ServiceCtrlHandler(DWORD ctrlCode);
void WriteEventLog(const wchar_t* message);
void ReportServiceStatus(DWORD currentState, DWORD exitCode, DWORD waitHint);
void ServiceStart(DWORD argc, LPTSTR* argv);
void ServiceStop();

// Глобальные переменные
SERVICE_STATUS_HANDLE g_ServiceStatusHandle = NULL;
SERVICE_STATUS g_ServiceStatus = { 0 };
bool g_IsRunning = false;

int main() {
    // Явно указываем, что SERVICE_NAME является LPWSTR
    wchar_t serviceName[] = SERVICE_NAME;

    SERVICE_TABLE_ENTRY serviceTable[] = {
        { serviceName, ServiceMain },  // Приводим к LPWSTR
        { NULL, NULL }
    };

    // Запуск службы
    if (StartServiceCtrlDispatcher(serviceTable) == 0) {
        WriteEventLog(L"Ошибка запуска службы.");
        return GetLastError();
    }

    return 0;
}

VOID WINAPI ServiceMain(DWORD argc, LPTSTR* argv) {
    g_ServiceStatusHandle = RegisterServiceCtrlHandler(SERVICE_NAME, ServiceCtrlHandler);
    if (!g_ServiceStatusHandle) {
        WriteEventLog(L"Ошибка регистрации обработчика управления.");
        return;
    }

    ReportServiceStatus(SERVICE_START_PENDING, NO_ERROR, 3000);
    ServiceStart(argc, argv);
}

VOID WINAPI ServiceCtrlHandler(DWORD ctrlCode) {
    switch (ctrlCode) {
    case SERVICE_CONTROL_STOP:
        ServiceStop();
        break;
    default:
        break;
    }
}

void WriteEventLog(const wchar_t* message) {
    HANDLE hEventLog = RegisterEventSource(NULL, SERVICE_NAME);
    if (hEventLog) {
        const wchar_t* messages[] = { message }; // Используем const wchar_t*
        ReportEvent(hEventLog, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, messages, NULL);
        DeregisterEventSource(hEventLog);
    }
}

void ReportServiceStatus(DWORD currentState, DWORD exitCode, DWORD waitHint) {
    g_ServiceStatus.dwServiceType = SERVICE_WIN32;
    g_ServiceStatus.dwCurrentState = currentState;
    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    g_ServiceStatus.dwWin32ExitCode = exitCode;
    g_ServiceStatus.dwCheckPoint = 0;
    g_ServiceStatus.dwWaitHint = waitHint;

    SetServiceStatus(g_ServiceStatusHandle, &g_ServiceStatus);
}

void ServiceStart(DWORD argc, LPTSTR* argv) {
    WriteEventLog(L"Служба запущена.");
    g_IsRunning = true;
    ReportServiceStatus(SERVICE_RUNNING, NO_ERROR, 0);

    // Основной цикл службы
    while (g_IsRunning) {
        Sleep(10000); // Задержка 10 секунд
        WriteEventLog(L"Служба работает.");
    }

    ReportServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
}

void ServiceStop() {
    WriteEventLog(L"Служба остановлена.");
    g_IsRunning = false;
    ReportServiceStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
}