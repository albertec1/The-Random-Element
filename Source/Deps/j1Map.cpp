#include "p2Defs.h"
#include "p2Log.h"
#include "j1Map.h"
#include "j1Window.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Collision.h"
#include "j1EntityManager.h"
#include "Pathfinding.h"

j1Map::j1Map() : j1Module()
{
	name.create("map");
}

j1Map::~j1Map()
{}

bool j1Map::Awake(pugi::xml_node& node)
{
	debug_metadata = false;
	debug_pathtiles = false;
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(node.child("folder").child_value());
	LOG("folder name: %s", folder.GetString());

	return ret;
}

bool j1Map::Load(const char* file_name)
{
	CleanUp();

	bool ret = true;

	p2SString tmp(folder.GetString());
	tmp += file_name;
	LOG("Map File Path: %s", tmp.GetString());

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	//Load general info -------------------------
	if ( ret == true )
		ret = LoadMap();

	//Load all tilesets info --------------------
	pugi::xml_node tileset_node;
	for (tileset_node = map_file.child("map").child("tileset"); tileset_node && ret; tileset_node = tileset_node.next_sibling("tileset"))
	{
		TilesetData* tileset_data = new TilesetData();

		if (ret == true)
		{
			ret = LoadTilesetDetails(tileset_node, tileset_data);
		}

		if (ret == true)
		{
			ret = LoadTilesetImage(tileset_node, tileset_data);
		}

		mapdata.tilesets.add(tileset_data);
	}

	//Load layer info ----------------------------
	pugi::xml_node layer;
	for (layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* lay = new MapLayer();

		ret = LoadLayer(layer, lay);

		if (ret == true)
			mapdata.layers.add(lay);
	}

	//Set special layers -------------------
	ret = SetCollisionLayout();
		
	if (ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
	}

	map_loaded = ret;

	return ret;
}

bool j1Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node map = map_file.child("map");
	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}

	else
	{
		mapdata.map_version =		map.attribute("version").as_float();
		mapdata.orientation =		map.attribute("orientation").as_string();
		mapdata.render_order =		map.attribute("renderorder").as_string();
		mapdata.map_width =		map.attribute("width").as_int();
		mapdata.map_height =		map.attribute("height").as_int();
		mapdata.tile_width =		map.attribute("tilewidth").as_int();
		mapdata.tile_height =		map.attribute("tileheight").as_int();
		mapdata.next_layer_id =	map.attribute("nextlayerid").as_int();
		mapdata.next_object_id =	map.attribute("nextobjectid").as_int();

		/*background color?*/
	}

	if (mapdata.orientation == "orthogonal")
	{
		mapdata.map_type = MAPTYPE_ORTHOGONAL;
	}
	else if (mapdata.orientation == "isometric")
	{
		mapdata.map_type = MAPTYPE_ISOMETRIC;
	}
	else if (mapdata.orientation == "staggered")
	{
		mapdata.map_type = MAPTYPE_STAGGERED;
	}
	else
	{
		mapdata.map_type = MAPTYPE_UNKNOWN;
	}

	//LOG map details---------
	if (App->allow_debug_log == true)
	{
		LOG("\n --------- MAP DETAILS ----------\n- map_version: %0.2f \n- orientation: %s \n- render_order: %s \n- map_width: %d \n- map_height: %d \n- tile_width: %d \n- tile_height: %d \n- next_layer_id: %d \n- next_object_id: %d",
			mapdata.map_version,
			mapdata.orientation.GetString(),
			mapdata.render_order.GetString(),
			mapdata.map_width,
			mapdata.map_height,
			mapdata.tile_width,
			mapdata.tile_height,
			mapdata.next_layer_id,
			mapdata.next_object_id);

	}
	return ret;
}

bool j1Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TilesetData* set)
{
	bool ret = true;

	set->name.create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if (offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	//LOG Tileset details----------
	if (App->allow_debug_log == true)
	{
		LOG("\n --------- TILESET DETAILS ----------\n- name: %s \n- firstgid: %d \n- tile_width: %d \n- tile_height: %d \n- margin: %d \n- spacing: %d",
			set->name.GetString(),
			set->firstgid,
			set->tile_width,
			set->tile_height,
			set->margin,
			set->spacing);
	}
	return ret;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TilesetData* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");
	if (image == NULL)
	{
		LOG("Error parsng tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.GetString(), image.attribute("source").as_string()));
		
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);

		set->tex_width = image.attribute("width").as_int();
		if (set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if (set->tex_height <= 0)
		{
			set->tex_height = h;
		}
	}

	set->num_tiles_width = set->tex_width / set->tile_width;
	set->num_tiles_height = set->tex_height / set->tile_height;
	
	//LOG Tileset Image details----------
	if (App->allow_debug_log == true)
	{
		LOG("\n --------- TILESET IMAGE DETAILS ----------\n- tex_width: %d \n- tex_height: %d \n- num_tiles_width: %d \n- num_tiles_height: %d",
			set->tex_width,
			set->tex_height,
			set->num_tiles_width,
			set->num_tiles_height);
	}
	return ret;
}

bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	layer->name =	node.attribute("name").as_string();
	layer->id =		node.attribute("id").as_int();
	layer->width =	node.attribute("width").as_int();
	layer->height =	node.attribute("height").as_int();
	LoadProperties(node, layer->properties);

	pugi::xml_node layer_data = node.child("data");
	
	if (layer_data == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'layer/data' tag.");
		ret = false;
		RELEASE(layer);
	}
	else
	{
		layer->data = new uint[layer->width * layer->height];
		memset(layer->data, 0, layer->width * layer->height);

		int i = 0;
		for (pugi::xml_node tile = layer_data.child("tile"); tile; tile = tile.next_sibling("tile"))
		{
			int gid = tile.attribute("gid").as_int(0);
			layer->data[i++] = gid;
		}
	}

	//LOG Layer details------------
	if (App->allow_debug_log == true)
	{
		LOG("\n --------- LAYER %d DETAILS ----------\n- name: %s \n- width: %d \n- height: %d",
			layer->id,
			layer->name.GetString(),
			layer->width,
			layer->height);
	}
	return ret;
}

bool j1Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	pugi::xml_node data = node.child("properties");

	if (data != NULL)
	{
		pugi::xml_node prop;

		for (prop = data.child("property"); prop; prop = prop.next_sibling("property"))
		{
			Properties::Property* p = new Properties::Property();

			p->name = prop.attribute("name").as_string();
			p->value = prop.attribute("value").as_int();

			properties.list.add(p);
		}
	}
	return ret;
}

bool j1Map::SetCollisionLayout()
{
	bool ret = false;

	p2List_item<MapLayer*>* current_layer = mapdata.layers.start;
	SDL_Rect tile_rect;
	tile_rect.w = mapdata.tile_width;
	tile_rect.h = mapdata.tile_height;

	for (current_layer; current_layer != nullptr; current_layer = current_layer->next)
	{
		if (current_layer->data->properties.Get("Navigation") == 1)
		{
			metadata = current_layer->data;
			App->coll->metadata = metadata;
			for (int y = 0; y < mapdata.map_height; ++y)
			{
				for (int x = 0; x < mapdata.map_width; ++x)
				{
					int tile_id = current_layer->data->Get(x, y);
					if (tile_id > 0)
					{
						TilesetData* tileset = GetTilesetFromTileId(tile_id);
						if (tileset != nullptr)
						{
							iPoint pos = MapToWorld(x, y);

							tile_rect.x = pos.x;
							tile_rect.y = pos.y;

							if (tile_id == WALL_ID || tile_id == 121)
								App->coll->AddCollider(tile_rect, COLLIDER_TYPE::WALL);

							else if (tile_id == PLATFORM_ID || tile_id == 122)
								App->coll->AddCollider(tile_rect, COLLIDER_TYPE::PLATFORM);

							else if (tile_id == BONUS_ID || tile_id == 125)
								App->coll->AddCollider(tile_rect, COLLIDER_TYPE::BONUS);
						}
					}
				}
			}
			ret = true;
		}
	}
	if (ret == false)
	{
		LOG("No layer with 'Navigation' attribute set to 1");
	}
	
	return ret;
}

//prepare width, height and a buffer with the walkable path tiles to create the walkability map.
bool j1Map::SetPathTiles(int* w, int* h, uchar** buffer)
{
	bool ret = false;

	p2List_item<MapLayer*>* current_layer = mapdata.layers.start;
	SDL_Rect tile_rect;
	tile_rect.w = mapdata.tile_width;
	tile_rect.h = mapdata.tile_height;

	for (current_layer; current_layer != nullptr; current_layer = current_layer->next)
	{
		if (current_layer->data->properties.Get("PathNodes") == 1)
		{
			uchar* map = new uchar[current_layer->data->width * current_layer->data->height];
			memset(map, 1, current_layer->data->width * current_layer->data->height);

			for (int y = 0; y < mapdata.map_height; ++y)
			{
				for (int x = 0; x < mapdata.map_width; ++x)
				{
					int i = (y * current_layer->data->width) + x;

					int tile_id = current_layer->data->Get(x, y);

					TilesetData* tileset = GetTilesetFromTileId(tile_id);
					if (tileset != nullptr)
					{
						if (tile_id - tileset->firstgid != 0)
							map[i] = (tile_id - tileset->firstgid) > 0 ? 1 : 0;
					}

				}
			}

			*buffer = map;
			*w = mapdata.map_width;
			*h = mapdata.map_height;
			ret = true;
			break;
		}
	}

	return ret;
}

SDL_Rect j1Map::MapCulling(iPoint size, int extra_x, int extra_y)
{
	SDL_Rect ret;
	iPoint cam = { App->render->camera.x, App->render->camera.y };
	iPoint end = cam;
	cam.x /= -App->win->GetScale();
	cam.y /= -App->win->GetScale();
	cam = WorldToMap(cam.x, cam.y);
	cam.x -= extra_x * App->win->GetScale();
	cam.y -= extra_y * App->win->GetScale();

	end.x /= -App->win->GetScale();
	end.y /= -App->win->GetScale();
	end.x += App->render->camera.w;
	end.y += App->render->camera.h;
	end = WorldToMap(end.x, end.y);
	end.x += extra_x * App->win->GetScale();
	end.y += extra_y * App->win->GetScale();

	if (cam.x < 0)
		cam.x = 0;
	else if (cam.x > size.x)
		cam.x = size.x;
	if (cam.y < 0)
		cam.y = 0;
	else if (cam.y > size.y)
		cam.y = size.y;
	if (end.x < 0)
		end.x = 0;
	else if (end.x > size.x)
		end.x = size.x;
	if (end.y < 0)
		end.y = 0;
	else if (end.y > size.y)
		end.y = size.y;

	ret = { cam.x, cam.y, end.x, end.y };

	return ret;
}

void j1Map::Draw()
{
	if (map_loaded == false)
		return;

	p2List_item<MapLayer*>* current_layer = mapdata.layers.start;
	int properties_count = current_layer->data->properties.list.count();

	SDL_Rect tile_rect;
	tile_rect.w = mapdata.tile_width;
	tile_rect.h = mapdata.tile_height;

	for (current_layer; current_layer != nullptr; current_layer = current_layer->next)
	{
		if (current_layer->data->properties.Get("Draw") == 1)
		{
			SDL_Rect cam = MapCulling({ current_layer->data->width, current_layer->data->height }, 10, 10);
			for (int y = cam.y; y < cam.h; y++)
				for (int x = cam.x; x < cam.w; x++)
				{
					iPoint tileCoords = MapToWorld(x, y);
					int tile_id = current_layer->data->Get(x, y);

					TilesetData* tileset = GetTilesetFromTileId(tile_id);
					if (tileset != nullptr)
					{
						SDL_Rect r = tileset->GetTileRect(tile_id);
						iPoint pos = MapToWorld(x, y);

						App->render->Blit(tileset->texture, pos.x, pos.y, &r);
					}
				}
		}	
		if (current_layer->data->properties.Get("PathNodes") == 1 && debug_pathtiles)
		{
			for (int y = 0; y < mapdata.map_height; ++y)
			{
				for (int x = 0; x < mapdata.map_width; ++x)
				{
					iPoint tileCoords = MapToWorld(x, y);
					int tile_id = current_layer->data->Get(x, y);

					TilesetData* tileset = GetTilesetFromTileId(tile_id);
					if (tileset != nullptr)
					{
						SDL_Rect r = tileset->GetTileRect(tile_id);
						iPoint pos = MapToWorld(x, y);

						App->render->Blit(tileset->texture, pos.x, pos.y, &r);
					}
				}
			}
		}
	}
	
	if (debug_metadata)
			App->coll->DebugDraw();
}

iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	if (mapdata.map_type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * mapdata.tile_width;
		ret.y = y * mapdata.tile_height;
	}
	else if (mapdata.map_type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (mapdata.tile_width * 0.5f);
		ret.y = (x + y) * (mapdata.tile_height * 0.5f);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}
	return ret;
}

iPoint j1Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	if (mapdata.map_type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / mapdata.tile_width;
		ret.y = y / mapdata.tile_height;
	}
	else if (mapdata.map_type == MAPTYPE_ISOMETRIC)
	{

		float half_width = mapdata.tile_width * 0.5f;
		float half_height = mapdata.tile_height * 0.5f;
		ret.x = int((x / half_width + y / half_height) / 2);
		ret.y = int((y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

SDL_Rect TilesetData::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

TilesetData* j1Map::GetTilesetFromTileId(int id) const
{
	p2List_item<TilesetData*>* actual_tileset = mapdata.tilesets.start;

	while (actual_tileset->next && id >= actual_tileset->next->data->firstgid)
	{
		actual_tileset = actual_tileset->next;
	}
	return actual_tileset->data;
}

int Properties::Get(const char* name, int default_value) const
{
	p2List_item<Property*>* item = list.start;

	while (item)
	{
		if (item->data->name == name)
			return item->data->value;
		item = item->next;
	}

	return default_value;
}

bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// Remove all tilesets
	p2List_item<TilesetData*>* item;
	item = mapdata.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	mapdata.tilesets.clear();

	// Remove all layers
	p2List_item<MapLayer*>* item2;
	item2 = mapdata.layers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	mapdata.layers.clear();

	// Clean up the pugui tree
	map_file.reset();

	//Clean colliders
	App->coll->deleteAll();

	return true;
}


