#define  _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>
using namespace std;

class String
{
	friend ostream& operator<< (ostream& os,String& s);
public:
	String(const char* str = "")		//构造函数
		:_sz(strlen(str))
		,_capacity(strlen(str)+1)
		,_str(new char[strlen(str)+1])
	{
		cout<<"String(const char* str)"<<endl;
		strcpy(_str,str);
	}
	String(const String& s)		//拷贝构造
		:_sz(s._sz)
		,_capacity(strlen(s._str)+1)
		,_str(new char[strlen(s._str)+1])
	{
		cout<<"String(const String& s)"<<endl;
		strcpy(_str,s._str);
	}
	~String()		
	{
		cout<<"~String()"<<endl;
		if(*_str != NULL)
		{
			delete[] _str;
			_str = NULL;
			_sz = 0;
			_capacity = 0;
		}
	}
	String& operator= (const String& s);
	//String& operator= (const String& s);
	char& operator[] (int index);
	void Push_Back(char c);
	String& operator+= ( const String& str );
	String& operator+= ( const char* s );
	String& operator+= ( char c );
	String& insert ( size_t pos, const String& str );
	String& insert ( size_t pos1, const String& str, size_t pos2, size_t n );
	String& insert ( size_t pos, const char* s, size_t n);
	String& insert ( size_t pos, const char* s );
	String& insert ( size_t pos, size_t n, char c );
private:
	void CheckCapacity(int count)
	{
		if(_sz+count >= _capacity)
		{
			int newCapacity = 2*_capacity > (_capacity + count) ? 2*_capacity : (_capacity+count);
			char* temp = new char[newCapacity];
			strcpy(temp,_str);
			delete[] _str;
			_str = temp;
			_capacity = newCapacity;
		}
	}
private:
	char* _str;
	int _sz;
	int _capacity;
};

ostream& operator<<(ostream& os,String& s)
{
	os<<s._str;
	return os;
}

String& String::operator= (const String& s)
{
	if(this != &s)	//判断两个对象是否相等
	{
		delete[] _str;
		_str = new char[strlen(s._str)+1];
		strcpy(_str,s._str);
		_sz = s._sz;
		_capacity = s._capacity;
	}
	return *this;
}
//String& String::operator= (const String& s)
//{
//	std::swap(_str,s._str);
//	return *this;
//}
char& String::operator[] (int index)
{
	return _str[index];
}
void String::Push_Back(char c)
{
	CheckCapacity(1);
	_str[_sz++] = c;
	_str[_sz] = '\0';
}
String& String::operator+= ( const String& str )
{
	CheckCapacity(strlen(str._str));
	strcat(_str,str._str);
	_sz += strlen(str._str);
	_str[_sz] = '\0';
	return *this;
}
String& String::operator+= ( const char* s )
{
	CheckCapacity(strlen(s));
	strcat(_str,s);
	_sz += strlen(s);
	_str[_sz] = '\0';
	return *this;
}
String& String::operator+= ( char c )
{
	CheckCapacity(1);
	_str[_sz++] = c;
	_str[_sz] = '\0';
	return *this;
}
String& String::insert ( size_t pos, const String& str )
{
	if((pos>0) && (pos<=strlen(_str)))	//判断pos是否合理
	{
		CheckCapacity(strlen(str._str));
		char* tmp = new char[strlen(_str)-pos+2];
		strcpy(tmp,_str+pos-1);	//保存_str的pos位及之后的内容
		//我们可以利用strcat函数来追加一个字符串，但前提是必须使前一个字符串（str1）以'\0'结尾
		_str[pos-1] = '\0';
		strcat(_str,str._str);
		strcat(_str,tmp);
		_sz += strlen(str._str);
		_str[_sz] = '\0';
		delete[] tmp;
	}
	return *this;
}
String& String::insert ( size_t pos1, const String& str, size_t pos2, size_t n )
{
	if((pos1>0) && (pos1<=strlen(_str)))	//判断pos1是否合理
	{
		if((pos2>0) && (pos2<=strlen(str._str)))	//判断pos2是否合理
		{
			if((n>0) && (n<=strlen(str._str)-pos2))	//检测n是否合理
			{
				CheckCapacity(n);
				char* tmp = new char[strlen(_str)-pos1+2];
				strcpy(tmp,_str+pos1-1);	//保存_str的pos1位及之后的内容
				_str[pos1-1] = '\0';
				strncat(_str,str._str+pos2-1,n);
				strcat(_str,tmp);
				_sz += strlen(str._str);
				_str[_sz] = '\0';
				delete[] tmp;
			}
		}
	}
	return *this;
}
String& String::insert ( size_t pos, const char* s, size_t n)
{
	if((pos>0) && (pos<=strlen(_str)))	//判断pos是否合理
	{
		CheckCapacity(n);
		char* tmp = new char[strlen(_str)-pos+2];
		strcpy(tmp,_str+pos-1);	//保存_str的pos位及之后的内容
		_str[pos-1] = '\0';
		strncat(_str,s,n);
		strcat(_str,tmp);
		_sz += strlen(s);
		_str[_sz] = '\0';
		delete[] tmp;
	}
	return *this;
}
String& String::insert ( size_t pos, const char* s )
{
	if((pos>0) && (pos<=strlen(_str)))	//判断pos是否合理
	{
		CheckCapacity(strlen(s));
		char* tmp = new char[strlen(_str)-pos+2];
		strcpy(tmp,_str+pos-1);		//保存_str的pos位及之后的内容
		_str[pos-1] = '\0';
		strcat(_str,s);
		strcat(_str,tmp);
		_sz += strlen(s);
		_str[_sz] = '\0';
		delete[] tmp;
	}
	return *this;
}
String& String::insert ( size_t pos, size_t n, char c )
{
	if((pos>0) && (pos<=strlen(_str)))	//判断pos是否合理
	{
		CheckCapacity(n);
		int i = 1;
		char* tmp = new char[strlen(_str)-pos+2];
		strcpy(tmp,_str+pos-1);//2345
		//_str[pos-1] = '\0';
		for(i=1; i<=n; i++)
		{
			_str[i] = c;
		}
		_str[i] = '\0';
		strcat(_str,tmp);
		_sz += n;
		_str[_sz] = '\0';
		delete[] tmp;
	}
	return *this;
}


void test1()
{
	String str1("hell");
	cout<<str1<<endl;
	//String str2(str1);
	//cout<<str2<<endl;
	//String str3;
	//str3 = str1;		
	//cout<<str3<<endl;
	//String str1("hell");
	//str1.Push_Back('o');
	//cout<<str1<<endl;
}
void test2()     //operator+=
{
	String str1("hello");
	String str2("abcdef");
	//str1 += '\n';		//String& operator+= ( char c )
	//str1 += " world ";		//String& operator+= ( const char* s )
	str1 += str2;		//String& operator+= ( const String& str )
	cout<<str1<<endl;
}
void test3()		//insert
{
	String str1("12345");
	String str2("abcde");
	//str1.insert(3,str2);		//String& insert ( size_t pos, const String& str );
	str1.insert(2,str2,3,2);
						//String& insert ( size_t pos1, const String& str, size_t pos2, size_t n );
	//str1.insert(2,"abcdef",3);//String& insert ( size_t pos, const char* s, size_t n);
	//str1.insert(6,"abc");		//String& insert ( size_t pos, const char* s );
	//str1.insert(2,5,'c');		//String& insert ( size_t pos, size_t n, char c );
	cout<<str1<<endl;
}

int main()
{
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}