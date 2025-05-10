#include <iostream>
using namespace std;

int main() {
    int n = 4, from, to, k;

    for(k=1; k < (1 << n); k++) {
        from = (k&(k-1))%3;
        to   = ((k|(k-1))+1)%3;
        cout << "Mova disco de " << from << " para " << to << endl;
    }
}
