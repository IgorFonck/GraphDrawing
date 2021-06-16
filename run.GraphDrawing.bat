@ECHO OFF
ECHO GRAPH DRAWING WITH OGDF
:start
ECHO.
set step=
set /p step="Step: "
set nmax=
set /p nmax="N max: "
shift
shift
ECHO Starting to compile...
c++ -Ibuild/include -Iinclude -o main.o -c main.cpp
ECHO Generating executable...
c++ -o GraphDrawing -Lbuild main.o -lOGDF -lCOIN
ECHO Compilation done!
ECHO Running program...
GraphDrawing.exe %step% %nmax%
ECHO Ploting graph on python...
py plot_graph.py
ECHO Done!
set choice=
set /p choice="Run again? [y/n]: "
echo '%choice%'
if not '%choice%'=='' set choice=%choice:~0,1%
if '%choice%'=='y' goto start
PAUSE