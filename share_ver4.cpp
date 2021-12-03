#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <list>
#include <vector>
#include <fstream>
using namespace std;
string card[52] =
{
    "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10", "aJ", "aQ", "aK", "aA",
    "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "b10", "bJ", "bQ", "bK", "bA",
    "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "c10", "cJ", "cQ", "cK", "cA",
    "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "d10", "dJ", "dQ", "dK", "dA"
};
list<string> used;
list<long> numOnly;
class player
{
    public:
        string hand;
        string name;
        long value;
    bool operator > (const player& dummy) const
    {
        return (value > dummy.value);
    }
};
vector<player> flowOfPlayer (10);
vector<player> hofPlayer (99);
void initIns(long n)
{
    used.clear();
    long myRandom;
    srand(time(NULL));
    for (long h = 0; h < n; h++)
    {
        for (long i = 0; i < 5; i++)
        {
            do
            {
                myRandom = rand() % 52;
            } while (find(used.begin(), used.end(), card[myRandom]) != used.end());
            flowOfPlayer[h].hand += card[myRandom];
            flowOfPlayer[h].hand += " ";
            used.push_back(card[myRandom]);
        }
    }
}
void printCard(string ins)
{
    for (long i = 0; i < ins.length(); i++)
    {
        switch (ins[i])
        {
            case 'a':
                cout << "♦";
                break;
            case 'b':
                cout << "♣";
                break;
            case 'c':
                cout << "♥";
                break;
            case 'd':
                cout << "♠";
                break;
            default:
                cout << ins[i];
                break;
        }
    }
    cout << endl;
}
void stripFace(string ins)
{
    numOnly.clear();
    string num;
    string w = "";
    list<string> temp;
    for (long i = 0; i < ins.length(); i++)
    {
        if (ins[i] != 'a' && ins[i] != 'b' && ins[i] != 'c' && ins[i] != 'd')
            num += ins[i];
    }
    for (long i = 0; i < num.length(); i++)
    {
        if (num[i] == ' ')
        {
            temp.push_back(w);
            w = "";
        }
        else
        {
            w += num[i];
        }
    }
    list<string>::iterator itr;
    for (itr = temp.begin(); itr != temp.end(); itr++)
    {
        if (*itr == "2") numOnly.push_back(1);
        if (*itr == "3") numOnly.push_back(2);
        if (*itr == "4") numOnly.push_back(3);
        if (*itr == "5") numOnly.push_back(4);
        if (*itr == "6") numOnly.push_back(5);
        if (*itr == "7") numOnly.push_back(6);
        if (*itr == "8") numOnly.push_back(7);
        if (*itr == "9") numOnly.push_back(8);
        if (*itr == "10") numOnly.push_back(9);
        if (*itr == "J") numOnly.push_back(10);
        if (*itr == "Q") numOnly.push_back(11);
        if (*itr == "K") numOnly.push_back(12);
        if (*itr == "A") numOnly.push_back(13);
    }
}
void cHall()
{
    fstream hall;
    hall.open("HallOfFame", ios::out);
    if (!hall) cout << "Something went wrong..." << endl;
    else hall.close();
}
int rHall()
{
    fstream hall;
    int counter = 0;
    hall.open("HallOfFame", ios::in);
    while (!hall.eof())
    {
        getline(hall, hofPlayer[counter].name);
        getline(hall, hofPlayer[counter].hand);
        counter++;
    }
    hall.close();
    return counter;
}
int aHall(int counter)
{
    char response;
    do
    {
        cout << "Admit winner to hall of fame? (Y/N): ";
        cin >> response;
    } while (response != 'y' && response != 'Y' && response != 'n' && response != 'N');
    if (response == 'y' || response == 'Y')
    {
        hofPlayer[counter].name = flowOfPlayer[0].name;
        hofPlayer[counter].hand = flowOfPlayer[0].hand;
        return 1;
    }
    else return 0;
}
void wHall(int counter)
{
    fstream hall;
    hall.open("HallOfFame", ios::out);
    for (int i = 0; i < counter; i++)
    {
        hall << hofPlayer[i].name << endl;
        hall << hofPlayer[i].hand << endl;
    }
    hall.close();
}
void printMenu()
{
    system("clear");
    cout << "CARD OF FIVE" << endl;
    cout << "1. Play" << endl;
    cout << "2. Hall of fame" << endl;
    cout << "3. Exit" << endl;
}
long evaFace(string ins)
{
    string faceOnly;
    long val;
    for (long i = 0; i < ins.length(); i++)
    {
        if (ins[i] == 'a' || ins[i] == 'b' || ins[i] == 'c' || ins[i] == 'd')
            faceOnly += ins[i];
    }
    for (long i = 0; i < 5; i++)
    {
        switch (faceOnly[i])
        {
            case 'a':
                val += 1;
                break;
            case 'b':
                val += 2;
                break;
            case 'c':
                val += 3;
                break;
            case 'd':
                val += 4;
                break;
        }
    }
    return val;
}
long evaNum(list<long> l)
{
    list<long>::iterator itr;
    long counter = 1;
    long val = 0;
    for (itr = l.begin(); itr != l.end(); itr++)
    {
        val += *itr * counter * 10;
    }
    return val;
}
long evaPair(list<long> l)
{
    long flag[13];
    long numOfPair = 0;
    long pair;
    for (long i = 0; i < 13; i++)
    {
        flag[i] = 0;
    }
    list<long>::iterator itr;
    for (itr = l.begin(); itr != l.end(); itr++)
    {
        flag[*itr-1]++;
    }
    for (long i = 0; i < 13; i++)
    {
        if (flag[i] == 2)
        {
            numOfPair++;
            pair += i+1;
        }
    }
    if (numOfPair > 0) return 1000 * pair;
    return 0;
}
long evaThreeOfAKind(list<long> l)
{
    long flag[13];
    long numOfOcur = 0;
    long twin;
    for (long i = 0; i < 13; i++)
    {
        flag[i] = 0;
    }
    list<long>::iterator itr;
    for (itr = l.begin(); itr != l.end(); itr++)
    {
        flag[*itr-1]++;
    }
    for (long i = 0; i < 13; i++)
    {
        if (flag[i] == 3)
        {
            numOfOcur++;
            twin = i+1;
        }

    }
    if (numOfOcur == 1) return 100000 * twin;
    else return 0;
}
long evaStraight(list<long> l)
{
    long flag[13];
    long spree = 0;
    long lead;
    for (long i = 0; i < 13; i++)
    {
        flag[i] = 0;
    }
    list<long>::iterator itr;
    for (itr = l.begin(); itr != l.end(); itr++)
    {
        flag[*itr-1]++;
    }
    for (long i = 0; i < 13; i++)
    {
        if (flag[i] == 1) spree++;
        else spree = 0;
        if (spree == 5)
        {
            lead = i+1;
            break;
        }
    }
    if (spree == 5) return 10000000 * lead;
    else return 0;
}
long evaFlush(string ins)
{
    long flagFace[4];
    for (long i = 0; i < 4; i++)
    {
        flagFace[i] = 0;
    } 
    for (long i = 0; i < ins.length(); i++)
    {
        switch (ins[i])
        {
        case 'a':
            flagFace[0]++; 
            break;
        case 'b':
            flagFace[1]++; 
            break;
        case 'c':
            flagFace[2]++; 
            break;
        case 'd':
            flagFace[3]++; 
            break;
        }
    }
    for (long i = 0; i < 4; i++)
    {
        if (flagFace[i] == 5) return 1000000000;
    }
    return 0;
}
long evaFullHouse()
{
    if (evaPair(numOnly) > 0 && evaThreeOfAKind(numOnly) > 0)
        return 10000000000;
    else return 0;
}
long evaFourOfAKind(list<long> l)
{
    long flag[13];
    long numOfOcur = 0;
    long twin;
    for (long i = 0; i < 13; i++)
    {
        flag[i] = 0;
    }
    list<long>::iterator itr;
    for (itr = l.begin(); itr != l.end(); itr++)
    {
        flag[*itr-1]++;
    }
    for (long i = 0; i < 13; i++)
    {
        if (flag[i] == 4)
        {
            numOfOcur++;
            twin = i+1;
        }
    }
    if (numOfOcur == 1) return 1000000000000 * twin;
    return 0;
}
long evaRoyalFlush(string ins)
{
    if (ins == "a10 aJ aQ aK aA " || ins == "b10 bJ bQ bK bA " || ins == "c10 cJ cQ cK cA " || ins == "d10 dJ dQ dK dA ")
        return 10000000000000000;
    return 0;
}
long noPlayer()
{
    long num;
    do
    {
        cout << "Please enter number of player (max. 10): ";
        cin >> num;
    } while (!(num > 0) || !(num <= 10));
    for (long i = 0; i < num; i++)
    {
        cout << "Please enter name of player " << i+1 << ": ";
        cin >> flowOfPlayer[i].name;
    }
    return num;
}
int main()
{
    //cHall();
    int option;
    long noOfHofPlayer;
    do
    {
        noOfHofPlayer = rHall();
        printMenu();
        cout << "Enter your command: ";
        cin >> option;
        if (option == 1)
        {
            long noOfPlayer = noPlayer();
            system("clear");
            initIns(noOfPlayer);
            for (long i = 0; i < noOfPlayer; i++)
            {
                numOnly.clear();
                stripFace(flowOfPlayer[i].hand);
                if (evaFlush(flowOfPlayer[i].hand) > 0)
                    flowOfPlayer[i].value = evaFlush(flowOfPlayer[i].hand) + evaStraight(numOnly) + evaRoyalFlush(flowOfPlayer[i].hand);
                else
                    flowOfPlayer[i].value = evaFace(flowOfPlayer[i].hand) + evaNum(numOnly) + evaPair(numOnly) + evaThreeOfAKind(numOnly) + evaStraight(numOnly) + evaFullHouse() + evaFourOfAKind(numOnly);
            }
            sort(flowOfPlayer.begin(), flowOfPlayer.end(), greater<player>());
            for (long i = 0; i < noOfPlayer; i++)
            {
                cout << flowOfPlayer[i].name;
                if (i == 0) cout << " WINNER!" << endl;
                else cout << endl;
                printCard(flowOfPlayer[i].hand);
            }
            int admitted = aHall(noOfHofPlayer);
            if (admitted > 0)
            {
                noOfHofPlayer++;
                wHall(noOfHofPlayer);
            }
            for (int i = 0; i < noOfPlayer; i++)
            {
                flowOfPlayer[i].name = "";
                flowOfPlayer[i].hand = "";
                flowOfPlayer[i].value = 0;
            }
        }
        if (option == 2)
        {
            system("clear");
            if (noOfHofPlayer <= 2)
                cout << "Hall of fame is empty!" << endl;
            else
            {
                cout << "HALL OF FAME" << endl;
                for (int i = 0; i < noOfHofPlayer; i++)
                {
                    if (i % 2 == 1)
                        cout << (i+1)/2 << ". ";
                    cout << hofPlayer[i].name << " ";
                    printCard(hofPlayer[i].hand);
                }
            }
            cout << "Enter YES to continue: ";
            string input;
            cin >> input; 
        }
    } while (option != 3);
    return 0;
}