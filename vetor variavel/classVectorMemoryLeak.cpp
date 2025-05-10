#include <iostream>
using namespace std;

struct Produto {
	char teste = 'A';	//Soh pro produto ter um peso.
};

struct Prateleira {
	Produto* produtos = new Produto[10];	//Cada prateleira tera 10 produtos.
	Prateleira() { produtos[0].teste = 'B'; }	//Altera o primeiro produto, porque sim.
	~Prateleira() { delete[] produtos; }	//Destruir os produtos quando Prateleira for destruida.
};

int main() {
	Prateleira* prateleiras;
	int repetir = 0;
	cout << "Iniciar? - ";
	system("pause");
	cout << "Iniciando...\n\n";

	while (repetir++ < 1000) {
		cout << repetir;
		prateleiras = new Prateleira[1000000];	//Criando 1M de prateleiras.
		cout << " - criado";
		delete[] prateleiras; //Destruindo as prateleiras.
		cout << " - destruido\n";
	}

	cout << "\nFechar programa?\n";
	system("pause");
}
















Why does my dynamic class vector appear to have a memory leak?

A class vector that contains another vector from another class, visually there is no memory leak, but through testing the leak exists.


**----------The Problem----------**
I was creating a market system (for learning purposes only) using object orientation, but after some tests, I noticed that the RAM memory used never returned to what it was at the beginning of the program's execution.

Looking at the code, there doesn't appear to be any kind of RAM leak, but through testing, looking at the Windows task manager, it is there, the RAM is increasing uncontrollably.



**----------Tests----------**
The original code is very long, so I made a simpler one, with just the part that generates the problem so I can perform the tests. 

The test code I created works like this: 1 - Inside a loop, a vector of "n" shelves is created, then (still inside the loop) this vector is destroyed. 2 - The loop repeats "n" times. 3 - When the loop ends, I can look at the Windows task manager and see how much memory is still allocated.

**Some results:**
**1º -** When the "test program" I created is open, it allocates about 0.4 MB of RAM.

**2º -** So I create 1 million shelves, with each shelf having 10 products, and then I destroy all these shelves, also destroying their products. I repeat this action 1000 times (remember that the end of each action is to destroy the shelves **AND** their products), and at the end of the loop, when I look in the Windows task manager, the allocated RAM is around 15.3 MB (why?).

**3º -** To see the growth rate, I ran the test program again, but 10 thousand times. In the end, the allocated memory was around 17,2MB. --> Why is the memory allocated in this test not much larger than that allocated in the previous test? knowing that this one was executed 10x more than the previous one.

**Note:** for every 1 million shelves (10 products for each) the program allocates 38.4MB, so basically the loop allocates ~38MB and then deallocates, and repeats this "n" times.

**4º -** Now, I have increased the number of shelves to 10 million. I ran the test 100 times and the final result was 3.4MB allocated

**Note:** For every 10 million shelves (still with 10 products each), 384.1MB are allocated.

**5º -** Running the test with 10 million shelves 1000 times, the final result is 138.9MB of RAM allocated.



**----------My conclusion----------**
1- It really doesn't seem like my code has a RAM leak, but the tests say otherwise.
2- The more tests that are run in the loop, the more RAM is left at the end, but it gets smaller and smaller.
3- The larger the vector of shelves, the more unnecessarily allocated memory remains in the end.



**----------My test code----------**

```
#include <iostream>
using namespace std;

struct Product {
	char something = 'A';	//Just so that the “Product” has a “weight”.
};

struct Shelf {
	Product* products = new Product[10];	//Each shelf has 10 products.
	Shelf() { products[0].something = 'B'; } //Change the first product, just bcause I want to.
	~Shelf() { delete[] products; }	//Destroy products before your shelves are destroyed.
};

int main() {
	Shelf* shelves;
	int repeat = 0;
	cout << "START? - ";
	system("pause");	//Waits for user input.
	cout << "Starting\n\n";

	while (repeat++ < 10000) {	//Do this 10000 times.
		cout << repeat;
		shelves = new Shelf[1000000];	//Creating 1 million shelves.
		cout << " - created";
		delete[] shelves; //Destroying all the shelves.
		cout << " - destroyed\n";
	}

	//At this point, shouldnt the allocated RAM be the same as at the start of the program?
	cout << "\nCLOSE?\n";
	system("pause");
}

```


**Can someone please explain to me what is happening?**