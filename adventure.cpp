//
//  codesharedgame.cpp
//  OOP
//
//  Created by Joseph and Jared on 11/12/16.
//  Copyright © 2016 JosephC. All rights reserved.
//

/*
Item List
Potion + 20 health
Bandage +10 health
Chicken Breast +5 health
Squirrel Bits +2 health
Stick +3 dmg
Butter Knife + 6 dmg
Iron Sword + 10 dmg
Steel Sword +15 dmg
Dual Blades +25 dmg
Piecework Armor 5% damage modifier
Iron Armor 10% damage modifier
Steel Armor 25% damage modifier
Eye Shaped Key

Heart Shaped Key
Wing Shaped Key
Nursery Key
Portal Key (pyramid)
*/

/*
 global:
 Item** gameItems = new Item*[16];
 item
 
 lit candle,
 ACU Bean pizza (+1 health)
 chicken breast,
 squirrel bits
 piece work armor (+5 armor rating)
 wooden stick (+2 abilityPower)
 iron sword (+6 abilityPower),
 steel sword (+15 abilityPower)
 
 */
/*
 "global"(owned by game):
 Item** gameItems = new Item*[16];
 item
 
 lit candle,
 ACU Bean pizza (+1 health)
 chicken breast,
 squirrel bits
 piece work armor (+5 armor rating)
 wooden stick (+2 abilityPower)
 iron sword (+6 abilityPower),
 steel sword (+10 abilityPower)
 
 */

/*
 global:
 Item** gameItems = new Item*[16];
 item
 
 lit candle,
 ACU Bean pizza (+1 health)
 chicken breast,
 squirrel bits
 piece work armor (+5 armor rating)
 wooden stick (+2 abilityPower)
 iron sword (+6 abilityPower),
 steel sword (+10 abilityPower)
 
 */

#include <iostream>
using namespace std;
#include "advClasses.h"
#include "advFunctions.h"
#include <sstream>
int main()
{
    bool quitted = false;
    cout<<"Welcome to Merry Christmas the Game: A Wonderful Christmas Tale!\n";
    cout<<"It's a gorgeous Monday. Christmas is almost here, and it's been a long while since you've had time to be with your family. As you pull into the driveway of your house, your beautiful wife and four year old daughter open the door and come outside to greet you. Your daughter runs toward the car. You smile, but as you are getting out of your car to catch your daughter in your arms, the air vibrates with a low rumble. A small portal appears in front of her on the floor. A red hand reaches forward, grabs her foot, and drags her screaming into the void. You get out of the car and run to where she stood. Not a second later you are hit in the head and lose consciousness.\n";
    while(!quitted)
    {
        Game * dis = new Game;
        dis->initialize(23);
        Player player1(dis);
        string command ="";
    
        cout<<"WAKE UP?(y/n)\n<";
        cin>>command;
        if(command == "y")
        {
            cout<<"You open your eyes and realize something has dragged you into a pit. There are several open wounds on your body, and you are losing blood quickly.\n\nThere is a gigantic, hideous monster gorging on the flesh of your dying wife. You assess that the likelihood of saving her is low. She looks up to where you are lying and as a tear streams down her face she mouths the word \"run\".\nrun or fight?\n<";
            cin>>command;
            if(command == "run")
                cout<<"\nA giant foot replaces the area where your wife's face was. In complete shock you quickly crawl away and barricade yourself into the next room, the monster chases behind you.\nBecause of your yoga classes, you are able to quickly lock the steel door with your feet. The monster slams itself repeatedly against the door, and the roof in the previous room collapses.\n";
            else
            {
                cout<<"The monster turns to you and instantly jumps on you, shredding you into pieces.\n";
                player1.die();
            }
        }
        else
        {
            cout<<"Something devoured you while you were sleeping.\n\nYou snooze, you lose.\n";
            player1.die();
        }
        
        while(true)
        {
            if(!player1.isAlive())
            {
                cout<<"Play again?(y/n)\n";
                cin>>command;
                if(command =="y")//continue
                {
                    /* delete dis;
                     dis->initialize(23);
                     player1 = dis;
                     */
                    break;
                }
                else
                {
                    quitted = true;
                    break;
                }
            }
            cout<<"> ";
            cin>>command;
            if( command == "Quit" || command == "quit")
            {
                quitted = true;
                break; // quit loop/program
            }
            else if(command == "use" )
            {
                cin >> command;
                player1.use(command);
            }
            else if(command == "stats")
            {
                player1.showStats();
            }
            else if( command == "fight" || command == "attack")
            {
                if(player1.getRoom()->getMonst() == NULL)
                    cout<<"nothing to fight here.\n";
                else
                    player1.fight(*player1.getRoom()->getMonst());
                //            cin >> key;
                //            cin >> value;
                //            assign(map,key,value);
            }
            else if( command == "n" || command == "north" )//north
            {
                Room* current = player1.getRoom();
                if(current->getN() == NULL)
                    cout<<"Can't move, there's a wall there.\n";
                else
                    player1.enter(current->getN());
            }
            
            else if( command == "s" || command == "south" )//south
            {
                Room* current = player1.getRoom();
                if(current->getS() == NULL)
                    cout<<"Can't move, there's a wall there.\n";
                else
                    player1.enter(current->getS());
            }
            
            else if( command == "e" || command == "east" )//east
            {
                Room* current = player1.getRoom();
                if(current->getE() == NULL)
                    cout<<"Can't move, there's a wall there.\n";
                else
                    player1.enter(current->getE());
            }
            
            else if( command == "w" || command == "west" )//west
            {
                Room* current = player1.getRoom();
                if(current->getW() == NULL)
                    cout<<"Can't move, there's a wall there.\n";
                else
                    player1.enter(current->getW());
            }
            else if( command == "look" )
            {
                player1.getRoom()->look();
            }
            else if( command == "search")
            {
                player1.search();
            }
            else if( command == "help")
            {
                cout<<"This is the list of available commands.\n\n";
                cout<<"look: Describes the current room and available directions.\n\n"
                <<"north or n: Attempt to enter the room to the north.\nSame for south, east, and west.\n\n"
                <<"fight: Enter combat with a monster or NPC in the room.\n\n"
                <<"search: Search the current room for hidden items.\n\n"
                <<"use (itemname): Uses or equips the item.(currently broken)\n\n"
                <<"stats: prints stats about character.\n\n"
                <<"bag: prints items in the inventory.\n\n"
                <<"quit: ends the game.\n";
            }
            else
                cout<<"Invalid command. Type \"help\" to see the basic options.\n";
        }
        delete dis;
    }
    //    destroy(map);
    
}
