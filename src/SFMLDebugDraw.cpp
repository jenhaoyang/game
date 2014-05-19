#include "SFMLDebugDraw.h"
#include "Globals.h"

SFMLDebugDraw::SFMLDebugDraw(sf::RenderWindow &window) {
        this->window = &window;
}

sf::Color SFMLDebugDraw::b2ColorToSFColor(const b2Color& color) {
    return sf::Color(color.r * 255, color.g * 255, color.b * 255);
}

void SFMLDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape shape;
    shape.setFillColor(b2ColorToSFColor(color));
    shape.setPointCount(vertexCount);
    for (int32 i = 0; i < vertexCount; i++)
        shape.setPoint(i, sf::Vector2f(vertices[i].x * PM, vertices[i].y * PM));
    window->draw(shape);
}
