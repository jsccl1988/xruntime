set workspace=%~dp0
set depot_tools_path=%workspace%..\common\depot_tools
set python_path=%depot_tools_path%\python276_bin
set PATH=%depot_tools_path%;%python_path%;%PATH%
set DEPOT_TOOLS_WIN_TOOLCHAIN=0
call gn --root=src --ide=vs args out/debug
rem call gn gen --root=src --ide=vs out/debug