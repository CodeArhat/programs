#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

void open_dst_file(const string &src_dir, const string &file_name, int n_file, const string &ext_name, ofstream & ofs)
{
  ostringstream oss;
  oss << src_dir << file_name << '_' << setw(4) << setfill('0') << n_file << ext_name;

  ofs.close();
  ofs.open(oss.str().c_str());
  if(!ofs){
    cerr << "can not open taget file: " << oss.str() << endl;
    exit(1);
  }
}

int main(int argc, const char *argv[])
{
  if(argc < 5){
    cerr << "wzTxtSplitter <max_lines_per_file> <src_dir> <src_file> <ext>" << endl;
    cerr << "example: wzTxtSplitter  100  demo_dir/  demo_src_file  .txt" << endl;
    return 1;
  }

  istringstream iss(argv[1]);
  int line_limit = 0;
  if(!(iss >> line_limit) || line_limit <= 0){
    cerr << "argument <max_lines_per_file> should greater than zero." << endl;
    return 1;
  }

  string src_dir(argv[2]);
  string file_name(argv[3]);
  string ext_name(argv[4]);
  string src_path = src_dir + file_name + ext_name;
  ifstream ifs(src_path.c_str());
  if(!ifs){
    cerr << "can not open source file: " << src_path << endl;
    return 1;
  }

  int n_file = 0;
  int n_line = 0;
  ofstream ofs;
  open_dst_file(src_dir, file_name, n_file, ext_name, ofs);
  for(string s; getline(ifs, s); ){
    ofs << s << '\n';
    ++n_line;
    if(n_line >= line_limit){
      ++n_file;
      n_line = 0;

      open_dst_file(src_dir, file_name, n_file, ext_name, ofs);
    }
  }
  ofs.close();
  return 0;
}
