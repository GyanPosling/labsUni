# PowerMonitorA4

Компактный оконный виджет мониторинга питания для варианта A4.

## Структура

- `include/` - заголовочные файлы
- `src/` - исходные файлы приложения
- `CMakeLists.txt` - сборка проекта через CMake
- `CMakePresets.json` - готовый пресет для MSYS2 UCRT Qt

## Сборка

Для установленного MSYS2 UCRT Qt:

```powershell
cmake --preset msys2-ucrt
cmake --build --preset msys2-ucrt
```

Исполняемый файл появится в:

```text
build/PowerMonitorA4.exe
```

Если Qt установлен в другом месте, укажите свой путь:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:\path\to\qt" -DCMAKE_CXX_COMPILER="C:\path\to\g++.exe"
cmake --build build
```
