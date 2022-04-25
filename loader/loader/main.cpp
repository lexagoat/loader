#define VERSION (string)"1.0.0" 
#define WEBSITE (string)"yourwebsite.com" 

#include "includes.h"

tool* tools;

int main() {



	string username;
	string password;

#ifdef NDEBUG 

	tools->checkPrivileges();	
	tools->checkInternet();		


#endif 

	string check_version = tools->httpRequest(WEBSITE, "version.php"); 

	if (check_version == VERSION) {

		tools->setupConsole("Loader base", 400, 200); 

		tools->title(); 

		tools->gotoxy(2, 3); cout << termcolor::magenta << "Username: " << termcolor::white;

		do {						
			tools->gotoxy(12, 3);
			getline(cin, username);

		} while (username.empty());

		tools->gotoxy(2, 4); cout << termcolor::magenta << "Pass: ";

		tools->toggleText();	

		do {                     

			tools->gotoxy(8, 4);
			getline(cin, password);

		} while (password.empty());

		tools->toggleText(); 

		HW_PROFILE_INFO hwProfileInfo;
		string hwid;

		if (GetCurrentHwProfile(&hwProfileInfo)) { 

			hwid = hwProfileInfo.szHwProfileGuid; 

			char request[512];
			sprintf(request, "/check.php?username=%s&password=%s&hwid=%s", username.c_str(), password.c_str(), hwid.c_str());

			string login_response = tools->httpRequest(WEBSITE, request); 

			string first_response = login_response.substr(0, 1); 
			string second_response = login_response.substr(1, 2); 

			if (first_response == "1") { 

				if (second_response == "1" || second_response == "3") { 

					system("cls"); 
					tools->toggleCursor(); 
					tools->title();

					tools->gotoxy(2, 2); cout << termcolor::magenta << "1. Inject 1.dll";
					tools->gotoxy(2, 3); cout << termcolor::magenta << "2. Inject 2.dll";
					int key_chosen = _getch(); 

					switch (key_chosen) {

					case '1':						
						system("cls");
						if (tools->downloadFile("yourwebsite.com/1.dll", "c://1.dll")) {	
							tools->loadLibrary("notepad.exe", "c://1.dll");					
							cout << "1.dll injected into notepad.exe";
						}
						else {

							int msgboxID = MessageBoxA(
								NULL,
								(LPCSTR)"Couldn't download DLL.",
								(LPCSTR)"Loader base",
								MB_OK
							);
							exit(-1);

						}
						break;
					case '2':						
						system("cls");
						if (tools->downloadFile("yourwebsite.com/2.dll", "c://2.dll")) {	
							tools->loadLibrary("notepad.exe", "c://2.dll");					
							cout << "2.dll injected";
						}
						else {

							int msgboxID = MessageBoxA(
								NULL,
								(LPCSTR)"Couldn't download DLL.",
								(LPCSTR)"Loader base",
								MB_OK
							);
							exit(-1);

						}
						break;
					}


					Sleep(2000);
					exit(-1);

				}
				else {

					int msgboxID = MessageBoxA(
						NULL,
						(LPCSTR)"Wrong HWID.",
						(LPCSTR)"Loader base",
						MB_OK
					);
					exit(-1);

				}

			}
			else {

				int msgboxID = MessageBoxA(
					NULL,
					(LPCSTR)"Wrong password.",
					(LPCSTR)"Loader base",
					MB_OK
				);
				exit(-1);

			}

		}
		else {

			int msgboxID = MessageBoxA(
				NULL,
				(LPCSTR)"Couldn't read hwid.",
				(LPCSTR)"Loader base",
				MB_OK
			);
			exit(-1);

		}


	}
	else {

		int msgboxID = MessageBoxA(
			NULL,
			(LPCSTR)"There is a new version avaiable, please download it.",
			(LPCSTR)"Loader base",
			MB_OK
		);
		exit(-1);

	}

	return 0;
}