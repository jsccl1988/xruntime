echo on
git clone https://github.com/openssl/openssl.git .
rem 迁出稳定版本1.0.2j，并建立自己本地分支b1.0.2j
git checkout OpenSSL_1_0_2j -b b1.0.2j

rem 编译x86位参考INSTALL.W32说明文件
rem 如果你要编译不同的visualStudio版本，每个vs版本要单独开一个cmd窗口来操作，以免受到上一个vs版本环境变量的影响。
rem 使用vs2015 x86编译环境，运行下面这句话，就启用了vs2015的x86环境
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\vcvars32.bat"

rem 一定要注意INSTALL.W32的文档说明，win32 release 版本需要指定no-asm，并且使用ms\do_nasm.bat脚本

rem 生成win32/release静态库lib
nmake -f ms\nt.mak clean
rmdir /S /Q out32
rmdir /S /Q tmp32
perl Configure VC-WIN32 no-asm --prefix=C:/install/openssl-1.0.2j/vs2015/lib/win32/release
ms\do_nasm.bat
nmake -f ms\nt.mak install

rem 生成win32/release动态库dll
nmake -f ms\ntdll.mak clean
rmdir /S /Q out32dll
rmdir /S /Q tmp32dll
perl Configure VC-WIN32 no-asm --prefix=C:/install/openssl-1.0.2j/vs2015/dll/win32/release
ms\do_nasm.bat
nmake -f ms\ntdll.mak install

rem 生成win32/debug静态库lib
nmake -f ms\nt.mak clean
rmdir /S /Q out32.dbg
rmdir /S /Q tmp32.dbg
perl Configure debug-VC-WIN32 no-asm --prefix=C:/install/openssl-1.0.2j/vs2015/lib/win32/debug
ms\do_ms.bat
nmake -f ms\nt.mak install

rem 生成win32/debug动态库dll
nmake -f ms\ntdll.mak clean
rmdir /S /Q out32dll.dbg
rmdir /S /Q tmp32dll.dbg
perl Configure debug-VC-WIN32 no-asm --prefix=C:/install/openssl-1.0.2j/vs2015/dll/win32/debug
ms\do_ms.bat
nmake -f ms\ntdll.mak install

rem 编译x64位参考INSTALL.W64说明文件
rem 如果你要编译不同的visualStudio版本，每个vs版本要单独开一个cmd窗口来操作，以免受到上一个vs版本环境变量的影响。
rem 使用vs2015 x64编译环境，如果使用其他vs版本，只需修改这个运行环境
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64\vcvars64.bat"

rem 生成win64/release静态库lib
nmake -f ms\nt.mak clean
rmdir /S /Q out32
rmdir /S /Q tmp32
perl Configure VC-WIN64A --prefix=C:/install/openssl-1.0.2j/vs2015/lib/win64/release
ms\do_win64a.bat
nmake -f ms\nt.mak install

rem 生成win64/release动态库dll
nmake -f ms\ntdll.mak clean
rmdir /S /Q out32dll
rmdir /S /Q tmp32dll
perl Configure VC-WIN64A --prefix=C:/install/openssl-1.0.2j/vs2015/dll/win64/release
ms\do_win64a.bat
nmake -f ms\ntdll.mak install

rem 生成win64/debug静态库lib
nmake -f ms\nt.mak clean
rmdir /S /Q out32.dbg
rmdir /S /Q tmp32.dbg
perl Configure debug-VC-WIN64A --prefix=C:/install/openssl-1.0.2j/vs2015/lib/win64/debug
ms\do_win64a.bat
nmake -f ms\nt.mak install

rem 生成win64/debug动态库dll
nmake -f ms\ntdll.mak clean
rmdir /S /Q out32dll.dbg
rmdir /S /Q tmp32dll.dbg
perl Configure debug-VC-WIN64A --prefix=C:/install/openssl-1.0.2j/vs2015/dll/win64/debug
ms\do_win64a.bat
nmake -f ms\ntdll.mak install
