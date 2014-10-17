#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class pause
{
public:
  pause(string m="<Pulse una tecla para continuar>")
  {
      cout<<m<<endl;
      cin.get();//   cin.get();
  }
  inline ~pause(){};
};


namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
	FG_ORANGE   = 33,
        FG_BLUE     = 34,
	FG_VIOLET   = 35,
	FG_AQUAMARINE = 36,
	FG_BLUESKY  = 37,
        FG_DEFAULT  = 39,

        BG_RED      = 41,
        BG_GREEN    = 42,
	BG_ORANGE   = 43,
        BG_BLUE     = 44,
	BG_VIOLET   = 45,
	BG_AQUAMARINE = 46,
	BG_BLUESKY  = 47,
        BG_DEFAULT  = 49,
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}


class to_binary{
private:
  vector<int> v;
  //Pasa un entero a binario
  void to_bin(int n)
  {
      int d = n;
      if (n > 1)
      {
	  d = n % 2;
	  to_bin(n / 2);
      }
      v.push_back(d);
  }
public:
  //Pasa un entero a binario y rellena el byte completo de '0' si fuera necesario
  to_binary (int n,int bits=8)
  {
      to_bin(n);
      v.insert(v.begin(),(bits-v.size()),0);
  }
  inline ~to_binary(){};
  vector<int> get(void){return v;}
  string get_s(void)
  {
      stringstream aux;
      for (unsigned i=0;i<v.size();i++)
	  aux<<v[i];
      return aux.str();
  }
};


unsigned DH::exp_rap2 (unsigned base, unsigned exp, unsigned m)
{
  //P1
  bitset<BITS> b(exp);
  //P2
  unsigned r=1;
  //P3
  for (int i=(BITS-1); i>-1; i--)
  {
    r=(r*r)%m;
    if (b[i]==1)
      r=(r*base)%m;
  }
  return r;
}