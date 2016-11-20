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

#include <editor/gui/assetsinspector.h>
#include <editor/components/gui.h>
#include <shared/components/assetsmanager.h>
#include <client/gui/text-edit.h>
#include <client/gui/integer-edit.h>
#include <client/gui/float-edit.h>
#include <client/gui/color-edit.h>
#include <client/gui/popup.h>
#include <client/gui/expand.h>
#include <shared/components/localization.h>

/* ASSETS INSPECTOR ***************************************************/

CAssetsInspector::CAssetsInspector(CGuiEditor* pAssetsEditor) :
	gui::CTabs(pAssetsEditor),
	m_pAssetsEditor(pAssetsEditor)
{
	for(int i=0; i<NUM_TABS; i++)
		m_pTabs[TAB_IMAGE_ASSET] = 0;
	
	//TAG_NEW_ASSET
	m_pTabs[TAB_PACKAGE] = CreateTab_Package();
	m_pTabs[TAB_GENERIC_ASSET] = CreateTab_Generic_Asset();
	m_pTabs[TAB_GUIRECTSTYLE_ASSET] = CreateTab_GuiRectStyle_Asset();
	m_pTabs[TAB_GUILINESTYLE_ASSET] = CreateTab_GuiLineStyle_Asset();
	m_pTabs[TAB_GUIBOXSTYLE_ASSET] = CreateTab_GuiBoxStyle_Asset();
	m_pTabs[TAB_GUILABELSTYLE_ASSET] = CreateTab_GuiLabelStyle_Asset();
	m_pTabs[TAB_GUIBUTTONSTYLE_ASSET] = CreateTab_GuiButtonStyle_Asset();
	m_pTabs[TAB_GUIINTEDITSTYLE_ASSET] = CreateTab_GuiIntEditStyle_Asset();
	m_pTabs[TAB_GUITOGGLESTYLE_ASSET] = CreateTab_GuiToggleStyle_Asset();
	m_pTabs[TAB_GUISLIDERSTYLE_ASSET] = CreateTab_GuiSliderStyle_Asset();
	m_pTabs[TAB_GUISCROLLBARSTYLE_ASSET] = CreateTab_GuiScrollbarStyle_Asset();
	m_pTabs[TAB_GUITABSSTYLE_ASSET] = CreateTab_GuiTabsStyle_Asset();
	m_pTabs[TAB_IMAGE_ASSET] = CreateTab_Image_Asset();
	m_pTabs[TAB_MAP_ASSET] = CreateTab_Map_Asset();
	m_pTabs[TAB_MAPGROUP_ASSET] = CreateTab_MapGroup_Asset();
	m_pTabs[TAB_MAPLAYERTILES_ASSET] = CreateTab_MapLayerTiles_Asset();
	m_pTabs[TAB_MAPLAYERQUADS_ASSET] = CreateTab_MapLayerQuads_Asset();
	m_pTabs[TAB_MAPZONETILES_ASSET] = CreateTab_MapZoneTiles_Asset();
	m_pTabs[TAB_IMAGE_ASSET] = CreateTab_Image_Asset();
	m_pTabs[TAB_SPRITE_ASSET] = CreateTab_Sprite_Asset();
}

void CAssetsInspector::Update(bool ParentEnabled)
{
	for(int i=0; i<NUM_TABS; i++)
		m_pTabs[i]->Disable();
	
	if(AssetsManager()->GetAssetState(AssetsEditor()->GetEditedAssetPath()))
	{
		Enable();
		
		//TAG_NEW_ASSET
		switch(AssetsEditor()->GetEditedAssetPath().GetType())
		{
			case CAsset_GuiRectStyle::TypeId:
				m_pTabs[TAB_GUIRECTSTYLE_ASSET]->Enable();
				break;
			case CAsset_GuiLineStyle::TypeId:
				m_pTabs[TAB_GUILINESTYLE_ASSET]->Enable();
				break;
			case CAsset_GuiBoxStyle::TypeId:
				m_pTabs[TAB_GUIBOXSTYLE_ASSET]->Enable();
				break;
			case CAsset_GuiLabelStyle::TypeId:
				m_pTabs[TAB_GUILABELSTYLE_ASSET]->Enable();
				break;
			case CAsset_GuiButtonStyle::TypeId:
				m_pTabs[TAB_GUIBUTTONSTYLE_ASSET]->Enable();
				break;
			case CAsset_GuiIntEditStyle::TypeId:
				m_pTabs[TAB_GUIINTEDITSTYLE_ASSET]->Enable();
				break;
			case CAsset_GuiToggleStyle::TypeId:
				m_pTabs[TAB_GUITOGGLESTYLE_ASSET]->Enable();
				break;
			case CAsset_GuiSliderStyle::TypeId:
				m_pTabs[TAB_GUISLIDERSTYLE_ASSET]->Enable();
				break;
			case CAsset_GuiScrollbarStyle::TypeId:
				m_pTabs[TAB_GUISCROLLBARSTYLE_ASSET]->Enable();
				break;
			case CAsset_GuiTabsStyle::TypeId:
				m_pTabs[TAB_GUITABSSTYLE_ASSET]->Enable();
				break;
			case CAsset_Image::TypeId:
				m_pTabs[TAB_IMAGE_ASSET]->Enable();
				break;
			case CAsset_Map::TypeId:
				m_pTabs[TAB_MAP_ASSET]->Enable();
				break;
			case CAsset_MapGroup::TypeId:
				m_pTabs[TAB_MAPGROUP_ASSET]->Enable();
				break;
			case CAsset_MapLayerTiles::TypeId:
				m_pTabs[TAB_MAPLAYERTILES_ASSET]->Enable();
				break;
			case CAsset_MapLayerQuads::TypeId:
				m_pTabs[TAB_MAPLAYERQUADS_ASSET]->Enable();
				break;
			case CAsset_MapZoneTiles::TypeId:
				m_pTabs[TAB_MAPZONETILES_ASSET]->Enable();
				break;
			case CAsset_Sprite::TypeId:
				m_pTabs[TAB_SPRITE_ASSET]->Enable();
				break;
			default:
				m_pTabs[TAB_GENERIC_ASSET]->Enable();
				break;
		}
		
		gui::CTabs::Update(ParentEnabled);
	}
	else if(AssetsManager()->IsValidPackage(AssetsEditor()->GetEditedPackageId()))
	{
		Enable();
		
		m_pTabs[TAB_PACKAGE]->Enable();
		
		gui::CTabs::Update(ParentEnabled);
	}
	else
	{
		Disable();
	
		return;
	}
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_Generic_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	
	pTab->Disable();
	AddTab(pTab, "Asset", AssetsEditor()->m_Path_Sprite_IconAsset);
	
	AddField_AssetProperties(pTab);
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_Image_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Image", AssetsEditor()->m_Path_Sprite_IconImage);
	
	AddField_AssetProperties(pTab);
	
	AddField_Integer_NoEdit(pTab, CAsset_Image::DATA_WIDTH, "Width");
	AddField_Integer_NoEdit(pTab, CAsset_Image::DATA_HEIGHT, "Height");
	AddField_Integer(pTab, CAsset_Image::TEXELSIZE, "Texel size");
	AddField_Integer(pTab, CAsset_Image::GRIDWIDTH, "Grid width");
	AddField_Integer(pTab, CAsset_Image::GRIDHEIGHT, "Grid height");
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_Sprite_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Sprite", AssetsEditor()->m_Path_Sprite_IconSprite);
	
	AddField_AssetProperties(pTab);
	
	AddField_Asset(pTab, CAsset_Sprite::IMAGEPATH, CAsset_Image::TypeId, "Image");
	AddField_Integer(pTab, CAsset_Sprite::X, "X");
	AddField_Integer(pTab, CAsset_Sprite::Y, "Y");
	AddField_Integer(pTab, CAsset_Sprite::WIDTH, "Width");
	AddField_Integer(pTab, CAsset_Sprite::HEIGHT, "Height");
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_Map_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Map", AssetsEditor()->m_Path_Sprite_IconMap);
	
	AddField_AssetProperties(pTab);
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_MapGroup_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Map Group", AssetsEditor()->m_Path_Sprite_IconFolder);
	
	AddField_AssetProperties(pTab);
	
	AddField_Vec2(pTab, CAsset_MapGroup::POSITION_X, CAsset_MapGroup::POSITION_Y, "Position");	
	AddField_Vec2(pTab, CAsset_MapGroup::HARDPARALLAX_X, CAsset_MapGroup::HARDPARALLAX_Y, "Parallax");	
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_MapLayerTiles_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Map Layer Tiles", AssetsEditor()->m_Path_Sprite_IconTiles);
	
	AddField_AssetProperties(pTab);
		
	AddField_Integer(pTab, CAsset_MapLayerTiles::TILE_WIDTH, "Width");	
	AddField_Integer(pTab, CAsset_MapLayerTiles::TILE_HEIGHT, "Height");	
	AddField_Asset(pTab, CAsset_MapLayerTiles::IMAGEPATH, CAsset_Image::TypeId, "Image");
	AddField_Color(pTab, CAsset_MapLayerTiles::COLOR, "Color");	
	
	return pTab;
}

class CSubItemEditor : public gui::CVListLayout
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_SubPathType;
	
public:
	CSubItemEditor(CGuiEditor* pAssetsEditor, int SubPathType) :
		gui::CVListLayout(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_SubPathType(SubPathType)
	{
		
	}
	
	virtual void Update(bool ParentEnabled)
	{
		if(ParentEnabled)
		{
			if(m_pAssetsEditor->GetEditedSubPath().GetType() == m_SubPathType)
				Enable();
			else
				Disable();
		}
		
		gui::CVListLayout::Update(ParentEnabled);
	}
};

class CSubItem : public gui::CButton
{
protected:
	CGuiEditor* m_pAssetsEditor;
	CSubPath m_SubPath;
	
protected:
	virtual void MouseClickAction()
	{
		m_pAssetsEditor->SetEditedAsset(m_pAssetsEditor->GetEditedAssetPath(), m_SubPath);
	}

public:
	CSubItem(CGuiEditor* pAssetsEditor, CSubPath SubPath, const char* pName, CAssetPath IconPath) :
		gui::CButton(pAssetsEditor, pName, IconPath),
		m_pAssetsEditor(pAssetsEditor),
		m_SubPath(SubPath)
	{
		SetButtonStyle(m_pAssetsEditor->m_Path_Button_ListItem);
	}
	
	virtual void Update(bool ParentEnabled)
	{
		if(m_pAssetsEditor->GetEditedSubPath() == m_SubPath)
			SetButtonStyle(m_pAssetsEditor->m_Path_Button_ListItemHL);
		else
			SetButtonStyle(m_pAssetsEditor->m_Path_Button_ListItem);
		
		gui::CButton::Update(ParentEnabled);
	}
};

class CSubItemList_MapLayerQuads : public gui::CVScrollLayout
{
protected:
	CAssetPath m_AssetPath;
	CGuiEditor* m_pAssetsEditor;
	bool m_UpdateNeeded;
	
public:
	CSubItemList_MapLayerQuads(CGuiEditor* pAssetsEditor) :
		gui::CVScrollLayout(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_UpdateNeeded(true)
	{
		SetBoxStyle(m_pAssetsEditor->m_Path_Box_SubList);
	}
	
	virtual void Update(bool ParentEnabled)
	{
		if(ParentEnabled && IsEnabled())
		{
			if(m_pAssetsEditor->GetEditedAssetPath().GetType() == CAsset_MapLayerQuads::TypeId && m_AssetPath != m_pAssetsEditor->GetEditedAssetPath())
			{
				m_AssetPath = m_pAssetsEditor->GetEditedAssetPath();
				m_UpdateNeeded = true;
			}
			
			if(m_UpdateNeeded)
			{
				Clear();
				char aBuf[128];
					
				const CAsset_MapLayerQuads* pLayer = AssetsManager()->GetAsset<CAsset_MapLayerQuads>(m_pAssetsEditor->GetEditedAssetPath());
				if(pLayer)
				{
					CAsset_MapLayerQuads::CIteratorQuad Iter;
					int Counter = 1;
					for(Iter = pLayer->BeginQuad(); Iter != pLayer->EndQuad(); ++Iter)
					{
						str_format(aBuf, sizeof(aBuf), "Quad %d", Counter);
						Add(new CSubItem(m_pAssetsEditor, *Iter, aBuf, m_pAssetsEditor->m_Path_Sprite_IconQuad), false);
						Counter++;
					}
					
					m_UpdateNeeded = false;
				}
			}
		}
		
		gui::CVScrollLayout::Update(ParentEnabled);
	}
};

gui::CVScrollLayout* CAssetsInspector::CreateTab_MapLayerQuads_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Map Layer Quads", AssetsEditor()->m_Path_Sprite_IconQuad);
	
	AddField_AssetProperties(pTab);
	
	AddField_Asset(pTab, CAsset_MapLayerQuads::IMAGEPATH, CAsset_Image::TypeId, "Image");
	AddField_Integer_NoEdit(pTab, CAsset_MapLayerQuads::QUAD_ARRAYSIZE, "Number of quads");
	
	pTab->Add(new CSubItemList_MapLayerQuads(AssetsEditor()), true);
	
	gui::CVListLayout* pQuadEditor = new CSubItemEditor(AssetsEditor(), CAsset_MapLayerQuads::TYPE_QUAD);
	pTab->Add(pQuadEditor);
	
	AddField_Vec2(pQuadEditor, CAsset_MapLayerQuads::QUAD_PIVOT_X, CAsset_MapLayerQuads::QUAD_PIVOT_Y, "Position");
	AddField_Vec2(pQuadEditor, CAsset_MapLayerQuads::QUAD_SIZE_X, CAsset_MapLayerQuads::QUAD_SIZE_Y, "Size");
	AddField_Angle(pQuadEditor, CAsset_MapLayerQuads::QUAD_ANGLE, "Angle");
	AddField_Asset(pQuadEditor, CAsset_MapLayerQuads::QUAD_ANIMATIONPATH, CAsset_SkeletonAnimation::TypeId, "Animation");
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_MapZoneTiles_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Map Zone Tiles", AssetsEditor()->m_Path_Sprite_IconTiles);
	
	AddField_AssetProperties(pTab);
		
	AddField_Integer(pTab, CAsset_MapZoneTiles::TILE_WIDTH, "Width");	
	AddField_Integer(pTab, CAsset_MapZoneTiles::TILE_HEIGHT, "Height");
	AddField_Asset(pTab, CAsset_MapZoneTiles::ZONETYPEPATH, CAsset_ZoneType::TypeId, "Zone type");
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_GuiRectStyle_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Rectangle Style", AssetsEditor()->m_Path_Sprite_IconGuiRect);
	
	AddField_AssetProperties(pTab);
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_GuiLineStyle_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Line Style", AssetsEditor()->m_Path_Sprite_IconGuiLine);
	
	//~ AddField_Asset(pTab, CAsset_GuiLineStyle::RECTPATH, CAsset_GuiRectStyle::TypeId, "Rectangle");
	
	AddField_AssetProperties(pTab);
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_GuiBoxStyle_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Box Style", AssetsEditor()->m_Path_Sprite_IconGuiBox);
	
	AddField_AssetProperties(pTab);
	
	AddField_Asset(pTab, CAsset_GuiBoxStyle::RECTPATH, CAsset_GuiRectStyle::TypeId, "Rectangle");
	AddField_Integer(pTab, CAsset_GuiBoxStyle::MINWIDTH, "Width");
	AddField_Integer(pTab, CAsset_GuiBoxStyle::MINHEIGHT, "Height");
	AddField_Integer(pTab, CAsset_GuiBoxStyle::MARGIN, "Margin");
	AddField_Integer(pTab, CAsset_GuiBoxStyle::PADDING, "Padding");
	AddField_Integer(pTab, CAsset_GuiBoxStyle::SPACING, "Spacing");
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_GuiLabelStyle_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Label Style", AssetsEditor()->m_Path_Sprite_IconGuiLabel);
	
	AddField_AssetProperties(pTab);
	
	AddField_Asset(pTab, CAsset_GuiLabelStyle::RECTPATH, CAsset_GuiRectStyle::TypeId, "Rectangle");
	AddField_Integer(pTab, CAsset_GuiLabelStyle::MINWIDTH, "Width");
	AddField_Integer(pTab, CAsset_GuiLabelStyle::MINHEIGHT, "Height");
	AddField_Integer(pTab, CAsset_GuiLabelStyle::MARGIN, "Margin");
	AddField_Integer(pTab, CAsset_GuiLabelStyle::PADDING, "Padding");
	AddField_Integer(pTab, CAsset_GuiLabelStyle::SPACING, "Spacing");
	AddField_Integer(pTab, CAsset_GuiLabelStyle::FONTSIZE, "Font Size");
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_GuiButtonStyle_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Button Style", AssetsEditor()->m_Path_Sprite_IconGuiButton);
	
	AddField_AssetProperties(pTab);
	
	AddField_Asset(pTab, CAsset_GuiButtonStyle::IDLESTYLEPATH, CAsset_GuiLabelStyle::TypeId, "Idle Style");
	AddField_Asset(pTab, CAsset_GuiButtonStyle::MOUSEOVERSTYLEPATH, CAsset_GuiLabelStyle::TypeId, "Mouseover Style");
	AddField_Asset(pTab, CAsset_GuiButtonStyle::FOCUSSTYLEPATH, CAsset_GuiLabelStyle::TypeId, "Focus Style");
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_GuiIntEditStyle_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Integer Edit Style", AssetsEditor()->m_Path_Sprite_IconGuiIntEdit);
	
	AddField_AssetProperties(pTab);
	
	AddField_Asset(pTab, CAsset_GuiIntEditStyle::INCREASEBUTTONSTYLEPATH, CAsset_GuiButtonStyle::TypeId, "Increase Button");
	AddField_Asset(pTab, CAsset_GuiIntEditStyle::DECREASEBUTTONSTYLEPATH, CAsset_GuiButtonStyle::TypeId, "Decrease Button");
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_GuiToggleStyle_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Toggle Style", AssetsEditor()->m_Path_Sprite_IconGuiToggle);
	
	AddField_AssetProperties(pTab);
	
	AddField_Asset(pTab, CAsset_GuiToggleStyle::IDLETRUESTYLEPATH, CAsset_GuiLabelStyle::TypeId, "Idle Style (true)");
	AddField_Asset(pTab, CAsset_GuiToggleStyle::MOUSEOVERTRUESTYLEPATH, CAsset_GuiLabelStyle::TypeId, "Mouseover Style (true)");
	AddField_Asset(pTab, CAsset_GuiToggleStyle::IDLEFALSESTYLEPATH, CAsset_GuiLabelStyle::TypeId, "Idle Style (false)");
	AddField_Asset(pTab, CAsset_GuiToggleStyle::MOUSEOVERFALSESTYLEPATH, CAsset_GuiLabelStyle::TypeId, "Mouseover Style (false)");
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_GuiSliderStyle_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Slider Style", AssetsEditor()->m_Path_Sprite_IconGuiSlider);
	
	AddField_AssetProperties(pTab);
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_GuiScrollbarStyle_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Scrollbar Style", AssetsEditor()->m_Path_Sprite_IconGuiScrollbar);
	
	AddField_AssetProperties(pTab);
	
	return pTab;
}

gui::CVScrollLayout* CAssetsInspector::CreateTab_GuiTabsStyle_Asset()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	pTab->Disable();
	AddTab(pTab, "Tabs Style", AssetsEditor()->m_Path_Sprite_IconGuiTabs);
	
	AddField_AssetProperties(pTab);
	
	return pTab;
}

void CAssetsInspector::AddField(gui::CVListLayout* pList, gui::CWidget* pWidget, const char* pLabelText)
{
	if(pLabelText)
	{
		gui::CHListLayout* pLayout = new gui::CHListLayout(Context());
		pList->Add(pLayout, false);
		
		gui::CLabel* pLabel = new gui::CLabel(Context(), pLabelText);
		pLayout->Add(pLabel, true);
		
		pLayout->Add(pWidget, true);
	}
	else
	{
		pList->Add(pWidget, false);
	}
}

void CAssetsInspector::AddField_AssetProperties(gui::CVScrollLayout* pTab)
{
	AddField_Text(pTab, CAsset::NAME, "Name");
	
	pTab->AddSeparator();
}

/* PACKAGE EDIT *******************************************************/
	
class CPackageNameEdit : public gui::CAbstractTextEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	
	virtual void SaveFromTextBuffer()
	{
		AssetsManager()->SetPackageName(m_pAssetsEditor->GetEditedPackageId(), GetText());
	}
	
	virtual void CopyToTextBuffer()
	{
		const char* pName = AssetsManager()->GetPackageName(m_pAssetsEditor->GetEditedPackageId());
		
		if(pName)
		{
			if(str_comp(pName, m_aText) != 0)
				SetText(pName);
		}
		else
			SetText("");
	}
	
public:
	CPackageNameEdit(CGuiEditor* pAssetsEditor) :
		gui::CAbstractTextEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor)
	{ }
};

gui::CVScrollLayout* CAssetsInspector::CreateTab_Package()
{
	gui::CVScrollLayout* pTab = new gui::CVScrollLayout(Context());
	
	pTab->Disable();
	AddTab(pTab, "Package", AssetsEditor()->m_Path_Sprite_IconAsset);
	
	AddField(pTab, new CPackageNameEdit(AssetsEditor()), "Name");
	
	return pTab;
}

/* TEXT EDIT **********************************************************/
	
class CMemberTextEdit : public gui::CAbstractTextEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	
	virtual void SaveFromTextBuffer()
	{
		AssetsManager()->SetAssetValue<const char*>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetEditedSubPath(),
			m_Member,
			GetText()
		);
	}
	
	virtual void CopyToTextBuffer()
	{
		const char* pName = AssetsManager()->GetAssetValue<const char*>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetEditedSubPath(),
			m_Member,
			GetText()
		);
		
		if(pName)
		{
			if(str_comp(pName, m_aText) != 0)
				SetText(pName);
		}
		else
			SetText("");
	}
	
public:
	CMemberTextEdit(CGuiEditor* pAssetsEditor, int Member) :
		gui::CAbstractTextEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member)
	{ }
};

void CAssetsInspector::AddField_Text(gui::CVListLayout* pList, int Member, const char* pLabelText)
{
	CMemberTextEdit* pWidget = new CMemberTextEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, pLabelText);
}

/* INTEGER EDIT *******************************************************/
	
class CMemberIntegerEdit : public gui::CAbstractIntegerEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	
	virtual int GetValue() const
	{
		return m_pAssetsEditor->AssetsManager()->GetAssetValue<int>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetEditedSubPath(),
			m_Member,
			0
		);
	}
	
	virtual void SetValue(int Value)
	{
		m_pAssetsEditor->AssetsManager()->SetAssetValue<int>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetEditedSubPath(),
			m_Member,
			Value
		);
	}
	
public:
	CMemberIntegerEdit(CGuiEditor* pAssetsEditor, int Member) :
		gui::CAbstractIntegerEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member)
	{ }
};

void CAssetsInspector::AddField_Integer(gui::CVListLayout* pList, int Member, const char* pLabelText)
{
	CMemberIntegerEdit* pWidget = new CMemberIntegerEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, pLabelText);
}

void CAssetsInspector::AddField_Integer_NoEdit(gui::CVListLayout* pList, int Member, const char* pLabelText)
{
	CMemberIntegerEdit* pWidget = new CMemberIntegerEdit(
		m_pAssetsEditor,
		Member
	);
	pWidget->Editable(false);
	
	AddField(pList, pWidget, pLabelText);
}

/* FLOAT EDIT *********************************************************/
	
class CMemberFloatEdit : public gui::CAbstractFloatEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	
	virtual float GetValue() const
	{
		return m_pAssetsEditor->AssetsManager()->GetAssetValue<float>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetEditedSubPath(),
			m_Member,
			0
		);
	}
	
	virtual void SetValue(float Value)
	{
		m_pAssetsEditor->AssetsManager()->SetAssetValue<float>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetEditedSubPath(),
			m_Member,
			Value
		);
	}
	
public:
	CMemberFloatEdit(CGuiEditor* pAssetsEditor, int Member) :
		gui::CAbstractFloatEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member)
	{ }
};

void CAssetsInspector::AddField_Float(gui::CVListLayout* pList, int Member, const char* pLabelText)
{
	CMemberFloatEdit* pWidget = new CMemberFloatEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, pLabelText);
}

void CAssetsInspector::AddField_Vec2(gui::CVListLayout* pList, int Member, int Member2, const char* pLabelText)
{
	gui::CHListLayout* pLayout = new gui::CHListLayout(Context());
	
	pLayout->Add(new CMemberFloatEdit(
		m_pAssetsEditor,
		Member
	), true);
	pLayout->Add(new CMemberFloatEdit(
		m_pAssetsEditor,
		Member2
	), true);
	
	AddField(pList, pLayout, pLabelText);
}

/* FLOAT EDIT *********************************************************/
	
class CMemberAngleEdit : public gui::CAbstractFloatEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	
	virtual float GetValue() const
	{
		return 180.0f*m_pAssetsEditor->AssetsManager()->GetAssetValue<float>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetEditedSubPath(),
			m_Member,
			0
		)/pi;
	}
	
	virtual void SetValue(float Value)
	{
		m_pAssetsEditor->AssetsManager()->SetAssetValue<float>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetEditedSubPath(),
			m_Member,
			Value * pi/180.0f
		);
	}
	
public:
	CMemberAngleEdit(CGuiEditor* pAssetsEditor, int Member) :
		gui::CAbstractFloatEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member)
	{ }
};

void CAssetsInspector::AddField_Angle(gui::CVListLayout* pList, int Member, const char* pLabelText)
{
	CMemberAngleEdit* pWidget = new CMemberAngleEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, pLabelText);
}

/* COLOR EDIT *********************************************************/
	
class CMemberColorEdit : public gui::CAbstractColorEdit
{
protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	
	virtual vec4 GetValue() const
	{
		return m_pAssetsEditor->AssetsManager()->GetAssetValue<vec4>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetEditedSubPath(),
			m_Member,
			vec4(1.0f, 1.0f, 1.0f, 1.0f)
		);
	}
	
	virtual void SetValue(vec4 Value)
	{
		m_pAssetsEditor->AssetsManager()->SetAssetValue<vec4>(
			m_pAssetsEditor->GetEditedAssetPath(),
			m_pAssetsEditor->GetEditedSubPath(),
			m_Member,
			Value
		);
	}
	
public:
	CMemberColorEdit(CGuiEditor* pAssetsEditor, int Member) :
		gui::CAbstractColorEdit(pAssetsEditor),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member)
	{ }
};

void CAssetsInspector::AddField_Color(gui::CVListLayout* pList, int Member, const char* pLabelText)
{
	CMemberColorEdit* pWidget = new CMemberColorEdit(
		m_pAssetsEditor,
		Member
	);
	
	AddField(pList, pWidget, pLabelText);
}

/* ASSET EDIT *********************************************************/

class CMemberAssetEdit : public gui::CButton
{
public:
	class CPopup : public gui::CPopup
	{
	public:
		class CItem : public gui::CButton
		{
		protected:
			CAssetPath m_AssetPath;
			CPopup* m_pPopup;
		
		protected:
			virtual void MouseClickAction()
			{
				m_pPopup->SetValue(m_AssetPath);
			}
			
		public:
			CItem(CPopup* pPopup, CAssetPath AssetPath) :
				gui::CButton(pPopup->Context(), ""),
				m_pPopup(pPopup),
				m_AssetPath(AssetPath)
			{
				if(m_AssetPath.IsNull())
				{
					SetIcon(m_pPopup->m_pAssetsEditor->m_Path_Sprite_IconNone);
					SetText("None");
				}
				else
				{
					SetIcon(m_pPopup->m_pAssetsEditor->GetItemIcon(m_AssetPath, CSubPath::Null()));
					SetText(m_pPopup->m_pAssetsEditor->GetItemName(m_AssetPath, CSubPath::Null()));
				}
			}
			
			virtual void Update(bool ParentEnabled)
			{
				if(ParentEnabled)
				{
					if(m_pPopup->GetValue() == m_AssetPath)
						SetButtonStyle(m_pPopup->m_pAssetsEditor->m_Path_Button_ListItemHL);
					else
						SetButtonStyle(m_pPopup->m_pAssetsEditor->m_Path_Button_ListItem);
				}
				
				gui::CButton::Update(ParentEnabled);
			}
		};
	
	protected:
		CGuiEditor* m_pAssetsEditor;
		int m_Member;
		int m_AssetType;
	
	public:
		CPopup(CGuiEditor* pAssetsEditor, int Member, int AssetType, gui::CRect ParentRect) :
			gui::CPopup(pAssetsEditor, ParentRect, 250, 400, gui::CPopup::ALIGNMENT_SIDE),
			m_pAssetsEditor(pAssetsEditor),
			m_Member(Member),
			m_AssetType(AssetType)
		{
			
			gui::CVScrollLayout* pLayout = new gui::CVScrollLayout(Context());
			Add(pLayout);
			
			SetBoxStyle(m_pAssetsEditor->m_Path_Box_Dialog);
			pLayout->Add(new CItem(this, CAssetPath::Null()), false);
			
			#define MACRO_ASSETTYPE(Name) case CAsset_##Name::TypeId:\
				{\
					gui::CExpand* pExpand = new gui::CExpand(Context());\
					pLayout->Add(pExpand);\
					pExpand->SetTitle(new gui::CLabel(Context(), AssetsManager()->GetPackageName(m_pAssetsEditor->GetEditedPackageId()), m_pAssetsEditor->m_Path_Sprite_IconFolder));\
					for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_##Name>(m_pAssetsEditor->GetEditedPackageId()); i++)\
						pExpand->Add(new CItem(this, CAssetPath(CAsset_##Name::TypeId, m_pAssetsEditor->GetEditedPackageId(), i)));\
				}\
				for(int p=0; p<AssetsManager()->GetNumPackages(); p++)\
				{\
					if(p != m_pAssetsEditor->GetEditedPackageId())\
					{\
						gui::CExpand* pExpand = new gui::CExpand(Context());\
						pLayout->Add(pExpand);\
						pExpand->SetTitle(new gui::CLabel(Context(), AssetsManager()->GetPackageName(p), m_pAssetsEditor->m_Path_Sprite_IconFolder));\
						for(int i=0; i<AssetsManager()->GetNumAssets<CAsset_##Name>(p); i++)\
							pExpand->Add(new CItem(this, CAssetPath(CAsset_##Name::TypeId, p, i)));\
					}\
				}\
				break;
			
			switch(m_AssetType)
			{
				#include <generated/assets/assetsmacro.h>
			}
			
			#undef TU_MACRO_ASSETTYPE
		}
		
		CAssetPath GetValue()
		{
			return m_pAssetsEditor->AssetsManager()->GetAssetValue<CAssetPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetEditedSubPath(),
				m_Member,
				CAssetPath::Null()
			);
		}
		
		void SetValue(CAssetPath Value)
		{
			m_pAssetsEditor->AssetsManager()->SetAssetValue<CAssetPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetEditedSubPath(),
				m_Member,
				Value
			);
		}
	
		virtual int GetInputToBlock() { return CGui::BLOCKEDINPUT_ALL; }
	};

protected:
	CGuiEditor* m_pAssetsEditor;
	int m_Member;
	int m_AssetType;
	
protected:
	virtual void MouseClickAction()
	{
		Context()->DisplayPopup(new CPopup(m_pAssetsEditor, m_Member, m_AssetType, m_DrawRect));
	}

public:
	CMemberAssetEdit(CGuiEditor* pAssetsEditor, int Member, int AssetType) :
		gui::CButton(pAssetsEditor, "", CAssetPath::Null()),
		m_pAssetsEditor(pAssetsEditor),
		m_Member(Member),
		m_AssetType(AssetType)
	{
		
	}
	
	virtual void Update(bool ParentEnabled)
	{
		if(IsEnabled() && ParentEnabled)
		{
			CAssetPath Value = m_pAssetsEditor->AssetsManager()->GetAssetValue<CAssetPath>(
				m_pAssetsEditor->GetEditedAssetPath(),
				m_pAssetsEditor->GetEditedSubPath(),
				m_Member,
				CAssetPath::Null()
			);
			
			if(Value.IsNull())
			{
				SetIcon(m_pAssetsEditor->m_Path_Sprite_IconNone);
				SetText("None");
			}
			else
			{
				SetIcon(m_pAssetsEditor->GetItemIcon(Value, CSubPath::Null()));
				SetText(m_pAssetsEditor->GetItemName(Value, CSubPath::Null()));
			}
		}
		
		gui::CButton::Update(ParentEnabled);
	}
};

void CAssetsInspector::AddField_Asset(gui::CVListLayout* pList, int Member, int AssetType, const char* pLabelText)
{
	CMemberAssetEdit* pWidget = new CMemberAssetEdit(
		m_pAssetsEditor,
		Member,
		AssetType
	);
	
	AddField(pList, pWidget, pLabelText);
}