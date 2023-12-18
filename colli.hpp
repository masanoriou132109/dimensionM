#ifndef colli
#define colli
#include<cmath>
#include <SDL.h>
#include <iostream>
using namespace std;

struct vec {
    float x;
    float y;
};

class Polygon //多邊形 
{
public:
    vec point[15] = {};
    int vertex;
public:
    Polygon() {}

    Polygon(vec *a, int b) {
        vertex = b;
        for (int i = 0; i < vertex; i++) {
            point[i] = a[i];
        }
    }

    vec vectorBetweenPoints(vec p1, vec p2) {
        vec v;
        v.x = p2.x - p1.x;
        v.y = p2.y - p1.y;
        return v;
    }

    vec perpendicular(vec v) {
        vec p;
        p.x = -v.y;
        p.y = v.x;
        return p;
    }

    float dotProduct(vec v1, vec v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    void projectPolygon(vec axis, Polygon polygon, float *min, float *max) {
        float dot = dotProduct(axis, polygon.point[0]);
        *min = dot;
        *max = dot;
        for (int i = 1; i < polygon.vertex; i++) {
            dot = dotProduct(axis, polygon.point[i]);
            if (dot < *min) {
                *min = dot;
            } else if (dot > *max) {
                *max = dot;
            }
        }
    }

    bool overlap(float minA, float maxA, float minB, float maxB) {
        return minB <= maxA && minA <= maxB;
    }

    bool operator&&(Polygon poly2) //檢測多邊形撞多邊形 
	{
        vec axis;
        float minA, maxA, minB, maxB;
        for (int i = 0; i < vertex; i++) {
            int next = (i + 1 == this->vertex) ? 0 : i + 1;
            axis = perpendicular(vectorBetweenPoints(this->point[i], this->point[next]));
            projectPolygon(axis, *this, &minA, &maxA);
            projectPolygon(axis, poly2, &minB, &maxB);
            if (!overlap(minA, maxA, minB, maxB)) {
                return false;
            }
        }

        // Check edges of poly2 as well
        for (int i = 0; i < poly2.vertex; i++) 
		{
            int next = (i + 1 == poly2.vertex) ? 0 : i + 1;
            axis = perpendicular(vectorBetweenPoints(poly2.point[i], poly2.point[next]));
            projectPolygon(axis, *this, &minA, &maxA);
            projectPolygon(axis, poly2, &minB, &maxB);
            if (!overlap(minA, maxA, minB, maxB)) {
                return false;
            }
        }

        return true;
    }
    bool containsPoint(const vec &po) const 
	{
	    bool result = false;
	    int j = vertex - 1;
	    for (int i = 0; i < vertex; i++) {
	        if ((point[i].y < po.y && point[j].y >= po.y) || 
	            (point[j].y < po.y && point[i].y >= po.y)) 
			{
	            if (point[i].x + (po.y - point[i].y) / (point[j].y - point[i].y) * (point[j].x - point[i].x) < po.x) 
				{
	                result = !result;
	            }
	        }
	        j = i;
	    }
	    return result;
	}
};

class circle
{   

    // ... [Other methods of the circle class]
    friend class Polygon;//這行沒鳥用 寫給謝老頭爽 
    friend void drawCircle(SDL_Renderer* renderer, const circle& c);
	public:
		float radius;
		vec center;
	public:
		circle(float r, vec c) : radius(r), center(c) {};
		vec vectorBetweenPoints(vec p1, vec p2) 
		{
	        vec v;
	        v.x = p2.x - p1.x;
	        v.y = p2.y - p1.y;
	        return v;
        }
        float dotProduct(vec v1, vec v2) {
        return v1.x * v2.x + v1.y * v2.y;
        }
		float distance_from_center_to_vector(vec v0, vec v1, vec Center)
		{
			vec c = vectorBetweenPoints(v0,v1);
			vec d=vectorBetweenPoints(v0,Center);
			float cross=c.x*d.y-c.y*d.x;
			return cross/sqrt(c.x*c.x+c.y*c.y);
			
		}
		float distance_(vec c1,vec c2)
		{
			vec c = vectorBetweenPoints(c1 , c2);
			return sqrt(c.x*c.x+c.y*c.y);
			
		}
		bool check_circle_collide_with_circle(circle a,circle b)//圓形撞圓形我用距離判斷 
		{
			if(distance_(a.center,b.center)<=(a.radius+b.radius))
			return true;
			else 
			return false;
		}	
		vec projectionOntoSegment(const vec& v1, const vec& v2, const vec& point) {
        vec line = vectorBetweenPoints(v1, v2);
        vec pointVector = vectorBetweenPoints(v1, point);

        float lineLengthSquared = line.x * line.x + line.y * line.y;
        float dotProductResult = dotProduct(pointVector, line) / lineLengthSquared;

        vec projection;
        projection.x = v1.x + dotProductResult * line.x;
        projection.y = v1.y + dotProductResult * line.y;
        return projection;
    }

    // Function to check if a point is within a line segment
    bool isWithinSegment(const vec& projection, const vec& v1, const vec& v2) {
        float minX = min(v1.x, v2.x);
        float maxX = max(v1.x, v2.x);
        float minY = min(v1.y, v2.y);
        float maxY = max(v1.y, v2.y);

        return projection.x >= minX && projection.x <= maxX && 
               projection.y >= minY && projection.y <= maxY;
    }
};
	
bool collide(circle &cir, Polygon &poly) { ///這是最核心的SAT 圓形撞多邊形 
    // First, check potential separating axes from polygon edges
    for (int i = 0; i < poly.vertex; i++) {
        int next = (i + 1 == poly.vertex) ? 0 : i + 1;
        vec axis = poly.perpendicular(poly.vectorBetweenPoints(poly.point[i], poly.point[next]));

        // Normalize the axis for correct projection calculation
        float axisLength = sqrt(axis.x * axis.x + axis.y * axis.y);
        axis.x /= axisLength;
        axis.y /= axisLength;

        // Project polygon and circle onto the axis
        float minPoly, maxPoly;
        poly.projectPolygon(axis, poly, &minPoly, &maxPoly);
        float circleProjection = poly.dotProduct(axis, cir.center);
        float minCircle = circleProjection - cir.radius;
        float maxCircle = circleProjection + cir.radius;

        // Check for overlap
        if (!poly.overlap(minPoly, maxPoly, minCircle, maxCircle)) {
            return false; // Separating axis found, no collision
        }
    }
    return true;
}
void drawPolygon(SDL_Renderer *renderer, Polygon *polygon) {  //這坨也不用 
    for (int i = 0; i < polygon->vertex; i++) {
        int next = (i + 1 == polygon->vertex) ? 0 : i + 1;
        SDL_RenderDrawLine(renderer, polygon->point[i].x, polygon->point[i].y, polygon->point[next].x, polygon->point[next].y);
    }
}
void drawCircle(SDL_Renderer* renderer, const circle& c) {
    const int diameter = (c.radius * 2);

    int x = (c.radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y) {
        // Each of these lines draws a pair of points at each quadrant
        SDL_RenderDrawPoint(renderer, c.center.x + x, c.center.y - y);
        SDL_RenderDrawPoint(renderer, c.center.x + x, c.center.y + y);
        SDL_RenderDrawPoint(renderer, c.center.x - x, c.center.y - y);
        SDL_RenderDrawPoint(renderer, c.center.x - x, c.center.y + y);
        SDL_RenderDrawPoint(renderer, c.center.x + y, c.center.y - x);
        SDL_RenderDrawPoint(renderer, c.center.x + y, c.center.y + x);
        SDL_RenderDrawPoint(renderer, c.center.x - y, c.center.y - x);
        SDL_RenderDrawPoint(renderer, c.center.x - y, c.center.y + x);

        if (error <= 0) {
            y++;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            x--;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
/*
int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!init(&window, &renderer)) {
        cout << "Failed to initialize!" << endl;
    } else {
        bool quit = false;
        SDL_Event e;
        float vx=0,vy=0;
        vec quadPoints[] = {{100, 100}, {200, 100}, {200, 200}, {100, 200}};
        Polygon quad(quadPoints, 4);
        vec cc;cc.x=cc.y=500;
        vec dd;dd.x=dd.y=560;
        circle a(15,cc);  
        circle b(50,dd);
        //你真正需要的是算好向量位置 不然有圖我可以算  圖形不要太扁平不然扁平那邊 會錯 
        vec pentagonPoints[] = {{300+vx, 300+vy}, {400+vx, 300+vy}, {410+vx, 350+vy}, {350+vx, 400+vy}, {250+vx, 350+vy}};
        Polygon pentagon(pentagonPoints, 5);
        vec cirpt[]={{538, 538},{523, 523},{504, 504},{484, 484},{467, 467},{455, 455},{450, 450},{452, 452},{463, 463},{479, 479},{498, 498},{518, 518},{534, 534},{546, 546},{550, 550}};
        Polygon myCircle(cirpt, 5);
        float t=0,r=0;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:    vy += -10;t=-10; break;
                        case SDLK_DOWN:  vy += 10;t=10; break;
                        case SDLK_LEFT:  vx += -10;r=-10; break;
                        case SDLK_RIGHT: vx += 10; r=10;break;
                    }
                }
            }
            a.center.x=500+vx;
            a.center.y=500+vy;
            if(collide(a, quad) )
            {
			cout<<"haha"<<endl;
            cout<<"lap"<<endl;
            a.center.x-=r;
            a.center.y-=t;
            vx-=r;
            vy-=t;
            
        }   
        if(collide(a, pentagon) )
            {
			cout<<"當掉"<<endl;
            cout<<"C--"<<endl;
            a.center.x-=r;//超級愚蠢的碰撞+反彈寫法  
            a.center.y-=t;
            vx-=r;
            vy-=t;
        }  
            if (quad&&(quad, pentagon)) {
                cout << "Collision detected!" << endl;
                a.center.x-=r;
            a.center.y-=t;
            vx-=r;
            vy-=t;
            }
            if(a.check_circle_collide_with_circle(a,b))
            {
            	cout<<"Collu"<<endl;
            	a.center.x-=r;
            a.center.y-=t;
            vx-=r;
            vy-=t;
			}
			t=0;r=0;

            //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            //SDL_RenderClear(renderer);

            //SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            //drawPolygon(renderer, &quad);

            //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            //drawPolygon(renderer, &pentagon);

            // Draw the circle using the circle object
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green color for the circle
            drawCircle(renderer, a);
            
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green color for the circle
            drawCircle(renderer, b);

            SDL_RenderPresent(renderer); 
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}*/

#endif
