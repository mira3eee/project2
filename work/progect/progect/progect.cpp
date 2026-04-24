#include <iostream>
#include <windows.h> // Sleep, Beep, GetloLocalTime
#include <locale>
using namespace std;

int alarmhour;
int alarmminute;
int alarmsecond;
bool alarmEnabled = false;

void setAlarm()
{
	setlocale(LC_ALL, "RU");
	cout << "\nвведите час: ";
	cin >> alarmhour;
	cout << "введите минуты: ";
	cin >> alarmminute;
	cout << "введите секунды: ";
	cin >> alarmsecond;


	alarmEnabled = true;
	cout << "\nбудильник установлен на ";
	cout << alarmhour << ":" << alarmminute << ":" << alarmsecond << endl;
}

void ringAlarm()
{
	setlocale(LC_ALL, "RU");
	cout << "\nБудильник звонит!!!!!!!!!!!" << endl;

	while (true)
	{
		cout << "\nААААЛААААААРМ!!!!" << endl;
		cout << "НАЖМИТЕ НА ПРОБЕЛ ДЛЯ ОТКЛЮЧЕНИЯ" << endl;
		Beep(1000, 1000);

	
		if (GetAsyncKeyState(VK_SPACE))
		{
			alarmEnabled = false;
			cout << "\nбудильник выключен";
			break;
		}

		Sleep(100);
	}
}

void CheckAlarm()
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	int chour = t.wHour;
	int cminute = t.wMinute;
	int csecond = t.wSecond;

	if (alarmEnabled &&
		chour == alarmhour &&
		cminute == alarmminute &&
		csecond == alarmsecond)
	{
		ringAlarm();
	}
}

int main()
{
	setlocale(LC_ALL, "RU");
	cout << "программа запущена" << endl;

	setAlarm();

	while (true)
	{
		CheckAlarm();
		Sleep(1000);
	}
	return 0;
}
