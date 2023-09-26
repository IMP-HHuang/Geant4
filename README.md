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
  - G4UniformRand() 函数给的随机数是从随机数表中直接读取的，不改变CLHEP:HepRandom::setTheSeed(seed)的seed，每次获得的随机数是一样的，多个文件同时模拟的时候要注意。
  - 粒子直接发射到材料边界谁都不会管
  - Physics list
    - G4EmstandardPhysics_option4 : 580 MeV 以下的alpha粒子模拟时，不会考虑次级电子
