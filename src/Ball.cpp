#include "Ball.h"

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Pitch.h"
#include "Paddle.h"
#include "MathUtils.h"
#include <math.h>

#include "Constants.h"

Ball::Ball(Game* pGame)
    : m_pGame(pGame)
    , m_missed(false)
{
}

Ball::~Ball()
{
    
}

bool Ball::initialise()
{
    return true;
}

void Ball::update(float deltaTime)
{
    // check ball against boundaries of the pitch
    sf::Vector2f lastPosition = getPosition();
    sf::Vector2f newPosition = lastPosition + m_velocity*deltaTime;
    
    const sf::Vector2f pitchSize = m_pGame->getPitch()->getPitchSize();
    
    float ballTopPosition = newPosition.y-BallRadius;
    if (ballTopPosition < 0.f)
    {
        newPosition.y += ballTopPosition*2.f;
        m_velocity.y = -m_velocity.y;
    }
    
    float ballBottomPosition = newPosition.y+BallRadius;
    if (ballBottomPosition > pitchSize.y)
    {
        newPosition.y -= (ballBottomPosition-pitchSize.y)*2.f;
        m_velocity.y = -m_velocity.y;
    }
    
    newPosition.y = std::clamp(newPosition.y, 0.01f+BallRadius, pitchSize.y-0.01f-BallRadius);
    
    // check ball against paddles
    const Side sideToTest = (newPosition.x < pitchSize.x*0.5f) ? Side::LEFT : Side::RIGHT;
    Paddle* pPaddleToTest = m_pGame->getPaddle(sideToTest);
    const sf::FloatRect paddleRect = pPaddleToTest->getRect();
    
    const sf::Vector2f closestPointOnPaddle(
                std::clamp(newPosition.x, paddleRect.left, paddleRect.left+paddleRect.width),
                std::clamp(newPosition.y, paddleRect.top, paddleRect.top+paddleRect.height));
    const sf::Vector2f paddleToBall = newPosition - closestPointOnPaddle;
    const bool intersects = VecLength(paddleToBall) < BallRadius;
    if (intersects)
    {
        m_velocity.x = sideToTest == Side::LEFT ? fabs(m_velocity.x) : -fabs(m_velocity.x);

        // successfull defend, add score
        m_pGame->addScore(sideToTest);
    }
    
    // set the position and check for a goal
    setPosition(newPosition);
    
    if (newPosition.x+BallRadius < 0.f
        || newPosition.x - BallRadius > pitchSize.x)
    {
        pPaddleToTest->takeDamage();
        m_missed = true;
    }
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::CircleShape circle(BallRadius, BallPoints);
    circle.setFillColor(m_color);
    circle.setPosition(getPosition()-sf::Vector2f(BallRadius, BallRadius));
    target.draw(circle);
}

void Ball::fireFromCenter()
{
    static const sf::Color colors[4] = {
        sf::Color::Green,
        sf::Color::Cyan,
        sf::Color::Yellow,
        sf::Color::Red
    };

    sf::Vector2f pitchSize = m_pGame->getPitch()->getPitchSize();
    setPosition(pitchSize*0.5f);
    
    // Random direction, speed and color
    float   random = (rand() % 1000) * 0.001f;
    float   randomAngle = random * 3.14159265359 * 2.f;
    float   speed = random * (MaxFiringSpeed - MinFiringSpeed) + MinFiringSpeed;

    m_velocity.x = sinf(randomAngle) * speed;
    m_velocity.y = cosf(randomAngle) * speed;
    m_color = colors[(int)(random * 4.f) % 4];
}
