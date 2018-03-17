set workspace=%~dp0
set depot_tools_path=%workspace%..\common\depot_tools
set python_path=%depot_tools_path%\python276_bin
set PATH=%depot_tools_path%;%python_path%;%PATH%
call ninja -C out/debug
