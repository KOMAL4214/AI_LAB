#include <bits/stdc++.h>
using namespace std;
const int N = 8;
struct Result{
    vector<int> initialBoard, finalBoard;
    int initialH, finalH, steps;
    bool solved;
};
int heuristic(const vector<int>& board){
    int h=0;
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            if(board[i]==board[j])h++;
            if(abs(board[i]-board[j])==abs(i-j))h++;
        }
    }
    return h;
}
vector<int> randomBoard(){
    vector<int> board(N);
    for (int i=0;i<N;i++)
        board[i]=rand()%N;
    return board;
}
Result steepestHC(vector<int> board){
    vector<int> initialBoard=board;
    int initialH=heuristic(board);
    int steps=0;
    while(true){
        int currentH=heuristic(board);
        if (currentH==0)
            return {initialBoard, board, initialH, 0, steps, true};
        int bestH=currentH;
        vector<vector<int>>bestBoards;
        for(int col=0;col<N;col++) {
            for(int row=0;row<N;row++){
                if(board[col]==row)continue;
                vector<int>neighbor=board;
                neighbor[col]=row;
                int h=heuristic(neighbor);
                if(h<bestH){
                    bestH=h;
                    bestBoards.clear();
                    bestBoards.push_back(neighbor);
                }
                else if(h == bestH){
                    bestBoards.push_back(neighbor);
                }
            }
        }
        if(bestH>=currentH)
            return {initialBoard, board, initialH, currentH, steps, false};
        board=bestBoards[rand()%bestBoards.size()];
        steps++;
    }
}
void proveLocalMin(const Result& r) {
    int h = r.finalH;
    int better = 0, equal = 0, worse = 0;
    for (int col = 0; col < N; col++) {
        for (int row = 0; row < N; row++) {
            if (r.finalBoard[col] == row) continue;

            vector<int> neighbor = r.finalBoard;
            neighbor[col] = row;
            int nh = heuristic(neighbor);

            if (nh < h) better++;
            else if (nh == h) equal++;
            else worse++;
        }
    }
    cout << "\nLocal Minimum Proof:\n";
    cout << "Better neighbors: " << better << "\n";
    cout << "Equal neighbors : " << equal  << "\n";
    cout << "Worse neighbors : " << worse  << "\n";
    if (better == 0)
        cout << "=> LOCAL MINIMUM CONFIRMED\n";
}
int main() {
    srand(time(0));
    vector<Result> solvedList, failedList;
    cout << setw(4) << "#" 
         << setw(10) << "InitH" 
         << setw(10) << "FinalH" 
         << setw(8)  << "Steps" 
         << setw(10) << "Status\n";
    cout << string(42, '-') << "\n";
    for (int i = 0; i < 50; i++) {
        Result r = steepestHC(randomBoard());
        cout << setw(4)  << (i + 1)
             << setw(10) << r.initialH
             << setw(10) << r.finalH
             << setw(8)  << r.steps
             << setw(10) << (r.solved ? "Solved" : "Fail")
             << "\n";

        if (r.solved) solvedList.push_back(r);
        else failedList.push_back(r);
    }
    cout << "\n===== ONE SOLVED EXAMPLE =====\n";
    if (!solvedList.empty()) {
        const Result& r = solvedList[0];
        cout << "Initial h = " << r.initialH 
             << " | Steps = " << r.steps 
             << " | Final h = 0\n";
    } else {
        cout << "No solved boards found.\n";
    }
    cout << "\n===== ONE FAILED EXAMPLE =====\n";
    if (!failedList.empty()) {
        const Result& r = failedList[0];
        cout << "Initial h = " << r.initialH 
             << " | Steps = " << r.steps 
             << " | Stuck at h = " << r.finalH << "\n";
        proveLocalMin(r);
    } else {
        cout << "No failed boards found.\n";
    }
    return 0;
}