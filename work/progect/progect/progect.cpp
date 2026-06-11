#include <iostream>
#include <windows.h>
#include <locale>
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;

class Alarm
{
private:
    int hour, minute, second;
    bool enabled;
    string name;

public:
    Alarm(string n, int h, int m, int s)
        : name(n), hour(h), minute(m), second(s), enabled(true)
    {
        cout << "Будильник '" << name << "' создан!" << endl;
    }

    virtual ~Alarm()
    {
        cout << "Будильник '" << name << "' удалён из памяти." << endl;
    }

    int getHour() { return hour; }
    int getMinute() { return minute; }
    int getSecond() { return second; }
    bool isEnabled() { return enabled; }
    string getName() { return name; }

    void toggle()
    {
        enabled = !enabled;
        cout << "'" << name << "' теперь " << (enabled ? "включён" : "выключен") << endl;
    }

    bool isTime(int h, int m, int s)
    {
        return enabled && hour == h && minute == m && second == s;
    }

    virtual void print(int index)
    {
        cout << index << ". [" << (enabled ? "ВКЛ" : "ВЫКЛ") << "] ";
        cout << name << " - " << hour << ":" << minute << ":" << second << endl;
    }

    virtual void ring()
    {
        cout << "\nБудильник '" << name << "' звонит!" << endl;
        while (true)
        {
            cout << "НАЖМИТЕ ПРОБЕЛ ДЛЯ ОТКЛЮЧЕНИЯ" << endl;
            Beep(1000, 500);
            if (GetAsyncKeyState(VK_SPACE))
            {
                cout << "Выключен." << endl;
                enabled = false;
                break;
            }
            Sleep(100);
        }
    }
};

class RepeatingAlarm : public Alarm
{
private:
    int repeatDays;

public:
    RepeatingAlarm(string n, int h, int m, int s, int days)
        : Alarm(n, h, m, s), repeatDays(days)
    {
        cout << "(повторяется каждые " << days << " дн.)" << endl;
    }

    void print(int index) override
    {
        Alarm::print(index);
        cout << "   └─ повторяется каждые " << repeatDays << " дн." << endl;
    }

    void ring() override
    {
        cout << "[ПОВТОРЯЮЩИЙСЯ] ";
        Alarm::ring();
        cout << "Повторится через " << repeatDays << " дн." << endl;
    }
};

const int HISTORY_SIZE = 10;
string ringHistory[HISTORY_SIZE];
int historyCount = 0;

void addToHistory(const string& alarmName)
{
    if (historyCount < HISTORY_SIZE)
    {
        ringHistory[historyCount] = alarmName;
        historyCount++;
    }
}

void showHistory()
{
    if (historyCount == 0) { cout << "\nИстория пуста." << endl; return; }
    cout << "\n===== ИСТОРИЯ =====" << endl;
    for (int i = 0; i < historyCount; i++)
        cout << i + 1 << ". " << ringHistory[i] << endl;
}

vector<Alarm*> alarms;

void showAlarms()
{
    if (alarms.empty()) { cout << "\nБудильников нет." << endl; return; }
    cout << "\n===== БУДИЛЬНИКИ =====" << endl;
    for (int i = 0; i < alarms.size(); i++)
        alarms[i]->print(i + 1);
}

int inputInRange(const string& prompt, int min, int max)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (value >= min && value <= max)
            return value;
        cout << "Ошибка! Введите число от " << min << " до " << max << endl;
    }
}

void addAlarm()
{
    string name;
    cout << "\nНазвание: "; cin >> name;

    int h = inputInRange("Час (0-23): ", 0, 23);
    int m = inputInRange("Минуты (0-59): ", 0, 59);
    int s = inputInRange("Секунды (0-59): ", 0, 59);

    cout << "Повторяющийся? (1-да / 0-нет): ";
    int rep; cin >> rep;

    if (rep == 1)
    {
        int days = inputInRange("Повторять каждые N дней (1-365): ", 1, 365);
        alarms.push_back(new RepeatingAlarm(name, h, m, s, days));
    }
    else
    {
        alarms.push_back(new Alarm(name, h, m, s));
    }
}

void toggleAlarm()
{
    showAlarms();
    if (alarms.empty()) return;
    cout << "\nНомер: "; int idx; cin >> idx; idx--;
    if (idx < 0 || idx >= alarms.size()) 
    { 
        cout << "Неверный номер!" << endl; 
        return; 
    }
    alarms[idx]->toggle();
}

void deleteAlarm()
{
    showAlarms();
    if (alarms.empty()) return;
    cout << "\nНомер для удаления: "; int idx; cin >> idx; idx--;
    if (idx < 0 || idx >= alarms.size()) 
    { 
        cout << "Неверный номер!" << endl; 
        return; 
    }
    delete alarms[idx];
    alarms.erase(alarms.begin() + idx);
}

void sortAlarms()
{
    if (alarms.size() < 2) { cout << "Недостаточно будильников." << endl; return; }
    sort(alarms.begin(), alarms.end(), [](Alarm* a, Alarm* b)
        {
            int sA = a->getHour() * 3600 + a->getMinute() * 60 + a->getSecond();
            int sB = b->getHour() * 3600 + b->getMinute() * 60 + b->getSecond();
            return sA < sB;
        });
    cout << "Отсортировано!" << endl;
    showAlarms();
}

void checkAlarms()
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    for (int i = 0; i < alarms.size(); i++)
    {
        if (alarms[i]->isTime(t.wHour, t.wMinute, t.wSecond))
        {
            alarms[i]->ring();
            addToHistory(alarms[i]->getName());
        }
    }
}

void showMenu()
{
    cout << "\n===== МЕНЮ =====" << endl;
    cout << "1 - Добавить будильник" << endl;
    cout << "2 - Показать все" << endl;
    cout << "3 - Вкл/Выкл" << endl;
    cout << "4 - Удалить" << endl;
    cout << "5 - Сортировать" << endl;
    cout << "6 - История срабатываний" << endl;
    cout << "7 - Выход" << endl;
    cout << "\nНажмите цифру: ";
}

enum MenuOption { ADD = 1, SHOW, TOGGLE, DEL, SORT, HISTORY, EXIT };

int main()
{
    setlocale(LC_ALL, "RU");
    showMenu();

    while (true)
    {
        if (_kbhit())
        {
            char c = _getch();

            switch (c)
            {
            case '1': addAlarm();    showMenu(); break;
            case '2': showAlarms();  showMenu(); break;
            case '3': toggleAlarm(); showMenu(); break;
            case '4': deleteAlarm(); showMenu(); break;
            case '5': sortAlarms();  showMenu(); break;
            case '6': showHistory(); showMenu(); break;
            case '7':
                for (int i = 0; i < alarms.size(); i++)
                    delete alarms[i];
                cout << "До свидания!" << endl;
                return 0;
            default:
                cout << "Неверная клавиша!" << endl;
                break;
            }
        }

        checkAlarms();
        Sleep(1000);
    }

    return 0;
}
