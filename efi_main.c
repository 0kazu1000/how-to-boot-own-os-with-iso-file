/*

COMMAND:
    gcc -shared -nostdlib -mno-red-zone -fno-stack-protector -Wall -e EfiMain efi_main.c -o efi_main.dll

    objcopy --target=efi-app-x86_64 efi_main.dll bootx64.efi

    make directory : CD
    is structed below

    CD                        directory (its okay to set any name, because this directory become root directory.)
    CD/EFI/BOOT/bootx64.efi   object file you made
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


    for directory -> iso file,
    download imgburn from https://www.imgburn.com/,
    and create file from directory.

    and, make virtual machine on virtual box
    type : Other
    version : Other / Unknown (64bit)
    (dont forget enable the EFI!)

*/
typedef unsigned char       BOOLEAN;
typedef signed long         INTN;
typedef signed char         INT8;
typedef signed short        INT16;
typedef signed long         INT32;
typedef signed long long    INT64;
typedef unsigned long       UINTN;
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned long       UINT32;
typedef unsigned long long  UINT64;
typedef unsigned char       CHAR8;
typedef unsigned short      CHAR16;
typedef void                VOID;
typedef unsigned char       EFI_GUID[128];
typedef UINTN               EFI_STATUS;
typedef VOID*               EFI_HANDLE;
typedef VOID*               EFI_EVENT;
typedef UINT64              EFI_LBA;
typedef UINTN               EFI_TPL;
typedef unsigned char       EFI_MAC_ADDRESS[32];
typedef unsigned char       EFI_IPv4_ADDRESS[4];
typedef unsigned char       EFI_IPv6_ADDRESS[16];
typedef unsigned char       EFI_IP_ADDRESS[16];

#define IN
#define OUT
#define OPTIONAL
#define CONST         const
#define EFIAPI
#define EFI_SUCCESS   (0)

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// - UEFI Specification, Version 2.8 Errata B (from p442)
typedef struct
{
    UINT16 ScanCode;
    CHAR16 UnicodeChar;
}
EFI_INPUT_KEY;

// - UEFI Specification, Version 2.8 Errata B (from p90)
typedef struct
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
}
EFI_TABLE_HEADER;


// - UEFI Specification, Version 2.8 Errata B (from p445)
typedef EFI_STATUS(EFIAPI* EFI_TEXT_STRING) (IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This, IN CHAR16* String);


// - UEFI Specification, Version 2.8 Errata B (from p443)
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    //EFI_TEXT_RESET Reset;
    VOID* Reset;

    EFI_TEXT_STRING OutputString;
    //EFI_TEXT_TEST_STRING TestString;
    VOID* TestString;
    //EFI_TEXT_QUERY_MODE QueryMode;
    VOID* QueryMode;
    //EFI_TEXT_SET_MODE SetMode;
    VOID* SetMode;
    //EFI_TEXT_SET_ATTRIBUTE SetAttribute;
    VOID* SetAttribute;
    //EFI_TEXT_CLEAR_SCREEN ClearScreen;
    VOID* ClearScreen;
    //EFI_TEXT_SET_CURSOR_POSITION SetCursorPosition;
    VOID* SetCursorPosition;
    //EFI_TEXT_ENABLE_CURSOR EnableCursor;
    VOID* EnableCursor;
    //SIMPLE_TEXT_OUTPUT_MODE* Mode;
    VOID* Mode;

} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// - UEFI Specification, Version 2.8 Errata B (from p92)
typedef struct
{
    EFI_TABLE_HEADER                 Hdr;
    CHAR16*                          FirmwareVendor;
    UINT32                           FirmwareRevision;
    EFI_HANDLE                       ConsoleInHandle;
    
    //EFI_SIMPLE_TEXT_INPUT_PROTOCOL*  ConIn;
    VOID*                            ConIn;
    
    EFI_HANDLE                       ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
    EFI_HANDLE                       StandardErrorHandle;
}
EFI_SYSTEM_TABLE;


EFI_STATUS EFIAPI EfiMain(IN EFI_HANDLE h, IN EFI_SYSTEM_TABLE* SystemTable)
{
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello, World! :^D\n");
    while (1);
    return EFI_SUCCESS;
}
