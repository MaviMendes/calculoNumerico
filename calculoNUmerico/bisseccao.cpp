// parametros da funcao: a e b
// teste de f(a)*f(b) <0 -> entao a e b sao validos
// funcao calcula f(x1) com base em a e b, pois x1 = (a+b)/2
// condicao de parada: se f(x1) = 0, return x1 -> raiz
// funcao f eh uma funcao separada

//casos
// f(a)*f(x1)<0 -> chama funcao com [a,x1]
//  f(a)*f(x1)>0 -> chama funcao com [x1,b]

#include <bits/stdc++.h>
using namespace std;

vector<float> raizes;
int iteracoes=1;

float f(float x)
{
   //float fx = cos(x) -x;
   float fx = pow(2,x) - 3*x;
   return fx;
}

void bisseccao(float a,float b,float erro)
{
    cout<<"***Chamada "<<iteracoes<<" da funcao bisseccao***\n"<<endl;
    iteracoes++;

    float x1 = (a+b)/2;
    cout<<"\nx1 = "<<to_string(x1)<<" - para a = "<<to_string(a)<<" e b = "<<to_string(b)<<endl;
    float testeDeParada = (b-a);
    cout<<"\nTeste de parada: b-a = "<<to_string(b)<<" - "<<to_string(a)<<" = "<<to_string(testeDeParada)<<endl;
    cout<<"\nf(a)= "<<to_string(f(a))<<endl;
    cout<<"\nf(b)= "<<to_string(f(b))<<endl;

    if((b-a)<erro)
    {
        cout<<"\nb-a<erro"<<endl;
        raizes.push_back(x1);
        return;
    }
    if(f(x1)<= pow(10,-5)) // |f(x1)| < valor pequeno (menor que o erro)  10⁻5
    {
        raizes.push_back(x1);
        cout<<"\nf(x1)=0. Raiz aproximada encontrada. x1 = "<<to_string(x1)<<endl;
    }
    if(f(a)*f(x1)<0)
    {
        cout<<"\nf(a)*f(x1)<0. [a,x1] = [ "<<to_string(a)<<","<<to_string(x1)<<"]"<<endl;
        cout<<"\nf(x1)= "<<to_string(f(x1))<<endl;
        bisseccao(a,x1,erro);
    }
    else 
    {
            cout<<"\nf(a)*f(x1)>0. [x1,b] = [ "<<to_string(x1)<<","<<to_string(b)<<"]"<<endl;
            cout<<"\nf(x1)= "<<to_string(f(x1))<<endl;
        bisseccao(x1,b,erro);
    }

}

int main()
{
    
    float a,b,erro;
    cout<<"Insira a: "<<endl;
    cin>>a;
    cout<<"Insira b: "<<endl;
    cin>>b;
    cout<<"Insira o erro: "<<endl;
    cin>>erro;
    if(f(a)*f(b)<0)
        bisseccao(a,b,erro);
    else 
        cout<<"\nInvalido. f(a)*f(b)>0."<<endl;

    cout<<"\nRaizes: "<<endl;
    for(int i = 0;i<raizes.size();i++)
        cout<<raizes[i]<<endl;

    return 0;
}
