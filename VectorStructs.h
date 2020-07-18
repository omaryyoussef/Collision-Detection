

struct Vector2D
{
	double x;
	double y;

	Vector2D(): x(0), y(0){}
	Vector2D(double x1,double x2): x(x1),y(x2){}
	
	Vector2D operator-(const Vector2D& b)
	{
		Vector2D c;
		c.x = x-b.x;
		c.y = y-b.y;
		return c;
	}

	double operator*(const Vector2D& b) //DotProduct!
	{
		return x*b.x+y*b.y;
	}
};

struct Vector3D
{
	double x;
	double y;
	double z;
	
	Vector3D(): x(0), y(0), z(0){}
	Vector3D(double x1,double x2,double x3): x(x1),y(x2),z(x3){}

	

	Vector3D operator-(const Vector3D& b)
	{
		Vector3D c;
		c.x = x-b.x;
		c.y = y-b.y;
		c.z = z-b.z;
		return c;
	}

	Vector3D operator+(const Vector3D& b)
	{
		Vector3D c;
		c.x = x+b.x;
		c.y = y+b.y;
		c.z = z+b.z;
		return c;
	}

	bool operator==(const Vector3D& b)
	{
		if(x != b.x) return false;
		if(y != b.y) return false;
		if(z != b.z) return false;
		return true;
	}

	double operator*(const Vector3D& b) //DotProduct!
	{
		return x*b.x+y*b.y+z*b.z;
	}

	Vector3D operator*(double b) //scalar multiplication
	{
		Vector3D c;
		c.x = x*b; 
		c.y= y*b; 
		c.z = z*b;
		return c;
	}

	Vector3D crossproduct(const Vector3D& b)
	{
		Vector3D c;
		c.x = y*b.z-z*b.y;
		c.y = z*b.x - x*b.z;
		c.z = x*b.y - y*b.x;
		return c;
	}

	double norm()
	{
		return std::sqrt(x*x+y*y+z*z);
	}

};