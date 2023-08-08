#include <iostream>
#include <cstring>
using namespace std;
char Pos[3][3] = {{'1', '2', '3'},
                  {'4', '5', '6'},
                  {'7', '8', '9'}};
int row;
int column;
char token = 'x';
bool tie = false;

string name1 = "";
string name2 = "";
void PrintBoard()
{

   cout << "    |       |    " << endl;
   cout << " " << Pos[0][0] << "  |   " << Pos[0][1] << "   |  " << Pos[0][2] << endl;
   cout << "    |       |    " << endl;
   cout << "----|-------|----" << endl;
   cout << "    |       |    " << endl;
   cout << " " << Pos[1][0] << "  |   " << Pos[1][1] << "   |  " << Pos[1][2] << endl;
   cout << "    |       |    " << endl;
   cout << "----|-------|----" << endl;
   cout << "    |       |    " << endl;
   cout << " " << Pos[2][0] << "  |   " << Pos[2][1] << "   |  " << Pos[2][2] << endl;
   cout << "    |       |    " << endl;
}

void updateser()
{
   int digit;
   if (token == 'x')
   {
      cout << name1 << " Please enter position" << endl;
      cin >> digit;
   }
   if (token == '0')
   {
      cout << name2 << " Please enter position" << endl;
      cin >> digit;
   }

   if (digit == 1)
   {
      row = 0;
      column = 0;
   }
   if (digit == 2)
   {
      row = 0;
      column = 1;
   }
   if (digit == 3)
   {
      row = 0;
      column = 2;
   }
   if (digit == 4)
   {
      row = 1;
      column = 0;
   }
   if (digit == 5)
   {
      row = 1;
      column = 1;
   }
   if (digit == 6)
   {
      row = 1;
      column = 2;
   }
   if (digit == 7)
   {
      row = 2;
      column = 0;
   }
   if (digit == 8)
   {
      row = 2;
      column = 1;
   }
   if (digit == 9)
   {
      row = 2;
      column = 2;
   }
   else if (digit < 1 || digit > 9)
   {
      cout << "You enter Invalid value !" << endl;
   }

   if (token == 'x' && Pos[row][column] != 'x' && Pos[row][column] != '0')
   {
      Pos[row][column] = 'x';
      token = '0';
   }
   else if (token == '0' && Pos[row][column] != 'x' && Pos[row][column] != '0')
   {
      Pos[row][column] = '0';
      token = 'x';
   }
   else
   {
      cout << "Game is Draw !" << endl;

      updateser();
   }
   PrintBoard();
}

bool checkWinner()
{
   for (int i = 0; i < 3; i++)
   {
      if (Pos[i][0] == Pos[i][1] && Pos[i][1] == Pos[i][2] || Pos[0][i] == Pos[1][i] && Pos[1][i] == Pos[2][i])
      {
         return true;
      }
   }
   if (Pos[0][0] == Pos[1][1] && Pos[1][1] == Pos[2][2] || Pos[0][2] == Pos[1][1] && Pos[1][1] == Pos[2][0])
   {
      return true;
   }

   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         if (Pos[i][j] != 'x' || Pos[i][j] != '0')
         {
            return false;
         }
      }
   }
   tie = true;
   return false;
}

int main()
{
   cout << "Enter the first Player Name : " << endl;
   getline(cin, name1);
   cout << "Enter the second Player Name : " << endl;
   getline(cin, name2);

   cout << name1 << " is Player 1 so he/she will play first" << endl;
   cout << name2 << " is Player 2 so he/she will play second" << endl;
      PrintBoard();
   while (!checkWinner())
   {
      updateser();
      checkWinner();
   }

   if (token == 'x' && tie == false)
   {
      cout << name2 << " Player win the Game " << endl;
   }
   else if (token == '0' && tie == false)
   {
      cout << name1 << " Player win the Game " << endl;
   }
   else if (tie == true)
   {
      cout << "Game is Draw!" << endl;
   }

   return 0;
}