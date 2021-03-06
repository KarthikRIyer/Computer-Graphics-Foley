#include<iostream>
#include<vector>
#include <math.h>

using namespace std;

class Vector2 { 
	public: float x,y; 

	Vector2(){}
	Vector2(float a, float b):x(a),y(b){}
	Vector2 operator + (Vector2 v) const
    { return Vector2(x + v.x, y + v.y); }
    Vector2 operator - (Vector2 v) const
    { return Vector2(x - v.x, y - v.y); }
    Vector2 operator * (float f) const
    { return Vector2(x*f,y*f); }
    Vector2 operator - () const
    { return Vector2(-x,-y); }
    Vector2 operator / (float f) const
    { return Vector2(x/f,y/f); }
    float dot(const Vector2& v){
		return (x * v.x + y * v.y);
	}
	float length(){
		return (sqrt(x*x+y*y));
	}
	static Vector2 unitY(){return Vector2(0.0f,1.0f);}
	static Vector2 unitX(){return Vector2(1.0f,0.0f);}

	Vector2 max(Vector2 v){
		float a,b;
		if(y<=v.y){
			b = v.y;
		}else{b = y;}
		if(x<=v.x){
			a = v.x;
		}else{a = x;}

		return Vector2(a,b);
	}

	Vector2 min(Vector2 v){
		
		float a,b;
		if(y>=v.y){
			b = v.y;
		}else{b = y;}
		if(x>=v.x){
			a = v.x;
		}else{a = x;}

		return Vector2(a,b);

	}

};

class Vector3 { 
	public: 
	float x,y,z;
	Vector3 operator + (Vector3 v) const
    { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator - (Vector3 v) const
    { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator * (float f) const
    { return Vector3(x*f,y*f,z*f); }
    Vector3 operator - () const
    { return Vector3(-x,-y,-z); }
    Vector3 operator / (float f) const
    { return Vector3(x/f,y/f,z/f); }
    void operator += (Vector3 c){x+=(c.x); y+=(c.y); z+=(c.z);}
	Vector3(float a, float b,float c):x(a),y(b),z(c){}
	Vector3():x(0),y(0),z(0){}
	Vector3 direction() const{
	return Vector3(x/sqrt(x*x+y*y+z*z),y/sqrt(x*x+y*y+z*z),z/sqrt(x*x+y*y+z*z));
					}
	Vector3 cross(Vector3 v){
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	float dot(Vector3 v){
		return (x * v.x + y * v.y + z * v.z);
	}
	float length() const{
		return (sqrt(x*x+y*y+z*z));
	}
	static Vector3 unitY(){return Vector3(0.0f,1.0f,0.0f);}
	static Vector3 unitX(){return Vector3(1.0f,0.0f,0.0f);}
	static Vector3 unitZ(){return Vector3(0.0f,0.0f,1.0f);}
 };

typedef Vector2 Point2;
typedef Vector3 Point3;

class Color3 { 
	public: float r,g,b; 
			Color3(){}
			Color3(float a, float b, float c):r(a),g(b),b(c){}
			Color3(Vector3 v):r(v.x),g(v.y),b(v.z){}
			Color3(const Color3& c):r(c.r),g(c.g),b(c.b){}
			Color3 operator / (float f) const{return Color3(r/f,g/f,b/f);}
			Color3 operator * (Color3 c) const{return(Color3(r*c.r, g*c.g, b*c.b));}
			Color3 operator * (float f) const{return Color3(r*f,g*f,b*f);}
			void operator += (Color3 c){r+=(c.r); g+=(c.g); b+=(c.b);}
			Color3 operator + (Color3 c) const{return Color3(r+c.r,g+c.g,b+c.b);}

			static Color3 red(){return Color3(1.0f,0.0f,0.0f);}
			static Color3 green(){return Color3(0.0f,1.0f,0.0f);}
			static Color3 blue(){return Color3(0.0f,0.0f,1.0f);}
			static Color3 white(){return Color3(1.0f,1.0f,1.0f);}
			static Color3 indigo(){return Color3(0.05f,0.31f,0.55f);}
			static Color3 yellow(){return Color3(0.93f,0.93f,0.0f);}
			static Color3 violet(){return Color3(0.93,0.51f,0.93f);}
			static Color3 orange(){return Color3(0.8f,0.2f,0.2f);}
			static Color3 black(){return Color3(0.0f,0.0f,0.0f);}
};


typedef Color3 Radiance3;
typedef Color3 Power3;

//distance of point Q from line containing points A & B
float lineDistance2D(const Point2& A,const Point2& B, const Point2& Q){

	Vector2 n(A.y - B.y, B.x - A.x);
	const float d = A.x*B.y - B.x*A.y;
	return (n.dot(Q)+d)/n.length();
}

float bary2D(const Point2& A, const Point2& B, const Point2& C, const Point2& Q){
	return ((lineDistance2D(B,C,Q))/(lineDistance2D(B,C,A)));
}

class Ray{
	private: 
		Point3 m_origin;
		Vector3 m_direction;
	public: 
		Ray(Point3 org, Vector3 dir): m_origin(org),m_direction(dir){}

		Point3 origin() const {return m_origin;}
		Vector3 direction() const {return m_direction;}
};

class Image{

private: 
	int m_width;
	int m_height;
	std::vector<Radiance3> m_data;	

	int PPMGammaEncode(float radiance,float displayConstant) const;

public:
	Image(int width,int height): m_width(width),m_height(height),m_data(width*height){}

	int width() const{return m_width;}
	int height() const{return m_height;}

	void set(int x,int y,Radiance3 value){
		m_data[x+y*m_width] = value;
	}

	const Radiance3& get(int x,int y) const{
		return m_data[x+y*m_width];
	}

	void save(const std::string& filename,float displayConstant = 15.0f) const;

};

int Image::PPMGammaEncode(float radiance, float d) const{
	return int(pow(std::min(1.0f,std::max(0.0f,radiance*d)),1.0f/2.2f)*255.0f);
}

void Image::save(const std::string& filename,float d) const{
	FILE* file = fopen(filename.c_str(),"wt");
	fprintf(file,"P3 %d %d 255\n",m_width,m_height);
	for(int y = 0;y<m_height;++y){
		fprintf(file, "\n# y = %d\n", y);
		for(int x = 0;x<m_width;++x){
			const Radiance3& c(get(x,y));
			fprintf(file, "%d %d %d\n", PPMGammaEncode(c.r, d)
									  , PPMGammaEncode(c.g, d)
									  , PPMGammaEncode(c.b, d));
		}
	}
	fclose(file);
}

class DepthBuffer{

private: 
	int m_width;
	int m_height;
	std::vector<float> m_depth;	

public:
	DepthBuffer(int width,int height): m_width(width),m_height(height),m_depth(width*height){}

	DepthBuffer(int width,int height, float initialValue): m_width(width),m_height(height),m_depth(width*height,initialValue){}

	int width() const{return m_width;}
	int height() const{return m_height;}

	void set(int x,int y,float value){
		m_depth[x+y*m_width] = value;
	}

	const float& get(int x,int y) const{
		return m_depth[x+y*m_width];
	}

};

class BSDF{
public:
	Color3 k_L;
	Color3 k_G;
	float sharpness = 100.0f;
	BSDF(){}
	BSDF(Color3 lambert, Color3 gloss, float sharp):k_L(lambert),k_G(gloss),sharpness(sharp){}

	Color3 evaluateFiniteScatteringDensity(const Vector3& w_i,const Vector3& w_o,const Vector3& n) const{
		Vector3 w_h = (w_i + w_o).direction();
		return (k_L + k_G*((sharpness+8.0f)*powf(std::max(0.0f,w_h.dot(n)),sharpness)/8.0f))/M_PI;
	}
};

class Triangle{
private: 
	Point3 m_vertex[3];
	Vector3 m_normal[3];
	BSDF m_bsdf;

public:
	Triangle( Vector3 v0, Vector3 v1, Vector3 v2,
              Vector3 n0, Vector3 n1, Vector3 n2, BSDF bsdf): m_bsdf(bsdf){
        m_vertex[0] = v0;  m_normal[0] = n0;
        m_vertex[1] = v1;  m_normal[1] = n1;
        m_vertex[2] = v2;  m_normal[2] = n2;
    }
	Point3 vertex(int i) const{return m_vertex[i];}
	Vector3 normal(int i) const{return m_normal[i];}
	BSDF bsdf() const{return m_bsdf;}

};

class Light{
public:
	Point3 position;
	Power3 power;
};

class Scene{
public:
	std::vector<Triangle> triangleArray;
	std::vector<Light> lightArray;
	Scene(){}
};

class Camera{
public:
	float zNear;
	float zFar;
	float fieldOfViewX;

	Camera() : zNear(-1.0f), zFar(-100.0f), fieldOfViewX(M_PI/2.0f){}
};

Ray computeEyeRay(float x, float y, int width, int height, const Camera& camera){

	const float aspect = float(height)/float(width);

	const float s = -2.0*tan(camera.fieldOfViewX*0.5f);

	Vector3 start = Vector3(-(x/width - 0.5f)*s , (y/height - 0.5f)*s*aspect,1.0f*camera.zNear);

	return Ray(start,start.direction());

}

Vector2 perspectiveProject(Vector3 P, int width, int height,const Camera& camera){
	Vector2 Q(-P.x/P.z,-P.y/P.z);
	const float aspect = float(height)/width;

	const float s = -2.0*tan(camera.fieldOfViewX*0.5f);

	Q.x = width*(-Q.x/s + 0.5f);
	Q.y = height*(Q.y/(s*aspect) + 0.5f);

	return Q;

}

void computeBoundingBox(const Triangle& T, const Camera& camera, const Image& image, Point2 V[3], int& x0, int& y0, int& x1, int& y1){

	const int w = image.width();
	const int h = image.height();

	Vector2 high(w,h);
	Vector2 low(0,0);

	for(int i = 0 ; i < 3 ; ++i){
		const Point2& X = perspectiveProject(T.vertex(i),w,h,camera);
		V[i] = X;
		high = high.max(X);
		low = low.min(X);
	}

	x0 = (int)floor(low.x);
	y0 = (int)floor(low.y);
	x1 = (int)floor(high.x);
	y1 = (int)floor(high.y);

	if(x0<0){x0=0;}
	if(y0<0){y0=0;}
	if(x1>w){x1=w;}
	if(y1>h){y1=h;}	

}

float intersectT(Ray& R,const Triangle& T, float weight[3]){

	Vector3 e1 = T.vertex(1) - T.vertex(0);
	Vector3 e2 = T.vertex(2) - T.vertex(0);
	Vector3 q = R.direction().cross(e2);

	float  a = e1.dot(q);

	Vector3 s = R.origin() - T.vertex(0);
	Vector3 r = s.cross(e1);

	weight[1] = s.dot(q) / a;
	weight[2] = R.direction().dot(r) / a;
	weight[0] = 1 - (weight[1]+weight[2]);

	const float dist = e2.dot(r) / a;

	static const float epsilon = 1e-7f;
	static const float epsilon2 = 1e-10f;

	if((a<=epsilon) || (weight[0]<-epsilon2) || (weight[1]<-epsilon2) || (weight[2]<-epsilon2) || (dist<=0.0f)){
		return INFINITY;
	}else{
		return dist;
	}
}

bool visible(const Point3& P, Vector3& direction, float distanceToLight, const Scene& scene){

	static const float rayBumpEpsilon = 1e-4;
	Ray shadowRay = Ray(P+(direction*rayBumpEpsilon),direction);
	distanceToLight -= rayBumpEpsilon;
	float ignore[3];
	for(unsigned int i = 0;i < scene.triangleArray.size();++i){
		if(intersectT(shadowRay,scene.triangleArray[i],ignore) < distanceToLight){
			return false;
		}
	}
	return true;
}

void shade(const Scene& scene, Triangle& T,const Point3& P,const Vector3& n,const Vector3& w_o, Radiance3& L_o){
	L_o = Color3(0.0f,0.0f,0.0f);

	for(unsigned int i =0; i<scene.lightArray.size();i++){
		Light light = scene.lightArray[i];

		Vector3 offset = light.position - P;
		float distanceToLight = offset.length();
		Vector3 w_i = offset/distanceToLight;

		if(visible(P ,w_i ,distanceToLight ,scene)){
			Radiance3 L_i = light.power / (4*M_PI*distanceToLight*distanceToLight);
			
			L_o += (L_i*T.bsdf().evaluateFiniteScatteringDensity(w_i,w_o,n))*std::max(0.0f,w_i.dot(n));
	
		}
	}

}


bool sampleRayTriangle(const Scene& scene, int x, int y, Ray& R, Triangle& T, Radiance3& radiance, float& distance){
	float weight[3];
	const float d  = intersectT(R,T,weight);

	if(d >= distance){
		return false;
	}

	distance = d;

	Point3 P = R.origin() + R.direction()*d;

	Vector3 n = (T.normal(0)*weight[0] + T.normal(1)*weight[1] + T.normal(2)*weight[2]).direction();

	Vector3 w_o = -R.direction();

	shade(scene, T, P, n, w_o, radiance);

	return true;
}

void rasterize(Image image,const Scene& scene,Camera& camera){

	const int w = image.width();
	const int h = image.height();
	
	DepthBuffer depthBuffer(w,h,INFINITY);

	//for each triangle
	for(unsigned int i = 0 ; i < scene.triangleArray.size() ; ++i){

		Triangle T = scene.triangleArray[i];

		//projected vertices
		Vector2 V[3];
		int x0,y0,x1,y1;
		computeBoundingBox(T,camera,image,V,x0,y0,x1,y1);	

		//vertex attributes divided by -z		
		float vertexW[3];
		Vector3 vertexNw[3];
		Point3 vertexPw[3];
		for(int j = 0; j < 3; ++j){
			const float w = -1.0f/T.vertex(j).z;
			vertexW[j] = w;
			vertexPw[j] = T.vertex(j)*w;
			vertexNw[j] = T.normal(j)*w;
		}

		//for each pixel
		for (int y = y0 ; y < y1 ; ++y){
			for (int x = x0; x < x1; ++x)
			{	
				//pixel center
				const Point2 Q(x+0.5f,y+0.5f);

				//2D barycentric weights
				const float weight2D[3] = {bary2D(V[0],V[1],V[2],Q),bary2D(V[1],V[2],V[0],Q),bary2D(V[2],V[0],V[1],Q)};

				if(weight2D[0]>0 && weight2D[1]>0 && weight2D[2]>0){
					//interpolate depth
					float w = 0.0f;
					for(int k = 0; k<3; ++k){
						w += weight2D[k] * vertexW[k];
					}
					Point3 pW = Point3();
					Vector3 nW = Vector3();
					//interpolate projective attributes
					for(int k = 0;k<3;++k){
						pW += vertexPw[k]*weight2D[k];
						nW += vertexNw[k]*weight2D[k];
					}

					//recover interpolated attributes
					const Point3& P = pW/w;
					const Vector3& n = nW/w;

					const float depth = P.length();

					//depth test
					if(depth<depthBuffer.get(x,y)){
						//shade
						Radiance3 L_o;
						const Vector3& w_o = -P.direction();

						//make surface normal of unit length
						const Vector3& unitN = n.direction();

						shade(scene,T,P,unitN,w_o,L_o);
						depthBuffer.set(x,y,depth);
						image.set(x,y,L_o);
					}
				}
			}
		}

	}


	image.save("result_rasterize_3.ppm",2.0f);
}

void lightScene(Scene& scene){

	
	scene.lightArray.resize(1);
	scene.lightArray[0].position = Point3(1, 3, 1);
	scene.lightArray[0].power = Color3(1.0f,1.0f,1.0f)*20.0f;
	

}

void triangleGroundScene(Scene& scene){
	lightScene(scene);

	scene.triangleArray.push_back(Triangle(Vector3(-0.5,1.7,-3), Vector3(-2.4,-0.5,-3), Vector3(1.1,0,-3),Vector3(0,0.6f,1).direction(),Vector3(-0.4f,-0.4f, 1.0f).direction(),Vector3(0.4f,-0.4f, 1.0f).direction(), BSDF(Color3::green()*0.8,Color3::white()*0.2f,100.0f)));
	scene.triangleArray.push_back(Triangle(Vector3(-2.4,-0.5,-3),Vector3(-0.5,1.7,-3), Vector3(1.1,0,-3),Vector3(0,0.6f,1).direction(),Vector3(-0.4f,-0.4f, 1.0f).direction(),Vector3(0.4f,-0.4f, 1.0f).direction(), BSDF(Color3::green()*0.8,Color3::white()*0.2f,100.0f)));

	const float groundY = -1.0f;

	scene.triangleArray.push_back(Triangle(Vector3(-10, groundY, -10), Vector3(-10, groundY, -0.01f),Vector3(10, groundY, -0.01f),Vector3::unitY(), Vector3::unitY(), Vector3::unitY(), BSDF(Color3::white()*0.8f,Color3::white()*0.2f,100.0f)));
	scene.triangleArray.push_back(Triangle(Vector3(-10, groundY, -10), Vector3(10, groundY, -0.01f),Vector3(10, groundY, -10),Vector3::unitY(), Vector3::unitY(), Vector3::unitY(), BSDF(Color3::white()*0.8f,Color3::white()*0.2f,100.0f)));

}

int main(){
	Image image = Image(800,500);
	Camera camera;
	Scene scene = Scene();		
	triangleGroundScene(scene);
	rasterize(image,scene,camera);
}