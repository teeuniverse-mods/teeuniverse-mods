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

#ifndef __CLIENT_MAPRENDERER__
#define __CLIENT_MAPRENDERER__

#include <shared/components/assetsmanager.h>
#include <client/gui/rect.h>

class CMapRenderer : public CClientKernel::CGuest
{
public:
	vec2 m_GroupPos;
	vec2 m_GroupHardParallax;
	
	gui::CRect m_Canvas;
	vec2 m_ScreenPos;
	vec2 m_CameraPos;
	vec2 m_GroupCameraPos;
	float m_CameraZoom;
	float m_Time;
	float m_LocalTime;
	
public:	
	CMapRenderer(CClientKernel* pKernel);
	
	inline void SetTime(float Time) { m_Time = Time; }
	inline void SetLocalTime(float Time) { m_LocalTime = Time; }
	
	inline float GetTime() const { return m_Time; }
	inline float GetLocalTime() const { return m_LocalTime; }
	
	void SetCanvas(const gui::CRect& Canvas, vec2 ScreenPos);
	void SetCamera(vec2 CameraPos, float CameraZoom);
	void SetGroup(CAssetPath GroupPath);
	void UnsetGroup();
	
	inline const gui::CRect& GetCanvas() const { return m_Canvas; }
	
	vec2 MapPosToScreenPos(vec2 MapPos) const;
	vec2 MapPosToTilePos(vec2 MapPos) const;
	vec2 ScreenPosToMapPos(vec2 MapPos) const;
	vec2 ScreenPosToTilePos(vec2 MapPos) const;
	vec2 TilePosToMapPos(vec2 MapPos) const;
	vec2 TilePosToScreenPos(vec2 MapPos) const;
	
	void RenderGrid(int Width, int Height, float Scale);
	void RenderGrid_LayerTiles(CAssetPath LayerPath);
	void RenderTiles_Image(const array2d<CAsset_MapLayerTiles::CTile, allocator_copy<CAsset_MapLayerTiles::CTile> >& Tiles, vec2 Pos, CAssetPath ImagePath, vec4 Color);
	void RenderTiles_Zone(CAssetPath ZoneTypePath, const array2d<CAsset_MapLayerTiles::CTile, allocator_copy<CAsset_MapLayerTiles::CTile> >& Tiles, vec2 Pos, CAssetPath ZoneTexture);
	void RenderTiles_Zone(CAssetPath ZoneTypePath, const array2d<CAsset_MapZoneTiles::CTile, allocator_copy<CAsset_MapZoneTiles::CTile> >& Tiles, vec2 Pos, CAssetPath ZoneTexture);
	void RenderQuads(const CAsset_MapLayerQuads::CQuad* pQuads, int NbQuads, vec2 Pos, CAssetPath ImagePath, vec4 Color);
	void RenderQuads_Mesh(const CAsset_MapLayerQuads::CQuad* pQuads, int NbQuads);
	
	void RenderGroup(CAssetPath GroupPath);
	void RenderMap(CAssetPath MapPath);
	
	void RenderMap_Zones(CAssetPath MapPath, CAssetPath ZoneTexture);
};

#endif