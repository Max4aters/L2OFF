
#pragma once

#include <Server/CObject.h>
#include <Server/CContributeData.h>
#include <Server/CSkillInfo.h>
#include <windows.h>
#include <vector>

class CItem : CObject {
public:
	class WorldInfo {
	public:
		/* 0x0000 */ void *unknown;
		/* 0x0008 */ double x;
		/* 0x0010 */ double y;
		/* 0x0018 */ double z;
		/* 0x0020 */ unsigned char padding0x0020[0x0050 - 0x0020];
		/* 0x0050 */ bool pickable;
		/* 0x0051 */ unsigned char padding0x0051[0x0068 - 0x0051];
		/* 0x0068 */ UINT64 count;
		/* 0x0070 */ unsigned char padding0x0070[0x007C - 0x0070];
		/* 0x007C */ UINT32 itemType;
		/* 0x0080 */ unsigned char padding0x0080[0x0088 - 0x0080];
		/* 0x0088 */ UINT32 consumeType;
	};

	class ItemInfo {
	public:
		class Ext {
		public:
			Ext();
			~Ext();

			bool isPrivateStore;
			bool isPrivateStoreSet;
			bool isOlympiadCanUse;
		};

		ItemInfo* Constructor();
		void Destructor(bool isMemoryFreeUsed);

		/* 0x0000 */ unsigned char padding0x0000[0x0008 - 0x0000];
		/* 0x0008 */ UINT32 someType;
		/* 0x000C */ unsigned char padding0x000C[0x0108 - 0x000C];
		/* 0x0108 */ UINT32 dropPeriod;
		/* 0x010C */ unsigned char padding0x010C[0x0198 - 0x010C];
		/* 0x0198 */ Ext ext;
	};

	static void Init();

	class CContributeData* GetContributeData();
	bool IsTradeable(class CUser *user);

	static UINT64 __cdecl WarehouseDepositHelper(CItem *item);

	/* 0x0000 */ unsigned char padding0x0000[0x001C - 0x0000];
	/* 0x001C */ UINT32 itemId;
	/* 0x0020 */ unsigned char padding0x0020[0x0048 - 0x0020];
	/* 0x0048 */ WorldInfo *worldInfo;
	/* 0x0050 */ ItemInfo *itemInfo;
	/* 0x0058 */ unsigned char padding0x0058[0x0078 - 0x0058];
	/* 0x0078 */ std::vector<CSkillInfo*> skills;
	/* 0x0098 */ unsigned char padding0x0098[0x00B8 - 0x0098];
	/* 0x00B8 */ UINT32 contributeDataObjectId;
};

