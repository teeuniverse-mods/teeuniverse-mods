/*
 * Copyright (C) 2016 necropotame (necropotame@gmail.com)
 * 
 * This file is part of TeeUniverses.
 * 
 * TeeUniverses is free software: you can redistribute it and/or  modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * TeeUniverses is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with TeeUniverses.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * THIS FILE HAS BEEN GENERATED BY A SCRIPT.
 * DO NOT EDIT MANUALLY!
 *
 * Please use the script "scripts/assets/assets.py" to regenerate it.
 *
 * Why this file is generated by a script?
 * Because there is more than 10 files that follow the same format.
 * In addition, each time a new member is added, enums, getter, setters,
 * copy/transfert functions and storage structure must be updated.
 * It's too much to avoid mistakes.
 */

#ifndef __CLIENT_ASSETS_MAPZONETILES__
#define __CLIENT_ASSETS_MAPZONETILES__

#include <shared/assets/asset.h>
#include <shared/tl/array2d.h>
#include <shared/assets/assetpath.h>

class CAsset_MapZoneTiles : public CAsset
{
public:
	static const int TypeId = 18;
	
	enum
	{
		TYPE_TILE,
	};
	
	static inline CSubPath SubPath_Tile(int Id0, int Id1) { return CSubPath(TYPE_TILE, Id0, Id1, 0); }
	
	enum
	{
		NAME = CAsset::NAME,
		ZONETYPEPATH,
		TILE_WIDTH,
		TILE_HEIGHT,
		TILE_PTR,
		TILE_ARRAY,
		TILE_INDEX,
		TILE,
	};
	
	class CTile
	{
	public:
		class CTuaType
		{
		public:
			tua_uint8 m_Index;
			static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType& TuaType, CAsset_MapZoneTiles::CTile& SysType);
			static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapZoneTiles::CTile& SysType, CTuaType& TuaType);
		};
		
	
	private:
		uint8 m_Index;
	
	public:
		CTile();
		void copy(const CAsset_MapZoneTiles::CTile& Item)
		{
			m_Index = Item.m_Index;
		}
		
		void transfert(CAsset_MapZoneTiles::CTile& Item)
		{
			m_Index = Item.m_Index;
		}
		
		inline uint8 GetIndex() const { return m_Index; }
		
		inline void SetIndex(uint8 Value) { m_Index = Value; }
		
		void AssetPathOperation(const CAssetPath::COperation& Operation)
		{
		}
		
	};
	class CTuaType : public CAsset::CTuaType
	{
	public:
		CAssetPath::CTuaType m_ZoneTypePath;
		CTuaArray2d m_Tile;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType& TuaType, CAsset_MapZoneTiles& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_MapZoneTiles& SysType, CTuaType& TuaType);
	};
	

private:
	CAssetPath m_ZoneTypePath;
	array2d< CTile, allocator_copy<CTile> > m_Tile;

public:
	template<typename T>
	T GetValue(int ValueType, const CSubPath& SubPath, T DefaultValue) const
	{
		return CAsset::GetValue<T>(ValueType, SubPath, DefaultValue);
	}
	
	template<typename T>
	bool SetValue(int ValueType, const CSubPath& SubPath, T Value)
	{
		return CAsset::SetValue<T>(ValueType, SubPath, Value);
	}
	
	int AddSubItem(int Type, const CSubPath& SubPath);
	
	void copy(const CAsset_MapZoneTiles& Item)
	{
		CAsset::copy(Item);
		m_ZoneTypePath = Item.m_ZoneTypePath;
		m_Tile.copy(Item.m_Tile);
	}
	
	void transfert(CAsset_MapZoneTiles& Item)
	{
		CAsset::transfert(Item);
		m_ZoneTypePath = Item.m_ZoneTypePath;
		m_Tile.transfert(Item.m_Tile);
	}
	
	inline CAssetPath GetZoneTypePath() const { return m_ZoneTypePath; }
	
	inline int GetTileWidth() const { return m_Tile.get_width(); }
	
	inline int GetTileHeight() const { return m_Tile.get_height(); }
	
	inline const CAsset_MapZoneTiles::CTile* GetTilePtr() const { return m_Tile.base_ptr(); }
	
	inline const array2d< CTile, allocator_copy<CTile> >& GetTileArray() const { return m_Tile; }
	inline array2d< CTile, allocator_copy<CTile> >& GetTileArray() { return m_Tile; }
	
	inline const CAsset_MapZoneTiles::CTile& GetTile(const CSubPath& SubPath) const { return m_Tile.get_clamp(SubPath.GetId(), SubPath.GetId2()); }
	
	inline uint8 GetTileIndex(const CSubPath& SubPath) const { return m_Tile.get_clamp(SubPath.GetId(), SubPath.GetId2()).GetIndex(); }
	
	inline void SetZoneTypePath(const CAssetPath& Value) { m_ZoneTypePath = Value; }
	
	inline void SetTileWidth(int Value) { m_Tile.resize_width(max(Value, 1)); }
	
	inline void SetTileHeight(int Value) { m_Tile.resize_height(max(Value, 1)); }
	
	inline void SetTile(const CSubPath& SubPath, const CAsset_MapZoneTiles::CTile& Value) { m_Tile.set_clamp(SubPath.GetId(), SubPath.GetId2(), Value); }
	
	inline void SetTileIndex(const CSubPath& SubPath, uint8 Value) { m_Tile.get_clamp(SubPath.GetId(), SubPath.GetId2()).SetIndex(Value); }
	
	void AssetPathOperation(const CAssetPath::COperation& Operation)
	{
		Operation.Apply(m_ZoneTypePath);
		for(int i=0; i<m_Tile.get_linear_size(); i++)
		{
			m_Tile.linear_get_clamp(i).AssetPathOperation(Operation);
		}
	}
	
};

#endif