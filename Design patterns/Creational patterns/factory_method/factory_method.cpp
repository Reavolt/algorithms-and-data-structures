#include <iostream>

//-----------------------------------------------------------------------------
class sword 
{
public:
    virtual ~sword() {}
    virtual std::string material() const = 0;
};
//-----------------------------------------------------------------------------
class wood_sword : public sword 
{
public:
    std::string material() const override
    {
        return "{Wooden Sword}";
    }
};
//-----------------------------------------------------------------------------
class iron_sword : public sword
{
public:
    std::string material() const override
    {
        return "{Iron sword}";
    }
};
//-----------------------------------------------------------------------------
class gold_sword : public sword
{
public:
    std::string material() const override
    {
        return "{Golden Sword}";
    }
};
//-----------------------------------------------------------------------------
class master
{
public:
    virtual ~master() {};
    virtual sword* forge_a_sword() const = 0;

    std::string forging() const
    {
        sword* sword = this->forge_a_sword();
        std::string result = "Master: I forged for you " + sword->material();
        delete sword;

        return result;
    }
};
//-----------------------------------------------------------------------------
class wood_master : public master
{
public:
    sword* forge_a_sword() const override
    {
        return new wood_sword();
    }
};
//-----------------------------------------------------------------------------
class iron_master : public master
{
public:
    sword* forge_a_sword() const override
    {
        return new iron_sword();
    }
};
//-----------------------------------------------------------------------------
class gold_master : public master
{
public:
    sword* forge_a_sword() const override
    {
        return new gold_sword();
    }
};
//-----------------------------------------------------------------------------
void workshop(const master& master)
{
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n";
    std::cout << master.forging() << std::endl;
}
//-----------------------------------------------------------------------------
int main() 
{
    std::cout << "App: Launched with the wood_master.\n";
    master* w_master = new wood_master();
    workshop(*w_master);
    std::cout << std::endl;
    delete w_master;

    std::cout << "App: Launched with the iron_master.\n";
    master* i_master = new iron_master();
    workshop(*i_master);
    std::cout << std::endl;
    delete i_master;

    std::cout << "App: Launched with the gold_master.\n";
    master* g_master = new gold_master();
    workshop(*g_master);
    std::cout << std::endl;
    delete g_master;

    return 0;
}
//-----------------------------------------------------------------------------