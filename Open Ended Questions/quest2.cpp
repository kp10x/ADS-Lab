#include <iostream>
#include <bits/stdc++.h>
using namespace std;
 
void findUniqueDigitNos(int l, int r) {
 for (int i = l ; i <= r ; i++) { 
      int num = i; 
      bool visited[10] = {false}; 
      while (num){                            //for each value check if a digit has appeared before or not
          if (visited[num % 10]) break; 
          visited[num % 10] = true; 
          num = num / 10; 
      } 
      if (num == 0) {
        cout << i << " "; 
      }
  }
  cout<<"\n";
}

int main() {
  int l ,r;
  cin >> l >> r;
  findUniqueDigitNos(l, r);

  return 0;
}