#include <iostream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "magic.h"
#include "unit.h"
#include "board.h"

#include "sim.h"
extern Sim *sim;

// Default Constructor
Magic::Magic() {
    shape = '%';
    job = rand() % 5;
    skillNumber = rand() % 3 + 1;
}

Magic::Magic(Magic &other) {
    //*this = other;
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
}

Magic::Magic(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

Magic::~Magic() {}

Magic &Magic::operator=(Magic &other) {
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

void Magic::print() {
#ifdef ANSI_COLOR_OUTPUT
    if (skillNumber == 1) {
        cout << RED;
    }
    else if (skillNumber == 2) {
        cout << BLUE;
    }
    else {
        cout << GREEN;
    }
#endif
    cout << shape;
#ifdef ANSI_COLOR_OUTPUT
    cout << RESET;
#endif
}

void Magic::printFullSpec() {
    if (job == HERO_JOB_KNIGHT) {
        cout << " Job(" << setw(8) << "Knight" << ")";
    }
    else if (job == HERO_JOB_PALADIN) {
        cout << " Job(" << setw(8) << "Paladin" << ")";
    }
    else if (job == HERO_JOB_WARRIOR) {
        cout << " Job(" << setw(8) << "Warrior" << ")";
    }
    else if (job == HERO_JOB_HUNTER) {
        cout << " Job(" << setw(8) << "Hunter" << ")";
    }
    else {
        cout << " Job(" << setw(8) << "Archer" << ")";
    }
    
    cout << " Skill(" << skillNumber << ")";
}

int Magic::getJob() {
    return job;
}

int Magic::getSkillNumber() {
    return skillNumber;
}

bool Magic::cast(Unit *unit) {
    // N/A
    return false;
}

void Magic::effect(Unit *caster, Unit *unit, Item *item, Prop *prop) {
    // N/A
}

Magic *Magic::clone() {
    // N/A
    return NULL;
}

void Magic::save(ostream &out) {
    out << "#-------------------- class Magic" << endl;
    
    out << "# shape" << endl;
    out << shape << endl;
    
    out << "# job" << endl;
    out << job << endl;

    out << "# skillNumber" << endl;
    out << skillNumber << endl;
}

void Magic::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Prop" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# shape" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << shape << endl;
    in >> shape;
    in.get(); // skip enter code.

    //out << "# job" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << job << endl;
    in >> job;
    in.get(); // skip enter code.

    //out << "# skillNumber" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << skillNumber << endl;
    in >> skillNumber;
    in.get(); // skip enter code.
}

Magic *createRandMagic() {
    
    int randType = rand() % MAX_MAGIC_TYPES;
    
    if (randType == MAGIC_KNIGHT_LIGHT_HEAL_RING) {
        return new MagicKnightLightHealRing();
    }
    else if (randType == MAGIC_KNIGHT_LIGHT_SELF_HEAL) {
        return new MagicKnightSelfLightHeal();
    }
    else if (randType == MAGIC_KNIGHT_SLASH) {
        return new MagicKnightSlash();
    }
    else if (randType == MAGIC_PALADIN_HEAL_RING) {
        return new MagicPaladinHealRing();
    }
    else if (randType == MAGIC_PALADIN_SELF_HEAL) {
        return new MagicPaladinSelfHeal();
    }
    else if (randType == MAGIC_PALADIN_SLASH) {
        return new MagicPaladinSlash();
    }
    else if (randType == MAGIC_WARRIOR_STOMP) {
        return new MagicWarriorStomp;
    }
    else if (randType == MAGIC_WARRIOR_DEATH_CIRCLE) {
        return new MagicWarriorDeathCircle;
    }
    else if (randType == MAGIC_WARRIOR_SLASH) {
        return new MagicWarriorSlash();
    }
    else if (randType == MAGIC_HUNTER_TRIPLE_FIRE) {
        return new MagicHunterTripleFire;
    }
    else if (randType == MAGIC_HUNTER_LIGHT_HEAL) {
        return new MagicHunterLightHeal;
    }
    else if (randType == MAGIC_HUNTER_QUAD_STRIKE) {
        return new MagicHunterQuadStrike;
    }
    else if (randType == MAGIC_ARCHER_OCTO_STRIKE) {
        return new MagicArcherOctoStrike();
    }
    else if (randType == MAGIC_ARCHER_SNIPE) {
        return new MagicArcherSnipe();
    }
    else {
        return new MagicArcherArrowPlatter();
    }
}

Magic *createMagicByID(string magicID) {
    
    if (magicID == "MagicKnightLightHealRing") {
        return new MagicKnightLightHealRing();
    }
    else if (magicID == "MagicKnightSelfLightHeal") {
        return new MagicKnightSelfLightHeal();
    }
    else if (magicID == "MagicKnightSlash") {
        return new MagicKnightSlash();
    }
    else if (magicID == "MagicPaladinHealRing") {
        return new MagicPaladinHealRing();
    }
    else if (magicID == "MagicPaladinSelfHeal") {
        return new MagicPaladinSelfHeal();
    }
    else if (magicID == "MagicPaladinSlash") {
        return new MagicPaladinSlash();
    }
    else if (magicID == "MagicWarriorStomp") {
        return new MagicWarriorStomp;
    }
    else if (magicID == "MagicWarriorDeathCircle") {
        return new MagicWarriorDeathCircle;
    }
    else if (magicID == "MagicWarriorSlash") {
        return new MagicWarriorSlash();
    }
    else if (magicID == "MagicHunterTripleFire") {
        return new MagicHunterTripleFire;
    }
    else if (magicID == "MagicHunterLightHeal") {
        return new MagicHunterLightHeal;
    }
    else if (magicID == "MagicHunterQuadStrike") {
        return new MagicHunterQuadStrike;
    }
    else if (magicID == "MagicArcherOctoStrike") {
        return new MagicArcherOctoStrike();
    }
    else if (magicID == "MagicArcherSnipe") {
        return new MagicArcherSnipe();
    }
    else {
        return new MagicArcherArrowPlatter();
    }

}

//==============================================================================
// class Knight
//==============================================================================

//------------------------------------------------------------------------------
// class MagicKnightLightHealRing
//------------------------------------------------------------------------------

MagicKnightLightHealRing::MagicKnightLightHealRing() {
    shape = '%';
    job = HERO_JOB_KNIGHT;
    skillNumber = 1;
}

MagicKnightLightHealRing::MagicKnightLightHealRing(MagicKnightLightHealRing &other) : Magic(other) {
    //*this = other;
}

MagicKnightLightHealRing::MagicKnightLightHealRing(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicKnightLightHealRing::~MagicKnightLightHealRing() {}

MagicKnightLightHealRing &MagicKnightLightHealRing::operator=(MagicKnightLightHealRing &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicKnightLightHealRing::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    int row = unit->getRow();
    int col = unit->getCol();
    int mp = unit->getMp();
    
    if (mp >= 5) {
        sim->board->startWave(unit, NULL, NULL,
                          row, col,
                          4,
                          BOMB_WAVE_FRAME_INTERVAL,
                          BOMB_WAVE_SHAPE, skillNumber);
        unit->decMp(5);
        return true;
    }
    return false;
}

void MagicKnightLightHealRing::effect(Unit *caster, Unit *unit, Item *item, Prop *prop) {
    
    int meeleAtk = caster->getMeleeAtk();
    
    caster->incHp(meeleAtk/10);
    if (unit->isHero()) {
        unit->incHp(meeleAtk/2);
    }
    else if (unit->isMon()) {
        unit->decHp(meeleAtk*3);
        caster->setUnitEngaged(unit);
        unit->setUnitEngaged(caster);
    }
    
    if (unit->getHp() == 0) {
        if (unit->isHero()) {
            caster->incGold(unit->getGold()/10);
            caster->incExp(unit->getLevel()*50);
            unit->decExp(unit->getLevel()*50);
        }
        else if (unit->isMon()) {
            caster->incGold(unit->getGold());
            caster->incExp(unit->getExp());
        }
    }
}

Magic *MagicKnightLightHealRing::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicKnightLightHealRing(*this);
}

string MagicKnightLightHealRing::getID() {
    return string("MagicKnightLightHealRing");
}

void MagicKnightLightHealRing::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicKnightLightHealRing" << endl;
}

void MagicKnightLightHealRing::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];

    //out << "#-------------------- class MagicKnightLightHealRing" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class MagicKnightSelfLightHeal
//------------------------------------------------------------------------------

MagicKnightSelfLightHeal::MagicKnightSelfLightHeal() {
    shape = '%';
    job = HERO_JOB_KNIGHT;
    skillNumber = 2;
}

MagicKnightSelfLightHeal::MagicKnightSelfLightHeal(MagicKnightSelfLightHeal &other) : Magic(other) {
    //*this = other;
}

MagicKnightSelfLightHeal::MagicKnightSelfLightHeal(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicKnightSelfLightHeal::~MagicKnightSelfLightHeal() {}

MagicKnightSelfLightHeal &MagicKnightSelfLightHeal::operator=(MagicKnightSelfLightHeal &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicKnightSelfLightHeal::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    int mp = unit->getMp();
    
    if (mp >= 10) {
        unit->incHp(20);
        unit->decMp(10);
        return true;
    }
    return false;
}

Magic *MagicKnightSelfLightHeal::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicKnightSelfLightHeal(*this);
}

string MagicKnightSelfLightHeal::getID() {
    return string("MagicKnightSelfLightHeal");
}

void MagicKnightSelfLightHeal::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicKnightSelfLightHeal" << endl;
}

void MagicKnightSelfLightHeal::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicKnightSelfLightHeal" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class MagicKnightSlash
//------------------------------------------------------------------------------

MagicKnightSlash::MagicKnightSlash() {
    shape = '%';
    job = HERO_JOB_KNIGHT;
    skillNumber = 3;
}

MagicKnightSlash::MagicKnightSlash(MagicKnightSlash &other) : Magic(other) {
    //*this = other;
}

MagicKnightSlash::MagicKnightSlash(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicKnightSlash::~MagicKnightSlash() {}

MagicKnightSlash &MagicKnightSlash::operator=(MagicKnightSlash &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicKnightSlash::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    int row = unit->getRow();
    int col = unit->getCol();
    int mp = unit->getMp();
    
    if (mp >= 5) {
        int rowAfter;
        int colAfter;
        
        if (unit->getHeroFacingDirection() == MOVE_DIR_NORTH) {
            rowAfter = row-1;
            colAfter = col;
        }
        else if (unit->getHeroFacingDirection() == MOVE_DIR_EAST) {
            rowAfter = row;
            colAfter = col+1;
        }
        else if (unit->getHeroFacingDirection() == MOVE_DIR_SOUTH) {
            rowAfter = row+1;
            colAfter = col;
        }
        else {
            rowAfter = row;
            colAfter = col-1;
        }
        if (sim->board->getUnit(rowAfter, colAfter) != NULL) {
            sim->board->getUnit(rowAfter, colAfter)->decHp(unit->getMeleeAtk()*3);
            
            sim->board->getUnit(rowAfter, colAfter)->setUnitEngaged(unit);
            unit->setUnitEngaged(sim->board->getUnit(rowAfter, colAfter));
            unit->decMp(5);
            return true;
        }
    }
    
    return false;
}

Magic *MagicKnightSlash::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicKnightSlash(*this);
}

string MagicKnightSlash::getID() {
    return string("MagicKnightSlash");
}

void MagicKnightSlash::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicKnightSlash" << endl;
}

void MagicKnightSlash::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicKnightSlash" << endl;
    in.getline(buf, 80); // skip comment
}

//==============================================================================
// class Paladin
//==============================================================================

//------------------------------------------------------------------------------
// class MagicPaladinHealRing
//------------------------------------------------------------------------------

MagicPaladinHealRing::MagicPaladinHealRing() {
    shape = '%';
    job = HERO_JOB_PALADIN;
    skillNumber = 1;
}

MagicPaladinHealRing::MagicPaladinHealRing(MagicPaladinHealRing &other) : Magic(other) {
    //*this = other;
}

MagicPaladinHealRing::MagicPaladinHealRing(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicPaladinHealRing::~MagicPaladinHealRing() {}

MagicPaladinHealRing &MagicPaladinHealRing::operator=(MagicPaladinHealRing &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicPaladinHealRing::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    int row = unit->getRow();
    int col = unit->getCol();
    int mp = unit->getMp();
    
    if (mp >= 5) {
        sim->board->startWave(unit, NULL, NULL,
                          row, col,
                          6,
                          BOMB_WAVE_FRAME_INTERVAL,
                          BOMB_WAVE_SHAPE, skillNumber);
        unit->decMp(5);
        return true;
    }
    
    return false;
}

void MagicPaladinHealRing::effect(Unit *caster, Unit *unit, Item *item, Prop *prop) {
    
    int meeleAtk = caster->getMeleeAtk();
    
    if (skillNumber == 1) {
        unit->decHp(meeleAtk*2);
        caster->incHp(meeleAtk/5);
        caster->setUnitEngaged(unit);
        unit->setUnitEngaged(caster);
    }
    
    if (unit->getHp() == 0) {
        if (unit->isHero()) {
            caster->incGold(unit->getGold()/10);
            caster->incExp(unit->getLevel()*50);
            unit->decExp(unit->getLevel()*50);
        }
        else if (unit->isMon()) {
            caster->incGold(unit->getGold());
            caster->incExp(unit->getExp());
        }
    }
}

Magic *MagicPaladinHealRing::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicPaladinHealRing(*this);
}

string MagicPaladinHealRing::getID() {
    return string("MagicPaladinHealRing");
}

void MagicPaladinHealRing::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicPaladinHealRing" << endl;
}

void MagicPaladinHealRing::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicPaladinHealRing" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class MagicPaladinSelfHeal
//------------------------------------------------------------------------------

MagicPaladinSelfHeal::MagicPaladinSelfHeal() {
    shape = '%';
    job = HERO_JOB_PALADIN;
    skillNumber = 2;
}

MagicPaladinSelfHeal::MagicPaladinSelfHeal(MagicPaladinSelfHeal &other) : Magic(other) {
    //*this = other;
}

MagicPaladinSelfHeal::MagicPaladinSelfHeal(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicPaladinSelfHeal::~MagicPaladinSelfHeal() {}

MagicPaladinSelfHeal &MagicPaladinSelfHeal::operator=(MagicPaladinSelfHeal &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicPaladinSelfHeal::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    if (unit->getMp() >= (unit->getMaxMp()/10)) {
        unit->incHp(unit->getMaxHp()/10);
        unit->decMp(unit->getMaxMp()/10);
        return true;
    }
    
    return false;
}

Magic *MagicPaladinSelfHeal::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicPaladinSelfHeal(*this);
}

string MagicPaladinSelfHeal::getID() {
    return string("MagicPaladinSelfHeal");
}

void MagicPaladinSelfHeal::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicPaladinSelfHeal" << endl;
}

void MagicPaladinSelfHeal::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicPaladinSelfHeal" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class MagicPaladinSlash
//------------------------------------------------------------------------------

MagicPaladinSlash::MagicPaladinSlash() {
    shape = '%';
    job = HERO_JOB_PALADIN;
    skillNumber = 3;
}

MagicPaladinSlash::MagicPaladinSlash(MagicPaladinSlash &other) : Magic(other) {
    //*this = other;
}

MagicPaladinSlash::MagicPaladinSlash(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicPaladinSlash::~MagicPaladinSlash() {}

MagicPaladinSlash &MagicPaladinSlash::operator=(MagicPaladinSlash &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicPaladinSlash::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    int row = unit->getRow();
    int col = unit->getCol();
    int mp = unit->getMp();
    
    if (mp >= 5) {
        int rowAfter;
        int colAfter;
        
        if (unit->getHeroFacingDirection() == MOVE_DIR_NORTH) {
            rowAfter = row-1;
            colAfter = col;
        }
        else if (unit->getHeroFacingDirection() == MOVE_DIR_EAST) {
            rowAfter = row;
            colAfter = col+1;
        }
        else if (unit->getHeroFacingDirection() == MOVE_DIR_SOUTH) {
            rowAfter = row+1;
            colAfter = col;
        }
        else {
            rowAfter = row;
            colAfter = col-1;
        }
        if (sim->board->getUnit(rowAfter, colAfter) != NULL) {
            sim->board->getUnit(rowAfter, colAfter)->decHp(unit->getMeleeAtk()*3);
            
            sim->board->getUnit(rowAfter, colAfter)->setUnitEngaged(unit);
            unit->setUnitEngaged(sim->board->getUnit(rowAfter, colAfter));
            unit->decMp(5);
            return true;
        }
    }
    
    return false;
}

Magic *MagicPaladinSlash::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicPaladinSlash(*this);
}

string MagicPaladinSlash::getID() {
    return string("MagicPaladinSlash");
}

void MagicPaladinSlash::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicPaladinSlash" << endl;
}

void MagicPaladinSlash::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicPaladinSlash" << endl;
    in.getline(buf, 80); // skip comment
}

//==============================================================================
// class Warrior
//==============================================================================

//------------------------------------------------------------------------------
// class MagicWarriorStomp
//------------------------------------------------------------------------------

MagicWarriorStomp::MagicWarriorStomp() {
    shape = '%';
    job = HERO_JOB_WARRIOR;
    skillNumber = 1;
}

MagicWarriorStomp::MagicWarriorStomp(MagicWarriorStomp &other) : Magic(other) {
    //*this = other;
}

MagicWarriorStomp::MagicWarriorStomp(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicWarriorStomp::~MagicWarriorStomp() {}

MagicWarriorStomp &MagicWarriorStomp::operator=(MagicWarriorStomp &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicWarriorStomp::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    int row = unit->getRow();
    int col = unit->getCol();
    int mp = unit->getMp();
    
    if (mp >= 5) {
        sim->board->startWave(unit, NULL, NULL,
                          row, col,
                          5,
                          BOMB_WAVE_FRAME_INTERVAL,
                          BOMB_WAVE_SHAPE, skillNumber);
        unit->decMp(5);
        return true;
    }
    
    return false;
}

void MagicWarriorStomp::effect(Unit *caster, Unit *unit, Item *item, Prop *prop) {
    
    int meeleAtk = caster->getMeleeAtk();
    
    if (skillNumber == 1) {
        unit->decHp(meeleAtk*2);
        caster->setUnitEngaged(unit);
        unit->setUnitEngaged(caster);
    }
    
    if (unit->getHp() == 0) {
        if (unit->isHero()) {
            caster->incGold(unit->getGold()/10);
            caster->incExp(unit->getLevel()*50);
            unit->decExp(unit->getLevel()*50);
        }
        else if (unit->isMon()) {
            caster->incGold(unit->getGold());
            caster->incExp(unit->getExp());
        }
    }
}

Magic *MagicWarriorStomp::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicWarriorStomp(*this);
}

string MagicWarriorStomp::getID() {
    return string("MagicWarriorStomp");
}

void MagicWarriorStomp::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicWarriorStomp" << endl;
}

void MagicWarriorStomp::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicWarriorStomp" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class MagicWarriorDeathCircle
//------------------------------------------------------------------------------

MagicWarriorDeathCircle::MagicWarriorDeathCircle() {
    shape = '%';
    job = HERO_JOB_WARRIOR;
    skillNumber = 2;
}

MagicWarriorDeathCircle::MagicWarriorDeathCircle(MagicWarriorDeathCircle &other) : Magic(other) {
    //*this = other;
}

MagicWarriorDeathCircle::MagicWarriorDeathCircle(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicWarriorDeathCircle::~MagicWarriorDeathCircle() {}

MagicWarriorDeathCircle &MagicWarriorDeathCircle::operator=(MagicWarriorDeathCircle &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicWarriorDeathCircle::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    int row = unit->getRow();
    int col = unit->getCol();
    int mp = unit->getMp();
    
    if (mp >= 10) {
        sim->board->startWave(unit, NULL, NULL,
                          row, col,
                          2,
                          BOMB_WAVE_FRAME_INTERVAL,
                          BOMB_WAVE_SHAPE, skillNumber);
        unit->decMp(10);
        return true;
    }
    
    return false;
}

void MagicWarriorDeathCircle::effect(Unit *caster, Unit *unit, Item *item, Prop *prop) {
    
    int meeleAtk = caster->getMeleeAtk();
    
    
    unit->decHp(meeleAtk*3);
    caster->setUnitEngaged(unit);
    unit->setUnitEngaged(caster);
    
    
    if (unit->getHp() == 0) {
        if (unit->isHero()) {
            caster->incGold(unit->getGold()/10);
            caster->incExp(unit->getLevel()*50);
            unit->decExp(unit->getLevel()*50);
        }
        else if (unit->isMon()) {
            caster->incGold(unit->getGold());
            caster->incExp(unit->getExp());
        }
    }
}

Magic *MagicWarriorDeathCircle::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicWarriorDeathCircle(*this);
}

string MagicWarriorDeathCircle::getID() {
    return string("MagicWarriorDeathCircle");
}

void MagicWarriorDeathCircle::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicWarriorDeathCircle" << endl;
}

void MagicWarriorDeathCircle::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicWarriorDeathCircle" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class MagicWarriorSlash
//------------------------------------------------------------------------------

MagicWarriorSlash::MagicWarriorSlash() {
    shape = '%';
    job = HERO_JOB_WARRIOR;
    skillNumber = 3;
}

MagicWarriorSlash::MagicWarriorSlash(MagicWarriorSlash &other) : Magic(other) {
    //*this = other;
}

MagicWarriorSlash::MagicWarriorSlash(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicWarriorSlash::~MagicWarriorSlash() {}

MagicWarriorSlash &MagicWarriorSlash::operator=(MagicWarriorSlash &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicWarriorSlash::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    int row = unit->getRow();
    int col = unit->getCol();
    int mp = unit->getMp();
    
    if (mp >= 5) {
        int rowAfter;
        int colAfter;
        
        if (unit->getHeroFacingDirection() == MOVE_DIR_NORTH) {
            rowAfter = row-1;
            colAfter = col;
        }
        else if (unit->getHeroFacingDirection() == MOVE_DIR_EAST) {
            rowAfter = row;
            colAfter = col+1;
        }
        else if (unit->getHeroFacingDirection() == MOVE_DIR_SOUTH) {
            rowAfter = row+1;
            colAfter = col;
        }
        else {
            rowAfter = row;
            colAfter = col-1;
        }
        if (sim->board->getUnit(rowAfter, colAfter) != NULL) {
            sim->board->getUnit(rowAfter, colAfter)->decHp(unit->getMeleeAtk()*3);
            
            sim->board->getUnit(rowAfter, colAfter)->setUnitEngaged(unit);
            unit->setUnitEngaged(sim->board->getUnit(rowAfter, colAfter));
            unit->decMp(5);
            return true;
        }
    }
    
    return false;
}

Magic *MagicWarriorSlash::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicWarriorSlash(*this);
}

string MagicWarriorSlash::getID() {
    return string("MagicWarriorSlash");
}

void MagicWarriorSlash::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicWarriorSlash" << endl;
}

void MagicWarriorSlash::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicWarriorSlash" << endl;
    in.getline(buf, 80); // skip comment
}

//==============================================================================
// class Hunter
//==============================================================================

//------------------------------------------------------------------------------
// class MagicHunterTripleFire
//------------------------------------------------------------------------------

MagicHunterTripleFire::MagicHunterTripleFire() {
    shape = '%';
    job = HERO_JOB_HUNTER;
    skillNumber = 1;
}

MagicHunterTripleFire::MagicHunterTripleFire(MagicHunterTripleFire &other) : Magic(other) {
    //*this = other;
}

MagicHunterTripleFire::MagicHunterTripleFire(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicHunterTripleFire::~MagicHunterTripleFire() {}

MagicHunterTripleFire &MagicHunterTripleFire::operator=(MagicHunterTripleFire &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicHunterTripleFire::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    if (unit->getMp() >= 5) {
        unit->incRangeAtk(unit->getRangeAtk());
        unit->rangeAttack(unit->getHeroFacingDirection());
        unit->rangeAttack(unit->getHeroFacingDirection());
        unit->rangeAttack(unit->getHeroFacingDirection());
        unit->decRangeAtk(unit->getRangeAtk()/2);
        
        unit->decMp(5);
        return true;
    }
    
    return false;
}

Magic *MagicHunterTripleFire::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicHunterTripleFire(*this);
}

string MagicHunterTripleFire::getID() {
    return string("MagicHunterTripleFire");
}

void MagicHunterTripleFire::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicHunterTripleFire" << endl;
}

void MagicHunterTripleFire::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicHunterTripleFire" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class MagicHunterLightHeal
//------------------------------------------------------------------------------

MagicHunterLightHeal::MagicHunterLightHeal() {
    shape = '%';
    job = HERO_JOB_HUNTER;
    skillNumber = 2;
}

MagicHunterLightHeal::MagicHunterLightHeal(MagicHunterLightHeal &other) : Magic(other) {
    //*this = other;
}

MagicHunterLightHeal::MagicHunterLightHeal(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicHunterLightHeal::~MagicHunterLightHeal() {}

MagicHunterLightHeal &MagicHunterLightHeal::operator=(MagicHunterLightHeal &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicHunterLightHeal::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    
    int mp = unit->getMp();
    
    if (mp >= 5) {
        unit->incHp(10);
        unit->decMp(5);
        return true;
    }
    
    return false;
}

Magic *MagicHunterLightHeal::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicHunterLightHeal(*this);
}

string MagicHunterLightHeal::getID() {
    return string("MagicHunterLightHeal");
}

void MagicHunterLightHeal::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicHunterLightHeal" << endl;
}

void MagicHunterLightHeal::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicHunterLightHeal" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class MagicHunterQuadStrike
//------------------------------------------------------------------------------

MagicHunterQuadStrike::MagicHunterQuadStrike() {
    shape = '%';
    job = HERO_JOB_HUNTER;
    skillNumber = 3;
}

MagicHunterQuadStrike::MagicHunterQuadStrike(MagicHunterQuadStrike &other) : Magic(other) {
    //*this = other;
}

MagicHunterQuadStrike::MagicHunterQuadStrike(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicHunterQuadStrike::~MagicHunterQuadStrike() {}

MagicHunterQuadStrike &MagicHunterQuadStrike::operator=(MagicHunterQuadStrike &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicHunterQuadStrike::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    if (unit->getMp() >= 5) {
        unit->rangeAttack(MOVE_DIR_NORTH);
        unit->rangeAttack(MOVE_DIR_EAST);
        unit->rangeAttack(MOVE_DIR_SOUTH);
        unit->rangeAttack(MOVE_DIR_WEST);
        
        unit->decMp(5);
        return true;
    }
    
    return false;
}

Magic *MagicHunterQuadStrike::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicHunterQuadStrike(*this);
}

string MagicHunterQuadStrike::getID() {
    return string("MagicHunterQuadStrike");
}

void MagicHunterQuadStrike::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicHunterQuadStrike" << endl;
}

void MagicHunterQuadStrike::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicHunterQuadStrike" << endl;
    in.getline(buf, 80); // skip comment
}

//==============================================================================
// class Archer
//==============================================================================

//------------------------------------------------------------------------------
// class MagicArcherOctoStrike
//------------------------------------------------------------------------------

MagicArcherOctoStrike::MagicArcherOctoStrike() {
    shape = '%';
    job = HERO_JOB_ARCHER;
    skillNumber = 1;
}

MagicArcherOctoStrike::MagicArcherOctoStrike(MagicArcherOctoStrike &other) : Magic(other) {
    //*this = other;
}

MagicArcherOctoStrike::MagicArcherOctoStrike(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicArcherOctoStrike::~MagicArcherOctoStrike() {}

MagicArcherOctoStrike &MagicArcherOctoStrike::operator=(MagicArcherOctoStrike &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicArcherOctoStrike::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }

    if (unit->getMp() >= 10) {
        unit->rangeAttack(MOVE_DIR_NORTH);
        unit->rangeAttack(MOVE_DIR_EAST);
        unit->rangeAttack(MOVE_DIR_SOUTH);
        unit->rangeAttack(MOVE_DIR_WEST);
        unit->rangeAttack(MOVE_DIR_NORTH);
        unit->rangeAttack(MOVE_DIR_EAST);
        unit->rangeAttack(MOVE_DIR_SOUTH);
        unit->rangeAttack(MOVE_DIR_WEST);
        
        unit->decMp(10);
        return true;
    }
    
    return false;
}

Magic *MagicArcherOctoStrike::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicArcherOctoStrike(*this);
}

string MagicArcherOctoStrike::getID() {
    return string("MagicArcherOctoStrike");
}

void MagicArcherOctoStrike::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicArcherOctoStrike" << endl;
}

void MagicArcherOctoStrike::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicArcherOctoStrike" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class MagicArcherSnipe
//------------------------------------------------------------------------------

MagicArcherSnipe::MagicArcherSnipe() {
    shape = '%';
    job = HERO_JOB_ARCHER;
    skillNumber = 2;
}

MagicArcherSnipe::MagicArcherSnipe(MagicArcherSnipe &other) : Magic(other) {
    //*this = other;
}

MagicArcherSnipe::MagicArcherSnipe(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicArcherSnipe::~MagicArcherSnipe() {}

MagicArcherSnipe &MagicArcherSnipe::operator=(MagicArcherSnipe &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicArcherSnipe::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }

    if (unit->getMp() >= 5) {
        unit->incRangeAtk(unit->getRangeAtk()*3);
        unit->rangeAttack(unit->getHeroFacingDirection());
        unit->decRangeAtk((unit->getRangeAtk()/4)*3);
        
        unit->decMp(5);
        return true;
    }
    
    return false;
}

Magic *MagicArcherSnipe::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicArcherSnipe(*this);
}

string MagicArcherSnipe::getID() {
    return string("MagicArcherSnipe");
}

void MagicArcherSnipe::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicArcherSnipe" << endl;
}

void MagicArcherSnipe::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicArcherSnipe" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class MagicArcherArrowPlatter
//------------------------------------------------------------------------------

MagicArcherArrowPlatter::MagicArcherArrowPlatter() {
    shape = '%';
    job = HERO_JOB_ARCHER;
    skillNumber = 3;
}

MagicArcherArrowPlatter::MagicArcherArrowPlatter(MagicArcherArrowPlatter &other) : Magic(other) {
    //*this = other;
}

MagicArcherArrowPlatter::MagicArcherArrowPlatter(char shape, int job, int skillNumber) {
    this->shape = shape;
    this->job = job;
    this->skillNumber = skillNumber;
}

MagicArcherArrowPlatter::~MagicArcherArrowPlatter() {}

MagicArcherArrowPlatter &MagicArcherArrowPlatter::operator=(MagicArcherArrowPlatter &other) {
    Magic::operator=(other);
    
    shape = other.shape;
    job = other.job;
    skillNumber = other.skillNumber;
    
    return *this;
}

bool MagicArcherArrowPlatter::cast(Unit *unit) {
    if (unit->getJob() != job) {
        cout << "error: the unit's job is not matched to the magic's job!" << endl;
        return false;
    }
    
    if (unit->getMp() >= 5) {
        unit->rangeAttack(unit->getHeroFacingDirection());
        unit->rangeAttack(unit->getHeroFacingDirection());
        unit->rangeAttack(MOVE_DIR_NORTH);
        unit->rangeAttack(MOVE_DIR_EAST);
        unit->rangeAttack(MOVE_DIR_SOUTH);
        unit->rangeAttack(MOVE_DIR_WEST);
        
        unit->decMp(5);
        return true;
    }
    
    return false;
}

Magic *MagicArcherArrowPlatter::clone() {
    // 이렇게 자식을 return할 수 있다.
    return new MagicArcherArrowPlatter(*this);
}

string MagicArcherArrowPlatter::getID() {
    return string("MagicArcherArrowPlatter");
}

void MagicArcherArrowPlatter::save(ostream &out) {
    Magic::save(out);
    
    out << "#-------------------- class MagicArcherArrowPlatter" << endl;
}

void MagicArcherArrowPlatter::load(istream &in) {
    Magic::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class MagicArcherArrowPlatter" << endl;
    in.getline(buf, 80); // skip comment
}
