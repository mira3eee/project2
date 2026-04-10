#include <iostream>
#include <windows.h> // Sleep, Beep, GetlLcalTime
using namespace std;

int alarmhour;
int alarmminute;
int alarmsecond;
bool alarmEnabled = false;

void setAlarm()
{
	cout << "\nvvedite chas budilnica: ";
	cin >> alarmhour;
	cout << "vvedite minutes budilnica: ";
	cin >> alarmminute;
	cout << "vvedite seconds budilnica: ";
	cin >> alarmsecond;


	alarmEnabled = true;
	cout << "\nbudilnik ustanovlen na ";
	cout << alarmhour << ":" << alarmminute << ":" << alarmsecond << endl;
}

void ringAlarm()
{
	cout << "\nBudilnik Ring!!!!!!!!!!!" << endl;
		
	while (true)
	{
		cout << "\nALAAAARM!!!!" << endl;
		cout << "Najmite probel dla otkluchenia" << endl;
		Beep(1000, 1000);


		if (GetAsyncKeyState(VK_SPACE))
		{
			alarmEnabled = false;
			cout << "\nbudilnik vicluchen";
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
	cout << "programma zapuzhena" << endl;

	setAlarm();

	while (true)
	{
		CheckAlarm();
		Sleep(1000);
	}
	return 0;
}
