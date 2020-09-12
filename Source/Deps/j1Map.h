#pragma once

#include "j1Module.h"
#include "j1App.h"
#include "p2List.h"
#include "p2Point.h"
#include "PugiXml/src/pugixml.hpp"
#include "SDL_image/include/SDL_image.h"

#define WALL_ID			61 	 //Green
#define PLATFORM_ID		62	 //Blue
#define ENEMY_ID		64	 //Red
#define BONUS_ID		65	 //Purple
#define PLAYER_ID		67	 //Yellow

// Generic structure to hold properties.
// Our custom properties should have one method to ask for the value of a custom property
// ----------------------------------------------------
struct Properties
{

	struct Property
	{
		p2SString name;
		int value;
	};

	~Properties()
	{
		p2List_item<Property*>* item;
		item = list.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}

		list.clear();
	}

	int Get(const char* name, int default_value = 0) const;

	p2List<Property*>	list;

};

struct MapLayer
{
	p2SString			name;
	int					id;
	int					width;
	int					height;
	uint*				data;
	Properties			properties;

	MapLayer() : data(NULL) 
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		return data[(y * width) + x];
	}

	inline uint GetLayerPositon(int x, int y) const
	{
		return (y * width) + x;
	}
};

struct TilesetData
{
	SDL_Rect GetTileRect(int id) const;

	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

struct MapData
{
	float					map_version;
	p2SString				orientation;
	p2SString				render_order;
	int						map_width;
	int						map_height;
	int						tile_width;
	int						tile_height;
	int						next_layer_id;
	int						next_object_id;
	MapTypes				map_type;
	p2List<TilesetData*>	tilesets;
	p2List<MapLayer*>		layers;
};

class j1Map : public j1Module
{
public:

	j1Map();
	virtual ~j1Map();

	bool Awake(pugi::xml_node& node);
	void Draw();
	bool CleanUp();

	bool Load(const char* path);

	iPoint MapToWorld(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;
private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TilesetData* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TilesetData* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadProperties(pugi::xml_node& node, Properties& properties);
	bool SetCollisionLayout(pugi::xml_node& node);

	TilesetData* GetTilesetFromTileId(int id) const;

public:

	MapData		data;
	MapLayer*	metadata;
	uint		win_width = 0;
	uint		win_height = 0;
	bool		drawLayer;
	bool		debug_metadata;


private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};
