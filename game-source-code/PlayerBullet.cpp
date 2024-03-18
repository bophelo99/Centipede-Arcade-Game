#include "PlayerBullet.h"

struct PlayerBulletDimensions PlayerBullet::dimensions_;

PlayerBullet::PlayerBullet(positionHandler position, const ScreenParameters& grid):
    position_{position},
    grid_{grid},
    direction_{objectsDirection::UP},
    alive_{true}
{

}

void PlayerBullet::move()
{
    auto newYPos = position_.getY_position() - dimensions_.speed;
    auto half = 2.0f;
    if(newYPos > (dimensions_.height/half)) position_.setYposition(newYPos);
    else eliminated();
}

objectsDirection PlayerBullet::getDirection() const
{
    return direction_;
}

void PlayerBullet::setDirection(objectsDirection direction)
{
    direction_ = direction;
}

movingObjetsType PlayerBullet::getObjectType() const
{
    return movingObjetsType::BULLET;
}

positionHandler PlayerBullet::getPosition() const
{
    return position_;
}

boundaryHandler PlayerBullet::getBoundary()
{
    boundaryHandler boundaryHandler_(dimensions_.width, dimensions_.height, 0.f, position_);
    return boundaryHandler_;
}

bool PlayerBullet::isAlive() const
{
    return alive_;
}

void PlayerBullet::eliminated()
{
    alive_ = false;
}

void PlayerBullet::reincarnate()
{

}

int PlayerBullet::getLives() const
{
    if(isAlive()) return 1;
    return 0;
}

bool PlayerBullet::isPoisoned() const
{
    return false;
}

void PlayerBullet::poison()
{
    return;
}

int PlayerBullet::getPoints() const
{
    return 0;
}

PlayerBullet::~PlayerBullet()
{
    //dtor
}
