#include <iostream>

#include <ctime>
#include <chrono>



struct MyData
{
	double a;
	double b;
	double e;
	double (*function)(double x);
	double sum;


};

MyData generateData(double a, double b, double e, double (*function)(double x), double sum)
{
	MyData myData;
	myData.a = a;
	myData.b = b;
	myData.e = e;
	myData.function = function;
	myData.sum = sum;
	return myData;
}

double calculate(void* args)
{
	auto time1 = std::chrono::high_resolution_clock::now();
	MyData myData = *(MyData*)args;

	double a = myData.a;
	double b = myData.b;
	double e = myData.e;
	double h = e;
	double x = a;
	double sum = 0;
	int finish = (b - a) / h;
#pragma omp parallel for num_threads(6) reduction(+:sum) 
	for(int i=0;i< finish;i++)
	{
		sum += h * myData.function(i*e);
		/*if (i * e + h < b)
		{
			x += h;
		}
		else
		{
			x = b;

		}*/
	}
	//((MyData*)args)->sum = myData.sum;
	//std::cout << ((MyData*)args)->sum << std::endl;
	auto time2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
	auto avrDur = duration;
	std::cout << "Time = " << avrDur << std::endl;
	return sum;

}
double cosinus(double x)
{
	return cos(x);
}



int main()
{
	srand(time(NULL));
	//auto time1 = std::chrono::high_resolution_clock::now();
	const int N = 1;
	double sum = 0;
	double sums[N];
	//pthread_t threads[N];
	MyData data[N];
	double a = 0, b = 6000;
	data[0] = generateData(a, b, 0.001, cos, 0);
	/*for (int i = 0; i < N; i++)
	{
		data[i] = generateData((a + (i) * (b - a) / N), (a + (i + 1) * (b - a) / N), 0.001, cosinus, 0);
		
	}*/



	
	
		double rez=calculate(&data[0]);
	


	
	std::cout <<"Rez = "<< rez << std::endl;
	/*auto time2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
	auto avrDur = duration;
	std::cout << avrDur << std::endl;
	//13938
	//358k
	/*int N = 10000;
	for (int j = 0; j < N; j++)
	{
		if (j % 100 == 0)std::cout << j << " " << std::endl;
#pragma omp parallel for num_threads(8)  
		for (int i = 0; i < 100000; i++)
		{
			
			int x = rand() % 20;
		}
	}
	auto time2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
	auto avrDur = duration / N;
	std::cout << avrDur << std::endl;
	//6700 - 1 thread
	//2200 - 4 thread*/
	return 0;
};

