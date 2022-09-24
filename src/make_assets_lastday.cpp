/*
 * Copyright (C) 2016 necropotame (necropotame@gmail.com)
 * 
 * This file is part of TeeUniverse.
 * 
 * TeeUniverse is free software: you can redistribute it and/or  modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * TeeUniverse is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with TeeUniverse.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <shared/system/debug.h>
#include <shared/system/string.h>
#include <shared/kernel.h>
#include <shared/components/assetsmanager.h>
#include <shared/components/storage.h>
#include <client/loading_tools.h>

#include <cstdlib>

#define CREATE_ZONEINDEX(groupid, name, desc) {\
	SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());\
	pAsset->SetIndexTitle(SubPath, name);\
	pAsset->SetIndexDescription(SubPath, desc);\
	pAsset->SetIndexGroup(SubPath, groupid);\
}

#define CREATE_ZONEINDEX_NOUSE() {\
	SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());\
	pAsset->SetIndexUsed(SubPath, false);\
}

#define CREATE_SPRITE_PATH(path, packageid, name, image, x, y, w, h) {\
	CAsset_Sprite* pSprite = pKernel->AssetsManager()->NewAsset_Hard<CAsset_Sprite>(&path, packageid);\
	pSprite->SetName(name);\
	pSprite->SetImagePath(image);\
	pSprite->SetX(x);\
	pSprite->SetY(y);\
	pSprite->SetWidth(w);\
	pSprite->SetHeight(h);\
}

int main(int argc, char* argv[])
{
	{
		std::unique_ptr<CSharedKernel> pKernel(new CSharedKernel());
		
		if(!pKernel->Init(argc, (const char**) argv))
		{
			debug::ErrorStream("Kernel") << "unable to initialize shared kernel" << std::endl;
			exit(EXIT_FAILURE);
		}
		
		int PackageId = pKernel->AssetsManager()->NewPackage("lastday");
		pKernel->AssetsManager()->SetPackageAuthor(PackageId, "Error Dreemurr");
		pKernel->AssetsManager()->SetPackageCredits(PackageId, "necropotame, ErrorDreemurr");
		pKernel->AssetsManager()->SetPackageLicense(PackageId, "CC-BY-SA 3.0");
		pKernel->AssetsManager()->SetPackageVersion(PackageId, "0.0.1");
		
		CAssetPath ImageZonesPath = CreateNewImage(pKernel.get(), PackageId, "zones", "images/univ_lastday/zones.png", CStorage::TYPE_ALL, 16, 16, true, 0);
		CAssetPath ImageEntitiesPath = CreateNewImage(pKernel.get(), PackageId, "entities", "images/univ_lastday/entities.png", CStorage::TYPE_ALL, 4, 4);
	
		//Zone, damage
		{
			CAssetPath AssetPath;
			CSubPath SubPath;
			
			CAsset_ZoneType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_ZoneType>(&AssetPath, PackageId);
			pAsset->SetName("lastday");
			pAsset->SetImagePath(ImageZonesPath);
			
			int GroupId_Death = pAsset->AddGroup();
			int GroupId_Life = pAsset->AddGroup();
			int GroupId_Freeze = pAsset->AddGroup();
			
			pAsset->SetGroup(CAsset_ZoneType::SubPath_Group(GroupId_Death), "Death");
			pAsset->SetGroup(CAsset_ZoneType::SubPath_Group(GroupId_Life), "Life");
			pAsset->SetGroup(CAsset_ZoneType::SubPath_Group(GroupId_Freeze), "Freeze");
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "Empty");
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "Death zone");
			pAsset->SetIndexDescription(SubPath, "Any player touching this zone dies instantly");
			pAsset->SetIndexBorderIndex(SubPath, 1);
			pAsset->SetIndexBorderColor(SubPath, vec4(1.0f, 0.0f, 0.0f, 1.0f));
			pAsset->SetIndexGroup(SubPath, GroupId_Death);
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "Cold zone");
			pAsset->SetIndexDescription(SubPath, "Any player touching this zone will feel cold.");
			pAsset->SetIndexBorderIndex(SubPath, 2);
			pAsset->SetIndexBorderColor(SubPath, vec4(0.0f, 0.0f, 0.0f, 0.0f));
			pAsset->SetIndexGroup(SubPath, GroupId_Life);
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "Hot zone");
			pAsset->SetIndexDescription(SubPath, "Any player touching this zone will feel hot.");
			pAsset->SetIndexBorderIndex(SubPath, 3);
			pAsset->SetIndexBorderColor(SubPath, vec4(1.0f, 0.0f, 0.0f, 0.0f));
			pAsset->SetIndexGroup(SubPath, GroupId_Life);
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "Freeze");
			pAsset->SetIndexDescription(SubPath, "Freeze a player");
			pAsset->SetIndexBorderIndex(SubPath, 4);
			pAsset->SetIndexBorderColor(SubPath, vec4(0.0f, 0.0f, 0.0f, 0.0f));
			pAsset->SetIndexGroup(SubPath, GroupId_Freeze);
			
			SubPath = CAsset_ZoneType::SubPath_Index(pAsset->AddIndex());
			pAsset->SetIndexTitle(SubPath, "Unfreeze");
			pAsset->SetIndexDescription(SubPath, "Unfreeze a player");
			pAsset->SetIndexBorderIndex(SubPath, 5);
			pAsset->SetIndexBorderColor(SubPath, vec4(0.0f, 0.0f, 0.0f, 0.0f));
			pAsset->SetIndexGroup(SubPath, GroupId_Freeze);
		}	
		
		//EntityType, Human Spawn
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoHumanSpawn", ImageEntitiesPath, 0, 3, 1, 1);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("ldHuman");
			pAsset->SetCollisionRadius(64.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}
		
		//EntityType, Zombie Spawn
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoZombieSpawn", ImageEntitiesPath, 1, 3, 1, 1);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("ldZombie");
			pAsset->SetCollisionRadius(64.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}

		//EntityType, Rain Spawn
		{
			CAssetPath GizmoPath;
			CAssetPath AssetPath;
			
			CREATE_SPRITE_PATH(GizmoPath, PackageId, "gizmoRainSpawn", ImageEntitiesPath, 0, 0, 1, 1);
			
			CAsset_EntityType* pAsset = pKernel->AssetsManager()->NewAsset_Hard<CAsset_EntityType>(&AssetPath, PackageId);
			pAsset->SetName("ldRain");
			pAsset->SetCollisionRadius(64.0f);
			pAsset->SetGizmoPath(GizmoPath);
		}

		pKernel->AssetsManager()->Save_AssetsFile_SaveDir(PackageId);
		
		pKernel->Shutdown();
	}

	exit(EXIT_SUCCESS);
}
