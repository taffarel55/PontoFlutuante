/*----------------------------------------------------------|
| UFBA - Universidade Federal da Bahia                      |
| Trabalho: CIRCUITS 1.0                                    |
|                                                           |
| O programa simula um circuito RLC em Série e em Paralelo  |
| (Resistor Indutor Capacitor) através de métodos iterativos|
|                                                           |
| Além disso, simula como seriam essas contas em uma máquina|
| com configurações definidas no inicio do programa         |
|                                                           |
| Alunos: Breno Amim, Geraldo Junior e Mauricio Taffarel    |
|----------------------------------------------------------*/

#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

/*----------------------------------------------------------|
|             Variáveis Globais do Programa                 |
|----------------------------------------------------------*/
double R,L,C,A,B,x0,x1; // Constantes Físicas do Circuito
double pol[3],ri[2];    // Componentes de equação
short opcCircuito,      // Flag de controle
opcMetodo,              // Flag de controle
opcAproximacao;         // Flag de controle
int q,t,i,s;            // Parâmetros da Máquina
double a,b,c,d,e;       // Intervalos das raízes
int ex;                 // Expoente do número


/*----------------------------------------------------------|
|             Exibição de desenhos com ASCII Art            |
|----------------------------------------------------------*/
void title() {
  cout<<" ___________________________________"<<endl;
  cout<<"|       _                _ _        |"<<endl;
  cout<<"|      (_)              (_) |       |"<<endl;
  cout<<"|   ___ _ _ __ ___ _   _ _| |_ ___  |"<<endl;
  cout<<"|  / __| | '__/ __| | | | | __/ __| |"<<endl;
  cout<<"| | (__| | | | (__| |_| | | |_\\__ \\ |"<<endl;
  cout<<"|  \\___|_|_|  \\___|\\__,_|_|\\__|___/ |"<<endl;
  cout<<"|___________________________________|\n"<<endl;

  cout<<"\nO programa calcula a resposta natural de um circuito RLC série ou paralelo\n"<<endl;

  cout<<"            R       L      C"<<endl;
  cout<<"   _____/\\/\\/\\/\\___⌒⌒⌒____| |____"<<endl;
  cout<<"  |                       | |    |"<<endl;
  cout<<"__|__                            |"<<endl;
  cout<<" ---- V                          |"<<endl;
  cout<<"  |                              |"<<endl;
  cout<<"  |                              |"<<endl;
  cout<<"  |______________________________|"<<endl;
  cout<<"                SERIE\n"<<endl;

  cout<<"   ______________________________"<<endl;
  cout<<"  |          |        |          |"<<endl;
  cout<<"  |          \\        |_         |"<<endl;
  cout<<"__|__        /         _)       ---"<<endl;
  cout<<" ---- V      \\ R       _)  L    --- C"<<endl;
  cout<<"  |          /         _)        |"<<endl;
  cout<<"  |          \\         |         |"<<endl;
  cout<<"  |__________|_________|_________|"<<endl;
  cout<<"              PARALELO"<<endl;
}

/*----------------------------------------------------------|
|     Leitura de dados R,L,C,V,I e da opção do circuito     |
|----------------------------------------------------------*/
void lerDados() {

  do {
    cout<<"_____________________________________"<<endl;
    cout<<"\nO circuito está em série ou paralelo?\n1) Série \n2) Paralelo\n\nOpção: ";
    cin>>opcCircuito;
  } while (opcCircuito!=1 && opcCircuito!=2);
  
	cout<<"\nInsira o valor de R: ";
	cin>>R;
	cout<<"Insira o valor de L: ";
	cin>>L;
	cout<<"Insira o valor de C: ";
	cin>>C;

  cout<<"\nInsira o valor de x(0): ";
  cin>>x0;
  cout<<"Insira o valor de x'(0): ";
	cin>>x1;


  pol[2]=1;
  if (opcCircuito==1) {
    pol[1]=R/L;
    pol[0]=1.0/(L*C);
  } else {
    pol[1]=1.0/(R*C);
    pol[0]=1.0/(L*C);
  }
}

/*----------------------------------------------------------|
|           Leitura do método Newton ou Secante             |
|----------------------------------------------------------*/
void lerMetodo() {
  do {
    cout<<"_____________________________________"<<endl;
    cout<<"\nO método usado é Newton ou Secantes? \n1) Newton \n2) Secantes\nOpção: ";
    cin>>opcMetodo;
  } while (opcMetodo!=1 && opcMetodo!=2);
}

/*----------------------------------------------------------|
|           Leitura das configurações da máquina            |
|----------------------------------------------------------*/
void lerMaquina() {
  cout<<"_____________________________________"<<endl;
  cout<<"\nAgora defina os parâmetros da máquina!\n"<<endl;
  do {
    cout<<"Insira a mantissa da máquina: ";
    cin>>t;
  } while (t<0);
  do {
    cout<<"\nDefina os limites do expoente:"<<endl;
    cout<<"Insira o limite inferior: ";
    cin>>i;
    cout<<"Insira o limite superior: ";
    cin>>s;
  } while(abs(i)>8 || abs(s)>8 || i>=s);
}

/*----------------------------------------------------------|
|              Leitura do Tipo de Aproximacao               |
|----------------------------------------------------------*/
void lerAproximacao() {
  cout<<"_____________________________________"<<endl;
  cout<<"\nO tipo de aproximacao é Truncamento ou Arrendondamento? \n1) Truncamento \n2) Arrendondamento\nOpção: ";
  do cin>>opcAproximacao; while (opcAproximacao!=1 && opcAproximacao!=2);
}

/*----------------------------------------------------------|
|                   Calcula Discriminante                   |
|----------------------------------------------------------*/
double delta() {
  return pow(pol[1],2) - 4*pol[0];
}

/*----------------------------------------------------------|
|               Calcula valor da função no ponto            |
|----------------------------------------------------------*/
double f(double x) {
  return pow(x,2) + pol[1]*x + pol[0];
}

/*----------------------------------------------------------|
|       Calcula valor da derivada da função no ponto        |
|----------------------------------------------------------*/
double ddx(double x) {
  return 2*x + pol[1];
}

/*----------------------------------------------------------|
|            Leitura de configurações da maquina            |
|----------------------------------------------------------*/
void lerConfiguracoes() {
  int p=1;
  cout<<"____________________________________"<<endl;
  cout<<"\nO polinômio característico é: D²+"<<pol[1]<<"D+"<<pol[0]<<endl;
  if(delta()<0) {
    q=0;
  } else {
    cout<<"_____________________________________"<<endl;
    cout<<"\nInsira o intervalo da primeira raiz [a,b]\na = ";
    cin>>a;
    cout<<"b = ";
    cin>>b;
    if (f(a)*f(b)==0) {
      if(f(a)==f(b)) {
        ri[0] = a;
        ri[1] = b;
      } else if(f(a)==0) {
        ri[0] = a;
      } else ri[0] = b;
    }
    if(delta()==0) {
      p=0;
      q=1;
    }
    while (p && ((f(a)*f(b)>0) || ddx((a+b)/2)>0)) {
      cout<<"\nInsira o intervalo válido da primeira raiz [a,b]"<<endl;
      cout<<"a = ";
      cin>>a;
      cout<<"b = ";
      cin>>b;
    }
    if (delta()!=0) {
      q=2;
      cout<<"\nInsira o intervalo da segunda raiz [c,d]\nc = ";
      cin>>c;
      cout<<"d = ";
      cin>>d;
      if (f(c)*f(d)==0) {
        if(f(c)==f(d)) {
          ri[0] = c;
          ri[1] = d;
        } else if(f(c)==0) {
          ri[1] = c;
        } else ri[1] = d;
      }
      while(f(c)*f(d)>0 || (ddx((a+b)/2)*ddx((c+d)/2))>0 )  {
        cout<<"\nInsira o intervalo válido da segunda raiz [c,d]"<<endl;
        cout<<"c = ";
        cin>>c;
        cout<<"d = ";
        cin>>d;
      }
    }  
  }
  cout<<"____________________________________"<<endl;
  cout<<"\nInsira o valor da precisão E: ";
  cin>>e;
}

/*----------------------------------------------------------|
|          Leitura de todas Entradas do Programa            |
|----------------------------------------------------------*/
void lerEntradas() {
  title();
  lerDados();
  lerMetodo();
  lerMaquina();
  lerAproximacao();
  lerConfiguracoes();
}

/*----------------------------------------------------------|
|        Escolha de um X0 para aplicaçãp do método          |
|----------------------------------------------------------*/
double converge(double a, double b, int n) {
  int i=2;
  double x=(a+b)/2, y;
  if (n==2) {
    y=a;
    a=b;
    b=y;
  } 
  while(ddx(x)==0 || f(x)<0) {
    x=((pow(2,i)-1)*a + b)/pow(2,i);
    i++;
  }
  return x;
}

/*----------------------------------------------------------|
|  Escolha de um X1 para aplicaçãp do método da secante     |
|----------------------------------------------------------*/
double convergir(double x) {
  if (ddx(x)<0) {
    return x-5;
  } else return x+5;
}

/*----------------------------------------------------------|
|            Função retorna o sinal de um número            |
|----------------------------------------------------------*/
int sinal (double x) {
  if(x>=0) return 1;
  else return -1;
}

int arredondar(double x) {
  if (x-int(x)>=0.5) return int(x)+1;
  else return int(x);
}

/*----------------------------------------------------------|
|    Converte o valor em x em configurações da máquina      |
|----------------------------------------------------------*/
double converter(double x) {
  int j=0, p=sinal(x);
  x=abs(x);
  if (x==0) return 0;
  else if(x>=1) while((x*pow(10,--j)>=1));
  else if (x<0.1) while(x*pow(10,(++j))<0.1);
  ex = -j;
  x=x*pow(10,j);
  if (ex<i) {
    cout<<"Underflow!\nPor favor reinicie o programa e simule uma máquina com capacidade representação de valores menores que este"<<endl;
    exit(EXIT_FAILURE);
  } else if(ex>s) {
    cout<<"Overflow! Por favor reinicie o programa e simule uma máquina com capacidade de representação de valores maiores que este"<<endl;
    exit(EXIT_FAILURE);
  }
  
  if (opcAproximacao==1) x=int(x*pow(10,t))/pow(10,t);
  else x=arredondar(x*pow(10,t))/pow(10,t);
  if (x==1) {
    x=0.1;
    ex++;
  }
  return p*x;
}

/*----------------------------------------------------------|
| Calcula o valor de x de uma iteração do Método de Newton  |
|----------------------------------------------------------*/
double newton(double x) {
  if(ddx(x)==0) return x;
  else return x - f(x)/ddx(x);
}

/*----------------------------------------------------------|
|  Realiza o Método de Newton com valores simulados e reais |
|----------------------------------------------------------*/
void metodoNewton(double u, double h,int l) {
  cout<<"_____________________________________\n"<<endl;
  cout<<"Raiz "<<l<<":"<<endl;
  double y=converge(u,h,l);
  double w=converter(y)*pow(10,ex);
  cout<<"x0 = "<<y<<"\t\tx0 = "<<converter(w)<<"x10^"<<ex<<endl;
  double z=newton(y);
  double r=converter(newton(w))*pow(10,ex);
  cout<<"x1 = "<<z<<"\t\tx1 = "<<converter(r)<<"x10^"<<ex<<endl;
  int k=2;
  while(abs(z-y)>e) {
    y=z;
    z=newton(z);
    w=r;
    r=converter(newton(r))*pow(10,ex);
    cout<<"x"<<k<<" = "<<z<<"\t\tx"<<k<<" = "<<converter(r)<<"x10^"<<ex<<endl;
    k++;
  }
  cout<<"\nRaíz real x = "<<z<<endl;
  cout<<"Raíz encontrada x = "<<r<<endl;
  ri[l-1]=r;
}

/*----------------------------------------------------------|
|Calcula o valor de x de uma iteração do Método das Secantes|
|----------------------------------------------------------*/
double secante(double x, double y) {
  if (f(x)==f(y)) return x; 
  else return x - (f(x)*((x-y)))/(f(x)-f(y));
}

/*----------------------------------------------------------|
| Realiza o Método da Secante com valores simulados e reais |
|----------------------------------------------------------*/
void metodoSecante(double a, double b, int l) {
  cout<<"_____________________________________\n"<<endl;
  cout<<"Raiz "<<l<<":"<<endl;
  double q,w,r,t,x,y,aux;
  r=converge(a,b,l); 
  q=convergir(r);    
  x=secante(r,q);    
  w=converter(q);
  cout<<"x0 = "<<q<<"\t\tx0 = "<<w<<"x10e^"<<ex<<endl;
  w*=pow(10,ex);
  t=converter(r);
  cout<<"x1 = "<<r<<"\t\tx1 = "<<t<<"x10e^"<<ex<<endl;
  t*=pow(10,ex);
  y=converter(x);
  cout<<"x2 = "<<x<<"\t\tx2 = "<<y<<"x10e^"<<ex<<endl;
  y*=pow(10,ex);
  int k=3;
  while (abs(r-x)>=e) {
    q=r;
    r=x;
    x=secante(r,q);
    w=t;
    t=y;
    y=converter(secante(t,w));
    cout<<"x"<<k<<" = "<<x<<"\t\tx"<<k<<" = "<<y<<"x10e^"<<ex<<endl;
    y*=pow(10,ex);
    k++;
  }
  ri[l-1]=y;
}

void programa() {
  lerEntradas();
  if (q==0) {
    cout<<"_____________________________________\n"<<endl;
    cout<<"\nA solução é complexa! O sistema é subamortecido"<<endl;
    cout<<"\nA resposta do sistema é:"<<endl;
    if(opcCircuito==1) {
      cout<<"\n\ni(t)= e^-"<<R/2.0<<"t ("<<ri[0]<<"cos("<<(1/(L*C) - pow((R/2.0),2))<<"t))"<<endl;
    } else {
      cout<<"\n\nv(t)= e^-"<<1.0/(2*R*C)<<"t ("<<ri[0]<<"cos("<<(1/(L*C) - pow((1.0/(2*R*C)),2))<<"t))"<<endl;
    }
  } 
  
  else if(q==1) {
    cout<<"_____________________________________\n"<<endl;
    cout<<"\nA solução admite uma raíz real! O sistema é crítico"<<endl;
    if (opcMetodo==1) {
      metodoNewton(a,b,1);
    } else {
      metodoSecante(a,b,1);
    }
    cout<<"\nA resposta do sistema é:\n"<<endl;
    if(opcCircuito==1) {
      cout<<"\n\ni(t)="<<x0<<"e^"<<ri[0]<<"t + "<<x1-x0*ri[0]<<"te^"<<ri[0]<<"t"<<endl;
    } else {
      cout<<"\n\nv(t)="<<x0<<"e^"<<ri[0]<<"t + "<<x1-x0*ri[0]<<"te^"<<ri[0]<<"t"<<endl;
    }
  }
  
  else {
    cout<<"_____________________________________\n"<<endl;
    cout<<"\nA solução admite duas raízes reais! O sistema é sobreamortecido"<<endl;
    if (opcMetodo==1) {
      metodoNewton(a,b,1);
      metodoNewton(c,d,2);
    } else {
      metodoSecante(a,b,1);
      metodoSecante(c,d,2);
    }
    cout<<"\nA resposta do sistema é:"<<endl;
    if(opcCircuito==1) {
      cout<<"\n\ni(t)="<<(x0*ri[1]-x1)/(ri[1]-ri[0])<<"e^"<<ri[0]<<"t + "<<(x1*ri[0]-x0)/(ri[1]-ri[0])<<"e^"<<ri[1]<<"t"<<endl;
    } else {
      cout<<"\n\nv(t)="<<(x0*ri[1]-x1)/(ri[1]-ri[0])<<"e^"<<ri[0]<<"t + "<<(x1*ri[0]-x0)/(ri[1]-ri[0])<<"e^"<<ri[1]<<"t"<<endl;
    }
  }
  cout<<endl;
  cout<<endl;
}

// ------------------  Função Principal  --------------------
int main() {
  programa();
  return 0;
}