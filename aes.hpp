#include <sstream>
#include <bitset>
#include "mias.hpp"

const unsigned MAX=16;
const unsigned BITS=8;

typedef bitset<BITS> Num;
typedef bitset<MAX> Num2;

class AES
{
  private:
    vector<Num> k,m, est_int, round_key;
    vector<Num2> rcon;
    unsigned control;
    int to_dec(char e);
    int to_decimal (vector<int> &v);
    bitset<BITS> resize (bitset<MAX> &v);
    bitset<BITS> rodar_bit (bitset<BITS> a);
    vector<Num2> inicializa_sbox(void);
    void inicializa_rcon(void);
    void RoundKey (void);
  public:
    AES(void);
    inline ~AES(){};
    int cargar_fichero (char fichero[]);
    string get_m_bin(void);
    string get_k_bin(void);
    string get_m_hex (void);
    string get_k_hex (void);
    string get_round_key_hex (void);
//     string get_sbox_hex(void);
    string get_est_int_hex (void);
    void set_m(string input);
    void set_k(string input);
    string hexstr_to_binstr (string cad);
    void AddRoundKey (void);
    void AddRoundKey2 (void);
    void SubBytes(void);
    void ShiftRow (void);
    void MixColumn (void);
};
