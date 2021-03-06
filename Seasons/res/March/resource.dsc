#
FILE DESCRIPTION
BEGINFILE
# old style comment
// new style comment

ENDIAN LITTLE

TYPE DWORD:BYTE[4];FieldDWORD
TYPE WORD:BYTE[2];FieldWORD

TYPE V_INTSTRING
BEGIN
  UNION V_NAME
  BEGIN  
  WORD ValueOrBegin;
  CASE ValueOrBegin==0xffff;
  DWORD Ordinal;
  ELSE
  USTRING UString;
  END
END

TYPE RESOURCEHEADER
BEGIN
  DWORD DataSize,SIZE;
  DWORD HeaderSize,SIZE;
  V_INTSTRING TYPE;
  V_INTSTRING NAME;
  ALIGN DWORD;
  DWORD DataVersion,VERSION;
  WORD  MemoryFlags;
  WORD  LanguageId;
  DWORD Version;
  DWORD Characteristics;
END

ENDFILE
