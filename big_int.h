#include<cstdio>
typedef unsigned long long ull;
class big_int
{
private:
	struct node
	{
		node* pre;//前驱结点
		node* next;//后继结点
		ull v;//结点数据,4位
		node()//初始化
		{
			pre = NULL;
			next = NULL;
			v = 0;
		}
	};
	class list
	{
	private:
		ull size;//链表长度
	public:
		node* head, * tail;//头结点与尾结点
		inline list()//初始化
		{
			size = 0;
			head = new node;
			tail = new node;
			head->next = tail;
			head->pre = NULL;
			tail->pre = head;
			tail->next = NULL;
		}
		inline ~list()//删除
		{
			node* p = head;
			node* r = p;
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
			node* p = new node;
			p->v = v;
			p->pre = tail->pre;
			p->next = tail;
			p->next->pre = p;
			p->pre->next = p;
			size++;
		}
		inline void push_front(ull v)
		{
			node* p = new node;
			p->v = v;
			p->pre = head;
			p->next = head->next;
			p->pre->next = p;
			p->next->pre = p;
			size++;
		}
		inline void pop_back()
		{
			if (size == 0) return;
			node* p = tail->pre;
			tail->pre = p->pre;
			p->pre->next = tail;
			delete p;
			size--;
		}
		inline void pop_front()
		{
			if (size == 0) return;
			node* p = head->next;
			head->next = p->next;
			p->next->pre = head;
			delete p;
			size--;
		}
		inline void clear()
		{
			node* p = head;
			node* r = p;
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
		inline ull length()//长度
		{
			return size;
		}
	};
	inline void clean()//清除前导0
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
	list data;
public:
	bool sign;//1为负,0为正
	inline ull length()//数据位数
	{
		clean();
		ull len = data.length();
		ull f = data.head->next->v;
		if (len == 0) return 0;
		if (f > 999) return len << 2;
		if (f > 99) return (len << 2) - 1;
		if (f > 9) return (len << 2) - 2;
		return (len << 2) - 3;
	}
	inline big_int()//初始化
	{
		sign = 0;
	}
	inline big_int(long long v)
	{
		if (v < 0)//符号
		{
			sign = 1;
			v = -v;
		}
		else
		{
			sign = 0;
		}
		data.clear();//清除原来数据
		while (v != 0)
		{
			data.push_front(v % 10000);//插入链表
			v /= 10000;//下一个四位
		}
	}
	inline big_int(const big_int& b)
	{
		data.clear();//清除数据
		node* p = b.data.head->next;//第一个数据结点
		while (p != b.data.tail)//没有到达尾结点
		{
			data.push_back(p->v);//插入
			p = p->next;//下一个结点
		}
		sign = b.sign;//设置符号
	}
	inline bool zero()//判断值是否为0
	{
		clean();
		return data.length() == 0;//长度为0值一定为0
	}
	inline void operator = (long long v)
	{
		if (v < 0)//符号
		{
			sign = 1;
			v = -v;
		}
		data.clear();//清除数据
		while (v != 0)
		{
			ull s = v / 10000;
			s = v - s * (ull)10000;
			data.push_front(s);
			v /= 10000;
		}
	}
	inline void operator = (big_int b)
	{
		b.clean();//清理
		data.clear();
		node* p = b.data.head->next;//从头开始
		while (p != b.data.tail)//一位一位赋值
		{
			data.push_back(p->v);
			p = p->next;
		}
		sign = b.sign;//别忘了符号
	}
	inline bool operator > (long long v)
	{
		clean();//清理
		if (v < 0 && sign == 0) return true;//正数比负数大
		if (v > 0 && sign == 1) return false;//负数比正数小
		if (v == 0 && sign == 1) return false;//负数比零小
		if (v == 0 && sign == 0 && data.length() > 0) return true;//正数比0大
		unsigned long long t = v;//存档一份
		ull lena = 0;//该数的位数
		ull lenb = length();
		while (t != 0)
		{
			t /= 10;
			lena++;
		}
		if (lena < lenb) return v < 0 ? false : true;//负数比大小，绝对值大的小
		if (lena > lenb) return v < 0 ? true : false;//负数比大小，绝对值小的大
		long long mod = 1;//用来取出最后一段
		node* p = data.head->next;//从前往后比较
		t = lenb % 4;
		if (t)//若第一位不足4位，单独判断
		{
			for (int i = 0; i < lena; i += 4) mod *= 10000;
			mod /= 10000;//取出前4位
			if ((ull)v / mod > p->v) return v < 0 ? true : false;
			if ((ull)v / mod < p->v) return v < 0 ? false : true;
			v %= mod;
			lena -= t;
			p = p->next;
		}
		while (lena > 0)//一位一位判断，直到比出结果或没有位可比
		{
			mod /= 10000;
			if (ull(v / mod) > p->v) return v < 0 ? true : false;
			if (ull(v / mod) < p->v) return v < 0 ? false : true;
			v /= 10000;
			p = p->next;
			lena -= 4;
		}
		return false;//两数相等
	}
	inline bool operator < (long long v)
	{
		clean();//清理
		if (v < 0 && sign == 0) return false;//正数比负数大
		if (v > 0 && sign == 1) return true;//负数比正数小
		if (v == 0 && sign == 1) return true;//负数比零小
		if (v == 0 && sign == 0 && data.length() > 0) return false;//正数比0大
		unsigned long long t = v;//存档一份
		ull lena = 0;//该数的位数
		ull lenb = length();
		while (t != 0)
		{
			t /= 10;
			lena++;
		}
		if (lena < lenb) return v < 0 ? true : false;//负数比大小，绝对值大的小
		if (lena > lenb) return v < 0 ? false : true;//负数比大小，绝对值小的大
		long long mod = 1;//用来取出最后一段
		node* p = data.head->next;//从前往后比较
		t = lenb % 4;
		if (t)//若第一位不足4位，单独判断
		{
			for (int i = 0; i < lena; i += 4) mod *= 10000;
			mod /= 10000;//取出前4位
			if ((ull)v / mod > p->v) return v < 0 ? false : true;
			if ((ull)v / mod < p->v) return v < 0 ? true : false;
			v %= mod;
			lena -= t;
			p = p->next;
		}
		while (lena > 0)//一位一位判断，直到比出结果或没有位可比
		{
			mod /= 10000;
			if (ull(v / mod) > p->v) return v < 0 ? false : true;
			if (ull(v / mod) < p->v) return v < 0 ? true : false;
			v /= 10000;
			p = p->next;
			lena -= 4;
		}
		return false;//两数相等
	}
	inline bool operator >= (long long v)
	{
		return !(*this < v);
	}
	inline bool operator <= (long long v)
	{
		return !(*this > v);
	}
	inline bool operator == (long long v)
	{
		clean();
		ull len = length();
		if (len == 0)
		{
			if (v != 0)return false;
			else return true;
		}
		if (v < 0 != sign) return false;
		if (v < 0) v = -v;
		long long t = v;
		int lena = 0;
		while (t != 0)
		{
			t /= 10;
			lena++;
		}
		if (lena != len) return false;
		long long mod = 1;
		for (int i = 0; i < lena; i += 4) mod *= 10000;
		mod /= 10000;
		t = len % 4;
		node* p = data.head->next;
		if (t)
		{
			if (v / mod != p->v)return false;
			v %= mod;
			p = p->next;
			lena -= t;
		}
		for (int i = 4; i <= lena; i += 4)
		{
			mod /= 10000;
			if (v / mod != p->v) return false;
			p = p->next;
			v %= mod;
		}
		return true;
	}
	inline bool operator > (big_int b)
	{
		clean();
		b.clean();
		if (b.sign == 0 && sign == 1) return false;
		if (b.sign == 1 && sign == 0) return true;
		if (length() > b.length()) return b.sign ? false : true;
		if (length() < b.length()) return b.sign ? true : false;
		node* p, * r;
		p = data.head->next;
		r = b.data.head->next;
		while (p != data.tail)
		{
			if (p->v > r->v) return b.sign ? false : true;
			if (p->v < r->v) return b.sign ? true : false;
			p = p->next;
			r = r->next;
		}
		return false;
	}
	inline bool operator < (big_int b)
	{
		clean();
		b.clean();
		if (b.sign == 0 && sign == 1) return true;
		if (b.sign == 1 && sign == 0) return false;
		if (length() > b.length()) return b.sign ? true : false;
		if (length() < b.length()) return b.sign ? false : true;
		node* p, * r;
		p = data.head->next;
		r = b.data.head->next;
		while (p != data.tail)
		{
			if (p->v > r->v) return b.sign ? true : false;
			if (p->v < r->v) return b.sign ? false : true;
			p = p->next;
			r = r->next;
		}
		return false;
	}
	inline bool operator >= (big_int b)
	{
		return !(*this < b);
	}
	inline bool operator <= (big_int b)
	{
		return !(*this > b);
	}
	inline bool operator == (big_int b)
	{
		clean();
		b.clean();
		if (sign != b.sign) return false;
		if (length() != b.length()) return false;
		node* p = data.head->next;
		node* r = b.data.head->next;
		while (p != data.tail)
		{
			if (p->v != r->v) return false;
			p = p->next;
			r = r->next;
		}
		return true;
	}
	inline bool operator !=(big_int b)
	{
		return !(*this == b);
	}
	inline big_int operator - ()
	{
		clean();
		big_int c = *this;
		c.sign = !c.sign;
		c.clean();
		return c;
	}
	inline big_int operator + (big_int b)
	{
		if (b.zero()) return *this;
		b.clean();
		clean();
		if (length() == 0) return b;
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
		ull x = 0;//储存进位
		long long lena = data.length(), lenb = b.data.length();
		long long len = lena > lenb ? lena : lenb;
		node* p = data.tail;
		node* r = b.data.tail;
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
				ans.data.push_front(x % 10000);
				x /= 10000;
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
				ans.data.push_front(x % 10000);
				x /= 10000;
			}
		if (x != 0)ans.data.push_front(x);
		ans.clean();
		return ans;
	}
	inline big_int operator - (big_int b)
	{
		clean();
		b.clean();
		if (length() == 0) return -b;
		if (b.zero()) return *this;
		if (sign == 0 && b.sign == 1)//a-(-b)=a+b
		{
			return *this + (-b);
		}
		if (sign == 1 && b.sign == 0)//-a-b=-(a+b)
		{
			return -(b + (-(*this)));
		}
		if (sign == 1 && b.sign == 1)//-a-(-b)=b-a
		{
			return -b - (-*this);
		}
		big_int ans;
		big_int a = *this;
		if (*this < b)//保证a>b
		{
			ans.sign = 1;
			big_int p = a;
			a = b;
			b = p;
		}
		ull lena = a.data.length(), lenb = b.data.length();
		ull len = lena > lenb ? lena : lenb;
		node* p = a.data.tail;
		node* r = b.data.tail;
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
				x += 10000;
			}
			ans.data.push_front(x % 10000);
			x /= 10000;
		}
		if (x != 0) ans.data.push_front(x);
		ans.clean();
		return ans;
	}
	inline big_int operator * (big_int b)
	{
		clean();
		b.clean();
		if (data.length() == 0 || b.zero())
		{
			big_int ans;
			return ans;
		}
		ull lena = data.length(), lenb = b.data.length();
		if (lena > lenb)//保证a长度小于b
		{
			return b * (*this);
		}
		big_int ans;
		if (sign != b.sign) ans.sign = 1;//同号得正，异号得负
		node* p = data.tail;
		node* r = b.data.tail;
		node* t = ans.data.tail;
		node* c;
		unsigned long long x = 0;
		for (long long i = 1; i <= lena; i++)
		{
			p = p->pre;
			if (t->pre == ans.data.head)
			{
				ans.data.push_front(0);
				t = ans.data.head->next;
			}
			else t = t->pre;
			c = t;
			x = 0;
			r = b.data.tail;
			for (long long j = 1; j <= lenb; j++)
			{
				r = r->pre;
				x += p->v * r->v;
				if (c == ans.data.head)
				{
					ans.data.push_front(0);
					c = ans.data.head->next;
				}
				c->v += x % 10000;
				x /= 10000;
				if (c->v >= 10000)
				{
					x += c->v / 10000;
					c->v %= 10000;
				}
				c = c->pre;
			}
			if (x != 0) ans.data.push_front(x);
		}
		ans.clean();
		return ans;
	}
	inline big_int operator + (long long b)
	{
		return *this + (big_int)b;
	}
	inline big_int operator - (long long b)
	{
		return *this - (big_int)b;
	}
	inline big_int operator * (long long b)
	{
		return *this * (big_int)b;
	}
	inline big_int operator / (long long b)
	{
		clean();
		big_int ans;
		node* p = data.head->next;
		ull x = 0;
		if (sign != (b < 0)) ans.sign = 1;
		if (b < 0) b = -b;
		if (*this == 0) return 0;
		while (p != data.tail)
		{
			x *= 10000;
			x += p->v;
			ans.data.push_back(x / b);
			x %= b;
			p = p->next;
		}
		ans.clean();
		return ans;
	}
	inline big_int operator * (long b)
	{
		clean();
		if (b == 0) return 0;
		big_int ans;
		if (sign != (b < 0))
		{
			ans.sign = 1;
		}
		if (b < 0) b = -b;
		ull x = 0;
		node* p = data.tail->pre;
		while (p != data.head)
		{
			x += b * p->v;
			ans.data.push_front(x % 10000);
			x /= 10000;
			p = p->pre;
		}
		while (x > 0)
		{
			ans.data.push_front(x % 10000);
			x /= 10000;
		}
		ans.clean();
		return ans;
	}
	inline big_int operator * (int b)
	{
		return *this * (long)b;
	}
	inline long long hhh(big_int a, big_int b)//两个相等位数的四位高精度数相除，名字想不到w(ﾟДﾟ)w
	{
		if (a < b) return 0;
		long long l = 0, r = 9999;
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
	inline big_int operator / (big_int b)
	{
		big_int ans;
		clean();
		b.clean();
		if (b.zero()) return ans;
		if (data.length() == 0)
		{
			return ans;
		}
		if ((*this) < b)
		{
			return ans;
		}
		if (sign != b.sign) ans.sign = 1;//同号得正，异号得负
		big_int tmp;
		ull lenb = b.data.length();
		ull lena = data.length();
		node* h = data.head->next;
		for (ull i = 0; i < lenb; i++)//先得复制一份
		{
			tmp.data.push_back(h->v);
			h = h->next;
		}
		//tmp.out();
		lena -= lenb;
		lena++;
		long long ans1;
		while (lena--)
		{
			ans1 = hhh(tmp, b);
			tmp = tmp - b * ans1;
			ans.data.push_back(ans1);
			tmp.data.push_back(h->v);
			h = h->next;
		}
		ans.clean();
		return ans;
	}
	inline big_int operator % (big_int b)
	{
		clean();
		b.clean();
		big_int tmp;
		if (b.zero()) return tmp;
		if (data.length() == 0)
		{
			return tmp;
		}
		if ((*this) < b)
		{
			return tmp;
		}
		ull lenb = b.data.length();
		ull lena = data.length();
		node* h = data.head->next;
		for (ull i = 0; i < lenb; i++)
		{
			tmp.data.push_back(h->v);
			h = h->next;
		}
		//tmp.out();
		lena -= lenb;
		lena++;
		long long ans1;
		while (lena--)
		{
			ans1 = hhh(tmp, b);
			tmp = tmp - b * ans1;
			tmp.data.push_back(h->v);
			h = h->next;
		}
		tmp.data.pop_back();
		return tmp;
	}
	inline void operator += (big_int b)
	{
		*this = *this + b;
	}
	inline void operator -= (big_int b)
	{
		*this = *this - b;
	}
	inline void operator *= (big_int b)
	{
		*this = *this * b;
	}
	inline void operator /= (big_int b)
	{
		*this = *this / b;
	}
	inline void operator %= (big_int b)
	{
		*this = *this % b;
	}
	inline ull operator % (long long b)
	{
		clean();
		node* p = data.head->next;
		ull x = 0;
		if (b < 0) b = -b;
		if (*this == 0) return 0;
		while (p != data.tail)
		{
			x *= 10000;
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
			while (step - 4 > 0)
			{
				step -= 4;
				data.push_back(0);
			}
			if (step == 1) *this *= 10;
			if (step == 2) *this *= 100;
			if (step == 3) *this *= 1000;
		}
		else
		{
			while (step + 4 < 0)
			{
				data.pop_back();
			}
			if (step == -1) *this /= 10;
			if (step == -2) *this /= 100;
			if (step == -3) *this /= 1000;
		}
	}
	inline void pop()
	{
		ull v = data.head->next->v;
		if (v < 100)
		{
			data.pop_front();
			return;
		}
		v %= 100;
		data.head->next->v = v;
	}
	inline ull top()//取出最前面十进制的两位
	{
		ull v = data.head->next->v;
		if (v < 100) return v;
		if (v < 1000) return v / 100;
		return v / 100;
	}
	inline ull d_length()//高精度数长度
	{
		return data.length();
	}
	inline void out()//输出
	{
		clean();
		if (sign == 1 && data.length() > 0) putchar('-');
		if (data.length() == 0)
		{
			putchar('0');
			return;
		}
		node* p = data.head->next;
		printf("%lld", p->v);
		p = p->next;
		while (p != data.tail)
		{
			if (p->v > 999)
			{
				printf("%lld", p->v);
				p = p->next;
				continue;
			}
			if (p->v > 99)
			{
				printf("0%lld", p->v);
				p = p->next;
				continue;
			}
			if (p->v > 9)
			{
				printf("00%lld", p->v);
				p = p->next;
				continue;
			}
			if (p->v > 0)
			{
				printf("000%lld", p->v);
				p = p->next;
				continue;
			}
			printf("0000");
			p = p->next;
		}
	}
	inline void in()//读入
	{
		list num;
		data.clear();
		char c;
		c = getchar();
		while (c == ' ' || c == '\n' || c == '\r') c = getchar();
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
		node* p = num.tail->pre;
		node* r = data.tail;
		int nnn;
		while (num.length() >= 4)
		{
			nnn = 1;
			data.push_front(0);
			r = r->pre;
			r->v += p->v;
			p = p->pre;
			num.pop_back();
			for (int i = 1; i < 4; i++)
			{
				nnn *= 10;
				r->v += p->v * nnn;
				p = p->pre;
				num.pop_back();
			}
		}
		if (num.length() == 3) data.push_front(p->pre->pre->v * 100 + p->pre->v * 10 + p->v);
		else if (num.length() == 2) data.push_front(p->pre->v * 10 + p->v);
		else if (num.length() == 1) data.push_front(p->v);
		clean();
	}
	inline long long change()//高精转低精
	{
		long long ans = 0;
		node* p = data.head->next;
		while (p != data.tail)
		{
			ans *= 10000;
			ans += p->v;
			p = p->next;
		}
		if (sign == 1) ans = -ans;
		return ans;
	}
};
inline big_int operator + (long long b, big_int a)
{
	return a + b;
}
inline big_int operator - (long long b, big_int a)
{
	return -(a - b);
}
inline big_int operator * (long long b, big_int a)
{
	return a * b;
}
inline bool operator > (long long b, big_int a)
{
	return a < b;
}
inline bool operator >= (long long b, big_int a)
{
	return !(a > b);
}
inline bool operator < (long long b, big_int a)
{
	return a > b;
}
inline bool operator <= (long long b, big_int a)
{
	return !(a < b);
}
inline bool operator == (long long b, big_int a)
{
	return a == b;
}
inline bool operator != (long long b, big_int a)
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
	big_int ans = 0;//答案
	big_int tmp;
	tmp = 0;
	int one;
	big_int last = 0;
	ull ci = (num.length() + 1) / 2;//需要执行几次
	while (ci > 0)
	{
		ci -= 1;
		//-------------------------------------落下两位------------------------------
		ull t = num.top();
		last.move(2);
		last = last + t;
		num.pop();
		//----------------------------------------------------------------------------
		one = bigest(tmp, last);//得到这样一个最大的数：在tmp后插入这个数，再乘以这个数，值<=last
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
