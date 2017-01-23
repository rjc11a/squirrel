//
//  Game.hpp
//  OOP
//
//  Created by Joseph on 11/12/16.
//  Copyright © 2016 JosephC. All rights reserved.
//


class Room;
class Being;
class Monster;
class Player;
class NPC;
class Item;
class Consumable;
class Weapon;
class Game
{
public:
    Game() {Map = NULL;}
    Room* Start() {return Map;}
    void initialize(int rooms);
    void end(bool win); //brings resets everything, brings player to menu
    //    void start();
    int getItemLen() {return itemLen;}
    Item** getInv() {return ItemList;}
    Weapon** getWeps() { return WeaponList;}
    Consumable** getCons() {return ConsumList;}
    int getWepLen() {return weaponLen;}
    int getConLen(){ return consumLen;}
    ~Game();
private:
    string description;
    Room * Map;//array of rooms
    Item** ItemList;
    Weapon** WeaponList;
    Consumable** ConsumList;
    int weaponLen;
    int consumLen;
    int itemLen;
    int mapLen;//length of above array, 1 above last room num
};
//==================================================================
//                             Room
//==================================================================
class Room
{
public:
    Room()
    {
        keyReq = 0;
        //      cout<<"room being made\n";
        secretKey = 0;
        secretItem = NULL;
        disMonst = NULL;
        disNPC = NULL;
        n = s = e = w = NULL;
        denied = "couldn't enter room for some reason. Contact Joseph.\n";
    }
    
    ~Room();
    //initialize functions
    void setEnt(string ent){entered = ent;}
    void setDen(string den){denied = den;}
    void setOpt(string opt){options = opt;}
    void setKey(int key){keyReq = key;}
    void setMonster(Monster* scary) {disMonst = scary;}
    void setSecrets(Item* a, int sk){ secretItem = a; secretKey = sk;}
    
    string getEnt() { return entered;}
    string getDen() { return denied;}
    string getOpt() { return options;}
    Monster* getMonst() {return disMonst;}
    NPC* getNPC() {return disNPC;}
    //    string getEnt() { return ;}
    int getKey(){ return keyReq;}
    Item* getSi() {return secretItem;}
    int getSk() {return secretKey;}
    
    void addNext(char ptr, Room* next)
    {
        if(ptr == 'n')
        {
            //          cout<<"added a north room\n";
            n = next;
        }
        else if(ptr == 's')
            s = next;
        else if(ptr == 'e')
            e = next;
        else if(ptr == 'w')
            w = next;
        else
            cout<<"failed to add "<<ptr<<endl;
    }
    void killNPC();
    void killMonst();
    Room* getN() {return n;}
    Room* getS() {return s;}
    Room* getE() {return e;}
    Room* getW() {return w;}
    
    //ingame functions
    void look();
    //    void search();// give player item if exists
private:
    int keyReq;
    Item * secretItem;
    int secretKey;
    string entered, denied, options;
    Room* n, *s, *e, *w;
    Monster* disMonst;
    NPC* disNPC;
};
//====================================================================
//                                 Being
//====================================================================
class Being
{
public:
    
    virtual ~Being();
    virtual void die() = 0;
    //virtual void attack(Being &other);
    
    int getHealth(){return health;}
    string getName(){return name;}
    double getPow(){return powerLevel;}
    Item** getInv(){return inventory;}
    Weapon** getWeps(){return weapons;}
    Consumable** getCons(){return consums;}
    int* getAmt(){return amt;}
    int* getWamt(){return wamt;}
    int* getCamt() {return camt;}
    int getInvLen(){return inventoryLen;}
    int getWepLen(){return wlen;}
    int getConLen(){return clen;}
    
    void setHealth(int init){health = init;}
    void setName(string new1){name = new1;}
    void setPow(int pow) {powerLevel = pow;}
    void setInv(Item** inv, int* parallel, int len) {inventory = inv; amt = parallel; inventoryLen = len;}
    
    void changeHealth(int change) { health += change; }
    //    void giveItem(Item* toGive);
    
    void setWep(Weapon** weps, int* pw, int wl) {weapons = weps; wamt = pw; wlen = wl;}
    
    void setCon(Consumable** cons, int* pc, int cl){consums = cons; camt = pc; clen = cl;}
    
private:
    int health, powerLevel;
    string name;
    int inventoryLen; //
    Item** inventory;
    int* amt; //parallel with inventory, zeroed initially
    Weapon** weapons;
    int* wamt;
    int wlen;
    Consumable** consums;
    int* camt;
    int clen;
    
};
class Monster : public Being
{
public:
    Monster() {hostile = false;setInv(NULL, NULL, 0);setWep(NULL,NULL,0);setCon(NULL, NULL, 0);}
    Monster(int idc) {hostile = true;setInv(NULL, NULL, 0);setWep(NULL,NULL,0);setCon(NULL, NULL, 0);}
    Monster(Monster &other);
    ~Monster();
    bool isHostile() const {return hostile;}
    string describe() const {return description;}
    string react() const {return reaction;}
    
    void setReact(string re) {reaction = re;}
    void setDesc(string de) {description = de;}
    void setDial(string dia) {dialogue = dia;}
    
    void die();
    void attack(Player &other);
    string speak() const {return dialogue;}
private:
    string reaction, description, dialogue;
    bool hostile;
};

//  **** Player ****

class Player : public Being
{
public:
    Player(Game* dis)
    {
        alive = true;
        setHealth(100);
        setPow(29);
        abilityPower = 1;
        
        currentRoom = dis->Start();
        keys = new bool[6];
        keys[0] = true;
        for(int i=1; i<5; i++)
            keys[i] = false;
        armorName = "nothing";
        wep = NULL;
        currency = 0;
        maxHealth = 100;
        
        Item** pitemlist = new Item*[dis->getItemLen()];
        for(int i=0; i<dis->getItemLen(); i++)
            pitemlist[i] = dis->getInv()[i];
        int* nums = new int[dis->getItemLen()];
        for(int i=0; i<dis->getItemLen(); i++)
            nums[i] = 0;
        setInv(pitemlist, nums, dis->getItemLen());
        
        
        Weapon** pweplist = new Weapon*[dis->getWepLen()];
        for(int i=0; i<dis->getWepLen(); i++)
            pweplist[i] = dis->getWeps()[i];
        int* wnums = new int[dis->getWepLen()];
        for(int i=0; i<dis->getWepLen(); i++)
            wnums[i] = 0;
        setWep(pweplist, wnums, dis->getWepLen());
        
        
        Consumable** pconlist = new Consumable*[dis->getConLen()];
        for(int i=0; i<dis->getWepLen(); i++)
            pconlist[i] = dis->getCons()[i];
        int* cnums = new int[dis->getConLen()];
        for(int i=0; i<dis->getConLen(); i++)
            cnums[i] = 0;
        setCon(pconlist, cnums, dis->getConLen());
        //wep = dis->;
    }
    Player& operator=(Game* dis)
    {
        alive = true;
        setHealth(100);
        setPow(29);
        abilityPower = 1;
        
        currentRoom = dis->Start();
        keys[0] = true;
        for(int i=1; i<6; i++)
            keys[i] = false;
        armorName = "nothing";
        wep = NULL;
        currency = 0;
        maxHealth = 100;
        return *this;
    }
    
    ~Player();
    void showStats();
    void showKeys();
    void showInv();
    
    bool isAlive() {return alive;}
    void use(string iName);
    void attack(Monster &other); //
    void fight(Monster &other);
    void fight(NPC& other);
    void enter(Room* next); //changes the room that a character is in
    void eat(string tryEat); //increases players health
    string speak(NPC &person); //returns a box of text for information
    void die(); //calls game's end function
    void sell(Item& object); //returns gold for selling items
    void incrementCurrency(int c){currency += c;}
    void search();//check room
    Room* getRoom() {return currentRoom;}
    
    void setRoom(Room* other){currentRoom = other;}
private:
    int abilityPower;
    bool* keys, alive;
    int currency;
    int armorRating;
    string armorName;
    Room* currentRoom;
    Weapon* wep;
    int maxHealth;
};




//  **** NPC ****

class NPC : public Being
{
public:
    Item give(Item &object);
    NPC() {setInv(NULL, NULL, 0);setWep(NULL,NULL,0);setCon(NULL, NULL, 0);}
    ~NPC();
    void describe(){cout<< description;}
    void die();
private:
    string dialogue, description;
};
//==============================================================================
//                                   Item
//==============================================================================
class Item
{
public:
    Item() {edible = 0;}
    ~Item() {}
    //init funcs
    void setEd(bool ed) {edible = ed;}
    void setVal(int a) {value = a;}
    void setDesc(string a) {description = a;}
    void setName(string a){name = a;}
    
    string getName(){return name;}
    //ingame funcs
    bool isEd() {return edible;}
    string getDesc(){return description;}
    int getVal(){return value;}
private:
    bool edible;
    string description;
    string name;
    // 	Being* owner;
    int value;
};


class Weapon : public Item
{
public:
    void setAbCost(int a){special = a;}
    void setDmg(int a){dmg = a;}
    void setSpec(string a){specialAbility = a;}
    
    void useSpecial();
    int getAbCost(){return special;}
    int getDmg(){return dmg;}
private:
    int special;
    int dmg;
    string specialAbility;
};

/*
 class Armor : public Item
 {
 public:
 
 private:
 double defenceStat;
 };
 */

class Consumable : public Item
{
public:
    Consumable(int hreg, bool pct) {healthRegen = hreg; percentage = pct; setEd(1);}
    void setRegen();
    
    bool isPct() {return percentage;}
    int getReg(){return healthRegen;}
private:
    int healthRegen;
    bool percentage;
};

