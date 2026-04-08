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
}

