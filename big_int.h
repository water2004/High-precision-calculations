#include <cstdio>
#include <cmath>
typedef unsigned long long ull;
#define pi (double)3.141592653589793
class cpx
{ //复数类
public:
	double rl;
	double ul;
	cpx(double a, double b)
	{
		rl = a;
		ul = b;
	}
	cpx()
	{
		rl = 0;
		ul = 0;
	}
	cpx(double a)
	{
		rl = a;
		ul = 0;
	}
	// void out()
	// {
	//     printf("%lf+%lfi",rl,ul);
	// }
	const cpx operator+(const cpx b)
	{
		cpx ans;
		ans.rl = rl + b.rl;
		ans.ul = ul + b.ul;
		return ans;
	}
	const cpx operator-(const cpx b)
	{
		cpx ans;
		ans.rl = rl - b.rl;
		ans.ul = ul - b.ul;
		return ans;
	}
	const cpx operator*(const cpx b)
	{
		cpx ans;
		ans.rl = rl * b.rl - ul * b.ul;
		ans.ul = rl * b.ul + ul * b.rl;
		return ans;
	}
	const cpx operator/(const cpx b)
	{
		cpx ans;
		double devide = b.rl * b.rl + b.ul * b.ul;
		ans.rl = (rl * b.rl + ul * b.ul) / devide;
		ans.ul = (ul * b.rl - rl * b.ul) / devide;
		return ans;
	}
	void operator+=(const cpx b)
	{
		rl = rl + b.rl;
		ul = ul + b.ul;
	}
	void operator-=(const cpx b)
	{
		rl = rl - b.rl;
		ul = ul - b.ul;
	}
	void operator*=(const cpx b)
	{
		rl = rl * b.rl - ul * b.ul;
		ul = rl * b.ul + ul * b.rl;
	}
	void operator/=(const cpx b)
	{
		double devide = b.rl * b.rl + b.ul * b.ul;
		rl = (rl * b.rl + ul * b.ul) / devide;
		ul = (ul * b.rl - rl * b.ul) / devide;
	}
	void operator=(cpx b)
	{
		rl = b.rl;
		ul = b.ul;
	}
	void operator=(double a) // real number
	{
		rl = a;
		ul = 0;
	}
	void operator!=(double a) // unreal number
	{
		rl = 0;
		ul = a;
	}
	const bool operator==(const cpx b)
	{
		if (rl == b.rl && ul == b.ul)
			return true;
		else
			return false;
	}
	const bool operator!=(const cpx b)
	{
		return !(*this == b);
	}
	const cpx operator/(const double a) const
	{
		cpx ans;
		ans.ul = ul / a;
		ans.rl = rl / a;
		return ans;
	}
	const cpx operator/(const int a) const
	{
		cpx ans;
		ans.ul = ul / a;
		ans.rl = rl / a;
		return ans;
	}
};
cpx pow(cpx a, int n)
{
	cpx ans = 1;
	cpx tmp = a;
	n--;
	while (n)
	{
		if (n >> 1 << 1 == n)
		{
			n >>= 1;
			tmp *= tmp;
		}
		else
		{
			ans *= tmp;
			tmp = a;
			n--;
		}
	}
	ans *= tmp;
	return ans;
}
void FFT(ull cnt, cpx *a, int type)
{
#define half (cnt >> 1)
	if (cnt == 1)
		return;
	cpx *a1 = new cpx[half + 10];
	cpx *a2 = new cpx[half + 10];
	for (ull i = 0; i <= cnt; i += 2)
	{
		a1[i >> 1] = a[i];
		a2[i >> 1] = a[i + 1];
	}
	FFT(half, a1, type);
	FFT(half, a2, type);
	cpx wn = cpx(cos((double)2 * pi / cnt), type * sin((double)2 * pi / cnt)), w = cpx(1, 0);
	for (ull i = 0; i < half; i++, w = w * wn)
	{
		a[i] = a1[i] + w * a2[i];
		a[i + half] = a1[i] - w * a2[i];
	}
	delete[] a1;
	delete[] a2;
}
class big_int
{
private:
	struct node
	{
		node *pre;	//前驱结点
		node *next; //后继结点
		ull v;		//结点数据,2位
		node()		//初始化
		{
			pre = NULL;
			next = NULL;
			v = 0;
		}
	};
	class list
	{
	private:
		ull size; //链表长度
	public:
		node *head, *tail; //头结点与尾结点
		inline list()	   //初始化
		{
			size = 0;
			head = new node;
			tail = new node;
			head->next = tail;
			head->pre = NULL;
			tail->pre = head;
			tail->next = NULL;
		}
		inline ~list() //删除
		{
			node *p = head;
			node *r = p;
			while (p->next != NULL)
			{
				p = p->next;
				delete r;
				r = p;
			}
			delete p;
		}
		inline void push_back(ull v)
		{
			node *p = new node;
			p->v = v;
			p->pre = tail->pre;
			p->next = tail;
			p->next->pre = p;
			p->pre->next = p;
			size++;
		}
		inline void push_front(ull v)
		{
			node *p = new node;
			p->v = v;
			p->pre = head;
			p->next = head->next;
			p->pre->next = p;
			p->next->pre = p;
			size++;
		}
		inline void pop_back()
		{
			if (size == 0)
				return;
			node *p = tail->pre;
			tail->pre = p->pre;
			p->pre->next = tail;
			delete p;
			size--;
		}
		inline void pop_front()
		{
			if (size == 0)
				return;
			node *p = head->next;
			head->next = p->next;
			p->next->pre = head;
			delete p;
			size--;
		}
		inline void clear()
		{
			node *p = head;
			node *r = p;
			while (p->next != NULL)
			{
				p = p->next;
				delete r;
				r = p;
			}
			delete p;
			head = new node;
			tail = new node;
			head->next = tail;
			tail->next = NULL;
			head->pre = NULL;
			tail->pre = head;
			size = 0;
		}
		inline ull length() //长度
		{
			return size;
		}
	};
	inline void clean() //清除前导0
	{

		if (data.length() == 0)
		{
			sign = 0;
			return;
		}
		while (data.head->next->v == 0 && data.head->next != data.tail)
		{
			data.pop_front();
		}
	}

public:
	list data;
	bool sign;			// 1为负,0为正
	inline ull length() //数据位数
	{
		clean();
		ull len = data.length();
		ull f = data.head->next->v;
		if (len == 0)
			return 0;
		if (f > 9)
			return (len << 1);
		return (len << 1) - 1;
	}
	inline big_int() //初始化
	{
		sign = 0;
	}
	inline big_int(long long v)
	{
		if (v < 0) //符号
		{
			sign = 1;
			v = -v;
		}
		else
		{
			sign = 0;
		}
		data.clear(); //清除原来数据
		while (v != 0)
		{
			data.push_front(v % 100); //插入链表
			v /= 100;				  //下一个四位
		}
	}
	inline big_int(const big_int &b)
	{
		data.clear();				 //清除数据
		node *p = b.data.head->next; //第一个数据结点
		while (p != b.data.tail)	 //没有到达尾结点
		{
			data.push_back(p->v); //插入
			p = p->next;		  //下一个结点
		}
		sign = b.sign; //设置符号
	}
	inline bool zero() //判断值是否为0
	{
		clean();
		return data.length() == 0; //长度为0值一定为0
	}
	inline void operator=(long long v)
	{
		if (v < 0) //符号
		{
			sign = 1;
			v = -v;
		}
		data.clear(); //清除数据
		while (v != 0)
		{
			ull s = v / 100;
			s = v - s * (ull)100;
			data.push_front(s);
			v /= 100;
		}
	}
	inline void operator=(big_int b)
	{
		b.clean(); //清理
		data.clear();
		node *p = b.data.head->next; //从头开始
		while (p != b.data.tail)	 //一位一位赋值
		{
			data.push_back(p->v);
			p = p->next;
		}
		sign = b.sign; //别忘了符号
	}
	inline bool operator>(long long v)
	{
		clean(); //清理
		if (v < 0 && sign == 0)
			return true; //正数比负数大
		if (v > 0 && sign == 1)
			return false; //负数比正数小
		if (v == 0 && sign == 1)
			return false; //负数比零小
		if (v == 0 && sign == 0 && data.length() > 0)
			return true;		  //正数比0大
		unsigned long long t = v; //存档一份
		ull lena = 0;			  //该数的位数
		ull lenb = length();
		while (t != 0)
		{
			t /= 10;
			lena++;
		}
		if (lena < lenb)
			return v < 0 ? false : true; //负数比大小，绝对值大的小
		if (lena > lenb)
			return v < 0 ? true : false; //负数比大小，绝对值小的大
		long long mod = 1;				 //用来取出最后一段
		node *p = data.head->next;		 //从前往后比较
		t = lenb % 2;
		if (t) //若第一位不足2位，单独判断
		{
			for (int i = 0; i < lena; i += 2)
				mod *= 100;
			mod /= 100; //取出前2位
			if ((ull)v / mod > p->v)
				return v < 0 ? true : false;
			if ((ull)v / mod < p->v)
				return v < 0 ? false : true;
			v %= mod;
			lena -= t;
			p = p->next;
		}
		while (lena > 0) //一位一位判断，直到比出结果或没有位可比
		{
			mod /= 100;
			if (ull(v / mod) > p->v)
				return v < 0 ? true : false;
			if (ull(v / mod) < p->v)
				return v < 0 ? false : true;
			v /= 100;
			p = p->next;
			lena -= 2;
		}
		return false; //两数相等
	}
	inline bool operator<(long long v)
	{
		clean(); //清理
		if (v < 0 && sign == 0)
			return false; //正数比负数大
		if (v > 0 && sign == 1)
			return true; //负数比正数小
		if (v == 0 && sign == 1)
			return true; //负数比零小
		if (v == 0 && sign == 0 && data.length() > 0)
			return false;		  //正数比0大
		unsigned long long t = v; //存档一份
		ull lena = 0;			  //该数的位数
		ull lenb = length();
		while (t != 0)
		{
			t /= 10;
			lena++;
		}
		if (lena < lenb)
			return v < 0 ? true : false; //负数比大小，绝对值大的小
		if (lena > lenb)
			return v < 0 ? false : true; //负数比大小，绝对值小的大
		long long mod = 1;				 //用来取出最后一段
		node *p = data.head->next;		 //从前往后比较
		t = lenb % 2;
		if (t) //若第一位不足2位，单独判断
		{
			for (int i = 0; i < lena; i += 2)
				mod *= 100;
			mod /= 100; //取出前2位
			if ((ull)v / mod > p->v)
				return v < 0 ? false : true;
			if ((ull)v / mod < p->v)
				return v < 0 ? true : false;
			v %= mod;
			lena -= t;
			p = p->next;
		}
		while (lena > 0) //一位一位判断，直到比出结果或没有位可比
		{
			mod /= 100;
			if (ull(v / mod) > p->v)
				return v < 0 ? false : true;
			if (ull(v / mod) < p->v)
				return v < 0 ? true : false;
			v /= 100;
			p = p->next;
			lena -= 2;
		}
		return false; //两数相等
	}
	inline bool operator>=(long long v)
	{
		return !(*this < v);
	}
	inline bool operator<=(long long v)
	{
		return !(*this > v);
	}
	inline bool operator==(long long v)
	{
		clean();
		ull len = length();
		if (len == 0)
		{
			if (v != 0)
				return false;
			else
				return true;
		}
		if (v < 0 != sign)
			return false;
		if (v < 0)
			v = -v;
		long long t = v;
		int lena = 0;
		while (t != 0)
		{
			t /= 10;
			lena++;
		}
		if (lena != len)
			return false;
		long long mod = 1;
		for (int i = 0; i < lena; i += 2)
			mod *= 100;
		mod /= 100;
		t = len % 2;
		node *p = data.head->next;
		if (t)
		{
			if (v / mod != p->v)
				return false;
			v %= mod;
			p = p->next;
			lena -= t;
		}
		for (int i = 2; i <= lena; i += 2)
		{
			mod /= 100;
			if (v / mod != p->v)
				return false;
			p = p->next;
			v %= mod;
		}
		return true;
	}
	inline bool operator>(big_int b)
	{
		clean();
		b.clean();
		if (b.sign == 0 && sign == 1)
			return false;
		if (b.sign == 1 && sign == 0)
			return true;
		if (length() > b.length())
			return b.sign ? false : true;
		if (length() < b.length())
			return b.sign ? true : false;
		node *p, *r;
		p = data.head->next;
		r = b.data.head->next;
		while (p != data.tail)
		{
			if (p->v > r->v)
				return b.sign ? false : true;
			if (p->v < r->v)
				return b.sign ? true : false;
			p = p->next;
			r = r->next;
		}
		return false;
	}
	inline bool operator<(big_int b)
	{
		clean();
		b.clean();
		if (b.sign == 0 && sign == 1)
			return true;
		if (b.sign == 1 && sign == 0)
			return false;
		if (length() > b.length())
			return b.sign ? true : false;
		if (length() < b.length())
			return b.sign ? false : true;
		node *p, *r;
		p = data.head->next;
		r = b.data.head->next;
		while (p != data.tail)
		{
			if (p->v > r->v)
				return b.sign ? true : false;
			if (p->v < r->v)
				return b.sign ? false : true;
			p = p->next;
			r = r->next;
		}
		return false;
	}
	inline bool operator>=(big_int b)
	{
		return !(*this < b);
	}
	inline bool operator<=(big_int b)
	{
		return !(*this > b);
	}
	inline bool operator==(big_int b)
	{
		clean();
		b.clean();
		if (sign != b.sign)
			return false;
		if (length() != b.length())
			return false;
		node *p = data.head->next;
		node *r = b.data.head->next;
		while (p != data.tail)
		{
			if (p->v != r->v)
				return false;
			p = p->next;
			r = r->next;
		}
		return true;
	}
	inline bool operator!=(big_int b)
	{
		return !(*this == b);
	}
	inline big_int operator-()
	{
		clean();
		big_int c = *this;
		c.sign = !c.sign;
		c.clean();
		return c;
	}
	inline big_int operator+(big_int b)
	{
		if (b.zero())
			return *this;
		b.clean();
		clean();
		if (length() == 0)
			return b;
		if (b.sign == 1 && sign == 0)
		{
			return *this - (-b);
		}
		if (b.sign == 0 && sign == 1)
		{
			return b - (-(*this));
		}
		if (b.sign == 1 && sign == 1)
		{
			return -(-b + (-(*this)));
		}
		big_int ans;
		ull x = 0; //储存进位
		long long lena = data.length(), lenb = b.data.length();
		long long len = lena > lenb ? lena : lenb;
		node *p = data.tail;
		node *r = b.data.tail;
		if (lena <= lenb)
			for (int i = 1; i <= len; i++)
			{
				if (i <= lena)
				{
					p = p->pre;
					r = r->pre;
					x += (p->v + r->v);
				}
				else
				{
					r = r->pre;
					x += r->v;
				}
				ans.data.push_front(x % 100);
				x /= 100;
			}
		else
			for (int i = 1; i <= len; i++)
			{
				if (i <= lenb)
				{
					p = p->pre;
					r = r->pre;
					x += p->v + r->v;
				}
				else
				{
					p = p->pre;
					x += p->v;
				}
				ans.data.push_front(x % 100);
				x /= 100;
			}
		if (x != 0)
			ans.data.push_front(x);
		ans.clean();
		return ans;
	}
	inline big_int operator-(big_int b)
	{
		clean();
		b.clean();
		if (length() == 0)
			return -b;
		if (b.zero())
			return *this;
		if (sign == 0 && b.sign == 1) // a-(-b)=a+b
		{
			return *this + (-b);
		}
		if (sign == 1 && b.sign == 0) //-a-b=-(a+b)
		{
			return -(b + (-(*this)));
		}
		if (sign == 1 && b.sign == 1) //-a-(-b)=b-a
		{
			return -b - (-*this);
		}
		big_int ans;
		big_int a = *this;
		if (*this < b) //保证a>b
		{
			ans.sign = 1;
			big_int p = a;
			a = b;
			b = p;
		}
		ull lena = a.data.length(), lenb = b.data.length();
		ull len = lena > lenb ? lena : lenb;
		node *p = a.data.tail;
		node *r = b.data.tail;
		long long x = 0;
		for (int i = 1; i <= lena; i++)
		{
			if (i <= lenb)
			{
				p = p->pre;
				r = r->pre;
				x += p->v - r->v;
			}
			else
			{
				p = p->pre;
				x += p->v;
			}
			if (x < 0)
			{
				p->pre->v--;
				x += 100;
			}
			ans.data.push_front(x % 100);
			x /= 100;
		}
		if (x != 0)
			ans.data.push_front(x);
		ans.clean();
		return ans;
	}
	inline big_int operator*(big_int b)
	{
		clean();
		b.clean();
		if (data.length() == 0 || b.zero())
		{
			big_int ans;
			return ans;
		}
		ull lena = data.length(), lenb = b.data.length();
		if (lena > lenb) //保证a长度小于b
		{
			return b * (*this);
		}
		big_int ans;
		if (sign != b.sign)
			ans.sign = 1; //同号得正，异号得负
		//----------------------------------------------------------------------------------------------------
		ull cnt = 1;
		for (; cnt <= lena + lenb; cnt <<= 1)
			;
		cpx *a1 = new cpx[cnt + 10], *a2 = new cpx[cnt + 10];
		node *p = data.tail->pre;
		node *t = b.data.tail->pre;
		ull i = 0;
		while (p != data.head)
		{
			a1[i] = p->v;
			p = p->pre;
			i++;
		}
		i = 0;
		while (t != b.data.head)
		{
			a2[i] = t->v;
			t = t->pre;
			i++;
		}
		FFT(cnt, a1, 1);
		FFT(cnt, a2, 1);
		for (ull i = 0; i <= cnt; i++)
		{
			a1[i] = a1[i] * a2[i];
		}
		FFT(cnt, a1, -1);
		for (ull i = 0; i <= (lena + lenb + 1); i++)
		{
			ans.data.push_front((ull)(a1[i].rl / cnt + 0.5));
		}
		p = ans.data.tail->pre;
		while (p->pre != ans.data.head)
		{
			p->pre->v += p->v / 100;
			p->v %= 100;
			p = p->pre;
		}
		while (p->v > 99)
		{
			ans.data.push_front(p->v / 100);
			p->v %= 100;
			p = p->pre;
		}
		ans.clean();
		delete[] a1;
		delete[] a2;
		return ans;
	}
	inline big_int operator+(long long b)
	{
		return *this + (big_int)b;
	}
	inline big_int operator-(long long b)
	{
		return *this - (big_int)b;
	}
	inline big_int operator*(long long b)
	{
		return *this * (big_int)b;
	}
	inline big_int operator/(long long b)
	{
		clean();
		big_int ans;
		node *p = data.head->next;
		ull x = 0;
		if (sign != (b < 0))
			ans.sign = 1;
		if (b < 0)
			b = -b;
		if (*this == 0)
			return 0;
		while (p != data.tail)
		{
			x *= 100;
			x += p->v;
			ans.data.push_back(x / b);
			x %= b;
			p = p->next;
		}
		ans.clean();
		return ans;
	}
	inline big_int operator*(long b)
	{
		clean();
		if (b == 0)
			return 0;
		big_int ans;
		if (sign != (b < 0))
		{
			ans.sign = 1;
		}
		if (b < 0)
			b = -b;
		ull x = 0;
		node *p = data.tail->pre;
		while (p != data.head)
		{
			x += b * p->v;
			ans.data.push_front(x % 100);
			x /= 100;
			p = p->pre;
		}
		while (x > 0)
		{
			ans.data.push_front(x % 100);
			x /= 100;
		}
		ans.clean();
		return ans;
	}
	inline big_int operator*(int b)
	{
		return *this * (long)b;
	}
	inline long long hhh(big_int a, big_int b) //两个相等位数的2位高精度数相除，名字想不到w(ﾟДﾟ)w
	{
		if (a < b)
			return 0;
		long long l = 0, r = 99;
		long long mid = (l + r) / 2;
		big_int tmp = b * mid;
		while (mid != l && mid != r)
		{
			if (tmp > a)
			{
				r = mid;
				mid = (l + r) / 2;
				tmp = b * mid;
			}
			else
			{
				l = mid;
				mid = (l + r) / 2;
				tmp = b * mid;
			}
		}
		return mid;
	}
	inline big_int operator/(big_int b)
	{
		big_int ans;
		clean();
		b.clean();
		if (b.zero())
			return ans;
		if (data.length() == 0)
		{
			return ans;
		}
		if ((*this) < b)
		{
			return ans;
		}
		if (sign != b.sign)
			ans.sign = 1; //同号得正，异号得负
		//---------------------------------------------------------------------
		big_int two = 2;
		int lenb = b.length();
		int b1 = 10 / (b.data.head->next->v > 10 ? b.data.head->next->v / 10 : b.data.head->next->v);
		if (b1 == 10 || b1 == 1)
		{
			b1 = 9;
		}
		ans = b1;
		int exans = -1, exb = -b.length() + 1;//希望ans<1,b>1
		for (int i = 0; i <= log2(length()) + 1; i++)
		{
			two.move(-exb - exans - two.length() + 1);
			ans = ans * (two - ans * b);
			exans = -ans.length();
		}
		int cnt = ans.length() >> 1;
		ans.move(-cnt);
		ans *= *this;
		ans.clean();
		two = b;
		two.move(length() - lenb);
		if (two <= *this)
			ans.move(length() - lenb + 1 - ans.length());
		else
			ans.move(length() - lenb - ans.length());
		if (*this >= (ans + 1) * b)
			return ans + 1;
		else
			return ans;
	}
	inline big_int operator%(big_int b)
	{
		clean();
		b.clean();
		big_int tmp;
		if (b.zero())
			return tmp;
		if (data.length() == 0)
		{
			return tmp;
		}
		if ((*this) < b)
		{
			return (*this);
		}
		ull lenb = b.data.length();
		ull lena = data.length();
		tmp=*this-((*this)/b)*b;
		return tmp;
	}
	inline void operator+=(big_int b)
	{
		*this = *this + b;
	}
	inline void operator-=(big_int b)
	{
		*this = *this - b;
	}
	inline void operator*=(big_int b)
	{
		*this = *this * b;
	}
	inline void operator/=(big_int b)
	{
		*this = *this / b;
	}
	inline void operator%=(big_int b)
	{
		*this = *this % b;
	}
	inline ull operator%(long long b)
	{
		clean();
		node *p = data.head->next;
		ull x = 0;
		if (b < 0)
			b = -b;
		if (*this == 0)
			return 0;
		while (p != data.tail)
		{
			x *= 100;
			x += p->v;
			x %= b;
			p = p->next;
		}
		return x;
	}
	inline void move(long long step)
	{
		if (step > 0)
		{
			while (step - 2 >= 0)
			{
				step -= 2;
				data.push_back(0);
			}
			if (step == 1)
				*this *= 10;
		}
		else
		{
			while (step + 2 <= 0)
			{
				step += 2;
				data.pop_back();
			}
			if (step == -1)
				*this = *this / 10;
		}
	}
	inline void pop()
	{
		// ull v = data.head->next->v;
		// if (v < 100)
		// {
		// 	data.pop_front();
		// 	return;
		// }
		// v %= 100;
		// data.head->next->v = v;
		data.pop_front();
	}
	inline ull top() //取出最前面十进制的两位
	{
		return data.head->next->v;
	}
	inline ull d_length() //高精度数长度
	{
		return data.length();
	}
	inline void out() //输出
	{
		clean();
		if (sign == 1 && data.length() > 0)
			putchar('-');
		if (data.length() == 0)
		{
			putchar('0');
			return;
		}
		node *p = data.head->next;
		printf("%lld", p->v);
		p = p->next;
		while (p != data.tail)
		{
			// printf(" ");
			if (p->v > 9)
			{
				printf("%lld", p->v);
				p = p->next;
				continue;
			}
			if (p->v > 0)
			{
				printf("0%lld", p->v);
				p = p->next;
				continue;
			}
			printf("00");
			p = p->next;
		}
	}
	inline void in() //读入
	{
		list num;
		data.clear();
		char c;
		c = getchar();
		while (c == ' ' || c == '\n' || c == '\r')
			c = getchar();
		if (c == '-')
		{
			sign = 1;
			c = getchar();
		}
		while (c >= '0' && c <= '9')
		{
			num.push_back(c - (ull)'0');
			c = getchar();
		}
		node *p = num.tail->pre;
		node *r = data.tail;
		int nnn;
		while (num.length() >= 2)
		{
			data.push_front(0);
			r = r->pre;
			r->v += p->v;
			p = p->pre;
			num.pop_back();
			r->v += p->v * 10;
			p = p->pre;
			num.pop_back();
		}
		if (num.length() == 2)
			data.push_front(p->pre->v * 10 + p->v);
		else if (num.length() == 1)
			data.push_front(p->v);
		clean();
	}
	inline long long change() //高精转低精
	{
		long long ans = 0;
		node *p = data.head->next;
		while (p != data.tail)
		{
			ans *= 100;
			ans += p->v;
			p = p->next;
		}
		if (sign == 1)
			ans = -ans;
		return ans;
	}
};
inline big_int operator+(long long b, big_int a)
{
	return a + b;
}
inline big_int operator-(long long b, big_int a)
{
	return -(a - b);
}
inline big_int operator*(long long b, big_int a)
{
	return a * b;
}
inline bool operator>(long long b, big_int a)
{
	return a < b;
}
inline bool operator>=(long long b, big_int a)
{
	return !(a > b);
}
inline bool operator<(long long b, big_int a)
{
	return a > b;
}
inline bool operator<=(long long b, big_int a)
{
	return !(a < b);
}
inline bool operator==(long long b, big_int a)
{
	return a == b;
}
inline bool operator!=(long long b, big_int a)
{
	return a != b;
}
inline int bigest(big_int begin, big_int num)
{
	/*begin.out();
	putchar('\n');
	num.out();
	putchar('\n');*/
	int ans = 0;
	long l = 0, r = 10, m = (l + r) >> 1;
	begin.move(1);
	while (m != l && m != r)
	{
		if (m * (begin + m) > num)
		{
			r = m;
			m = (l + r) >> 1;
			continue;
		}
		if (((long)m + (long)1) * (begin + m) < num)
		{
			l = m;
			m = (l + r) >> 1;
			continue;
		}
		return m;
	}
	return m;
}
inline big_int sqrt(big_int num)
{
	big_int ans = 0; //答案
	big_int tmp;
	tmp = 0;
	int one;
	big_int last = 0;
	ull ci = (num.length() + 1) / 2; //需要执行几次
	while (ci > 0)
	{
		ci -= 1;
		//-------------------------------------落下两位------------------------------
		ull t = num.top();
		last.move(2);
		last = last + t;
		num.pop();
		//----------------------------------------------------------------------------
		one = bigest(tmp, last); //得到这样一个最大的数：在tmp后插入这个数，再乘以这个数，值<=last
		/*std::cout << "last=";
		last.out();
		std::cout << "\none="<<one;
		std::cout << "\ntmp=";
		tmp.out();
		std::cout << "\ntop=" << t << std::endl;*/
		//-----------------------------------在tmp后插入-----------------------------
		tmp.move(1);
		tmp = tmp + one;
		//----------------------------------------相减--------------------------------
		last = last - tmp * one;
		tmp = tmp + one;
		//--------------------------------------记录答案-----------------------------
		ans.move(1);
		ans = ans + one;
		//---------------------------------------------------------------------------
	}
	return ans;
}
inline big_int pow_int(big_int num, big_int p)
{
	big_int ans = 1;
	while (p > 0)
	{
		if (p % 2 == 0)
		{
			num = num * num;
			p = p / 2;
		}
		else
		{
			ans = ans * num;
			p = p - 1;
		}
	}
	return ans;
}
inline big_int pow_int(big_int num, long long p)
{
	big_int ans = 1;
	while (p > 0)
	{
		if (p % 2 == 0)
		{
			num = num * num;
			p >>= 1;
		}
		else
		{
			ans = ans * num;
			p = p - 1;
		}
	}
	return ans;
}