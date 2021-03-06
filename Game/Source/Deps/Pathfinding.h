#ifndef __j1PATHFINDING_H__
#define __j1PATHFINDING_H__

#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "p2List.h"
#include "j1Entity.h"

#define DEFAULT_PATH_LENGTH 50
#define INVALID_WALK_CODE 255

// --------------------------------------------------
// Recommended reading:
// Intro: http://www.raywenderlich.com/4946/introduction-to-a-pathfinding
// Details: http://theory.stanford.edu/~amitp/GameProgramming/
// --------------------------------------------------

class Pathfinding : public j1Module
{
public:

	Pathfinding();

	// Destructor
	~Pathfinding();

	// Debug update
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	// Sets up the walkability map
	void SetMap(uint width, uint height, uchar* data);

	// Main function to request a path from A to B
	int CreatePath(const iPoint& origin, const iPoint& destination, ENTITY_TYPE constraint);

	// To request all tiles involved in the last generated path
	const p2DynArray<iPoint>* GetLastPath() const;
	// To request all tiles involved in the last generated path and copy them into a p2list
	void GetLastPath(p2List<iPoint>*);

	// Utility: return true if pos is inside the map boundaries
	bool CheckBoundaries(const iPoint& pos) const;

	// Utility: returns true is the tile is walkable
	bool IsWalkable(const iPoint& pos) const;

	// Utility: return the walkability value of a tile
	uchar GetTileAt(const iPoint& pos) const;

	void CopyPathList(p2List<iPoint>* given_list);
public:
	bool debug_pathList = false;

private:

	// size of the map
	uint width;
	uint height;
	// all map walkability values;
	uchar* map;
	// we store the created path here
	p2DynArray<iPoint> last_path;

	p2List<iPoint> path_list;
};

// forward declaration
struct PathList;

// ---------------------------------------------------------------------
// Pathnode: Helper struct to represent a node in the path creation
// ---------------------------------------------------------------------
struct PathNode
{
	// Convenient constructors
	PathNode();
	PathNode(int g, int h, const iPoint& pos, const PathNode* parent);
	PathNode(const PathNode& node);

	// Fills a list (PathList) of all valid adjacent pathnodes
	uint FindWalkableAdjacents(PathList& list_to_fill, ENTITY_TYPE constraint) const;
	// Calculates this tile score
	int Score() const;
	// Calculate the F for a specific destination tile
	int CalculateF(const iPoint& destination);

	// -----------
	int g;
	int h;
	iPoint pos;
	const PathNode* parent; // needed to reconstruct the path in the end
};

// ---------------------------------------------------------------------
// Helper struct to include a list of path node
// ---------------------------------------------------------------------
struct PathList
{
	// Looks for a node in this list and returns its list node or NULL
	const p2List_item<PathNode>* Find(const iPoint& point) const;

	// Returns the Pathnode with lowest score in this list or NULL if empty
	p2List_item<PathNode>* GetNodeLowestScore() const;

	// The list itself, note they are not pointers!
	p2List<PathNode> list;
};



#endif // __j1PATHFINDING_H__
