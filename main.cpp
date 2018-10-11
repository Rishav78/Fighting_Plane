#include <iostream>
#include<conio.h>
#include<windows.h>
#include<vector>
#include<time.h>
using namespace std;

int z=0;

class Moving
{
    char **border;
    int m,n; //STAGE
    int herox,heroy; // x and y co-ordinate of fighting plane
    vector<int> bulletx,bullety;//jijuuju
    int prevx,prevy;
    vector<int> enemyx,enemyy;
    int flag;
public:
    int score;
    Moving()
    {
        flag=0;
        score=0;
        cin >> m >> n;
        border = new char*[m];
        for(int i=0;i<m;i++)
        {
            border[i] = new char[n];
        }
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i==0 || j==0 || i==(m-1) || j==(n-1))
                {
                    border[i][j]='#';
                }
                else
                {
                    border[i][j]=' ';
                }
            }
        }
    }
    void move_enemy()
    {
        for(int i=0;i<enemyx.size();i++)
        {
            border[enemyx[i]][enemyy[i]]=' ';
            if(++enemyx[i]==(n-1))
            {
                cout << endl << "GAME OVER" << endl;
                throw 1;
            }
            border[enemyx[i]][enemyy[i]]='e';
        }
    }
    void generate_enemy()
    {
        srand(++z);
        if(rand()%2==0 && flag!=2)
        {
            ++flag;
            int x;
            for(int i=0;i<rand()%(n/3);i++)
            {
                enemyx.push_back(1);
                srand(++z);
                if(x=rand()%(n-1)){}
                else{x=1;}
                enemyy.push_back(x);
                border[1][x]='e';
            }
        }
        else
        {
            flag=0;
        }
    }
    void kill_enemy()
    {
        for(int i=0;i<bulletx.size();i++)
        {
            for(int j=0;j<enemyx.size();j++)
            {
                if(bulletx[i]==enemyx[j] && bullety[i]==enemyy[j])
                {
                    score=score+5;
                    enemyx.erase(enemyx.begin()+j);
                    enemyy.erase(enemyy.begin()+j);
                }
            }
        }
    }
    void Draw_ob()//FIGHTING PLANE
    {
        herox = prevx = m-2;
        heroy = prevy = n/2;
        border[herox][heroy]='^';
    }
    void start()//MOVE FIGHTING PLANE
    {
        border[herox][heroy]=' ';
        if(kbhit())
        {
            switch(getch())
            {
            case 'a':
                {
                    if(heroy>1)
                    {
                        --heroy;
                    }
                    break;
                }
            case 'd':
                {
                    if(heroy<(n-2))
                    {
                        ++heroy;
                    }
                    break;
                }
            case 'p':
                {
                    system("pause");
                }
            }
        }
        border[herox][heroy]='^';
    }
    void bullet()
    {
        border[prevx][prevy]=' ';
        for(int i=0;i<bulletx.size();i++)
        {
            if(bulletx[i]<2)
            {
                border[bulletx[i]][bullety[i]]=' ';
                bulletx.erase(bulletx.begin()+i);
                bullety.erase(bullety.begin()+i);
            }
            else if(bulletx[i]!=bulletx[i+1])
            {
                border[bulletx[i]][bullety[i]]=' ';
                --bulletx[i];
                border[bulletx[i]][bullety[i]]='|';
            }
            else
            {
                --bulletx[i];
                border[bulletx[i]][bullety[i]]='|';
            }
        }
        border[herox-1][heroy]='|';
        bulletx.push_back(herox-1);
        bullety.push_back(heroy);
        prevx=herox-1;
        prevy=heroy;
    }
    void Draw()
    {
        system("cls");
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout << border[i][j];
            }
            cout << endl;
        }
    }
    ~Moving()
    {
        delete border;
    }
};

int main()
{
    int x=3,dup=0;
    Moving obj;
    obj.Draw_ob();
    while(true)
    {
        try
        {
            obj.Draw();
            obj.start();
            obj.bullet();
            if(++dup==x)
            {
                x=x+3;
                obj.generate_enemy();
                obj.move_enemy();
            }
            obj.kill_enemy();
            Sleep(50);
        }
        catch(int i)
        {
            break;
        }
    }
    cout << "SCORE: " << obj.score;
    return 0;
}
