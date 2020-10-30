#include <bits/stdc++.h>
#include <Windows.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

using namespace std;

string GetExeFileName()
{
  char buffer[MAX_PATH];
  GetModuleFileName( NULL, buffer, MAX_PATH );
  return string(buffer);
}

string GetExePath()
{
  string f = GetExeFileName();
  return f.substr(0, f.find_last_of( "\\/" ));
}

bool IsProcessRunning(const TCHAR* const executableName) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        return false;
    }

    do {
        if (!_tcsicmp(entry.szExeFile, executableName)) {
            CloseHandle(snapshot);
            return true;
        }
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);
    return false;
}

void Pauza(int ora, int minut){
    string startCommand = "start " + GetExePath() + "\\sound.mp3";
    system(startCommand.c_str());
    Sleep(5000);
    if(IsProcessRunning("Music.UI.exe"))
        system("taskkill /F /im Music.UI.exe");
    else if(IsProcessRunning("vlc.exe"))
        system("taskkill /F /im vlc.exe");
}

int main(){

    bool pauza = false;

    while(1){
        time_t now;
        struct tm nowLocal;
        now = time(NULL);
        nowLocal = *localtime(&now);
        int ora = nowLocal.tm_hour, minut = nowLocal.tm_min;

        if((8 < ora && ora < 11 && (minut == 38 || minut == 50)) || (10 < ora && ora < 14 && (minut == 10 || minut == 0)) || 14 == ora && minut == 0){
            if(!pauza){
                Pauza(ora, minut);
                pauza = true;
            }}
        else
            pauza = false;
    }

    return 0;
}
