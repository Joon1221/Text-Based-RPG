#ifndef MAIN_H
#define MAIN_H

// flags
//#define ANSI_COLOR_OUTPUT
//#define DAY_AND_NIGHT_ON
//#define DEBUG_DRAGON_MOVE
//#define BOSS_RUSH_EVENT_ON

//==============================================================================
// #define => Constants
//==============================================================================
//------------------------------------------------------------------------------
// General
//------------------------------------------------------------------------------
// time
#define DELAY 95000
#define FPS 10

#define DAY true
#define NIGHT false

// boss iq flag: 아래중에 하나만 켠다.
//#define BOSS_IQ_80
#define BOSS_IQ_120

#define MOVE_INTERVAL_MON (FPS-0)
#define MOVE_INTERVAL_BOSS (FPS-6)
//#define MOVE_INTERVAL_BOSS (FPS-9)
#define MOVE_INTERVAL_CAR (FPS-8)
#define MOVE_INTERVAL_DRAGON (FPS-8)
#define MOVE_INTERVAL_THROWING_ITEM (FPS-9)
#define HP_AND_MP_RECOVERY (FPS-0)

// The size of the board
#define MAX_ROW_SIZE 50 // constant MAX_ROW_SIZE
#define MAX_COL_SIZE 50
#define MAX_NUM_PIECES MAX_ROW_SIZE*MAX_COL_SIZE

//#define MAX_NUM_MONS 0 // (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.025)
#define MAX_NUM_MONS (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.025)
#define MAX_NUM_BOSS_MONS (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.0015)
//#define MAX_NUM_BOSS_MONS (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.01)
#define MAX_NUM_CARS 100
#define MAX_NUM_MERCHANTS (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.005)
#define MAX_NUM_DRAGONS 1

#define MAX_NUM_TREES (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.05)
#define MAX_NUM_CHESTS (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.015)
#define MAX_NUM_POTIONS (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.015)
#define MAX_NUM_KEYS (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.015)
#define MAX_NUM_BOMBS (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.5)

//#define MAX_NUM_ARMORS (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.01)
//#define MAX_NUM_WEAPONS (int)(MAX_ROW_SIZE*MAX_COL_SIZE*0.01)
#define MAX_NUM_ARMORS 20
#define MAX_NUM_WEAPONS 20

// Distance Between Stats related
#define BAR 64
#define HALF_BAR BAR/2

#define BETWEEN_STAT_WINDOWS 12

//// Direction related
//#define NUM_DIRECTIONS 8
//
//#define DIR_NORTH 0
//#define DIR_NORTHEAST 1
//#define DIR_EAST 2
//#define DIR_SOUTHEAST 3
//#define DIR_SOUTH 4
//#define DIR_SOUTHWEST 5
//#define DIR_WEST 6
//#define DIR_NORTHWEST 7

// User input
#define YES_LOWERCASE 'y'
#define YES_UPPERCASE 'Y'
#define NO_LOWERCASE 'n'
#define NO_UPPERCASE 'N'
#define SINGLEPLAYER_LOWERCASE 's'
#define SINGLEPLAYER_UPPERCASE 'S'

#define MULTIPLAYER_LOWERCASE 's'
#define MULTIPLAYER_UPPERCASE 'S'

// help command
#define COMMAND_HELP 'h'

// screen UI related. used by Unit::printStatDual()
#define GAP_BETWEEN_PLAYERS_STAT "          "

// for save()/load()
#define MAX_LEN_BUF 1000

#define USER_CMD_LOAD_LEVEL ';'

#define MODE_CAMPAIGN 0
#define MODE_SINGLE_RANDOM 1
#define MODE_SINGLE_LEVEL 2

#define MAX_LEN_FILENAME 80

//------------------------------------------------------------------------------
// hero movement related
//------------------------------------------------------------------------------
#define NUM_HERO_MOVE_DIR 4

#define MOVE_DIR_NONE -1
#define MOVE_DIR_NORTH 0
#define MOVE_DIR_EAST 1
#define MOVE_DIR_SOUTH 2
#define MOVE_DIR_WEST 3

#define HERO_MOVE_DIR_NORTH_CHAR 'w'
#define HERO_MOVE_DIR_EAST_CHAR 'd'
#define HERO_MOVE_DIR_SOUTH_CHAR 's'
#define HERO_MOVE_DIR_WEST_CHAR 'a'

// level related
#define NEXT_LEVEL_MAX_EXP_INCREMENTAL 1000
#define NEXT_LEVEL_DEF_INCREMENTAL 1
#define NEXT_LEVEL_ATK_INCREMENTAL 1
#define NEXT_LEVEL_MAX_HP_INCREMENTAL 25
#define NEXT_LEVEL_MAX_HP_BASE 250
#define NEXT_LEVEL_MAX_MP_INCREMENTAL 25
#define NEXT_LEVEL_MAX_MP_BASE 250

// shockwave related
#define HERO_POSTIONING_WAVE_RANGE 10
#define HERO_POSTIONING_WAVE_FRAME_INTERVAL 1
#define HERO_POSTIONING_WAVE_SHAPE '*'

//------------------------------------------------------------------------------
// class Tile related
//------------------------------------------------------------------------------
// Tile related
#define TILE_EMPTY '.'

// print when the tile to print is out of bound of board
#define TILE_WALL '#'
#define TILE_NIGHT 'Z'

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Unit
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define DEFAULT_UNIT_SHAPE 'U'
#define DEFAULT_UNIT_HP 100
#define DEFAULT_UNIT_HP_MAX DEFAULT_UNIT_HP
#define DEFAULT_UNIT_MELEE_ATK 1
#define DEFAULT_UNIT_RANGE_ATK 0
#define DEFAULT_UNIT_FREEZE false
#define DEFAULT_UNIT_GOLD 0
#define DEFAULT_UNIT_EXP 0
#define DEFAULT_MAX_EXP_TO_LEVEL_UP 1000
#define DEFAULT_LEVEL 1

//------------------------------------------------------------------------------
// class Hero related
//------------------------------------------------------------------------------
#define DEFAULT_HERO_HP_BASE 0

#define UNIT_ID_HERO "Hero"

#define DEFAULT_HERO_SHAPE 'H'
#define DEFAULT_HERO_HP 300 //(300+DEFAULT_HERO_HP_BASE)
//#define DEFAULT_HERO_HP 100000 //(300+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_HP_MAX (300+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_MP 300
#define DEFAULT_HERO_MP_MAX 300
#define DEFAULT_HERO_MELEE_ATK 10
#define DEFAULT_HERO_RANGE_ATK 0
#define DEFAULT_HERO_DEF 0
#define DEFAULT_HERO_FREEZE false
#define DEFAULT_HERO_GOLD 1000
#define DEFAULT_HERO_EXP 0
#define DEFAULT_MAX_EXP_TO_LEVEL_UP 1000
#define DEFAULT_LEVEL 1
#define DEFAULT_HERO_VIEWPORT_RANGE_ROW 12
#define DEFAULT_HERO_VIEWPORT_RANGE_COL 31
#define DEFAULT_HERO_NIGHT_RANGE 3

//------------------------------------------------------------------------------
// Hero jobs related
//------------------------------------------------------------------------------
#define HERO_JOB_KNIGHT 0
#define HERO_JOB_PALADIN 1
#define HERO_JOB_WARRIOR 2
#define HERO_JOB_HUNTER 3
#define HERO_JOB_ARCHER 4

#define DEFAULT_HERO_JOB HERO_JOB_HUNTER

#define DEFAULT_HERO_KNIGHT_HP (200+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_KNIGHT_HP_MAX (200+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_KNIGHT_MP 300
#define DEFAULT_HERO_KNIGHT_MP_MAX 300
#define DEFAULT_HERO_KNIGHT_MELEE_ATK 20
#define DEFAULT_HERO_KNIGHT_RANGE_ATK 0
#define DEFAULT_HERO_KNIGHT_DEF 10

#define DEFAULT_HERO_PALADIN_HP (400+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_PALADIN_HP_MAX (400+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_PALADIN_MP 150
#define DEFAULT_HERO_PALADIN_MP_MAX 150
#define DEFAULT_HERO_PALADIN_MELEE_ATK 10
#define DEFAULT_HERO_PALADIN_RANGE_ATK 0
#define DEFAULT_HERO_PALADIN_DEF 40

#define DEFAULT_HERO_WARRIOR_HP (200+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_WARRIOR_HP_MAX (200+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_WARRIOR_MP 250
#define DEFAULT_HERO_WARRIOR_MP_MAX 250
#define DEFAULT_HERO_WARRIOR_MELEE_ATK 20
#define DEFAULT_HERO_WARRIOR_RANGE_ATK 0
#define DEFAULT_HERO_WARRIOR_DEF 10

#define DEFAULT_HERO_HUNTER_HP (250+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_HUNTER_HP_MAX (250+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_HUNTER_MP 250
#define DEFAULT_HERO_HUNTER_MP_MAX 250
#define DEFAULT_HERO_HUNTER_MELEE_ATK 0
#define DEFAULT_HERO_HUNTER_RANGE_ATK 15
#define DEFAULT_HERO_HUNTER_DEF 20

#define DEFAULT_HERO_ARCHER_HP (200+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_ARCHER_HP_MAX (200+DEFAULT_HERO_HP_BASE)
#define DEFAULT_HERO_ARCHER_MP 400
#define DEFAULT_HERO_ARCHER_MP_MAX 400
#define DEFAULT_HERO_ARCHER_MELEE_ATK 0
#define DEFAULT_HERO_ARCHER_RANGE_ATK 15
#define DEFAULT_HERO_ARCHER_DEF 10

//------------------------------------------------------------------------------
// class Monster related
//------------------------------------------------------------------------------
#define UNIT_ID_MON "Mon"

#define DEFAULT_MON_SHAPE 'm'
#define DEFAULT_MON_HP 50
#define DEFAULT_MON_HP_MAX DEFAULT_MON_HP
#define DEFAULT_MON_MELEE_ATK 30
#define DEFAULT_MON_RANGE_ATK 0
#define DEFAULT_MON_DEF 10
#define DEFAULT_MON_FREEZE false
#define DEFAULT_MON_GOLD 100
#define DEFAULT_MON_EXP 100
#define DEFAULT_LEVEL 1
#define DEFAULT_MON_RANGE 2

//------------------------------------------------------------------------------
// class Boss related
//------------------------------------------------------------------------------
#define UNIT_ID_BOSS "Boss"

#define DEFAULT_BOSS_SHAPE '&'
#define DEFAULT_BOSS_HP 2000
#define DEFAULT_BOSS_HP_MAX DEFAULT_BOSS_HP
#define DEFAULT_BOSS_MELEE_ATK 0
#define DEFAULT_BOSS_RANGE_ATK 0
#define DEFAULT_BOSS_FREEZE false
#define DEFAULT_BOSS_GOLD 1000
#define DEFAULT_BOSS_EXP 1000
#define DEFAULT_LEVEL 1
#define DEFAULT_BOSS_RANGE 5

#define DEFAULT_LEVEL 1

//------------------------------------------------------------------------------
// class Merchant related
//------------------------------------------------------------------------------
#define UNIT_ID_MERCHANT "Merchant"

#define DEFAULT_MERCHANT_SHAPE 'G'
#define DEFAULT_MERCHANT_ITEMS_TO_SELL_CAPACITY 20
#define DEFAULT_MERCHANT_ITEMS_BOUGHT_CAPACITY 100

#define DEFAULT_MERCHANT_NUM_ITEMS_TO_SELL 10

//------------------------------------------------------------------------------
// class Car related
//------------------------------------------------------------------------------
#define UNIT_ID_CAR "Car"

#define DEFAULT_CAR_SHAPE '='

//------------------------------------------------------------------------------
// class Dragon related
//------------------------------------------------------------------------------
#define UNIT_ID_DRAGON "Dragon"

#define DRAGON_START_ROW HERO_START_ROW
#define DRAGON_START_COL HERO_START_COL+1

#define DRAGON_LEN 10

#define UNIT_ID_DRAGON "Dragon"
#define DEFAULT_DRAGON_SHAPE_HEAD 'V'
#define DEFAULT_DRAGON_SHAPE_BODY 'r'
#define DEFAULT_DRAGON_SHAPE DEFAULT_DRAGON_SHAPE_HEAD

#define DEFAULT_DRAGON_HP 30
#define DEFAULT_DRAGON_MAX_HP 30
#define DEFAULT_DRAGON_MELEE_ATK 30
#define DEFAULT_DRAGON_RANGE_ATK 30
#define DEFAULT_DRAGON_GOLD 1000
#define DEFAULT_DRAGON_EXP 1000

#define DEFAULT_DRAGON_DEF 5

#define DEFAULT_DRAGON_LEVEL 1
#define DEFAULT_DRAGON_FREEZE false

#define MIN_NUM_EMPTY_CELLS_TO_MOVE (DRAGON_LEN-5)/2

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Prop related
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define DEFAULT_PROP_SHAPE 'P'
#define DEFAULT_PROP_CLIMBABLE false

//------------------------------------------------------------------------------
// Tree related
//------------------------------------------------------------------------------
#define PROP_ID_TREE "Tree"

#define DEFAULT_PROP_TREE_SHAPE 'Y'
#define DEFAULT_PROP_TREE_CLIMBABLE false

//------------------------------------------------------------------------------
// Chest related
//------------------------------------------------------------------------------
#define PROP_ID_CHEST "Chest"

#define CHEST_RUSTY 0     //lvl 1+
#define CHEST_BRONZE 1    //lvl 30+
#define CHEST_SILVER 2    //lvl 60+
#define CHEST_GOLD 3      //lvl 100+

#define MAX_ITEMS_CHEST (CHEST_GOLD+1)

#define DEFAULT_CHEST_SHAPE 'D'
#define DEFAULT_CHEST_CLIMBABLE false

#define DEFAULT_CHEST_LOCKED false
#define DEFAULT_CHEST_LOCK_LEVEL CHEST_RUSTY

//------------------------------------------------------------------------------
// Wall related
//------------------------------------------------------------------------------
#define PROP_ID_WALL "Wall"

#define DEFAULT_PROP_WALL_SHAPE_01 '+'
#define DEFAULT_PROP_WALL_SHAPE_02 '|'
#define DEFAULT_PROP_WALL_SHAPE_03 '-'
#define DEFAULT_PROP_WALL_CLIMBABLE false

//------------------------------------------------------------------------------
// Exit related
//------------------------------------------------------------------------------
#define PROP_ID_EXIT "Exit"

#define DEFAULT_PROP_EXIT_SHAPE 'X'
#define DEFAULT_PROP_EXIT_CLIMBABLE true

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Item
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define NUM_ITEM_TYPES 8

#define ITEM_TYPE_POTION 0 
#define ITEM_TYPE_WEAPON 1 
#define ITEM_TYPE_ARMOR 2 
//#define ITEM_TYPE_ARROW 3 <----- DO NOT INCLUDE
#define ITEM_TYPE_KEY 3
#define ITEM_TYPE_BOMB 4
#define ITEM_TYPE_MAGICSCROLL 5
#define ITEM_TYPE_TORCH 6
#define ITEM_TYPE_TIMEBOMB 7

#define DEFAULT_ITEM_SHAPE 'I'
#define DEFAULT_ITEM_NAME "Item"
#define DEFAULT_ITEM_PRICE 0
#define DEFAULT_ITEM_LEVEL 1

//------------------------------------------------------------------------------
// class Potion related
//------------------------------------------------------------------------------
#define ITEM_ID_POTION "Potion"

#define DEFAULT_POTION_SHAPE 'b'
#define DEFAULT_POTION_NAME "Potion"
#define DEFAULT_POTION_PRICE 10
#define DEFAULT_POTION_LEVEL 1
#define DEFAULT_POTION_HP_TO_INC 50
#define DEFAULT_POTION_MP_TO_INC 50

#define POTION_HP 0
#define POTION_MP 1
#define POTION_SPECIAL 2

//------------------------------------------------------------------------------
// class Key related
//------------------------------------------------------------------------------
#define ITEM_ID_KEY "Key"

#define KEY_RUSTY 0    //lvl 1+
#define KEY_BRONZE 1   //lvl 30+
#define KEY_SILVER 2   //lvl 60+
#define KEY_GOLD 3     //lvl 90+

#define NUM_KEY_TYPES (KEY_GOLD+1)

#define KEY_RUSTY_NAME "Rusty Key"
#define KEY_BRONZE_NAME "Bronze Key"
#define KEY_SILVER_NAME "Silver Key"
#define KEY_GOLD_NAME "Gold Key"

#define KEY_RUSTY_PRICE 1
#define KEY_BRONZE_PRICE 100
#define KEY_SILVER_PRICE 1000
#define KEY_GOLD_PRICE 5000

#define DEFAULT_KEY_SHAPE '`'
#define DEFAULT_KEY_NAME KEY_RUSTY_NAME
#define DEFAULT_KEY_PRICE KEY_RUSTY_PRICE
#define DEFAULT_KEY_LEVEL 1
#define DEFAULT_KEY_TYPE KEY_RUSTY

//------------------------------------------------------------------------------
// class Arrow related
//------------------------------------------------------------------------------
#define ITEM_ID_ARROW "Arrow"

#define ARROW_SHAPE_NORTH '^'
#define ARROW_SHAPE_EAST '>'
#define ARROW_SHAPE_SOUTH 'v'
#define ARROW_SHAPE_WEST '<'

#define DEFAULT_ARROW_SHAPE ARROW_SHAPE_NORTH
#define DEFAULT_ARROW_NAME "Arrow"
#define DEFAULT_ARROW_PRICE 5
#define DEFAULT_ARROW_LEVEL 1
#define DEFAULT_ARROW_ATK 10
#define DEFAULT_ARROW_DIR ARROW_SHAPE_NORTH
#define DEFAULT_ARROW_MAX_RANGE 10

//------------------------------------------------------------------------------
// class Weapon related
//------------------------------------------------------------------------------
#define ITEM_ID_WEAPON "Weapon"

#define DEFAULT_WEAPON_SHAPE 'W'
#define DEFAULT_WEAPON_NAME "Weapon"
#define DEFAULT_WEAPON_PRICE 500
#define DEFAULT_WEAPON_LEVEL 1
#define DEFAULT_WEAPON_ATK 5
#define DEFAULT_WEAPON_DURABILITY 200
#define DEFAULT_WEAPON_NUM_HANDS 1
#define DEFAULT_WEAPON_TYPE WEAPON_WOOD

#define WEAPON_ONE_HAND 1
#define WEAPON_TWO_HAND 2

#define WEAPON_SHAPE_NONE '\0'
#define WEAPON_ONE_HAND_SHAPE '!'
#define WEAPON_TWO_HAND_SHAPE '?'
#define WEAPON_BOW_SHAPE 'C'

#define NUM_RANDOM_WEAPONS 10

#define WEAPON_WOOD 0       //lvl 1+
#define WEAPON_STONE 1      //lvl 10+

//not use yet
//#define WEAPON_BRONZE 2   //lvl 20+
//#define WEAPON_IRON 3     //lvl 30+
//#define WEAPON_SILVER 4   //lvl 40+
//#define WEAPON_GOLD 5     //lvl 50+
//#define WEAPON_OBSIDIAN 6 //lvl 60+
//#define WEAPON_DIAMOND 7  //lvl 70+
//#define WEAPON_PLATINUM 8 //lvl 80+
//#define WEAPON_GOD 9      //lvl 90+

//------------------------------------------------------------------------------
// class Armor related
//------------------------------------------------------------------------------
#define ITEM_ID_ARMOR "Armor"

#define DEFAULT_ARMOR_SHAPE 'A'
#define DEFAULT_ARMOR_NAME "Armor"
#define DEFAULT_ARMOR_PRICE 500
#define DEFAULT_ARMOR_LEVEL 1
#define DEFAULT_ARMOR_DEFENCE 2
#define DEFAULT_ARMOR_DURABILITY 200

#define BODY_PART_ID_NONE -1
#define BODY_PART_ID_HEAD 1
#define BODY_PART_ID_CHEST 2
#define BODY_PART_ID_BACK 3
#define BODY_PART_ID_HANDS 4
#define BODY_PART_ID_LEGS 5
#define BODY_PART_ID_FEET 6
#define BODY_PART_ID_LEFT_HAND 7
#define BODY_PART_ID_RIGHT_HAND 8

#define ARMOR_SHAPE_NONE '\0'
#define ARMOR_SHAPE_HEAD 'A'
#define ARMOR_SHAPE_CHEST 'W'
#define ARMOR_SHAPE_BACK 'Q'
#define ARMOR_SHAPE_HANDS 'U'
#define ARMOR_SHAPE_LEGS 'L'
#define ARMOR_SHAPE_FEET 'F'

#define DEFAULT_ARMOR_TYPE ARMOR_WOOD

#define NUM_RANDOM_ARMORS 6

#define ARMOR_WOOD 0       //lvl 1+
//#define ARMOR_STONE 1      //lvl 10+

//not use yet
//#define ARMOR_BRONZE 2   //lvl 20+
//#define ARMOR_IRON 3     //lvl 30+
//#define ARMOR_SILVER 4   //lvl 40+
//#define ARMOR_GOLD 5     //lvl 50+
//#define ARMOR_OBSIDIAN 6 //lvl 60+
//#define ARMOR_DIAMOND 7  //lvl 70+
//#define ARMOR_PLATINUM 8 //lvl 80+
//#define ARMOR_GOD 9      //lvl 90+

//------------------------------------------------------------------------------
// class Bomb related
//------------------------------------------------------------------------------
#define ITEM_ID_BOMB "Bomb"

#define DEFAULT_BOMB_SHAPE '*'
#define DEFAULT_BOMB_NAME "Bomb"
#define DEFAULT_BOMB_PRICE 100
#define DEFAULT_BOMB_DISPOSABLE true

#define DEFAULT_BOMB_RANGE 7
#define DEFAULT_BOMB_ATK 100

#define BOMB_WAVE_FRAME_INTERVAL 1
#define BOMB_WAVE_SHAPE '@'

//------------------------------------------------------------------------------
// class Bomb related
//------------------------------------------------------------------------------
#define ITEM_ID_TIMEBOMB "TimeBomb"

#define DEFAULT_TIMEBOMB_SHAPE '_'
#define DEFAULT_TIMEBOMB_NAME "TimeBomb"
#define DEFAULT_TIMEBOMB_PRICE 100
#define DEFAULT_TIMEBOMB_DISPOSABLE true

#define DEFAULT_TIMEBOMB_RANGE 7
#define DEFAULT_TIMEBOMB_ATK 100

#define TIMEBOMB_WAVE_FRAME_INTERVAL 1
#define TIMEBOMB_WAVE_SHAPE '@'

//------------------------------------------------------------------------------
// class Magicscroll related
//------------------------------------------------------------------------------
#define ITEM_ID_MAGICSCROLL "Magicscroll"

#define DEFAULT_MAGICSCROLL_SHAPE '$'
#define DEFAULT_MAGICSCROLL_NAME "Magicscroll"
#define DEFAULT_MAGICSCROLL_PRICE 100

//------------------------------------------------------------------------------
// class Torch related
//------------------------------------------------------------------------------
#define ITEM_ID_TORCH "Torch"

#define DEFAULT_TORCH_RANGE 5
#define DEFAULT_TORCH_SHAPE 'I'
#define DEFAULT_TORCH_NAME "Torch"
#define DEFAULT_TORCH_PRICE 1000

//------------------------------------------------------------------------------
// FX related
//------------------------------------------------------------------------------
#define MAX_NUM_SHOCKWAVES 100

//------------------------------------------------------------------------------
// Magic related
//------------------------------------------------------------------------------
#define MAGIC_KNIGHT_LIGHT_HEAL_RING 0
#define MAGIC_KNIGHT_LIGHT_SELF_HEAL 1
#define MAGIC_KNIGHT_SLASH 2

#define MAGIC_PALADIN_HEAL_RING 3
#define MAGIC_PALADIN_SELF_HEAL 4
#define MAGIC_PALADIN_SLASH 5

#define MAGIC_WARRIOR_STOMP 6
#define MAGIC_WARRIOR_DEATH_CIRCLE 7
#define MAGIC_WARRIOR_SLASH 8

#define MAGIC_HUNTER_TRIPLE_FIRE 9
#define MAGIC_HUNTER_LIGHT_HEAL 10
#define MAGIC_HUNTER_QUAD_STRIKE 11

#define MAGIC_ARCHER_OCTO_STRIKE 12
#define MAGIC_ARCHER_SNIPE 13
#define MAGIC_ARCHER_ARROW_PLATTER 14

#define MAX_MAGIC_TYPES 15

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Container
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Inventory related
//------------------------------------------------------------------------------
#define DEFAULT_INVENTORY_MAX_NUM_ITMES 5

#define DEFAULT_SLOTS_MAX_NUM_ITMES 5
#define DEFAULT_BACKPACK_CAPACITY 10

#define COMMAND_MOVE_ITEM_FROM_SLOTS_TO_BACKPACK 'z'
#define COMMAND_MOVE_ITEM_FROM_BACKPACK_TO_SLOTS 'x'
#define COMMAND_MOVE_ITEM_FROM_BACKPACK_TO_BACKPACK 'c'
#define COMMAND_MOVE_ITEM_FROM_SLOTS_TO_SLOTS 'v'
#define COMMAND_ATTACK 'e'
#define COMMAND_UNEQUIP_ARMOR 'f'
#define COMMAND_FIRST_SKILL 'r'
#define COMMAND_SECOND_SKILL 't'
#define COMMAND_THIRD_SKILL 'y'
#define COMMAND_GET_OFF_CAR 'g'

//------------------------------------------------------------------------------
// Backpack(Inventory) related
//------------------------------------------------------------------------------
#define HERO_BACKPACK_TOGGLE 'q'
#define HERO_BACKPACK_SHOW_DEFAULT false

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// ETC
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Color related
//------------------------------------------------------------------------------

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

//------------------------------------------------------------------------------
// save/load general
//------------------------------------------------------------------------------
#define TOMB_STONE_EMPTY "EMPTY"
#define TOMB_STONE_NON_EMPTY "NON-EMPTY"

//------------------------------------------------------------------------------
// A* related
//------------------------------------------------------------------------------
#define INF 2147483647
#define MAX_LEN_PATH_BY_ASTAR (MAX_ROW_SIZE*MAX_COL_SIZE)

//------------------------------------------------------------------------------
// MonRespawnEvent related
//------------------------------------------------------------------------------
#define MON_RESPAWN_EVENT_INTERVAL_MIN (5*FPS)
#define MON_RESPAWN_EVENT_INTERVAL_MAX (10*FPS)

//------------------------------------------------------------------------------
// DayAndNightEvent related
//------------------------------------------------------------------------------
#define DAY_AND_NIGHT_EVENT_INTERVAL (3*FPS)

//------------------------------------------------------------------------------
// TimeBombEvent related
//------------------------------------------------------------------------------
#define TIME_BOMB_EVENT_INTERVAL (5*FPS)

//------------------------------------------------------------------------------
// BossRushEvent related
//------------------------------------------------------------------------------
#define BOSS_RUSH_EVENT_INTERVAL (5*FPS)

//------------------------------------------------------------------------------
// Statistics related
//------------------------------------------------------------------------------
#define STAT_LOG_EVENT_INTERVAL (5*FPS)
#define STAT_LOG_FILENAME "rpg_log.txt"

#endif
