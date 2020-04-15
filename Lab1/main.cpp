#include <iostream>
#include <pthread.h>

using namespace std;
struct data{int X0,a,c,m,N;};

class LKG
{
public:
	LKG(data par):tid(0), param(par){}
	~LKG(){}

	static void* calc(void *temp)
	{
		LKG* cur=reinterpret_cast<LKG*>(temp);
		return cur->schet(cur);
	}

	void* schet(LKG* cur)
        {
		data curPar=cur->getParam();
        int *rez=new int [curPar.N];
        rez[0]=curPar.X0;
        for (int i=1; i<curPar.N; i++)
            {
            rez[i]=(curPar.a*curPar.X0+curPar.c) % curPar.m;
            curPar.X0=rez[i];
            }
            return rez;
        };

	int* start_thread()
	{
		void *per;
		int *sum;
		pthread_create(&tid, NULL, calc, this);
		int buf;
		buf = pthread_join(tid, &per);
		sum = (int*)per;
		return sum;
	};

	data getParam()	{return param;}
	pthread_t tid;
	data param;

};


int main()
{


	data dt;
	dt.X0=1; dt.a=5; dt.c=3; dt.m =11; dt.N=16;/*(0<=X0,a,c<m*)(m>=2),N-kol-vo*/
    cout <<"X0="<<dt.X0<<" a="<<dt.a<<" c="<<dt.c<<" m="<<dt.m<<" N="<<dt.N<<endl;
	LKG lkg(dt);
	int* res = lkg.start_thread();

	for(int i=0; i<dt.N; i++)
        {cout << res[i] << " ";}
 	delete []res;
	cout<< endl << "Vse OK"<< endl;
	return 0;
}
