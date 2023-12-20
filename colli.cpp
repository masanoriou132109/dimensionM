#include"colli.hpp"
using namespace std;
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
void drawPolygon(SDL_Renderer *renderer, Polygon polygon) {  //這坨也不用 
    for (int i = 0; i < polygon.vertex; i++) {
        int next = (i + 1 == polygon.vertex) ? 0 : i + 1;
        SDL_RenderDrawLine(renderer, polygon.point[i].x, polygon.point[i].y, polygon.point[next].x, polygon.point[next].y);
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
