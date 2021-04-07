#include <iostream>

//-----------------------------------------------------------------------------
class sword
{
public:
    virtual ~sword() {};
    virtual std::string damage() const = 0;
};
//-----------------------------------------------------------------------------
class wooden_sword : public sword
{
public:
    std::string damage() const override
    {
        return "Wooden sword has little damage";
    }
};
//-----------------------------------------------------------------------------
class iron_sword : public sword
{
public:
    std::string damage() const override
    {
        return "Iron sword has medium damage";
    }
};
//-----------------------------------------------------------------------------
class gold_sword : public sword
{
public:
    std::string damage() const override
    {
        return "Golden sword has high damage";
    }
};
//-----------------------------------------------------------------------------
class bow
{
public:
    virtual ~bow() {};
    virtual std::string damage() const = 0;
};
//-----------------------------------------------------------------------------
class wooden_bow : public bow
{
public:
    std::string damage() const override
    {
        return "Wooden bow has little damage";
    }
};
//-----------------------------------------------------------------------------
class iron_bow : public bow
{
public:
    std::string damage() const override
    {
        return "Iron bow has medium damage";
    }
};
//-----------------------------------------------------------------------------
class gold_bow : public bow
{
public:
    std::string damage() const override
    {
        return "Golden bow has high damage";
    }
};
//-----------------------------------------------------------------------------
class dagger
{
public:
    virtual ~dagger() {};
    virtual std::string damage() const = 0;
};
//-----------------------------------------------------------------------------
class wooden_dagger : public dagger
{
public:
    std::string damage() const override
    {
        return "Wooden dagger has little damage";
    }
};
//-----------------------------------------------------------------------------
class iron_dagger : public dagger
{
public:
    std::string damage() const override
    {
        return "Iron dagger has medium damage";
    }
};
//-----------------------------------------------------------------------------
class gold_dagger : public dagger
{
public:
    std::string damage() const override
    {
        return "Golden dagger has high damage";
    }
};
//-----------------------------------------------------------------------------
class weapon_master
{
public:
    virtual sword* create_sword() const = 0;
    virtual bow* create_bow() const = 0;
    virtual dagger* create_dagger() const = 0;
};
//-----------------------------------------------------------------------------
class wooden_master : public weapon_master
{
public:
    sword* create_sword() const override
    {
        return new wooden_sword();
    }
    
    bow* create_bow() const override
    {
        return new wooden_bow();
    }    
    
    dagger* create_dagger() const override
    {
        return new wooden_dagger();
    }
};
//-----------------------------------------------------------------------------
class iron_master : public weapon_master
{
public:
    sword* create_sword() const override
    {
        return new iron_sword();
    }

    bow* create_bow() const override
    {
        return new iron_bow();
    }

    dagger* create_dagger() const override
    {
        return new iron_dagger();
    }
};
//-----------------------------------------------------------------------------
class gold_master : public weapon_master
{
public:
    sword* create_sword() const override
    {
        return new gold_sword();
    }

    bow* create_bow() const override
    {
        return new gold_bow();
    }

    dagger* create_dagger() const override
    {
        return new gold_dagger();
    }
};
//-----------------------------------------------------------------------------
void test_damage(const weapon_master& master)
{
    const sword* sword = master.create_sword();
    const bow* bow = master.create_bow();
    const dagger* dagger = master.create_dagger();
    
    std::cout << sword->damage() << "\n";
    std::cout << bow->damage() << "\n";
    std::cout << dagger->damage() << "\n";
    
    delete sword;
    delete bow;
    delete dagger;
}
//-----------------------------------------------------------------------------
int main() 
{
    std::cout << "Client: Wooden weapon damage check:\n";
    wooden_master* wooden_m = new wooden_master();
    test_damage(*wooden_m);
    std::cout << std::endl;
    delete wooden_m;

    std::cout << "Client: Iron weapon damage check:\n";
    iron_master* iron_m = new iron_master();
    test_damage(*iron_m);
    std::cout << std::endl;
    delete iron_m;    
    
    std::cout << "Client: Gold weapon damage check:\n";
    gold_master* gold_m = new gold_master();
    test_damage(*gold_m);
    std::cout << std::endl;
    delete gold_m;

    return 0;
}
//-----------------------------------------------------------------------------