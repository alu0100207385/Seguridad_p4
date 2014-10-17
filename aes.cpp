#include "aes.hpp"

//Esta representado por bloques de 128bits
AES::AES(void)
{
  bitset<BITS> a;
  for (unsigned i=0;i<MAX;i++)
  {
       m.push_back(a);
       k.push_back(a);
       est_int.push_back(a);
  }
  inicializa_rcon();
  control=0;
}

vector<Num2> AES::inicializa_sbox(void)
{
  vector<Num2> sbox;
  unsigned int s[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
  };

  unsigned fin= (MAX*16);
  for (unsigned i=0;i<fin;i++)
  {
      bitset<MAX> a(s[i]);
      sbox.push_back(a);
  }
  return sbox;
}


void AES::inicializa_rcon(void)
{
  unsigned int MatrizRcon[40] = {
    0x01,0x00,0x00,0x00,
    0x02,0x00,0x00,0x00,
    0x04,0x00,0x00,0x00,
    0x08,0x00,0x00,0x00,
    0x10,0x00,0x00,0x00,
    0x20,0x00,0x00,0x00,
    0x40,0x00,0x00,0x00,
    0x80,0x00,0x00,0x00,
    0x1b,0x00,0x00,0x00,
    0x36,0x00,0x00,0x00
  };
  for (unsigned i=0;i<40;i++)
  {
      bitset<MAX> a(MatrizRcon[i]);
      rcon.push_back(a);
  }
}

string AES::get_m_bin(void)
{
  stringstream mystring;
  for (unsigned i=0;i<MAX;i++)
    mystring << m[i].to_string<char,std::string::traits_type,std::string::allocator_type>()<<" ";
  return mystring.str();
}

string AES::get_k_bin(void)
{
  stringstream mystring;
  for (unsigned i=0;i<MAX;i++)
    mystring << k[i].to_string<char,std::string::traits_type,std::string::allocator_type>()<<" ";
  return mystring.str();
}


string AES::get_k_hex (void)
{
  stringstream salida;
/*  for (unsigned i=0; i<MAX; i++)
    salida<<hex<<k[i].to_ulong();*/
 for (unsigned i=0; i<MAX; i++)
  {
    vector<int> v1,v2;
    for (int j=(BITS-1); j>3; j--)
      v1.push_back(k[i][j]);
    salida<<hex<<to_decimal(v1);

    for (int j=3; j>-1; j--)
      v2.push_back(k[i][j]);
    salida<<hex<<to_decimal(v2);
  }
  return salida.str();
}


string AES::get_m_hex (void)
{
  stringstream salida;
/*  for (unsigned i=0; i<MAX; i++)
    salida<<hex<<m[i].to_ulong();*/
  for (unsigned i=0; i<MAX; i++)
  {
    vector<int> v1,v2;
    for (int j=(BITS-1); j>3; j--)
      v1.push_back(m[i][j]);
    salida<<hex<<to_decimal(v1);

    for (int j=3; j>-1; j--)
      v2.push_back(m[i][j]);
    salida<<hex<<to_decimal(v2);
  }
  return salida.str();
}


string AES::get_est_int_hex (void)
{
  stringstream salida;
  for (unsigned i=0; i<MAX; i++)
  {
    vector<int> v1,v2;
    for (int j=(BITS-1); j>3; j--)
      v1.push_back(est_int[i][j]);
    salida<<hex<<to_decimal(v1);

    for (int j=3; j>-1; j--)
      v2.push_back(est_int[i][j]);
    salida<<hex<<to_decimal(v2);
  }
  return salida.str();
}

string AES::get_round_key_hex (void)
{
  stringstream salida;
  for (unsigned i=0; i<MAX; i++)
    salida<<hex<<round_key[i].to_ulong();
  return salida.str();
}

/*
string AES::get_sbox_hex(void)
{
  unsigned fin= (MAX*16);
  stringstream salida;
  for (unsigned i=0; i<fin; i++)
  {
    salida<<hex<<sbox[i].to_ulong()<<" ";
    if ((i+1)%MAX==0)
      salida<<"\n";
  }
  return salida.str();
}
*/

//Introducir el valor del mensaje a traves de cadena
void AES::set_m(string input)
{
  int t=0;
  string cad;
  for (unsigned i=0;i<MAX;i++)
  {
      for (unsigned j=t;j<(BITS+t);j++)
	cad+=input[j];
      t+=BITS;
      bitset<BITS> set(cad);
      cad.clear();
      m[i] = set.to_ulong();
  }
}

//Introducir el valor de la clave a traves de cadena
void AES::set_k(string input)
{
  int t=0;
  string cad;
  for (unsigned i=0;i<MAX;i++)
  {
      for (unsigned j=t;j<(BITS+t);j++)
	cad+=input[j];
      t+=BITS;
      bitset<BITS> set(cad);
      cad.clear();
      k[i] = set.to_ulong();
  }
}


int AES::to_dec (char e)
{
  switch (e)
  {
    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    case 'A': case 'a':
      return 10;
    case 'B': case 'b':
      return 11;
    case 'C': case 'c':
      return 12;
    case 'D': case 'd':
      return 13;
    case 'E': case 'e':
      return 14;
    case 'F': case 'f':
      return 15;
//     default:
//       break;
  }
}


string AES::hexstr_to_binstr (string cad)
{
    //cada caracter lo tngo q pasar a binario
    stringstream aux;
    for (unsigned i=0; i<(MAX*2);i++)
       aux<<to_binary(to_dec(cad[i]),4).get_s();
    return aux.str();
}


int AES::cargar_fichero (char fichero[])
{
  ifstream flujo;
  flujo.open(fichero);
  if (flujo.is_open())
  {
    string aux_k, aux_m;
    flujo>>aux_m;
    flujo>>aux_k;
    if ((aux_k.size()!=MAX*2)||(aux_m.size()!=MAX*2))//Error, no son 4x4=16*2=32
      return 1;
    set_m(hexstr_to_binstr(aux_m));
    set_k(hexstr_to_binstr(aux_k));
    round_key = k;
    flujo.close();
    return 0;
  }
  else
    return 1;
}


int AES::to_decimal (vector<int> &v)
{
  int b[] = {8,4,2,1};
  int r=0;
  for (unsigned i=0; i<v.size(); i++)
    if (v[i]==1)
      r+=b[i];
  return r;
}

void AES::AddRoundKey (void)
{
  for (unsigned i=0; i<MAX; i++)
     est_int[i]= m[i]^k[i];
}

void AES::AddRoundKey2 (void)
{
    RoundKey();
    for (unsigned i=0; i<MAX; i++)
       est_int[i]= est_int[i]^round_key[i];
}

void AES::SubBytes(void)
{
  vector<Num2> sbox = inicializa_sbox();
  //cogemos el valor del AddRoundKey, por casilla, su 1er valor=col cajaS
  //2o valor= fil caja S. Su correspondencia sera su nuevo valor.

  for (unsigned i=0; i<MAX;i++)
  {
    bitset<4> aux1,aux2;
    int n=3;
    for (int j=7; j>-1;j--)
    {
	if (n<0)
	  n=3;
	if (j>3)
	  aux1.set(n,est_int[i][j]);
	else
	  aux2.set(n,est_int[i][j]);
	n--;
    }
    int fil= aux1.to_ulong();
    int col= aux2.to_ulong();
    est_int[i] = resize(sbox[col+MAX*fil]);
  }
//   cout<<"SubBytes= "<<get_est_int_hex()<<endl;
}

//Pasa de 16bits a 1byte
bitset<BITS> AES::resize (bitset<MAX> &v)
{
  bitset<BITS> b;
  for (int i=(BITS-1); i>-1; i--)
    b[i] = v[i];
  return b;
}


void AES::ShiftRow (void)
{
  //La fila 0 no se rota
  bitset<BITS> swap;
  swap= est_int[1];
  for (int i=1; i<10;i+=4) //La fila 1 se rota una vez
    est_int[i]= est_int[i+4];
  est_int[13]= swap;

  for (int j= 0; j<2; j++)   //La fila 2 se rota dos veces
  {
    swap= est_int[2];
    for (int i=2; i<11; i+=4)
       est_int[i]= est_int[i+4];
    est_int[14]= swap;
  }

  for (int j= 0; j<3; j++)   //La fila 3 se rota una veces
  {
    swap= est_int[3];
    for (int i=3; i<12; i+=4)
       est_int[i]= est_int[i+4];
    est_int[15]= swap;
  } 
//   cout<<"ShiftRow= "<<get_est_int_hex()<<endl;
}


void AES::MixColumn (void)
{
  vector<Num> base,tmp;
  const unsigned int v[MAX] = {
    0x02,0x03,0x01,0x01,
    0x01,0x02,0x03,0x01,
    0x01,0x01,0x02,0x03,
    0x03,0x01,0x01,0x02
  };

  for (unsigned i=0;i<MAX;i++) //Creamos la matriz base: 020301...
      base.push_back(v[i]);
  
  int x=0;
  for (unsigned v=0; v<4; v++)
  {
      vector<Num> r,aux;
      bitset<BITS> a;

      for (unsigned i=x; i<(x+4); i++)
      {
	aux.push_back(est_int[i]); //tomamos la 1a col de est_int
	r.push_back(a);
      }
      x+=4;
  
      int k=0;
      bitset<BITS> mod(0x1b);//Lo usaremos para el mod (xor 1B)
      for (unsigned i=0;i<4;i++)
      {
	for (unsigned j=0;j<4;j++)
	{
	    a.reset();
	    a = aux[j];
	    if (base[k].to_ulong() == 2)
	    {
	      a = rodar_bit (aux[j]);
	      if (aux[j][BITS-1]==1) //se desborda y aplicamos el mod
		a = a^mod;
	    }
	    if (base[k].to_ulong() == 3)
	    {
	      a = rodar_bit (aux[j]);
	      if (aux[j][BITS-1]==1) //se desborda y aplicamos el mod
		a = a^mod;
	      a = a^(aux[j]);
	    }
	    r[i] = r[i]^a;
	    k++;
	}
      }
      for (unsigned i=0; i<4; i++)
	tmp.push_back(r[i]);
  }
//   cout<<"Tmp= ";
//   for (unsigned i=0; i<tmp.size(); i++)
//     cout<<hex<<tmp[i].to_ulong();
//   cout<<endl;
  est_int = tmp;	//actualizamos el est_int
//   cout<<"MixColumn= "<<get_est_int_hex()<<endl;
}


bitset<BITS> AES::rodar_bit (bitset<BITS> a)
{
  for (int i = (BITS-1); i>-1; i--)
    a[i] = a[i-1];
  a[0]=0;
  return a;
}


void AES::RoundKey (void)
{ 
  vector<Num> tmp;
  vector<Num2> sbox= inicializa_sbox();
  
  for (unsigned i=12; i<(MAX-1); i++)
    tmp.push_back(round_key[i+1]);
  tmp.push_back(round_key[12]);
   
  for (unsigned i=0; i<tmp.size();i++)
  {
    bitset<4> aux1,aux2;
    bitset<BITS> tmp2;
    int n=3;
    for (int j=7; j>-1;j--)
    {
	if (n<0)
	  n=3;
	if (j>3)
	  aux1.set(n,tmp[i][j]);
	else
	  aux2.set(n,tmp[i][j]);
	n--;
    }
    int fil= aux1.to_ulong();
    int col= aux2.to_ulong();
    tmp2 = resize(sbox[col+MAX*fil]);
    tmp[i]= tmp2;
  }

  vector<Num> resul;
  for (int i=0; i<MAX; i++)
  {
    if (i<4)
      resul.push_back(round_key[i]^tmp[i]^resize(rcon[i+control]));
    else
      resul.push_back(round_key[i]^resul[i-4]);
  }
  control+=4;
  round_key = resul;
//   cout<<"RoundKey= "<<get_round_key_hex()<<endl;
}
