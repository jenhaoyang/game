#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class SFMLDebugDraw : public b2Draw
{
    public:
        SFMLDebugDraw(sf::RenderWindow &window);

        static sf::Color b2ColorToSFColor(const b2Color& color);
        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}
        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}
        void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {}
        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
        void DrawTransform(const b2Transform& xf) {}

    private:
        sf::RenderWindow *window;
};
