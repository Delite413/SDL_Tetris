#pragma once
class Vector2D
{
public:
	Vector2D(int x, int y);
	Vector2D();
	~Vector2D();

	int getX() { return _x; }
	int getY() { return _y; }

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

protected:
	int _x;
	int _y;

private:

};

