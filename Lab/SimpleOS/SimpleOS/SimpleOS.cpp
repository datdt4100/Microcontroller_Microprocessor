// SimpleOS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "scheduler.h"
#include <windows.h>

DWORD WINAPI Timer(LPVOID lpParameter)
{
	while (1)
	{
		SCH_Update_Task();
		Sleep(10);
	}
	return 0;
}

void Task1()
{
    cout << "Task 1 executed completely!\n";
}

void Task2()
{
    cout << "Task 2 executed completely!\n";
}

void Task3()
{
	cout << "Task 3 executed completely!\n";
}

void Task4()
{
	cout << "Task 4 executed completely!\n";
}

void Task5()
{
	cout << "Task 5 executed completely!\n";
}

int main()
{
    
    SCH_INIT();

    SCH_Add_Task(Task1, 10, 200);
    //SCH_Add_Task(Task2, 30, 200);
	//SCH_Add_Task(Task3, 50, 0);
	//SCH_Add_Task(Task4, 50, 300);
	SCH_Add_Task(Task5, 40, 100);
	unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE pthread0 = CreateThread(0, 0, Timer, &myCounter , 0, &myThreadID);

	while (1)
	{
		SCH_Dispatch_Task();
	}
	CloseHandle(pthread0);
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
