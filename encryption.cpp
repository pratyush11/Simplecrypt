#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

typedef unsigned long long int keytype;

keytype convert(char x[8])
{
	keytype temp = 0;
	for (int i = 0; i < 8; ++i)
	{
			temp *= 256;		
			temp += x[i];
	}
 	return temp;
}

void revert(keytype a,char x[8])
{
	for(int i = 7; i >= 0; i--)
	{
		x[i] = a % 256;
		a /= 256;
	}
}

void display(char x[8])
{
	for (int i = 0; i < 8; ++i)
	{
		cout << x[i];
	}
}

keytype getkey()
{
	char k[8];
	cout << "\nEnter the 8 character key: ";
	cin >> k;
	keytype x = convert(k);
	return x;
}

keytype shiftaround(keytype k)
{
	keytype temp = 0;
	temp = k % 16;
	temp << 60;
	k >> 4;
	k += temp;
	return k;
}

keytype substitution(keytype k, keytype n)
{
	keytype t,temp = 0;
	keytype key = n;
	while(k > 0)
	{
		temp *= 16;
		temp += k % 16;
		k /= 16;
		temp += key % 16;
		key /= 16;
		temp += key % 16;
		key /= 16;
		if (key == 0)
			key = shiftaround(k);
	}
	return temp;
}

keytype inc(keytype n)
{
	keytype temp = n;
	n += n % 65536;
	if(n < 65536)
		n += temp / 2;
	return n;
}

void shufflearray(keytype x,int a[8])
{
	int b[8] = {0,1,2,3,4,5,6,7};
	int temp,i,j,k,size = 8;
	j = 0;
	while(size > 0)
	{
		temp = x % 256;
		x /= 256;
		k = temp % size;
		a[j++] = b[k];
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

void text_file_encrypt(keytype key)
{
	keytype temp,val,n;
	ifstream fp1;
	ofstream fp2;
	char fname[50];
	cout << "\nEnter the filename  to encrypt: ";
	//cin >> fname;
	std::strcpy(fname,"sample.txt");
	fp1.open(fname);
	cout << "\nEnter the new name of the encrypted file: ";
	cin >> fname;
	//std::strcpy(fname,"sample_encrypted.txt");
	fp2.open(fname);
	int i = 0;
	char a[8],b[8];
	//n = inc(key);
	cout << endl;
	while(!fp1.eof())
	{
		if(i == 8)
		{
			i = 0;
			val = convert(a);
			temp = encrypt(val,key);
			//n = inc(n);
			//val ^ temp;
			revert(temp,b);
			for(int j = 0; j < 8; j++)
			{	
				//cout << b[j];
				fp2.put(b[j]);
			}
		}
		fp1.get(a[i]);
		i++;
	}
	if(i < 8)
	{
		int temp1 = i;
		while(i < 8)
			a[i++] = '\0';
		val = convert(a);
		temp = encrypt(val,key);
		//n = inc(n);
		//val ^ temp;
		revert(temp,b);
		for(int j = 0; j < temp1; j++)
		{	
			//cout << b[j];
			fp2.put(b[j]);
		}
		fp2.put(EOF);

	}
	fp1.close();
	fp2.close();
}

int main()
{
	keytype key = getkey();
	text_file_encrypt(key);
	return 0;
}