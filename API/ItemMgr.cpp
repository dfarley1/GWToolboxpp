#include "ItemMgr.h"

void GWAPI::ItemMgr::OpenXunlaiWindow()
{
	static DWORD* xunlaibuf = new DWORD[2]{0, 1};
	parent->GameThread->Enqueue(_OpenXunlai,
		*MemoryMgr::ReadPtrChain<DWORD*>((DWORD)MemoryMgr::XunlaiSession, 4, 0x118, 0x10, 0, 0x14), xunlaibuf);
}

void GWAPI::ItemMgr::PickUpItem(Item* item, DWORD CallTarget /*= 0*/)
{
	parent->CtoS->SendPacket(0xC, 0x39, item->AgentId, CallTarget);
}

void GWAPI::ItemMgr::DropItem(Item* item, DWORD quantity)
{
	parent->CtoS->SendPacket(0xC, 0x26, item->ItemId, quantity);
}

void GWAPI::ItemMgr::EquipItem(Item* item)
{
	parent->CtoS->SendPacket(0x8, 0x2A, item->ItemId);
}

void GWAPI::ItemMgr::UseItem(Item* item)
{
	parent->CtoS->SendPacket(0x8, 0x78, item->ItemId);
}

GWAPI::ItemMgr::Bag* GWAPI::ItemMgr::GetBagArray()
{
	return *MemoryMgr::ReadPtrChain<Bag**>(MemoryMgr::GetContextPtr(), 2, 0x40, 0xF8);
}

GWAPI::ItemMgr::ItemArray GWAPI::ItemMgr::GetItemArray()
{
	return *MemoryMgr::ReadPtrChain<ItemArray*>(MemoryMgr::GetContextPtr(), 2, 0x40, 0xB8);
}

GWAPI::ItemMgr::ItemMgr(GWAPIMgr* obj) : parent(obj)
{
	_OpenXunlai = (OpenXunlai_t)MemoryMgr::OpenXunlaiFunction;
}