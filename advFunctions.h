//
//  Game.hpp
//  OOP
//
//  Created by Joseph on 11/12/16.
//  Copyright © 2016 JosephC. All rights reserved.
//

//                      normal functions


void Player::use(string tryuse)
{
    for(int i=0; i<getConLen(); i++)
    {
        if(getCons()[i] != NULL)
        {
            if(getCons()[i]->getName() == tryuse)//found item, is consumable
            {
                if(getCamt()[i]>0)//have item consumable
                {
                    if(getCons()[i]->isPct() == true)//percent heal
                    {
                        int restore = maxHealth * getCons()[i]->getReg();
                        restore /= 100;
                        int difference = maxHealth - getHealth();
                        if(difference < restore)
                            restore = difference;
                        cout<<"The "<<tryuse<<" restored "<<restore<<" health.\n";
                        changeHealth(restore);
                        return;
                    }
                    else//non percent
                    {
                        int restore = getCons()[i]->getReg();
                        int difference = maxHealth - getHealth();
                        if(difference < restore)
                            restore = difference;
                        cout<<"The "<<tryuse<<" restored "<<restore<<" health.\n";
                        return;
                    }
                }
            }
        }
    }
    cout<<"You can't use that.\n";
}


void Player::showStats()
{
    cout<<"You have "<<getHealth()<<"health.\nCurrent strength is "<<getPow()<<".\n";
}
void Player::showKeys()
{
    
}
void Player::showInv()
{
    for(int i=0; i<getInvLen(); i++)
    {
        
    }
}
void Room::look()
{
    cout<<options;
    if(disMonst!= NULL)
    {
        cout<<disMonst->describe();
        if(disNPC!=NULL)
            cout<<"There is also someone nearby, bent in fear.\n";
    }
    else if(disNPC != NULL)
        disNPC->describe();
}
void Player::search()
{
    if (currentRoom->getMonst() != NULL)
    {
        cout<<"Can't loot with an enemy nearby.\n";
    }
    else
    {
        int k = currentRoom->getSk();
        Item* rItem = currentRoom->getSi();
        if(k<1 && rItem == NULL)//no item or key
        {
            cout<<"You rummage around but find nothing useful.\n";
        }
        else
        {
            if(k > 0)
            {
                if(k == 1) // first key
                {
                    cout<<"You find a bloody key.\n";
                    keys[1] = true;
                }
                if(k == 2)//second key
                {
                    cout<<"You find a small pyramid-shaped artifact. \n";
                    keys[2] = true;
                }
                if(k == 3)//3rd
                {
                    cout<<"You shove your fist in the face of the ogre, and pull the black eye from its socket.\n";
                    keys[3] = true;
                }
                if(k == 4)//4th
                {
                    cout<<"You split the demon's chest in half, removing its beating, black heart from its body.\n";
                    keys[4] = true;
                }
                if(k == 5)//5th
                {
                    cout<<"You found key 5.\n";
                    keys[5] = true;
                }
            }
            if(rItem != NULL)
            {
                cout<<"You found a "<<rItem->getName()<<"!\n";
                for(int i=0; i<getInvLen(); i++)
                {
                    if(getInv()[i] == rItem)
                    {
                        cout<<"it's a regular item.\n";
                        getAmt()[i]++;
                    }
                }
                for(int i=0; i<getConLen(); i++)
                {
                    if(getCons()[i] == rItem)
                    {
                        cout<<"it's a consumable item.\n";
                        getCamt()[i]++;
                    }
                }
                for(int i=0; i<getWepLen(); i++)
                {
                    if(getWeps()[i] == rItem)
                    {
                        cout<<"it's a weapon.\n";
                        getWamt()[i]++;
                    }
                }
            }
            currentRoom->setSecrets(NULL, 0);
        }
    }
}
Monster::Monster(Monster &other)
{
    setHealth(other.getHealth());
    setPow(other.getPow());
    setName(other.getName());
    reaction = other.react();
    description = other.describe();
    dialogue = other.speak();
    hostile = other.isHostile();
    if(other.getInv() != NULL)
    {
        int n = other.getInvLen();
        Item** old = other.getInv();
        Item** oyvey = new Item*[n];
        for(int i=0; i<n; i++)//oyvey array points to the old item pointers
            oyvey[i] = old[i];
        
        int* oi = new int[n];
        int* oldamt = other.getAmt();
        for(int i=0; i<n; i++)
        {
            oi[i] = oldamt[i];
        }
        
        setInv(oyvey, oi, n);
    }
    else
    {
        setInv(NULL, NULL, 0);
    }
    if(other.getCons() != NULL)
    {
        
        int n2 = other.getConLen();
        Consumable** old2 = other.getCons();
        Consumable** oyvey2 = new Consumable*[n2];
        for(int i=0; i<n2; i++)//oyvey array points to the old item pointers
            oyvey2[i] = old2[i];
        
        int* oi2 = new int[n2];
        int* oldCamt2 = other.getCamt();
        for(int i=0; i<n2; i++)
        {
            oi2[i] = oldCamt2[i];
        }
        
        setCon(oyvey2, oi2, n2);
    }
    else
        setCon(NULL, NULL, 0);
    if(other.getWeps() != NULL)
    {
        int n3 = other.getWepLen();
        Weapon** old3 = other.getWeps();
        Weapon** oyvey3 = new Weapon*[n3];
        for(int i=0; i<n3; i++)
            oyvey3[i] = old3[i];
        
        int* oi3 = new int[n3];
        int* oldWamt3 = other.getWamt();
        for(int i=0; i<n3; i++)
        {
            oi3[i] = oldWamt3[i];
        }
        
        setWep(oyvey3, oi3, n3);
    }
    else
        setWep(NULL,NULL,0);
}

void Player::fight( Monster &other )
{
    if(other.isHostile() == true)
    {
        other.attack(*this);
        attack(other);
        
    }
    else
    {
        attack(other);
        other.attack(*this);
    }
    while(getHealth()>0 && other.getHealth()>0)
    {
        string cd;
        cout<<endl<<other.getName()<<" has "<<other.getHealth()<<"health left.\n";
        cout<<"You have "<<getHealth()<<" health left.\n";
        cout<<"do what?\n>";
        cin>>cd;
        if(cd == "attack"||cd == "fight")
        {
            attack(other);
            other.attack(*this);
        }
        else
            return;
    }
    if(getHealth())
    {
        cout<<"victory and stuff!\n";
        other.die();
        getRoom()->killMonst();
    }
    else
    {
        cout<<"You got pooped on.\n";
        die();
    }
}

void Player::fight(NPC &other)
{
    cout<<"You killed "<<other.getName()
    <<". I can't belive you've done this, " << getName()<<".\n";
    currentRoom->killNPC();
    incrementCurrency(1);
}
void Player::attack(Monster &other)
{
    cout<<"You did "<<getPow()<<" damage to "<<other.getName()<<".\n";
    other.changeHealth(-getPow());
}
void Monster::attack(Player &other)
{
    cout<<getName()<<" did "<<getPow()<<" damage to you.\n";
    other.changeHealth(-getPow());
    
}
/*
 {}{}{}}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{
 DESTRUCTORS
 */
Game::~Game()//needs to del items 2
{
    delete [] Map;
    Map = NULL;
    for(int i=0; i<itemLen; i++)
    {
        if(ItemList[i]!=NULL)
            delete ItemList[i];
        ItemList[i] = NULL;
    }
    
    for(int i=0; i<weaponLen; i++)
    {
        if(WeaponList[i]!=NULL)
            delete WeaponList[i];
        WeaponList[i] = NULL;
    }
    
    for(int i=0; i<consumLen; i++)
    {
        if(ConsumList[i]!=NULL)
            delete ConsumList[i];
        ConsumList[i] = NULL;
    }
    //delete [] ItemList;
    //ItemList = NULL;
}
Room::~Room()
{
    //    cout<<"byebye room\n";
    if(disMonst != NULL)//something inside
    {
        delete disMonst;
        disMonst = NULL;
    }
    if(disNPC != NULL)
    {
        delete disNPC;
        disNPC = NULL;
    }
    
}

Being::~Being()
{
    if(inventory != NULL)
    {
        delete [] inventory;
        inventory = NULL;
    }
    if(amt != NULL)
    {
        delete [] amt;
        amt = NULL;
    }
    if(wamt != NULL)
    {
        delete [] wamt;
        wamt = NULL;
    }
    if(camt != NULL)
    {
        delete [] camt;
        camt = NULL;
    }
}
Monster::~Monster()
{
    
}
Player::~Player()
{
    delete [] keys;
    keys = NULL;
}
NPC::~NPC()
{
    
}

/* *********************************************** */
//              dies
void Player::die()
{
    cout<<"You ded.\n";
    alive = false;
}
void Monster::die()
{
    cout<<"Monster ded\n";//this function should give player the monster's inventory
    
}
void NPC::die()
{
    cout<<"NPC ded\n";
    
}
void Room::killNPC()
{
    delete disNPC;
    disNPC = NULL;
}
void Room::killMonst()
{
    delete disMonst;
    disMonst = NULL;
}
//ewrqwerqwerqwerqweriuhqeiourqyuwoeyroiqwueyriouqwyeriouqweouirqyewiur

void Player::enter(Room* next)
{
    //    cout<<"trying to enter from player func!\n";
    //if next not null and can enter
    if(keys[next->getKey()])
    {
        cout<<next->getEnt()<<endl;
        if(next->getMonst()!= NULL)
            cout<<next->getMonst()->describe();
        this->setRoom(next);
        if(next->getKey() > 1)
            keys[next->getKey()] = 0;
        next->setKey(0);
        //check npc, check monster
    }
    else
    {
        cout<<"Key didn't work\n";
        /*  cout<<"Key array is: ";
         for(int i=0; i<5; i++)
         cout<<keys[i]<<endl;
         */
        cout<<next->getDen()<<endl;
    }
}

//void Player::speak(NPC &person)
//{
//	NPC::speak();
//}
//
//int NPC::speak(int& pos)
//{
//	string cmd = "";
//	cout << text[0];
//	cin >> cmd;
//	while(place != pos)
//	{
//		if(cmd == "yes" || cmd == "Yes")
//		{
//			pos++;
//		}
//	}
//
//	return pos;
//}


/*
 class Game
 {
 public:
 void initialize(int rooms);
 void end(bool win); //brings resets everything, brings player to menu
 //    void start();
 private:
 string description;
 Room * Map;//array of rooms
 int mapLen;//length of above array, 1 above last room num
 };
 */
/*
 class Item
 {
 public:
 Item() {edible = 0;}
 ~Item() {}
 //init funcs
 void setEd(bool ed) {edible = ed;}
 void setVal(int a) {value = a;}
 void setDesc(string a) {description = a;}
 
 //ingame funcs
 bool isEd() {return edible;}
 string getDesc(){return description;}
 int getVal(){return value;}
 private:
 bool edible;
 string description;
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
 
 */
void Game::initialize(int n)
{
    //create items here
    itemLen = 10;
    ItemList = new Item*[10];
    for(int i=0; i<itemLen; i++)
    {
        ItemList[i] = NULL;
    }
    weaponLen = 10;
    WeaponList = new Weapon*[10];
    for(int i=0; i<weaponLen; i++)
        WeaponList[i] = NULL;
    
    consumLen = 10;
    ConsumList = new Consumable*[10];
    for(int i=0; i<consumLen; i++)
        ConsumList[i] = NULL;
    //percent consumables
    Consumable* bandage = new Consumable(25,1);//consumable
    ConsumList[0] = bandage;
    bandage->setName("bandage");
    
    Consumable* potion = new Consumable(50,1);
    ConsumList[1] = potion;
    potion->setName("potion");
    
    //regular consumables
    Consumable* pizza = new Consumable(1,0);
    ConsumList[2] = pizza;
    pizza->setName("pizza");
    
    Consumable* chicken = new Consumable(5, 0);
    ConsumList[3] = chicken;
    chicken->setName("chicken");
    
    Consumable* squirrel = new Consumable(2,0);
    ConsumList[4] = squirrel;
    squirrel->setName("squirrel");
    
    //weapons
    Weapon* stick = new Weapon;
    stick->setAbCost(0);
    stick->setDmg(2);
    stick->setName("wooden stick");
    stick->setDesc("A useless wooden stick.");
    ItemList[10] = stick;
    
    
    mapLen = n;
    Map = new Room[n];
    //room 0
    
    Map[0].addNext('n', Map+1);
    Map[0].setEnt("Entered room 0.");
    Map[0].setOpt("Try n to enter room 1.");
    Map[0].setSecrets(pizza, 3);//test1
    
    //room 1
    Map[1].addNext('s', Map);//0
    Map[1].addNext('e', Map+3);//3
    Map[1].addNext('n', Map+2);//2
    Map[1].setSecrets(potion, 0);//test2
    
    Map[1].setEnt("Entered room 1.");
    Map[1].setOpt("Try n to enter room 2, s to enter 0, e to enter 3.");
    
    //room 2
    
    Map[2].addNext('e', Map+4);      //Room 4
    Map[2].addNext('s', Map+1);      //Room 1
    Map[2].addNext('w', Map+5);      //Room 5
    Map[2].setEnt("Entered room 2.");
    Map[2].setOpt("Try s to enter room 1., w for 5, e for 4.");
    
    //Room 3
    Map[3].addNext('n', Map+4);      //Room 4
    Map[3].addNext('w', Map+1);      //Room 1
    Map[3].setEnt("Entered room 3.");
    Map[3].setOpt("Try w to enter room 1.");
    
    
    
    
    
    //Room 4
    Map[4].addNext('n', Map+12);     //Room 12
    Map[4].addNext('s', Map+3);      //Room 3
    Map[4].addNext('w', Map+2);      //Room 2
    Map[4].setEnt("Entered room 4.");
    Monster * room4monster = new Monster;
    room4monster->setName("Billybob");
    room4monster->setDesc("There is a flaming demon in this room, and his name is Billybob.\n");
    Map[4].setMonster(room4monster);
    Map[4].setSecrets(NULL, 1);
    room4monster->setHealth(60);
    room4monster->setPow(20);
    room4monster->setInv(NULL, NULL, 0); //no inventory
    //change things about room4monster;
    
    
    Monster* room5monster = new Monster(*room4monster);
    room5monster->setName("The small goblin");
    room5monster->setDesc("There is a small goblin in this room, looking at you angrily.\n");
    //Room 5
    Map[5].addNext('n', Map+6);      //Room 6
    Map[5].addNext('e', Map+2);      //Room 2
    Map[5].addNext('w', Map+7);      //Room 7
    Map[5].setEnt("Entered room 5.");
    Map[5].setMonster(room5monster);
    
    //Room 6
    Map[6].addNext('s', Map+5);      //Room 5
    Map[6].setEnt("Entered room 6.");
    
    //Room 7
    Map[7].addNext('n', Map+8);      //Room 8
    Map[7].addNext('e', Map+5);      //Room 5
    Map[7].addNext('w', Map+10);     //Room 10
    Map[7].setEnt("Entered room 7.");
    
    //Room 8
    Map[8].addNext('s', Map+7);      //Room 7
    Map[8].addNext('w', Map+9);      //Room 9
    Map[8].setEnt("Entered room 8.");
    
    //Room 9
    Map[9].addNext('e', Map+8);      //Room 8
    Map[9].addNext('s', Map+10);     //Room 10
    Map[9].setEnt("Entered room 9.");
    
    //Room 10
    Map[10].addNext('n', Map+9);     //Room 9
    Map[10].addNext('e', Map+7);     //Room 7
    Map[10].addNext('s', Map+11);    //Room 11
    Map[10].setEnt("Entered room 10.");
    
    //Room 11
    Map[11].addNext('n', Map+10);    //Room 10
    Map[11].setEnt("Entered room 11.");
    
    //Room 12
    Map[12].addNext('n', Map+13);    //Room 13
    Map[12].addNext('s', Map+4);     //Room 4
    Map[12].setEnt("Entered room 12.");
    
    //Room 13
    Map[13].addNext('n', Map+15);    //Room 15
    Map[13].addNext('s', Map+12);    //Room 12
    Map[13].addNext('w', Map+14);    //Room 14
    Map[13].setEnt("Entered room 13.");
    
    //Room 14
    Map[14].addNext('n', Map+16);    //Room 16
    Map[14].addNext('e', Map+13);    //Room 13
    Map[14].addNext('w', Map+17);    //Room 17
    Map[14].setEnt("Entered room 14.");
    
    //Room 15
    Map[15].addNext('s', Map+13);    //Room 13
    Map[15].addNext('w', Map+16);    //Room 16
    Map[15].setEnt("Entered room 15.");
    
    //Room 16
    Map[16].addNext('e', Map+15);    //Room 15
    Map[16].addNext('s', Map+14);    //Room 14
    Map[16].addNext('w', Map+18);    //Room 18
    Map[16].setEnt("Entered room 16.");
    
    //Room 17
    Map[17].addNext('n', Map+18);    //Room 18
    Map[17].addNext('e', Map+14);    //Room 14
    Map[17].addNext('w', Map+19);    //Room 19
    Map[17].setEnt("Entered room 17.");
    
    //Room 18
    Map[18].addNext('e', Map+16);    //Room 16
    Map[18].addNext('s', Map+17);    //Room 17
    Map[18].addNext('w', Map+21);    //Room 21
    Map[18].setEnt("Entered room 18.");
    
    //Room 19
    Map[19].addNext('n', Map+21);    //Room 21
    Map[19].addNext('e', Map+17);    //Room 17
    Map[19].addNext('w', Map+20);    //Room 20
    Map[19].setEnt("Entered room 19.");
    
    //Room 20
    Map[20].addNext('e', Map+19);    //Room 19
    Map[20].setEnt("Entered room 20.");
    
    //Room 21
    Map[21].addNext('e', Map+18);    //Room 18
    Map[21].addNext('s', Map+19);    //Room 19
    Map[21].addNext('w', Map+22);    //Room 22
    Map[21].setEnt("Entered room 21.");
    
    //Room 22
    Map[22].addNext('e', Map+21);    //Room 21
    Map[22].setEnt("Entered room 22.");
    
    
}

