/* "Connect Four" game implementation template (C) Akira Kawaguchi April,2016.

 This program is to implement a simplified minimax-style intelligence by
 evaluating board situation. Only I/O interface is shown below. Any addition
 of method and new classes is allowed.
 */
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

struct MyGameDef { // professional way to define global enumerable values.
    enum Player { Human, Progm, Empty };
    Player m_player;
    MyGameDef (const Player p) : m_player(p) {}
    operator Player() const { return m_player; }
};

class Cell {       // representing a cell of a board.
    MyGameDef::Player m_occu; // marked 'Empty', 'Human', and 'Progm'.
public:
    Cell() : m_occu(MyGameDef::Empty) {}
    void setTurn(const MyGameDef::Player p) { assert(!isOccupied()); m_occu = p; }
    bool isOccupied() const { return m_occu != MyGameDef::Empty; }
    bool isMe(const MyGameDef::Player p) const { return m_occu == p; }
    void erase() { m_occu = MyGameDef::Empty; }
    friend ostream& operator<<(ostream& o, const Cell& c) {
        char mark;
        switch(c.m_occu) {
            case MyGameDef::Empty: return o << " . ";
            case MyGameDef::Human: return o << " o ";
            case MyGameDef::Progm: return o << " x ";
            default: abort();
        }
    }
};

class Eval {
    int m_conn; // connected to me.
    int m_poss; // possible spaces.
public:
    Eval(const int c = 0, const int p = 0) : m_conn(c), m_poss(p) {}
    bool isConnect4() const { return m_conn >= 3; }
    bool isWinning()  const { return m_conn == 2 && m_poss >= 1; }
    int getValue()  const { return m_conn * 2 + m_poss; }
    int getm_conn() {return m_conn;}
    int getm_poss() {return m_poss;}
    friend ostream& operator<<(ostream& o, const Eval& e) {
        return o << "(" << e.m_conn << ", " << e.m_poss << ")";
    }
};

class Turn {
    char m_turn;
    int  m_score;
public:
    Turn(const char c = '\0', const int s = 0) : m_turn(c), m_score(s) {}
    char getTurn() const { return m_turn; }
    int getScore() const { return m_score; }
    friend bool operator<(const Turn& lhs, const Turn& rhs) {
        return lhs.m_score < rhs.m_score;
    }
    friend ostream& operator<<(ostream& o, const Turn& t) {
        return o << "\t--> (" << t.m_turn << ") with score " << t.m_score;
    }
};

class Board {       // represents Connect Four board.
    int m_row;
    int m_col;
    const int m_max;  // used to detect tie.
    int m_num;        // the number of the marks placed.
    vector<vector<Cell> > m_map;

    Eval vertical(const int r, const int c, const MyGameDef::Player p) const {
        int count = 0, possible = 0;
        bool connected = true;
        for (int row = r + 1, saw = 0; row < m_row && saw < 3; ++row, ++saw) { // up direction.
            if (m_map[row][c].isMe(p)) {
                if (++count > 2) { if (connected) break; }
                continue;
            }
            connected = false;
            if (m_map[row][c].isOccupied()) break;
            ++possible;
        }
        for (int row = r - 1, saw = 0; row >= 0 && saw < 3; --row, ++saw) { //down direction.
            if (m_map[row][c].isMe(p)) {
                if (++count > 2) { if (connected) break; }
                continue;
            }
            connected = false;
            if (m_map[row][c].isOccupied()) break;
            ++possible;
        }
    //    cout << "Count in Eval vertical fucntion is " << count << endl;
    //    cout << "Poss in Eval vertical function is " << possible << endl;
        return Eval(count, possible);
    }

    Eval horizontal(const int r, const int c, const MyGameDef::Player p) const {
        int count = 0, possible = 0;
        bool connected = true;
        for (int col = c + 1, saw = 0; col < m_col && saw < 3; ++col, ++saw) { // east direction.
            if (m_map[r][col].isMe(p)) {
                if (++count > 2) { if (connected) break; }
                continue;
            }
            connected = false;
            if (m_map[r][col].isOccupied()) break;
            ++possible;
        }
        for (int col = c - 1, saw = 0; col >= 0 && saw < 3; --col, ++saw) { // west direction.
            if (m_map[r][col].isMe(p)) {
                if (++count > 2) { if (connected) break; }
                continue;
            }
            connected = false;
            if (m_map[r][col].isOccupied()) break;
            ++possible;
        }
        return Eval(count, possible);
    }
    Eval leftup(const int r, const int c, const MyGameDef::Player p) const {
        int count = 0, possible = 0;
        bool connected = true;
        for (int col = c - 1, row = r - 1, saw = 0; col >= 0 && row >=0 && saw < 3; --col,--row, ++saw) { // left up direction
            if (m_map[row][col].isMe(p)) {
                if (++count > 2) { if (connected) break; }
                continue;
            }
            connected = false;
            if (m_map[row][col].isOccupied()) break;
            ++possible;
        }
    //    cout << "Connected in leftup direction " << count << endl;
        for (int col = c + 1, row = r + 1 , saw = 0; row < m_row && col < m_col && saw < 3; ++col,++row, ++saw) { // right down direction.
            if (m_map[row][col].isMe(p)) {
                if (++count > 2) { if (connected) break; }
                continue;
            }
            connected = false;
            if (m_map[row][col].isOccupied()) break;
            ++possible;
        }
    //    cout << "connected in rightdown direction " << count << endl;

        return Eval(count, possible);
    }
    Eval rightup(const int r, const int c, const MyGameDef::Player p) const {
        int count = 0, possible = 0;
        bool connected = true;
        for (int col = c + 1, row = r - 1, saw = 0; col < m_col && row >= 0 && saw < 3; ++col,--row, ++saw) { // right up direction.
            if (m_map[row][col].isMe(p)) {
                if (++count > 2) { if (connected) break; }
                continue;
            }
            connected = false;
            if (m_map[row][col].isOccupied()) break;
            ++possible;
        }
        for (int col = c - 1, row = r + 1 , saw = 0; row <  m_row && col >= 0 && saw < 3; --col,++row, ++saw) { // left down direction.
            if (m_map[row][col].isMe(p)) {
                if (++count > 2) { if (connected) break; }
                continue;
            }
            connected = false;
            if (m_map[row][col].isOccupied()) break;
            ++possible;
        }

        return Eval(count, possible);
    }

public:
    Board(const int r = 6, const int c = 7) :
    m_row(r), m_col(c), m_max(r * c), m_num(0) {
        vector<Cell> arow(m_col, Cell());
        for (int i = 0; i < m_row; ++i) m_map.push_back(arow);
    }
    bool isTie() const { return m_num >= m_max; }
    bool isValid(const char c, const MyGameDef::Player p) {
        int col = c - 'a';
        if (col < 0 || col >= m_col) return false;
        bool placed = false;
        for (int row = m_row - 1; row >= 0; --row) {
            if (m_map[row][col].isOccupied()) continue;

            placed = true;
            ++m_num;
            m_map[row][col].setTurn(p); break;
        }
        return placed;
    }

    bool isWon(const char c, const MyGameDef::Player p) const {
        int col = c - 'a', row = 0;
        for (; row < m_row; ++row) {
            if (!m_map[row][col].isOccupied()) continue;

            assert(m_map[row][col].isMe(p));
            break;
        }
        Eval V = vertical(row, col, p); // check vertical line.
       // cout << "In is won vecrtical conn " << V.getm_conn() << endl;
        Eval H = horizontal(row, col, p); // check horizontal line.
       // cout << "In is won Horrizontal conn " << H.getm_conn() << endl;
        Eval L = leftup(row, col, p);     // check leftup diagnal line.
       // cout << "In is won Left conn " << L.getm_conn() << endl;
        Eval R = rightup(row, col, p);    // check rightup diagnal line.
       // cout << "In is won Rigth conn " << R.getm_conn() << endl;
        return V.isConnect4() || H.isConnect4() || L.isConnect4() || R.isConnect4();
    }
    char findBestMove(const MyGameDef::Player p, const bool show = false) {
        char c = 'a';
        int col = c - 'a';
        char best = ' ';
        int bestScore = 0;


        for(int cl = 0; cl < m_col; ++cl)// go through each column, i = column
        {
            for(int r = m_row - 1 ; r >= 0 ; --r)
            {
               // cout << "Current Position being searched (col , row) (" << cl << " , " << r << ")" << endl;
                if(m_map[r][cl].isOccupied())
                { //cout << "Possition (col , row) is occupied (" << cl << " , " << r << ")" << endl;
                    continue;
                }
                int score = 2;
                //score += getScore(r, cl, p);

                Eval V = vertical(r, cl, p);   // check vertical line.
                Eval H = horizontal(r, cl, p); // check horizontal line.
                //cout << "Human H(1.3) " << H(1,3,MyGameDef::Human) << "\n" << "Program H(1,3) " << H(1,3,MyGameDef::Progm) << "\n";
                //vertical(0,0,MyGameDef::Progm).getValue() +
                Eval L = leftup(r, cl, p);     // check leftup diagnal line.
                Eval R = rightup(r, cl, p);    // check rightup diagnal line
                score += V.getValue() + H.getValue() + L.getValue() + R.getValue();
                score += Addscore(V) + Addscore(H) + Addscore(L) + Addscore(R);
                //cout << "Score is " << score << endl;
                //cout << "show is " << show << endl;
                if(show && p == MyGameDef::Human)
                {
                    cout << "If you chose (" << char(cl + 'a') << ") - H " << H << ", V " << V << ", L " << L << ", R " << R << ", total score " << getScore(r,cl,MyGameDef::Human) << endl;
                }

                if(!show && p == MyGameDef::Progm) // changed human to progm
                {
                    cout << "If machine chose (" << char(cl + 'a') << ") - H " << H << ", V " << V << ", L " << L << ", R " << R << ", total score " << getScore(r,cl,MyGameDef::Progm) << endl;
                }
                if(score > bestScore)
                {	bestScore = score;
                    best = 'a' + cl;
                   // cout << "Your best move is " << best;
                  //  cout << "The Best column is " << best << endl;
                }
                break;
            }
        }
        if(show && p == MyGameDef::Human)
        {	findBestMove(MyGameDef::Progm,false); // just added here
        	cout << "\n Your best move for you is " << best << endl;}
            return best;

    }


    int getScore(int r, int cl, MyGameDef::Player p)
    {   int score = 2;
        Eval V = vertical(r, cl, p);   // check vertical line.
        Eval H = horizontal(r, cl, p); // check horizontal line.
        Eval L = leftup(r, cl, p);     // check leftup diagnal line.
        Eval R = rightup(r, cl, p);    // check rightup diagnal line
        score += V.getValue() + H.getValue() + L.getValue() + R.getValue();
        score += Addscore(V) + Addscore(H) + Addscore(L) + Addscore(R);
        return score;
    }
    int Addscore(Eval O)
    { int addscore = 0;
        if(O.isWinning())
        {return addscore += 50;}
        else if (O.isConnect4())
        {return addscore += 100;}
        else
            return 0;
    }

    void erase(const char c, const MyGameDef::Player p) {
        int col = c - 'a';
        for (int row = 0; row < m_row; ++row) {
            if (!m_map[row][col].isOccupied()) continue;

            assert(m_map[row][col].isMe(p));
            m_map[row][col].erase(); break;
        }
        --m_num;
    }
    friend ostream& operator<<(ostream& o, const Board& m) {
        o << endl;
        for (int col = 0; col < m.m_col; ++col)
            o << setw(3) << (char)('a' + col) << ' ';
        o << endl;
        for (int row = 0; row < m.m_row; ++row) {
            o << '|';
            for (int col = 0; col < m.m_col; ++col)
                o << setw(3) << m.m_map[row][col] << '|';
            o << endl;
        }
        o << endl;
        return o;
    }
};

int main() {
    Board b(6, 7); // traditional size Connect Four game.
    while (!b.isTie()) {
        cout << b;   // showing board status.
        cout << "Enter your turn: "; char turn; cin >> turn; turn = tolower(turn);
        if (turn == '?') { b.findBestMove(MyGameDef::Human, true); continue; }

        while (!b.isValid(tolower(turn), MyGameDef::Human)) {
            cout << "Invalid input, try again: "; cin >> turn;
        }
        if (b.isWon(turn, MyGameDef::Human)) {
            cout << "You won :)";
            break;
        }
        turn = b.findBestMove(MyGameDef::Progm, true);//changed show from true to false for machine's turn
        if (!b.isValid(tolower(turn), MyGameDef::Progm)) {
            cout << "Serious error occurred, program cannot continue..." << endl;
            abort();
        }
        if (b.isWon(turn, MyGameDef::Progm)) {
            cout << "You lost :(";
            break;
        }
    }
    if (b.isTie()) cout << "Tied..." << endl;
    cout << " Final board is" << endl << b << "Bye..." << endl;
    return 0;
}
