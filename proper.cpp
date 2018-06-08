#include <iostream>
#include <string>
#include <fstream>

using namespace std;

typedef unsigned long long int keytype;

keytype getkey()
{
	char k[8];
	cout << "\nEnter the 8 character key: ";
	cin >> k;
	keytype x = convert(k);
	return x;
}

keytype convert(char x[8])
{
	keytype temp = 0;
	for (int i = 0; i < 8; ++i)
	{
			temp << 8;		
			temp += x[i];
	}
 	return temp;
}

void revert(keytype a,char x[8])
{
	for(int i = 7; i >= 0; i++)
	{
		x[i] = a % 256;
		a /= 256;
	}
}

keytype substitution(keytype k, keytype n)
{
	keytype t,temp = 0;
	keytype key = n;
	while(buf > 0)
	{
		temp += k % 16
		k /= 16;
		temp += key % 16;
		key /= 16;
		temp += key % 16;
		key /= 16;
		if (key == 0)
		{
			key += k;
			t = key % 16;
			key >> 4;
			t >> 60;
			key += t;
		}
	}
	return temp;
}

void shufflearray(keytype x,int a[8])
{
	int b[8] = {0,1,2,3,4,5,6,7};
	int temp,i,j,k,size = 8;
	while(size > 0)
	{
		temp = x % 256;
		x /= 256;
		k = temp % size;
		a[i] = b[k];
		for(i = k; i < size; i++)
		{
			b[i] = b[i+1];
		}
		size--;
	}
}

keytype transposition(keytype k, keytype n)
{
	int a[8];
	char buf1[8],buf2[8];
	revert(k,buf1);
	shufflearray(n,a);
	for (int i = 0; i < 8; i++)
		buf2[i] = buf1[a[i]];
	keytype temp = convert(buf2);
	return temp;
}

keytype encrypt(keytype val,keytype key)
{
	for (int i = 0; i < 10; ++i)
	{
		val = substitution(val,key);
		val = transposition(val,key);
	}
	return val;
}

void makeblocks(keytype key)
{
	ifstream fp1;
	ofstream fp2;
	char fname[50];
	cout << "\nEnter the filename  to encrypt: ";
	cin >> fname;
	fp1.open(fname);
	cout << "\nEnter the new name  of the encrypted file: ";
	cin >> fname;
	fp2.open(fname);
	int i = 0;
	char a[8],b[8];
	keytype val;
	while(!fp1.eof())
	{
		if(i == 8)
		{
			i = 0;
			val = convert(a);
			val ^ key;
			revert(val,b);
			for(int j = 0; j < 8; j++)
				fp2.put(b[j]);
		}
		fp1.get(a[i]);
		i++;
	}
	if(i < 8)
	{
		while(i < 8)
		{
			a[i++] = '*';
		}
	}
	fp1.close();
	fp2.close();
}

int main()
{
	keytype key = getkey();
	makeblocks(key);
	return 0;
}