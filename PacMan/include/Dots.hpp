// Dots.hpp

#ifndef INCLUDE_DOTS_
#define INCLUDE_DOTS_

#include "SFML/Graphics.hpp"
#include "Map.hpp"

class Dots
{
public:
    Dots(const int*, int, int);
    void setDots(const int*, int, int);
    sf::CircleShape** getDotsPtr();
    sf::CircleShape** getEnergizersPtr();
    int getNumDots();
    int getNumEnergizers();
    void nullDotPtr(int);
    void nullEnergizerPtr(int);
    void resetPtrs();
private:
    static const int numDots{ 284 };     // 284
    static const int numEnergizers{ 4 }; // 4
    sf::CircleShape dots[numDots];
    sf::CircleShape* dotsPtr[numDots]{nullptr};
    sf::CircleShape energizers[numEnergizers];
    sf::CircleShape* energizersPtr[numEnergizers]{ nullptr };
};

#endif /* INCLUDE_DOTS_ */
