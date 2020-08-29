#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "hero.h"
#include "car.h"
#include "board.h"
#include "prop.h"

#include "sim.h"
extern Sim *sim;

// Default Constructor
Car::Car()
: Unit(DEFAULT_CAR_SHAPE, -1, -1, -1, -1,
       -1, -1,
       -1, -1,
       -1, -1, false) {
    carDir = MOVE_DIR_NONE;
    idle = true;
}

Car::~Car() {
    delete passenger;
    passenger = NULL;
}

void Car::print() {
#ifdef ANSI_COLOR_OUTPUT
    cout << CYAN;
#endif
    cout << shape;
#ifdef ANSI_COLOR_OUTPUT
    cout << RESET;
#endif
}

void Car::move(int moveDir) {
    if (passenger == NULL) {
        return;
    }
    
    int prevRow = row;
    int prevCol = col;
    int nextRow = row;
    int nextCol = col;
    
    if (carDir != MOVE_DIR_NONE) {
        if (carDir == MOVE_DIR_NORTH) {
            nextRow = row - 1;
        }
        else if (carDir == MOVE_DIR_EAST) {
            nextCol = col + 1;
        }
        else if (carDir == MOVE_DIR_SOUTH) {
            nextRow = row + 1;
        }
        else if (carDir == MOVE_DIR_WEST) {
            nextCol = col - 1;
        }

        if (sim->board->validate(nextRow, nextCol) &&
            sim->board->isClimbable(nextRow, nextCol)) {
            sim->board->setUnit(prevRow, prevCol, NULL);
            sim->board->setUnit(nextRow, nextCol, this);
            passenger->setRow(nextRow);
            passenger->setCol(nextCol);
            unitCurDir = carDir;
        }
    }
}

void Car::changeDirection(int moveDir) {
    prevDir = carDir;

    if (prevDir == MOVE_DIR_NONE && moveDir != MOVE_DIR_NONE) {
        idle = false;
        carDir = moveDir;
    }
    else if (moveDir != MOVE_DIR_NONE &&
             prevDir != MOVE_DIR_NONE &&
             prevDir != moveDir &&
             (prevDir + moveDir) % 2 == 0) {
        idle = true;
        carDir = MOVE_DIR_NONE;
        prevDir = MOVE_DIR_NONE;
    }
    else if (prevDir != MOVE_DIR_NONE && moveDir != MOVE_DIR_NONE) {
        idle = false;
        carDir = moveDir;
    }
    
    if (passenger != NULL && moveDir != MOVE_DIR_NONE) {
        ((Hero *)passenger)->setHeroFacingDirection(moveDir);
    }
}

bool Car::isCar() {
    return true;
}

int Car::getCarDir() {
    return carDir;
}

void Car::setCarDir(int carDir) {
    this->carDir = carDir;
    if ((prevDir + carDir) % 2 == 0) {
        idle = true;
    }
}

int Car::getPrevDir() {
    return prevDir;
}

void Car::setPrevDir(int prevDir) {
    this->prevDir = prevDir;
}

bool Car::getIdle() {
    return idle;
}

void Car::setIdle(int idle) {
    this->idle = idle;
}

void Car::interact(Unit *unit) {
    if (unit == NULL) {
        return;
    }
    
    if (passenger == NULL) {
        unit->getInCar(this);
        passenger = (Hero*)unit;
        carDir = MOVE_DIR_NONE;
    }
}

void Car::getOffCar() {
    if (!idle) {
        return;
    }
    
    for (int i = row-1; i <= row+1; i++) {
        for (int j = col-1; j <= col+1; j++) {
            if (sim->board->validate(i, j) &&
                sim->board->isClimbable(i, j)) {
                sim->board->setUnit(i, j, passenger);
                passenger->getOffCar();
                idle = true;
                passenger = NULL;
                return;
            }
        }
    }
}

string Car::getID() {
    return string(UNIT_ID_CAR);
}

void Car::save(ostream &out) {
    Unit::save(out);
    out << "#-------------------- class Car" << endl;
    
    // passenger: do not save!
    
    out << "# carDir" << endl;
    out << carDir << endl;
    
    out << "# prevDir" << endl;
    out << prevDir << endl;
    
    out << "# idle" << endl;
    out << idle << endl;
}

void Car::load(istream &in) {
    Unit::load(in);
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Car" << endl;
    in.getline(buf, 80); // skip comment
    
    passenger = NULL;
    
    //out << "# carDir" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << carDir << endl;
    in >> carDir;
    in.get(); // skip enter code.
    
    //out << "# prevDir" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << prevDir << endl;
    in >> prevDir;
    in.get(); // skip enter code.
    
    //out << "# idle" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << idle << endl;
    in >> idle;
    in.get(); // skip enter code.
    
}
