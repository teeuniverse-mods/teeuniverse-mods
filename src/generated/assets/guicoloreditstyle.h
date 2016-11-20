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

#ifndef __CLIENT_ASSETS_GUICOLOREDITSTYLE__
#define __CLIENT_ASSETS_GUICOLOREDITSTYLE__

#include <shared/assets/asset.h>
#include <shared/assets/assetpath.h>

class CAsset_GuiColorEditStyle : public CAsset
{
public:
	static const int TypeId = 4;
	
	enum
	{
		NAME = CAsset::NAME,
		BUTTONSTYLEPATH,
		POPUPSTYLEPATH,
		RGBICONPATH,
		HSVICONPATH,
		SQUAREICONPATH,
		WHEELICONPATH,
	};
	
	class CTuaType : public CAsset::CTuaType
	{
	public:
		CAssetPath::CTuaType m_ButtonStylePath;
		CAssetPath::CTuaType m_PopupStylePath;
		CAssetPath::CTuaType m_RGBIconPath;
		CAssetPath::CTuaType m_HSVIconPath;
		CAssetPath::CTuaType m_SquareIconPath;
		CAssetPath::CTuaType m_WheelIconPath;
		static void Read(class CAssetsSaveLoadContext* pLoadingContext, const CTuaType& TuaType, CAsset_GuiColorEditStyle& SysType);
		static void Write(class CAssetsSaveLoadContext* pLoadingContext, const CAsset_GuiColorEditStyle& SysType, CTuaType& TuaType);
	};
	

private:
	CAssetPath m_ButtonStylePath;
	CAssetPath m_PopupStylePath;
	CAssetPath m_RGBIconPath;
	CAssetPath m_HSVIconPath;
	CAssetPath m_SquareIconPath;
	CAssetPath m_WheelIconPath;

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
	
	void copy(const CAsset_GuiColorEditStyle& Item)
	{
		CAsset::copy(Item);
		m_ButtonStylePath = Item.m_ButtonStylePath;
		m_PopupStylePath = Item.m_PopupStylePath;
		m_RGBIconPath = Item.m_RGBIconPath;
		m_HSVIconPath = Item.m_HSVIconPath;
		m_SquareIconPath = Item.m_SquareIconPath;
		m_WheelIconPath = Item.m_WheelIconPath;
	}
	
	void transfert(CAsset_GuiColorEditStyle& Item)
	{
		CAsset::transfert(Item);
		m_ButtonStylePath = Item.m_ButtonStylePath;
		m_PopupStylePath = Item.m_PopupStylePath;
		m_RGBIconPath = Item.m_RGBIconPath;
		m_HSVIconPath = Item.m_HSVIconPath;
		m_SquareIconPath = Item.m_SquareIconPath;
		m_WheelIconPath = Item.m_WheelIconPath;
	}
	
	inline CAssetPath GetButtonStylePath() const { return m_ButtonStylePath; }
	
	inline CAssetPath GetPopupStylePath() const { return m_PopupStylePath; }
	
	inline CAssetPath GetRGBIconPath() const { return m_RGBIconPath; }
	
	inline CAssetPath GetHSVIconPath() const { return m_HSVIconPath; }
	
	inline CAssetPath GetSquareIconPath() const { return m_SquareIconPath; }
	
	inline CAssetPath GetWheelIconPath() const { return m_WheelIconPath; }
	
	inline void SetButtonStylePath(const CAssetPath& Value) { m_ButtonStylePath = Value; }
	
	inline void SetPopupStylePath(const CAssetPath& Value) { m_PopupStylePath = Value; }
	
	inline void SetRGBIconPath(const CAssetPath& Value) { m_RGBIconPath = Value; }
	
	inline void SetHSVIconPath(const CAssetPath& Value) { m_HSVIconPath = Value; }
	
	inline void SetSquareIconPath(const CAssetPath& Value) { m_SquareIconPath = Value; }
	
	inline void SetWheelIconPath(const CAssetPath& Value) { m_WheelIconPath = Value; }
	
	void AssetPathOperation(const CAssetPath::COperation& Operation)
	{
		Operation.Apply(m_ButtonStylePath);
		Operation.Apply(m_PopupStylePath);
		Operation.Apply(m_RGBIconPath);
		Operation.Apply(m_HSVIconPath);
		Operation.Apply(m_SquareIconPath);
		Operation.Apply(m_WheelIconPath);
	}
	
};

#endif