#pragma once
class Vec2D {
private:
	double m_x;
	double m_y;

public:
	Vec2D();
	Vec2D(double x, double y);

	double GetX() const;
	double GetY() const;

	Vec2D& operator+=(const Vec2D& vc);
	Vec2D& operator*=(const double k);
	const bool operator==(const Vec2D& rh);

	friend Vec2D operator+ (Vec2D lv, const Vec2D& rv);
	friend Vec2D operator- (Vec2D lv, const Vec2D& rv);
	friend Vec2D operator* (double k, Vec2D rv);
	
};

struct Waypoint {
	Vec2D m_coords;
	Vec2D m_gradient;

	//coordinates in carteisan system
	Waypoint(const Vec2D& coords, const Vec2D& gradient = { 0, 0 });
	Waypoint(const Vec2D& coords, double heading); //heading in degrees

	const double GetHeading() const; //returns in radians
	const double GetHeadingInDegrees() const; //returns in degrees
};


