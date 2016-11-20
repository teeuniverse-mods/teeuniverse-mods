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

#include <editor/gui/view.h>
#include <editor/gui/view_image.h>
#include <editor/gui/view_sprite.h>
#include <editor/gui/view_map.h>
#include <editor/gui/view_gui.h>
#include <editor/components/gui.h>
#include <shared/components/assetsmanager.h>
#include <client/components/assetsrenderer.h>
#include <shared/components/localization.h>

/* CURSORTOOL *********************************************************/

CViewManager::CView::CCursorTool::CCursorTool(CView* pView, const char* pName, CAssetPath IconPath) :
	gui::CButton(pView->Context(), pName, IconPath),
	m_pView(pView),
	m_OnUse(false)
{
	NoTextClipping();
}

void CViewManager::CView::CCursorTool::MouseClickAction()
{
	m_pView->SetCursorTool(this);
}

void CViewManager::CView::CCursorTool::Update(bool ParentEnabled)
{
	if(m_OnUse)
		SetButtonStyle(AssetsEditor()->m_Path_Button_CursorToolHL);
	else
		SetButtonStyle(AssetsEditor()->m_Path_Button_CursorTool);
}

void CViewManager::CView::CCursorTool::OnUse(bool Used)
{
	m_OnUse = Used;
}

/* VIEW ***************************************************************/

CViewManager::CView::CView(CGuiEditor* pAssetsEditor) :
	gui::CWidget(pAssetsEditor),
	m_pCursorTool(0),
	m_pAssetsEditor(pAssetsEditor)
{
	m_pToolbar = new gui::CHListLayout(Context());
	m_pToolbar->SetBoxStyle(m_pAssetsEditor->m_Path_Box_Panel);
}

CViewManager::CView::~CView()
{
	delete m_pToolbar;
}

void CViewManager::CView::SetCursorTool(CCursorTool* pCursorTool)
{
	if(m_pCursorTool == pCursorTool)
		return;
	
	if(m_pCursorTool)
		m_pCursorTool->OnUse(false);
	
	m_pCursorTool = pCursorTool;
	
	if(m_pCursorTool)
		m_pCursorTool->OnUse(true);
}

void CViewManager::CView::Update(bool ParentEnabled)
{
	m_pToolbar->Update(ParentEnabled);
	
	if(m_pCursorTool && m_pCursorTool->IsEnabled())
		m_pCursorTool->UpdateView();
}

void CViewManager::CView::UpdateBoundingSize()
{
	m_pToolbar->UpdateBoundingSize();
	
	m_BoundingSizeRect.BSMinimum(200, 200);
	m_BoundingSizeRect.BSVerticalAdd(m_pToolbar->GetBS());
}

void CViewManager::CView::UpdatePosition(const gui::CRect& BoundingRect, const gui::CRect& VisibilityRect)
{
	gui::CWidget::UpdatePosition(BoundingRect, VisibilityRect);
	
	gui::CRect ToolbarRect(
		m_DrawRect.x,
		m_DrawRect.y,
		m_DrawRect.w,
		m_pToolbar->GetBS().minh
	);
	m_pToolbar->UpdatePosition(ToolbarRect, m_VisibilityRect);
	
	m_ViewRect = gui::CRect(
		m_DrawRect.x,
		ToolbarRect.y + ToolbarRect.h,
		m_DrawRect.w,
		m_DrawRect.h - m_pToolbar->GetBS().minh
	);
}

void CViewManager::CView::Render()
{
	Graphics()->ClipPush(m_ViewRect.x, m_ViewRect.y, m_ViewRect.w, m_ViewRect.h);
	
	RenderView();
	
	if(m_pCursorTool && m_pCursorTool->IsEnabled())
		m_pCursorTool->RenderView();
	
	Graphics()->ClipPop();
	
	m_pToolbar->Render();
}

void CViewManager::CView::OnButtonClick(int Button)
{
	if(m_pCursorTool && m_pCursorTool->IsEnabled())
		m_pCursorTool->OnViewButtonClick(Button);
		
	m_pToolbar->OnButtonClick(Button);
}

void CViewManager::CView::OnButtonRelease(int Button)
{
	if(m_pCursorTool && m_pCursorTool->IsEnabled())
		m_pCursorTool->OnViewButtonRelease(Button);
		
	m_pToolbar->OnButtonRelease(Button);
}

void CViewManager::CView::OnMouseMove()
{
	if(m_pCursorTool && m_pCursorTool->IsEnabled())
		m_pCursorTool->OnViewMouseMove();
		
	m_pToolbar->OnMouseMove();
}


/* VIEW MANAGER *******************************************************/

CViewManager::CViewManager(CGuiEditor* pAssetsEditor) :
	gui::CWidget(pAssetsEditor),
	m_pAssetsEditor(pAssetsEditor),
	m_pCurrentView(0),
	m_BoxStylePath(pAssetsEditor->m_Path_Box_View)
{
	m_pViewImage = new CViewImage(AssetsEditor());
	m_pViewSprite = new CViewSprite(AssetsEditor());
	m_pViewMap = new CViewMap(AssetsEditor());
	m_pViewGui = new CViewGui(AssetsEditor());
}

void CViewManager::Destroy()
{
	m_pViewImage->Destroy();
	
	gui::CWidget::Destroy();
}

void CViewManager::Update(bool ParentEnabled)
{
	switch(AssetsEditor()->GetEditedAssetPath().GetType())
	{
		case CAsset_Image::TypeId:
			m_pCurrentView = m_pViewImage;
			break;
		case CAsset_Sprite::TypeId:
			m_pCurrentView = m_pViewSprite;
			break;
		case CAsset_Map::TypeId:
		case CAsset_MapGroup::TypeId:
		case CAsset_MapLayerQuads::TypeId:
		case CAsset_MapLayerTiles::TypeId:
		case CAsset_MapZoneTiles::TypeId:
			m_pCurrentView = m_pViewMap;
			break;
		case CAsset_GuiRectStyle::TypeId:
		case CAsset_GuiLineStyle::TypeId:
		case CAsset_GuiBoxStyle::TypeId:
		case CAsset_GuiLabelStyle::TypeId:
		case CAsset_GuiButtonStyle::TypeId:
		case CAsset_GuiTabsStyle::TypeId:
			m_pCurrentView = m_pViewGui;
			break;
		default:
			m_pCurrentView = 0;
	}
	
	if(m_pCurrentView)
		m_pCurrentView->Update(ParentEnabled);
}

void CViewManager::UpdateBoundingSize()
{
	m_BoundingSizeRect.BSNoConstraint();
	
	if(m_pCurrentView)
	{
		m_pCurrentView->UpdateBoundingSize();
		m_BoundingSizeRect.BSVerticalAdd(m_pCurrentView->GetBS());
	}
	
	const CAsset_GuiBoxStyle* pBoxStyle = AssetsManager()->GetAsset<CAsset_GuiBoxStyle>(m_BoxStylePath);
	if(pBoxStyle)
	{
		m_BoundingSizeRect.BSAddMargin(Context()->ApplyGuiScale(pBoxStyle->GetMargin()));
		m_BoundingSizeRect.BSAddMargin(Context()->ApplyGuiScale(pBoxStyle->GetPadding()));
	}
}

void CViewManager::UpdatePosition(const gui::CRect& BoundingRect, const gui::CRect& VisibilityRect)
{
	gui::CWidget::UpdatePosition(BoundingRect, VisibilityRect);
	
	gui::CRect Rect = m_DrawRect;
	const CAsset_GuiBoxStyle* pBoxStyle = AssetsManager()->GetAsset<CAsset_GuiBoxStyle>(m_BoxStylePath);
	if(pBoxStyle)
	{
		Rect.RemoveMargin(Context()->ApplyGuiScale(pBoxStyle->GetMargin()));
		Rect.RemoveMargin(Context()->ApplyGuiScale(pBoxStyle->GetPadding()));
	}
	
	if(m_pCurrentView)
		m_pCurrentView->UpdatePosition(Rect, m_VisibilityRect);
}

void CViewManager::Render()
{
	const CAsset_GuiBoxStyle* pBoxStyle = AssetsManager()->GetAsset<CAsset_GuiBoxStyle>(m_BoxStylePath);
	if(pBoxStyle)
	{
		gui::CRect Rect = m_DrawRect;
		Rect.RemoveMargin(Context()->ApplyGuiScale(pBoxStyle->GetMargin()));
	
		AssetsRenderer()->DrawGuiRect(&Rect, pBoxStyle->GetRectPath());
			
		Rect.RemoveMargin(Context()->ApplyGuiScale(pBoxStyle->GetPadding()));
	}
	
	if(m_pCurrentView)
		m_pCurrentView->Render();
}

void CViewManager::OnMouseMove()
{
	if(m_pCurrentView)
		m_pCurrentView->OnMouseMove();
}

void CViewManager::OnButtonClick(int Button)
{
	if(m_pCurrentView)
		m_pCurrentView->OnButtonClick(Button);
}

void CViewManager::OnButtonRelease(int Button)
{
	if(m_pCurrentView)
		m_pCurrentView->OnButtonRelease(Button);
}

void CViewManager::OnInputEvent(const CInput::CEvent& Event)
{
	if(m_pCurrentView)
		m_pCurrentView->OnInputEvent(Event);
}