#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

set <string> seen;

struct board_node {
  string charc;
  int value;
};

struct node {
  int row, col;
  string word;
  vector < vector <board_node> > board;
  int value;
};

bool operator<(const node &leftNode, const node &rightNode) {
  if (leftNode.value != rightNode.value) return leftNode.value > rightNode.value;
  return true;
}

int rowd[] = { 1, 1, -1, -1, 0, 0, 1, -1 };
int cold[] = { 1, -1, -1, 1, 1, -1, 0, 0 };

bool is_valid(int row, int col, vector < vector <board_node> > board) {
  if( row >= 0 && col >= 0 && row < board.size() && col < board.size() ) return true;
  return false;
}

void kick_off(int row, int col, vector < vector <board_node> > board, set <string> words) {
  node root;
  root.row = row;
  root.col = col;
  root.word = board[row][col].charc;
  root.value = board[row][col].value;
  board[row][col].charc = "";
  root.board = board;

  priority_queue <node> q;
  q.push(root);

  while(!q.empty())
  {
    node cur = q.top();
    q.pop();

    if(words.find(cur.word) != words.end())
    {
      if(seen.find(cur.word) == seen.end())
      {
        seen.insert(cur.word);
        cout << cur.word << endl;
      }
    }

    for(int i = 0; i < 8; i++)
    {
      int tRow = cur.row + rowd[i];
      int tCol = cur.col + cold[i];

      if( is_valid(tRow, tCol, board) && cur.board[tRow][tCol].charc != "" )
      {
        node n;
        n.row = tRow;
        n.col = tCol;
        n.word = cur.word + cur.board[tRow][tCol].charc;
        n.value = cur.value + cur.board[tRow][tCol].value;
        n.board = cur.board;
        n.board[tRow][tCol].charc = "";

        if(words.find(n.word) != words.end())
        {
          if(seen.find(n.word) == seen.end())
          {
            seen.insert(n.word);
            cout << n.word << endl;
          }
        }

        q.push(n);
      }
    }
  }
}

void print_solutions(vector < vector <board_node> > board, set <string> word_list)
{
  for(int i = 0; i < board.size(); i++)
  {
    for(int j = 0; j < board.size(); j++)
    {
      kick_off(i, j, board, word_list);
    }
  }
}

int main()
{
  set <string> word_list;
  string line;
  ifstream myfile ("/usr/share/dict/words");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      word_list.insert(line);
    }
    myfile.close();
  }

  vector <board_node> t(4);
  vector < vector <board_node> > board(4, t);

  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
    {
      string charc;
      int value;

      cin >> charc >> value;

      board_node new_board_node;
      new_board_node.charc = charc;
      new_board_node.value = value;

      board[i][j] = new_board_node;
    }

  print_solutions(board, word_list);

  return 0;
}
