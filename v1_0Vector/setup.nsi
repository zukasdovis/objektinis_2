!include "MUI2.nsh"

; =============================================
; Pagrindiniai nustatymai
; =============================================
Name "Studentas v1.5"
OutFile "Studentas_Setup.exe"
InstallDir "$PROGRAMFILES\VU\Vardenis-Pavardenis"
RequestExecutionLevel admin

; =============================================
; MUI puslapiai
; =============================================
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"

; =============================================
; Diegimas
; =============================================
Section "Pagrindinė programa" SEC01
    SetOutPath "$INSTDIR"

    ; Programa
    File "build\programa.exe"

    ; Testavimo failai
    File "studentai_10000.txt"
    File "studentai_100000.txt"

    ; Uninstaller
    WriteUninstaller "$INSTDIR\uninstall.exe"

    ; =============================================
    ; Darbalaukio nuoroda
    ; =============================================
    CreateShortcut "$DESKTOP\Studentas.lnk" "$INSTDIR\programa.exe"

    ; =============================================
    ; Start meniu nuoroda
    ; =============================================
    CreateDirectory "$SMPROGRAMS\VU\Vardenis-Pavardenis"
    CreateShortcut "$SMPROGRAMS\VU\Vardenis-Pavardenis\Studentas.lnk" "$INSTDIR\programa.exe"

    ; =============================================
    ; Administratoriaus teisės
    ; =============================================
    WriteRegStr HKLM \
        "SOFTWARE\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" \
        "$INSTDIR\programa.exe" \
        "RUNASADMIN"

    ; Add/Remove Programs įrašas
    WriteRegStr HKLM \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\Studentas" \
        "DisplayName" "Studentas v1.5"
    WriteRegStr HKLM \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\Studentas" \
        "UninstallString" "$INSTDIR\uninstall.exe"
    WriteRegStr HKLM \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\Studentas" \
        "InstallLocation" "$INSTDIR"
    WriteRegStr HKLM \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\Studentas" \
        "Publisher" "VU"
SectionEnd

; =============================================
; Pašalinimas
; =============================================
Section "Uninstall"
    Delete "$INSTDIR\programa.exe"
    Delete "$INSTDIR\studentai_10000.txt"
    Delete "$INSTDIR\studentai_100000.txt"
    Delete "$INSTDIR\uninstall.exe"

    ; Nuorodų šalinimas
    Delete "$DESKTOP\Studentas.lnk"
    Delete "$SMPROGRAMS\VU\Vardenis-Pavardenis\Studentas.lnk"

    ; Aplankų šalinimas
    RMDir "$SMPROGRAMS\VU\Vardenis-Pavardenis"
    RMDir "$SMPROGRAMS\VU"
    RMDir "$INSTDIR"
    RMDir "$PROGRAMFILES\VU"

    ; Registry šalinimas
    DeleteRegValue HKLM \
        "SOFTWARE\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" \
        "$INSTDIR\programa.exe"
    DeleteRegKey HKLM \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\Studentas"
SectionEnd