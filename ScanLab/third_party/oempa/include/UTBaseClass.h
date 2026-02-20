
#pragma once


class CUTFormat;
enum enumBaseStatus{eStatusReadEnable=(1<<0),eStatusWriteEnable=(1<<1),
						eStatusEditEnable=(1<<2),
						eStatusVisible=(1<<3),
						eStatusEventUpdateEnable=(1<<4),
						eStatusKernel=(1<<5),
						eStatusUpdate=(1<<6),eStatusPathRootID=(1<<7)
					};


class UTKERNEL_API_ALIGN _CUTBaseClass
{
private:
	ULONGLONG m_ullPrivateMemory[18];
public:
	_CUTBaseClass();

};

class UTKERNEL_API_ALIGN CUTBaseClass :
	public _CUTBaseClass
{
public:
public:

public:
public:

public:
	CUTBaseClass(const CUTBaseClass &a);
	~CUTBaseClass();
	virtual void ProcessPreSignalDestructor();
	void PreSignalDestructor();
	virtual bool vf_driver_FillContext(enumClassID eClassID,CUTBaseClass *pMember,structDrvContext &drvContext);
	virtual bool vf_IsKernelRoot() const;
	virtual bool vf_UpdateData(int iIndexItem) const;
	virtual bool vf_GetArrayIndex(CUTBaseClass *pItem,int &iIndex1,int &iIndex2,int &iIndexItem);
	virtual void vf_GetIndex(int iIndexItem,int &iIndex1,int &iIndex2) const;
	virtual enumClassID vf_GetChildClassID() const;
	virtual int vf_GetNewListId();
	virtual bool vf_SetLoadIndex(int iLoadIndex);
	virtual bool vf_GetLoadIndex(int &iLoadIndex);
	virtual bool vf_UpdateUserMode(enumUserMode eUserMode);

public:
	int GetListId() const;
	virtual CUTBaseClass *vf_GetChild(wchar_t *pDefaultLanguageName,enumClassID eClassID);//default language.
	virtual CUTBaseClass *vf_GetNextChild(structMaskStatus maskStatus,CUTBaseClass **ppChild,int &iIndex,enumClassID &eClassID);
	virtual const CUTBaseClass *vf_cGetNextChild(structMaskStatus maskStatus,CUTBaseClass **ppChild,int &iIndex,enumClassID &eClassID) const;
	virtual CUTBaseClass *vf_GetChildStatus(structMaskStatus maskStatus,int iIndex,enumClassID &eClassID);
	virtual const CUTBaseClass *vf_cGetChildStatus(structMaskStatus maskStatus,int iIndex,enumClassID &eClassID) const;
	virtual bool vf_HeaderSave(CUTFormat *pFormat,bool bNewClass=false);//save header part for binary format (size, type id, status), nothing for text format.
	virtual bool vf_SaveAllChildMember(CUTFormat *pFormat);//save all child members (call "vf_Save" for each child member).
	virtual bool vf_HeaderLoad(CUTFormat *pFormat,int iSize,wchar_t *pValue,int &iSizeof,enumClassID &eClassID,bool &bNewClass,bool &bArray,bool &bEnd,int &iStatus,int &iLayerIndex);//default language, load header part for binary format (size, type id, status), nothing for text format. Call "StaticHeaderLoad".
	virtual bool vf_Remove(CUTBaseClass *pBaseClass,bool bEventUpdate,bool bSharedMemory);
	virtual bool vf_driver_Update();
	virtual int vf_Sizeof(CUTFormat *pFormat);
	virtual bool vf_Save(CUTFormat *pFormat,const structLayer &layerIndex);//call "vf_HeaderSave" et "vf_SaveAllChildMember".
	virtual bool vf_Load(CUTFormat *pFormat,const structLayer &layerIndex);

public:
	CUTBaseClass *GetObject(int iKernelLanguageIndex,const wchar_t *pPath,structLayer &layerIndex);//current language.
	CUTBaseClass *GetUserObject(int iSizeIndex,structLayer *pLayerIndex,structLayer &layerIndex);
	static bool sGetValueString(const wchar_t *pPath,int iSize, wchar_t *pValue);
	static bool sSetValueString(const wchar_t *pPathWithValue);

public:
	int GetPathSize(int iKernelLanguageIndex) const;
	bool GetPath(int iKernelLanguageIndex,int iSize,wchar_t *pPath) const;
	bool GetPath(int iKernelLanguageIndex,int iSize,wchar_t *pPath,int &iSizeRequired) const;

public:
	void GetMemberStringValue(const structLayer &layerIndex,int iKernelLanguageIndex,int iSizeName,wchar_t *pMemberValue,CUTBaseClass *pBaseClass);//current language.

public:
	bool GetValueString(int iKernelLanguageIndex,int iSize,wchar_t *pValue) const;//current language.
	int SetValueString(wchar_t *pValue);
	virtual bool vf_GetValueString(int iKernelLanguageIndex,int iSize,wchar_t *pValue) const;//current language.
	virtual int vf_SetValueString(wchar_t *pValue);
	virtual int vf_SetValueString(wchar_t *pValue,bool bEventUpdate,bool bSharedMemory);

public:
	int GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual int vf_GetChildCount(enumClassID eClassID,int &iCount1,int &iCount2) const;
	virtual bool vf_GetStringComment(int iSize,wchar_t *pValue,int &iSizeRequired) const;//current language.
	virtual enumUnit vf_GetUnit() const;

public:
	bool GetUserLayerPath(int iKernelLanguageIndex,const wchar_t *pMember,int iSizeIndex,structLayer *pLayerIndex,int &iLayer) const;//user function.

public:
	bool GetName(int iKernelLanguageIndex,int iSize,wchar_t *pName) const;
	const wchar_t *GetName(int iKernelLanguageIndex) const;
	const wchar_t *GetDefaultName() const;
	virtual void vf_SetBaseDefault(bool bEventUpdate,bool bSharedMemory);
	virtual void vf_SetDefault(bool bUpdateClass,bool bEventUpdate,bool bSharedMemory);
	virtual bool vf_CheckLimit(enumClassID eClassID,bool bEventUpdate,bool bSharedMemory);//multiple inheritance
	virtual bool vf_PostLoad(enumClassID eClassID,CUTFormat *pFormat);//multiple inheritance
	virtual bool vf_PreLoad(enumClassID eClassID,CUTFormat *pFormat);//multiple inheritance
	virtual void vf_UpdateClass(enumClassID eClassID);//multiple inheritance

public:
	bool IsDisabled(bool bRead,CUTBaseClass *pObject,const structLayer &layerIndex);
	bool IsReadDisabled(CUTBaseClass *pObject,const structLayer &layerIndex);
	bool IsWriteDisabled(CUTBaseClass *pObject,const structLayer &layerIndex);
	void Enable(bool bValue);//both read and write
	void EnableWrite(bool bValue);
	void EnableWrite(bool bValue,bool bEventUpdate);
	void EnableRead(bool bValue);
	void Visible(bool bValue);

public:
	bool IsReadDisabled(bool bThisItemOnly=false) const;
	bool IsWriteDisabled(bool bThisItemOnly=false) const;
	bool IsReadEnabled(bool bThisItemOnly=false) const;
	bool IsWriteEnabled(bool bThisItemOnly=false) const;
	bool IsEnabled(bool bThisItemOnly=false) const;
	bool IsVisibled(bool bThisItemOnly=false) const;
	bool IsExpand() const;

	bool IsStatusEnabled() const;
	unsigned int GetStatus() const;
	unsigned int GetLimitStatus() const;

public:
	bool IsStatusVisibled() const;
	bool IsStatusKernel() const;
	bool IsStatusKernelItem() const;
	bool IsStatusKernelItem1D() const;
	bool IsStatusKernelItem2D() const;
	bool IsStatusKernelItemClass() const;
	bool IsStatusKernelItemList() const;
	bool IsStatusKernelArray() const;
	bool IsStatusKernelArrayClass() const;
	bool IsStatusKernelArrayList() const;
	bool IsApplyToAll() const;
	void Kernel(bool bValue);
	bool ApplyToAll(bool bValue);

	bool GetEnumCount(int &iCount) const;
	bool GetEnumItem(int iItem,int iSize,wchar_t *pEnum,bool &bEnabled) const;
	virtual bool vf_GetEnumItem(int iItem,int iSize,wchar_t *pEnum,int &iCurrent) const;
protected:
private:
protected:

public:
private:
	
};
