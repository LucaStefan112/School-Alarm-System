#include <bits/stdc++.h>
#include <Windows.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

using namespace std;

void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
    return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}

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

void Pauza(int ora, int minut){
    string startCommand = "start " + GetExePath() + "\\sound.mp3";
    system(startCommand.c_str());
    Sleep(5000);

    system("taskkill /F /im Music.UI.exe");
}

int main(){
    HideConsole();
    bool pauza = false;

    while(1){
        time_t now;
        struct tm nowLocal;
        now = time(NULL);
        nowLocal = *localtime(&now);
        int ora = nowLocal.tm_hour, minut = nowLocal.tm_min;

        if((7 < ora && ora < 11 && (minut == 0 || minut == 50)) || (10 < ora && ora < 16 && (minut == 10 || minut == 0)) && !(ora == 11 && minut == 0)){
            if(!pauza){
                Pauza(ora, minut);
                pauza = true;
            }}
        else
            pauza = false;

	Sleep(5000);
    }

    return 0;
}
