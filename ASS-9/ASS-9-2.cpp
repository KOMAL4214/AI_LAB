#include <bits/stdc++.h>
using namespace std;

char board[3][3] = {
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
};

string indent(int depth)
{
    return string(depth * 3, ' ');
}

void printMiniBoard(int depth)
{
    for(int i=0;i<3;i++)
    {
        cout << indent(depth);
        for(int j=0;j<3;j++)
            cout << (board[i][j]==' ' ? '.' : board[i][j]) << " ";
        cout << "\n";
    }
}

int evaluate()
{
    for(int i=0;i<3;i++)
    {
        if(board[i][0]==board[i][1] &&
           board[i][1]==board[i][2] &&
           board[i][0]!=' ')
            return (board[i][0]=='X') ? 10 : -10;

        if(board[0][i]==board[1][i] &&
           board[1][i]==board[2][i] &&
           board[0][i]!=' ')
            return (board[0][i]=='X') ? 10 : -10;
    }

    if(board[0][0]==board[1][1] &&
       board[1][1]==board[2][2] &&
       board[0][0]!=' ')
        return (board[0][0]=='X') ? 10 : -10;

    if(board[0][2]==board[1][1] &&
       board[1][1]==board[2][0] &&
       board[0][2]!=' ')
        return (board[0][2]=='X') ? 10 : -10;

    return 0;
}

bool movesLeft()
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]==' ')
                return true;
    return false;
}

int countStates(bool isMax)
{
    int score = evaluate();

    if(score == 10 || score == -10)
        return 1;

    if(!movesLeft())
        return 1;

    int total = 0;

    if(isMax)
    {
        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='X';
                total += countStates(false);
                board[i][j]=' ';
            }
        }
    }
    else
    {
        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='O';
                total += countStates(true);
                board[i][j]=' ';
            }
        }
    }

    return total;
}

int alphaBeta(bool isMax, int alpha, int beta)
{
    int score = evaluate();

    if(score == 10 || score == -10)
        return score;

    if(!movesLeft())
        return 0;

    if(isMax)
    {
        int best = -1000;

        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='X';
                best = max(best, alphaBeta(false, alpha, beta));
                board[i][j]=' ';

                alpha = max(alpha, best);
                if(beta <= alpha)
                    return best;
            }
        }
        return best;
    }
    else
    {
        int best = 1000;

        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='O';
                best = min(best, alphaBeta(true, alpha, beta));
                board[i][j]=' ';

                beta = min(beta, best);
                if(beta <= alpha)
                    return best;
            }
        }
        return best;
    }
}

pair<int,int> bestMoveWithTree(int depth)
{
    int bestVal = 1000;
    pair<int,int> best = {-1,-1};

    vector<pair<int,int>> allMoves;

    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
        if(board[i][j]==' ')
            allMoves.push_back({i,j});

    for(auto m : allMoves)
    {
        board[m.first][m.second]='O';
        int val = alphaBeta(true, -1000, 1000);
        board[m.first][m.second]=' ';

        if(val < bestVal)
        {
            bestVal = val;
            best = m;
        }
    }

    board[best.first][best.second]='O';
    int states = countStates(true);
    board[best.first][best.second]=' ';

    cout << indent(depth)
         << "└── AI ("<<best.first<<","<<best.second<<") "
         << "[States: " << states << "]\n";

    board[best.first][best.second]='O';
    printMiniBoard(depth);

    for(auto m : allMoves)
    {
        if(m != best)
        {
            cout << indent(depth+1)
                 << "├── AI ("<<m.first<<","<<m.second<<") (PRUNED)\n";
        }
    }

    board[best.first][best.second]=' ';

    return best;
}

int main()
{

    int depth = 0;

    while(true)
    {
        int r,c;
        cout<<"Enter row and column (0-2): ";
        cin>>r>>c;

        if(board[r][c]!=' ') continue;

        board[r][c]='X';

        int states = countStates(false);

        cout << indent(depth)
             << "YOU ("<<r<<","<<c<<") "
             << "[States: " << states << "]\n";

        printMiniBoard(depth);

        if(evaluate()==10 || !movesLeft())
            break;

        auto ai = bestMoveWithTree(depth+1);

        board[ai.first][ai.second]='O';

        depth += 2;

        if(evaluate()==-10 || !movesLeft())
            break;
    }

    int result = evaluate();

    if(result==10) cout<<"\nYou Win!\n";
    else if(result==-10) cout<<"\nAI Wins!\n";
    else cout<<"\nDraw!\n";
}