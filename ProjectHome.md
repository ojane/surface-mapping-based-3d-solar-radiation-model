1.	Requirements
The program is a freeware licensed under terms of the GNU General Public License (GPL) and runs under Windows operating systems with hardware and software support for NVIDIA CUDA and OpenGL. A minimum of 4 GB system memory and 1 GB video memory is recommended. The full source codes for SURFSUN3D and the demonstrated prototype system is available at https://code.google.com/p/surface-mapping-based-3d-solar-radiation-model/.

2.	Configuration
Mandatory:
1)	Install Visual Studio 2010 with C++ checked.
2)	Decompress ' dependencies.rar" and 'bin.rar'.
3)	Add "SURSUN3D/dependencies/bin" to system environment variable "path". The folder 'dependences' contains all libraries, headers and dlls required for runtime and development.
4)	Install qt-opensource-windows-x86-vs2010-4.8.6.exe and qt-vs-addin-1.1.11-opensource.exe  (http://download.qt-project.org/archive/qt/4.8/4.8.6/) .
5)	Install CUDA driver 'devdriver\_4.2\_winvista-win7\_32\_301.32\_general.exe' (http://developer.download.nvidia.com/compute/cuda/4_2/rel/drivers/devdriver_4.2_winvista-win7_32_301.32_general.exe) and CUDA Toolkit 'cudatoolkit\_4.2.9\_win\_32.msi'. (http://developer.download.nvidia.com/compute/cuda/4_2/rel/toolkit/cudatoolkit_4.2.9_win_32.msi)
6)	Make the 'Working directory' of VS2010 is set to $(OutDir) to run in debug model
Optional:
1)	Compile osgEarth (https://github.com/gwaldron/osgearth). The folder ' dependencies' contains a workable copy of the third-party libraries necessary for compiling osgEarth.

3.	Developer
Jianming LIANG, PhD., ljm35@163.com, Institute of Remote Sensing and Digital Earth, Chinese Academy of Sciences.

4.	References
Liang, J., Gong, J., & Zhou, J., et al. , 2015. An open-source 3D solar radiation model integrated with a 3D Geographic Information System. Environmental Modelling & Software, 64, 94–101.

Liang, J., Gong, J., Li, W., & Ibrahim, A. N., 2014. A visualization-oriented 3D method for efficient computation of urban solar radiation based on 3D–2D surface mapping. International Journal of Geographical Information Science, 28(4), 780–798.
