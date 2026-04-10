#include <iostream>
#include <windows.h> // Sleep, Beep, GetlLcalTime
using namespace std;

int alarmhour;
int alarmminute;
int alarmsecond;
bool alarmEnabled = false;

void setAlarm()
{
	cout << "vvedite chas budilnica: ";
	cin >> alarmhour;
	cout << "vvedite minutes budilnica: ";
	cin >> alarmminute;
	cout << "vvedite seconds budilnica: ";
	cin >> alarmsecond;


	alarmEnabled = true;
	cout << "budilnik ustanovlen na ";
	cout << alarmhour << ":" << alarmminute << ":" << alarmsecond << endl;
}

void ringAlarm()
{
	cout << "Budilnik Ring!!!!!!!!!!!" << endl;
		
	while (true)
	{
		cout << "ALAAAARM!!!!" << endl;
		Beep(1000, 1000);
		cout << "Najmite probel dla otkluchenia" << endl;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			alarmEnabled = false;
			cout << "budilnik vicluchen";
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
		cout << "\nproverca" << endl;
		ringAlarm();
	}
}

int main()
{
	cout << "programma zapuzhena" << endl;

	setAlarm();

	while (true)
	{
		CheckAlarm();
		Sleep(1000);
	}
	return 0;
}
