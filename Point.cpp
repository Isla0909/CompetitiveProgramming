template<class T> struct Point
{
	T x, y;

	Point(T x_, T y_) : x(x_), y(y_) {}

	template<class U> operator Point<U>()
	{
		return Point<U>(U(x), U(y));
	}

	constexpr Point &operator+=(Point rhs) &
	{
		x += rhs.x, y += rhs.y;
		return *this;
	}
	constexpr Point &operator+=(T rhs) &
	{
		x += rhs, y += rhs;
		return *this;
	}
	constexpr Point &operator-=(Point rhs) &
	{
		x -= rhs.x, y -= rhs.y;
		return *this;
	}
	constexpr Point &operator-=(T rhs) &
	{
		x -= rhs, y -= rhs;
		return *this;
	}
	constexpr Point &operator*=(T rhs) &
	{
		x *= rhs, y *= rhs;
		return *this;
	}
	constexpr Point &operator/=(T rhs) &
	{
		x /= rhs, y /= rhs;
		return *this;
	}
	constexpr Point operator-() const 
	{ 
		return Point(-x, -y); 
	}
	friend constexpr Point operator+(Point lhs, Point rhs)
	{
		Point res = lhs;
		res += rhs;
		return res;
	}
	friend constexpr Point operator-(Point lhs, Point rhs)
	{
		Point res = lhs;
		res -= rhs;
		return res;
	}
	friend constexpr Point operator+(Point lhs, T rhs)
	{
		Point res = lhs;
		res += rhs;
		return res;
	}
	friend constexpr Point operator-(Point lhs, T rhs)
	{
		Point res = lhs;
		res -= rhs;
		return res;
	}
	friend constexpr std::istream &operator>>(std::istream &is, Point &p) 
    {
        return is >>p.x >>p.y;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Point &p) 
    {
        return os <<p.x <<" " <<p.y;
    }
};

template<class T> T cross(Point<T> a, Point<T> b)
{
	return a.x * b.y - a.y * b.x;
}