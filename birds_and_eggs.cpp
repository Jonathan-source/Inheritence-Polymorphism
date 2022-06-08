#include <iostream>
#include <memory>

class IBird;

class Egg {
public:
    Egg(std::shared_ptr<IBird> (*createBirdFunc)()) : m_createFunc(createBirdFunc), m_hasHatched(false) {}
    virtual ~Egg() = default;

    std::shared_ptr<IBird> Hatch()
    {
        if (!m_hasHatched)
        {
            std::cout << "It's Alive!" << std::endl;
            m_hasHatched = true;
            return m_createFunc();
        }
        else
        {
            std::cout << "Egg already hatched" << std::endl;
        }

        return nullptr;
    }

private:
    std::shared_ptr<IBird>(*m_createFunc)();
    bool m_hasHatched;
};


class IBird {
public:
    virtual ~IBird() = default;
    virtual Egg LayEgg() = 0;
    virtual void Sound() = 0;
};


class Chicken : public IBird {
public:
    Chicken() { std::cout << "A " << __func__ << std::endl; }
    virtual ~Chicken() = default;

    Egg LayEgg() override
    {
        return { []() -> std::shared_ptr<IBird> { return std::make_shared<Chicken>(); } };
    }

    void Sound() override
    {
        std::cout << "Bawk!" << std::endl;
    }
};


class Duck : public IBird {
public:
    Duck() { std::cout << "A " << __func__ << std::endl; }
    virtual ~Duck() = default;

    Egg LayEgg() override
    {
        return { []() -> std::shared_ptr<IBird> { return std::make_shared<Duck>(); } };
    }

    void Sound() override
    {
        std::cout << "Quack!" << std::endl;
    }
};


int main()
{
    std::cout << "<Chicken_Section>" << std::endl;

    auto pChicken = std::make_unique<Chicken>();
    Egg chickenEgg = pChicken->LayEgg();
    auto pLittleChicken = chickenEgg.Hatch();
    pLittleChicken->Sound();
    //chickenEgg should be already hatched
    chickenEgg.Hatch();

    std::cout << "</Chicken_Section>\n" << std::endl;
    std::cout << "<Duck_Section>" << std::endl;

    auto pDuck = std::make_unique<Duck>();
    Egg duckEgg = pDuck->LayEgg();
    auto pDuckling = duckEgg.Hatch();
    pDuckling->Sound();
    //duckEgg should be already hatched
    duckEgg.Hatch();

    std::cout << "</Duck_Section>" << std::endl;

    return 0;
}
