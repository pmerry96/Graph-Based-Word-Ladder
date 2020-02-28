#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <queue>
using namespace std;

//maybe use adjacency lists

void fill_word_vector(string filename);
void search(string source_node);
bool adjacent(string a, string b);
void printpath(string t, vector<string> &path);
//typedef pair<string, int> state;

unordered_map<string, bool> visited;         // have we queued up this state for visitation?
unordered_map<string, string> pred;           // predecessor state we came from
unordered_map<string, int> dist;             // distance (# of hops) from source node
unordered_map<string, vector<string>> nbrs;
vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type

//Implement breadth-first search, refer to Lab 10

void wordLadder(string s, string t, int &steps, vector<string> &p)
{
	fill_word_vector("wordlist05.txt");//hardcode bc easier
	//Stringset wordmap = Stringset(V, s); //so this will make a map with
										//everything 1 letter off from the
										//strings s
	//cout << "filled V\n";
	//cout << "made map\n";
	for (int i = 0; i < V.size(); ++i) {
		for(int j = i + 1; j < V.size(); j++)
		{
			if(adjacent(V[i], V[j])) {
				nbrs[V[i]].push_back(V[j]);
				nbrs[V[j]].push_back(V[i]);
			}
		}
	}
	//cout << "compared \n";
	//wordmap is created here
	//do a breadth first search here
	search(s); //populates predecessor
	//cout << endl << pred.size() << endl << dist.count(t) << endl;
	steps = dist[t];
	printpath(t, p);
}

void printpath(string t, vector<string> &path)
{
	if(pred.count(t) == 1)
	{
		printpath(pred[t], path);
	}
	path.push_back(t);
}

//just work with this when correcting first
void search(string source_node)
{
	queue<string> to_visit;
	to_visit.push(source_node);
	//visited[source_node] = true;
	dist[source_node] = 0;
	while (!to_visit.empty()) {
		string curnode = to_visit.front();
		to_visit.pop();
		for (auto &n : nbrs[curnode])
			if (dist.count(n) == 0) {
				to_visit.push(n);
				dist[n] = 1 + dist[curnode];
				pred[n] = curnode;
				//visited[n] = true;
			}
	}
}
//reads from file and into V, is good!
void fill_word_vector(const string filename)
{
	//this will read in from wordlist05.txt and place in V
	string line;
	fstream StringFile(filename);
	//sizecount will ONLY hold the indexable values
	//also holds (#lines - 1)
	//if #sizecount = -1, stringset is empty
	while (StringFile >> line) {
		V.push_back(line);
	}
	//already removed all from the file
	StringFile.close();
}

//I trust this code as well
bool adjacent(string a, string b)
{
	int count = 0;
	for(int i = 0; i < 5; i++) //all words 5 letters
	{
		if(a[i] != b[i]) //check letter by letter for diff
			count++;
		if(count > 1)
			return false; //no more than one diff allowed
	}
	return count == 1;
}
//provided test driver
int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;
  
  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);
	cout << "wordLadder complete\n";
  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (int i=0; i<path.size(); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}
