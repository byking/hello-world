#include <iostream>
#include <gflags/gflags.h>
#include <ctime>

DEFINE_string(input, "", "input");

using namespace std;

vector<int> split(string str, char a) {
  vector<int> strvec;
  string::size_type pos1, pos2;
  pos2 = str.find(a);
  pos1 = 0;
  while (string::npos != pos2) {
    strvec.push_back(stoi(str.substr(pos1, pos2 - pos1)));
    pos1 = pos2 + 1;
    pos2 = str.find(a, pos1);
  }
  strvec.push_back(stoi(str.substr(pos1)));
  return strvec;
}


//LCG a = 1103515245, c = 12345, m = 2^31 
static unsigned int seed = 1;
void set_seed (int newseed) {
    seed = (unsigned int)newseed & 0x7fffffff;
}
int gen_rand (void) {
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return (int)seed;
}


int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  cout << "get input: " << FLAGS_input << endl;

  vector<int> input_numbers = split(FLAGS_input, ',');  

  int i = 0;
  unsigned int newseed = 0;  
  for(vector<int>::iterator it = input_numbers.begin(); it != input_numbers.end(); it++) {
    newseed |= *it << (i * 8); 
    i++;
  }
  set_seed(newseed);
  cout << gen_rand()%2000 << endl;

  return 0;
}
