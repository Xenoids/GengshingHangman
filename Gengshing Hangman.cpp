#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

// Totally Not E4st3r 3gg
#define SalamdariLuofu(x) printf(x)
#define KingYuan(x) puts(x)
void Rama();

void Set_Color(int tColor, int bgColor);
void genshin_title();
void title(int option, char* guess);
void generate_char();
void print_char();
void print_charList();
void print_guesschar(char* guess_char, bool* isCharExist);
void print_wrongchar(char* wrongChar, int count);
void space();
void display_Hangman();
void convert_guesschar(char* guess, bool* isExist);
bool check_answer(char* guess, char* ans, bool* isExist, bool isComplete);
bool check_alpha(char* alpha);
bool check_YN(char* alpha);
void sort_leaderboard();
void print_leaderboard();
void menu_display(int option,char* alphabet);
void menu_play(char* guess);
void menu_about(char* guess);
void menu_exit();

int calculate_score(int score, bool isWrong);

// Global Variables
struct charData{
	char charName[100];	
	char charDesc[100];
};

// Pake LinkedList?
struct playerData{
	char playerName[100];
	int playerScore;
};

enum txtColor {
		RED = 1,
		BLUE,
		YELLOW,
		GREEN,
		WHITE,
		BLACK,
		ORANGE,
}color;

void Set_TextColor(txtColor c);

enum listChar{
	KAEYA = 0,
	BENNETT,
	XINYAN,
	DILUC,
	ZHONGLI,
}chara;

void view_result(listChar c);
void kaeya();
void xinyan();
void diluc();
void bennett();
void zhongli();

charData cData[10];
playerData pData[100];
int dataCount = 0;


int randomNum;
int choice;
int lives = 3;

char currName[100];
int currScore = 0;

int wrongCounter;
char wrongChar[10];

int main()
{
	// BACKUP = alphabet awalnya char, diganti jadi string
	// Lives System (OTW) :), Validasi Input (80%?) :), Game Over Scene Blm :), Coloring (masih di hangman)
	// Leaderboard (player + score) ? sort  , Gambar" mini karakter gengshing + data tambahan
	// Set BG color + text
	// Pastikan Validasi duplikat yang wrong char (v)
	SetConsoleTitle("Gengshing Hangman");
	
	Set_Color(17,7);
	//Set_Color(17,15);
	
	// randomizer trigger
	srand(time(0));
	
	// Input
	char guess[100] ={0};
	
	// Reset Score and Name
	currScore = 0;
	strcpy(currName,"");
	
	// Generate Hangman List
	generate_char();
	
	// randomizer 0 to 3
	//randomNum = rand() % 4;
	
	//print_char();
	//print_charList();
	
	/*char charName[][30] = {
	{"kaeya"},{"bennett"}
	};
	char charDesc[][100] = {
	{"pirates"},{"bouken"}
	};*/

	title(choice, guess);
	
	return 0;
}

void Set_Color(int textColor, int bgColor)
{
	HANDLE h_Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h_Console,textColor | (bgColor << 4));
	//	SetConsoleTextAttribute(h_Console,FOREGROUND_INTENSITY | FOREGROUND_GREEN | (1 << 4));
}

void Set_TextColor(txtColor color)
{
	switch(color)
	{
		case RED:
		printf("\033[1;31m");
		break;
		case BLUE:
		printf("\033[1;34m");
		break;
		case YELLOW:
		printf("\033[38;5;226m");
		break;
		case GREEN:
		printf("\033[1;32m");
		break;
		case WHITE:
		printf("\033[1;37m");
		break;
		case BLACK:
		printf("\033[1;30m");
		break;
		case ORANGE:
		printf("\033[38;5;202m");	
		break;
	}
}

void title(int option, char* guess)
{
	do{
	system("cls");
//	puts("Gengshing Hangman");
	genshin_title();
	Set_Color(17,7);
	puts("1. Play!");
	puts("2. About");
	puts("3. Exit");
	puts("");
	printf("Tekan angka");
	Set_TextColor(RED);
	printf(" [1-3] ");
	Set_Color(17,7);
	printf("untuk memilih salah satu menu :\n");
	
	printf(">>");
	scanf("%d",&option);
	getchar();
		
	}while(option < 1 || option > 3);
//	printf("%d",option);
	system("cls");
	menu_display(option, guess);
}

void generate_char()
{
	strcpy(cData[0].charName,"KAEYA");
	strcpy(cData[0].charDesc,"Ini Pirate");
	strcpy(cData[1].charName,"BENNETT");
	strcpy(cData[1].charDesc,"Bouken");
	strcpy(cData[2].charName,"XINYAN");
	strcpy(cData[2].charDesc,"Kesukaan Xeno :)");
	strcpy(cData[3].charName,"DILUC");
	strcpy(cData[3].charDesc,"Batman");
	strcpy(cData[4].charName,"ZHONGLI");
	strcpy(cData[4].charDesc,"Pencipta Mora");
}

// For Randomizer Debug Result
void print_char()
{
	printf("%s\n%s\n",cData[randomNum].charName, cData[randomNum].charDesc);
}

// For Debug List Result
void print_charList()
{
	for(int i=0;i<sizeof(cData)/200;i++)
	{
		if(strlen(cData[i].charName) == 0) break;
		printf("Char %d : %s\n%s\n\n",i+1,cData[i].charName,cData[i].charDesc);
	}
}

void display_Hangman()
{
	if(lives == 3)
	{
		Set_TextColor(GREEN);
		puts("============");
		puts("||  +---+ ||");
		puts("||  |   | ||");
		puts("||      | ||");
		puts("||      | ||");
		puts("||      | ||");
		puts("||      | ||");
		puts("============");
		Set_Color(17,7);
	}
	else if(lives == 2)
	{
		Set_TextColor(YELLOW);
		puts("============");
		puts("||  +---+ ||");
		puts("||  |   | ||");
		puts("||  O   | ||");
		puts("||  |   | ||");
		puts("||      | ||");
		puts("||      | ||");
		puts("============");
		Set_Color(17,7);
	}
	else if(lives == 1)
	{
		Set_TextColor(ORANGE);
		puts("============");
		puts("||  +---+ ||");
		puts("||  |   | ||");
		puts("||  O   | ||");
		puts("|| /|\\  | ||");
		puts("||      | ||");
		puts("||      | ||");
		puts("============");
		Set_Color(17,7);
	}
	else
	{
		Set_TextColor(RED);
		puts("============");
		puts("||  +---+ ||");
		puts("||  |   | ||");
		puts("||  O   | ||");
		puts("|| /|\\  | ||");
		puts("|| / \\  | ||");
		puts("||      | ||");
		puts("============");
		Set_Color(17,7);
	}
}

void menu_display(int option, char* alphabet)
{
	switch(option)
	{
		case 1:
		menu_play(alphabet);	
		break;
		
		case 2:
		menu_about(alphabet);
		break;
		
		case 3:
		menu_exit();
		break;
	}
}

void menu_play(char* alphabet)
{
	// randomizer 0 to 4
	randomNum = rand() % 5;
	
	lives = 3;
	strcpy(wrongChar,"");
	wrongCounter = 0;
	
	
	// For Debug cData value
	//printf("%d\n",strlen(cData[randomNum].charName));
	char guess_char[strlen(cData[randomNum].charName)-1];
	//printf("%d\n",sizeof(guess_char));
	
	bool isCharExist[strlen(cData[randomNum].charName)-1];
	bool isComplete = false;
	bool isAlpha = false;
	
	convert_guesschar(guess_char,isCharExist);

do{
	//system("cls");
	do{
	strcpy(alphabet,"");
	
	// For Debug Purpose
	//printf("%d\n",isComplete);
	
	//puts("ini play!");
	printf("lives : %d\n",lives);
	printf("score : %d\n",currScore);
	space();
	display_Hangman();
	space();
	
	print_guesschar(guess_char,isCharExist);
	puts("");
	
	print_wrongchar(wrongChar,wrongCounter);
	
	puts("");
	printf("Ketik");
	Set_TextColor(RED);
	printf(" \"back\" ");
	Set_Color(17,7);
	printf("untuk kembali ke menu\n");
	
	printf(">>");
	scanf("%[^\n]",alphabet);
	getchar();
	
	isAlpha = check_alpha(alphabet);
	
	system("cls");
	
	strupr(alphabet);
	
	if(strcmp(alphabet,"BACK")== 0){
		lives = 3;
		main();	
	} 
	
	if(!isAlpha)
	{
		//alphabet[0] = '\0';
		puts("");
		puts("Ngetik yang bener bukan malah asal ngetik tod... ");
		puts("hanya boleh satu huruf dan ga boleh yang lain ngerti ga :) ?");
		puts("");
	}
	
	}while(!isAlpha);

	// Convert to Uppercase
	
	// n00b convert
	//alphabet = toupper(alphabet);
	
	// ASCII Convert
	if(alphabet[0] >= 'a' && alphabet[0] <= 'z')
	alphabet[0] = alphabet[0] - 32;
	//printf("%c",alphabet);
	
	isComplete = check_answer(guess_char, alphabet, isCharExist, isComplete);	
	
}while(lives != 0 && !isComplete);
	
	strcpy(alphabet,"");
	
	if(isComplete){
		bool isYN = false;
		char input_YN[10];
		
		do{
		strcpy(input_YN,"");
		system("cls");
		printf("score : %d\n",currScore);
		display_Hangman();
		Set_TextColor(GREEN);
		printf("YOU WIN!\n\n");
		Set_Color(17,7);
		
		printf("Nama Karakter : %s\n\n",guess_char);
		
		Sleep(500);
		view_result((enum listChar)randomNum);
		Sleep(1500);
		
		puts("");
		puts("Mau main lagi?");
		printf("Ketik");
		Set_TextColor(RED);
		printf(" [ya/tidak] ");
		Set_Color(17,7);
		printf("untuk memilih:\n\n");
		
		printf(">>");
		scanf("%s",input_YN);
		getchar();
		
		strupr(input_YN);
		
		isYN = check_YN(input_YN);
		
		}while(!isYN);
		
		if(strcmp(input_YN,"YA")==0){
			system("cls");
			menu_play(alphabet);
		} 
		else if(strcmp(input_YN,"TIDAK")==0)
		{
			system("cls");
			Set_TextColor(RED);
			puts("GAME OVER!");
			Set_Color(17,7);
			
			printf("score : %d\n",currScore);
			puts("Tulis Namamu : ");
			printf(">>");
			scanf("%[^\n]",currName);
			getchar();
			
			puts("");
			
			strcpy(pData[dataCount].playerName,currName);
			pData[dataCount].playerScore = currScore;
			
			// For Debug Purpose
			//printf("player name : %s\n",pData[dataCount].playerName);
			//printf("player score : %d\n",pData[dataCount].playerScore);
			
			dataCount++;
			
			if(dataCount-1 > 0)
			{
				sort_leaderboard();
			}
			
			print_leaderboard();
			
			puts("");
			system("pause");
			main();
		} 
		
	}
	
	else{
		bool isYN = false;
		char input_YN[10];
		
		do{
		strcpy(input_YN,"");
		system("cls");
		printf("score : %d\n",currScore);
		display_Hangman();
		Set_TextColor(RED);
		printf("YOU LOSE!\n");
		Set_Color(17,7);
		
		puts("Mau main lagi?");
		printf("Ketik");
		Set_TextColor(RED);
		printf(" [ya/tidak] ");
		Set_Color(17,7);
		printf("untuk memilih:\n\n");
		
		printf(">>");
		scanf("%s",input_YN);
		getchar();
		
		strupr(input_YN);
		
		isYN = check_YN(input_YN);
		
		}while(!isYN);
		
		if(strcmp(input_YN,"YA")==0){
			system("cls");
			menu_play(alphabet);
		} 
		else if(strcmp(input_YN,"TIDAK")==0)
		{
			system("cls");
			Set_TextColor(RED);
			puts("GAME OVER!");
			Set_Color(17,7);
			
			printf("score : %d\n",currScore);
			puts("Tulis Namamu : ");
			printf(">>");
			scanf("%[^\n]",currName);
			getchar();
			
			puts("");
			
			strcpy(pData[dataCount].playerName,currName);
			pData[dataCount].playerScore = currScore;
			
			// For Debug purpose
			//printf("player name : %s\n",pData[dataCount].playerName);
			//printf("player score : %d\n",pData[dataCount].playerScore);
			
			dataCount++;
			
			if(dataCount-1 > 0)
			{
				sort_leaderboard();
			}
			
			print_leaderboard();
			
			// File save testing
			FILE* fp;
			fp = fopen("leaderboard.txt","w");
			
			if(fp == NULL) printf("gagal");
			else 
			{
				for(int i=0;i<dataCount;i++)
				{
					fprintf(fp,"%s - %d\n",pData[i].playerName,pData[i].playerScore);
				}
				
				fclose(fp);
			}
			
			puts("");
			system("pause");
			main();
		} 
		
	}

    //printf("Duar!");
	
}

void sort_leaderboard()
{
	for(int i = 0;i<dataCount;i++)
	{
		for(int j=0;j<dataCount;j++)
		{
			if(pData[j+1].playerScore > pData[j].playerScore)
			{
				playerData temp = pData[j];
				pData[j] = pData[j+1];
				pData[j+1] = temp;
			
				//playerData temp;
				//strcpy(temp.playerName,pData[j].playerName);
				//temp.playerScore = pData[j].playerScore; 
							
				//strcpy(pData[j].playerName,pData[j+1].playerName);
				//pData[j].playerScore = pData[j+1].playerScore;
							
				//strcpy(pData[j+1].playerName,temp.playerName);
				//pData[j+1].playerScore = temp.playerScore;
			}
		}
	}
}

void print_leaderboard()
{
	printf("LeaderBoard\n");
	for(int i=0;i<dataCount;i++)
	{
		printf("Rank %d: %s - %d\n",i+1,pData[i].playerName,pData[i].playerScore);
	}
}

bool check_alpha(char* alphabet)
{
	if(strlen(alphabet) > 1) return false;
	if((alphabet[0] >= 'a' && alphabet[0] <= 'z') || (alphabet[0] >= 'A' && alphabet[0] <= 'Z') ) return true;
	return false;
}

bool check_YN(char* alphabet)
{
	if(strcmp(alphabet,"YA")==0) return true;
	else if(strcmp(alphabet,"TIDAK")== 0) return true;
	return false;
}

bool check_answer(char* guess_char, char* alphabet, bool* isCharExist, bool isComplete)
{
	bool isWrong = true;
	
	// check for wrong char
	for(int i=0;i<wrongCounter;i++)
	{
		if(alphabet[0] == wrongChar[i]){
			isWrong = false;
			break;
		}
	}
	
	// check alphabet input for guess char
	for(int i=0;i<strlen(cData[randomNum].charName);i++)
	{
		if(alphabet[0] == cData[randomNum].charName[i] && !isCharExist[i])
		{
			isCharExist[i] = true;
			guess_char[i] = alphabet[0];
			isWrong = false;
			currScore = calculate_score(currScore,isWrong);
		}
		else if(alphabet[0] == cData[randomNum].charName[i] && isCharExist[i])
		{
			isWrong = false;
			break;
		}
		else if(i == strlen(cData[randomNum].charName)-1 && alphabet[0] != cData[randomNum].charName[i] && isWrong)
		{
			lives--;
			currScore = calculate_score(currScore,isWrong);
			wrongChar[wrongCounter] = alphabet[0];
			wrongCounter++;
		}
	}
	
	if(strcmp(guess_char,cData[randomNum].charName) == 0 )
	{
		// For Debug Purpose
		//printf("MENANG!");
		isComplete = true;
	} 
	
	return isComplete;	
	
	// For Debug Purpose
//	for(int i=0;i<strlen(cData[randomNum].charName);i++)
//	{
//		printf("%c ",guess_char[i]);
//		printf("%d",isCharExist[i]);
//	}
}

int calculate_score(int score, bool isWrong)
{
	if(isWrong) score-=5;
	else if(!isWrong) score+=10;
	
	if(score < 0) score = 0;
	
	return score;
}

void convert_guesschar(char* guess_char, bool* isCharExist)
{	
//	printf("%s\n",cData[randomNum].charDesc);
//	printf("%d\n",sizeof(guess_char));
	for(int i=0;i<strlen(cData[randomNum].charName);i++)
	{
		guess_char[i] = '_';
		isCharExist[i] = false;
	}
	
}

void print_guesschar(char* guess_char, bool* isCharExist)
{
	printf("%s\n",cData[randomNum].charDesc);
	for(int i=0;i<strlen(cData[randomNum].charName);i++)
	{
		printf("%c ",guess_char[i]);
		
		// For Debug Purpose
		//printf("%d",isCharExist[i]);
	}
	
	puts("");
	//	printf("%s\n",guess_char);
}

void print_wrongchar(char* wrongChar, int count)
{
	printf("List alphabet salah : ");
	for(int i=0;i<count;i++)
	{
		printf("%c ",wrongChar[i]);
	}
	
	puts("");
}

void menu_about(char* guess)
{
	system("cls");
	choice = 0;
	KingYuan("SALAM DARI LUOFU");
	Sleep(500);
	SalamdariLuofu("Total Damage 999999\n");
	Sleep(500);
	Rama();
	
	Sleep(500);
	puts("");
	puts("==================================================================================================================");
	puts("ABOUT");
	puts("");
	puts("Game kegabutan yang dibuat oleh Xenoids, untuk mengisi waktu luang :)");
	puts("Game Hangman pada dasarnya tapi karakter gengshing (emot batu)");
	puts("");
	puts("Cara Bermain :");
	puts("Baca Clue / Deskripsi yang diberikan, jawab per 1 huruf saja");
	puts("");
	puts("~ Hoyolab / Tiktok / Youtube : Xenoids ~");
	puts("");
	
	system("pause");
	title(choice, guess);
}

void menu_exit()
{
	system("cls");
	char c1[] = "Terima kasih sudah mencoba game hangman gengshing ini :)!\n";
		for(int i=0;c1[i]!=NULL;i++)
		{
			printf("%c",c1[i]);
			for(int j=0;j<=88888888;j++);
		}
	
	char c2[] = "Semoga kalian terhibur dengan ini ^o^ b\n\n";
		for(int i=0;c2[i]!=NULL;i++)
		{
			printf("%c",c2[i]);
			for(int j=0;j<=88888888;j++);
		}
	system("pause");
	exit(0);
}

void space()
{
	puts("");
	puts("");
}

void genshin_title()
{
Set_Color(5, 12);
puts("=================================================================");
puts("                            _     _                             |");
puts("  __ _  ___ _ __   __ _ ___| |__ (_)_ __   __ _                 |");    
puts(" / _` |/ _ \\ '_ \\ / _` / __| '_ \\| | '_ \\ / _` |                |");     
puts("| (_| |  __/ | | | (_| \\__ \\ | | | | | | | (_| |                |");  
puts(" \\__, |\\___|_| |_|\\__, |___/_| |_|_|_| |_|\\__, |                |");    
puts(" |___/            |___/                   |___/                 |");     
puts("               _                                                |");    
puts("              | |__   __ _ _ __   __ _ _ __ ___   __ _ _ __     |"); 
puts("              | '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\    |");
puts("              | | | | (_| | | | | (_| | | | | | | (_| | | | |   |");
puts("              |_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|   |");
puts("                                 |___/                          |");
puts("=================================================================");
}

void view_result(listChar chara)
{
	switch(chara)
	{
		case KAEYA:
		kaeya();
		break;
		
		case BENNETT:
		bennett();
		break;
		
		case XINYAN:
		xinyan();
		break;
		
		case DILUC:
		diluc();
		break;
		
		case ZHONGLI:
		zhongli();
		break;
			
	}
}

void kaeya()
{
Set_TextColor(BLUE);
puts("	               ###                 ");
puts("                  ####  #####                ");
puts("             #################               ");
puts("          ####################               ");
puts("        ########################             ");
puts("       ######++###++############+#           ");
puts("    #  #####+++++++#############+-#          ");
puts("    ## #######-.-+############+#+-+#         ");
puts("    ########+--+++++++++++++++++++++#        ");
puts("     ####+##++++#+++++++#+#+##++##+++        ");
puts("       ##+#+++++#++++++#+##+##++##+++##      ");
puts("       #++#++++#++++++#+#++###++###++######  ");
puts("     ##+++#+++##++++++++++++##++++++++####   ");
puts(" ## ##+#+##+++##++###++++++++++++-++#        ");
puts(" ########+++++#######+--.-.+-++#+++#         ");
puts("   #########++#####+--------++##++#          ");
puts("       ######++-----+------++######          ");
puts("         #####+-------------+##+##           ");
puts("             ###+-----+----###+.+            ");
puts("              ####------+######-#            ");
puts("               ####+--+#  #######            ");
puts("                ##        #######            ");
puts("                         ######+###          ");
puts("                        ##  ###+++##         ");
puts("                            ###+##+#         ");
puts("                             ##  #           ");
Set_Color(17,7);
}

void diluc()
{
Set_TextColor(RED);
puts("	      @@@@ @@%%@@@                 ");
puts("             %%@@#%%%###%@@%@                ");
puts("           @%%%%%###%%**#**#%@               ");
puts("         @%*%%#*##****##*+*=*#@              ");
puts("        @=#*#######*#*#*+=:-#**##%@          ");
puts("   @#+-::-##**+*#*#*#**=:-+-*###@@@@%@       ");
puts("     @%:+##+==:+=-*-===+****##**#@@@%%@      ");
puts("      +-#%##**+**+#*+****##*#***##*#%@       ");
puts("      =-#%*#******#**#******#*##**#@         ");
puts("     @=+#%***##**#***#****#***%##%##@ @#%    ");
puts("     @*#*+**%##****#*=+#%*####%*#@%@@  @+#@  ");
puts("      @#+%%#%#@#**++-+*#*#*#%##*@@@#*@@**=%  ");
puts("       %-*%%#...::......+***%*###+=*%#+*+=%  ");
puts("       %-++%%=#..:......+#####***+===+#**+#  ");
puts("      %#+**++*:.......-%%+*%%@%***#=-==***%@ ");
puts("  %#==#*#      @=....=@%%@@@   #***#+==++++% ");
puts("%+%##%###         @@           @#****==+**@  ");
puts("%#%+# @%++#%@                   @****=****@  ");
puts("@#++*                          @#****%@@#%@  ");
puts("   @#*@                                 @    ");     
Set_Color(17,7);                                       
}

void xinyan()
{
Set_TextColor(RED);
puts("	      ##  ####                           ");
puts("      ###+######                 #           ");
puts("    #####++++###  ##    #        ##      ##  ");
puts("   ###+###-+######-#   ##     ######     ##  ");
puts("  ########+.+####.+    #.#######+##########  ");
puts("  +########.-+##--+    +.++##+#####+#######  ");
puts("  ##..-+####-##########+.+#+.#######+####### ");
puts("  ###+-..+#++#############..+########+#####  ");
puts("  #######-+-#########################+####   ");
puts("   #####-###+#+##########+#+.....-+##+###    ");
puts("   +..--+###+##++##+#+++###+--+####++####    ");
puts("  ####+++######+#####################++###   ");
puts("   ############+##+++######+.-#######        ");
puts("  ####+###+++--+++++++######+.+              ");
puts("    ######-+##++++###+#####++#+#             ");
puts("        ##--------..++###+##-##              ");
puts("      #####---------+##################      ");
puts("         ##+-------+################+#       ");
puts("             #+-++###              ##        ");
Set_Color(17,7);
}

void bennett()
{
Set_TextColor(RED);                                           
puts("                    &$x:.....:$              ");
puts("                $+X$;:;+;:..:$&              ");
puts("            &$$&::+x$$$X;+;..;X$     &&      ");
puts("         $+:;;;+::xX$XxX$$X$x:+;:.:+&&&      ");
puts("       $;x$$$x+XXxX$$$x$$$$$$X..+::XX&$$     ");
puts("      X:xxXX+xXX$X;:;xX$$$XxXXx;...X$&x:&    ");
puts("     $X$X$$$X$$$+:::.......::.:x+..:+:.+&    ");
puts("    &&&+$&&$$&X:..::;:........;+::....x&X$   ");
puts("     &+;+&$X+++:.......;;::...;;::...::;$    ");
puts("    &X;;+X...:+:........::::;;;++;::..:X     ");
puts("  &$+xx;+;..::;::.......:+:...:....;:.:+&    ");
puts("     $+;x....:+:::......:;+:..;.....x.::x    ");
puts("     $;;x....++:........;:.;;.;.....+;:;:X&  ");
puts("     $:;;...::.;;.......+:;+;;+::..:x::;++X  ");
puts("     $:+....;:;xXx:;...x;x$&$&$X:.:+:.;+& &&&");
puts("     $+&:..:;$XXXxx++.:;:;x++;+;::;+:;X$     ");
puts("      & $::.++++x+..:+++..:::..;:+x+++$      ");
puts("         x&x.:.....:+;:::.....:+xx+x$&&      ");
puts("         &$++x+...............:XX++X&        ");
puts("            &xx;...xxxxxXx...:++$            ");
puts("              &XX:..:xxx;..:X& $$&&          ");
puts("                  &$;....+$                  ");
puts("                     &&&&                    ");
Set_Color(17,7);
}

void zhongli()
{
//Set_TextColor(YELLOW);
printf("\e[1;33m");
puts("                     %%%%%      %@           ");
puts("                        @%+.=% %%%           ");
puts("               @%%%####*=+%#-*=+##%          ");
puts("             ######%#*+##%%%##-.-+%          ");
puts("         %+++%%#%%####%%%%%%%%%==:.+%        ");
puts("      %- ..##%%%%%%###+==#%#%%%%-#*.*%       ");
puts("        %#=*#***++*###*#%##%#*==*=-+.%%      ");
puts("        #*+*%%%%%##*#####%##%%##*+=...#      ");
puts("      @#***#%%%%%%%#######%%%%#*#+*-. :      ");
puts("     %*+**##%%#%#*####*#*#%%%%#%#*##+: +%    ");
puts(" %#+=-=***##%###*##**:.=%%%#%%######**..-%%  ");
puts("    %#-**#*#%*%*#*+..  =%%#%%#=.=#####-+     ");
puts("   %==+*##*##*#%%%#*%%.*%%%%#:. .*##*#:.%    ");
puts(" %%##%##**###*-+#-=:---%%%%*##+=-*##*-::=    ");
puts("    %###*#+*#+.    ...*%%=..=+--+###==:-:-*% ");
puts("    #*+*#*=*++.     .-+.    ..:--+*+-==%%%   ");
puts("   @#++*%#+-**-                 .+=:=%+%     ");
puts("   @%++%@ @*...        ..      .+=:*@%%      ");
puts("    %+*     ##-    ..          ..=@  @       ");
puts("    @#*     #%%+.    .....    +*#            ");
puts("     @%     @%%##:.         =##*=%           ");
puts("       %%    %%%%##:.    :*%%%#+%@           ");
puts("                   %%#=#% %   +*             ");
puts("                           %+++%             ");
puts("                           %%                ");
Set_Color(17,7);
}

void Rama()
{
puts("*******************************=-----=+=*#+#*=------=+---===+==------===-=------=#####%%%%%%%%%%%%%++*@@#*********");
puts("******************************+--=--===##+%*==----=+====-========++**+=-=+++==-----+###%%%%%%%%%@@@@%*#%#****%@@@@");
puts("***+++++++++##**##+***#+*##**+#***#****+----=======-====+===++====+=+==-=++++++===---=##%%%%++++++**##%%%%%%%#****");
puts("*+++++++++++##*####################*##*+-----===-==+-------==---+=--+=-==----=---------=#%%%*###%%%%%#+*#%%%%@@@@@");
puts("+++++++++++++++==========-----------++=---==-+=====--------+---+===----====--=------------***#######%%%*++*%***%@@");
puts("+++++=============-----------------+***=====+===+=---=-----+--==-----=++++++++=-----------==+####%%%%%%%%%%%%%#**#");
puts("+=========-------------------------=++=-==-===-+======-=---+-=++=++++----+++==+++=---------+=+%%%%%%%%%%%%%%%%%%%#");
puts("====-------------------------======*==*=====--+======--=---+-++===--=-=--+--==++==++==-----+*+#%%%%%%%%@@%%%%%%%%%");
puts("==================-----======+*****==++====--========-===-====------==+--+--==++--=+=+++===+*#*%%%%%%%%@@%%%%%%%%%");
puts("=====================+=++++=*#*+===+++=-==--+==============+==------=====+---=*=---==-====+####%%%######%@@%%%%%%%");
puts("-====================+=-==+#==-=++====+=+-=+=---====-====++-==------===+++---=+=----=-==-==+%%%%%%%%%%%%%%%%%%@%%%");
puts("-====================---=*#=-=+---==+==+=+++=-----=======+---=------==-=+=---=-=----=-=+==+=#%%%%%%%%%%%##%%#%%%%%");
puts("-=--===============-----*#+--===++=+++++++=+--=----=====+====-------+=-=+--===------===*+=+*+#####################");
puts("---------------==-----==#*+-=++===+++===+++=-=+==--====-=---=+*#%#*++=--=-=-=-=--==+++=+*==***#%%%%%%%%%%%%%%%*---");
puts("---------------=----===+**+==++*+=--==+++=+==+*====-=+*=+*##%%%###*+++=+====###++====+++**==#%%%@@@@@@@@@@@@%=---=");
puts("=------------=----=+=-======*+=====++++++=+==++++====++====--+++++-=+++===++##%*#*+%*+*+**%#=*%%%%%%%%%%%%%+----=-");
puts("=----+#=----==-======-=+===+++++***++***==+=+++++++===-===--=====----=+=+==---====-***++**###%#%#########*=----==+");
puts("=---=#@+---===+=-=+===+=+==+++++*++++++===+=+=++++====---=+=--------===+=+=-------+*#+++*#%%@@@@@@@@@@*-===---==++");
puts("----=#%+---===---+==++==+==++++*+++*+===+++=+=++++*+==+------=----++=---+==------=***#*+=+*##########*==+=---==-++");
puts("----+%%*+++++++###*++====+=+++++*****=+*+++*+==++==+++===------------------------=***+#**#####***###*=+==---=+-=++");
puts("--+%@@%%%%%%%#%%%**+=====+++++==++++=+#++++====++====+==-------------------=-----+***++#*********#+*===----=+=-=++");
puts("+%@@%%%%%%%%%%%%#*=======++*+==+++=++*+++++====++====+=------------------==-----+*****=++*++++*#+=+-==----=++---++");
puts("#@%%%%%%%%%%%#%#+======++*++==*==+++**++*+=+====+=====+=-----------------------+**+***++++++#%*+=====----=++=---++");
puts("#%%%%%%######*++++++++++**+++==++++*++**+**=====*=====+=+--------==========---+****++#*+++#%#+=-======--=++*==-==+");
puts("#%%%%%%%%#*++++++++++**+*+==+++****++***+*======+*====+===+=----------------=*++***+++#+#*#*+=--=====-==++++====++");
puts("#%%%%#*++++++++**++*+**+=+++*****+=******+======+%*===*++===+=-------------++**+#@@@++%+#@*+=-=+=======++++======+");
puts("*#****+#%###******+*++++*+******++*******========*+#==++======++---------+%++****%@@*+*+@@#=-=+-===+====++++======");
puts("-=+*##***###*****+++++********+++*******+==+=====+==++++*+=======+=-----#@%++*+=+*%@#+*@@%+===============+=======");
puts("=+++****#######*++++*********+*#********+==+======+====+*%@#=======++*@@@@#+#*+++++*#*%%%*=+======*===============");
puts("=+++*++*#####*++++********++**#+*%*##*++*+++==++=+++====+*+@@*====++*@#@=%%+#**++++#=#%@@++++=====+===============");
puts("----+**%###******#*+=======**#-*#*@=-=%++%--+%=+-+-+###*-==@=-=%+==++*@@-%#-=%#-%=#--*=@=*+======++===============");
puts("-==++**########*+++======++**%*=-=@*=-%++%+=-%-*+=%-%#%-#*=%+=-%++@=+%*%-#-%*=#-%-#=+%-@=**+===++++===============");
puts("+===*##*+=+*#**++***=+++*++**#=--+#-=-=++*-=-*-#+=%-##%+-==*-=-++*@++#*%-%==-*%-=-#=+%-=-*%#*+++++================");
puts("==*#*+===+**##*++**#%%@@@#****#%@@@@@@*++**######*#***##%#@%@%%%@%%@#*#++%@%%@@@@%#***########**++================");
}






