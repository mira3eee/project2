#include <iostream>
#include <windows.h> // Sleep, Beep, GetlLcalTime
using namespace std;

int alarmhour;
int alarmminute;
bool alarmEnabled = false;

void setAlarm()
{
	cout << "vvedite chas budilnica: ";
	cin >> alarmhour;
	cout << "vvedite minutes budilnica: ";
	cin >> alarmminute;

	alarmEnabled = true;
	cout << "budilnik ustanovlen na ";
	cout << alarmhour << ":" << alarmminute;
}

void ringAlarm()
{
	cout << "Budilnik Ring!!!!!!!!!!!" << endl;
	cout << "Najmite probel dla otkluchenia" << endl;
		
	while (alarmEnabled)
	{
		Beep(1000, 500);

		if (GetAsyncKeyState(VK_SPACE))
		{
			alarmEnabled = false;
			cout << "budilnik vicluchen";
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

	if (alarmEnabled &&
		chour == alarmhour &&
		cminute == alarmminute)
	{
		ringAlarm;
	}
}

int main()
{
	while (true)
	{
		CheckAlarm();
		Sleep(1000);
	}
	return 0;
}
