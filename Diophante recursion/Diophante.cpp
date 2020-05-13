#include <iostream>
#include <cmath>

using namespace std;

bool diophantine(int a, int b, int c, int &x, int &y);
int gcd(int a, int b);

int main() {

    int a, b, c, x, y;

    cout << "Enter a b c" << endl;
    cin >> a >> b >> c;
    cout << endl;

    cout << "Result: ";
    if (diophantine(a, b, c, x, y)) {
        cout << x << " " << y << endl;
    } else {
        cout << "No solution!" << endl;
    }

    return 0;
}
/* Returns true if a solution was found and false if there is no solution.
   x and y will contain a solution if a solution was found. 
   This function will NOT output anything.
*/
bool diophantine(int a, int b, int c, int &x, int &y) {
	int u;
	int v;	
	bool value = false;
	
	if(c % gcd(a,b) == 0) {

		if(a % b == 0) {
			x = 0;
			y = c/b;
			return true;
		}
		else if(b % a == 0) {
			y = 0;
			x = c/a;
			return true;
		}
		else {
			
			value = diophantine(b, a % b, c, u, v);
			x = v;
			y = u - (a/b) * x;
		}
	}
	
	return value;
}

int gcd(int a, int b) {

	if(a < 0) { 
		a *= -1;
	}
	if(b < 0){
		b *= -1;
	}
	if(a == b) {
		return a;
	}
	else {
		int temp;
		if(a < b)
		{
			temp = a;
			a = b;
			b = temp;
		}
		return gcd(a - b, b);
	}
}