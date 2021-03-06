#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Vector2 { 
	public: float x,y; 

	Vector2(float a, float b):x(a),y(b){}

	float dot(Vector2 v){
		return (x * v.x + y * v.y);
	}
	Vector2 operator - (Vector2 v) const
	{ return Vector2(x - v.x, y - v.y); }
	Vector2 operator + (Vector2 v) const
	{ return Vector2(x + v.x, y + v.y); }

	Vector2 operator * (float f) const{
		return Vector2(x*f,y*f);
	}
};
typedef Vector2 Point2;

bool inside(Point2 V, Point2 P, Vector2 n){

	return (((V-P).dot(n))<0);

}

Point2 intersection(Point2 C, Point2 D,Point2 P, Vector2 n){

	Vector2 u = D - C;
	Vector2 v = C - P;

	float t = -(v.dot(n))/(u.dot(n));

	Point2 iPt = C*(1-t) + D*t;

	return iPt;

}

vector<Point2> clip(vector<Point2> sourcePoly,Point2 P, Vector2 n){

	vector<Point2> result;
	Point2 D = sourcePoly[sourcePoly.size() - 1]; 
	bool Din = inside(D,P,n);
	if(Din){result.push_back(D);}

	for(int i = 0; i<sourcePoly.size();++i){
		Point2 C = D;
		bool Cin = Din;
		D = sourcePoly[i];
		Din = inside(D,P,n);
		if(Din != Cin){result.push_back(intersection(C,D,P,n));}
		if(Din){result.push_back(D);}
	}
	
	return result;

}

vector<Point2> polyClip(vector<Point2> boundaryPoly,vector<Point2> sourcePoly){

	for(int i = 0; i<boundaryPoly.size();i++){
		if(i == boundaryPoly.size()-1){
			sourcePoly = clip(sourcePoly,boundaryPoly[i],Vector2(boundaryPoly[i].y-boundaryPoly[0].y,boundaryPoly[0].x-boundaryPoly[i].x));
		}else{
			sourcePoly = clip(sourcePoly,boundaryPoly[i],Vector2(boundaryPoly[i].y-boundaryPoly[i+1].y,boundaryPoly[i+1].x-boundaryPoly[i].x));
		}

	}
	return sourcePoly;

}

bool comparePoint(Point2 p1 , Point2 p2){
	if(p1.x != p2.x){
		return p1.x>p2.x;
	}else if(p1.y != p2.y){
		return p1.y>p2.y;
	}
}

bool equalPoint(Point2 p1, Point2 p2){
	if(p1.x == p2.x && p1.y == p2.y){return true;}
	else{return false;}
}

int main(){


	vector<Point2> boundaryPoly;
	vector<Point2> sourcePoly;

	boundaryPoly.push_back(Point2(1,1));
	boundaryPoly.push_back(Point2(1,-1));
	boundaryPoly.push_back(Point2(-1,-1));
	boundaryPoly.push_back(Point2(-1,1));

	sourcePoly.push_back(Point2(0,1.5f));
	sourcePoly.push_back(Point2(1.5f,0));
	sourcePoly.push_back(Point2(0,-1.5f));
	sourcePoly.push_back(Point2(-1.5f,0));

	// sourcePoly.push_back(Point2(0,1));
	// sourcePoly.push_back(Point2(1,0));
	// sourcePoly.push_back(Point2(0,-1));
	// sourcePoly.push_back(Point2(-1,0));

	sourcePoly = polyClip(boundaryPoly,sourcePoly);

	std::sort(sourcePoly.begin(),sourcePoly.end(),comparePoint);
	auto unique_end = unique(sourcePoly.begin(),sourcePoly.end(),equalPoint);
	sourcePoly.erase(unique_end,sourcePoly.end());


	for(int i = 0;i<sourcePoly.size();i++){
		cout<<sourcePoly[i].x<<" "<<sourcePoly[i].y<<endl;
	}
}

