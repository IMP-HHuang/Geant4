# Geant4

## Compile
  - cd bulid
  - cmake ..
  - make
## Run
  - 注意修改CMakeLists.txt中ROOT库的位置（ include_directories(/opt/ROOT/root_v6.16.00/include) ）
  - ./DSSD
  -  /run/beamOn Number
  -  exit(必须正常退出，否则root文件无法保存)
## 一些模拟经验
  - 粒子直接发射到材料边界谁都不会管
