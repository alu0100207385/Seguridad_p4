//ALUMNO: Aaron Socas Gaspar
//Seguridad curso 2013-2014
//Practica 4: Rijndael (AES)
//Recursos: http://www.cs.bc.edu/~straubin/cs381-05/blockciphers/rijndael_ingles2004.swf

#include "aes.hpp"

bool check_fich (char fichero[])
{
    ifstream flujo;
    flujo.open(fichero);
    if (flujo.is_open())
    {
	flujo.close();
	return true;
    }
    else
      return false;
}


int main (int argc, char* argv[])
{
  if (argc==2)
  {
      if (check_fich(argv[1]))
      {
	cout<<"Fichero cargado: "<<argv[1]<<endl;
	AES r;

	if (r.cargar_fichero(argv[1])==0)
	{
// 	  cout<<"Texto= "<<r.get_m_bin()<<endl;
// 	  cout<<"Clave= "<<r.get_k_bin()<<endl;
// 	  cout<<"Sbox: "<<r.get_sbox_hex()<<endl;
	  cout<<"Clave: "<<r.get_k_hex()<<endl;
	  cout<<"Texto: "<<r.get_m_hex()<<endl;
	  r.AddRoundKey();
	  cout<<"R0 (Subclave = "<<r.get_round_key_hex()<<") = "<<r.get_est_int_hex()<<endl;
	  
	  for (int i=1; i<10; i++)
	  {
	    r.SubBytes();
	    r.ShiftRow();
	    r.MixColumn();
	    r.AddRoundKey2();
	    cout<<"R"<<i<<" (Subclave = "<<r.get_round_key_hex()<<") = "<<r.get_est_int_hex()<<endl;
	  }
	  r.SubBytes();
	  r.ShiftRow();
	  r.AddRoundKey2();
	  cout<<"R10 (Subclave = "<<r.get_round_key_hex()<<") = "<<r.get_est_int_hex()<<endl;
	  cout<<"\nTexto cifrado = "<<r.get_est_int_hex()<<endl;
	  
	  return 0;
	}
	else
	{
	  cout<<"Error de lectura del fichero. Formato incorrecto."<<endl;
	  return 3;
	}
      }
      else
      {
	  cout<<"Error en la carga del fichero, compruebe nombre y/o ruta."<<endl;
	  return 2;
      }
  }
  else
  {
      cout<<"Error de argumentos. Introduzca ./aes nombre_fichero"<<endl;
      return 1;
  }
}