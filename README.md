# MFC_Menu - Custom Owner-Draw Menu (CNewMenu)

Full example of a self-drawing MFC menu class based on the provided `DrawItem` / `MeasureItem` implementation.

## Features

- Owner-draw menu items with custom background / hover / disabled colors
- Icon support on the left
- Separators
- Sub-menu indicators
- Shortcut text support
- Configurable font, item height, menu width, icon size
- Proper memory management for `itemData` (`StruItemInfo`)

## Project Structure

```
MFC_Menu/
├── README.md
├── Source/
│   ├── NewMenu.h          // CNewMenu class declaration
│   └── NewMenu.cpp        // Full implementation (DrawItem + MeasureItem + helpers)
├── Sample/
│   ├── MFC_Menu.h / .cpp  // Application class
│   ├── MFC_MenuDlg.h / .cpp // Dialog that demonstrates the menu
│   ├── resource.h
│   ├── MFC_Menu.rc       // Minimal resources
│   ├── stdafx.h / stdafx.cpp
│   └── targetver.h
└── MFC_Menu.sln / MFC_Menu.vcxproj   // Visual Studio project files (VS2019+)
```

## How to use

1. Open `MFC_Menu.sln` in Visual Studio (with MFC support installed).
2. Build & run (x86 or x64, Debug/Release).
3. Click the **Show Custom Menu** button → popup menu appears with icons, separators, shortcuts and hover effects.

### Core usage snippet

```cpp
CNewMenu menu;
menu.CreatePopupMenu();
menu.SetColors(...);          // optional
menu.SetFont(_T("Segoe UI"), 16);
menu.SetIconSize(16, 16);
menu.SetItemHeight(28);
menu.SetMenuWidth(220);

// Add items (icons optional)
menu.AddMenuItem(ID_FILE_NEW,  _T("New"),    _T("Ctrl+N"), hIconNew);
menu.AddSeparator();
menu.AddMenuItem(ID_FILE_OPEN, _T("Open"),   _T("Ctrl+O"), hIconOpen);
menu.AddSubMenu(_T("Recent"), &subMenu);

// Track
CPoint pt;
GetCursorPos(&pt);
menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
```

## Key implementation notes

- Items are created with `MF_OWNERDRAW` and a heap-allocated `StruItemInfo*` stored in `itemData`.
- `MeasureItem` / `DrawItem` are overridden on `CMenu` (self-draw style).
- Memory is cleaned in `DeleteItem` and destructor.
- Colors, sizes and font are fully configurable via public setters.

## Requirements

- Visual Studio 2017 or newer with **Desktop development with C++** + **MFC** workload
- Windows SDK

## License

Free to use / modify for any purpose.
