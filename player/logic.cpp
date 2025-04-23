#include <iostream>
#include "helper.h"
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;



/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    ifstream inFS; //opening it
    char value;
    bool door = false;
    int r,c;
    bool exit = false;

    inFS.open(fileName);
    if(!inFS.is_open()){
        return nullptr;
    }
    inFS >> maxRow >> maxCol >> r >> c;

    if(inFS.fail()){
        return nullptr;
    }
    if(maxRow<=0 || maxCol<=0 || r<0 || c<0 || maxCol<=c || maxRow<=r || INT32_MAX/ maxCol < maxRow || INT32_MAX/ maxRow < maxCol || maxRow > 999999 || maxCol > 999999){//invalid measurements for the rows and columns
        return nullptr;
    }
        
    player.row = r;//reads players starting position
    player.col = c;

    char** map = createMap(maxRow,maxCol); //poinyrt
    
    for(int row=0; row<maxRow; row++){
        for(int col=0; col<maxCol; col++){
            inFS >> value;
            if(inFS.fail()){
                deleteMap(map,maxRow);
                return nullptr;
            }
            if(!inFS.eof()) {
                if(value == '-'){
                    map[row][col] = TILE_OPEN;
                } else if (value =='$'){
                    map[row][col] = TILE_TREASURE;
                } else if (value == '@'){
                    map[row][col] = TILE_AMULET;
                } else if (value == '+'){
                    map[row][col] = TILE_PILLAR;
                } else if (value == '?'){
                    map[row][col] = TILE_DOOR;
                    door = true;
                }else if (value == '!'){
                    map[row][col] = TILE_EXIT;
                    exit = true;
                } else if (value == 'M'){
                    map[row][col] = TILE_MONSTER;
                } else{
                    deleteMap(map,maxRow);
                    return nullptr;
                }
            } else {
                deleteMap(map,maxRow);
                return nullptr;
            }   
        }
    }
    if (map[player.row][player.col] != TILE_OPEN){
        deleteMap(map,maxRow);
        return nullptr;
    } 
    if (!door && !exit){
        deleteMap(map,maxRow);
        return nullptr;
    }
    
    char x;
    inFS >> x;
    if(!isspace(x) && !inFS.eof()){
        deleteMap(map,maxRow);  
        return nullptr;  
    } 

    map[player.row][player.col] = TILE_PLAYER;

    inFS.close();
    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    if(input == MOVE_UP){
        nextRow -= 1;
    } else if (input == MOVE_DOWN){
        nextRow += 1;
    } else if (input == MOVE_RIGHT){
        nextCol += 1;
    } else if (input == MOVE_LEFT){
        nextCol -= 1;
    } 
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    if(maxRow<=0 || maxCol<=0  || INT32_MAX/ maxCol < maxRow)
        return nullptr;
    char** map = new char*[maxRow];
    for( int row=0; row<maxRow; row++){
        map[row]= new char[maxCol];
    }
    for(int row=0; row<maxRow; row++){
        for(int col=0; col<maxCol; col++){
            map[row][col] = TILE_OPEN;
        }    
    }
    return map;

}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map) {
        for (int i = 0; i < maxRow; ++i) delete[] map[i];
        delete[] map;
        map = nullptr;
        maxRow = 0;
    }
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    if(maxRow <=0|| map == nullptr || maxCol <=0){
        return nullptr;
    }
    char** newMap = createMap(maxRow * 2, maxCol * 2);

    for(int row=0; row<maxRow; row++){
        for(int col=0; col<maxCol; col++){
            newMap[row][col] = map[row][col];
            if (map[row][col] == TILE_PLAYER){
                continue;
            } else {
                newMap[row+maxRow][col] = map[row][col];
                newMap[row][col+maxCol] = map[row][col];
                newMap[row+maxRow][col+maxCol] = map[row][col];
            }
        }
    }
    int x = maxRow;
    deleteMap(map,maxRow);
    maxRow = x;
    maxRow *= 2;
    maxCol *= 2;

    return newMap;
}



/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    int status = 0;
    int r = nextRow;
    int c = nextCol;

    if(nextRow<0 || nextRow>= maxRow || nextCol<0 || 
    nextCol>=maxCol || map[nextRow][nextCol] == TILE_MONSTER || 
    map[nextRow][nextCol] == TILE_PILLAR || (player.treasure < 1 && map[r][c] == TILE_EXIT)){
        nextRow = player.row;
        nextCol = player.col;
        status = STATUS_STAY;
    } else{
        if (map[r][c] == TILE_TREASURE){    
            player.treasure += 1;
            status = STATUS_TREASURE;
        }else if (map[r][c] == TILE_AMULET){
            status = STATUS_AMULET;
        } else if (map[r][c] == TILE_DOOR){
            status = STATUS_LEAVE;
        } else if (map[r][c] == TILE_EXIT){
            if(player.treasure >= 1){
                status = STATUS_ESCAPE;
            }
        } else if (map[r][c] == TILE_OPEN){
            status = STATUS_MOVE;
        }     
    } 
    
    if (status != STATUS_STAY){
        map[player.row][player.col] = TILE_OPEN;
        map[r][c] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol; 
    }
    return status;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    //gpin up
    for(int i = player.row-1; i>-1; i--){
        if (map[i][player.col] == TILE_PILLAR)
            break;
        else if (map[i][player.col] == TILE_MONSTER) {
            map[i+1][player.col] = TILE_MONSTER;
            map[i][player.col] = TILE_OPEN;
        }
    }

    //down
    for(int i = player.row+1; i<maxRow; i++){
        if (map[i][player.col] == TILE_PILLAR)
            break;
        else if (map[i][player.col] == TILE_MONSTER) {
            map[i-1][player.col] = TILE_MONSTER;
            map[i][player.col] = TILE_OPEN;
            
        }
    }

    //to go right
    for(int i = player.col+1; i<maxCol; i++){
        if (map[player.row][i] == TILE_PILLAR)
            break;
        else if (map[player.row][i] == TILE_MONSTER) {
            map[player.row][i-1] = TILE_MONSTER;
            map[player.row][i] = TILE_OPEN;
        }
    }

    //left
    for(int i = player.col-1; i>-1; i--){
        if (map[player.row][i] == TILE_PILLAR)
            break;
        else if (map[player.row][i] == TILE_MONSTER) {
            map[player.row][i+1] = TILE_MONSTER;
            map[player.row][i] = TILE_OPEN;
            
        }
    }

    if(map[player.row][player.col] == TILE_MONSTER){
        return true; 
    }
    return false;
}
